#include"opencv.hpp"
#include <vector>

namespace image_lib
{
    void CannyEdgeDetection(const cv::Mat &originImage,cv::Mat &dstImage,int thre1,int thre2)
    {
        //获取灰度图
        cv::Mat grayImage;
        cv::cvtColor(originImage,grayImage,cv::COLOR_BGR2GRAY);
        //直接拿现成的canny边缘检测
        cv::Canny(grayImage,dstImage,thre1,thre2);
    }

    void GaussFilter(const cv::Mat &originImage,cv::Mat &dstImage,int gaussSize,double sigma)
    {
        //将卷积核的层数变成三的倍数
        if(gaussSize<3) gaussSize=3;
        else gaussSize=(gaussSize/2)*2+1;

        //生成卷积核
        std::vector<std::vector<double>>gaussKernel(gaussSize,std::vector<double>(gaussSize,0));
	    int center = gaussSize / 2;
	    
        double sum = 0;
        for (int i = 0; i < gaussSize; i++)
	    {
		    for (int j = 0; j < gaussSize; j++)
		    {
		    	gaussKernel[i][j] = exp(-((i - center) * (i - center) + (j - center) * (j - center)) / (2 * sigma * sigma));//套用高斯公式
		    	sum += gaussKernel[i][j];
		    }
	    }

        //卷积核的归一化
        double normSum = 1 / sum;
	    for (int i = 0; i < gaussSize; i++)
	    {
	    	for (int j = 0; j < gaussSize; j++)
	    	{
	    		gaussKernel[i][j] *= normSum;
	    	}
	    }

        //遍历每一个像素点进行卷积
        dstImage=cv::Mat(originImage.rows,originImage.cols,CV_8UC3,cv::Scalar(255,255,255));
        int rows = originImage.rows - center;
	    int cols = originImage.cols - center;
        if(originImage.channels()==1)
        {
	        for (int i = center; i < rows; i++) 
	        {
	        	for (int j = center; j < cols; j++) 
	        	{
                    double sum=0;
                    for (int m = -center; m <= center; m++) 
	        		{
	        			for (int n = -center; n <= center; n++) 
	        			{
	        				sum += gaussKernel[center + m][center + n] * originImage.at<uchar>(i + m, j + n);
	        			}
	        		}
	        		dstImage.at<cv::Vec2b>(i, j) = static_cast<uchar>(sum);
	        	}
	        }
        }
        else if(originImage.channels()==3)
        {
            for (int i = center; i < rows; i++) 
	        {
	        	for (int j = center; j < cols; j++) 
	        	{
                    double postPixelR = 0;
                    double postPixelG = 0;
                    double postPixelB = 0;
                    for (int m = -center; m <= center; m++) 
	        		{
	        			for (int n = -center; n <= center; n++) 
	        			{
	        				postPixelB += gaussKernel[center + m][center + n] * originImage.at<cv::Vec3b>(i + m, j + n)[0];
                            postPixelG += gaussKernel[center + m][center + n] * originImage.at<cv::Vec3b>(i + m, j + n)[1];
                            postPixelR += gaussKernel[center + m][center + n] * originImage.at<cv::Vec3b>(i + m, j + n)[2];
	        			}
	        		}
	        		dstImage.at<cv::Vec3b>(i, j)[0] = static_cast<uchar>(postPixelB);
                    dstImage.at<cv::Vec3b>(i, j)[1] = static_cast<uchar>(postPixelG);
                    dstImage.at<cv::Vec3b>(i, j)[2] = static_cast<uchar>(postPixelR);
	        	}
	        }          	
        }
	    //释放内存
	    std::vector<std::vector<double>>().swap(gaussKernel);
    }
}