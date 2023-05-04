#include "opencv.hpp"
#include"GrayChange.cpp"
#include "Module.hpp"
#include "Filters.cpp"
using namespace image_lib;
//写一些测试用例
namespace test
{
   void GrayChangeTest()
   {
       cv::Mat image;   //创建一个空图像image
	   image = cv::imread("1.jpg");  //读取文件夹中的图像

	   imwrite("output/GrayChange/梨沙_反转变换.jpg", GrayscaleChange(image,grayscaleChangeMode::Reverse));
	   imwrite("output/GrayChange/梨沙_对数变换.jpg", GrayscaleChange(image,grayscaleChangeMode::Logarithmic));
	   imwrite("output/GrayChange/梨沙_伽玛变换.jpg", GrayscaleChange(image,grayscaleChangeMode::Gamma));
   }

   void SolidColorTest()
   {
      imwrite("output/SolidColor/蓝色.jpg",CreateSolidColorImage(500,500,0,0,255));
      imwrite("output/SolidColor/绿色.jpg",CreateSolidColorImage(500,500,0,255,0));
      imwrite("output/SolidColor/红色.jpg",CreateSolidColorImage(500,500,255,0,0));
   }

   void SaltTest()
   {
      imwrite("output/Salt/噪声-5.jpg",Salt(500,500,5));
      imwrite("output/Salt/噪声-25.jpg",Salt(500,500,25));
      imwrite("output/Salt/噪声-100.jpg",Salt(500,500,100));
      imwrite("output/Salt/噪声-1000.jpg",Salt(500,500,1000));  
      imwrite("output/Salt/噪声-10000.jpg",Salt(500,500,10000));  
   }

   void FilterTest()
   {
      cv::Mat image=cv::imread("1.jpg");

      imwrite("output/Filter/梨沙-毛玻璃.jpg",Glass(image));
   }
};