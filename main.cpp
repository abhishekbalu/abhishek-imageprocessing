#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "highgui.h"
#include "cv.h"
#include "iostream"
#include "objects.h"
#include <math.h>
#include<QLabel>
#include"ipl2qimg.h"
#include"mainwindow.h"
#include "time.h"
#include "contour.h"
#include<sys/shm.h>

#include <sys/stat.h>


typedef struct uav_coords{
    int x;
    int y;
    int x_angular_offset;
    int y_angular_offset;
    bool found;
};

uav_coords* myuav;



void createCapture();
void FC_FindBiggestContours(IplImage *src) ;

bool reduavFound=false,blueuavFound=false,yellowuavFound=false;

    IplImage *imgTracking;
    IplImage *frame;
    IplImage *frame_resized;
    IplImage *originalFrame;
    IplImage *frame_resized_gray;
    IplImage *imgHSV;
    IplImage * imgLUV;
    IplImage *canny_destination;
    IplImage *binary_flatten;
    IplImage *grayScale;
    IplImage *r,*g,*b;
    IplImage *L,*U,*V,*L_adp;
    IplImage *canny_r;
    IplImage *canny_g;
    IplImage *canny_b;
    IplImage *photo;
    IplImage * normalized;





    CvMemStorage* storage=cvCreateMemStorage(0);
    CvSeq* results;
    float*p; //used in hough circles
    CvPoint pt;//used in hough circles

    int lastX=-1;
    int lastY=-1;
    int dFactor=2;  //used for min distance between canny circles in hough circle transform
    CvCapture *cam=NULL;
    //------------------------------------------------------------

    int percent=60; ///set the size of the output image
    double dp=2;//used for Circlular Hough Transform
    float canny_t1=75,canny_t2=150; //used for canny

 filters* settings=new filters;
 switches* flip=new switches;
    //------------------------------------------------------------

