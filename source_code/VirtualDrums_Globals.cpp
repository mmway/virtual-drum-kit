#include "stdafx.h"

#include "opencv/cv.h"

#include "VirtualDrums_Globals.h"
#include "markerPosition3d.h"
#include "otherFunctions.h"
#include "string.h"
#include <vector>

#include "Form1.h"

using namespace virtualDrums_temp;


mmDrum::mmDrum(){
	x = 0.0;	//center point of a drum
	y = 0.0;	//center point of a drum
	z = 0.0;	//center point of a drum
	width = g_iDrumsWidth;
	height = g_iDrumsHeight;
	depth = g_iDrumsDepth;
	ifDrumIsHitted = false;
	iTimeToLightOff = false;
	voice = "snaredrum.wav";
	iTimesHitted = 0;

	soundEngine = irrklang::createIrrKlangDevice();
	soundSampleEng = soundEngine->addSoundSourceFromFile("audioSamples\\snaredrum.wav");

	if (!soundEngine) 
		MessageBox::Show("could not start audio engine");

}


mmDrum::~mmDrum(){
}


void mmDrum::reset(){
	x = 0.0;
	y = 0.0;
	z = 0.0;
	width = g_iDrumsWidth;
	height = g_iDrumsHeight;
	depth = g_iDrumsDepth;
	ifDrumIsHitted = false;
	voice = "snaredrum.wav";
	iTimesHitted = 0;

	soundEngine = irrklang::createIrrKlangDevice();
	soundSampleEng = soundEngine->addSoundSourceFromFile("audioSamples\\snaredrum.wav");

	if (!soundEngine) 
		MessageBox::Show("could not start audio engine");

}



void mmDrum::refresingDrumPlaneCornersAndABCDcenterPlane(){
	A.x = x + ( -double(width)/2.0 );
	A.y = y;
	A.z = z + ( double(depth)/2.0 );

	B.x = x + ( -double(width)/2.0 );
	B.y = y;
	B.z = z + ( -double(depth)/2.0 );

	C.x = x + ( double(width)/2.0 );
	C.y = y;
	C.z = z + ( -double(depth)/2.0 );

	D.x = x + ( double(width)/2.0 );
	D.y = y;
	D.z = z + ( double(depth)/2.0 );


	CvPoint3D64f _ptVecABCDnormal;


	mmIloczWekt( (A.x - B.x), (A.y - B.y), (A.z - B.z), 
				  (B.x - C.x), (B.y - C.y), (B.z - C.z),
				  &_ptVecABCDnormal.x, &_ptVecABCDnormal.y, &_ptVecABCDnormal.z);


	mmFindPlaneParameters(A, _ptVecABCDnormal, &_plABCDcenterPlane);


	////computing edge of a drum plane
		linAB.pointOn.x = A.x;
		linAB.pointOn.y = A.y;
		linAB.pointOn.z = A.z;
		linAB.vectorDir.x = A.x - B.x;
		linAB.vectorDir.y = A.y - B.y;
		linAB.vectorDir.z = A.z - B.z;

		linBC.pointOn.x = B.x;
		linBC.pointOn.y = B.y;
		linBC.pointOn.z = B.z;
		linBC.vectorDir.x = B.x - C.x;
		linBC.vectorDir.y = B.y - C.y;
		linBC.vectorDir.z = B.z - C.z;

		linCD.pointOn.x = C.x;
		linCD.pointOn.y = C.y;
		linCD.pointOn.z = C.z;
		linCD.vectorDir.x = C.x - D.x;
		linCD.vectorDir.y = C.y - D.y;
		linCD.vectorDir.z = C.z - D.z;

		linDA.pointOn.x = D.x;
		linDA.pointOn.y = D.y;
		linDA.pointOn.z = D.z;
		linDA.vectorDir.x = D.x - A.x;
		linDA.vectorDir.y = D.y - A.y;
		linDA.vectorDir.z = D.z - A.z;
	//end - computing edge of a drum plane
}





