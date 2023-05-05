#include"opencv.hpp"
#include"GrayChange.cpp"
#include"EdgeDetection.cpp"
#include<random>
namespace image_lib
{
    enum SketchColorMode{color,gray};
    enum FleetColor{green,red,blue};//赋值这一步属于多此一举，仅作提醒作用
    enum OneLastKissMode{normal,reverse};
    /*
    功能：将图片变为毛玻璃特效
    约束：
        输入：原始图像（Mat），输出：处理后图像(Mat)
        之后的函数也同样适用此约束，之后不再赘述
    */
    cv::Mat Glass(const cv::Mat &originImage)
    {
        //复制一份原图
        cv::Mat glassImage=originImage.clone();
        int i,j;
        int randX,randY;//随机数[-1,1]
        std::default_random_engine generater;
	    std::uniform_int_distribution<int>randomX(-1, 1);
        std::uniform_int_distribution<int>randomY(-1, 1);
        for(i=1;i<originImage.rows-1;i++)
        {
            for(j=1;j<originImage.cols-1;j++)
            {
                //随机将邻域内一个像素作为当前像素
                randX=randomX(generater);
                randY=randomY(generater);
                while(randX==0&&randY==0)
                {
                    randX=randomX(generater);
                    randY=randomY(generater);
                }
                glassImage.at<cv::Vec3b>(i,j)=originImage.at<cv::Vec3b>(i+randX,j+randY);
            }
        }
        return glassImage;
    }

    //功能：将输入图片变为浮雕特效
    cv::Mat Relief(const cv::Mat &originImage)
    {
        cv::Mat output=originImage.clone();
        int rows=originImage.rows;
        int cols=originImage.cols;
        //todo:边缘检测
        if(originImage.channels()==1)
        {
            for(int i=1;i<rows-1;i++)
            {
                for(int j=1;j<cols-1;j++)
                {
                    output.at<uchar>(i,j)=std::clamp(originImage.at<uchar>(i + 1, j + 1) - originImage.at<uchar>(i - 1, j - 1) + 128,0,255);
                }
            }
        }
        else if(originImage.channels()==3)
        {
            for(int i=1;i<rows-1;i++)
            {
                for(int j=1;j<cols-1;j++)
                {
                    output.at<cv::Vec3b>(i,j)[0]=std::clamp(originImage.at<cv::Vec3b>(i + 1, j + 1)[0] - originImage.at<cv::Vec3b>(i - 1, j - 1)[0] + 128,0,255);
                    output.at<cv::Vec3b>(i,j)[1]=std::clamp(originImage.at<cv::Vec3b>(i + 1, j + 1)[1] - originImage.at<cv::Vec3b>(i - 1, j - 1)[1] + 128,0,255);
                    output.at<cv::Vec3b>(i,j)[2]=std::clamp(originImage.at<cv::Vec3b>(i + 1, j + 1)[2] - originImage.at<cv::Vec3b>(i - 1, j - 1)[2] + 128,0,255);
                }
            }
        }
        return output;
    }

    cv::Mat Sketch(const cv::Mat &originImage,int size,int sigma,SketchColorMode mode=SketchColorMode::color)//素描特效和彩铅特效
    {
        //0.去色
        //1.反转变换
        cv::Mat gray;
        Decolor(originImage,gray);
        cv::Mat revGray=GrayscaleChange(originImage,grayscaleChangeMode::Reverse);
        cv::GaussianBlur(revGray,revGray,cv::Size(size,size),sigma);
        //3.颜色叠加，混合公式：C =MIN A+（A×B）/（255−B）,255
        cv::Mat output(gray.size(), CV_8UC3);
        //彩色模式
        if(originImage.channels()==3&&mode==SketchColorMode::color)
        {
            for(int i=0;i<originImage.rows;i++)
            {
                for(int j=0;j<originImage.cols;j++)
                {
                    for(int k=0;k<originImage.channels();k++)
                    {
                        int B=revGray.at<uchar>(i,j);
                        int A=originImage.at<cv::Vec3b>(i,j)[k];     
                        int C=std::min(A + (A * B) / (255 - B), 255);
                        output.at<cv::Vec3b>(i,j)[k]=C;
                    }          
                }
            }
        }
        else if(originImage.channels()==1||mode==SketchColorMode::gray)
        {
            for(int i=0;i<originImage.rows;i++)
            {
                for(int j=0;j<originImage.cols;j++)
                {
                    for (size_t k = 0; k < 3; k++)
                    {
                        int A=gray.at<cv::Vec3b>(i,j)[k];
                        int B=revGray.at<uchar>(i,j);
                        int C=std::min(A + (A * B) / (255 - B), 255);

                        output.at<cv::Vec3b>(i,j)[k]=C;
                    }
                }
            }
        }
        return output;
    }

