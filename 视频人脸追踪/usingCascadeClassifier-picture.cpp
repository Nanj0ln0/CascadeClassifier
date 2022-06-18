#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

CascadeClassifier face_cascade;
String harrfile = "C:/Program Files/opencv/opencv/build/etc/haarcascades/haarcascade_frontalface_alt.xml";
String lbpfile = "C:/Program Files/opencv/opencv/build/etc/lbpcascades/lbpcascade_frontalface.xml";

int main() {
	if (!face_cascade.load(harrfile))
	{
		printf("empty");
		return -1;
	}
	namedWindow("face",CV_WINDOW_AUTOSIZE);
	Mat src = imread("C:/Users/22207/Desktop/superis/man.jpg");
	Mat src_gray;
	cvtColor(src,src_gray,COLOR_BGR2GRAY);
	equalizeHist(src_gray,src_gray);
	
	int st = getTickCount();
	vector<Rect>face;
	face_cascade.detectMultiScale(src_gray,face,1.1,3,0,Size(30,30));

	int et = (getTickCount() - st)/getTickFrequency();
	printf("Times = %d",et);

	for (size_t i = 0; i < face.size(); i++)
	{

		rectangle(src,face[i],Scalar(0,0,255),2,8,0);

	}
	imshow("face",src);
	waitKey(0);
	return 0;

}