#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

int main() {
	//------------------------练习1：分离RGB--------------------------------------

	cv::Mat image = imread("ee.png");
	std::vector<cv::Mat> channels;				//定义Mat型Vector变量
	cv::split(image, channels);					//调用split函数
	cv::Mat B = channels.at(0);
	cv::Mat G = channels.at(1);
	cv::Mat R = channels.at(2);
	namedWindow("channel blue", CV_WINDOW_NORMAL);
	imshow("channel blue", B);
	namedWindow("channel green", CV_WINDOW_NORMAL);
	imshow("channel green", G);
	namedWindow("channel red", CV_WINDOW_NORMAL);
	imshow("channel red", R);
	waitKey(0);

	//----------------------------练习2：打开摄像头----------------------------------
	VideoCapture cap;
	cap.open(0);								//打开0号摄像头
	if (!cap.isOpened())						//检验摄像头是否打开
	{
		std::cout << "打开错误" << std::endl;
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);			//获取cap帧数
	std::cout << "fps" << fps << std::endl;
	while (1)
	{
		cv::Mat frame;
		bool rSucess = cap.read(frame);				//布尔型变量 rSucess
		if (!rSucess)
		{
			std::cout << "打开错误" << std::endl;
			break;
		}
		else
		{
			cv::imshow("frame", frame);			//显示画面
		}
		waitKey(1);								//控制画面刷新间隔
	}


	//----------------------------------练习3：绘制圆、直线、矩形--------------------------------
	cv::Mat disMat(200, 200, CV_8UC3);
	cv::Point pt1;
	pt1.x = 100;
	pt1.y = 100;
	cv::Point pt2;
	pt2.x = 100;
	pt2.y = 200;
	circle(disMat, pt1, 50, CV_RGB(0, 255, 50), 5, 8, 0);				//画圆
	line(disMat, pt1, pt2, CV_RGB(1, 180, 50), 3, 8, 0);		//画线
	cv::Rect rect;
	rect.x = 50;
	rect.y = 50;
	rect.width = 100;
	rect.height = 100;
	rectangle(disMat, rect, CV_RGB(255, 58, 45), 1, 8, 0);				//画矩形
	imshow("disMat", disMat);
	waitKey(0);


	//----------------练习4：获得图像直方图数据----------------------------------
	cv::Mat M1 = imread("ee.png", 0);
	//imshow("", M1);
	double histgram[256]{ 0 };					//建立并初始化数据
	int he;
	int value;
	int row = M1.rows;						//统计行数
	int col = M1.cols;						//统计列数
	std::cout << "行数" << row << std::endl;
	std::cout << "列数" << col << std::endl;
	for (int j = 0; j < row; j++)			//遍历图像
	{
		for (int i = 0; i < col; i++)
		{
			value = M1.at<uchar>(j, i);
			histgram[value]++;
		}
	}
	std::cout << "灰度值列表" << std::endl;			//输出灰度数据数组
	for (int a = 0; a < 256; a++)
	{
		std::cout << histgram[a] << std::endl;
	}
	std::cout << "校验总像素数" << std::endl;
	he = 0;
	for (int i = 0; i < 256; i++)
	{
		he = he + histgram[i];
	}
	std::cout << he << std::endl;
	waitKey(0);


	//---------------------------练习5：绘制直方图-------------------------------------
	double histgram2[256];
	for (int i = 0; i < 256; i++)
	{
		histgram2[i] = histgram[i] / he;					//归一化
	}
	cv::Mat M2(3000, 10240, CV_8UC3);

	for (int i = 0; i < 256; i++)
	{
		cv::Point pt3;
		pt3.x = i * 40;
		pt3.y = 3000 - (15000 * histgram2[i]);
		circle(M2, pt3, 20, CV_RGB(0, 255, 50), -1, 8, 0);   //画圆表示

	}

	namedWindow("灰度图", CV_WINDOW_NORMAL);
	imshow("灰度图", M2);
	waitKey(0);








}

