#include"opencv.hpp"
#include<random>
namespace image_lib
{
    /*
    功能：将图片变为毛玻璃特效
    约束：
        输入：原始图像（Mat），输出：处理后图像(Mat)
    */
    cv::Mat Glass(cv::Mat originImage)
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
};