#include"Module.cpp"
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
};