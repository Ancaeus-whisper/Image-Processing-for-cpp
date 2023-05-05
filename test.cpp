#include "opencv.hpp"
#include "Module.hpp"
#include "PostProcess.cpp"
#include"EdgeDetection.cpp"
using namespace image_lib;
//Ğ´Ò»Ğ©²âÊÔÓÃÀı
namespace test
{
   void GrayChangeTest()
   {
       cv::Mat image;   //´´½¨Ò»¸ö¿ÕÍ¼Ïñimage
	   image = cv::imread("1.jpg");  //¶ÁÈ¡ÎÄ¼ş¼ĞÖĞµÄÍ¼Ïñ
      cv::Mat output;
      Decolor(image,output);
	   imwrite("output/GrayChange/ÀæÉ³_·´×ª±ä»».jpg", GrayscaleChange(image,grayscaleChangeMode::Reverse));
	   imwrite("output/GrayChange/ÀæÉ³_¶ÔÊı±ä»».jpg", GrayscaleChange(image,grayscaleChangeMode::Logarithmic));
	   imwrite("output/GrayChange/ÀæÉ³_Ù¤Âê±ä»».jpg", GrayscaleChange(image,grayscaleChangeMode::Gamma));
      imwrite("output/GrayChange/ÀæÉ³_È¥É«.jpg",output);
   }

   void SolidColorTest()
   {
      imwrite("output/SolidColor/À¶É«.jpg",CreateSolidColorImage(500,500,0,0,255));
      imwrite("output/SolidColor/ÂÌÉ«.jpg",CreateSolidColorImage(500,500,0,255,0));
      imwrite("output/SolidColor/ºìÉ«.jpg",CreateSolidColorImage(500,500,255,0,0));
   }

   void SaltTest()
   {
      imwrite("output/Salt/ÔëÉù-5.jpg",Salt(500,500,5));
      imwrite("output/Salt/ÔëÉù-25.jpg",Salt(500,500,25));
      imwrite("output/Salt/ÔëÉù-100.jpg",Salt(500,500,100));
      imwrite("output/Salt/ÔëÉù-1000.jpg",Salt(500,500,1000));  
      imwrite("output/Salt/ÔëÉù-10000.jpg",Salt(500,500,10000));  
   }

   void FilterTest()
   {
      cv::Mat image=cv::imread("1.jpg");

      imwrite("output/Filter/ÀæÉ³-Ã«²£Á§.jpg",Glass(image));
      imwrite("output/Filter/ÀæÉ³-¸¡µñ.jpg",Relief(image));
      imwrite("output/Filter/ÀæÉ³-²ÊÇ¦.jpg",Sketch(image,15,15));
      imwrite("output/Filter/ÀæÉ³-ËØÃè.jpg",Sketch(image,15,15,SketchColorMode::gray));
      imwrite("output/Filter/ÀæÉ³-ÂíÈü¿Ë.jpg",Mask(image,5));
      imwrite("output/Filter/ÀæÉ³-»³¾É.jpg",Old(image));
      imwrite("output/Filter/ÀæÉ³-Á÷ÄêÀ¶.jpg",Fleet(image));
      imwrite("output/Filter/ÀæÉ³-Á÷ÄêÂÌ.jpg",Fleet(image,FleetColor::green));
      imwrite("output/Filter/ÀæÉ³-Á÷Äêºì.jpg",Fleet(image,FleetColor::red));
   }

   void EdgeTest()
   {
      //case1
      cv::Mat image=cv::imread("1.jpg");
      cv::Mat dstImage1,dstImage2;
      CannyEdgeDetection(image,dstImage1,50,150);
      GaussFilter(image,dstImage2,9,1);
      imwrite("output/EdgeDetection/ÀæÉ³-±ßÔµ¼ì²â.jpg",dstImage1);
      imwrite("output/EdgeDetection/ÀæÉ³-¸ßË¹ÂË²¨.jpg",dstImage2);
   }
};