    cv::Mat Mask(const cv::Mat &originImage,int size)//马赛克的实现
    {
        if(size>originImage.rows||size>originImage.cols) return originImage;//最重要的一步
        cv::Mat mask=originImage.clone();
        for(int i=0;i<originImage.rows-size;i++)
        {
            for(int j=0;j<originImage.cols-size;j++)
            {
                if(i%5==0&&j%5==0)
                {
                    int oB=originImage.at<cv::Vec3b>(i,j)[0];
                    int oG=originImage.at<cv::Vec3b>(i,j)[1];
                    int oR=originImage.at<cv::Vec3b>(i,j)[2];
                    for(int k=0;k<size;k++)
                    {
                        for(int l=0;l<size;l++)
                        {
                            mask.at<cv::Vec3b>(i+k,j+l)[0]=oB;
                            mask.at<cv::Vec3b>(i+k,j+l)[1]=oG;
                            mask.at<cv::Vec3b>(i+k,j+l)[2]=oR;
                        }
                    }
                }
            }
        }
        return mask;
    }
    /*
    功能：基于经验公式的怀旧特效
        B= 0.272 * r + 0.534 * g + 0.131 * b
        G = 0.349 * r + 0.686 * g + 0.168 * b
        R = 0.393 * r + 0.769 * g + 0.189 * b
    */
    cv::Mat Old(const cv::Mat &originImage)
    {
        cv::Mat output=originImage.clone();
        for(int i=0;i<originImage.rows;i++)
        {
            for(int j=0;j<originImage.cols;j++)
            {
                float b=(double)originImage.at<cv::Vec3b>(i,j)[0];
                float g=(double)originImage.at<cv::Vec3b>(i,j)[1];
                float r=(double)originImage.at<cv::Vec3b>(i,j)[2];

                float B=std::min( 0.272 * r + 0.534 * g + 0.131 * b,255.0);
                float G=std::min( 0.349 * r + 0.686 * g + 0.168 * b,255.0);
                float R=std::min( 0.393 * r + 0.769 * g + 0.189 * b,255.0);

                output.at<cv::Vec3b>(i,j)[0]=(int)B;
                output.at<cv::Vec3b>(i,j)[1]=(int)G;
                output.at<cv::Vec3b>(i,j)[2]=(int)R;
            }
        }
        return output;
    }

    cv::Mat Fleet(const cv::Mat &originImage,FleetColor channel=FleetColor::blue)
    {
        cv::Mat output=originImage.clone();
        for(int i=0;i<originImage.rows;i++)
        {
            for(int j=0;j<originImage.cols;j++)
            {
                output.at<cv::Vec3b>(i,j)[channel]=sqrt(originImage.at<cv::Vec3b>(i,j)[channel])*14;//好吧，说FleetColor赋值多余是在骗你，其实数值还是有设计过的w
            }
        }
        return output;
    }   

    cv::Mat OneLastKiss(const cv::Mat &originImage,OneLastKissMode mode=OneLastKissMode::normal)//整活部分来咯
    {
        cv::Mat edgeImage; 
        cv::Mat output(originImage.rows,originImage.cols,CV_8UC3);
        
        CannyEdgeDetection(originImage,edgeImage,50,150);//边缘提取
        cv::Mat sketch=Sketch(originImage,15,15,gray);
        // 绘制渐变矩形
        cv::Mat gradient(edgeImage.rows, edgeImage.cols, CV_8UC3,cv::Scalar(0,0,0));
        double m=1.0;//渐变方向的斜率
        double b=0.0;
        
        //生成渐变图，要实现颜色过渡需要使用插值算法
        gradient=GradientColor(cv::Scalar(255,82,95),cv::Scalar(85,72,209),cv::Scalar(255,82,95),1,edgeImage.rows, edgeImage.cols);
        
        // 将渐变矩形与边缘提取图像进行混合
        
        for (int i = 0; i < sketch.rows; i++)
        {
            for (int j = 0; j < sketch.cols; j++)
            {
                
                if(mode==OneLastKissMode::normal)
                {
                    if (edgeImage.at<uchar>(i, j) > 0)
                    {
                        float alpha = static_cast<float>(edgeImage.at<uchar>(i, j)) / 255.0f;
                        output.at<cv::Vec3b>(i, j)[0] = (1 - alpha) * output.at<cv::Vec3b>(i, j)[0] + alpha  * gradient.at<cv::Vec3b>(i, j)[0];
                        output.at<cv::Vec3b>(i, j)[1] = (1 - alpha) * output.at<cv::Vec3b>(i, j)[1] + alpha  * gradient.at<cv::Vec3b>(i, j)[1];
                        output.at<cv::Vec3b>(i, j)[2] = (1 - alpha) * output.at<cv::Vec3b>(i, j)[2] + alpha  * gradient.at<cv::Vec3b>(i, j)[2];
                    }
                }
                else if(mode==OneLastKissMode::reverse){
                    if (sketch.at<cv::Vec3b>(i, j)[0] == 255)
                    {
                        output.at<cv::Vec3b>(i, j)[0] = (1 - sketch.at<cv::Vec3b>(i, j)[0]/255.0f) * output.at<cv::Vec3b>(i, j)[0] + sketch.at<cv::Vec3b>(i, j)[0]/255.0f  * gradient.at<cv::Vec3b>(i, j)[0];
                        output.at<cv::Vec3b>(i, j)[1] = (1 - sketch.at<cv::Vec3b>(i, j)[1]/255.0f) * output.at<cv::Vec3b>(i, j)[1] + sketch.at<cv::Vec3b>(i, j)[1]/255.0f  * gradient.at<cv::Vec3b>(i, j)[1];
                        output.at<cv::Vec3b>(i, j)[2] = (1 - sketch.at<cv::Vec3b>(i, j)[2]/255.0f) * output.at<cv::Vec3b>(i, j)[2] + sketch.at<cv::Vec3b>(i, j)[2]/255.0f  * gradient.at<cv::Vec3b>(i, j)[2];
                    }
                }
            }
        }
        return output;
    }
};