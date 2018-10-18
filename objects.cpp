
#include "objects.h"
#include <QtCore>


CvSize *myfontSize;
int baseline;




bool uav::isFound(){
    return found;

}


void uav::setXY(int src_x,int src_y){

    lastX=posX;
    lastY=posY;
    posX=src_x;
    posY=src_y;



    dx=posX-lastX;
    dy=posY-lastY;
    distance=sqrt(dx*dx+dy*dy);

    if(pHit==0.00||pMiss==0.00){
        pHit=0.5;
        pMiss=0.5;
    }


    if(distance<=thresh_hit_distance){
        pHit=pHit*0.8;
        pMiss=pMiss*0.1;
        sum=pHit+pMiss;
        pHit/=sum;
        pMiss/=sum;

    }

    else {
        pHit=pHit*0.1;
        pMiss=pMiss*0.8;
        sum=pHit+pMiss;
        pHit/=sum;
        pMiss/=sum;

    }
   // qDebug()<<"pHit: "<<pHit<<"  pMiss: "<<pMiss<<"\n";


}
int uav::getX(){
    return posX;
}
int uav::getY(){
    return posY;
}

void uav::setWindowSettings(){
     cvCreateTrackbar("LowerH",threshWindow,&lowerH,180,NULL);
       cvCreateTrackbar("UpperH",threshWindow,&upperH,180,NULL);

       cvCreateTrackbar("LowerS",threshWindow,&lowerS,256,NULL);
       cvCreateTrackbar("UpperS",threshWindow,&upperS,256,NULL);

        cvCreateTrackbar("LowerV",threshWindow,&lowerV,256,NULL);
       cvCreateTrackbar("UpperV",threshWindow,&upperV,256,NULL);
   }

void uav::setHSV(int lH,int lS,int lV,int uH,int uS,int uV){
    lowerH=lH;
    lowerS=lS;
    lowerV=lV;
    upperH=uH;
    upperS=uS;
    upperV=uV;
}



void uav::TrackObjects(IplImage* imgThresh,IplImage** frame_resized){
    CvMoments *moments=(CvMoments*)malloc(sizeof(CvMoments));
    cvMoments(imgThresh,moments,1);
    double moment10=cvGetSpatialMoment(moments,1,0);
    double moment01=cvGetSpatialMoment(moments,0,1);
    double area=cvGetCentralMoment(moments,0,0);

    if(area>10){
        qDebug()<<area<<endl;
    //	cout<<area<<"\n";
        //printf(" Object Found: ");
        char coordinates_red[32];
        char coordinates_yellow[32];
        char coordinates_green[32];
        setXY(moment10/area,moment01/area);
        int posX=getX();
        int posY=getY();
         CvFont myfont;
        cvInitFont(&myfont,CV_FONT_HERSHEY_COMPLEX_SMALL,0.5,0.5,0.0,1,8);

        if(pHit>0.5){


        if(uavColor=="yellow"){
            found=true;
            sprintf(coordinates_yellow,"YELLOW|X=%d|Y=%d",posX,posY);
            //sprintf(coordinates_yellow,"Yellow has just been found and");
            cvGetTextSize(coordinates_yellow,&myfont,myfontSize,&baseline);
            cvRectangle(*frame_resized,cvPoint(posX+5,posY+3),cvPoint(posX+125,posY-8),CV_RGB(0,0,0),CV_FILLED);
            cvPutText(*frame_resized,coordinates_yellow,cvPoint(posX+5,posY),&myfont,CV_RGB(255,255,255));
            cvCircle(*frame_resized,cvPoint(posX,posY),4,CV_RGB(255,255,0),2);

        }



        if(uavColor=="red"){
            sprintf(coordinates_red,"RED|X=%d|Y=%d",posX,posY);
            cvGetTextSize(coordinates_red,&myfont,myfontSize,&baseline);
            cvRectangle(*frame_resized,cvPoint(posX+5,posY+3),cvPoint(posX+105,posY-8),CV_RGB(0,0,0),CV_FILLED);
            cvPutText(*frame_resized,coordinates_red,cvPoint(posX+5,posY),&myfont,CV_RGB(255,255,255));
            cvCircle(*frame_resized,cvPoint(posX,posY),4,CV_RGB(255,0,0),2);
        }



        if(uavColor=="green"){
            sprintf(coordinates_green,"GREEN|X=%d|Y=%d",posX,posY);
            cvGetTextSize(coordinates_green,&myfont,myfontSize,&baseline);
            cvRectangle(*frame_resized,cvPoint(posX+5,posY+3),cvPoint(posX+124,posY-8),CV_RGB(0,0,0),CV_FILLED);
            cvPutText(*frame_resized,coordinates_green,cvPoint(posX+5,posY),&myfont,CV_RGB(255,255,255));
            cvCircle(*frame_resized,cvPoint(posX,posY),4,CV_RGB(0,255,0),2);

        }
}




    }
    else
          found=false;

    free(moments);
}

