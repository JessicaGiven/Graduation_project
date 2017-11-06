#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//�������������������
bool biggerSort(vector<Point> v1, vector<Point> v2)
{
	return contourArea(v1)>contourArea(v2);
}

int main()
{
	//��Ƶ�����ڣ��ͷ���
	VideoCapture cap("3.AVI");
	if (cap.isOpened() == false)
		return 0;

	//�������
	int i;

	Mat frame;			//��ǰ֡
	Mat foreground;		//ǰ��
	Mat bw;				//�м��ֵ����
	Mat se;				//��̬ѧ�ṹԪ��

	//�û�ϸ�˹ģ��ѵ������ͼ��
	BackgroundSubtractorMOG mog;
	for (i = 0; i<10; ++i)
	{
		cout << "����ѵ������:" << i << endl;
		cap >> frame;
		if (frame.empty() == true)
		{
			cout << "��Ƶ̫֡�٣��޷�ѵ������" << endl;
			getchar();
			return 0;
		}
		mog(frame, foreground, 0.01);
	}

	//Ŀ����ӿ����ɽṹԪ�أ��������ӶϿ���СĿ�꣩
	Rect rt;
	se = getStructuringElement(MORPH_RECT, Size(5, 5));

	//ͳ��Ŀ��ֱ��ͼʱʹ�õ��ı���
	vector<Mat> vecImg;
	vector<int> vecChannel;
	vector<int> vecHistSize;
	vector<float> vecRange;
	Mat mask(frame.rows, frame.cols, DataType<uchar>::type);
	//������ʼ��
	vecChannel.push_back(0);
	vecHistSize.push_back(32);
	vecRange.push_back(0);
	vecRange.push_back(180);

	Mat hsv;		//HSV��ɫ�ռ䣬��ɫ��H�ϸ���Ŀ�꣨camshift�ǻ�����ɫֱ��ͼ���㷨��
	MatND hist;		//ֱ��ͼ����
	double maxVal;		//ֱ��ͼ���ֵ��Ϊ�˱���ͶӰͼ��ʾ����Ҫ��ֱ��ͼ��һ����[0 255]������
	Mat backP;		//����ͶӰͼ
	Mat result;		//���ٽ��

	//��Ƶ��������
	while (1)
	{
		//����Ƶ
		cap >> frame;
		if (frame.empty() == true)
			break;

		//���ɽ��ͼ
		frame.copyTo(result);

		//���Ŀ��(��ʵ�Ǳ�ѵ���߼��)
		mog(frame, foreground, 0.01);
		imshow("��ϸ�˹���ǰ��", foreground);
		moveWindow("��ϸ�˹���ǰ��", 400, 0);
		//��ǰ��������ֵ�˲�����̬ѧ���Ͳ�������ȥ��αĿ��ͽ����Ͽ���СĿ��		
		medianBlur(foreground, foreground, 5);
		imshow("��ֵ�˲�", foreground);
		moveWindow("��ֵ�˲�", 800, 0);
		morphologyEx(foreground, foreground, MORPH_DILATE, se);

		//����ǰ���и�����ͨ����������
		foreground.copyTo(bw);
		vector<vector<Point>> contours;
		findContours(bw, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
		if (contours.size()<1)
			continue;
		//����ͨ������������
		std::sort(contours.begin(), contours.end(), biggerSort);

		//���camshift���¸���λ�ã�����camshift�㷨�ڵ�һ�����£�����Ч���ǳ��ã�
		//�����ڼ����Ƶ�У����ڷֱ���̫�͡���Ƶ����̫�Ŀ��̫��Ŀ����ɫ��������
		//�ȸ������أ����¸���Ч���ǳ��  ��ˣ���Ҫ�߸��١��߼�⣬������ٲ����ã�
		//���ü��λ���޸�
		cvtColor(frame, hsv, COLOR_BGR2HSV);
		vecImg.clear();
		vecImg.push_back(hsv);
		for (int k = 0; k<contours.size(); ++k)
		{
			//��k����ͨ��������Ӿ��ο�
			if (contourArea(contours[k])<contourArea(contours[0]) / 5)
				break;
			rt = boundingRect(contours[k]);
			mask = 0;
			mask(rt) = 255;

			//ͳ��ֱ��ͼ
			calcHist(vecImg, vecChannel, mask, hist, vecHistSize, vecRange);
			minMaxLoc(hist, 0, &maxVal);
			hist = hist * 255 / maxVal;
			//���㷴��ͶӰͼ
			calcBackProject(vecImg, vecChannel, hist, backP, vecRange, 1);
			//camshift����λ��
			Rect search = rt;
			RotatedRect rrt = CamShift(backP, search, TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 1));
			Rect rt2 = rrt.boundingRect();
			rt &= rt2;

			//���ٿ򻭵���Ƶ��
			rectangle(result, rt, Scalar(0, 255, 0), 2);
		}

		//�����ʾ
		imshow("ԭͼ", frame);
		moveWindow("ԭͼ", 0, 0);

		imshow("��������", foreground);
		moveWindow("��������", 0, 350);

		imshow("����ͶӰ", backP);
		moveWindow("����ͶӰ", 400, 350);

		imshow("����Ч��", result);
		moveWindow("����Ч��", 800, 350);
		waitKey(30);
	}

	getchar();
	return 0;
}