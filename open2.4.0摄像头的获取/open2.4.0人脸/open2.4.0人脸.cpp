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
String face_cascade_name="E:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml";//需要载入的级联分类器文件CascadeClassifier用于检测物体的级联分类器类，
String eyes_cascade_name = "E:/opencv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
String nose_cascade_name = "E:/opencv/sources/data/haarcascades/haarcascade_mcs_nose.xml";
CascadeClassifier face_cascade; //创建级联分类器对象,人脸
CascadeClassifier eyes_cascade;//人脸
CascadeClassifier nose_cascade;//鼻子
string window_name="人脸识别";
void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;//std：：vector<T>就是数组容器类，尖括号表示里面的RECT是实际类，整体定义了faces对象是一个RECT数组.
	Mat frame_gray;//直接赋值矩阵    
	cvtColor( frame, frame_gray, CV_BGR2GRAY );//将frame转换成灰度图,输出到frame_gray。因为用的是类haar特征，所以都是基于灰度图像的，这里都转换成灰度图像
	equalizeHist( frame_gray, frame_gray ); //对图像进行直方图均衡化，对比度强化,拉伸像素强度分布范围,放在frame_gray

	face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));//对人脸进行识别检测faces表示检测到的人脸目标序列.
	for(int  i = 0; i < faces.size(); i++ )
	{
		Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );  
		ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );//用椭圆框出脸
		Mat faceROI = frame_gray(faces[i]);
		std::vector<Rect> eyes; //每张脸上检测双眼
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30)); //对图片frame进行识别检测 
		for (int j = 0; j < eyes.size(); j++)
		{
			Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2); 
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);//圆心坐标
			circle(frame, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0);//-- 蓝色圆框出眼睛
		  //在img图像内绘制一个圆心为center半径为radius线条颜色为colors[i%8]的圆，thickness为设置圆线条的粗细，值越大则线条越粗，为负数则是填充效果
	    }
		std::vector<Rect> nose; 
		nose_cascade.detectMultiScale( faceROI, nose, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
		for ( int j = 0; j< nose.size(); j++ )
		{
			Point nose_center( faces[i].x + nose[j].x + nose[j].width/2, faces[i].y + nose[j].y + nose[j].height/2 ); 
			int radius = cvRound( (nose[j].width + nose[j].height)*0.25 );
			circle( frame, nose_center, radius, Scalar( 0, 255, 0 ), 4, 8, 0 );//-- 蓝色圆框出鼻子 
		}
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
	VideoCapture cap(0);//opencv读取视频创建视频对象、定义帧率
	if(!cap.isOpened())
		return -1;
	Mat edges;
	if(!face_cascade.load(face_cascade_name))//从指定文件目录中载入级联分类器，并判断是否载入成功，如果不成功则打印提示
	{
		printf("[error]loading face cascade！\n");
		return -1;
	}
	if(!eyes_cascade.load(eyes_cascade_name)){
		printf("[error]loading face cascade！\n");
		return -1;
	}
	if(!nose_cascade.load(nose_cascade_name)){
		printf("[error]loading nose cascade！\n");
		return -1;
	}
	int nTick=0;//计算运行时间
	for(;;)
	{
		if(!cap.isOpened())//等等摄像头打开
		{
			continue;
		}
		Mat frame;
		nTick=getTickCount();
		cap>>frame;//采集视频到testImage中
		if(frame.data==NULL)//等到捕捉到数据
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
	cvReleaseImage(&frame);
	cvDestroyWindow("Camera Show");*/
	return 0;
}   


