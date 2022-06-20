#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

String facefile = "C:/Program Files/opencv/opencv/build/etc/haarcascades/haarcascade_frontalface_alt.xml";
String lefteyefile = "C:/Program Files/opencv/opencv/build/etc/haarcascades/haarcascade_eye.xml";
String righteyefile = "C:/Program Files/opencv/opencv/build/etc/haarcascades/haarcascade_eye.xml";
CascadeClassifier face;
CascadeClassifier lefteye;
CascadeClassifier righteye;

Rect left, right;

int main() {
	if (!face.load(facefile))
	{
		printf("ERROR");
		return -1;
	}
	if (!lefteye.load(lefteyefile))
	{
		printf("ERROR");
		return -2;
	}

	if (!righteye.load(righteyefile))
	{
		printf("ERROR");
		return -3;
	}

	
	Mat frame;
	/*
	VideoCapture capture;
	capture.open("D:/OpenCV/picture zone/ZTZ.mp4");
	*/
	VideoCapture capture(0);
	namedWindow("output",CV_WINDOW_AUTOSIZE);
	
	Mat gray;
	vector<Rect> faces;
	vector<Rect> lefteyes;
	vector<Rect> righteyes;

	while (capture.read(frame))
	{
		flip(frame,frame,1);//ÐÞÕýÉãÏñÍ·µÄ¾µÏñ
		cvtColor(frame,gray,COLOR_BGR2GRAY);
		equalizeHist(gray,gray);

		face.detectMultiScale(gray,faces,1.1,3,0,Size(30,30));

		for (size_t i = 0; i < faces.size(); i++)
		{
			rectangle(frame,faces[i],Scalar(0,0,255),2,8,0);

			//¼ÆËãÑÛ¾¦·¶Î§
			int offsety = faces[i].height / 4;
			int offsetx = faces[i].width / 8;
			int eyeheight = faces[i].height - offsety;
			int eyewidth = faces[i].width - offsetx;

			//×óÑÛ·¶Î§
			Rect leftrect;
			leftrect.x = faces[i].x + offsetx;
			leftrect.y = faces[i].y + offsety;
			leftrect.width = eyewidth;
			leftrect.height = eyeheight;
			Mat leftRoi = gray(leftrect);

			//¼ì²â×óÑÛ
			lefteye.detectMultiScale(leftRoi,lefteyes,1.1,1,0,Size(20,20));
			if (lefteyes.size())
			{
				//½«ÑÛ¾¦ÔÚÔ­Í¼µÄ×ø±ê¼ÆËã³öÀ´
				leftrect = lefteyes[0] + Point(leftrect.x,leftrect.y );
				rectangle(frame, leftrect, Scalar(0, 0, 255), 2, 8, 0);
			}


			//ÓÒÑÛ·¶Î§
			Rect rightrect;
			rightrect.x = faces[i].x + faces[i].width /2;
			rightrect.y = faces[i].y + offsety;
			rightrect.width = eyewidth;
			rightrect.height = eyeheight;
			Mat rightRoi = gray(rightrect);

			//¼ì²âÓÒÑÛ
			righteye.detectMultiScale(rightRoi, righteyes, 1.1, 1, 0, Size(20, 20));
			if (righteyes.size())
			{
				//½«ÑÛ¾¦ÔÚÔ­Í¼µÄ×ø±ê¼ÆËã³öÀ´
				rightrect = righteyes[0] + Point(rightrect.x, rightrect.y);
				rectangle(frame, rightrect, Scalar(0, 255, 255), 2, 8, 0);
			}


		}
		imshow("output",frame);
		char c =waitKey(30);
		if (c==27)
		{
			break;
		}
	}

	capture.release();
	waitKey(0);
	return 0;

}