// open2.4.0人脸.cpp : 定义控制台应用程序的入口点。
//

#include "string.h"
#include "stdafx.h"  
#include <cv.h>  
#include <cxcore.h>  
#include <highgui.h> 
#include<stdio.h>
#include<opencv2/imgproc//imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/objdetect/objdetect.hpp>
using namespace cv;
using namespace std;
string face_cascade_name="E:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml";
CascadeClassifier face_cascade; 
string window_name="人脸识别";
void detectAndDisplay(Mat frame){
	std::vector<Rect> faces;
	Mat frame_gray;  
	cvtColor( frame, frame_gray, CV_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray ); 
	face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));
	 for( int i = 0; i < faces.size(); i++ ){  
		 Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );  
		 ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
	 }
	 imshow(window_name,frame);

}
//实现将拍下来的图片缩放一倍
/*IplImage* DoPyrDown(IplImage* image,int filter=IPL_GAUSSIAN_5x5)
{
	CvSize size = cvSize(image->width / 2,image->height / 2);
	IplImage* outImage = cvCreateImage(size,image->depth,image->nChannels); 
	cvPyrDown(image,outImage);
	cvReleaseImage(&image);  
    return outImage; 
}*/
int main(int argc, char** argv )  
{ 
	VideoCapture cap(0);
	if(!cap.isOpened())
		return -1;
	Mat edges;
	if(!face_cascade.load(face_cascade_name)){
		printf("[error]无法加载级联分类器文件！\n");
		return -1;
	}
	int nTick=0;
	for(;;)
	{
		if(!cap.isOpened())
		{
			continue;
		}
		Mat frame;
		nTick=getTickCount();
		cap>>frame;
		if(frame.data==NULL)
		{
			continue;
		}
		cvtColor(frame,edges,CV_BGR2BGRA);
		detectAndDisplay(edges);
		if(waitKey(30)>=0)break;


	}
	/*CvCapture * capture;
	if((capture = cvCreateCameraCapture(0))==NULL)
	{
		printf("Camera Open Fail!Please check your Camera.");
		return 0;
	}
	 cvNamedWindow("Camera Show",CV_WINDOW_AUTOSIZE);
	 IplImage * frame;
	 cvWaitKey(300);2016.1.1*/
	/*if(1 == argc)  
    {  
        capture = cvCreateCameraCapture(0);  
    }  
    else  
    {  
        capture = cvCreateCameraCapture(atoi(argv[1]));  
    }  
  
    assert(NULL != capture); 
	IplImage* frame;
	*/
	/*char keyCode;
	while((keyCode = cvWaitKey(30)))  
    {  
        //表示按下了ESC键，退出  
        if(keyCode == 27)  
        {  
            break;  
        }  
  
        //表示按下了回车键，此时应当保存照片  
        if(keyCode == 13)  
        {  
            //初始化一张图片  
            IplImage* outImage = cvCreateImage(cvGetSize(frame),frame->depth,frame->nChannels);  
            // 将原图拷贝过来  
            cvCopy(frame,outImage,NULL);  
            //实现缩放操作  
            outImage = DoPyrDown(outImage);  
            //设置保存的图片名称和格式  
            char* outImageName = "test.jpg";  
            //保存图片  
            cvSaveImage(outImageName,outImage);  
            cvReleaseImage(&outImage);  
            printf(" 恭喜你，保存图片成功！\n");  
        }  
		frame = cvQueryFrame(capture);
		if(!frame)  
        {  
            break;  
        }  
        cvShowImage("Camera Show",frame); 
	}
	
	/* while(1)
	 {
		 frame=cvQueryFrame(capture);
		  if(!frame)
			   break;
		  cvShowImage("Camera Show",frame);
		  char c=cvWaitKey(33);
		  if(c==27)
			  break;
	 }
	 cvReleaseCapture(&capture);
	 cvDestroyAllWindows();不是*/
	 /*cvReleaseImage(&frame);
	 cvDestroyWindow("Camera Show");*/
	return 0;

}   