int cval; //adaptive thresh
int window=23;

 void * getFrames(void* params){
     filters* q=(filters*)params;
     while(1){

         frame=cvQueryFrame(cam);
         //qDebug()<<"In thread";

     }
     qDebug()<<"exiting thread";
 }



 int main(int argc, char *argv[])
{

    QApplication app(argc,argv);


    //setting for allocating shared memory:
    int segment_id;
    const int shared_segment_size=sizeof(uav_coords);
    uav_coords* shared_memory;
    struct shmid_ds shmbuffer;
    int segment_size;
    segment_id=shmget(123,shared_segment_size,IPC_CREAT|S_IRUSR|S_IWUSR);
    shared_memory=(uav_coords*)shmat(segment_id,0,0);
    segment_size=shmbuffer.shm_segsz;



//settings:

  settings->do_canny_src=false;
  settings->createCam=true;
  settings->do_split_rgb=true;
  settings->do_canny_b=false;
  settings->do_canny_g=false;
  settings->do_canny_r=false;
  settings->do_circular_hough=false;
  settings->do_thresh_green=false;
  settings->do_thresh_red=false;
  settings->do_thresh_yellow=false;
  settings->do_thresh_green_mc=true;
  settings->do_thresh_red_mc=true;
  settings->do_thresh_yellow_mc=true;
  settings->dFactor=7;

  settings->dp=1;
  settings->hi=64;
  settings->lo=45;

  //flips:
  flip->show_canny=false;
  flip->show_orig=true;
  flip->show_thresh_green=false;
  flip->show_thresh_red=false;
  flip->show_thresh_yellow=false;
  flip->show_b=false;
  flip->show_g=false;
  flip->show_r=false;
  flip->show_thresh_flat=false;
  flip->quit=false;

    time_t start,end;
  //  double fps;
    int counter;
    double sec;
    time(&start);

    QImage qimg,qimgOrig;


    //thread creation:
    pthread_t thread1_id;
   pthread_create(&thread1_id,NULL,&getFrames,settings);

    MainWindow w;
    w.passFilters(settings);
    w.passFlips(flip);
    w.show();

    QLabel myLabel;


 photo=cvLoadImage("/home/abhishek/qt/second/uav/uavsf.jpg");



          cvNamedWindow("CamOut",CV_WINDOW_AUTOSIZE);


            cvCreateTrackbar("dFactor","CamOut",&settings->dFactor,10,NULL);
            cvCreateTrackbar("dP","CamOut",&settings->dp,15,NULL);
            cvCreateTrackbar("hi", "CamOut", &settings->hi, 255);
            cvCreateTrackbar("lo", "CamOut", &settings->lo, 255);
            cvCreateTrackbar("C", "CamOut", &cval, 255);
            cvCreateTrackbar("block", "CamOut", &window, 100);



             //cvNamedWindow("myWin");

           createCapture();

            if(settings->createCam==true)
                frame=cvQueryFrame(cam);
            else{
                frame=cvLoadImage("/home/abhishek/qt/second/uav/uavsf.jpg");


            }

                grayScale=cvLoadImage("/home/abhishek/qt/second/uav/uavsf.jpg",CV_LOAD_IMAGE_GRAYSCALE);


            frame_resized=cvCreateImage(cvSize((frame->width*percent)/100,(frame->height*percent)/100),IPL_DEPTH_8U,3);
            originalFrame=cvCreateImage(cvGetSize(frame_resized),IPL_DEPTH_8U,3);
            frame_resized_gray=cvCreateImage(cvSize((frame->width*percent)/100,(frame->height*percent)/100),IPL_DEPTH_8U,1);
            r=cvCreateImage(cvSize((frame->width*percent)/100,(frame->height*percent)/100),IPL_DEPTH_8U,1);
            g=cvCreateImage(cvSize((frame->width*percent)/100,(frame->height*percent)/100),IPL_DEPTH_8U,1);
            b=cvCreateImage(cvSize((frame->width*percent)/100,(frame->height*percent)/100),IPL_DEPTH_8U,1);
            L=cvCreateImage(cvSize((frame->width*percent)/100,(frame->height*percent)/100),IPL_DEPTH_8U,1);
            L_adp=cvCreateImage(cvSize((frame->width*percent)/100,(frame->height*percent)/100),IPL_DEPTH_8U,1);
            U=cvCreateImage(cvSize((frame->width*percent)/100,(frame->height*percent)/100),IPL_DEPTH_8U,1);
            V=cvCreateImage(cvSize((frame->width*percent)/100,(frame->height*percent)/100),IPL_DEPTH_8U,1);
            normalized=cvCreateImage(cvSize((frame->width*percent)/100,(frame->height*percent)/100),IPL_DEPTH_8U,3);




            uav red("red",frame_resized);
            uav green("green",frame_resized);
            uav yellow("yellow",frame_resized);

            //Read the HSV values from the XML in final design///
            settings->red.lowerH=0;
            settings->red.lowerS=160;
            settings->red.lowerV=60;
            settings->red.upperH=16;
            settings->red.upperS=255;
            settings->red.upperV=255;

            settings->yellow.lowerH=24;
            settings->yellow.lowerS=106;
            settings->yellow.lowerV=59;
            settings->yellow.upperH=54;
            settings->yellow.upperS=255;
            settings->yellow.upperV=255;

            settings->green.lowerH=52;
            settings->green.lowerS=163;
            settings->green.lowerV=97;
            settings->green.upperH=82;
            settings->green.upperS=255;
            settings->green.upperV=255;


            red.setHSV(settings->red.lowerH,settings->red.lowerS,settings->red.lowerV,settings->red.upperH,settings->red.upperS,settings->red.upperV);
            yellow.setHSV(settings->yellow.lowerH,settings->yellow.lowerS,settings->yellow.lowerV,settings->yellow.upperH,settings->yellow.upperS,settings->yellow.upperV);
            green.setHSV(settings->green.lowerH,settings->green.lowerS,settings->green.lowerV,settings->green.upperH,settings->green.upperS,settings->green.upperV);





            imgHSV=cvCreateImage(cvGetSize(frame_resized),IPL_DEPTH_8U,3);
            imgLUV=cvCreateImage(cvGetSize(frame_resized),IPL_DEPTH_8U,3);
            canny_destination=cvCreateImage(cvGetSize(frame_resized),IPL_DEPTH_8U,1);
            binary_flatten=cvCreateImage(cvGetSize(frame_resized),IPL_DEPTH_8U,1);

            while(1){
                if(settings->createCam!=true)

                //   else
                     createCapture();


                cvResize(frame,frame_resized);
                cvResize(grayScale,frame_resized_gray);
                cvCopy(frame_resized,originalFrame);

                cvSmooth(frame_resized,frame_resized,CV_GAUSSIAN,3,3);
                cvSmooth(frame_resized_gray,frame_resized_gray,CV_GAUSSIAN,3,3);

                if(settings->do_split_rgb||settings->do_canny_b||settings->do_canny_g||settings->do_canny_r)
                cvSplit(frame_resized,r,g,b,NULL);


                cvCvtColor(frame_resized,imgHSV,CV_BGR2HSV);
                cvCvtColor(frame_resized,imgLUV,CV_BGR2Luv);
                cvSplit(imgLUV,L,U,V,NULL);
                if(window%2==0)
                       window+=1;
                cvAdaptiveThreshold(V,L_adp,255,CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,window,cval*(-1));


                red.setHSV(settings->red.lowerH,settings->red.lowerS,settings->red.lowerV,settings->red.upperH,settings->red.upperS,settings->red.upperV);
                yellow.setHSV(settings->yellow.lowerH,settings->yellow.lowerS,settings->yellow.lowerV,settings->yellow.upperH,settings->yellow.upperS,settings->yellow.upperV);
                green.setHSV(settings->green.lowerH,settings->green.lowerS,settings->green.lowerV,settings->green.upperH,settings->green.upperS,settings->green.upperV);


                //Colour Thresholding
                if(settings->do_thresh_red)
                red.imgThresh=red.GetThresholdedImage(imgHSV);                               
                if(settings->do_thresh_yellow)
                yellow.imgThresh=yellow.GetThresholdedImage(imgHSV);
                if(settings->do_thresh_green)
                green.imgThresh=green.GetThresholdedImage(imgHSV);

                //Minimum contours
                if(settings->do_thresh_red_mc){
                    cvCopy(red.imgThresh,red.imgThreshBiggestContour);
                    red.FC_FindBiggestContours(red.imgThreshBiggestContour) ;
                }
                if(settings->do_thresh_yellow_mc){
                    cvCopy(yellow.imgThresh,yellow.imgThreshBiggestContour);
                    yellow.FC_FindBiggestContours(yellow.imgThreshBiggestContour);
                }

                if(settings->do_thresh_green_mc){
                    cvCopy(green.imgThresh,green.imgThreshBiggestContour);
                    green.FC_FindBiggestContours(green.imgThreshBiggestContour) ;
                }



                //adding the 3 channes into a single binary image
                cvAdd(red.imgThresh,yellow.imgThresh,binary_flatten);
                cvAdd(binary_flatten,green.imgThresh,binary_flatten);



                //Canny edge detector
           //     cvCanny(binary_flatten,canny,canny_t1,canny_t2);
                if(settings->do_canny_b)
                    cvCanny(b,canny_destination,canny_t1,canny_t2,3);
                else if
                        (settings->do_canny_g)
                    cvCanny(g,canny_destination,canny_t1,canny_t2,3);
                else if(settings->do_canny_r)
                    cvCanny(r,canny_destination,canny_t1,canny_t2,3);
                else if(settings->do_canny_binary)
                    cvCanny(binary_flatten,canny_destination,canny_t1,canny_t2,3);


                cvSmooth(canny_destination,canny_destination,CV_GAUSSIAN,5,5);


                //vector<vector<Point> > contours;


                if(settings->do_circular_hough){
            //Hough Circles
                results=cvHoughCircles(
                    canny_destination,
                    storage,
                    CV_HOUGH_GRADIENT,
                    dp,
                    canny_destination->width/settings->dFactor,
                    settings->hi > 0 ? settings->hi : 1, settings->lo > 0 ? settings->lo : 1
                );

                //drawing the circles
                for(int i=0;i<results->total;i++){
                    p=(float*)cvGetSeqElem(results,i);
                    pt=cvPoint(cvRound(p[0]),cvRound(p[1]));
                    cvCircle(
                        frame_resized,
                        pt,
                        cvRound(p[2]),
                        CV_RGB(255,0,0)
                        );
                }
}



                red.TrackObjects(red.imgThreshBiggestContour,&frame_resized);
                yellow.TrackObjects(yellow.imgThreshBiggestContour,&frame_resized);

                if(flip->show_orig)
                    IplImage22QImage(frame_resized,&qimg);
                else if(flip->show_canny)
                   IplImage22QImage(canny_destination,&qimg);
                else if(flip->show_thresh_green)
                    IplImage22QImage(green.imgThreshBiggestContour,&qimg);
                else if(flip->show_thresh_red)
                    IplImage22QImage(red.imgThreshBiggestContour,&qimg);
                else if(flip->show_thresh_yellow)
                    IplImage22QImage(yellow.imgThreshBiggestContour,&qimg);
                else if(flip->show_b)
                    IplImage22QImage(b,&qimg);
                else if(flip->show_g)
                    IplImage22QImage(g,&qimg);
                else if(flip->show_r)
                    IplImage22QImage(r,&qimg);
                else if(flip->show_thresh_flat)
                    IplImage22QImage(binary_flatten,&qimg);



                IplImage22QImage(originalFrame,&qimgOrig);



                w.setImageLabels(&qimgOrig,&qimg);



                shared_memory->x=yellow.getX();
                shared_memory->y=yellow.getY();
                shared_memory->found=yellow.isFound();





                time(&end);
                ++counter;
                sec=difftime(end,start);
                settings->fps=counter/sec;






                if(!frame_resized)
                    break;
              cvShowImage("CamOut",canny_destination);


                char c=cvWaitKey(33);
                if(c==27||flip->quit==true)
                    break;


            }
            cvReleaseCapture(&cam);
            delete(settings);
            delete(flip);

            shmdt(shared_memory);



}


    void createCapture(){

        if(settings->createCam==true){
          cam=cvCreateCameraCapture(0);
            if(!cam){
                printf("Camera not available");
                exit(-1);
            }
        }
        else{

            frame=photo;

        }
    }






