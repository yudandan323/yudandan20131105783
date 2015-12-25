// open2.4.0人脸.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"  
#include <cv.h>  
#include <cxcore.h>  
#include <highgui.h>  


int main( int argc, char** argv )  
{ 
	CvCapture * capture;
	if((capture = cvCreateCameraCapture(0))==NULL)
	{
		printf("Camera Open Fail!Please check your Camera.");
		return 0;
	}
	 cvNamedWindow("Camera Show",CV_WINDOW_AUTOSIZE);
	 IplImage * frame;
	 cvWaitKey(300);
	 while(1)
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
	 cvDestroyWindow("Camera Show");
}   


