#include "string.h"
#include "stdafx.h"  
#include <cv.h>  
#include <cxcore.h>  
#include <highgui.h> 
#include<stdio.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/objdetect/objdetect.hpp>
using namespace cv;
using namespace std;
String face_cascade_name="E:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml";//��Ҫ����ļ����������ļ�CascadeClassifier���ڼ������ļ����������࣬
String eyes_cascade_name = "E:/opencv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
String nose_cascade_name = "E:/opencv/sources/data/haarcascades/haarcascade_mcs_nose.xml";
CascadeClassifier face_cascade; //������������������,����
CascadeClassifier eyes_cascade;//����
CascadeClassifier nose_cascade;//����
string window_name="����ʶ��";
void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;//std����vector<T>�������������࣬�����ű�ʾ�����RECT��ʵ���࣬���嶨����faces������һ��RECT����.
	Mat frame_gray;//ֱ�Ӹ�ֵ����    
	cvtColor( frame, frame_gray, CV_BGR2GRAY );//��frameת���ɻҶ�ͼ,�����frame_gray����Ϊ�õ�����haar���������Զ��ǻ��ڻҶ�ͼ��ģ����ﶼת���ɻҶ�ͼ��
	equalizeHist( frame_gray, frame_gray ); //��ͼ�����ֱ��ͼ���⻯���Աȶ�ǿ��,��������ǿ�ȷֲ���Χ,����frame_gray

	face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));//����������ʶ����faces��ʾ��⵽������Ŀ������.
	for(int  i = 0; i < faces.size(); i++ )
	{
		Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );  
		ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );//����Բ�����
		Mat faceROI = frame_gray(faces[i]);
		std::vector<Rect> eyes; //ÿ�����ϼ��˫��
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30)); //��ͼƬframe����ʶ���� 
		for (int j = 0; j < eyes.size(); j++)
		{
			Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2); 
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);//Բ������
			circle(frame, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0);//-- ��ɫԲ����۾�
		  //��imgͼ���ڻ���һ��Բ��Ϊcenter�뾶Ϊradius������ɫΪcolors[i%8]��Բ��thicknessΪ����Բ�����Ĵ�ϸ��ֵԽ��������Խ�֣�Ϊ�����������Ч��
	    }
		std::vector<Rect> nose; 
		nose_cascade.detectMultiScale( faceROI, nose, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
		for ( int j = 0; j< nose.size(); j++ )
		{
			Point nose_center( faces[i].x + nose[j].x + nose[j].width/2, faces[i].y + nose[j].y + nose[j].height/2 ); 
			int radius = cvRound( (nose[j].width + nose[j].height)*0.25 );
			circle( frame, nose_center, radius, Scalar( 0, 255, 0 ), 4, 8, 0 );//-- ��ɫԲ������� 
		}
	}
	imshow(window_name,frame);
}
//ʵ�ֽ���������ͼƬ����һ��
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
	VideoCapture cap(0);//opencv��ȡ��Ƶ������Ƶ���󡢶���֡��
	if(!cap.isOpened())
		return -1;
	Mat edges;
	if(!face_cascade.load(face_cascade_name))//��ָ���ļ�Ŀ¼�����뼶�������������ж��Ƿ�����ɹ���������ɹ����ӡ��ʾ
	{
		printf("[error]loading face cascade��\n");
		return -1;
	}
	if(!eyes_cascade.load(eyes_cascade_name)){
		printf("[error]loading face cascade��\n");
		return -1;
	}
	if(!nose_cascade.load(nose_cascade_name)){
		printf("[error]loading nose cascade��\n");
		return -1;
	}
	int nTick=0;//��������ʱ��
	for(;;)
	{
		if(!cap.isOpened())//�ȵ�����ͷ��
		{
			continue;
		}
		Mat frame;
		nTick=getTickCount();
		cap>>frame;//�ɼ���Ƶ��testImage��
		if(frame.data==NULL)//�ȵ���׽������
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
	 cvWaitKey(300);
	if(1 == argc)  
    {  
        capture = cvCreateCameraCapture(0);  
    }  
    else  
    {  
        capture = cvCreateCameraCapture(atoi(argv[1]));  
	}
	assert(NULL != capture); 
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
	cvReleaseImage(&frame);
	cvDestroyWindow("Camera Show");*/
	return 0;
}   


