// open2.4.0人脸.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"  
#include <cv.h>  
#include <cxcore.h>  
#include <highgui.h> 
#include<stdio.h>
//实现将拍下来的图片缩放一倍
IplImage* DoPyrDown(IplImage* image,int filter=IPL_GAUSSIAN_5x5)
{
	CvSize size = cvSize(image->width / 2,image->height / 2);
	IplImage* outImage = cvCreateImage(size,image->depth,image->nChannels); 
	cvPyrDown(image,outImage);
	cvReleaseImage(&image);  
    return outImage; 
}
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
	char keyCode;
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
	 cvDestroyAllWindows();*/
	 cvReleaseImage(&frame);
	 cvDestroyWindow("Camera Show");
}   


