#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

CascadeClassifier face_file;
CascadeClassifier eye_file;
String filname_face = "C:/Program Files/opencv/opencv/build/etc/haarcascades/haarcascade_frontalface_alt.xml";
String filname_eye = "C:/Program Files/opencv/opencv/build/etc/haarcascades/haarcascade_eye.xml";
int main() {
	if (!face_file.load(filname_face))
	{
		printf("ERROR");
		return 0;
	}
	if (!eye_file.load(filname_eye))
	{
		printf("ERROR");
		return 0;
	}
	namedWindow("face", CV_WINDOW_AUTOSIZE);
	VideoCapture capture(0);
	Mat frame;
	Mat src_gray;
	vector<Rect>face;
	vector<Rect>eyes;
	while (capture.read(frame))
	{
		cvtColor(frame, src_gray, COLOR_BGR2GRAY);
		equalizeHist(src_gray, src_gray);
		//人脸识别
		face_file.detectMultiScale(src_gray, face, 1.1, 2, 0, Size(30, 30));
		for (size_t i = 0; i < face.size(); i++)
		{
			Rect roi;
			roi.x = face[static_cast<int>(i)].x;
			roi.y = face[static_cast<int>(i)].y;
			roi.width = face[static_cast<int>(i)].width;
			roi.height = face[static_cast<int>(i)].height / 2;

			Mat faceROI = frame(roi);
			//眼部识别
			eye_file.detectMultiScale(faceROI, eyes, 1.2, 3, 0, Size(20, 20));
			for (size_t t = 0; t< eyes.size(); t++)
			{
				Rect rect;
				rect.x = face[static_cast<int>(i)].x + eyes[t].x;
				rect.y = face[static_cast<int>(i)].y + eyes[t].y;
				rect.width = eyes[t].width;
				rect.height = eyes[t].height;
				rectangle(frame, rect, Scalar(0, 255, 0), 2, 8, 0);
			}
			rectangle(frame, face[static_cast<int>(i)], Scalar(0, 0, 255), 2, 8, 0);

		}
		imshow("face", frame);
		char c = waitKey(30);
		if (c == 27) {
			break;
		}
	}

	waitKey(0);
	return 0;

}