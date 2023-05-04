#include <random>
#include"opencv.hpp"

namespace image_lib
{
  /*
    功能：创建一个纯色图片
    约束：
      输入:分辨率(float)，颜色(float)，输出：纯色图（Mat）
    */
    cv::Mat CreateSolidColorImage(const int x,
                                  const int y,
                                  const float r,const float g,const float b)
    {
        return cv::Mat(x,y,CV_8UC3,cv::Scalar(b,g,r));
    }

    //生成噪声图
    cv::Mat Salt(const int x,const int y,const int seed)
    {
      cv::Mat image=CreateSolidColorImage(x,y,0,0,0);
      //生成随机种子
      std::default_random_engine generater;
	    std::uniform_int_distribution<int>randomRow(0, image.rows - 1);
	    std::uniform_int_distribution<int>randomCol(0, image.cols - 1);
    
	    int i, j;
	    for (int k = 0; k < seed; k++)
	    {
	    	i = randomCol(generater);
	    	j = randomRow(generater);
	    	if (image.channels() == 1)
	    	{
	    		image.at<uchar>(j, i) = 255;
	    	}
	    	else if (image.channels() == 3)
	    	{
	    		image.at<cv::Vec3b>(j, i)[0] = 255;
	    		image.at<cv::Vec3b>(j, i)[1] = 255;
	    		image.at<cv::Vec3b>(j, i)[2] = 255;
	    	}
	    }
      return image;
    }

    //todo:直方图调整（优先度低）
    //todo:高通/低通滤波（优先度低）
    //todo:频谱图输出（优先度低）    
}