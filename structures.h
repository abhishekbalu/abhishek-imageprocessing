#ifndef STRUCTURES_H
#define STRUCTURES_H

#endif // STRUCTURES_H

typedef struct filters{
    char imgThresh;
    bool do_canny_src;
    char HSV;
    bool do_canny_binary;

    bool do_canny_r;
    bool do_canny_g;
    bool do_canny_b;

    bool do_split_rgb;
    bool createCam;
    bool do_circular_hough;

    bool do_thresh_red;
    bool do_thresh_green;
    bool do_thresh_yellow;

    bool do_thresh_red_mc;
    bool do_thresh_green_mc;
    bool do_thresh_yellow_mc;

    //some settings
    float fps;
    struct HSV{
    int lowerH,lowerS,lowerV;
    int upperH,upperS,upperV;
    }red,yellow,green;

    int hi;
    int lo;
    int dp;
    int dFactor;


};

typedef struct switches{
   bool show_canny;
   bool show_orig;
   bool show_thresh_red;
   bool show_thresh_green;
   bool show_thresh_yellow;
   bool show_r;
   bool show_g;
   bool show_b;
   bool show_thresh_flat;
   bool quit;
   bool show_thresh_red_mc;
   bool show_thresh_green_mc;
   bool show_thresh_yellow_mc;




};