IplImage* uav::GetThresholdedImage(IplImage* imageHSV){


    cvInRangeS(imageHSV,cvScalar(lowerH,lowerS,lowerV),cvScalar(upperH,upperS,upperV),imgThresh);
    return imgThresh;
}

 void uav::getThreshLUV(IplImage* src,IplImage* dest){
    // adaptiveThreshold(src,dest,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY,13,0);

}



void uav::FC_FindBiggestContours(IplImage *src)
{

    _mask=0;
    nContours=0;
    largest_length=0;
    len=0;
    dst=0;
    contours=0;
    c=0;
    newC=0;

    CvMemStorage* tempStorage = cvCreateMemStorage();
   temp=*src;
  IplImage *src_img=cvCreateImage(cvSize(temp.width,temp.height),IPL_DEPTH_32S,1);
//  IplImage *dest=cvCreateImage(cvSize(temp.width,temp.height),IPL_DEPTH_8U,1);
   _mask=&temp;
  int poly1Hull0=1;
  CvPoint offset;
  offset.x=0;
  offset.y=0;
 mask = cvGetMat( _mask, &mstub );




 // clean up raw mask
 cvMorphologyEx( mask, mask, 0, 0, CV_MOP_OPEN, 1 );
 cvMorphologyEx( mask, mask, 0, 0, CV_MOP_CLOSE, 1 );
 // find contours around only bigger regions
 scanner = cvStartFindContours( mask, tempStorage,
                 sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, offset );
 while( (c = cvFindNextContour( scanner )) != 0 )
 {
   len = cvContourPerimeter( c );
   if(len > largest_length)
   {
     largest_length = len;
   }
 }
 contours=cvEndFindContours( &scanner );
 scanner = cvStartFindContours( mask, tempStorage,
                 sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, offset );
 while( (c = cvFindNextContour( scanner )) != 0 )
 {
   len = cvContourPerimeter( c );
   double q = largest_length ;
   if( len < q ) //Get rid of blob if it's perimeter is too small
     cvSubstituteContour( scanner, 0 );
   else  //Smooth it's edges if it's large enough
   {

     if( poly1Hull0 ) //Polygonal approximation of the segmentation
       newC = cvApproxPoly( c, sizeof(CvContour), tempStorage, CV_POLY_APPROX_DP, 2, 0 );
     else //Convex Hull of the segmentation
       newC = cvConvexHull2( c, tempStorage, CV_CLOCKWISE, 1 );
     cvSubstituteContour( scanner, newC );
     nContours++;
     R=cvBoundingRect(c,0);
   }
 }
 contours = cvEndFindContours( &scanner );
 // paint the found regions back into the image
 cvZero( src_img );
 cvZero( _mask );
 for( c=contours; c != 0; c = c->h_next )
 {
   cvDrawContours( src_img, c, cvScalarAll(1), cvScalarAll(1), -1, -1, 8,
           cvPoint(-offset.x,-offset.y));
 }
   cvReleaseMemStorage( &tempStorage );
// convert to 8 bit IplImage
for( int i = 0; i < src_img->height; i++ )
  for( int j = 0; j < src_img->width; j++ )
  {
   int idx = CV_IMAGE_ELEM( src_img, int, i, j );  //get reference to pixel at (col,row),
    dst = &CV_IMAGE_ELEM( src, uchar, i, j );                          //for multi-channel images (col) should be multiplied by number of channels */
   if( idx == -1 || idx == 1 )
    *dst = (uchar)255;
   else if( idx <= 0 || idx > 1 )
    *dst = (uchar)0; // should not get here
   else {
    *dst = (uchar)0;
      }
    }
//qDebug()<<nContours;
cvReleaseImage(&src_img);
// cvReleaseImage(&temp);

//return dest;
}

