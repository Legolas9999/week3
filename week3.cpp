#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

int main() {
	//------------------------��ϰ1������RGB--------------------------------------

	cv::Mat image = imread("ee.png");
	std::vector<cv::Mat> channels;				//����Mat��Vector����
	cv::split(image, channels);					//����split����
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

	//----------------------------��ϰ2��������ͷ----------------------------------
	VideoCapture cap;
	cap.open(0);								//��0������ͷ
	if (!cap.isOpened())						//��������ͷ�Ƿ��
	{
		std::cout << "�򿪴���" << std::endl;
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);			//��ȡcap֡��
	std::cout << "fps" << fps << std::endl;
	while (1)
	{
		cv::Mat frame;
		bool rSucess = cap.read(frame);				//�����ͱ��� rSucess
		if (!rSucess)
		{
			std::cout << "�򿪴���" << std::endl;
			break;
		}
		else
		{
			cv::imshow("frame", frame);			//��ʾ����
		}
		waitKey(1);								//���ƻ���ˢ�¼��
	}


	//----------------------------------��ϰ3������Բ��ֱ�ߡ�����--------------------------------
	cv::Mat disMat(200, 200, CV_8UC3);
	cv::Point pt1;
	pt1.x = 100;
	pt1.y = 100;
	cv::Point pt2;
	pt2.x = 100;
	pt2.y = 200;
	circle(disMat, pt1, 50, CV_RGB(0, 255, 50), 5, 8, 0);				//��Բ
	line(disMat, pt1, pt2, CV_RGB(1, 180, 50), 3, 8, 0);		//����
	cv::Rect rect;
	rect.x = 50;
	rect.y = 50;
	rect.width = 100;
	rect.height = 100;
	rectangle(disMat, rect, CV_RGB(255, 58, 45), 1, 8, 0);				//������
	imshow("disMat", disMat);
	waitKey(0);


	//----------------��ϰ4�����ͼ��ֱ��ͼ����----------------------------------
	cv::Mat M1 = imread("ee.png", 0);
	//imshow("", M1);
	double histgram[256]{ 0 };					//��������ʼ������
	int he;
	int value;
	int row = M1.rows;						//ͳ������
	int col = M1.cols;						//ͳ������
	std::cout << "����" << row << std::endl;
	std::cout << "����" << col << std::endl;
	for (int j = 0; j < row; j++)			//����ͼ��
	{
		for (int i = 0; i < col; i++)
		{
			value = M1.at<uchar>(j, i);
			histgram[value]++;
		}
	}
	std::cout << "�Ҷ�ֵ�б�" << std::endl;			//����Ҷ���������
	for (int a = 0; a < 256; a++)
	{
		std::cout << histgram[a] << std::endl;
	}
	std::cout << "У����������" << std::endl;
	he = 0;
	for (int i = 0; i < 256; i++)
	{
		he = he + histgram[i];
	}
	std::cout << he << std::endl;
	waitKey(0);


	//---------------------------��ϰ5������ֱ��ͼ-------------------------------------
	double histgram2[256];
	for (int i = 0; i < 256; i++)
	{
		histgram2[i] = histgram[i] / he;					//��һ��
	}
	cv::Mat M2(3000, 10240, CV_8UC3);

	for (int i = 0; i < 256; i++)
	{
		cv::Point pt3;
		pt3.x = i * 40;
		pt3.y = 3000 - (15000 * histgram2[i]);
		circle(M2, pt3, 20, CV_RGB(0, 255, 50), -1, 8, 0);   //��Բ��ʾ

	}

	namedWindow("�Ҷ�ͼ", CV_WINDOW_NORMAL);
	imshow("�Ҷ�ͼ", M2);
	waitKey(0);








}

