#include "stdafx.h"

#include <stdlib.h>
#define _USE_MATH_DEFINES	//for PI constant
#include <math.h>
#include <windows.h>
#include <time.h>
#include <vector>

#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv/cvaux.h"
#include "opencv/cxcore.h"
#include "opencv/cxmisc.h"
#include "omp.h"	//openMP

#include "codeBookMethod.h"
#include "otherFunctions.h"
#include "VirtualDrums_Globals.h"
#include "Form1.h"
#include "markerPosition3d.h"



using namespace virtualDrums_temp;


//////////////////////////////////////SETUP////////////////////////////////////

bool l_bDrawingBox = false;     //if box is drawing to define color of markers
bool l_bIfDrewBox = false;    //if box was drawn to define color of markers
bool l_bIfFindMarkerStarted = false;    //if finding marker started

///////////////////////////////////////////////////////////////////////////////


//int
	int l_iKey;	//to store what key was hitted


//cvRETANGLES
	CvRect l_rectMaskFindMarkerColorSelection;	//defines rectangle of markers color


//cvSCALARS
	CvScalar	l_scMarkerColorAvgTemp, l_scMarkerColorSdvTemp, 
				l_scMarkerSaturationAvgTemp, l_scMarkerSaturationSdvTemp, 
				l_scMarkerValueAvgTemp, l_scMarkerValueSdvTemp;

	CvScalar	l_scMarker1ColorAvg, l_scMarker1ColorSdv, 
				l_scMarker1SaturationAvg, l_scMarker1SaturationSdv, 
				l_scMarker1ValueAvg, l_scMarker1ValueSdv;
	CvScalar	l_scMarker2ColorAvg, l_scMarker2ColorSdv, 
				l_scMarker2SaturationAvg, l_scMarker2SaturationSdv,	
				l_scMarker2ValueAvg, l_scMarker2ValueSdv;

	CvScalar	l_scMarker1ColorAvgHigh = {0,0,0}, l_scMarker1ColorAvgLow = {0,0,0},			//bounds of marker 1 color
				l_scMarker1SaturationAvgHigh = {0,0,0}, l_scMarker1SaturationAvgLow = {0,0,0};	//bounds of marker 1 saturation
	CvScalar	l_scMarker2ColorAvgHigh = {0,0,0}, l_scMarker2ColorAvgLow = {0,0,0},			//bounds of marker 2 color
				l_scMarker2SaturationAvgHigh = {0,0,0}, l_scMarker2SaturationAvgLow = {0,0,0};	//bounds of marker 2 saturation


//random images
	IplImage *l_I1,*l_I2;
	IplImage *l_I1temp,*l_I2temp;


//8U, 3-channel images
	IplImage *l_I1hsv_8u, *l_I1yuv_8u;
	IplImage *l_I2hsv_8u, *l_I2yuv_8u;
	IplImage *l_ImaskFindMarkerColor1_8u, *l_ImaskFindMarkerSaturation1_8u, *l_ImaskFindMarkerValue1_8u;


//masks for camera 1 to show steps of processing
	IplImage *l_I1maskWithoutBackground1_8u, *l_I1maskMarker1ColorSeparation1_8u, *l_I1maskMarker2ColorSeparation1_8u, 
			 *l_I1maskMarker1ColorSeparationWithoutBackground1_8u, *l_I1maskMarker2ColorSeparationWithoutBackground1_8u,
			 *l_I1maskMarker1ColorSeparationWithoutBackgroundClosed1_8u, *l_I1maskMarker2ColorSeparationWithoutBackgroundClosed1_8u,
			 *l_I1maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u, *l_I1maskMarker2ColorSeparationWithoutBackgroundClosedSegment1_8u;


//masks for camera 2 to show steps of processing
	IplImage *l_I2maskWithoutBackground1_8u, *l_I2maskMarker1ColorSeparation1_8u, *l_I2maskMarker2ColorSeparation1_8u, 
			 *l_I2maskMarker1ColorSeparationWithoutBackground1_8u, *l_I2maskMarker2ColorSeparationWithoutBackground1_8u,
			 *l_I2maskMarker1ColorSeparationWithoutBackgroundClosed1_8u, *l_I2maskMarker2ColorSeparationWithoutBackgroundClosed1_8u,
			 *l_I2maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u, *l_I2maskMarker2ColorSeparationWithoutBackgroundClosedSegment1_8u;


//32Float, 3-channel images


//32Float, 1-channel images
	IplImage *l_I1undistortionMainLoopSizeMapX1_32f, *l_I1undistortionMainLoopSizeMapY1_32f;
	IplImage *l_I2undistortionMainLoopSizeMapX1_32f, *l_I2undistortionMainLoopSizeMapY1_32f;


//8U, 1-channel images
	IplImage *l_I1hsv1_8u, *l_I1hsv2_8u, *l_I1hsv3_8u;
	IplImage *l_I2hsv1_8u, *l_I2hsv2_8u, *l_I2hsv3_8u;

	IplImage *l_I1hsvForeground1_8u, *l_I1hsvForegroundFindMarkerColor1_8u, *l_I1hsvForegroundFindMarkerSaturation1_8u, *l_I1hsvForegroundFinal1_8u;
	IplImage *l_I2hsvForeground1_8u, *l_I2hsvForegroundFindMarkerColor1_8u, *l_I2hsvForegroundFindMarkerSaturation1_8u, *l_I2hsvForegroundFinal1_8u;

	IplImage *l_I1maskCodeBook1_8u;
	IplImage *l_I2maskCodeBook1_8u;

	IplImage *l_I1maskTemp1_8u, *l_I1maskTemp2_8u;
	IplImage *l_I2maskTemp1_8u, *l_I2maskTemp2_8u;

	IplImage *l_I1maskAroundMarker1Area1_8u, *l_I1maskAroundMarker2Area1_8u;
	IplImage *l_I2maskAroundMarker1Area1_8u, *l_I2maskAroundMarker2Area1_8u;

//16S, 1-channel images



void mmAllocateImages( IplImage* _I ){
CvSize sz = cvGetSize( _I );


////CAMERA 1

	//3channel 8u
	l_I1hsv_8u = cvCreateImage( sz, IPL_DEPTH_8U, 3 );
	l_I1yuv_8u = cvCreateImage( sz, IPL_DEPTH_8U, 3 );

	cvZero( l_I1hsv_8u );
	cvZero( l_I1yuv_8u );

	//1channel 8u
	l_I1hsv1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1hsv2_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1hsv3_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1maskCodeBook1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1hsvForeground1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1hsvForegroundFindMarkerColor1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1maskTemp1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1maskTemp2_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1hsvForegroundFindMarkerSaturation1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1hsvForegroundFinal1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1maskWithoutBackground1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1maskMarker1ColorSeparation1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1maskMarker2ColorSeparation1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1maskMarker1ColorSeparationWithoutBackground1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1maskMarker2ColorSeparationWithoutBackground1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1maskMarker1ColorSeparationWithoutBackgroundClosed1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1maskMarker2ColorSeparationWithoutBackgroundClosed1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1maskMarker2ColorSeparationWithoutBackgroundClosedSegment1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1maskAroundMarker1Area1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I1maskAroundMarker2Area1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );


	cvZero( l_I1hsv1_8u );
	cvZero( l_I1hsv2_8u );
	cvZero( l_I1hsv3_8u );
	cvZero( l_I1maskCodeBook1_8u );
	cvZero( l_I1hsvForeground1_8u );
	cvZero( l_I1hsvForegroundFindMarkerColor1_8u );
	cvZero( l_I1maskTemp1_8u );
	cvZero( l_I1maskTemp2_8u );
	cvZero( l_I1hsvForegroundFindMarkerSaturation1_8u );
	cvZero( l_I1hsvForegroundFinal1_8u );
	cvZero( l_I1maskWithoutBackground1_8u );
	cvZero( l_I1maskMarker1ColorSeparation1_8u );
	cvZero( l_I1maskMarker2ColorSeparation1_8u );
	cvZero( l_I1maskMarker1ColorSeparationWithoutBackground1_8u );
	cvZero( l_I1maskMarker2ColorSeparationWithoutBackground1_8u );
	cvZero( l_I1maskMarker1ColorSeparationWithoutBackgroundClosed1_8u );
	cvZero( l_I1maskMarker2ColorSeparationWithoutBackgroundClosed1_8u );
	cvZero( l_I1maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u );
	cvZero( l_I1maskMarker2ColorSeparationWithoutBackgroundClosedSegment1_8u );
	cvZero( l_I1maskAroundMarker1Area1_8u );
	cvZero( l_I1maskAroundMarker2Area1_8u );


	//32Float, 1-channel images

////end - CAMERA 1



////CAMERA 2

	//3channel 8u
	l_I2hsv_8u = cvCreateImage( sz, IPL_DEPTH_8U, 3 );
	l_I2yuv_8u = cvCreateImage( sz, IPL_DEPTH_8U, 3 );

	cvZero( l_I2hsv_8u );
	cvZero( l_I2yuv_8u );

	//1channel 8u
	l_I2hsv1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2hsv2_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2hsv3_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2maskCodeBook1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2hsvForeground1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2hsvForegroundFindMarkerColor1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2maskTemp1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2maskTemp2_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2hsvForegroundFindMarkerSaturation1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2hsvForegroundFinal1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2maskWithoutBackground1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2maskMarker1ColorSeparation1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2maskMarker2ColorSeparation1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2maskMarker1ColorSeparationWithoutBackground1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2maskMarker2ColorSeparationWithoutBackground1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2maskMarker1ColorSeparationWithoutBackgroundClosed1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2maskMarker2ColorSeparationWithoutBackgroundClosed1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2maskMarker2ColorSeparationWithoutBackgroundClosedSegment1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2maskAroundMarker1Area1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_I2maskAroundMarker2Area1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );

	cvZero( l_I2hsv1_8u );
	cvZero( l_I2hsv2_8u );
	cvZero( l_I2hsv3_8u );
	cvZero( l_I2maskCodeBook1_8u );
	cvZero( l_I2hsvForeground1_8u );
	cvZero( l_I2hsvForegroundFindMarkerColor1_8u );
	cvZero( l_I2maskTemp1_8u );
	cvZero( l_I2maskTemp2_8u );
	cvZero( l_I2hsvForegroundFindMarkerSaturation1_8u );
	cvZero( l_I2hsvForegroundFinal1_8u );
	cvZero( l_I2maskWithoutBackground1_8u );
	cvZero( l_I2maskMarker1ColorSeparation1_8u );
	cvZero( l_I2maskMarker2ColorSeparation1_8u );
	cvZero( l_I2maskMarker1ColorSeparationWithoutBackground1_8u );
	cvZero( l_I2maskMarker2ColorSeparationWithoutBackground1_8u );
	cvZero( l_I2maskMarker1ColorSeparationWithoutBackgroundClosed1_8u );
	cvZero( l_I2maskMarker2ColorSeparationWithoutBackgroundClosed1_8u );
	cvZero( l_I2maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u );
	cvZero( l_I2maskMarker2ColorSeparationWithoutBackgroundClosedSegment1_8u );
	cvZero( l_I2maskAroundMarker1Area1_8u );
	cvZero( l_I2maskAroundMarker2Area1_8u );

	//32Float, 1-channel images

//end - CAMERA 2


////SHARED

	//3channel 8u

	//1channel 8u
	l_ImaskFindMarkerColor1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_ImaskFindMarkerSaturation1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	l_ImaskFindMarkerValue1_8u = cvCreateImage( sz, IPL_DEPTH_8U, 1 );

//end - SHARED

}

void mmDeallocateImages(){


	////CAMERA 1

		cvReleaseImage( &l_I1);

		//3channel 8u
		cvReleaseImage( &l_I1hsv_8u);
		cvReleaseImage( &l_I1yuv_8u);

		//1channel 8u
		cvReleaseImage( &l_I1hsv1_8u);
		cvReleaseImage( &l_I1hsv2_8u);
		cvReleaseImage( &l_I1hsv3_8u);
		cvReleaseImage( &l_I1maskCodeBook1_8u);
		cvReleaseImage( &l_I1hsvForeground1_8u);
		cvReleaseImage( &l_I1hsvForegroundFindMarkerColor1_8u);
		cvReleaseImage( &l_I1maskTemp1_8u);
		cvReleaseImage( &l_I1maskTemp2_8u);
		cvReleaseImage( &l_I1hsvForegroundFindMarkerSaturation1_8u);
		cvReleaseImage( &l_I1hsvForegroundFinal1_8u);
		cvReleaseImage( &l_I1maskWithoutBackground1_8u );
		cvReleaseImage( &l_I1maskMarker1ColorSeparation1_8u );
		cvReleaseImage( &l_I1maskMarker2ColorSeparation1_8u );
		cvReleaseImage( &l_I1maskMarker1ColorSeparationWithoutBackground1_8u );
		cvReleaseImage( &l_I1maskMarker2ColorSeparationWithoutBackground1_8u );
		cvReleaseImage( &l_I1maskMarker1ColorSeparationWithoutBackgroundClosed1_8u );
		cvReleaseImage( &l_I1maskMarker2ColorSeparationWithoutBackgroundClosed1_8u );
		cvReleaseImage( &l_I1maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u );
		cvReleaseImage( &l_I1maskMarker2ColorSeparationWithoutBackgroundClosedSegment1_8u );
		cvReleaseImage( &l_I1maskAroundMarker1Area1_8u );
		cvReleaseImage( &l_I1maskAroundMarker2Area1_8u );

		//32Float, 1-channel images
		cvReleaseImage( &l_I1undistortionMainLoopSizeMapX1_32f);
		cvReleaseImage( &l_I1undistortionMainLoopSizeMapY1_32f);

	//end - CAMERA 1



	////CAMERA 2

		cvReleaseImage( &l_I2);
		//cvReleaseImage( &l_I2temp);

		//3channel 8u
		cvReleaseImage( &l_I2hsv_8u);
		cvReleaseImage( &l_I2yuv_8u);

		//1channel 8u
		cvReleaseImage( &l_I2hsv1_8u);
		cvReleaseImage( &l_I2hsv2_8u);
		cvReleaseImage( &l_I2hsv3_8u);
		cvReleaseImage( &l_I2maskCodeBook1_8u);
		cvReleaseImage( &l_I2hsvForeground1_8u);
		cvReleaseImage( &l_I2hsvForegroundFindMarkerColor1_8u);
		cvReleaseImage( &l_I2maskTemp1_8u);
		cvReleaseImage( &l_I2maskTemp2_8u);
		cvReleaseImage( &l_I2hsvForegroundFindMarkerSaturation1_8u);
		cvReleaseImage( &l_I2hsvForegroundFinal1_8u);
		cvReleaseImage( &l_I2maskWithoutBackground1_8u );
		cvReleaseImage( &l_I2maskMarker1ColorSeparation1_8u );
		cvReleaseImage( &l_I2maskMarker2ColorSeparation1_8u );
		cvReleaseImage( &l_I2maskMarker1ColorSeparationWithoutBackground1_8u );
		cvReleaseImage( &l_I2maskMarker2ColorSeparationWithoutBackground1_8u );
		cvReleaseImage( &l_I2maskMarker1ColorSeparationWithoutBackgroundClosed1_8u );
		cvReleaseImage( &l_I2maskMarker2ColorSeparationWithoutBackgroundClosed1_8u );
		cvReleaseImage( &l_I2maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u );
		cvReleaseImage( &l_I2maskMarker2ColorSeparationWithoutBackgroundClosedSegment1_8u );
		cvReleaseImage( &l_I2maskAroundMarker1Area1_8u );
		cvReleaseImage( &l_I2maskAroundMarker2Area1_8u );

		//32Float, 1-channel images
		cvReleaseImage( &l_I2undistortionMainLoopSizeMapX1_32f);
		cvReleaseImage( &l_I2undistortionMainLoopSizeMapY1_32f);

	//end - CAMERA 2


	//SHARED

		//3channel 8u

		//1channel 8u
		cvReleaseImage( &l_ImaskFindMarkerColor1_8u);
		cvReleaseImage( &l_ImaskFindMarkerSaturation1_8u);
		cvReleaseImage( &l_ImaskFindMarkerValue1_8u);

	//end - shared

}


void mmMouseBox(int event, int x, int y, int flags, void* param) {

    //bool _bDrawingBox=false; CvRect _Box;
    IplImage* _Imask = (IplImage*) param;

    switch( event ) {
        case CV_EVENT_MOUSEMOVE: {
            if( l_bDrawingBox ) {
                l_rectMaskFindMarkerColorSelection.width = x-l_rectMaskFindMarkerColorSelection.x;
                l_rectMaskFindMarkerColorSelection.height = y-l_rectMaskFindMarkerColorSelection.y;
            }
        }
        break;

        case CV_EVENT_LBUTTONDOWN: {
            l_bDrawingBox = true;
            l_bIfDrewBox = false;
            l_bIfFindMarkerStarted = false;
            l_rectMaskFindMarkerColorSelection = cvRect(x, y, 0, 0);
        }
        break;

        case CV_EVENT_LBUTTONUP: {
            l_bDrawingBox = false;
            l_bIfDrewBox = true;
            if(l_rectMaskFindMarkerColorSelection.width<0) {
                l_rectMaskFindMarkerColorSelection.x+=+l_rectMaskFindMarkerColorSelection.width;
                l_rectMaskFindMarkerColorSelection.width *=-1;
            }
            if(l_rectMaskFindMarkerColorSelection.height<0) {
                l_rectMaskFindMarkerColorSelection.y+=l_rectMaskFindMarkerColorSelection.height;
                l_rectMaskFindMarkerColorSelection.height*=-1;
            }
            //drawBox(_Imask, l_rectMaskFindMarkerColorSelection);
        }
        break;
    }
    cvReleaseImage(&_Imask);
};



