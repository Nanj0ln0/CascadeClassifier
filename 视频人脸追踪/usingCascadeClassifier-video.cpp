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
	namedWindow("DBWS", CV_WINDOW_AUTOSIZE);

	VideoCapture DBWS;
	DBWS.open("D:/OpenCV/picture zone/DBWS.mp4");
	Mat frame;
	Mat src_gray;
	vector<Rect>face;

	while (DBWS.read(frame))
	{
		
		cvtColor(frame, src_gray, COLOR_BGR2GRAY);
		equalizeHist(src_gray, src_gray);
		face_cascade.detectMultiScale(src_gray, face, 1.1, 3, 0, Size(30, 30));

		for (size_t i = 0; i < face.size(); i++)
		{
			rectangle(frame, face[i], Scalar(0, 0, 255), 2, 8, 0);
		}

		char c = waitKey(30);
		imshow("DBWS", frame);
		if (c == 27)
		{
			break;
		}
	}

	DBWS.release();
	waitKey(0);
	return 0;

}