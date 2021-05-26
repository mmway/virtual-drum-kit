#include "stdafx.h"

#ifndef _VIRTUALDRUMS_GLOBALS_H
#define _VIRTUALDRUMS_GLOBALS_H

#include "markerPosition3d.h"

#include <irrKlang/irrKlang.h>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

	class mmDrum{
		public:
			double x,y,z;	//position of drum center in 3D space
			int width, height, depth;	//dimensions of a drum, now when drum is only a plane this is not used
			
			CvPoint3D64f A, B, C, D;	//vertecs of drum plane
			std::string voice;				//remebering voice of a drum
			bool ifDrumIsHitted;				//if the drum is in moment of hitting
			int iTimeToLightOff;	//time that drum is lighted up in a interface3D after hitting this drum
			mmLine linAB, linBC, linCD, linDA;	//edge of drum plane
			mmPlane _plABCDcenterPlane;	//when drum is only a plane - not a box

			//Audio
			irrklang::ISoundEngine* soundEngine;
			irrklang::ISoundSource* soundSampleEng;

			mmDrum();	//constructor
			~mmDrum();	//destructor
			void reset();
			void refresingDrumPlaneCornersAndABCDcenterPlane();

			//or drums testing
			int iTimesHitted;	//how many times drum was hitted
			CvPoint3D64f ptMab, ptMbc, ptMcd, ptMda, ptCrossPoint;	//store points on a drum edges

	};


//Drums
	extern std::vector<mmDrum> g_vecDrums1;
	extern std::vector<mmDrum> g_vecDrums2;
	extern bool g_bIfDrumsPositioning;	//also decide of how often background is doing "clear_stale"
	extern double g_dTimeCounting;	//time to next step of positioning drums
	extern int g_iDrumsNumber;		//number of drums to place around an user
	extern int g_iDrumNumberToChangeProperty;	//which drum is now selected to change it's properties

	extern bool g_bDrumBassHitted;		//if bass drum is hitted - defines playing bass drum sound in sound loop
	extern bool g_bDrumPedalHihatState;	//1-foot down; 2-foot up
	extern bool g_bDrumPedalStateChange;

	extern int g_iDrumsWidth;		//user changable width of drum
	extern int g_iDrumsHeight;		//user changable height of drum
	extern int g_iDrumsDepth;		//user changable depth of drum
	extern int g_iTimeToSitDownInPlayingSpot,	//time to wait for user to sit down in playing spot
				g_iTimeToPlaceMarkerInDesiredPosition,	//time to wait for user to place marker in write position
				g_iTimeToWaitForAveragingPositionOfMarker;	//time to wait for averaging position of marker


//Markers
	extern bool g_bIfThereIsChangeOfMarker1VelocityDirY;
	extern bool g_bIfThereIsChangeOfMarker2VelocityDirY;
	extern double g_dMarker1DistanceFromLastChangeDirY;
	extern double g_dMarker2DistanceFromLastChangeDirY;
	extern bool g_bIfMarker1GoingDown;
	extern bool g_bIfMarker2GoingDown;
	extern double g_dMarker1Velocity;
	extern double g_dMarker2Velocity;
	//markers positions actual, previous, previous of previous
	extern double g_matrixMarker1Position3D[3], g_matrixMarker1Position3DPrev[3], g_matrixMarker1Position3DPrevPrev[3];
	extern double g_matrixMarker2Position3D[3], g_matrixMarker2Position3DPrev[3], g_matrixMarker2Position3DPrevPrev[3];

	extern bool g_bIfMarkersColorMarkingIsDone;


//cameras variables
	extern int g_iCamera1FPS, g_iCamera2FPS;
	extern long g_liFrameCount;