int mmStartCalibration(){

char _cFileName[200];

int _iChessboardPointsCurrentNumber = g_iChessboardCornersNumberX * g_iChessboardCornersNumberY;
int _iChessboardPointsAllNumber = 0;
int _iChessboardFullFound1and2 = 0;

std::vector<CvPoint3D32f> _vecChessboardPoints;
std::vector<CvPoint2D32f> _vecChessboardPointsImages1;
std::vector<CvPoint2D32f> _vecChessboardPointsImages2;
std::vector<int> _vecNumberPoints;
std::vector<CvPoint2D32f> _vecChessboardPointsTemp1(_iChessboardPointsCurrentNumber);
std::vector<CvPoint2D32f> _vecChessboardPointsTemp2(_iChessboardPointsCurrentNumber);
std::vector<uchar> _vecChessboardFullFound1;
std::vector<uchar> _vecChessboardFullFound2;

//// vectors and arrays used in calibration process
	double M1[3][3], M2[3][3], D1[5], D2[5];
	double R[3][3], Rhalf[3][3], T[3], E[3][3], F[3][3];
	double R3x1[3], R3x1Half[3];
	CvMat* _M1 = cvCreateMat(3, 3, CV_64F);
	CvMat* _M2 = cvCreateMat(3, 3, CV_64F);
	CvMat* _D1 = cvCreateMat(1, 5, CV_64F);
	CvMat* _D2 = cvCreateMat(1, 5, CV_64F);
	CvMat* _R = cvCreateMat(3, 3, CV_64F);
	CvMat* _Rhalf = cvCreateMat(3, 3, CV_64F);
	CvMat* _T = cvCreateMat(3, 1, CV_64F);
	CvMat* _E = cvCreateMat(3, 3, CV_64F);
	CvMat* _F = cvCreateMat(3, 3, CV_64F);
	CvMat* _R3x1 = cvCreateMat(3, 1, CV_64F);
	CvMat* _R3x1Half = cvCreateMat(3, 1, CV_64F);
	_M1->data.ptr = (uchar*)M1;
	_M2->data.ptr = (uchar*)M2;
	_D1->data.ptr = (uchar*)D1;
	_D2->data.ptr = (uchar*)D2;
	_R->data.ptr = (uchar*)R;
	_Rhalf->data.ptr = (uchar*)Rhalf;
	_T->data.ptr = (uchar*)T;
	_E->data.ptr = (uchar*)E;
	_F->data.ptr = (uchar*)F;
	_R3x1->data.ptr = (uchar*)R3x1;
	_R3x1Half->data.ptr = (uchar*)R3x1Half;
//end - vectors and arrays used in calibration process



IplImage *l_I1temp1_8u = cvCreateImage( cvSize(g_iCamerasCalibrationResolutionWidth,g_iCamerasCalibrationResolutionHeight), IPL_DEPTH_8U, 1 );
IplImage *l_I2temp1_8u = cvCreateImage( cvSize(g_iCamerasCalibrationResolutionWidth,g_iCamerasCalibrationResolutionHeight), IPL_DEPTH_8U, 1 );

////setup CAMERAS
	CvCapture* _Camera1;
	CvCapture* _Camera2;
	_Camera1 = cvCaptureFromCAM(CV_CAP_DSHOW + 0);	//getting first two capture devices from connected to computer
	_Camera2 = cvCaptureFromCAM(CV_CAP_DSHOW + 1);	//

	//Setting up capture setup for calibration
		cvSetCaptureProperty(_Camera1 ,CV_CAP_PROP_FRAME_WIDTH,g_iCamerasCalibrationResolutionWidth);
		cvSetCaptureProperty(_Camera1 ,CV_CAP_PROP_FRAME_HEIGHT,g_iCamerasCalibrationResolutionHeight);

		cvSetCaptureProperty(_Camera2 ,CV_CAP_PROP_FRAME_WIDTH,g_iCamerasCalibrationResolutionWidth);
		cvSetCaptureProperty(_Camera2 ,CV_CAP_PROP_FRAME_HEIGHT,g_iCamerasCalibrationResolutionHeight);
	//end - Setting up capture setup for calibration

	if( !(_Camera1) || !(_Camera2)  ){

		sprintf(g_cMessages, "Could not initialize capturing - check if there are two cameras connected to USB ports\n");
		System::String^ _sysstringMessages = gcnew String(g_cMessages);
		MessageBox::Show(_sysstringMessages);
		return -1;
	}

	cvNamedWindow("Camera 1 Calibration View", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Camera 2 Calibration View", CV_WINDOW_AUTOSIZE);
//end - setup CAMERAS


//calibrationType - NEW CAMEREA SETTLEMENT   or   USE OLD, SAVED CONFIGURATION
if (g_iCalibrationType){


	////finding chessboards corners in Left and Right images
	for(int i=0;; i++){
		int _iResult1 = 0, _iResult2 = 0;	//if all the corners have been found
		int _iCount1 = 0, _iCount2 = 0;	//how many corners were found

		////parallel grabing frames from cameras
			#pragma omp parallel sections default(shared) private(_cFileName, _iChessboardPointsAllNumber, _iChessboardPointsCurrentNumber) shared(_Camera1, _Camera2, l_I1, l_I2, g_liFrameCount, _vecChessboardPointsTemp1, _vecChessboardPointsTemp2, _iResult1, _iCount1, _iResult2, _iCount2)
			{
				//taking frame from camera to image I
				#pragma omp section  
				{
					cvGrabFrame(_Camera1);
					l_I1 = cvRetrieveFrame(_Camera1);

					if (i%2 == 0)
					_iResult1 = cvFindChessboardCorners( l_I1, cvSize(g_iChessboardCornersNumberX, g_iChessboardCornersNumberY),
														&_vecChessboardPointsTemp1[0], &_iCount1,
														CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);

				}

				//taking frame from camera to image I
				#pragma omp section  
				{
					cvGrabFrame(_Camera2);
					l_I2 = cvRetrieveFrame(_Camera2);

					if (i%2 == 0)
					_iResult2 = cvFindChessboardCorners( l_I2, cvSize(g_iChessboardCornersNumberX, g_iChessboardCornersNumberY),
														&_vecChessboardPointsTemp2[0], &_iCount2,
														CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);
				}

			}//end - parallel grabing frames from cameras


			cvDrawChessboardCorners( l_I1, cvSize(g_iChessboardCornersNumberX, g_iChessboardCornersNumberY),
												&_vecChessboardPointsTemp1[0], _iCount1, _iResult1 );
			cvDrawChessboardCorners( l_I2, cvSize(g_iChessboardCornersNumberX, g_iChessboardCornersNumberY),
												&_vecChessboardPointsTemp2[0], _iCount2, _iResult2 );



			if (i%2 == 0)
			// corners subpixel accuracy & filling VECTORS only if all corners (whole chessboard) were found in both camera - LEFT & RIGHT
			if ( _iResult1 && _iResult2 ){
				////parallel subpixel accuracy & filling VECTORS
				#pragma omp parallel sections default(shared) private(_cFileName, _iChessboardPointsAllNumber, _iChessboardPointsCurrentNumber) shared(_Camera1, _Camera2, l_I1, l_I2, g_liFrameCount, _vecChessboardPointsTemp1, _vecChessboardPointsTemp2, _iResult1, _iCount1, _iResult2, _iCount2)
				{
					//camera 1
					#pragma omp section  
					{
						//getting ready _vecChessboardPointsImages1 for next pack of points
						_iChessboardPointsCurrentNumber = g_iChessboardCornersNumberX * g_iChessboardCornersNumberY;
						_iChessboardPointsAllNumber = _vecChessboardPointsImages1.size();
						_vecChessboardPointsImages1.resize(_iChessboardPointsAllNumber + _iChessboardPointsCurrentNumber, cvPoint2D32f(0,0));

						cvCvtColor( l_I1, l_I1temp1_8u, CV_BGR2GRAY );
						cvFindCornerSubPix( l_I1temp1_8u, &_vecChessboardPointsTemp1[0], _iCount1,
											cvSize(11, 11), cvSize(-1,-1),
											cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS,
											30, 0.01) );

						//placing in vector next points from next grabed frame
						copy( _vecChessboardPointsTemp1.begin(), _vecChessboardPointsTemp1.end(), _vecChessboardPointsImages1.begin() + _iChessboardPointsAllNumber );

						_vecChessboardFullFound1.push_back((uchar)_iResult1);
					}

					//camera 2
					#pragma omp section  
					{
						//getting ready _vecChessboardPointsImages1 for next pack of points
						_iChessboardPointsCurrentNumber = g_iChessboardCornersNumberX * g_iChessboardCornersNumberY;
						_iChessboardPointsAllNumber = _vecChessboardPointsImages2.size();
						_vecChessboardPointsImages2.resize(_iChessboardPointsAllNumber + _iChessboardPointsCurrentNumber, cvPoint2D32f(0,0));

						cvCvtColor( l_I2, l_I2temp1_8u, CV_BGR2GRAY );
						cvFindCornerSubPix( l_I2temp1_8u, &_vecChessboardPointsTemp2[0], _iCount2,
											cvSize(11, 11), cvSize(-1,-1),
											cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS,
											30, 0.01) );

						//placing in vector next points from next grabed frame
						copy( _vecChessboardPointsTemp2.begin(), _vecChessboardPointsTemp2.end(), _vecChessboardPointsImages2.begin() + _iChessboardPointsAllNumber );

						_vecChessboardFullFound2.push_back((uchar)_iResult2);
					}

				}//end - parallel subpixel accuracy & filling VECTORS

			}//end - corners subpixel accuracy & filling VECTORS only if corners were found in both camera - LEFT & RIGHT




			//show computed corners
			cvShowImage( "Camera 1 Calibration View", l_I1 );
			cvShowImage( "Camera 2 Calibration View", l_I2 );


			if( cvWaitKey(5) == 27 ) //Allow ESC to quit
				break;

			if ( _vecChessboardFullFound2.size() >= g_iCalibrationActualProcessNumberOfFrames )
				break;

	}//end - finding chessboards corners in Left and Right images

	//destroy windows after	finding corners
	cvDestroyAllWindows();


	////getting lowest number frames of fully founded chessboard corners - NOW NOT NECESSARY
		if (_vecChessboardFullFound1 >= _vecChessboardFullFound2){
			_iChessboardFullFound1and2 = _vecChessboardFullFound2.size();
		}
		else{
			_iChessboardFullFound1and2 = _vecChessboardFullFound1.size();
		}

		_vecChessboardPoints.resize(_iChessboardFullFound1and2 * _iChessboardPointsCurrentNumber);
	//end - getting lowest number frames of fully founded chessboard corners

	////creating ChessboardPoints
		for(int i = 0; i < g_iChessboardCornersNumberY; i++ )
			for(int j = 0; j < g_iChessboardCornersNumberX; j++ )
				_vecChessboardPoints[i*g_iChessboardCornersNumberX + j] = cvPoint3D32f(i*g_dChessboardSquareSize, j*g_dChessboardSquareSize, 0);

		for(int i = 1; i < _iChessboardFullFound1and2; i++ )
			copy( _vecChessboardPoints.begin(), _vecChessboardPoints.begin() + _iChessboardPointsCurrentNumber, _vecChessboardPoints.begin() + i*_iChessboardPointsCurrentNumber );
	//end - creating ChessboardPoints

	////creating inputs for stereoCalibrate()
		_vecNumberPoints.resize(_iChessboardFullFound1and2, _iChessboardPointsCurrentNumber);
		_iChessboardPointsAllNumber = _iChessboardFullFound1and2 * _iChessboardPointsCurrentNumber;

		CvMat _matChessboardPoints = cvMat(1, _iChessboardFullFound1and2 * _iChessboardPointsCurrentNumber, CV_32FC3, &_vecChessboardPoints[0] );
		CvMat _matChessboardPointsImages1 = cvMat(1, _iChessboardFullFound1and2 * _iChessboardPointsCurrentNumber, CV_32FC2, &_vecChessboardPointsImages1[0] );
		CvMat _matChessboardPointsImages2 = cvMat(1, _iChessboardFullFound1and2 * _iChessboardPointsCurrentNumber, CV_32FC2, &_vecChessboardPointsImages2[0] );
		CvMat _matNumberPoints = cvMat(1, _vecNumberPoints.size(), CV_32S, &_vecNumberPoints[0] );
		cvSetIdentity(_M1);
		cvSetIdentity(_M2);
		cvZero(_D1);
		cvZero(_D2);
	//end - creating inputs for stereoCalibrate()



	////reading computed cameras intrinsic & distorion parameters from calibration from file
		CvFileStorage* _fs_calibIntrinsicDistFile = cvOpenFileStorage(	"_calibIntrinsicDist.xml",
																	0,
																	CV_STORAGE_READ
																	);

		_M1 = (CvMat*) cvReadByName(_fs_calibIntrinsicDistFile, 0, "_M1");
		_M2 = (CvMat*) cvReadByName(_fs_calibIntrinsicDistFile, 0, "_M2");
		_D1 = (CvMat*) cvReadByName(_fs_calibIntrinsicDistFile, 0, "_D1");
		_D2 = (CvMat*) cvReadByName(_fs_calibIntrinsicDistFile, 0, "_D2");

		cvReleaseFileStorage( &_fs_calibIntrinsicDistFile );
	//end - reading computed cameras intrinsic & distorion parameters from calibration from file



	//Calibrate both CAMERAS in stereo
	cvStereoCalibrate( &_matChessboardPoints, &_matChessboardPointsImages1,
						&_matChessboardPointsImages2, &_matNumberPoints,
						_M1, _D1, _M2, _D2,
						cvSize(l_I1->width,l_I1->height), _R, _T, _E, _F,
						cvTermCriteria(CV_TERMCRIT_ITER+
						CV_TERMCRIT_EPS, 100, 1e-5),
						CV_CALIB_USE_INTRINSIC_GUESS +
						CV_CALIB_FIX_PRINCIPAL_POINT +
						CV_CALIB_FIX_ASPECT_RATIO +
						CV_CALIB_ZERO_TANGENT_DIST +
						CV_CALIB_SAME_FOCAL_LENGTH + CV_CALIB_FIX_K3 + CV_CALIB_FIX_K2 + CV_CALIB_FIX_K1 );


	////making parallel translation vector of two cameras (X & Z diretion only) and X axis of origin
		double _dVectorTranslationLenghtInXZdirection = 0.0;
		_dVectorTranslationLenghtInXZdirection = mmVectorLenght( T[0], 0.0, T[2] );
		T[0] = _dVectorTranslationLenghtInXZdirection;
		T[2] = 0.0;
	//end - making parallel translation vector of two cameras (X & Z diretion only) and X axis of origin

	////writing computed cameras calibration to file
		CvFileStorage* _fsCalibrationCfgFile = cvOpenFileStorage(	"_calibrationCfg.xml",
																	0,
																	CV_STORAGE_WRITE
																	);

		cvWrite(_fsCalibrationCfgFile, "_M1", _M1);
		cvWrite(_fsCalibrationCfgFile, "_M2", _M2);
		cvWrite(_fsCalibrationCfgFile, "_D1", _D1);
		cvWrite(_fsCalibrationCfgFile, "_D2", _D2);
		cvWrite(_fsCalibrationCfgFile, "_R", _R);
		cvWrite(_fsCalibrationCfgFile, "_T", _T);
		cvWrite(_fsCalibrationCfgFile, "_E", _E);
		cvWrite(_fsCalibrationCfgFile, "_F", _F);

		cvReleaseFileStorage( &_fsCalibrationCfgFile );
	//end - writing computed cameras calibration to file



}//end - calibrationType - NEW CAMEREA SETTLEMENT
else{

	////reading computed cameras calibration from file
		CvFileStorage* _fsCalibrationCfgFile = cvOpenFileStorage(	"_calibrationCfg.xml",
																	0,
																	CV_STORAGE_READ
																	);

		_M1 = (CvMat*) cvReadByName(_fsCalibrationCfgFile, 0, "_M1");
		_M2 = (CvMat*) cvReadByName(_fsCalibrationCfgFile, 0, "_M2");
		_D1 = (CvMat*) cvReadByName(_fsCalibrationCfgFile, 0, "_D1");
		_D2 = (CvMat*) cvReadByName(_fsCalibrationCfgFile, 0, "_D2");
		_R = (CvMat*) cvReadByName(_fsCalibrationCfgFile, 0, "_R");
		_T = (CvMat*) cvReadByName(_fsCalibrationCfgFile, 0, "_T");
		_E = (CvMat*) cvReadByName(_fsCalibrationCfgFile, 0, "_E");
		_F = (CvMat*) cvReadByName(_fsCalibrationCfgFile, 0, "_F");

		cvReleaseFileStorage( &_fsCalibrationCfgFile );
	//end - reading computed cameras calibration from file

		l_I1 = cvRetrieveFrame(_Camera1);

}//end - calibrationType - USE OLD CONFIGURATION



