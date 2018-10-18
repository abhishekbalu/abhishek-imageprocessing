#ifndef OBJECTS_H
#define OBJECTS_H
#endif
#include "highgui.h"

#include "cv.h"
#include "iostream"
#include "string.h"


using namespace std;




class uav{

	string color;
	int radius;
	int posX;
	int posY;
    int lastX;
    int lastY;
    float dx,dy;
    float distance;
    float pHit;
    float pMiss;
    float sum;

    float thresh_hit_distance;
    bool found;
	

public:
	IplImage * canny;
	IplImage* imgThresh;
	IplImage* houghCircles;
    IplImage* imgThreshBiggestContour;

	
	int lowerH,lowerS,lowerV,upperH,upperS,upperV;
    string uavColor;
    const char* threshWindow;
//------------------------------------
    CvArr* _mask;
    CvMat mstub, *mask ;
    int nContours;
    double largest_length ,len;
    CvContourScanner scanner;
    uchar* dst;
    CvRect R;
    IplImage temp;
    CvSeq *contours, *c;
    CvSeq* newC;



//-------------------------------------------

    void   FC_FindBiggestContours(IplImage *src);

	bool isFound();
	int getX();
	int getY();
	void setWindowSettings();
	void setXY(int,int);
	void TrackObjects(IplImage*,IplImage**);
   void  setHSV(int lowerH,int lowerS,int lowerV,int upperH,int upperS,int upperV);
	IplImage* GetThresholdedImage(IplImage* );
 void getThreshLUV(IplImage*,IplImage*);

     uav(string color,IplImage* size){    //constructor

         uavColor=color;
		 radius=5;
		 houghCircles=cvCreateImage(cvGetSize(size),IPL_DEPTH_8U,1);
         imgThresh=cvCreateImage(cvGetSize(size),IPL_DEPTH_8U,1);
         imgThreshBiggestContour=cvCreateImage(cvGetSize(size),IPL_DEPTH_8U,1);

         pHit=0.5;
         pMiss=0.5;
         thresh_hit_distance=6;

         nContours=0;
         largest_length=0;
         len=0;

         found=false;

		 
		
		 if(color=="red"){
			
			lowerH=0;
			lowerS=160;
			lowerV=60;
			upperH=16;
			upperS=255;
			upperV=255;
			threshWindow="Debug_red_thresh";
						
			
		}

		 if(color=="yellow"){
			lowerH=24;
			lowerS=106;
			lowerV=59;
			upperH=54;
			upperS=256;
			upperV=256;
			threshWindow="Debug_yellow_thresh";
	 }
		 if(color=="green"){
			lowerH=52;
			lowerS=163;
			lowerV=97;
			upperH=82;
			upperS=256;
			upperV=256;
			threshWindow="Debug_green_thresh";

		 }
	}
	
};







	
	

