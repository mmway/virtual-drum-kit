/* 
 * File:   perkusjaMain.cpp
 * Author: Majk
 *
 * Created on 22 maj 2010, 00:52
 */

#include "stdafx.h"

#include <stdlib.h>
//#include <iostream.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include "cv.h"
#include "highgui.h"
#include "cvaux.h"
#include "cxcore.h"
#include "cxmisc.h"
#include "omp.h"


#include "codeBookMethod.h"
#include "otherFunctions.h"
#include "tracking.h"
#include "VirtualDrums_Globals.h"
#include "Form1.h"

//#include "backgroundSee.h"
//#include "backgroundSeeCodeBook.h"

/*
 * 
 */

using namespace virtualDrums_temp;

//////////////////////////////////////SETUP////////////////////////////////////

double g_dMarkerColorBound = 3;    // bounds of marker color threshold

bool g_bDrawingBox = false;     //if box to find color if drawing (if left mouse button is pressed)
bool g_bCircleFound = false;    //if first circle(marker) was found
bool g_bIfDrewBox = false;    //if box for marker kolor estimation was drawn
bool g_bIfFindMarkerStarted = false;    //if finding marker started

const int g_iNumChannels = 3;  //how many channels




//bool g_bChannels[g_iNumChannels]={true,true,true};  //on which channels we operate

///////////////////////////////////////////////////////////////////////////////

int g_iKey;
int g_iHdims = 16;

float g_fHranges_arr[] = {0,180};
float* g_fHranges = g_fHranges_arr;




CvHistogram *g_histMarker;

CvRect g_rectMarkerSelection;
CvRect g_rectMeanSgiftInitWin;

CvContour *g_contFGfirstMarker;

CvScalar g_scMarkerColorAvg, g_scMarkerColorSdv;
CvScalar g_scMarkerColorAvgHigh = {0,0,0}, g_scMarkerColorAvgLow = {0,0,0};

CvConnectedComp g_ccTrackComp;


CvMemStorage* g_msPyrSegFindMarker = cvCreateMemStorage(0);
CvMemStorage* g_msMeanShift = cvCreateMemStorage(0);
CvMemStorage* g_msConnectFinalMask = cvCreateMemStorage(0);

CvSeq* g_seqConnectFGfirstFindMarker = NULL;





//random images
IplImage *I1,*I2;



//32Float, 3-channel images
IplImage *g_IprevFrame_32f, *g_IdiffFrame_32f, *g_IavgFrame_32f;



//8U, 3-channel images
IplImage *ItempRGB_8u, *I1HSV_8u, *ItempHSV_8u, *g_IHSVfixedMarkerColor_8u, *Itemp_8u, *g_IprevFrame_8u, *g_I1yuv_8u = 0, *g_Iforeground_8u, *g_ImaskFindColor_8u, *g_IforegroundMean_8u, *g_Ihistimg_8u;
IplImage *IHSV_8u, *g_Iyuv_8u = 0;


//8U, 1-channel images
IplImage *IHSV1_8u, *IHSV2_8u, *IHSV3_8u;
IplImage *ItempRGB1_8u, *ItempRGB2_8u, *ItempRGB3_8u;
IplImage *ItempHSV1_8u, *ItempHSV2_8u, *ItempHSV3_8u;
IplImage *g_IHSVfixedMarkerColor1_8u, *g_IHSVfixedMarkerColor2_8u, *g_IHSVfixedMarkerColor3_8u;
IplImage *Itemp1_8u, *Itemp2_8u, *Itemp3_8u;
IplImage *g_IbackgroundMask_8u, *g_ImaskCodeBook1_8u, *g_ImaskCodeBookCC1_8u, *g_ImaskFindColor1_8u, *g_ImaskColorRange1_8u;
IplImage *g_IbackProject1_8u;

//16S, 1-channel images
IplImage *Itemp1_16s;


