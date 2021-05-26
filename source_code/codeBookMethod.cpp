#include "stdafx.h"

#include <opencv/cvaux.h>
#include <opencv/cxmisc.h>
#include <opencv/highgui.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "VirtualDrums_Globals.h"





void mmUpdateBackgroundCodeBook (IplImage* _IyuvImage, IplImage* _ImaskMarkers, CvBGCodeBookModel* _modelCodebook, int _iFrameCount, int _iFps )
{

    int _iUpdateIter = 0.25*_iFps+1.0;      // how often cvBGCodeBookUpdate, it is "+1" because of have to be non-zero to avid "divide by zero error"
    int _iClearIter = 30*_iFps+1.0;     // how often cvBGCodeBookClearStale is lunching, , it is "+1" because of have to be non-zero to avid "divide by zero error"

	IplImage *_ImaskMarkersInvert = 0;
	_ImaskMarkersInvert = cvCloneImage(_ImaskMarkers);

	cvSet(_ImaskMarkersInvert, cvScalar(1.0), NULL);
	cvSet(_ImaskMarkersInvert, cvScalar(0.0), _ImaskMarkers);


    if(_IyuvImage){
        
       if ( _iFrameCount % _iUpdateIter == 0.0)
			cvBGCodeBookUpdate( _modelCodebook, _IyuvImage, cvRect(0,0,0,0), _ImaskMarkersInvert );

       if (_iFrameCount % _iClearIter == 0.0)
		   cvBGCodeBookClearStale( _modelCodebook, _modelCodebook->t*0.90 );	//0.75 - to clear from background-model olny those entries that were very short time "as background" - like markers

    }
	cvReleaseImage( &_ImaskMarkersInvert);

}



void mmLearnBackgroundCodeBook (CvCapture* _capture, CvBGCodeBookModel* _modelCodebook, IplImage *_IundistortMapX, IplImage *_IundistortMapY )
{

    IplImage *_IrawImage = 0, *_IyuvImage = 0; //hsvImage is for codebook method
	IplImage *_Itemp;

    int _iNframes = 0;


    //Set color thresholds to default values
    _modelCodebook->modMin[0] = _modelCodebook->modMin[1] = _modelCodebook->modMin[2] = 4;
    _modelCodebook->modMax[0] = _modelCodebook->modMax[1] = _modelCodebook->modMax[2] = 6;
    _modelCodebook->cbBounds[0] = _modelCodebook->cbBounds[1] = _modelCodebook->cbBounds[2] = 20;

    //MAIN PROCESSING LOOP:
    for(_iNframes=0; _iNframes<=g_iNumberFramesToLearnBG; )
    {

            _IrawImage = cvQueryFrame( _capture );
			_Itemp = cvCloneImage(_IrawImage);

			//if there where calibration process
			if (_IundistortMapX && _IundistortMapY){
				cvRemap(_Itemp, _IrawImage, _IundistortMapX, _IundistortMapY);
			}

            ++_iNframes;
            if(!_IrawImage)
                break;

        //First time:
        if( _iNframes == 1 && _IrawImage )
            _IyuvImage = cvCloneImage(_IrawImage);

        // If we've got an _IrawImage and are good to go:
        if( _IrawImage )
        {
			cvCvtColor( _IrawImage, _IyuvImage, CV_BGR2YCrCb );//YUV For codebook method to separate Luminance from other channels
            //This is where we build our background model
            if( _iNframes-1 < g_iNumberFramesToLearnBG  )
				cvBGCodeBookUpdate( _modelCodebook, _IyuvImage );

            if( _iNframes-1 == g_iNumberFramesToLearnBG  )
                cvBGCodeBookClearStale( _modelCodebook, _modelCodebook->t*0.95 );	//to remember almost all objects from background on learing - reject only true foreground

        }

    }

	g_iNumberFramesToLearnBG = 0;

}