//Drums
	std::vector<mmDrum> g_vecDrums1;
	std::vector<mmDrum> g_vecDrums2;
	bool g_bIfDrumsPositioning = false;	//also decide of how often background is doing "clear_stale"
	double g_dTimeCounting = 0.0;	//time to next step of positioning drums
	int g_iDrumsNumber = 2;		//number of drums to place around an user
	extern int g_iDrumNumberToChangeProperty = 2;	//which drum is now selected to change it's properties

	bool g_bDrumBassHitted = false;		//if bass drum is hitted - defines playing bass drum sound in sound loop
	bool g_bDrumPedalHihatState = false;	//1-foot down; 2-foot up
	bool g_bDrumPedalStateChange = false;

	int g_iDrumsWidth = 30;		//user changable width of drum
	int g_iDrumsHeight = 30;		//user changable height of drum
	int g_iDrumsDepth = 30;		//user changable depth of drum

	int g_iTimeToSitDownInPlayingSpot = 4,	//time to wait for user to sit down in playing spot
		g_iTimeToPlaceMarkerInDesiredPosition = 2,	//time to wait for user to place marker in write position
		g_iTimeToWaitForAveragingPositionOfMarker = 1;	//time to wait for averaging position of marker


//Markers
	bool g_bIfThereIsChangeOfMarker1VelocityDirY = false;
	bool g_bIfThereIsChangeOfMarker2VelocityDirY = false;
	double g_dMarker1DistanceFromLastChangeDirY = 0.0;
	double g_dMarker2DistanceFromLastChangeDirY = 0.0;
	bool g_bIfMarker1GoingDown = false;
	bool g_bIfMarker2GoingDown = false;
	double g_dMarker1Velocity = 0;
	double g_dMarker2Velocity = 0;
	//markers positions actual, previous, previous of previous
	double g_matrixMarker1Position3D[3], g_matrixMarker1Position3DPrev[3], g_matrixMarker1Position3DPrevPrev[3];
	double g_matrixMarker2Position3D[3], g_matrixMarker2Position3DPrev[3], g_matrixMarker2Position3DPrevPrev[3];

	bool g_bIfMarkersColorMarkingIsDone = false;


//cameras variables
int g_iCamera1FPS, g_iCamera2FPS;
long  g_liFrameCount;


////stereo calibration
	int g_iCalibrationType = 0;		// 1 - new calibration;   0 - use calibration info from file
	int g_iCalibrationActualProcessNumberOfFrames = 25;
	double g_dAngleOfCameraSeeingInDegree = 80.0;
	double g_dDistanceOfSensorImageD = 5;	//
	double g_dDimensionOfImgOfSensorX, g_dDimensionOfImgOfSensorY;

	double g_dChessboardSquareSize = 3;	//in centimeters
	int g_iChessboardCornersNumberX = 9, 
		g_iChessboardCornersNumberY = 6;

	int g_iCamerasCalibrationResolutionWidth = 1600,
		g_iCamerasCalibrationResolutionHeight = 1200;

	//rotation & traslation matrix
	double  g_matrixRotationBetweenBothCameras[3][3], 
			g_matrixRotationBetweenBothCamerasHalfPlus[3][3], 
			g_matrixRotationBetweenBothCamerasHalfMinus[3][3], 
			g_matrixTranslationBetweenBothCameras[3];
	double g_matrixRotationBetweenBothCameras3x1Half[3], g_matrixTranslationBetweenBothCamerasHalf[3];
	double g_matrixCamera1Intristic[3][3];
	double g_matrixCamera2Intristic[3][3];

	IplImage *g_I1undistortMapX1_32f, *g_I1undistortMapY1_32f;	//undistortion maps
	IplImage *g_I2undistortMapX1_32f, *g_I2undistortMapY1_32f;	//