void AllocateImages( IplImage* I1 ){
CvSize sz = cvGetSize( I1 );

g_IprevFrame_32f = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
g_IdiffFrame_32f = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
g_IavgFrame_32f = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
cvZero( g_IprevFrame_32f );
cvZero( g_IdiffFrame_32f );
cvZero( g_IavgFrame_32f );

ItempRGB_8u = cvCreateImage( sz, IPL_DEPTH_8U, 3 );
ItempHSV_8u = cvCreateImage( sz, IPL_DEPTH_8U, 3 );
IHSV_8u = cvCreateImage( sz, IPL_DEPTH_8U, 3 );
g_IHSVfixedMarkerColor_8u = cvCreateImage( sz, IPL_DEPTH_8U, 3 );
Itemp_8u = cvCreateImage( sz, IPL_DEPTH_8U, 3 );
g_IprevFrame_8u = cvCreateImage( sz, IPL_DEPTH_8U, 3 );
//g_Iyuv_8u = cvCreateImage( sz, IPL_DEPTH_8U, 3 );
g_IbackgroundMask_8u = cvCreateImage( sz, IPL_DEPTH_8U, 3 );
g_Iforeground_8u = cvCreateImage( sz, IPL_DEPTH_8U, 3 );
g_ImaskFindColor_8u = cvCreateImage( sz, IPL_DEPTH_8U, 3 );
g_IforegroundMean_8u = cvCreateImage( sz, IPL_DEPTH_8U, 3 );
g_Ihistimg_8u = cvCreateImage( cvSize(320,200), 8, 3 );
cvZero( ItempRGB_8u );
cvZero( ItempHSV_8u );
cvZero( IHSV_8u );
cvZero( g_IHSVfixedMarkerColor_8u );
cvZero( Itemp_8u );
cvZero( g_IprevFrame_8u );
cvZero( g_IbackgroundMask_8u );
cvZero( g_Iforeground_8u );
cvZero( g_ImaskFindColor_8u );
cvZero( g_IforegroundMean_8u );
cvZero( g_Ihistimg_8u );
//cvZero( g_Iyuv_8u );

IHSV1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
IHSV2_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
IHSV3_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
ItempRGB1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
ItempRGB2_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
ItempRGB3_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
ItempHSV1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
ItempHSV2_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
ItempHSV3_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
g_IHSVfixedMarkerColor1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
g_IHSVfixedMarkerColor2_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
g_IHSVfixedMarkerColor3_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
Itemp1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
Itemp2_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
Itemp3_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
g_ImaskCodeBook1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
g_ImaskCodeBookCC1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
g_ImaskFindColor1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
g_ImaskColorRange1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
g_IbackProject1_8u = cvCreateImage( sz, 8, 1 );


cvZero( IHSV1_8u );
cvZero( IHSV2_8u );
cvZero( IHSV3_8u );
cvZero( ItempRGB1_8u );
cvZero( ItempRGB2_8u );
cvZero( ItempRGB3_8u );
cvZero( ItempHSV1_8u );
cvZero( ItempHSV2_8u );
cvZero( ItempHSV3_8u );
cvZero( Itemp1_8u );
cvZero( Itemp2_8u );
cvZero( Itemp3_8u );
cvSet(g_ImaskCodeBook1_8u,cvScalar(255));
cvZero( g_ImaskCodeBookCC1_8u );
cvZero( g_ImaskFindColor1_8u );
cvZero( g_ImaskColorRange1_8u );


Itemp1_16s = cvCreateImage( sz, IPL_DEPTH_16S, 1 );

cvZero( Itemp1_16s );


g_histMarker = cvCreateHist( 1, &g_iHdims, CV_HIST_ARRAY, &g_fHranges, 1 );

}

