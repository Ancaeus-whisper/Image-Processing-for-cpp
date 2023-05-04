#include "opencv.hpp"
#include"GrayChange.cpp"
#include "Module.hpp"
#include "Filters.cpp"
using namespace image_lib;
//дһЩ��������
namespace test
{
   void GrayChangeTest()
   {
       cv::Mat image;   //����һ����ͼ��image
	   image = cv::imread("1.jpg");  //��ȡ�ļ����е�ͼ��

	   imwrite("output/GrayChange/��ɳ_��ת�任.jpg", GrayscaleChange(image,grayscaleChangeMode::Reverse));
	   imwrite("output/GrayChange/��ɳ_�����任.jpg", GrayscaleChange(image,grayscaleChangeMode::Logarithmic));
	   imwrite("output/GrayChange/��ɳ_٤��任.jpg", GrayscaleChange(image,grayscaleChangeMode::Gamma));
   }

   void SolidColorTest()
   {
      imwrite("output/SolidColor/��ɫ.jpg",CreateSolidColorImage(500,500,0,0,255));
      imwrite("output/SolidColor/��ɫ.jpg",CreateSolidColorImage(500,500,0,255,0));
      imwrite("output/SolidColor/��ɫ.jpg",CreateSolidColorImage(500,500,255,0,0));
   }

   void SaltTest()
   {
      imwrite("output/Salt/����-5.jpg",Salt(500,500,5));
      imwrite("output/Salt/����-25.jpg",Salt(500,500,25));
      imwrite("output/Salt/����-100.jpg",Salt(500,500,100));
      imwrite("output/Salt/����-1000.jpg",Salt(500,500,1000));  
      imwrite("output/Salt/����-10000.jpg",Salt(500,500,10000));  
   }

   void FilterTest()
   {
      cv::Mat image=cv::imread("1.jpg");

      imwrite("output/Filter/��ɳ-ë����.jpg",Glass(image));
   }
};