//end - stereo calibration


////interface 3D
	double g_dInterface3dRotX = 0, g_dInterface3dRotY = 0, g_dInterface3dRotZ = 0;	//rotations of 3D interface controled by user

	//texts showed on interface3D
	char g_cDrumsPositioningText0[100];
	char g_cDrumsPositioningText1[100];
	char g_cDrumsPositioningText2[100];
	char g_cDrumsPositioningText3[100];
	char g_cDrumsPositioningText4[100];
	char g_cDrumsPositioningText5[100];
	char g_cDrumsPositioningText6[100];
	char g_cDrumsPositioningText7[100];

	//marker 1 rays
	double g_matrixMarker1LineA[2][3];	//two point in two rows - are both points on line, where one of them is principal point, and second is marker camera on imager
	double g_matrixMarker1LineB[2][3];	
	//marker 2 rays
	double g_matrixMarker2LineA[2][3];	//two point in two rows - are both points on line, where one of them is principal point, and second is marker camera on imager
	double g_matrixMarker2LineB[2][3];	

	double g_matrixMarker1color[3] = {1.0, 0.0, 1.0};	//starting values of markers color
	double g_matrixMarker2color[3] = {0.0, 1.0, 0.0};	//
//end - interface 3D



////user interface - setting & options

	//on/off windows
		bool g_bInterfaceShowOpenCVWinRightView = 0,
			 g_bInterfaceShowOpenCVWinLeftView = 1,
			 g_bInterfaceShowViewOnlyMasks = 0,
			 g_bInterfaceShowViewHue = 0,
			 g_bInterfaceShowViewSaturation = 0,
			 g_bInterfaceShowViewValue = 0,
			 g_bInterfaceShowViewRed = 0,
			 g_bInterfaceShowViewGreen = 0,
			 g_bInterfaceShowViewBlue = 0,
			 g_bInterfaceShowViewWithoutBackground = 0,
			 g_bInterfaceShowViewColorSeparationWithoutBackground = 0,
			 g_bInterfaceShowViewColorSeparationWithoutBackgroundClosed = 0,
			 g_bInterfaceShowViewColorSeparationWithoutBackgroundClosedSegment = 0;

	bool g_bIfDrumsListNeedToRefresh = true;
	bool g_bIfDrumsAllArePlaced = false;
	bool g_bRefreshingAutoProcessingParameters = false;

	bool g_bIfProgramClosing = false;
	bool g_bIfMainLoopStopped = false;

	char g_cMessages[1024] = " no message written ";

	//processing options
		bool g_bUseBackgroundSubtraction = 1,
			g_bLookOnMarkerSaturation = 0;

		//codebook parameters start setup
		int g_iCodeBookModMin = 6, g_iCodeBookModMax = 6, g_iCodeBookCbBounds = 12;
		int g_iNumberFramesToLearnBG = 200;

		//camera acquisition parameters
		int g_iCamerasMainLoopResolutionWidth = 320, g_iCamerasMainLoopResolutionHeight = 240;

		//color separating parameters
		double g_dColorFactorBounds = 2.5, g_dSaturationFactorBounds = 2.5;

		//auto adjust processing parameters
		double g_dAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust = 0.005,	//experimentally fixed // g_dAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust = 0.005 because of max acceptable 0.5% noise
				g_dAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust = 0.002,	//experimentally fixed //g_dAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust = 0.002 because of max acceptable 0.2% noise at final picture
				g_dAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust = 0.6,	//experimentally fixed
				g_dAutoAdjustGoodResultsPercentageAfterColorFactorAdjust = 0.85;	//experimentally fixed

		bool g_bIfPositionMarker1Measure = false;	//for measuring precision of marker position

	//int g_iTimeDelay = 0;
	//int g_iTimeDelayAvg = 0;
	//bool g_bIfTimeDelayNeedReset = 0;

//end - user interface - setting & options
