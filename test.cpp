#include"Module.cpp"
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
};