////copying temp R & T & M1 & M2 matrices to their global equivalent
	for (int ii=0; ii<=2; ii++){
			g_matrixTranslationBetweenBothCameras[ii] = cvmGet(_T, 0, ii);// T[ii];
			g_matrixTranslationBetweenBothCamerasHalf[ii] = cvmGet(_T, 0, ii)/2.0;// T[ii]/2.0;
	}

	cvRodrigues2(_R, _R3x1, NULL);
	for (int ii=0; ii<=2; ii++)
		for (int jj=0; jj<=2; jj++){
			g_matrixRotationBetweenBothCameras[ii][jj] = cvmGet(_R, ii, jj);// R[ii][jj];
			g_matrixRotationBetweenBothCameras3x1Half[jj] = cvmGet(_R3x1, 0, jj)/2.0;// R3x1[jj]/2.0;

			cvmSet(_R3x1Half, 0, jj, cvmGet(_R3x1, 0, jj)/2.0);
		}

	cvRodrigues2(_R3x1Half, _Rhalf, NULL);
	for (int ii=0; ii<=2; ii++)
		for (int jj=0; jj<=2; jj++){
			g_matrixRotationBetweenBothCamerasHalfPlus[ii][jj] = cvmGet(_Rhalf, ii, jj);// R[ii][jj];

			cvmSet(_R3x1Half, 0, jj, cvmGet(_R3x1, 0, jj)/(-2.0));
		}


	cvRodrigues2(_R3x1Half, _Rhalf, NULL);
	for (int ii=0; ii<=2; ii++)
		for (int jj=0; jj<=2; jj++){
			g_matrixRotationBetweenBothCamerasHalfMinus[ii][jj] = cvmGet(_Rhalf, ii, jj);// R[ii][jj];

			g_matrixCamera1Intristic[ii][jj] = cvmGet(_M1, ii, jj);// M1[ii][jj];
			g_matrixCamera2Intristic[ii][jj] = cvmGet(_M2, ii, jj);// M2[ii][jj];
		}
//end - copying temp R & T matrices to their global equivalent



////create global undistortion map for CAMERA1 & CAMERA2
	//first release old distortion maps for both camera if they were
	if (g_I1undistortMapX1_32f){
		cvReleaseImage(&g_I1undistortMapX1_32f);
		cvReleaseImage(&g_I1undistortMapY1_32f);
		cvReleaseImage(&g_I2undistortMapX1_32f);
		cvReleaseImage(&g_I2undistortMapY1_32f);
	}

	//create new distortion maps for both camera
	g_I1undistortMapX1_32f = cvCreateImage( cvGetSize(l_I1), IPL_DEPTH_32F, 1 );
	g_I1undistortMapY1_32f = cvCreateImage( cvGetSize(l_I1), IPL_DEPTH_32F, 1 );
	g_I2undistortMapX1_32f = cvCreateImage( cvGetSize(l_I1), IPL_DEPTH_32F, 1 );
	g_I2undistortMapY1_32f = cvCreateImage( cvGetSize(l_I1), IPL_DEPTH_32F, 1 );

	cvInitUndistortMap(_M1, _D1, g_I1undistortMapX1_32f, g_I1undistortMapY1_32f);
	cvInitUndistortMap(_M2, _D2, g_I2undistortMapX1_32f, g_I2undistortMapY1_32f);

//end - create global undistortion map for CAMERA1 & CAMERA2


//
//finish jobs
//
cvDestroyAllWindows();
cvReleaseCapture(&_Camera1);
cvReleaseCapture(&_Camera2);

}



int mmStartCalibrationCameraIntrinsicDistortion(){

char _cFileName[200];

System::String^ _sysstringMessages;

int _iChessboardPointsCurrentNumber = g_iChessboardCornersNumberX * g_iChessboardCornersNumberY;
int _iChessboardPointsAllNumber1 = 0;
int _iChessboardPointsAllNumber2 = 0;
int _iChessboardFullFound1and2 = 0;

std::vector<CvPoint3D32f> _vecChessboardPoints1;
std::vector<CvPoint3D32f> _vecChessboardPoints2;
std::vector<CvPoint2D32f> _vecChessboardPointsImages1;
std::vector<CvPoint2D32f> _vecChessboardPointsImages2;
std::vector<int> _vecNumberPoints1;
std::vector<int> _vecNumberPoints2;
std::vector<CvPoint2D32f> _vecChessboardPointsTemp1(_iChessboardPointsCurrentNumber);
std::vector<CvPoint2D32f> _vecChessboardPointsTemp2(_iChessboardPointsCurrentNumber);
std::vector<uchar> _vecChessboardFullFound1;
std::vector<uchar> _vecChessboardFullFound2;

// vectors and arrays used in calibration process
double M1[3][3], M2[3][3], D1[5], D2[5];
CvMat* _M1 = cvCreateMat(3, 3, CV_64F);
CvMat* _M2 = cvCreateMat(3, 3, CV_64F);
CvMat* _D1 = cvCreateMat(1, 5, CV_64F);
CvMat* _D2 = cvCreateMat(1, 5, CV_64F);
_M1->data.ptr = (uchar*)M1;
_M2->data.ptr = (uchar*)M2;
_D1->data.ptr = (uchar*)D1;
_D2->data.ptr = (uchar*)D2;


IplImage *l_I1temp1_8u = cvCreateImage( cvSize(g_iCamerasCalibrationResolutionWidth,g_iCamerasCalibrationResolutionHeight), IPL_DEPTH_8U, 1 );
IplImage *l_I2temp1_8u = cvCreateImage( cvSize(g_iCamerasCalibrationResolutionWidth,g_iCamerasCalibrationResolutionHeight), IPL_DEPTH_8U, 1 );

//setup CAMERAS
	CvCapture* _Camera1;
	CvCapture* _Camera2;
	_Camera1 = cvCaptureFromCAM(CV_CAP_DSHOW + 0);
	_Camera2 = cvCaptureFromCAM(CV_CAP_DSHOW + 1);

	//Setting up capture setup for calibration
		cvSetCaptureProperty(_Camera1 ,CV_CAP_PROP_FRAME_WIDTH,g_iCamerasCalibrationResolutionWidth);
		cvSetCaptureProperty(_Camera1 ,CV_CAP_PROP_FRAME_HEIGHT,g_iCamerasCalibrationResolutionHeight);

		cvSetCaptureProperty(_Camera2 ,CV_CAP_PROP_FRAME_WIDTH,g_iCamerasCalibrationResolutionWidth);
		cvSetCaptureProperty(_Camera2 ,CV_CAP_PROP_FRAME_HEIGHT,g_iCamerasCalibrationResolutionHeight);
	//end - Setting up capture setup for calibration

	if( (!_Camera1) || (!_Camera2) ){

		sprintf(g_cMessages, "Could not initialize capturing - check if there are two cameras connected to USB ports\n");
		_sysstringMessages = gcnew String(g_cMessages);
		MessageBox::Show(_sysstringMessages);

		return -1;
	}
//end - setup CAMERAS



	cvNamedWindow("Camera 1 Calibration View", CV_WINDOW_AUTOSIZE);

	////CAMERA 1 finding chessboards corners in Left and Right images
	for(int i=0;; i++){
		int _iResult1 = 0, _iResult2 = 0;	//if all the corners have been found
		int _iCount1 = 0, _iCount2 = 0;	//how many corners were found

			cvGrabFrame(_Camera1);
			l_I1 = cvRetrieveFrame(_Camera1);

			_iResult1 = cvFindChessboardCorners( l_I1, cvSize(g_iChessboardCornersNumberX, g_iChessboardCornersNumberY),
												&_vecChessboardPointsTemp1[0], &_iCount1,
												CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);


			////corners subpixel accuracy & filling VECTORS only if corners were found
			if (i%2 == 0)
			if ( _iResult1 ){
				//getting ready _vecChessboardPointsImages1 for next pack of points
				_iChessboardPointsCurrentNumber = g_iChessboardCornersNumberX * g_iChessboardCornersNumberY;
				_iChessboardPointsAllNumber1 = _vecChessboardPointsImages1.size();
				_vecChessboardPointsImages1.resize(_iChessboardPointsAllNumber1 + _iChessboardPointsCurrentNumber, cvPoint2D32f(0,0));

				cvCvtColor( l_I1, l_I1temp1_8u, CV_BGR2GRAY );
				cvFindCornerSubPix( l_I1temp1_8u, &_vecChessboardPointsTemp1[0], _iCount1,
									cvSize(11, 11), cvSize(-1,-1),
									cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS,
									30, 0.01) );

				//placing in vector next points from next grabed frame
				copy( _vecChessboardPointsTemp1.begin(), _vecChessboardPointsTemp1.end(), _vecChessboardPointsImages1.begin() + _iChessboardPointsAllNumber1 );
				_vecChessboardFullFound1.push_back((uchar)_iResult1);

			}//end - corners subpixel accuracy & filling VECTORS only if corners were found


			cvDrawChessboardCorners( l_I1, cvSize(g_iChessboardCornersNumberX, g_iChessboardCornersNumberY),
												&_vecChessboardPointsTemp1[0], _iCount1, _iResult1 );

			//show computed corners
			cvShowImage( "Camera 1 Calibration View", l_I1 );


			if( cvWaitKey(5) == 27 ) //Allow ESC to quit
				break;

			if ( _vecChessboardFullFound1.size() >= g_iCalibrationActualProcessNumberOfFrames )
				break;

	}//end - CAMERA 1 finding chessboards corners in Left and Right images
	cvDestroyWindow("Camera 1 Calibration View");



	cvNamedWindow("Camera 2 Calibration View", CV_WINDOW_AUTOSIZE);

	////CAMERA 2 finding chessboards corners in Left and Right images
	for(int i=0;; i++){
		int _iResult1 = 0, _iResult2 = 0;	//if all the corners have been found
		int _iCount1 = 0, _iCount2 = 0;	//how many corners were found

			cvGrabFrame(_Camera2);
			l_I2 = cvRetrieveFrame(_Camera2);

			_iResult2 = cvFindChessboardCorners( l_I2, cvSize(g_iChessboardCornersNumberX, g_iChessboardCornersNumberY),
												&_vecChessboardPointsTemp2[0], &_iCount2,
												CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);


			////corners subpixel accuracy & filling VECTORS only if corners were found
			if (i%2 == 0)
			if ( _iResult2 ){
				//getting ready _vecChessboardPointsImages2 for next pack of points
				_iChessboardPointsCurrentNumber = g_iChessboardCornersNumberX * g_iChessboardCornersNumberY;
				_iChessboardPointsAllNumber2 = _vecChessboardPointsImages2.size();
				_vecChessboardPointsImages2.resize(_iChessboardPointsAllNumber2 + _iChessboardPointsCurrentNumber, cvPoint2D32f(0,0));

				cvCvtColor( l_I2, l_I2temp1_8u, CV_BGR2GRAY );
				cvFindCornerSubPix( l_I2temp1_8u, &_vecChessboardPointsTemp2[0], _iCount2,
									cvSize(11, 11), cvSize(-1,-1),
									cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS,
									30, 0.01) );

				//placing in vector next points from next grabed frame
				copy( _vecChessboardPointsTemp2.begin(), _vecChessboardPointsTemp2.end(), _vecChessboardPointsImages2.begin() + _iChessboardPointsAllNumber2 );

				_vecChessboardFullFound2.push_back((uchar)_iResult2);

			}//end - corners subpixel accuracy & filling VECTORS only if corners were found


			cvDrawChessboardCorners( l_I2, cvSize(g_iChessboardCornersNumberX, g_iChessboardCornersNumberY),
												&_vecChessboardPointsTemp2[0], _iCount2, _iResult2 );

			//show computed corners
			cvShowImage( "Camera 2 Calibration View", l_I2 );


			if( cvWaitKey(5) == 27 ) //Allow ESC to quit
				break;

			if ( _vecChessboardFullFound2.size() >= g_iCalibrationActualProcessNumberOfFrames )
				break;

	}//end - CAMERA 2 finding chessboards corners in Left and Right images
	cvDestroyWindow("Camera 2 Calibration View");

	//destroy windows after	finding corners
	cvDestroyAllWindows();


	
	////creating inputs for calibrateCamera2()

		////CAMERA 1 creating ChessboardPoints
			_vecChessboardPoints1.resize(_vecChessboardFullFound1.size() * _iChessboardPointsCurrentNumber);

			for(int i = 0; i < g_iChessboardCornersNumberY; i++ )
				for(int j = 0; j < g_iChessboardCornersNumberX; j++ )
					_vecChessboardPoints1[i*g_iChessboardCornersNumberX + j] = cvPoint3D32f(i*g_dChessboardSquareSize, j*g_dChessboardSquareSize, 0);

			for(int i = 1; i < _vecChessboardFullFound1.size(); i++ )
				copy( _vecChessboardPoints1.begin(), _vecChessboardPoints1.begin() + _iChessboardPointsCurrentNumber, _vecChessboardPoints1.begin() + i*_iChessboardPointsCurrentNumber );
		//end - CAMERA 1 creating ChessboardPoints

		////CAMERA 2 creating ChessboardPoints
			_vecChessboardPoints2.resize(_vecChessboardFullFound2.size() * _iChessboardPointsCurrentNumber);

			for(int i = 0; i < g_iChessboardCornersNumberY; i++ )
				for(int j = 0; j < g_iChessboardCornersNumberX; j++ )
					_vecChessboardPoints2[i*g_iChessboardCornersNumberX + j] = cvPoint3D32f(i*g_dChessboardSquareSize, j*g_dChessboardSquareSize, 0);

			for(int i = 1; i < _vecChessboardFullFound2.size(); i++ )
				copy( _vecChessboardPoints2.begin(), _vecChessboardPoints2.begin() + _iChessboardPointsCurrentNumber, _vecChessboardPoints2.begin() + i*_iChessboardPointsCurrentNumber );
		//end - CAMERA 2 creating ChessboardPoints

		
		_vecNumberPoints1.resize(_vecChessboardFullFound1.size(), _iChessboardPointsCurrentNumber);
		_vecNumberPoints2.resize(_vecChessboardFullFound2.size(), _iChessboardPointsCurrentNumber);
		_iChessboardPointsAllNumber1 = _vecChessboardFullFound1.size() * _iChessboardPointsCurrentNumber;
		_iChessboardPointsAllNumber2 = _vecChessboardFullFound2.size() * _iChessboardPointsCurrentNumber;

		CvMat _matChessboardPoints1 = cvMat(1, _vecChessboardFullFound1.size()* _iChessboardPointsCurrentNumber, CV_32FC3, &_vecChessboardPoints1[0] );
		CvMat _matChessboardPoints2 = cvMat(1, _vecChessboardFullFound2.size()* _iChessboardPointsCurrentNumber, CV_32FC3, &_vecChessboardPoints2[0] );
		CvMat _matChessboardPointsImages1 = cvMat(1, _vecChessboardFullFound1.size()* _iChessboardPointsCurrentNumber, CV_32FC2, &_vecChessboardPointsImages1[0] );
		CvMat _matChessboardPointsImages2 = cvMat(1, _vecChessboardFullFound2.size()* _iChessboardPointsCurrentNumber, CV_32FC2, &_vecChessboardPointsImages2[0] );
		CvMat _matNumberPoints1 = cvMat(1, _vecNumberPoints1.size(), CV_32S, &_vecNumberPoints1[0] );
		CvMat _matNumberPoints2 = cvMat(1, _vecNumberPoints2.size(), CV_32S, &_vecNumberPoints2[0] );
		cvSetIdentity(_M1);
		cvSetIdentity(_M2);
		cvZero(_D1);
		cvZero(_D2);
	//end - creating inputs for calibrateCamera2()




	//CAMERA 1 Calibrate
	cvCalibrateCamera2( &_matChessboardPoints1, &_matChessboardPointsImages1,
						&_matNumberPoints1,
						cvSize(l_I1->width,l_I1->height), 
						_M1, _D1,
						NULL, NULL,
						CV_CALIB_ZERO_TANGENT_DIST);

	//CAMERA 2 Calibrate
	cvCalibrateCamera2( &_matChessboardPoints2, &_matChessboardPointsImages2,
						&_matNumberPoints2,
						cvSize(l_I1->width,l_I1->height), 
						_M2, _D2,
						NULL, NULL,
						CV_CALIB_ZERO_TANGENT_DIST);


	////writing computed cameras calibration to file
		CvFileStorage* _fs_calibIntrinsicDistFile = cvOpenFileStorage(	"_calibIntrinsicDist.xml",
																	0,
																	CV_STORAGE_WRITE
																	);

		cvWrite(_fs_calibIntrinsicDistFile, "_M1", _M1);
		cvWrite(_fs_calibIntrinsicDistFile, "_M2", _M2);
		cvWrite(_fs_calibIntrinsicDistFile, "_D1", _D1);
		cvWrite(_fs_calibIntrinsicDistFile, "_D2", _D2);

		cvReleaseFileStorage( &_fs_calibIntrinsicDistFile );
	//end - writing computed cameras calibration to file




//finish jobs
	cvDestroyAllWindows();
	cvReleaseCapture(&_Camera1);
	cvReleaseCapture(&_Camera2);

}







