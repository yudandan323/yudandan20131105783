// 测试程序.cpp : 定义控制台应用程序的入口点。
#include<opencv.hpp>
#include <stdio.h>
#include <cxcore.h>  
#include <stdlib.h>
#include <Windows.h>
#include "stdafx.h"
#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <time.h>
//using namespace std;  
using namespace cv; 

const char *pcascadeName = "E:\\opencv2.4.4\\data\\haarcascades\\haarcascade_frontalface_alt.xml"; //选择自己的安装目录
const char *pImageName = "images8.jpg";  
void DetectAndMark();

int main(int argc, const char** argv)  
{  
	DetectAndMark();
    return 0;  
}



void DetectAndMark()
{
	// load the Haar classifier  
    CvHaarClassifierCascade *pHaarClassCascade;  
    pHaarClassCascade = (CvHaarClassifierCascade*)cvLoad(pcascadeName);  
  
    //load the test image  
    IplImage *pSrcImage = cvLoadImage(pImageName, CV_LOAD_IMAGE_UNCHANGED);
    IplImage *pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);  
	if(pSrcImage == NULL || pGrayImage == NULL)
	{
		 printf("can't load image!\n");
		 return;
	}
    cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY);  
  
    if (pHaarClassCascade != NULL && pSrcImage != NULL && pGrayImage != NULL)  
    {         
        const static CvScalar colors[] =   
        {  
			CV_RGB(0,0,255),
			CV_RGB(0,128,255),
			CV_RGB(0,255,255),
			CV_RGB(0,255,0),
			CV_RGB(255,128,0),
			CV_RGB(255,255,0),
			CV_RGB(255,0,0),
			CV_RGB(255,0,255) 
        };  
  
        CvMemStorage *pcvMemStorage = cvCreateMemStorage(0);  
        cvClearMemStorage(pcvMemStorage);  
		CvSeq *pcvSeqFaces = cvHaarDetectObjects(pGrayImage, pHaarClassCascade, pcvMemStorage);
        //detect the face  
        /*int TimeStart, TimeEnd;  
        TimeStart = GetTickCount();  
        CvSeq *pcvSeqFaces = cvHaarDetectObjects(pGrayImage, pHaarClassCascade, pcvMemStorage);  
        TimeEnd = GetTickCount();  
  
        printf("the number of faces: %d\nSpending Time: %d ms\n", pcvSeqFaces->total, TimeEnd - TimeStart);  
          
        //mark the face   */
        for(int i = 0; i <pcvSeqFaces->total; i++)  
        {  
            CvRect* r = (CvRect*)cvGetSeqElem(pcvSeqFaces, i);  
            CvPoint center;  
            int radius;  
            center.x = cvRound((r->x + r->width * 0.5));  
            center.y = cvRound((r->y + r->height * 0.5));  
            radius = cvRound((r->width + r->height) * 0.25);  
            cvCircle(pSrcImage, center, radius, colors[i % 8], 2);  
        }  
        cvReleaseMemStorage(&pcvMemStorage);  
    }  
      
    const char *pstrWindowsTitle = "FaceDetect Demo";  
    cvNamedWindow(pstrWindowsTitle, CV_WINDOW_AUTOSIZE);  
    cvShowImage(pstrWindowsTitle, pSrcImage);  
  
    cvWaitKey(0);  
  
    cvDestroyWindow(pstrWindowsTitle);  
    cvReleaseImage(&pSrcImage);   
    cvReleaseImage(&pGrayImage);  
}