void mmChangeCodeBookParam(CvBGCodeBookModel* _modelCodebook, int _iModMin, int _iModMax, int _iCbBounds){

    //Set color thresholds to default values
    _modelCodebook->modMin[0] = _modelCodebook->modMin[1] = _modelCodebook->modMin[2] = _iModMin;
    _modelCodebook->modMax[0] = _modelCodebook->modMax[1] = _modelCodebook->modMax[2] = _iModMax;
    _modelCodebook->cbBounds[0] = _modelCodebook->cbBounds[1] = _modelCodebook->cbBounds[2] = _iCbBounds;


}


int l_iWhichStepOfAutoAdjust = 0;
int l_iAdjustingModMinModMaxInterval = 0;
int l_iAdjustingHowManyGoodResults = 0, l_iAdjustingHowManyResults = 0;

bool mmAutoAdjustImagesProcessingPrameters(IplImage *_I1maskMarkersFinal, IplImage *_I2maskMarkersFinal,
										int _iFrameCount, int _iFps, 
										CvBGCodeBookModel *_backgroundModelCamera1, CvBGCodeBookModel *_backgroundModelCamera2,
										int &_iCodeBookModMin, int &_iCodeBookModMax, double &_dColorFactorBounds){

	int _iI1NonZeroPixels = 0, _iI2NonZeroPixels = 0;

	if (l_iWhichStepOfAutoAdjust <=1){
		_iI1NonZeroPixels = cvCountNonZero(_I1maskMarkersFinal);
		_iI2NonZeroPixels = cvCountNonZero(_I2maskMarkersFinal);
	}


	////adjusting modMin modMax of codebook method of substracking background
		if (l_iWhichStepOfAutoAdjust == 0){

			if ( (double(double(_iI1NonZeroPixels)/double(_I1maskMarkersFinal->width*_I1maskMarkersFinal->height)) <= g_dAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust) &&
				 (double(double(_iI2NonZeroPixels)/double(_I2maskMarkersFinal->width*_I2maskMarkersFinal->height)) <= g_dAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust) ){	

					 l_iAdjustingHowManyGoodResults++;
			}
			l_iAdjustingHowManyResults++;

			if (l_iAdjustingHowManyResults % (4*(_iFps+5)) == 0){	//checking for 4sec of learing (5*_iFps) how many there where good pictures

				if ( (double(l_iAdjustingHowManyGoodResults)/double(l_iAdjustingHowManyResults) >= g_dAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust) || (_iCodeBookModMax >= 10) ){
					l_iWhichStepOfAutoAdjust++;	//going to next step of auto adjusting

					l_iAdjustingHowManyGoodResults = 0;	//reseting before next step od adjustment
					l_iAdjustingHowManyResults = 0;
				}
				else{
					_iCodeBookModMin++;
					_iCodeBookModMax++;
				}

			}

		}
	//end - adjusting modMin modMax of codebook method of substracking background


	////adjusting colorFactorBounds of color searching
		if (l_iWhichStepOfAutoAdjust == 1){

			if ( (double(double(_iI1NonZeroPixels)/double(_I1maskMarkersFinal->width*_I1maskMarkersFinal->height)) <= g_dAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust) &&
				 (double(double(_iI2NonZeroPixels)/double(_I2maskMarkersFinal->width*_I2maskMarkersFinal->height)) <= g_dAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust) ){	

					 l_iAdjustingHowManyGoodResults++;
			}
			l_iAdjustingHowManyResults++;

			if (l_iAdjustingHowManyResults % (4*(_iFps+5)) == 0){	//checking for 4sec of learing (4*_iFps) how many there where good pictures

				if ( (double(l_iAdjustingHowManyGoodResults)/double(l_iAdjustingHowManyResults) >= g_dAutoAdjustGoodResultsPercentageAfterColorFactorAdjust) || (_dColorFactorBounds <= 0.5) ){
					l_iWhichStepOfAutoAdjust = 0;

					l_iAdjustingHowManyGoodResults = 0;	//reseting before next step od adjustment
					l_iAdjustingHowManyResults = 0;

					g_bRefreshingAutoProcessingParameters = false;

					return true;
				}
				else{
					_dColorFactorBounds -= 0.2;
				}

			}

		}
	//end - adjusting _dColorFactorBounds of color searching

	return false;
}