int mmStartMain() {


	SYSTEMTIME _systemtime;	//for counting seconds of time in positionig drums
	double _dTimeSecTemp;

	bool _bIfDrumPositioningStartingPrepare = true;
	bool _bIfDrumPositioned = false;
	bool _bIfDrumPositioningStarted = false;
	bool _bIfStartCountingTime = false;
	
	mmDrum _drumTemp;
	int _iDrumPositioningFrameToAvgCount = 0;
	int _iDrumsLeft = 0;
	char _cKindOfAction[100] = "";

	char _cFileName[200];

	System::String^ _sysstringMessages;

    int _iTimeDiff = 1, _iFpsTemp = 1, _iFps = 20;	
	int _i1,_i2;

	bool _bIfMarkerColorSelected = false;
	int _iWhichMarkerColorSelecting = 1;	// '0'-stop selecting; '1'-marker1; '2'-marker2

	//for contour size computing
	double _dContourSizeTemp1;
	double _dContourSizeTemp2;
	double _dContourMaxSize1_tab[4];
	double _dContourMaxSize2_tab[4];
	CvSeq *_contourContourMaxSize1_tab[4];
	CvSeq *_contourContourMaxSize2_tab[4];
	_contourContourMaxSize1_tab[0] = NULL;
	_contourContourMaxSize1_tab[1] = NULL;
	_contourContourMaxSize1_tab[2] = NULL;
	_contourContourMaxSize1_tab[3] = NULL;
	_contourContourMaxSize2_tab[0] = NULL;
	_contourContourMaxSize2_tab[1] = NULL;
	_contourContourMaxSize2_tab[2] = NULL;
	_contourContourMaxSize2_tab[3] = NULL;

	CvMoments _momentsContoursMaxSize1;
	CvMoments _momentsContoursMaxSize2;
	std::vector<CvPoint> _pointMarker1ComtourMaxSize1_vec;
	std::vector<CvPoint> _pointMarker1ComtourMaxSize2_vec;
	std::vector<CvPoint> _pointMarker2ComtourMaxSize1_vec;
	std::vector<CvPoint> _pointMarker2ComtourMaxSize2_vec;
	//4 time push_bac to make place for 4 points
	_pointMarker1ComtourMaxSize1_vec.push_back(cvPoint(0,0));_pointMarker1ComtourMaxSize1_vec.push_back(cvPoint(0,0));_pointMarker1ComtourMaxSize1_vec.push_back(cvPoint(0,0));_pointMarker1ComtourMaxSize1_vec.push_back(cvPoint(0,0));
	_pointMarker1ComtourMaxSize2_vec.push_back(cvPoint(0,0));_pointMarker1ComtourMaxSize2_vec.push_back(cvPoint(0,0));_pointMarker1ComtourMaxSize2_vec.push_back(cvPoint(0,0));_pointMarker1ComtourMaxSize2_vec.push_back(cvPoint(0,0));
	_pointMarker2ComtourMaxSize1_vec.push_back(cvPoint(0,0));_pointMarker2ComtourMaxSize1_vec.push_back(cvPoint(0,0));_pointMarker2ComtourMaxSize1_vec.push_back(cvPoint(0,0));_pointMarker2ComtourMaxSize1_vec.push_back(cvPoint(0,0));
	_pointMarker2ComtourMaxSize2_vec.push_back(cvPoint(0,0));_pointMarker2ComtourMaxSize2_vec.push_back(cvPoint(0,0));_pointMarker2ComtourMaxSize2_vec.push_back(cvPoint(0,0));_pointMarker2ComtourMaxSize2_vec.push_back(cvPoint(0,0));


	////allocating memory for codebook method model
		CvBGCodeBookModel *_backgroundModelCamera1;
		_backgroundModelCamera1 = cvCreateBGCodeBookModel();

		CvBGCodeBookModel *_backgroundModelCamera2;
		_backgroundModelCamera2 = cvCreateBGCodeBookModel();
	//end - allocating memory for codebook method model

	IplConvKernel* _seStructElementIntensity = cvCreateStructuringElementEx( 3, 3, 0, 0, CV_SHAPE_ELLIPSE, NULL );

	//for connected component function
	CvSeq* _seqI1ConnectedForegroundFindMarker1Color = NULL;
	CvSeq* _seqI2ConnectedForegroundFindMarker1Color = NULL;
	CvSeq* _seqI1ConnectedForegroundFindMarker2Color = NULL;
	CvSeq* _seqI2ConnectedForegroundFindMarker2Color = NULL;
	CvMemStorage* _msI1ConnectedForegroundFindMarker1Color = cvCreateMemStorage(0);
	CvMemStorage* _msI2ConnectedForegroundFindMarker1Color = cvCreateMemStorage(0);
	CvMemStorage* _msI1ConnectedForegroundFindMarker2Color = cvCreateMemStorage(0);
	CvMemStorage* _msI2ConnectedForegroundFindMarker2Color = cvCreateMemStorage(0);


    CvCapture* _Camera1;
	CvCapture* _Camera2;
	_Camera1 = cvCaptureFromCAM(CV_CAP_DSHOW + 0);
	_Camera2 = cvCaptureFromCAM(CV_CAP_DSHOW + 1);

	//Setting up capture setup
		cvSetCaptureProperty(_Camera1 ,CV_CAP_PROP_FRAME_WIDTH,g_iCamerasMainLoopResolutionWidth);
		cvSetCaptureProperty(_Camera1 ,CV_CAP_PROP_FRAME_HEIGHT,g_iCamerasMainLoopResolutionHeight);

		cvSetCaptureProperty(_Camera2 ,CV_CAP_PROP_FRAME_WIDTH,g_iCamerasMainLoopResolutionWidth);
		cvSetCaptureProperty(_Camera2 ,CV_CAP_PROP_FRAME_HEIGHT,g_iCamerasMainLoopResolutionHeight);
	//end - Setting up capture setup


	////Adjusting calibrationUndistortionMap size to undistortion map size used in main loop
		if (g_I1undistortMapX1_32f && g_I1undistortMapY1_32f && g_I1undistortMapY1_32f && g_I1undistortMapY1_32f){

			l_I1undistortionMainLoopSizeMapX1_32f = cvCreateImage( cvSize(g_iCamerasMainLoopResolutionWidth,g_iCamerasMainLoopResolutionHeight), IPL_DEPTH_32F, 1 );
			l_I1undistortionMainLoopSizeMapY1_32f = cvCreateImage( cvSize(g_iCamerasMainLoopResolutionWidth,g_iCamerasMainLoopResolutionHeight), IPL_DEPTH_32F, 1 );
			cvZero( l_I1undistortionMainLoopSizeMapX1_32f );
			cvZero( l_I1undistortionMainLoopSizeMapY1_32f );
			l_I2undistortionMainLoopSizeMapX1_32f = cvCreateImage( cvSize(g_iCamerasMainLoopResolutionWidth,g_iCamerasMainLoopResolutionHeight), IPL_DEPTH_32F, 1 );
			l_I2undistortionMainLoopSizeMapY1_32f = cvCreateImage( cvSize(g_iCamerasMainLoopResolutionWidth,g_iCamerasMainLoopResolutionHeight), IPL_DEPTH_32F, 1 );
			cvZero( l_I2undistortionMainLoopSizeMapX1_32f );
			cvZero( l_I2undistortionMainLoopSizeMapY1_32f );

			cvResize(g_I1undistortMapX1_32f, l_I1undistortionMainLoopSizeMapX1_32f, CV_INTER_AREA);
			cvResize(g_I1undistortMapY1_32f, l_I1undistortionMainLoopSizeMapY1_32f, CV_INTER_AREA);
			cvResize(g_I2undistortMapX1_32f, l_I2undistortionMainLoopSizeMapX1_32f, CV_INTER_AREA);
			cvResize(g_I2undistortMapY1_32f, l_I2undistortionMainLoopSizeMapY1_32f, CV_INTER_AREA);

			cvConvertScale(l_I1undistortionMainLoopSizeMapX1_32f, l_I1undistortionMainLoopSizeMapX1_32f, double(g_iCamerasMainLoopResolutionWidth)/double(g_iCamerasCalibrationResolutionWidth), 0);
			cvConvertScale(l_I1undistortionMainLoopSizeMapY1_32f, l_I1undistortionMainLoopSizeMapY1_32f, double(g_iCamerasMainLoopResolutionHeight)/double(g_iCamerasCalibrationResolutionHeight), 0);
			cvConvertScale(l_I2undistortionMainLoopSizeMapX1_32f, l_I2undistortionMainLoopSizeMapX1_32f, double(g_iCamerasMainLoopResolutionWidth)/double(g_iCamerasCalibrationResolutionWidth), 0);
			cvConvertScale(l_I2undistortionMainLoopSizeMapY1_32f, l_I2undistortionMainLoopSizeMapY1_32f, double(g_iCamerasMainLoopResolutionHeight)/double(g_iCamerasCalibrationResolutionHeight), 0);

		}
	//end - Adjusting calibrationUndistortionMap size to undistortion map size used in main loop


    if( (!_Camera1) || (!_Camera2)  )
    {
		sprintf(g_cMessages, "Could not initialize capturing - check if there are two cameras connected to USB ports\n");
		_sysstringMessages = gcnew String(g_cMessages);
		MessageBox::Show(_sysstringMessages);
        return -1;
    }
    
	cvNamedWindow("Camera 1 View", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Camera 2 View", CV_WINDOW_AUTOSIZE);

	cvNamedWindow("Camera 1 - Hue", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Camera 1 - Saturation", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Camera 1 - Value", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Camera 1 - Red", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Camera 1 - Green", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Camera 1 - Blue", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Camera 1 - view without background", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Camera 1 - view without background + color separation", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Camera 1 - view without background + color separation + closing", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Camera 1 - view without background + color separation + closing + segmentation", CV_WINDOW_AUTOSIZE);

    cvNamedWindow("Camera 2 - Hue", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Camera 2 - Saturation", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Camera 2 - Value", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Camera 2 - Red", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Camera 2 - Green", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Camera 2 - Blue", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Camera 2 - view without background", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Camera 2 - view without background + color separation", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Camera 2 - view without background + color separation + closing", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Camera 2 - view without background + color separation + closing + segmentation", CV_WINDOW_AUTOSIZE);
    

    cvSetMouseCallback( "Camera 1 View",
                        mmMouseBox,
                        (void*) (l_ImaskFindMarkerColor1_8u)
                      );


    ///////////////////////////////////////////////////////////////////////////
    ////////////////////////////end_of_initial_main_stuff//////////////////////
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////


    // main loop
    while(1){

        //starting time count for fps computing
        _iTimeDiff = GetTickCount();

        ////First time: init all images and learn backgrunds
        if (g_liFrameCount==0){
            cvGrabFrame(_Camera1);
            l_I1 = cvRetrieveFrame(_Camera1);
            mmAllocateImages(l_I1);

			//waiting for camera1 to be free
			cvWaitKey(50);

			sprintf(g_cMessages, "After click ok algorithm will be learning background.\nPlease:\n- LEAVE drum sticks away from cameras view area\n- be in your playing spot all over this time\n- make moves like you will be doing in playing drums ( simply move your arms;) )\n\nPLEASE DO THIS UNTIL NEXT MESSAGE APPEAR");
			_sysstringMessages = gcnew String(g_cMessages);
			MessageBox::Show(_sysstringMessages);
            
			#pragma omp parallel sections default(none) shared(_Camera1, _Camera2, _backgroundModelCamera1, _backgroundModelCamera2, l_I1undistortionMainLoopSizeMapX1_32f, l_I1undistortionMainLoopSizeMapY1_32f, l_I2undistortionMainLoopSizeMapX1_32f, l_I2undistortionMainLoopSizeMapY1_32f)
			{
				//learning background from camera 1
				#pragma omp section  
				{
					mmLearnBackgroundCodeBook(_Camera1, _backgroundModelCamera1, l_I1undistortionMainLoopSizeMapX1_32f, l_I1undistortionMainLoopSizeMapY1_32f);
				}

				//learning background from camera 2
				#pragma omp section  
				{
					mmLearnBackgroundCodeBook(_Camera2, _backgroundModelCamera2, l_I2undistortionMainLoopSizeMapX1_32f, l_I2undistortionMainLoopSizeMapY1_32f);
				}
			}

			sprintf(g_cMessages, "After click ok, switch to window 'Interface 3D' and fallow instructions that appear on top of it");
			_sysstringMessages = gcnew String(g_cMessages);
			MessageBox::Show(_sysstringMessages);

			sprintf (g_cDrumsPositioningText0,"Please use mouse to select where is first marker on camera 1 view");

        }//end - First time: init all images and learn backgrunds
		

		//synchro both cameras to grab frames in the same time
		#pragma omp barrier

		////parallel background subtracting
		#pragma omp parallel sections default(shared) private(_cFileName) shared(_Camera1, _Camera2, l_I1, l_I2, g_liFrameCount)
		{

			#pragma omp section  
			{
				////taking frame from camera1 to image I and undistorting it
					//if (!g_bIfTimeDelayNeedReset){
					//	g_iTimeDelay = GetTickCount();
					//}

					cvGrabFrame(_Camera1);
					l_I1 = cvRetrieveFrame(_Camera1);

					//undistorting images from earlier computed distortion maps
					if (g_I1undistortMapX1_32f && g_I1undistortMapY1_32f){

						l_I1temp = cvCloneImage(l_I1);
						cvRemap(l_I1temp, l_I1, l_I1undistortionMainLoopSizeMapX1_32f, l_I1undistortionMainLoopSizeMapY1_32f);

					}
				//end - taking frame from camera1 to image I and undistorting it

				//for forward using
				cvCvtColor(l_I1, l_I1hsv_8u, CV_BGR2HSV);
				cvSplit(l_I1hsv_8u, l_I1hsv1_8u, l_I1hsv2_8u, l_I1hsv3_8u, NULL);

				if (g_bUseBackgroundSubtraction){

					//for forward using
					cvCvtColor(l_I1, l_I1yuv_8u, CV_BGR2YCrCb);

					cvZero(l_I1maskCodeBook1_8u);
					cvBGCodeBookDiff( _backgroundModelCamera1, l_I1yuv_8u, l_I1maskCodeBook1_8u );
				
				}
				else{
					cvZero(l_I1maskCodeBook1_8u);
					cvSet(l_I1maskCodeBook1_8u, cvScalar(255));
				}


				//leaving only hue foreground in l_I1hsvForeground1_8u
				cvZero(l_I1hsvForeground1_8u);
				cvCopy(l_I1hsv1_8u, l_I1hsvForeground1_8u, l_I1maskCodeBook1_8u);

				if (g_bInterfaceShowViewWithoutBackground)
					cvCopy(l_I1maskCodeBook1_8u, l_I1maskWithoutBackground1_8u);

			}

			#pragma omp section  
			{
				////taking frame from camera1 to image I and undistorting it

					cvGrabFrame(_Camera2);
					l_I2 = cvRetrieveFrame(_Camera2);

					//undistorting images from earlier computed distortion maps
					if (g_I2undistortMapX1_32f && g_I2undistortMapY1_32f){

						l_I2temp = cvCloneImage(l_I2);
						cvRemap(l_I2temp, l_I2, l_I2undistortionMainLoopSizeMapX1_32f, l_I2undistortionMainLoopSizeMapY1_32f);

					}
				//end - taking frame from camera1 to image I and undistorting it

				//for forward using
				cvCvtColor(l_I2, l_I2hsv_8u, CV_BGR2HSV);
				cvSplit(l_I2hsv_8u, l_I2hsv1_8u, l_I2hsv2_8u, l_I2hsv3_8u, NULL);

				if (g_bUseBackgroundSubtraction){

					//for forward using
					cvCvtColor(l_I2, l_I2yuv_8u, CV_BGR2YCrCb);

					cvZero(l_I2maskCodeBook1_8u);
					cvBGCodeBookDiff( _backgroundModelCamera2, l_I2yuv_8u, l_I2maskCodeBook1_8u );
					
				}
				else{
					cvZero(l_I2maskCodeBook1_8u);
					cvSet(l_I2maskCodeBook1_8u, cvScalar(255));
				}

				//leaving only hue foreground in l_I2hsvForeground1_8u
				cvZero(l_I2hsvForeground1_8u);
				cvCopy(l_I2hsv1_8u, l_I2hsvForeground1_8u, l_I2maskCodeBook1_8u);

				if (g_bInterfaceShowViewWithoutBackground)
					cvCopy(l_I2maskCodeBook1_8u, l_I2maskWithoutBackground1_8u);

			}

		}//end - parallel background subtracting


		//computing user-marked color of a marker
        if (l_bDrawingBox){

			////computing marker color AVG and SDV
				cvZero(l_ImaskFindMarkerColor1_8u);
				drawBox(l_ImaskFindMarkerColor1_8u, l_rectMaskFindMarkerColorSelection, CV_FILLED);
				cvAvgSdv(l_I1hsv1_8u, &l_scMarkerColorAvgTemp, &l_scMarkerColorSdvTemp, l_ImaskFindMarkerColor1_8u);
				drawBox(l_I1, l_rectMaskFindMarkerColorSelection, 1);
			//end - computing marker color AVG and SDV

			////computing marker saturation AVG and SDV
				cvZero(l_ImaskFindMarkerSaturation1_8u);
				drawBox(l_ImaskFindMarkerSaturation1_8u, l_rectMaskFindMarkerColorSelection, CV_FILLED);
				cvAvgSdv(l_I1hsv2_8u, &l_scMarkerSaturationAvgTemp, &l_scMarkerSaturationSdvTemp, l_ImaskFindMarkerSaturation1_8u);
			//end - computing marker saturation AVG and SDV

			////computing marker value AVG and SDV
				cvZero(l_ImaskFindMarkerValue1_8u);
				drawBox(l_ImaskFindMarkerValue1_8u, l_rectMaskFindMarkerColorSelection, CV_FILLED);
				cvAvgSdv(l_I1hsv3_8u, &l_scMarkerValueAvgTemp, &l_scMarkerValueSdvTemp, l_ImaskFindMarkerValue1_8u);
			//end - computing marker value AVG and SDV
        }

		if (l_bIfDrewBox){
			//when marker first was taken change to take next marker color taking
			_iWhichMarkerColorSelecting++;
			l_bIfDrewBox = false;
		}

		if ( (_iWhichMarkerColorSelecting == 1) && (l_bDrawingBox) ){	//marker1 setting up color and satiration bounds

			////marker 1: refreshing average and standard deviation of color and saturation and value
				l_scMarker1ColorAvg.val[0] = l_scMarkerColorAvgTemp.val[0];
				l_scMarker1ColorSdv.val[0] = l_scMarkerColorSdvTemp.val[0];

				l_scMarker1SaturationAvg.val[0] = l_scMarkerSaturationAvgTemp.val[0];
				l_scMarker1SaturationSdv.val[0] = l_scMarkerSaturationSdvTemp.val[0];

				l_scMarker1ValueAvg.val[0] = l_scMarkerSaturationAvgTemp.val[0];
				l_scMarker1ValueSdv.val[0] = l_scMarkerSaturationSdvTemp.val[0];
			//end - marker 1: refreshing average and standard deviation of color and saturation and value

			sprintf (g_cDrumsPositioningText0,"Please use mouse to select where is second marker on camera 1 view");

		}

		if ( (_iWhichMarkerColorSelecting == 2) && (l_bDrawingBox) ){//marker1 setting up color and satiration bounds

			////marker 2: refreshing average and standard deviation of color and saturation and value
				l_scMarker2ColorAvg.val[0] = l_scMarkerColorAvgTemp.val[0];
				l_scMarker2ColorSdv.val[0] = l_scMarkerColorSdvTemp.val[0];

				l_scMarker2SaturationAvg.val[0] = l_scMarkerSaturationAvgTemp.val[0];
				l_scMarker2SaturationSdv.val[0] = l_scMarkerSaturationSdvTemp.val[0];

				l_scMarker2ValueAvg.val[0] = l_scMarkerSaturationAvgTemp.val[0];
				l_scMarker2ValueSdv.val[0] = l_scMarkerSaturationSdvTemp.val[0];
			//end - marker 2: refreshing average and standard deviation of color and saturation and value

			g_bIfMarkersColorMarkingIsDone = true;

			sprintf (g_cDrumsPositioningText0,"Please adjust processing parameters manually/auto or start drums setup");

		}


		////marker 1: refresing "cut-offs"
			////refreshing low and high cut-out color threshold
				l_scMarker1ColorAvgLow.val[0] = l_scMarker1ColorAvg.val[0];
				l_scMarker1ColorAvgHigh.val[0] = l_scMarker1ColorAvg.val[0];

				l_scMarker1ColorAvgLow.val[0] -= g_dColorFactorBounds *l_scMarker1ColorSdv.val[0];
				l_scMarker1ColorAvgHigh.val[0] += g_dColorFactorBounds *l_scMarker1ColorSdv.val[0];

				//to not be out of image values bands (0..255)
				if (l_scMarker1ColorAvgLow.val[0] <= 0)
					l_scMarker1ColorAvgLow.val[0] = 1;
				if (l_scMarker1ColorAvgHigh.val[0] >= 255)
					l_scMarker1ColorAvgHigh.val[0] = 255;
			//end - refreshing low and high cut-out color threshold


			////refreshing low and high cut-out saturation threshold
				l_scMarker1SaturationAvgLow.val[0] = l_scMarker1SaturationAvg.val[0];
				l_scMarker1SaturationAvgHigh.val[0] = l_scMarker1SaturationAvg.val[0];

				l_scMarker1SaturationAvgLow.val[0] -= g_dSaturationFactorBounds *l_scMarker1SaturationSdv.val[0];
				l_scMarker1SaturationAvgHigh.val[0] += g_dSaturationFactorBounds *l_scMarker1SaturationSdv.val[0];

				//to not be out of image values bands (0..255)
				if (l_scMarker1SaturationAvgLow.val[0] <= 0)
					l_scMarker1SaturationAvgLow.val[0] = 1;
				if (l_scMarker1SaturationAvgHigh.val[0] >= 255)
					l_scMarker1SaturationAvgHigh.val[0] = 255;
			//end - refreshing low and high cut-out color threshold			

			mmHSVtoRGB( l_scMarker1ColorAvg.val[0]/255.0*360.0, l_scMarker1SaturationAvg.val[0]/255.0, l_scMarker1ValueAvg.val[0]/255.0, 
						 g_matrixMarker1color[0], g_matrixMarker1color[1], g_matrixMarker1color[2] );
		//end - marker 1: refresing "cut-offs"
			
		////marker 2: refresing "cut-offs"
			////refreshing low and high cut-out color threshold
				l_scMarker2ColorAvgLow.val[0] = l_scMarker2ColorAvg.val[0];
				l_scMarker2ColorAvgHigh.val[0] = l_scMarker2ColorAvg.val[0];

				l_scMarker2ColorAvgLow.val[0] -= g_dColorFactorBounds *l_scMarker2ColorSdv.val[0];
				l_scMarker2ColorAvgHigh.val[0] += g_dColorFactorBounds *l_scMarker2ColorSdv.val[0];

				//to not be out of image values bands (0..255)
				if (l_scMarker2ColorAvgLow.val[0] <= 0)
					l_scMarker2ColorAvgLow.val[0] = 1;
				if (l_scMarker2ColorAvgHigh.val[0] >= 255)
					l_scMarker2ColorAvgHigh.val[0] = 255;
			//end - refreshing low and high cut-out color threshold


			////refreshing low and high cut-out saturation threshold
				l_scMarker2SaturationAvgLow.val[0] = l_scMarker2SaturationAvg.val[0];
				l_scMarker2SaturationAvgHigh.val[0] = l_scMarker2SaturationAvg.val[0];

				l_scMarker2SaturationAvgLow.val[0] -= g_dSaturationFactorBounds *l_scMarker2SaturationSdv.val[0];
				l_scMarker2SaturationAvgHigh.val[0] += g_dSaturationFactorBounds *l_scMarker2SaturationSdv.val[0];

				//to not be out of image values bands (0..255)
				if (l_scMarker2SaturationAvgLow.val[0] <= 0)
					l_scMarker2SaturationAvgLow.val[0] = 1;
				if (l_scMarker2SaturationAvgHigh.val[0] >= 255)
					l_scMarker2SaturationAvgHigh.val[0] = 255;
			//end - refreshing low and high cut-out color threshold

			mmHSVtoRGB( l_scMarkerColorAvgTemp.val[0]/255.0*360.0, l_scMarkerSaturationAvgTemp.val[0]/255.0, l_scMarker2ValueAvg.val[0]/255.0, 
						 g_matrixMarker2color[0], g_matrixMarker2color[1], g_matrixMarker2color[2] );
		//end - marker 2: refresing "cut-offs"



		////parallel markers colors searching & computing center of markers
		#pragma omp parallel sections default(shared) //private(l_scMarker1ColorAvgLow, l_scMarker1ColorAvgHigh)
		{
			#pragma omp section  
			{
				////marker1 taking connected components
					//leaving only choosed color only on the FOREGROUNG (by finding cirlce or marking rect) (color with some range only on the FOREGROUND)
					cvZero(l_I1hsvForegroundFindMarkerColor1_8u);
					cvZero(l_I1hsvForegroundFindMarkerSaturation1_8u);

					cvInRangeS(l_I1hsvForeground1_8u, l_scMarker1ColorAvgLow, l_scMarker1ColorAvgHigh, l_I1hsvForegroundFindMarkerColor1_8u);
					
					if (!g_bLookOnMarkerSaturation)
						cvSet(l_I1hsvForegroundFindMarkerSaturation1_8u, cvScalar(255));
					else
						cvInRangeS(l_I1hsv2_8u, l_scMarker1SaturationAvgLow, l_scMarker1SaturationAvgHigh, l_I1hsvForegroundFindMarkerSaturation1_8u);

					cvAnd(l_I1hsvForegroundFindMarkerColor1_8u, l_I1hsvForegroundFindMarkerSaturation1_8u, l_I1hsvForegroundFinal1_8u);

					if (g_bInterfaceShowViewColorSeparationWithoutBackground)
						cvCopy(l_I1hsvForegroundFinal1_8u, l_I1maskMarker1ColorSeparationWithoutBackground1_8u);

					cvErode(l_I1hsvForegroundFinal1_8u, l_I1maskTemp1_8u, _seStructElementIntensity, 0);
					cvDilate(l_I1maskTemp1_8u, l_I1maskTemp1_8u, _seStructElementIntensity, 3);

					if (g_bInterfaceShowViewColorSeparationWithoutBackgroundClosed)
						cvCopy(l_I1maskTemp1_8u, l_I1maskMarker1ColorSeparationWithoutBackgroundClosed1_8u);

					_seqI1ConnectedForegroundFindMarker1Color = cvSegmentFGMask(l_I1maskTemp1_8u, 0, 210, _msI1ConnectedForegroundFindMarker1Color );

					if (g_bInterfaceShowViewColorSeparationWithoutBackgroundClosedSegment){
						cvZero(l_I1maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u);
						cvDrawContours(l_I1maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u,_seqI1ConnectedForegroundFindMarker1Color ,cvScalarAll(255),cvScalarAll(255),100,CV_FILLED);
					}

				////end - marker1 taking connected components

				////marker 1
					////if there are some connectedComponents in final mask
					if (_seqI1ConnectedForegroundFindMarker1Color){
						//for every new frame there are new contours, so clearing old ones
						for (int i=0; i<=3; i++)
							_dContourMaxSize1_tab[i] = 0;
						
						_i1=0;
						//forming 4 biggest contours
						for(CvSeq* c=_seqI1ConnectedForegroundFindMarker1Color; c!=NULL; c=c->h_next) {
							_i1++;

							cvZero(l_I1maskTemp1_8u);
							_dContourSizeTemp1 = fabs(cvContourArea(c, CV_WHOLE_SEQ));

							//refreshing max_tab contours
							if (_dContourSizeTemp1 > _dContourMaxSize1_tab[0]){
								_dContourMaxSize1_tab[3] = _dContourMaxSize1_tab[2];
								_dContourMaxSize1_tab[2] = _dContourMaxSize1_tab[1];
								_dContourMaxSize1_tab[1] = _dContourMaxSize1_tab[0];
								_dContourMaxSize1_tab[0] = _dContourSizeTemp1;

								_contourContourMaxSize1_tab[3] = _contourContourMaxSize1_tab[2];
								_contourContourMaxSize1_tab[2] = _contourContourMaxSize1_tab[1];
								_contourContourMaxSize1_tab[1] = _contourContourMaxSize1_tab[0];
								_contourContourMaxSize1_tab[0] = c;
							}
							else{
								if (_dContourSizeTemp1 > _dContourMaxSize1_tab[1]){
									_dContourMaxSize1_tab[3] = _dContourMaxSize1_tab[2];
									_dContourMaxSize1_tab[2] = _dContourMaxSize1_tab[1];
									_dContourMaxSize1_tab[1] = _dContourSizeTemp1;

									_contourContourMaxSize1_tab[3] = _contourContourMaxSize1_tab[2];
									_contourContourMaxSize1_tab[2] = _contourContourMaxSize1_tab[1];
									_contourContourMaxSize1_tab[1] = c;
								}
								else{
									if (_dContourSizeTemp1 > _dContourMaxSize1_tab[2]){
										_dContourMaxSize1_tab[3] = _dContourMaxSize1_tab[2];
										_dContourMaxSize1_tab[2] = _dContourSizeTemp1;

										_contourContourMaxSize1_tab[3] = _contourContourMaxSize1_tab[2];
										_contourContourMaxSize1_tab[2] = c;
									}
									else{
										if (_dContourSizeTemp1 > _dContourMaxSize1_tab[3]){
											_dContourMaxSize1_tab[3] = _dContourSizeTemp1;

											_contourContourMaxSize1_tab[3] = c;
										}
									}
								}
							}


						}//end - forming 4 biggest contours

						
						for(_i1=0; _i1<=0; _i1++) {//ZERO in for loop bacause only for one marker

							////if there is contur on _i1 place
							if ( _contourContourMaxSize1_tab[_i1] != NULL ){
								//Find the center of each contour
								cvZero(l_I1maskTemp1_8u);
								cvZero(l_I1maskAroundMarker1Area1_8u);

								////making mask for only one blob, but with some out-border for being sure that whol marker will be inside that rectangle-mask
									cvRectangle(l_I1maskAroundMarker1Area1_8u,
												cvPoint(cvBoundingRect(_contourContourMaxSize1_tab[_i1]).x - cvRound(cvBoundingRect(_contourContourMaxSize1_tab[_i1]).width/2.) , cvBoundingRect(_contourContourMaxSize1_tab[_i1]).y - cvRound(cvBoundingRect(_contourContourMaxSize1_tab[_i1]).height/2.)),
												cvPoint(cvBoundingRect(_contourContourMaxSize1_tab[_i1]).x + cvBoundingRect(_contourContourMaxSize1_tab[_i1]).width  + cvRound(cvBoundingRect(_contourContourMaxSize1_tab[_i1]).width/2.), cvBoundingRect(_contourContourMaxSize1_tab[_i1]).y + cvBoundingRect(_contourContourMaxSize1_tab[_i1]).height + cvRound(cvBoundingRect(_contourContourMaxSize1_tab[_i1]).height/2.)),
												CV_RGB(255,255,255),
												CV_FILLED,
												8,
												0 );
									cvCopy(l_I1hsvForegroundFinal1_8u, l_I1maskTemp1_8u, l_I1maskAroundMarker1Area1_8u);
									cvDilate(l_I1maskTemp1_8u, l_I1maskTemp1_8u, NULL, 4);
								//end - making mask for only one blob, but with some out-border for being sure that whol marker will be inside that rectangle-mask

								//cvDrawContours(l_I1maskTemp1_8u, _contourContourMaxSize1_tab[_i1] , cvScalarAll(255), cvScalarAll(255), 100, CV_FILLED);
								cvMoments(l_I1maskTemp1_8u, &_momentsContoursMaxSize1,1);
								_pointMarker1ComtourMaxSize1_vec[_i1].x = (int)(_momentsContoursMaxSize1.m10/_momentsContoursMaxSize1.m00);
								_pointMarker1ComtourMaxSize1_vec[_i1].y = (int)(_momentsContoursMaxSize1.m01/_momentsContoursMaxSize1.m00);

								//marking center of marker ;)
								cvCircle(l_I1,
											cvPoint(_pointMarker1ComtourMaxSize1_vec[_i1].x, _pointMarker1ComtourMaxSize1_vec[_i1].y),
											3,
											CV_RGB(255,0,0),
											CV_FILLED,
											8,
											0 );
							}//end - if there is contur on _i1 place

						}// end - for loop

					}//end - if there are some connectedComponents in final mask

				//end - marker 1





				////marker2 taking connected components
					//leaving only choosed color only on the FOREGROUNG (by finding cirlce or marking rect) (color with some range only on the FOREGROUND)
					cvZero(l_I1hsvForegroundFindMarkerColor1_8u);
					cvZero(l_I1hsvForegroundFindMarkerSaturation1_8u);

					cvInRangeS(l_I1hsvForeground1_8u, l_scMarker2ColorAvgLow, l_scMarker2ColorAvgHigh, l_I1hsvForegroundFindMarkerColor1_8u);
					
					if (!g_bLookOnMarkerSaturation)
						cvSet(l_I1hsvForegroundFindMarkerSaturation1_8u, cvScalar(255));
					else
						cvInRangeS(l_I1hsv2_8u, l_scMarker2SaturationAvgLow, l_scMarker2SaturationAvgHigh, l_I1hsvForegroundFindMarkerSaturation1_8u);

					cvAnd(l_I1hsvForegroundFindMarkerColor1_8u, l_I1hsvForegroundFindMarkerSaturation1_8u, l_I1hsvForegroundFinal1_8u);

					if (g_bInterfaceShowViewColorSeparationWithoutBackground)
						cvCopy(l_I1hsvForegroundFinal1_8u, l_I1maskMarker2ColorSeparationWithoutBackground1_8u);

					cvErode(l_I1hsvForegroundFinal1_8u, l_I1maskTemp1_8u, _seStructElementIntensity, 0);
					cvDilate(l_I1maskTemp1_8u, l_I1maskTemp1_8u, _seStructElementIntensity, 3);

					if (g_bInterfaceShowViewColorSeparationWithoutBackgroundClosed)
						cvCopy(l_I1maskTemp1_8u, l_I1maskMarker2ColorSeparationWithoutBackgroundClosed1_8u);

					_seqI1ConnectedForegroundFindMarker2Color = cvSegmentFGMask(l_I1maskTemp1_8u, 0, 210, _msI1ConnectedForegroundFindMarker2Color );

					if (g_bInterfaceShowViewColorSeparationWithoutBackgroundClosedSegment){
						cvZero(l_I1maskMarker2ColorSeparationWithoutBackgroundClosedSegment1_8u);
						cvDrawContours(l_I1maskMarker2ColorSeparationWithoutBackgroundClosedSegment1_8u,_seqI1ConnectedForegroundFindMarker2Color ,cvScalarAll(255),cvScalarAll(255),100,CV_FILLED);
					}

				////end - marker2 taking connected components

				////marker 2
					////if there are some connectedComponents in final mask
					if (_seqI1ConnectedForegroundFindMarker2Color){
						//for every new frame there are new contours, so clearing old ones
						for (int i=0; i<=3; i++)
							_dContourMaxSize1_tab[i] = 0;
						
						_i1=0;
						//forming 4 biggest contours
						for(CvSeq* c=_seqI1ConnectedForegroundFindMarker2Color; c!=NULL; c=c->h_next) {
							_i1++;

							cvZero(l_I1maskTemp1_8u);
							_dContourSizeTemp1 = fabs(cvContourArea(c, CV_WHOLE_SEQ));

							//refreshing max_tab contours
							if (_dContourSizeTemp1 > _dContourMaxSize1_tab[0]){
								_dContourMaxSize1_tab[3] = _dContourMaxSize1_tab[2];
								_dContourMaxSize1_tab[2] = _dContourMaxSize1_tab[1];
								_dContourMaxSize1_tab[1] = _dContourMaxSize1_tab[0];
								_dContourMaxSize1_tab[0] = _dContourSizeTemp1;

								_contourContourMaxSize1_tab[3] = _contourContourMaxSize1_tab[2];
								_contourContourMaxSize1_tab[2] = _contourContourMaxSize1_tab[1];
								_contourContourMaxSize1_tab[1] = _contourContourMaxSize1_tab[0];
								_contourContourMaxSize1_tab[0] = c;
							}
							else{
								if (_dContourSizeTemp1 > _dContourMaxSize1_tab[1]){
									_dContourMaxSize1_tab[3] = _dContourMaxSize1_tab[2];
									_dContourMaxSize1_tab[2] = _dContourMaxSize1_tab[1];
									_dContourMaxSize1_tab[1] = _dContourSizeTemp1;

									_contourContourMaxSize1_tab[3] = _contourContourMaxSize1_tab[2];
									_contourContourMaxSize1_tab[2] = _contourContourMaxSize1_tab[1];
									_contourContourMaxSize1_tab[1] = c;
								}
								else{
									if (_dContourSizeTemp1 > _dContourMaxSize1_tab[2]){
										_dContourMaxSize1_tab[3] = _dContourMaxSize1_tab[2];
										_dContourMaxSize1_tab[2] = _dContourSizeTemp1;

										_contourContourMaxSize1_tab[3] = _contourContourMaxSize1_tab[2];
										_contourContourMaxSize1_tab[2] = c;
									}
									else{
										if (_dContourSizeTemp1 > _dContourMaxSize1_tab[3]){
											_dContourMaxSize1_tab[3] = _dContourSizeTemp1;

											_contourContourMaxSize1_tab[3] = c;
										}
									}
								}
							}


						}//end - forming 4 biggest contours

						
						for(_i1=0; _i1<=0; _i1++) {//ZERO in for loop bacause only for one marker

							////if there is contur on _i1 place
							if ( _contourContourMaxSize1_tab[_i1] != NULL ){
								//Find the center of each contour
								cvZero(l_I1maskTemp1_8u);
								cvZero(l_I1maskAroundMarker2Area1_8u);

								////making mask for only one blob, but with some out-border for being sure that whol marker will be inside that rectangle-mask
									cvRectangle(l_I1maskAroundMarker2Area1_8u,
												cvPoint(cvBoundingRect(_contourContourMaxSize1_tab[_i1]).x - cvRound(cvBoundingRect(_contourContourMaxSize1_tab[_i1]).width/2.) , cvBoundingRect(_contourContourMaxSize1_tab[_i1]).y - cvRound(cvBoundingRect(_contourContourMaxSize1_tab[_i1]).height/2.)),
												cvPoint(cvBoundingRect(_contourContourMaxSize1_tab[_i1]).x + cvBoundingRect(_contourContourMaxSize1_tab[_i1]).width  + cvRound(cvBoundingRect(_contourContourMaxSize1_tab[_i1]).width/2.), cvBoundingRect(_contourContourMaxSize1_tab[_i1]).y + cvBoundingRect(_contourContourMaxSize1_tab[_i1]).height + cvRound(cvBoundingRect(_contourContourMaxSize1_tab[_i1]).height/2.)),
												CV_RGB(255,255,255),
												CV_FILLED,
												8,
												0 );
									cvCopy(l_I1hsvForegroundFinal1_8u, l_I1maskTemp1_8u, l_I1maskAroundMarker2Area1_8u);
									cvDilate(l_I1maskTemp1_8u, l_I1maskTemp1_8u, NULL, 4);
								//end - making mask for only one blob, but with some out-border for being sure that whol marker will be inside that rectangle-mask

								//cvDrawContours(l_I1maskTemp1_8u, _contourContourMaxSize1_tab[_i1] , cvScalarAll(255), cvScalarAll(255), 100, CV_FILLED);
								cvMoments(l_I1maskTemp1_8u, &_momentsContoursMaxSize1,1);
								_pointMarker2ComtourMaxSize1_vec[_i1].x = (int)(_momentsContoursMaxSize1.m10/_momentsContoursMaxSize1.m00);
								_pointMarker2ComtourMaxSize1_vec[_i1].y = (int)(_momentsContoursMaxSize1.m01/_momentsContoursMaxSize1.m00);

								//marking center of marker ;)
								cvCircle(l_I1,
											cvPoint(_pointMarker2ComtourMaxSize1_vec[_i1].x, _pointMarker2ComtourMaxSize1_vec[_i1].y),
											3,
											CV_RGB(255,0,0),
											CV_FILLED,
											8,
											0 );
							}//end - if there is contur on _i1 place

						}// end - for loop

					}//end - if there are some connectedComponents in final mask

				//end - marker 2

			}

			#pragma omp section  
			{
				////marker1 taking connected components
					//leaving only choosed color only on the FOREGROUNG (by finding cirlce or marking rect) (color with some range only on the FOREGROUND)
					cvZero(l_I2hsvForegroundFindMarkerColor1_8u);
					cvZero(l_I2hsvForegroundFindMarkerSaturation1_8u);

					cvInRangeS(l_I2hsvForeground1_8u, l_scMarker1ColorAvgLow, l_scMarker1ColorAvgHigh, l_I2hsvForegroundFindMarkerColor1_8u);
					
					if (!g_bLookOnMarkerSaturation)
						cvSet(l_I2hsvForegroundFindMarkerSaturation1_8u, cvScalar(255));
					else
						cvInRangeS(l_I2hsv2_8u, l_scMarker1SaturationAvgLow, l_scMarker1SaturationAvgHigh, l_I2hsvForegroundFindMarkerSaturation1_8u);

					cvAnd(l_I2hsvForegroundFindMarkerColor1_8u, l_I2hsvForegroundFindMarkerSaturation1_8u, l_I2hsvForegroundFinal1_8u);

					if (g_bInterfaceShowViewColorSeparationWithoutBackground)
						cvCopy(l_I2hsvForegroundFinal1_8u, l_I2maskMarker1ColorSeparationWithoutBackground1_8u);

					cvErode(l_I2hsvForegroundFinal1_8u, l_I2maskTemp1_8u, _seStructElementIntensity, 0);
					cvDilate(l_I2maskTemp1_8u, l_I2maskTemp1_8u, _seStructElementIntensity, 3);

					if (g_bInterfaceShowViewColorSeparationWithoutBackgroundClosed)
						cvCopy(l_I2maskTemp1_8u, l_I2maskMarker1ColorSeparationWithoutBackgroundClosed1_8u);

					_seqI2ConnectedForegroundFindMarker1Color = cvSegmentFGMask(l_I2maskTemp1_8u, 0, 210, _msI2ConnectedForegroundFindMarker1Color );

					if (g_bInterfaceShowViewColorSeparationWithoutBackgroundClosedSegment){
						cvZero(l_I2maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u);
						cvDrawContours(l_I2maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u,_seqI2ConnectedForegroundFindMarker1Color ,cvScalarAll(255),cvScalarAll(255),100,CV_FILLED);
					}

				//end - marker1 taking connected components

				////marker 1
					////if there are some connectedComponents in final mask
					if (_seqI2ConnectedForegroundFindMarker1Color){
						//for every new frame there are new contours, so clearing old ones
						for (int i=0; i<=3; i++)
							_dContourMaxSize2_tab[i] = 0;
						
						_i2=0;
						//forming 4 biggest contours
						for(CvSeq* c=_seqI2ConnectedForegroundFindMarker1Color; c!=NULL; c=c->h_next) {
							_i2++;

							cvZero(l_I2maskTemp1_8u);
							_dContourSizeTemp2 = fabs(cvContourArea(c, CV_WHOLE_SEQ));

							//refreshing max_tab contours
							if (_dContourSizeTemp2 > _dContourMaxSize2_tab[0]){
								_dContourMaxSize2_tab[3] = _dContourMaxSize2_tab[2];
								_dContourMaxSize2_tab[2] = _dContourMaxSize2_tab[1];
								_dContourMaxSize2_tab[1] = _dContourMaxSize2_tab[0];
								_dContourMaxSize2_tab[0] = _dContourSizeTemp2;

								_contourContourMaxSize2_tab[3] = _contourContourMaxSize2_tab[2];
								_contourContourMaxSize2_tab[2] = _contourContourMaxSize2_tab[1];
								_contourContourMaxSize2_tab[1] = _contourContourMaxSize2_tab[0];
								_contourContourMaxSize2_tab[0] = c;
							}
							else{
								if (_dContourSizeTemp2 > _dContourMaxSize2_tab[1]){
									_dContourMaxSize2_tab[3] = _dContourMaxSize2_tab[2];
									_dContourMaxSize2_tab[2] = _dContourMaxSize2_tab[1];
									_dContourMaxSize2_tab[1] = _dContourSizeTemp2;

									_contourContourMaxSize2_tab[3] = _contourContourMaxSize2_tab[2];
									_contourContourMaxSize2_tab[2] = _contourContourMaxSize2_tab[1];
									_contourContourMaxSize2_tab[1] = c;
								}
								else{
									if (_dContourSizeTemp2 > _dContourMaxSize2_tab[2]){
										_dContourMaxSize2_tab[3] = _dContourMaxSize2_tab[2];
										_dContourMaxSize2_tab[2] = _dContourSizeTemp2;

										_contourContourMaxSize2_tab[3] = _contourContourMaxSize2_tab[2];
										_contourContourMaxSize2_tab[2] = c;
									}
									else{
										if (_dContourSizeTemp2 > _dContourMaxSize2_tab[3]){
											_dContourMaxSize2_tab[3] = _dContourSizeTemp2;

											_contourContourMaxSize2_tab[3] = c;
										}
									}
								}
							}


						}//end - forming 4 biggest contours


						for(_i2=0; _i2<=0; _i2++) {//ZERO in for loop bacause only for one marker

							////if there is contur on _i2 place
							if ( _contourContourMaxSize2_tab[_i2] != NULL ){
								//Find the center of each contour
								cvZero(l_I2maskTemp1_8u);
								cvZero(l_I2maskAroundMarker1Area1_8u);

								////making mask for only one blob, but with some out-border for being sure that whol marker will be inside that rectangle-mask
									cvRectangle(l_I2maskAroundMarker1Area1_8u,
												cvPoint(cvBoundingRect(_contourContourMaxSize2_tab[_i2]).x - cvRound(cvBoundingRect(_contourContourMaxSize2_tab[_i2]).width/2.) , cvBoundingRect(_contourContourMaxSize2_tab[_i2]).y - cvRound(cvBoundingRect(_contourContourMaxSize2_tab[_i2]).height/2.)),
												cvPoint(cvBoundingRect(_contourContourMaxSize2_tab[_i2]).x + cvBoundingRect(_contourContourMaxSize2_tab[_i2]).width  + cvRound(cvBoundingRect(_contourContourMaxSize2_tab[_i2]).width/2.), cvBoundingRect(_contourContourMaxSize2_tab[_i2]).y + cvBoundingRect(_contourContourMaxSize2_tab[_i2]).height + cvRound(cvBoundingRect(_contourContourMaxSize2_tab[_i2]).height/2.)),
												CV_RGB(255,255,255),
												CV_FILLED,
												8,
												0 );
									cvCopy(l_I2hsvForegroundFinal1_8u, l_I2maskTemp1_8u, l_I2maskAroundMarker1Area1_8u);
									cvDilate(l_I2maskTemp1_8u, l_I2maskTemp1_8u, NULL, 4);
								//end - making mask for only one blob, but with some out-border for being sure that whol marker will be inside that rectangle-mask

								//cvDrawContours(l_I2maskTemp1_8u, _contourContourMaxSize2_tab[_i2] , cvScalarAll(255), cvScalarAll(255), 100, CV_FILLED);
								cvMoments(l_I2maskTemp1_8u, &_momentsContoursMaxSize2,1);
								_pointMarker1ComtourMaxSize2_vec[_i2].x = (int)(_momentsContoursMaxSize2.m10/_momentsContoursMaxSize2.m00);
								_pointMarker1ComtourMaxSize2_vec[_i2].y = (int)(_momentsContoursMaxSize2.m01/_momentsContoursMaxSize2.m00);

								//marking center of marker ;)
								cvCircle(l_I2,
											cvPoint(_pointMarker1ComtourMaxSize2_vec[_i2].x, _pointMarker1ComtourMaxSize2_vec[_i2].y),
											3,
											CV_RGB(255,0,0),
											CV_FILLED,
											8,
											0 );
							}//end - if there is contur on _i2 place

						}// end - for loop

					}//end - if there are some connectedComponents in final mask

				// end - marker 1





				////marker2 taking connected components
					//leaving only choosed color only on the FOREGROUNG (by finding cirlce or marking rect) (color with some range only on the FOREGROUND)
					cvZero(l_I2hsvForegroundFindMarkerColor1_8u);
					cvZero(l_I2hsvForegroundFindMarkerSaturation1_8u);

					cvInRangeS(l_I2hsvForeground1_8u, l_scMarker2ColorAvgLow, l_scMarker2ColorAvgHigh, l_I2hsvForegroundFindMarkerColor1_8u);					
					
					if (!g_bLookOnMarkerSaturation)
						cvSet(l_I2hsvForegroundFindMarkerSaturation1_8u, cvScalar(255));
					else
						cvInRangeS(l_I2hsv2_8u, l_scMarker2SaturationAvgLow, l_scMarker2SaturationAvgHigh, l_I2hsvForegroundFindMarkerSaturation1_8u);

					cvAnd(l_I2hsvForegroundFindMarkerColor1_8u, l_I2hsvForegroundFindMarkerSaturation1_8u, l_I2hsvForegroundFinal1_8u);

					if (g_bInterfaceShowViewColorSeparationWithoutBackground)
						cvCopy(l_I2hsvForegroundFinal1_8u, l_I2maskMarker2ColorSeparationWithoutBackground1_8u);

					cvErode(l_I2hsvForegroundFinal1_8u, l_I2maskTemp1_8u, _seStructElementIntensity, 0);
					cvDilate(l_I2maskTemp1_8u, l_I2maskTemp1_8u, _seStructElementIntensity, 3);

					if (g_bInterfaceShowViewColorSeparationWithoutBackgroundClosed)
						cvCopy(l_I2maskTemp1_8u, l_I2maskMarker2ColorSeparationWithoutBackgroundClosed1_8u);

					_seqI2ConnectedForegroundFindMarker2Color = cvSegmentFGMask(l_I2maskTemp1_8u, 0, 210, _msI2ConnectedForegroundFindMarker2Color );

					if (g_bInterfaceShowViewColorSeparationWithoutBackgroundClosedSegment){
						cvZero(l_I2maskMarker2ColorSeparationWithoutBackgroundClosedSegment1_8u);
						cvDrawContours(l_I2maskMarker2ColorSeparationWithoutBackgroundClosedSegment1_8u,_seqI2ConnectedForegroundFindMarker2Color ,cvScalarAll(255),cvScalarAll(255),100,CV_FILLED);
					}
					
				//end - marker2 taking connected components

				////marker 2
					////if there are some connectedComponents in final mask
					if (_seqI2ConnectedForegroundFindMarker2Color){
						//for every new frame there are new contours, so clearing old ones
						for (int i=0; i<=3; i++)
							_dContourMaxSize2_tab[i] = 0;
						
						_i2=0;
						//forming 4 biggest contours
						for(CvSeq* c=_seqI2ConnectedForegroundFindMarker2Color; c!=NULL; c=c->h_next) {
							_i2++;

							cvZero(l_I2maskTemp1_8u);
							_dContourSizeTemp2 = fabs(cvContourArea(c, CV_WHOLE_SEQ));

							//refreshing max_tab contours
							if (_dContourSizeTemp2 > _dContourMaxSize2_tab[0]){
								_dContourMaxSize2_tab[3] = _dContourMaxSize2_tab[2];
								_dContourMaxSize2_tab[2] = _dContourMaxSize2_tab[1];
								_dContourMaxSize2_tab[1] = _dContourMaxSize2_tab[0];
								_dContourMaxSize2_tab[0] = _dContourSizeTemp2;

								_contourContourMaxSize2_tab[3] = _contourContourMaxSize2_tab[2];
								_contourContourMaxSize2_tab[2] = _contourContourMaxSize2_tab[1];
								_contourContourMaxSize2_tab[1] = _contourContourMaxSize2_tab[0];
								_contourContourMaxSize2_tab[0] = c;
							}
							else{
								if (_dContourSizeTemp2 > _dContourMaxSize2_tab[1]){
									_dContourMaxSize2_tab[3] = _dContourMaxSize2_tab[2];
									_dContourMaxSize2_tab[2] = _dContourMaxSize2_tab[1];
									_dContourMaxSize2_tab[1] = _dContourSizeTemp2;

									_contourContourMaxSize2_tab[3] = _contourContourMaxSize2_tab[2];
									_contourContourMaxSize2_tab[2] = _contourContourMaxSize2_tab[1];
									_contourContourMaxSize2_tab[1] = c;
								}
								else{
									if (_dContourSizeTemp2 > _dContourMaxSize2_tab[2]){
										_dContourMaxSize2_tab[3] = _dContourMaxSize2_tab[2];
										_dContourMaxSize2_tab[2] = _dContourSizeTemp2;

										_contourContourMaxSize2_tab[3] = _contourContourMaxSize2_tab[2];
										_contourContourMaxSize2_tab[2] = c;
									}
									else{
										if (_dContourSizeTemp2 > _dContourMaxSize2_tab[3]){
											_dContourMaxSize2_tab[3] = _dContourSizeTemp2;

											_contourContourMaxSize2_tab[3] = c;
										}
									}
								}
							}


						}//end - forming 4 biggest contours


						for(_i2=0; _i2<=0; _i2++) {//ZERO in for loop bacause only for one marker

							////if there is contur on _i2 place
							if ( _contourContourMaxSize2_tab[_i2] != NULL ){
								//Find the center of each contour
								cvZero(l_I2maskTemp1_8u);
								cvZero(l_I2maskAroundMarker2Area1_8u);

								////making mask for only one blob, but with some out-border for being sure that whol marker will be inside that rectangle-mask
									cvRectangle(l_I2maskAroundMarker2Area1_8u,
												cvPoint(cvBoundingRect(_contourContourMaxSize2_tab[_i2]).x - cvRound(cvBoundingRect(_contourContourMaxSize2_tab[_i2]).width/2.) , cvBoundingRect(_contourContourMaxSize2_tab[_i2]).y - cvRound(cvBoundingRect(_contourContourMaxSize2_tab[_i2]).height/2.)),
												cvPoint(cvBoundingRect(_contourContourMaxSize2_tab[_i2]).x + cvBoundingRect(_contourContourMaxSize2_tab[_i2]).width  + cvRound(cvBoundingRect(_contourContourMaxSize2_tab[_i2]).width/2.), cvBoundingRect(_contourContourMaxSize2_tab[_i2]).y + cvBoundingRect(_contourContourMaxSize2_tab[_i2]).height + cvRound(cvBoundingRect(_contourContourMaxSize2_tab[_i2]).height/2.)),
												CV_RGB(255,255,255),
												CV_FILLED,
												8,
												0 );
									cvCopy(l_I2hsvForegroundFinal1_8u, l_I2maskTemp1_8u, l_I2maskAroundMarker2Area1_8u);
									cvDilate(l_I2maskTemp1_8u, l_I2maskTemp1_8u, NULL, 4);
								//end - making mask for only one blob, but with some out-border for being sure that whol marker will be inside that rectangle-mask

								//cvDrawContours(l_I2maskTemp1_8u, _contourContourMaxSize2_tab[_i2] , cvScalarAll(255), cvScalarAll(255), 100, CV_FILLED);
								cvMoments(l_I2maskTemp1_8u, &_momentsContoursMaxSize2,1);
								_pointMarker2ComtourMaxSize2_vec[_i2].x = (int)(_momentsContoursMaxSize2.m10/_momentsContoursMaxSize2.m00);
								_pointMarker2ComtourMaxSize2_vec[_i2].y = (int)(_momentsContoursMaxSize2.m01/_momentsContoursMaxSize2.m00);

								//marking center of marker ;)
								cvCircle(l_I2,
											cvPoint(_pointMarker2ComtourMaxSize2_vec[_i2].x, _pointMarker2ComtourMaxSize2_vec[_i2].y),
											3,
											CV_RGB(255,0,0),
											CV_FILLED,
											8,
											0 );
							}//end - if there is contur on _i2 place

						}// end - for loop

					}//end - if there are some connectedComponents in final mask

				// end - marker 2

			}

		}//end - parallel markers colors searching & computing center of markers

		mmComputeDimensionsOfImageOfSensor(l_I1->width, l_I1->height,
											g_dAngleOfCameraSeeingInDegree*2.0*M_PI/360.0, 
											g_dDistanceOfSensorImageD,
											g_dDimensionOfImgOfSensorX, g_dDimensionOfImgOfSensorY);

		//marker 1 position comuputing
		mmFindMarkerPosition(- _pointMarker1ComtourMaxSize1_vec[0].x + l_I1->width/2.0,		// "- _pointMarker1ComtourMaxSize2_vec[0].x" because we want to have pixel coordinates in the way where origin point (0,0) is in principal point - center of image
							  - _pointMarker1ComtourMaxSize1_vec[0].y + l_I1->height/2.0,		// "- l_I1->height/2.0" because we want to have pixel coordinates in the way where origin point (0,0) is in principal point - center of image
							  - _pointMarker1ComtourMaxSize2_vec[0].x + l_I2->width/2.0,
							  - _pointMarker1ComtourMaxSize2_vec[0].y + l_I2->height/2.0,
								g_dDimensionOfImgOfSensorX, g_dDimensionOfImgOfSensorY,
								g_dDimensionOfImgOfSensorX, g_dDimensionOfImgOfSensorY,
								g_dDistanceOfSensorImageD,
								g_dDistanceOfSensorImageD,
							    g_matrixRotationBetweenBothCamerasHalfPlus, g_matrixRotationBetweenBothCamerasHalfMinus,
							    g_matrixTranslationBetweenBothCamerasHalf,
								g_matrixMarker1Position3D, g_matrixMarker1Position3DPrev, g_matrixMarker1Position3DPrevPrev,
								1);

		//marker 2 position comuputing
		mmFindMarkerPosition(- _pointMarker2ComtourMaxSize1_vec[0].x + l_I1->width/2.0,		// "- _pointMarker1ComtourMaxSize2_vec[0].x" because we want to have pixel coordinates in the way where origin point (0,0) is in principal point - center of image
							  - _pointMarker2ComtourMaxSize1_vec[0].y + l_I1->height/2.0,		// "- l_I1->height/2.0" because we want to have pixel coordinates in the way where origin point (0,0) is in principal point - center of image
							  - _pointMarker2ComtourMaxSize2_vec[0].x + l_I2->width/2.0,
							  - _pointMarker2ComtourMaxSize2_vec[0].y + l_I2->height/2.0,
								g_dDimensionOfImgOfSensorX, g_dDimensionOfImgOfSensorY,
								g_dDimensionOfImgOfSensorX, g_dDimensionOfImgOfSensorY,
								g_dDistanceOfSensorImageD,
								g_dDistanceOfSensorImageD,
							    g_matrixRotationBetweenBothCamerasHalfPlus, g_matrixRotationBetweenBothCamerasHalfMinus,
							    g_matrixTranslationBetweenBothCamerasHalf,
								g_matrixMarker2Position3D, g_matrixMarker2Position3DPrev, g_matrixMarker2Position3DPrevPrev,
								2);



		
		////finding where is marker in relation to drums
		if ( (!g_bIfDrumsPositioning) && (g_bIfMarkersColorMarkingIsDone) && (g_bIfDrumsAllArePlaced) ){
			for(int i=0; i<g_vecDrums1.size(); i++){

				if ( g_vecDrums1[i].iTimeToLightOff <= 0 )
					g_vecDrums1[i].iTimeToLightOff = 0;
				else
					g_vecDrums1[i].iTimeToLightOff--;	//counting down time to light off of a drum in a interface 3D
				if ( g_vecDrums2[i].iTimeToLightOff <= 0 )
					g_vecDrums2[i].iTimeToLightOff = 0;
				else
					g_vecDrums2[i].iTimeToLightOff--;	//counting down time to light off of a drum in a interface 3D

				mmIfMarkerCutDrumPlane(&g_vecDrums1[i], g_matrixMarker1Position3D, g_matrixMarker1Position3DPrev);
				mmIfMarkerCutDrumPlane(&g_vecDrums2[i], g_matrixMarker2Position3D, g_matrixMarker2Position3DPrev);

			}

		}
		//end - finding where is marker in relation to drums


		////computing velocity and if there is change of sign of velocity vector in Y-direction (up-down)
			g_dMarker1Velocity = mmVectorLenght( g_matrixMarker1Position3D[0] - g_matrixMarker1Position3DPrev[0],
												  g_matrixMarker1Position3D[1] - g_matrixMarker1Position3DPrev[1],
												  g_matrixMarker1Position3D[2] - g_matrixMarker1Position3DPrev[2] ) / (1/double(g_iCamera1FPS));

			g_dMarker2Velocity = mmVectorLenght( g_matrixMarker2Position3D[0] - g_matrixMarker2Position3DPrev[0],
												  g_matrixMarker2Position3D[1] - g_matrixMarker2Position3DPrev[1],
												  g_matrixMarker2Position3D[2] - g_matrixMarker2Position3DPrev[2] ) / (1/double(g_iCamera1FPS));


			sprintf (g_cDrumsPositioningText3,"Marker 1:   x = %f,   y = %f,   z = %f", g_matrixMarker1Position3D[0], g_matrixMarker1Position3D[1], g_matrixMarker1Position3D[2]);
			sprintf (g_cDrumsPositioningText4,"Marker 2:   x = %f,   y = %f,   z = %f", g_matrixMarker2Position3D[0], g_matrixMarker2Position3D[1], g_matrixMarker2Position3D[2]);
			sprintf (g_cDrumsPositioningText5,"%dfps", g_iCamera1FPS);
			
			//Marker 1 chanege of velocity
			if ( (((g_matrixMarker1Position3D[1] - g_matrixMarker1Position3DPrev[1]) < 0) && ((g_matrixMarker1Position3DPrev[1] - g_matrixMarker1Position3DPrevPrev[1]) > 0)) ||
				 (((g_matrixMarker1Position3D[1] - g_matrixMarker1Position3DPrev[1]) > 0) && ((g_matrixMarker1Position3DPrev[1] - g_matrixMarker1Position3DPrevPrev[1]) < 0)) ) {

					 g_bIfThereIsChangeOfMarker1VelocityDirY = true;
					 g_dMarker1DistanceFromLastChangeDirY = fabs(g_matrixMarker1Position3D[1] - g_matrixMarker1Position3DPrev[1]);
			}
			else{
				g_bIfThereIsChangeOfMarker1VelocityDirY = false;
				g_dMarker1DistanceFromLastChangeDirY = g_dMarker1DistanceFromLastChangeDirY + fabs(g_matrixMarker1Position3D[1] - g_matrixMarker1Position3DPrev[1]);
			}

			//Marker 2 chanege of velocity
			if ( (((g_matrixMarker2Position3D[1] - g_matrixMarker2Position3DPrev[1]) < 0) && ((g_matrixMarker2Position3DPrev[1] - g_matrixMarker2Position3DPrevPrev[1]) > 0)) ||
				 (((g_matrixMarker2Position3D[1] - g_matrixMarker2Position3DPrev[1]) > 0) && ((g_matrixMarker2Position3DPrev[1] - g_matrixMarker2Position3DPrevPrev[1]) < 0)) ) {

					 g_bIfThereIsChangeOfMarker2VelocityDirY = true;
					 g_dMarker2DistanceFromLastChangeDirY = fabs(g_matrixMarker2Position3D[1] - g_matrixMarker2Position3DPrev[1]);
			}
			else{
				g_bIfThereIsChangeOfMarker2VelocityDirY = false;
				g_dMarker2DistanceFromLastChangeDirY = g_dMarker2DistanceFromLastChangeDirY + fabs(g_matrixMarker2Position3D[1] - g_matrixMarker2Position3DPrev[1]);
			}


			////if markers are going down
				if ( (g_matrixMarker1Position3DPrev[1] - g_matrixMarker1Position3D[1]) > 0 )
					g_bIfMarker1GoingDown = true;
				else
					g_bIfMarker1GoingDown = false;

				if ( (g_matrixMarker2Position3DPrev[1] - g_matrixMarker2Position3D[1]) > 0 )
					g_bIfMarker2GoingDown = true;
				else
					g_bIfMarker2GoingDown = false;
			//end - if markers are going down
			
		//end - computing velocity and if there is change of sign of velocity vector




		////positioning of drums
		if (g_bIfDrumsPositioning) {
			if (_bIfDrumPositioningStartingPrepare){

				_iDrumsLeft = g_iDrumsNumber;

				GetLocalTime(&_systemtime); 
				if (!_bIfStartCountingTime){	//to remeber time in moment of start
					_dTimeSecTemp = _systemtime.wSecond + _systemtime.wMinute*60 + _systemtime.wMilliseconds/1000.0 + g_iTimeToSitDownInPlayingSpot;
					_bIfStartCountingTime = true;
					sprintf(_cKindOfAction, "Sit down in playing spot");
				}
				
				g_dTimeCounting = _dTimeSecTemp - (_systemtime.wSecond + _systemtime.wMinute*60 + _systemtime.wMilliseconds/1000.0);
				
				if ( (g_dTimeCounting<=0) || (g_dTimeCounting>=g_iTimeToSitDownInPlayingSpot+1) ){	//second term is for to be sure only
					_bIfDrumPositioningStartingPrepare = false;
					_bIfStartCountingTime = false;	//reset before positioning drums
				}
				
			}
			else{
				if (!_bIfDrumPositioningStarted){

					GetLocalTime(&_systemtime);
					if (!_bIfStartCountingTime){	//to remeber time in moment of start
						_dTimeSecTemp = _systemtime.wSecond + _systemtime.wMinute*60 + _systemtime.wMilliseconds/1000.0 + g_iTimeToPlaceMarkerInDesiredPosition;	
						_bIfStartCountingTime = true;
						sprintf(_cKindOfAction, "Move marker to position of the next drum");
					}
					
					g_dTimeCounting =  _dTimeSecTemp - (_systemtime.wSecond + _systemtime.wMinute*60 + _systemtime.wMilliseconds/1000.0);
					
					if ( (g_dTimeCounting<=0) || (g_dTimeCounting>=g_iTimeToPlaceMarkerInDesiredPosition+1) ){	//second term is for to be sure only
						_bIfDrumPositioningStarted = true;
						_bIfStartCountingTime = false;	//reset before positioning drums
					}
				}
			}

			//here is finding position
			if (_bIfDrumPositioningStarted){
				if (_iDrumsLeft > 0){
					
					GetLocalTime(&_systemtime);
					if (!_bIfStartCountingTime){	//to remeber time in moment of start

						_iDrumPositioningFrameToAvgCount = 0;

						_drumTemp.reset();

						_dTimeSecTemp = _systemtime.wSecond + _systemtime.wMinute*60 + _systemtime.wMilliseconds/1000.0 + g_iTimeToWaitForAveragingPositionOfMarker;	
						_bIfStartCountingTime = true;
						sprintf(_cKindOfAction, "Hold marker for 1sec");
					}
					
					g_dTimeCounting = _dTimeSecTemp - (_systemtime.wSecond + _systemtime.wMinute*60 + _systemtime.wMilliseconds/1000.0);

					_iDrumPositioningFrameToAvgCount++;

					if ((_drumTemp.x == 0.0) && (_drumTemp.y == 0.0) && (_drumTemp.z == 0.0)){
						_drumTemp.x = _drumTemp.x + g_matrixMarker1Position3D[0];
						_drumTemp.y = _drumTemp.y + g_matrixMarker1Position3D[1];
						_drumTemp.z = _drumTemp.z + g_matrixMarker1Position3D[2];
					}
					else{
						if ( (fabs(_drumTemp.x - g_matrixMarker1Position3D[0])<10.0) &&		//remove outliers that are too far from first grabed position of marker
							 (fabs(_drumTemp.y - g_matrixMarker1Position3D[1])<10.0) &&
							 (fabs(_drumTemp.z - g_matrixMarker1Position3D[2])<10.0) ){

							_drumTemp.x = (_drumTemp.x + g_matrixMarker1Position3D[0])/2.0;	//computing average position of drum
							_drumTemp.y = (_drumTemp.y + g_matrixMarker1Position3D[1])/2.0;	//
							_drumTemp.z = (_drumTemp.z + g_matrixMarker1Position3D[2])/2.0;	//
							_drumTemp.refresingDrumPlaneCornersAndABCDcenterPlane();
						}
					}

					if ( (g_dTimeCounting<=0) || (g_dTimeCounting>=g_iTimeToWaitForAveragingPositionOfMarker+1) ){
						g_vecDrums1.push_back(_drumTemp);
						g_vecDrums2.push_back(_drumTemp);
						g_bIfDrumsListNeedToRefresh = true;
						_bIfDrumPositioningStarted = false;
						_bIfStartCountingTime = false;	//reset before waiting for placing marker in next spot by user
						_iDrumsLeft--;
						if (_iDrumsLeft<=0){	//when there are no dums to settle - end drumsPositioning
							g_bIfDrumsPositioning = false;
							g_bIfDrumsAllArePlaced = true;

							g_vecDrums1[0].voice = "hi-hat";	//setting first drum to be hi-hat
							g_vecDrums2[0].voice = "hi-hat";	//
						}

					}

					
				}
			}
			sprintf (g_cDrumsPositioningText0,"%s", _cKindOfAction);
			sprintf (g_cDrumsPositioningText1,"Time to action... %f sec.", g_dTimeCounting);
			sprintf (g_cDrumsPositioningText2,"Left drums to place: %d", _iDrumsLeft);
		}
		else{
			if (g_bIfDrumsAllArePlaced){
				sprintf (g_cDrumsPositioningText0,"Virtual Drums are ready to Play! :)");
				sprintf (g_cDrumsPositioningText1,"");
				sprintf (g_cDrumsPositioningText2,"");
			}
		}
		//end - positioning of drums		



		////show output

			////which windows show/hide
				if (g_bInterfaceShowOpenCVWinLeftView)
					cvShowImage("Camera 1 View", l_I1);
				else
					cvDestroyWindow("Camera 1 View");


				if (g_bInterfaceShowOpenCVWinRightView)
					cvShowImage("Camera 2 View", l_I2);
				else
					cvDestroyWindow("Camera 2 View");



				////camera 1 views
					if ((g_bInterfaceShowViewHue) && (g_bInterfaceShowOpenCVWinLeftView))
						cvShowImage("Camera 1 - Hue", l_I1hsv1_8u);
					else
						cvDestroyWindow("Camera 1 - Hue");

					if ((g_bInterfaceShowViewSaturation) && (g_bInterfaceShowOpenCVWinLeftView))
						cvShowImage("Camera 1 - Saturation", l_I1hsv2_8u);
					else
						cvDestroyWindow("Camera 1 - Saturation");

					if ((g_bInterfaceShowViewValue) && (g_bInterfaceShowOpenCVWinLeftView))
						cvShowImage("Camera 1 - Value", l_I1hsv3_8u);
					else
						cvDestroyWindow("Camera 1 - Value");

					
					if ((g_bInterfaceShowViewRed) && (g_bInterfaceShowOpenCVWinLeftView))
						;//cvShowImage("Camera 1 - Red", l_I1rgb1_8u);
					else
						cvDestroyWindow("Camera 1 - Red");

					if ((g_bInterfaceShowViewGreen) && (g_bInterfaceShowOpenCVWinLeftView))
						;//cvShowImage("Camera 1 - Green", l_I1rgb2_8u);
					else
						cvDestroyWindow("Camera 1 - Green");

					if ((g_bInterfaceShowViewBlue) && (g_bInterfaceShowOpenCVWinLeftView))
						;//cvShowImage("Camera 1 - Blue", l_I1rgb3_8u);
					else
						cvDestroyWindow("Camera 1 - Blue");


					if ((g_bInterfaceShowViewWithoutBackground) && (g_bInterfaceShowOpenCVWinLeftView)){
						if (g_bInterfaceShowViewOnlyMasks)
							cvShowImage("Camera 1 - view without background", l_I1maskWithoutBackground1_8u);
						else{
							cvZero(l_I1temp);
							cvCopy(l_I1, l_I1temp, l_I1maskWithoutBackground1_8u);
							cvShowImage("Camera 1 - view without background", l_I1temp);
							//cvZero(l_I1temp);
						}
					}
					else
						cvDestroyWindow("Camera 1 - view without background");

					if ((g_bInterfaceShowViewColorSeparationWithoutBackground) && (g_bInterfaceShowOpenCVWinLeftView)){
						if (g_bInterfaceShowViewOnlyMasks){
							cvOr(l_I1maskMarker1ColorSeparationWithoutBackground1_8u, l_I1maskMarker2ColorSeparationWithoutBackground1_8u, l_I1maskMarker1ColorSeparationWithoutBackground1_8u, NULL);
							cvShowImage("Camera 1 - view without background + color separation", l_I1maskMarker1ColorSeparationWithoutBackground1_8u);
						}
						else{
							cvZero(l_I1temp);
							cvOr(l_I1maskMarker1ColorSeparationWithoutBackground1_8u, l_I1maskMarker2ColorSeparationWithoutBackground1_8u, l_I1maskMarker1ColorSeparationWithoutBackground1_8u, NULL);
							cvCopy(l_I1, l_I1temp, l_I1maskMarker1ColorSeparationWithoutBackground1_8u);
							cvShowImage("Camera 1 - view without background + color separation", l_I1temp);
							//cvZero(l_I1temp);
						}
					}
					else
						cvDestroyWindow("Camera 1 - view without background + color separation");

					if ((g_bInterfaceShowViewColorSeparationWithoutBackgroundClosed) && (g_bInterfaceShowOpenCVWinLeftView)){
						if (g_bInterfaceShowViewOnlyMasks){
							cvOr(l_I1maskMarker1ColorSeparationWithoutBackgroundClosed1_8u, l_I1maskMarker2ColorSeparationWithoutBackgroundClosed1_8u, l_I1maskMarker1ColorSeparationWithoutBackgroundClosed1_8u, NULL);
							cvShowImage("Camera 1 - view without background + color separation + closing", l_I1maskMarker1ColorSeparationWithoutBackgroundClosed1_8u);
						}
						else{
							cvZero(l_I1temp);
							cvOr(l_I1maskMarker1ColorSeparationWithoutBackgroundClosed1_8u, l_I1maskMarker2ColorSeparationWithoutBackgroundClosed1_8u, l_I1maskMarker1ColorSeparationWithoutBackgroundClosed1_8u, NULL);
							cvCopy(l_I1, l_I1temp, l_I1maskMarker1ColorSeparationWithoutBackgroundClosed1_8u);
							cvShowImage("Camera 1 - view without background + color separation + closing", l_I1temp);
							//cvZero(l_I1temp);
						}
					}
					else
						cvDestroyWindow("Camera 1 - view without background + color separation + closing");
					
					if ((g_bInterfaceShowViewColorSeparationWithoutBackgroundClosedSegment) && (g_bInterfaceShowOpenCVWinLeftView)){
						if (g_bInterfaceShowViewOnlyMasks){
							cvOr(l_I1maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u, l_I1maskMarker2ColorSeparationWithoutBackgroundClosedSegment1_8u, l_I1maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u, NULL);
							cvShowImage("Camera 1 - view without background + color separation + closing + segmentation", l_I1maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u);
						}
						else{
							cvZero(l_I1temp);
							cvOr(l_I1maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u, l_I1maskMarker2ColorSeparationWithoutBackgroundClosedSegment1_8u, l_I1maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u, NULL);
							cvCopy(l_I1, l_I1temp, l_I1maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u);
							cvShowImage("Camera 1 - view without background + color separation + closing + segmentation", l_I1temp);
							//cvZero(l_I1temp);
						}
					}
					else
						cvDestroyWindow("Camera 1 - view without background + color separation + closing + segmentation");
				//end - camera 1 views


				////camera 2 views
					if ((g_bInterfaceShowViewHue) && (g_bInterfaceShowOpenCVWinRightView))
						cvShowImage("Camera 2 - Hue", l_I2hsv1_8u);
					else
						cvDestroyWindow("Camera 2 - Hue");

					if ((g_bInterfaceShowViewSaturation) && (g_bInterfaceShowOpenCVWinRightView))
						cvShowImage("Camera 2 - Saturation", l_I2hsv2_8u);
					else
						cvDestroyWindow("Camera 2 - Saturation");

					if ((g_bInterfaceShowViewValue) && (g_bInterfaceShowOpenCVWinRightView))
						cvShowImage("Camera 2 - Value", l_I2hsv3_8u);
					else
						cvDestroyWindow("Camera 2 - Value");


					if ((g_bInterfaceShowViewRed) && (g_bInterfaceShowOpenCVWinRightView))
						;//cvShowImage("Camera 2 - Red", l_I2rgb1_8u);
					else
						cvDestroyWindow("Camera 2 - Red");

					if ((g_bInterfaceShowViewGreen) && (g_bInterfaceShowOpenCVWinRightView))
						;//cvShowImage("Camera 2 - Green", l_I2rgb2_8u);
					else
						cvDestroyWindow("Camera 2 - Green");

					if ((g_bInterfaceShowViewBlue) && (g_bInterfaceShowOpenCVWinRightView))
						;//cvShowImage("Camera 2 - Blue", l_I2rgb3_8u);
					else
						cvDestroyWindow("Camera 2 - Blue");



					if ((g_bInterfaceShowViewWithoutBackground) && (g_bInterfaceShowOpenCVWinRightView)){
						if (g_bInterfaceShowViewOnlyMasks)
							cvShowImage("Camera 2 - view without background", l_I2maskWithoutBackground1_8u);
						else{
							cvZero(l_I2temp);
							cvCopy(l_I2, l_I2temp, l_I2maskWithoutBackground1_8u);
							cvShowImage("Camera 2 - view without background", l_I2temp);
							//cvZero(l_I1temp);
						}
					}
					else
						cvDestroyWindow("Camera 2 - view without background");

					if ((g_bInterfaceShowViewColorSeparationWithoutBackground) && (g_bInterfaceShowOpenCVWinRightView)){
						if (g_bInterfaceShowViewOnlyMasks){
							cvOr(l_I2maskMarker1ColorSeparationWithoutBackground1_8u, l_I2maskMarker2ColorSeparationWithoutBackground1_8u, l_I2maskMarker1ColorSeparationWithoutBackground1_8u, NULL);
							cvShowImage("Camera 2 - view without background + color separation", l_I2maskMarker1ColorSeparationWithoutBackground1_8u);
						}
						else{
							cvZero(l_I2temp);
							cvOr(l_I2maskMarker1ColorSeparationWithoutBackground1_8u, l_I2maskMarker2ColorSeparationWithoutBackground1_8u, l_I2maskMarker1ColorSeparationWithoutBackground1_8u, NULL);
							cvCopy(l_I2, l_I2temp, l_I2maskMarker1ColorSeparationWithoutBackground1_8u);
							cvShowImage("Camera 2 - view without background + color separation", l_I2temp);
							//cvZero(l_I1temp);
						}
					}
					else
						cvDestroyWindow("Camera 2 - view without background + color separation");

					if ((g_bInterfaceShowViewColorSeparationWithoutBackgroundClosed) && (g_bInterfaceShowOpenCVWinRightView)){
						if (g_bInterfaceShowViewOnlyMasks){
							cvOr(l_I2maskMarker1ColorSeparationWithoutBackgroundClosed1_8u, l_I2maskMarker2ColorSeparationWithoutBackgroundClosed1_8u, l_I2maskMarker1ColorSeparationWithoutBackgroundClosed1_8u, NULL);
							cvShowImage("Camera 2 - view without background + color separation + closing", l_I2maskMarker1ColorSeparationWithoutBackgroundClosed1_8u);
						}
						else{
							cvZero(l_I2temp);
							cvOr(l_I2maskMarker1ColorSeparationWithoutBackgroundClosed1_8u, l_I2maskMarker2ColorSeparationWithoutBackgroundClosed1_8u, l_I2maskMarker1ColorSeparationWithoutBackgroundClosed1_8u, NULL);
							cvCopy(l_I2, l_I2temp, l_I2maskMarker1ColorSeparationWithoutBackgroundClosed1_8u);
							cvShowImage("Camera 2 - view without background + color separation + closing", l_I2temp);
							//cvZero(l_I1temp);
						}
					}
					else
						cvDestroyWindow("Camera 2 - view without background + color separation + closing");
					
					if ((g_bInterfaceShowViewColorSeparationWithoutBackgroundClosedSegment) && (g_bInterfaceShowOpenCVWinRightView)){
						if (g_bInterfaceShowViewOnlyMasks){
							cvOr(l_I2maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u, l_I2maskMarker2ColorSeparationWithoutBackgroundClosedSegment1_8u, l_I2maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u, NULL);
							cvShowImage("Camera 2 - view without background + color separation + closing + segmentation", l_I2maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u);
						}
						else{
							cvZero(l_I2temp);
							cvOr(l_I2maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u, l_I2maskMarker2ColorSeparationWithoutBackgroundClosedSegment1_8u, l_I2maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u, NULL);
							cvCopy(l_I2, l_I2temp, l_I2maskMarker1ColorSeparationWithoutBackgroundClosedSegment1_8u);
							cvShowImage("Camera 2 - view without background + color separation + closing + segmentation", l_I2temp);
							//cvZero(l_I1temp);
						}
					}
					else
						cvDestroyWindow("Camera 2 - view without background + color separation + closing + segmentation");
				//end - camera 2 views
				
			//end - which windows show/hide

		//end - show output

		sprintf(_cFileName, "z_Image%d_1.jpg", g_liFrameCount);
		cvSaveImage(_cFileName, l_I1);
		sprintf(_cFileName, "z_Image%d_2.jpg", g_liFrameCount);
		cvSaveImage(_cFileName, l_I2);


		////averaging fps
			_iTimeDiff = GetTickCount() - _iTimeDiff;
			_iFpsTemp = _iFpsTemp + _iTimeDiff;
			if ((g_liFrameCount % 6 == 0) && (g_liFrameCount != 0)){
				_iFps = static_cast<int>(1000/(_iFpsTemp/6));  // 6 - number of frames to average cameras FPS
				_iFpsTemp = 1;
			}
			g_iCamera1FPS = _iFps;
		//end - averaging fps



		////parallel backgroundmodel updating
		#pragma omp parallel sections default(shared)
		{
			#pragma omp section  
			{
				if (_iWhichMarkerColorSelecting >= 2){	//updating bacground only when we know colors of both markers - to not upgrade them
				cvZero(l_I1maskTemp1_8u);
				cvOr(l_I1maskAroundMarker1Area1_8u, l_I1maskAroundMarker2Area1_8u, l_I1maskTemp1_8u, NULL);
				mmUpdateBackgroundCodeBook(l_I1yuv_8u, l_I1maskTemp1_8u, _backgroundModelCamera1, g_liFrameCount, _iFps);
				}
			}

			#pragma omp section  
			{
				if (_iWhichMarkerColorSelecting >= 2){	//updating bacground only when we know colors of both markers - to not upgrade them
				cvZero(l_I2maskTemp1_8u);
				cvOr(l_I2maskAroundMarker1Area1_8u, l_I2maskAroundMarker2Area1_8u, l_I2maskTemp1_8u, NULL);
				mmUpdateBackgroundCodeBook(l_I2yuv_8u, l_I2maskTemp1_8u, _backgroundModelCamera2, g_liFrameCount, _iFps);
				}
			}
		}//end - parallel backgroundmodel updating


        g_liFrameCount++;

        l_iKey = cvWaitKey(10)&0xFF;
        l_iKey = tolower(l_iKey);

		if ( (_iWhichMarkerColorSelecting >= 2) && (g_bRefreshingAutoProcessingParameters) ){	//autoadjust after we know colors of both markers - but not with them in the views of cameras
			bool _bResult = mmAutoAdjustImagesProcessingPrameters(	l_I1maskMarker1ColorSeparationWithoutBackgroundClosed1_8u, l_I2maskMarker1ColorSeparationWithoutBackgroundClosed1_8u,
																	g_liFrameCount, _iFps, 
																	_backgroundModelCamera1, _backgroundModelCamera2,
																	g_iCodeBookModMin, g_iCodeBookModMax, g_dColorFactorBounds);
			if (_bResult){
				sprintf(g_cMessages, "Automatic adjusting processing parameters is done");
				_sysstringMessages = gcnew String(g_cMessages);
				MessageBox::Show(_sysstringMessages);
			}
		}



        mmChangeCodeBookParam(_backgroundModelCamera1, g_iCodeBookModMin, g_iCodeBookModMax, g_iCodeBookCbBounds);
		mmChangeCodeBookParam(_backgroundModelCamera2, g_iCodeBookModMin, g_iCodeBookModMax, g_iCodeBookCbBounds);

		cvReleaseImage( &l_I1temp);
		cvReleaseImage( &l_I2temp);

        if( (l_iKey == 5) || g_bIfProgramClosing ) break;        
    
	}

    
    ////finish jobs
		cvDestroyAllWindows();
		cvReleaseCapture(&_Camera1);		
		cvReleaseCapture(&_Camera2);
		//mmDeallocateImages();//	WHY HERE IS SHOWING ERROR? - zalezy od ustawienia cvReleaseCapture mmDeallocateImages, na jednym i drugim wywala sie
		
		g_bIfMainLoopStopped = true;
	//end - finish jobs


    return (EXIT_SUCCESS);
}



/////////IIIIIIDDDDDDDDDDDDDDDDDDEEEEEEEEEEEEEEEEAAAAAAAAAAAAAAAAAAA//////////////////////
//trzeba zmienic liczenie fps dla camery 1 i camery 2 i dodac fps calego praogramu (to co teraz jest fpsem camery1)

//kolory FPS w oknie interface3D (zielony-ok, zó³ty-moze byæ, czerwony-za ma³o klatek/s)

//po zmianie pozycji bêbna w interfejsie trzeba odswiezac rogi jego powierzchni
			
//komunikaty: na pocz¹tku, w trakcie i na koniec uczenia sie parametrów przetwarzania obrazu i pokazywanie ¿e dalej siê uczy, ¿eyb u¿ytkownik wiedzia³ o tym i nie zw¹tpi³