void DeallocateImages()
{
cvReleaseImage( &I1);
cvReleaseImage( &I2);
cvReleaseImage( &g_IprevFrame_32f );
cvReleaseImage( &g_IdiffFrame_32f );
cvReleaseImage( &g_IavgFrame_32f );

cvReleaseImage( &ItempRGB_8u );
cvReleaseImage( &ItempHSV_8u );
cvReleaseImage( &IHSV_8u );
cvReleaseImage( &g_IHSVfixedMarkerColor_8u );
cvReleaseImage( &Itemp_8u );
cvReleaseImage( &g_IprevFrame_8u );
cvReleaseImage( &g_Iyuv_8u );
cvReleaseImage( &g_Iforeground_8u );
cvReleaseImage( &g_ImaskFindColor_8u );
cvReleaseImage( &g_IforegroundMean_8u );
cvReleaseImage( &g_IbackgroundMask_8u );
cvReleaseImage( &g_Ihistimg_8u );

cvReleaseImage( &g_ImaskCodeBook1_8u );
cvReleaseImage( &g_ImaskCodeBookCC1_8u );
cvReleaseImage( &g_ImaskFindColor1_8u );
cvReleaseImage( &g_ImaskColorRange1_8u );
cvReleaseImage( &IHSV1_8u );
cvReleaseImage( &IHSV2_8u );
cvReleaseImage( &IHSV3_8u );
cvReleaseImage( &g_IHSVfixedMarkerColor1_8u );
cvReleaseImage( &g_IHSVfixedMarkerColor2_8u );
cvReleaseImage( &g_IHSVfixedMarkerColor3_8u );
cvReleaseImage( &ItempRGB1_8u );
cvReleaseImage( &ItempRGB2_8u );
cvReleaseImage( &ItempRGB3_8u );
cvReleaseImage( &ItempHSV1_8u );
cvReleaseImage( &ItempHSV2_8u );
cvReleaseImage( &ItempHSV3_8u );
cvReleaseImage( &Itemp1_8u );
cvReleaseImage( &Itemp2_8u );
cvReleaseImage( &Itemp3_8u );
cvReleaseImage( &g_IbackProject1_8u );


cvReleaseImage( &Itemp1_16s );

}


void mouseBox(int event, int x, int y, int flags, void* param) {

    //bool _bDrawingBox=false; CvRect _Box;
    IplImage* _Imask = (IplImage*) param;

    switch( event ) {
        case CV_EVENT_MOUSEMOVE: {
            if( g_bDrawingBox ) {
                g_rectMarkerSelection.width = x-g_rectMarkerSelection.x;
                g_rectMarkerSelection.height = y-g_rectMarkerSelection.y;
            }
        }
        break;

        case CV_EVENT_LBUTTONDOWN: {
            g_bDrawingBox = true;
            g_bIfDrewBox = false;
            g_bIfFindMarkerStarted = false;
            g_rectMarkerSelection = cvRect(x, y, 0, 0);
        }
        break;

        case CV_EVENT_LBUTTONUP: {
            g_bDrawingBox = false;
            g_bIfDrewBox = true;
            if(g_rectMarkerSelection.width<0) {
                g_rectMarkerSelection.x+=+g_rectMarkerSelection.width;
                g_rectMarkerSelection.width *=-1;
            }
            if(g_rectMarkerSelection.height<0) {
                g_rectMarkerSelection.y+=g_rectMarkerSelection.height;
                g_rectMarkerSelection.height*=-1;
            }
            //drawBox(_Imask, g_rectMarkerSelection);
        }
        break;
    }
    cvReleaseImage(&_Imask);
};




