#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

CascadeClassifier cat;
String cat_xml = "C:/Program Files/opencv/opencv/build/etc/haarcascades/haarcascade_frontalcatface.xml";

int main() {
	if (!cat.load(cat_xml))
	{
		printf("ERRPR");
		return -1;
	}

	Mat catFace = imread("D:/OpenCV/picture zone/morecat.png");
	Mat gray;
	cvtColor(catFace,gray,COLOR_BGR2GRAY);
	equalizeHist(gray,gray);

	vector<Rect> face;
	cat.detectMultiScale(gray,face,1.1,3,0,Size(20,20));

	for (size_t i = 0; i < face.size(); i++)
	{
		rectangle(catFace,face[i],Scalar(0,0,255),2,8,0);

	}
	namedWindow("cat",CV_WINDOW_AUTOSIZE);
	imshow("cat",catFace);

	waitKey(0);
	return 0;

}