////stereo calibration
	extern int g_iCalibrationType;		// 1 - new calibration;   0 - use calibration info from file
	extern int g_iCalibrationActualProcessNumberOfFrames;
	extern double g_dAngleOfCameraSeeingInDegree;
	extern double g_dDistanceOfSensorImageD;	//
	extern double g_dDimensionOfImgOfSensorX, g_dDimensionOfImgOfSensorY;

	extern double g_dChessboardSquareSize;	//in centimeters
	extern int g_iChessboardCornersNumberX, 
				g_iChessboardCornersNumberY;

	extern int g_iCamerasCalibrationResolutionWidth,
				g_iCamerasCalibrationResolutionHeight;

	//rotation & traslation matrix
	extern double  g_matrixRotationBetweenBothCameras[3][3], 
			g_matrixRotationBetweenBothCamerasHalfPlus[3][3], 
			g_matrixRotationBetweenBothCamerasHalfMinus[3][3], 
			g_matrixTranslationBetweenBothCameras[3];
	extern double g_matrixRotationBetweenBothCameras3x1Half[3], g_matrixTranslationBetweenBothCamerasHalf[3];
	extern double g_matrixCamera1Intristic[3][3];
	extern double g_matrixCamera2Intristic[3][3];

	extern IplImage *g_I1undistortMapX1_32f, *g_I1undistortMapY1_32f;	//undistortion maps
	extern IplImage *g_I2undistortMapX1_32f, *g_I2undistortMapY1_32f;	//

//end - stereo calibration


////interface 3D
	extern double g_dInterface3dRotX, g_dInterface3dRotY, g_dInterface3dRotZ;	//rotations of 3D interface controled by user

	//texts showed on interface3D
	extern char g_cDrumsPositioningText0[100],
				 g_cDrumsPositioningText1[100],
				 g_cDrumsPositioningText2[100],
				 g_cDrumsPositioningText3[100],
				 g_cDrumsPositioningText4[100],
				 g_cDrumsPositioningText5[100],
				 g_cDrumsPositioningText6[100],
				 g_cDrumsPositioningText7[100];

	//marker 1 rays
	extern double g_matrixMarker1LineA[2][3];	//two point in two rows - are both points on line, where one of them is principal point, and second is marker camera on imager
	extern double g_matrixMarker1LineB[2][3];	
	//marker 2 rays
	extern double g_matrixMarker2LineA[2][3];	//two point in two rows - are both points on line, where one of them is principal point, and second is marker camera on imager
	extern double g_matrixMarker2LineB[2][3];	

	extern double g_matrixMarker1color[3];	//starting values of markers color
	extern double g_matrixMarker2color[3];	//
//end - interface 3D



////user interface - setting & options

	//on/off windows
		extern bool g_bInterfaceShowOpenCVWinRightView,
					 g_bInterfaceShowOpenCVWinLeftView,
					 g_bInterfaceShowViewOnlyMasks,
					 g_bInterfaceShowViewHue,
					 g_bInterfaceShowViewSaturation,
					 g_bInterfaceShowViewValue,
					 g_bInterfaceShowViewRed,
					 g_bInterfaceShowViewGreen,
					 g_bInterfaceShowViewBlue,
					 g_bInterfaceShowViewWithoutBackground,
					 g_bInterfaceShowViewColorSeparationWithoutBackground,
					 g_bInterfaceShowViewColorSeparationWithoutBackgroundClosed,
					 g_bInterfaceShowViewColorSeparationWithoutBackgroundClosedSegment;

	extern bool g_bIfDrumsListNeedToRefresh;
	extern bool g_bIfDrumsAllArePlaced;
	extern bool g_bRefreshingAutoProcessingParameters;

	extern bool g_bIfProgramClosing;
	extern bool g_bIfMainLoopStopped;

	extern char g_cMessages[1024];

	//processing options
		extern bool g_bUseBackgroundSubtraction,
					g_bLookOnMarkerSaturation;

		//codebook parameters start setup
		extern int g_iCodeBookModMin, g_iCodeBookModMax, g_iCodeBookCbBounds;
		extern int g_iNumberFramesToLearnBG;

		//camera acquisition parameters
		extern int g_iCamerasMainLoopResolutionWidth, g_iCamerasMainLoopResolutionHeight;

		//color separating parameters
		extern double g_dColorFactorBounds, g_dSaturationFactorBounds;

		//auto adjust processing parameters
		extern double g_dAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust,	//experimentally fixed
						g_dAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust,	//experimentally fixed
						g_dAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust,	//experimentally fixed
						g_dAutoAdjustGoodResultsPercentageAfterColorFactorAdjust;	//experimentally fixed

		extern bool g_bIfPositionMarker1Measure;	//for measuring precision of marker position

	//extern int g_iTimeDelay;
	//extern int g_iTimeDelayAvg;
	//extern bool g_bIfTimeDelayNeedReset;

//end - user interface - setting & options
	
				

#endif