int startMain() {

//    uchar* g_ucPointPointner;
//    codeBook* codeBooks;
//    unsigned* codeBookBounds;

//    g_scMarkerColorAvg = (CvScalar*) (0,0,0);
//    g_scMarkerColorSdv = (CvScalar*) (0,0,0);
//    g_scMarkerColorAvgHigh = cvScalarAll(0);
//    g_scMarkerColorAvgLow = cvScalarAll(0);

	char cFileName[50];
	char _cMessages[200];

    int iTimeDiff = 1, _iTimeDiffTemp = 1, iFpsTemp = 1, iFps = 20, g_iConstTresholdPosition = 150, g_iFrameCount = 0;	

	CvBGCodeBookModel *_backgroundModelCamera1;
    _backgroundModelCamera1 = cvCreateBGCodeBookModel();
	CvBGCodeBookModel *_backgroundModelCamera2;
    _backgroundModelCamera2 = cvCreateBGCodeBookModel();

	IplConvKernel* g_seStructElementIntensity = cvCreateStructuringElementEx( 5, 5, 0, 0, CV_SHAPE_ELLIPSE, NULL );

    CvCapture* camera1;
	CvCapture* camera2;
	camera1 = cvCaptureFromCAM(CV_CAP_DSHOW + 0);
	camera2 = cvCaptureFromCAM(CV_CAP_DSHOW + 1);

	//Setting up capture setup
		cvSetCaptureProperty(camera1 ,CV_CAP_PROP_FRAME_WIDTH,800);
		cvSetCaptureProperty(camera1 ,CV_CAP_PROP_FRAME_HEIGHT,600);
		//cvSetCaptureProperty(camera1 ,CV_CAP_PROP_GAIN,300);


		cvSetCaptureProperty(camera2 ,CV_CAP_PROP_FRAME_WIDTH,800);
		cvSetCaptureProperty(camera2 ,CV_CAP_PROP_FRAME_HEIGHT,600);
		//cvSetCaptureProperty(camera2 ,CV_CAP_PROP_BRIGHTNESS,300);
	//end - Setting up capture setup




    if( (!camera1) || (!camera2)  )
    {
		sprintf(_cMessages, "Could not initialize capturing...\n");
		MessageBox::Show(" ");
        return -1;
    }
    
    cvNamedWindow("CameraView 1", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("CameraView 2", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("CameraView 3", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Camera 1 View", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Camera 2 View", CV_WINDOW_AUTOSIZE);

    cvSetMouseCallback(
                        "Camera 1 View",
                        mouseBox,
                        (void*) (g_ImaskFindColor1_8u)
                      );

    //cvGrabFrame(camera1);               // only for clone function
    //I1 = cvRetrieveFrame(camera1);       //
    //g_Iyuv_8u = cvCloneImage(I1);



    ///////////////////////////////////////////////////////////////////////////
    ////////////////////////////end_of_initial_main_stuff//////////////////////
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////


    // main loop
    while(1){

        //starting time count for fps computing
        iTimeDiff = GetTickCount();

        //First time: init all images and learn backgrund
        if (g_iFrameCount==0){
            cvGrabFrame(camera1);
            I1 = cvRetrieveFrame(camera1);
            AllocateImages(I1);
            g_Iyuv_8u = cvCloneImage(I1);
            
            learnBackgroundCodeBook(camera1, _backgroundModelCamera1);
        }


		_iTimeDiffTemp = GetTickCount();
		#pragma omp parallel sections default(shared) private(cFileName) shared(ItempRGB_8u, camera1, camera2, I1, I2, g_iFrameCount)
		{
			//taking frame from camera to image I
			#pragma omp section  
			{
				cvGrabFrame(camera1);
				I1 = cvRetrieveFrame(camera1);
				sprintf(cFileName, "z_Image%d_norm_1.jpg", g_iFrameCount);
		        //cvSaveImage(cFileName, I1);
				cvCopy (I1, ItempRGB_8u);
			}

			#pragma omp section  
			{
				cvGrabFrame(camera2);
				I2 = cvRetrieveFrame(camera2);
				sprintf(cFileName, "z_Image%d_norm_2.jpg", g_iFrameCount);
				//cvSaveImage(cFileName, I2);
			}
		}
		g_iTimeOperation1 = GetTickCount() - _iTimeDiffTemp;

        //for forward using
        cvCvtColor(I1,ItempHSV_8u,CV_BGR2HSV);
        cvSplit(ItempHSV_8u, IHSV1_8u, IHSV2_8u, IHSV3_8u, NULL);

        //to YUV only for codebook function
        cvCvtColor(I1,g_Iyuv_8u,CV_BGR2YCrCb);   

		_iTimeDiffTemp = GetTickCount();
			cvBGCodeBookDiff( _backgroundModelCamera1, g_Iyuv_8u, g_ImaskCodeBook1_8u );
		g_iTimeOperation2 = GetTickCount() - _iTimeDiffTemp;

        cvMerge(g_ImaskCodeBook1_8u, g_ImaskCodeBook1_8u, g_ImaskCodeBook1_8u, NULL, g_Iforeground_8u);
        cvThreshold(g_Iforeground_8u, g_Iforeground_8u, 100, 1, CV_THRESH_BINARY);
        cvMul(I1, g_Iforeground_8u, g_Iforeground_8u);   //only foregrund in GBR

        //create HSV in separate channels to forward compute
        cvCvtColor(g_Iforeground_8u,ItempHSV_8u,CV_BGR2HSV);
        cvSplit(ItempHSV_8u, ItempHSV1_8u, ItempHSV2_8u, ItempHSV3_8u, NULL);

        //early cuting out some color (necessary?????)
        cvInRangeS(ItempHSV1_8u, cvScalar(50), cvScalar(120), g_ImaskColorRange1_8u );
        cvMerge(g_ImaskColorRange1_8u, g_ImaskColorRange1_8u, g_ImaskColorRange1_8u, NULL, Itemp_8u);
        cvThreshold(Itemp_8u, Itemp_8u, 100, 1, CV_THRESH_BINARY);
        cvMul(I1, Itemp_8u, Itemp_8u);         //only foregrund in GBR with cut out some color
        cvCvtColor(Itemp_8u, g_IHSVfixedMarkerColor_8u, CV_BGR2HSV);
        cvSplit(g_IHSVfixedMarkerColor_8u, g_IHSVfixedMarkerColor1_8u, g_IHSVfixedMarkerColor2_8u, g_IHSVfixedMarkerColor3_8u, NULL);


        //find markers to init mean-shift and take kolor of the marker
        //if ( !g_bCircleFound ){


        //}

        //show position of found marker and init them to mean-shift window

        //computing user-marked color of a marker
        if (g_bDrawingBox){

            cvZero(g_ImaskFindColor1_8u);
 
            drawBox(g_ImaskFindColor1_8u, g_rectMarkerSelection, CV_FILLED);

            //cvMerge(g_ImaskFindColor1_8u, g_ImaskFindColor1_8u, g_ImaskFindColor1_8u, NULL, g_ImaskFindColor_8u);
            cvThreshold(g_ImaskFindColor1_8u, g_ImaskFindColor1_8u, 100, 1, CV_THRESH_BINARY);
            cvAnd(g_ImaskFindColor1_8u, g_IHSVfixedMarkerColor1_8u, Itemp2_8u); //operation "and" rectSelection with foreground
            cvNormalize(Itemp2_8u, Itemp2_8u, 0, 255, CV_MINMAX);

            cvAvgSdv(IHSV1_8u, &g_scMarkerColorAvg, &g_scMarkerColorSdv, Itemp2_8u);

            //printf("dziala %f \n\n", g_scMarkerColorAvg.val[0]);
            //cvCopy(g_scMarkerColorAvg->val, g_scMarkerColorAvgLow.val);

            g_scMarkerColorAvgLow.val[0] = g_scMarkerColorAvg.val[0];
            g_scMarkerColorAvgHigh.val[0] = g_scMarkerColorAvg.val[0];

            g_scMarkerColorAvgLow.val[0] -= 2.5 *g_scMarkerColorSdv.val[0];
            g_scMarkerColorAvgHigh.val[0] += 2.5 *g_scMarkerColorSdv.val[0];

//            cvSub(g_scMarkerColorAvgLow.val, g_scMarkerColorSdv.val, g_scMarkerColorAvgLow.val);    //3 times -> bound is 3 * Sdv
//            cvSub(g_scMarkerColorAvgLow.val, g_scMarkerColorSdv.val, g_scMarkerColorAvgLow.val);
//            cvSub(g_scMarkerColorAvgLow.val, g_scMarkerColorSdv.val, g_scMarkerColorAvgLow.val);
//            g_scMarkerColorAvgLow.val[0]-= g_dMarkerColorBound *3 ;

//            cvAdd(g_scMarkerColorAvgHigh.val, g_scMarkerColorSdv.val, g_scMarkerColorAvgHigh.val);  //3 times -> bound is 3 * Sdv
//            cvAdd(g_scMarkerColorAvgHigh.val, g_scMarkerColorSdv.val, g_scMarkerColorAvgHigh.val);
//            cvAdd(g_scMarkerColorAvgHigh.val, g_scMarkerColorSdv.val, g_scMarkerColorAvgHigh.val);
//            g_scMarkerColorAvgHigh.val[0]+= g_dMarkerColorBound *3;

            drawBox(I1, g_rectMarkerSelection, 1);
        }

        //leaving only choosed color (by finding cirlce or making rect) (color with some range)
        cvInRangeS(ItempHSV1_8u,g_scMarkerColorAvgLow, g_scMarkerColorAvgHigh, g_ImaskFindColor1_8u );
//        cvMerge(g_ImaskFindColor1_8u, g_ImaskFindColor1_8u, g_ImaskFindColor1_8u, NULL, g_ImaskFindColor_8u);
//        cvThreshold(g_ImaskFindColor_8u, g_ImaskFindColor_8u, 100, 1, CV_THRESH_BINARY);
//        cvMul(g_Iforeground_8u, g_ImaskFindColor_8u, g_ImaskFindColor_8u);


        //leaving only bigger areas
//        IplConvKernel* g_seStructElement = cvCreateStructuringElementEx( 5, 5, 0, 0, CV_SHAPE_RECT, NULL );
//        cvErode(g_ImaskFindColor_8u,g_ImaskFindColor_8u, g_seStructElement, 1);
//        cvDilate(g_ImaskFindColor_8u,g_ImaskFindColor_8u, g_seStructElement, 1);


        // segmentation final foreground
        if (g_bIfDrewBox){

            //how to use this cvSeq ?? want to get rect of countur of segmented marker
            //g_seqConnectFGfirstFindMarker = cvSegmentFGMask(g_ImaskFindColor1_8u, 0, 10, g_msConnectFinalMask );
//            printf("total connect seq: %d\n\n", cvSegmentFGMask(g_ImaskFindColor1_8u, 0, 10, g_msConnectFinalMask )->elem_size);
        }
        //g_contFGfirstMarker->ptr = g_seqConnectFGfirstFindMarker->first->data;
        //printf("Ile avg FPS: %d\n\n", g_contFGfirstMarker->rect);
        //drawBox(I1, g_contFGfirstMarker->rect, 1);



//        // if found any markers then start tracking
//        if (g_bIfDrewBox){
//
//			_iTimeDiffTemp = GetTickCount();
//				track(g_ImaskFindColor_8u, g_IbackProject1_8u, g_histMarker, g_ccTrackComp, g_rectMarkerSelection, g_bIfFindMarkerStarted, g_ImaskFindColor1_8u);
//			g_iTimeOperation3 = GetTickCount() - _iTimeDiffTemp;
//
//                cvZero( g_Ihistimg_8u );
//                int bin_w = g_Ihistimg_8u->width / g_iHdims;
//                for( int i = 0; i < g_iHdims; i++ )
//                {
//                    int val = cvRound( cvGetReal1D(g_histMarker->bins,i)*g_Ihistimg_8u->height/255 );
//                    CvScalar color = hsv2rgb(i*180.f/g_iHdims);
//                    cvRectangle( g_Ihistimg_8u, cvPoint(i*bin_w,g_Ihistimg_8u->height),
//                                 cvPoint((i+1)*bin_w,g_Ihistimg_8u->height - val),
//                                 color, -1, 8, 0 );
//                }
//
//            cvNormalize(g_IbackProject1_8u, g_IbackProject1_8u, 0, 255,CV_MINMAX, NULL);
////            cvSave("!backproj.txt", g_IbackProject1_8u);
//
//
//
//            drawBox(I1, g_ccTrackComp.rect, 1);
//
//
////            cvRectangle(I1,
////                            cvPoint(g_ccMeanShift->rect.x,g_ccMeanShift->rect.y),
////                            cvPoint(g_ccMeanShift->rect.x+g_ccMeanShift->rect.width,g_ccMeanShift->rect.y+g_ccMeanShift->rect.height),
////                            CV_RGB(0xff,0x00,0x00),
////                            1,
////                            8,
////                            0 );
//
//        }


		//////circles find
		//	IplConvKernel* g_seStructElementIntensity = cvCreateStructuringElementEx( 3, 3, 0, 0, CV_SHAPE_ELLIPSE, NULL );
		//	cvCvtColor(Itemp_8u, Itemp1_8u, CV_BGR2GRAY);
		//	cvDilate(Itemp1_8u, Itemp1_8u, g_seStructElementIntensity, 2);
		//	// Memory for hough circles
		//	CvMemStorage* storage = cvCreateMemStorage(0);
		//	// hough detector works better with some smoothing of the image
		//	cvSmooth( Itemp1_8u, Itemp1_8u, CV_GAUSSIAN, 9, 9 );
		//	CvSeq* circles = cvHoughCircles(Itemp1_8u, storage, CV_HOUGH_GRADIENT, 2, Itemp1_8u->height/6, 100, 70, 5, 200);
		////end - circles find

		//for( int i = 0; i < circles->total; i++ ) {
		//	float* p = (float*) cvGetSeqElem( circles, i );
		//	CvPoint pt = cvPoint( cvRound( p[0] ), cvRound( p[1] ) );
		//	cvCircle(
		//			I1,
		//			pt,
		//			cvRound( p[2] ),
		//			CV_RGB(0xff,0xff,0xff)
		//			);
		//}


        

        // OUTPUT TO:
        cvShowImage("Camera 1 View", I1);
		cvShowImage("Camera 2 View", I2);


		cvErode(g_ImaskFindColor1_8u, g_ImaskFindColor1_8u, g_seStructElementIntensity, 2);
        cvShowImage("CameraView 1", g_ImaskFindColor1_8u);



//        cvShowImage("CameraView 2", Itemp_8u);

        //cvShowImage("CameraView 3", g_IbackProject1_8u);



//        sprintf(cFileName, "z_Image%d_norm.jpg", g_iFrameCount);
//        cvSaveImage(cFileName, g_Iforeground_8u);

//        sprintf(cFileName, "z_Image%d_norm.jpg", g_iFrameCount);
//        cvSaveImage(cFileName, I1);
//        sprintf(cFileName, "z_Image%d_segm.jpg", g_iFrameCount);
//        cvSaveImage(cFileName, g_ImaskCodeBookCC1_8u);






        //averaging fps
        iTimeDiff = GetTickCount() - iTimeDiff;
        iFpsTemp = iFpsTemp + iTimeDiff;
        if ((g_iFrameCount % 6 == 0) && (g_iFrameCount != 0)){
            iFps = static_cast<int>(1000/(iFpsTemp/6));  // 6 - ilosc ramek usredniania
            iFpsTemp = 1;
        }
        //printf("Ile avg FPS: %d\n\n", iFps);
		g_iCamera1FPS = iFps;


        updateBackgroundCodeBook(I1, _backgroundModelCamera1, g_iFrameCount, iFps);

        g_iFrameCount++;

        g_iKey = cvWaitKey(10)&0xFF;
        g_iKey = tolower(g_iKey);

        changeCodeBookParam(_backgroundModelCamera1, g_iKey, g_iNumChannels);

        if( g_iKey == 27 ) break;        
    
    }

    

    //finish jobs
    cvDestroyAllWindows();
    cvReleaseCapture(&camera1);
	cvReleaseCapture(&camera2);
//    printf("dziala\n\n\n");
    DeallocateImages();
//    printf("dziala\n\n\n");


    return (EXIT_SUCCESS);
}

