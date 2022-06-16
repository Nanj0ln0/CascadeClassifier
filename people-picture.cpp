#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	string cascadeFilePath = ("C:/Program Files/opencv/opencv/build/etc/haarcascades/haarcascade_frontalface_alt.xml");

	CascadeClassifier face_cascade;

	if (!face_cascade.load(cascadeFilePath))
	{
		printf("Not face data");
		return -1;
	}

	Mat src = imread("C:/Users/22207/Desktop/superis/man.jpg");
	
	Mat src_gray;
	cvtColor(src,src_gray,COLOR_BGR2GRAY);
	equalizeHist(src_gray,src_gray);


	vector<Rect>face;
	face_cascade.detectMultiScale(src_gray,face,1.1,2,0,Size(30,30));

	for (size_t i = 0; i < face.size(); i++)
	{
		rectangle(src,face[i],Scalar(0,0,255),2,8,0);

	}
	imshow("face",src);

	waitKey(0);
	return 0;

}