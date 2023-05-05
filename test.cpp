#include "opencv.hpp"
#include "Module.hpp"
#include "PostProcess.cpp"
#include"EdgeDetection.cpp"
using namespace image_lib;
//дһЩ��������
namespace test
{
   void GrayChangeTest()
   {
       cv::Mat image;   //����һ����ͼ��image
	   image = cv::imread("1.jpg");  //��ȡ�ļ����е�ͼ��
      cv::Mat output;
      Decolor(image,output);
	   imwrite("output/GrayChange/��ɳ_��ת�任.jpg", GrayscaleChange(image,grayscaleChangeMode::Reverse));
	   imwrite("output/GrayChange/��ɳ_�����任.jpg", GrayscaleChange(image,grayscaleChangeMode::Logarithmic));
	   imwrite("output/GrayChange/��ɳ_٤��任.jpg", GrayscaleChange(image,grayscaleChangeMode::Gamma));
      imwrite("output/GrayChange/��ɳ_ȥɫ.jpg",output);
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
      imwrite("output/Filter/��ɳ-����.jpg",Relief(image));
      imwrite("output/Filter/��ɳ-��Ǧ.jpg",Sketch(image,15,15));
      imwrite("output/Filter/��ɳ-����.jpg",Sketch(image,15,15,SketchColorMode::gray));
      imwrite("output/Filter/��ɳ-������.jpg",Mask(image,5));
      imwrite("output/Filter/��ɳ-����.jpg",Old(image));
      imwrite("output/Filter/��ɳ-������.jpg",Fleet(image));
      imwrite("output/Filter/��ɳ-������.jpg",Fleet(image,FleetColor::green));
      imwrite("output/Filter/��ɳ-�����.jpg",Fleet(image,FleetColor::red));
   }

   void EdgeTest()
   {
      //case1
      cv::Mat image=cv::imread("1.jpg");
      cv::Mat dstImage1,dstImage2;
      CannyEdgeDetection(image,dstImage1,50,150);
      GaussFilter(image,dstImage2,9,1);
      imwrite("output/EdgeDetection/��ɳ-��Ե���.jpg",dstImage1);
      imwrite("output/EdgeDetection/��ɳ-��˹�˲�.jpg",dstImage2);
   }
};