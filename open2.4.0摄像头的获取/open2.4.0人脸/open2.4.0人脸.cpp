// open2.4.0����.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"  
#include <cv.h>  
#include <cxcore.h>  
#include <highgui.h> 
#include<stdio.h>
//ʵ�ֽ���������ͼƬ����һ��
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
        //��ʾ������ESC�����˳�  
        if(keyCode == 27)  
        {  
            break;  
        }  
  
        //��ʾ�����˻س�������ʱӦ��������Ƭ  
        if(keyCode == 13)  
        {  
            //��ʼ��һ��ͼƬ  
            IplImage* outImage = cvCreateImage(cvGetSize(frame),frame->depth,frame->nChannels);  
            // ��ԭͼ��������  
            cvCopy(frame,outImage,NULL);  
            //ʵ�����Ų���  
            outImage = DoPyrDown(outImage);  
            //���ñ����ͼƬ���ƺ͸�ʽ  
            char* outImageName = "test.jpg";  
            //����ͼƬ  
            cvSaveImage(outImageName,outImage);  
            cvReleaseImage(&outImage);  
            printf(" ��ϲ�㣬����ͼƬ�ɹ���\n");  
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


