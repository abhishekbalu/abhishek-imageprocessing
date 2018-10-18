#ifndef CONTOUR_H
#define CONTOUR_H

#endif // CONTOUR_H



//Contours---------------------------
CvArr* _mask;
CvMat mstub, *mask ;


int nContours = 0;
double largest_length = 0,len = 0;
CvContourScanner scanner;
uchar* dst;

CvRect R;
IplImage temp;
CvSeq *contours, *c;
CvSeq* newC;
// ------------------------------------


void   FC_FindBiggestContours(IplImage *src)
    {

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

    cvReleaseImage(&src_img);
   // cvReleaseImage(&temp);

    //return dest;
   }

