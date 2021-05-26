#include "stdafx.h"

#include <math.h>
#include "opencv/cv.h"

#include "otherFunctions.h"
#include "VirtualDrums_Globals.h"
#include "markerPosition3d.h"



CvPoint3D64f l_ptTemp;

int mmComputeDimensionsOfImageOfSensor( int _iImageWidth, int _iImageHeight, 
										 double _dAngleOfSeeingInRad, 
										 double _dDistanceOfSensorImageD,
										 double &_dDimensionOfImgOfSensorX, double &_dDimensionOfImgOfSensorY){

	_dDimensionOfImgOfSensorX = 8.0*_dDistanceOfSensorImageD*tan(_dAngleOfSeeingInRad/2.0)/5.0/double(_iImageWidth);
	_dDimensionOfImgOfSensorY = 6.0*_dDistanceOfSensorImageD*tan(_dAngleOfSeeingInRad/2.0)/5.0/double(_iImageHeight);

	return 0;
}


int mmMakeLineFromPointAndVector(mmLine _linPointFromThisLine, mmLine _linVectorFromThisLine, mmLine *_linLineOut){

	_linLineOut->pointOn.x = _linPointFromThisLine.pointOn.x;
	_linLineOut->pointOn.y = _linPointFromThisLine.pointOn.y;
	_linLineOut->pointOn.z = _linPointFromThisLine.pointOn.z;

	_linLineOut->vectorDir.x = _linVectorFromThisLine.vectorDir.x;
	_linLineOut->vectorDir.y = _linVectorFromThisLine.vectorDir.y;
	_linLineOut->vectorDir.z = _linVectorFromThisLine.vectorDir.z;

	return 0;
}

int mmFindPointOnLine(mmLine *_linLinePointThisLine, double _dTparameter){

	mmLine _linTemp;

	_linTemp.pointOn.x = _linLinePointThisLine->pointOn.x + _dTparameter*_linLinePointThisLine->vectorDir.x;
	_linTemp.pointOn.y = _linLinePointThisLine->pointOn.y + _dTparameter*_linLinePointThisLine->vectorDir.y;
	_linTemp.pointOn.z = _linLinePointThisLine->pointOn.z + _dTparameter*_linLinePointThisLine->vectorDir.z;

	_linLinePointThisLine->pointOn.x = _linTemp.pointOn.x;
	_linLinePointThisLine->pointOn.y = _linTemp.pointOn.y;
	_linLinePointThisLine->pointOn.z = _linTemp.pointOn.z;

	return 0;
}


int mmFindPlaneParameters(CvPoint3D64f _ptPointOnPlane, CvPoint3D64f _ptVectorDir, mmPlane *_plPlane){

	_plPlane->a1 = _ptVectorDir.x;
	_plPlane->b1 = _ptVectorDir.y;
	_plPlane->c1 = _ptVectorDir.z;

	_plPlane->d1 = -(_plPlane->a1 * _ptPointOnPlane.x) - (_plPlane->b1 * _ptPointOnPlane.y) - (_plPlane->c1 * _ptPointOnPlane.z) ;

	return 0;
}


int mmFindPlaneAndLineCrossPoint(mmLine _linLine , mmPlane _plPlane, mmLine *_linLineOut){
	double _dTparameter;
	
	_dTparameter = - ( (_plPlane.a1*_linLine.pointOn.x)+(_plPlane.b1*_linLine.pointOn.y)+(_plPlane.c1*_linLine.pointOn.z)+_plPlane.d1 )
					/
					( (_plPlane.a1*_linLine.vectorDir.x)+(_plPlane.b1*_linLine.vectorDir.y)+(_plPlane.c1*_linLine.vectorDir.z) );

	_linLineOut->pointOn.x = _linLine.pointOn.x + _dTparameter*_linLine.vectorDir.x;
	_linLineOut->pointOn.y = _linLine.pointOn.y + _dTparameter*_linLine.vectorDir.y;
	_linLineOut->pointOn.z = _linLine.pointOn.z + _dTparameter*_linLine.vectorDir.z;

	return 0;
}


int mmFindLineAndLineCrossPoint(mmLine _linLine1, mmLine _linLine2, mmLine *_linPointOut){
	double _dTparameter;
	
	if ( (_linLine1.vectorDir.x!=0) && (_linLine2.vectorDir.y!=0) ){	// 1 variant

		_dTparameter = ( (_linLine1.pointOn.y/_linLine2.vectorDir.y) 
							+ (_linLine1.vectorDir.y*_linLine2.pointOn.x/(_linLine1.vectorDir.x*_linLine2.vectorDir.y))
							- (_linLine1.vectorDir.y*_linLine1.pointOn.x/(_linLine1.vectorDir.x*_linLine2.vectorDir.y)) 
							- (_linLine2.pointOn.y/_linLine2.vectorDir.y) )
						/ 
						( 1 - (_linLine1.vectorDir.y*_linLine2.vectorDir.x/(_linLine1.vectorDir.x*_linLine2.vectorDir.y)) );

	}
	else
		if ( (_linLine1.vectorDir.x!=0) && (_linLine2.vectorDir.z!=0) ){	// 2 variant

			_dTparameter = ( (_linLine1.pointOn.z/_linLine2.vectorDir.z) 
							+ (_linLine1.vectorDir.z*_linLine2.pointOn.x/(_linLine1.vectorDir.x*_linLine2.vectorDir.z))
							- (_linLine1.vectorDir.z*_linLine1.pointOn.x/(_linLine1.vectorDir.x*_linLine2.vectorDir.z)) 
							- (_linLine2.pointOn.z/_linLine2.vectorDir.z) )
						/ 
						( 1 - (_linLine1.vectorDir.z*_linLine2.vectorDir.x/(_linLine1.vectorDir.x*_linLine2.vectorDir.z)) );

		}
		else
			if ( (_linLine1.vectorDir.y!=0) && (_linLine2.vectorDir.x!=0) ){	// 3 variant

				_dTparameter = ( (_linLine1.pointOn.x/_linLine2.vectorDir.x) 
							+ (_linLine1.vectorDir.x*_linLine2.pointOn.y/(_linLine1.vectorDir.y*_linLine2.vectorDir.x))
							- (_linLine1.vectorDir.x*_linLine1.pointOn.y/(_linLine1.vectorDir.y*_linLine2.vectorDir.x)) 
							- (_linLine2.pointOn.x/_linLine2.vectorDir.y) )
						/ 
						( 1 - (_linLine1.vectorDir.y*_linLine2.vectorDir.x/(_linLine1.vectorDir.y*_linLine2.vectorDir.x)) );

			}
			else
				if ( (_linLine1.vectorDir.y!=0) && (_linLine2.vectorDir.z!=0) ){	// 4 variant

					_dTparameter = ( (_linLine1.pointOn.z/_linLine2.vectorDir.z) 
							+ (_linLine1.vectorDir.z*_linLine2.pointOn.y/(_linLine1.vectorDir.y*_linLine2.vectorDir.z))
							- (_linLine1.vectorDir.z*_linLine1.pointOn.y/(_linLine1.vectorDir.y*_linLine2.vectorDir.z)) 
							- (_linLine2.pointOn.z/_linLine2.vectorDir.z) )
						/ 
						( 1 - (_linLine1.vectorDir.z*_linLine2.vectorDir.y/(_linLine1.vectorDir.y*_linLine2.vectorDir.z)) );

				}
				else
					if ( (_linLine1.vectorDir.z!=0) && (_linLine2.vectorDir.x!=0) ){	// 5 variant

						_dTparameter = ( (_linLine1.pointOn.x/_linLine2.vectorDir.x) 
							+ (_linLine1.vectorDir.x*_linLine2.pointOn.z/(_linLine1.vectorDir.z*_linLine2.vectorDir.x))
							- (_linLine1.vectorDir.x*_linLine1.pointOn.z/(_linLine1.vectorDir.z*_linLine2.vectorDir.x)) 
							- (_linLine2.pointOn.x/_linLine2.vectorDir.x) )
						/ 
						( 1 - (_linLine1.vectorDir.x*_linLine2.vectorDir.y/(_linLine1.vectorDir.z*_linLine2.vectorDir.x)) );

					}
					else
						if ( (_linLine1.vectorDir.z!=0) && (_linLine2.vectorDir.y!=0) ){	// 6 variant

							_dTparameter = ( (_linLine1.pointOn.y/_linLine2.vectorDir.y) 
							+ (_linLine1.vectorDir.y*_linLine2.pointOn.z/(_linLine1.vectorDir.z*_linLine2.vectorDir.y))
							- (_linLine1.vectorDir.y*_linLine1.pointOn.z/(_linLine1.vectorDir.z*_linLine2.vectorDir.y)) 
							- (_linLine2.pointOn.y/_linLine2.vectorDir.y) )
						/ 
						( 1 - (_linLine1.vectorDir.y*_linLine2.vectorDir.z/(_linLine1.vectorDir.z*_linLine2.vectorDir.y)) );

						}

	_linPointOut->pointOn.x = _linLine2.pointOn.x + _dTparameter*_linLine2.vectorDir.x;
	_linPointOut->pointOn.y = _linLine2.pointOn.y + _dTparameter*_linLine2.vectorDir.y;
	_linPointOut->pointOn.z = _linLine2.pointOn.z + _dTparameter*_linLine2.vectorDir.z;


	return 0;
}


int mmFindMarkerPosition( double _dMarkerPositionOnImagerX1, double _dMarkerPositionOnImagerY1, 
						double _dMarkerPositionOnImagerX2, double _dMarkerPositionOnImagerY2, 
						double _dSensorPixelDimensionX1, double _dSensorPixelDimensionY1, 
						double _dSensorPixelDimensionX2, double _dSensorPixelDimensionY2, 
						double _dFocalLenght1, 
						double _dFocalLenght2, 
						double _matrixRotationHalfPlus[][3], double _matrixRotationHalfMinus[][3], double _matrixTranslationHalf[],
						double (&_matrixMarkerPosition3D)[3], double (&_matrixMarkerPosition3DPrev)[3], double (&_matrixMarkerPosition3DPrevPrev)[3],
						int _iMarkerNubmer){


	// allocating needed lines
	mmLine _linA, _linB, _linKL, _linLG, _linGH;
	mmLine _linTemp;

	// allocating needed planes
	mmPlane _plPlanePI;



	////creating line A - camera 1
		_linA.pointOn.x = -_matrixTranslationHalf[0];
		_linA.pointOn.y = -_matrixTranslationHalf[1];
		_linA.pointOn.z = -_matrixTranslationHalf[2];

		//vector with start in principle point and end in pixel on imager which is center of marker
			l_ptTemp.x = _dSensorPixelDimensionX1*_dMarkerPositionOnImagerX1;
			l_ptTemp.y = _dSensorPixelDimensionY1*_dMarkerPositionOnImagerY1;
			l_ptTemp.z = _dFocalLenght1;

		_linA.vectorDir.x = //l_ptTemp.x 
							+ l_ptTemp.x*_matrixRotationHalfPlus[0][0]
							+ l_ptTemp.y*_matrixRotationHalfPlus[1][0]
							+ l_ptTemp.z*_matrixRotationHalfPlus[2][0];
		_linA.vectorDir.y = //l_ptTemp.y
							+ l_ptTemp.x*_matrixRotationHalfPlus[0][1]
							+ l_ptTemp.y*_matrixRotationHalfPlus[1][1]
							+ l_ptTemp.z*_matrixRotationHalfPlus[2][1];
		_linA.vectorDir.z = //l_ptTemp.z
							+ l_ptTemp.x*_matrixRotationHalfPlus[0][2]
							+ l_ptTemp.y*_matrixRotationHalfPlus[1][2]
							+ l_ptTemp.z*_matrixRotationHalfPlus[2][2];

		
		if (_iMarkerNubmer == 1){
		////computing rays from principal point to marker
			g_matrixMarker1LineA[0][0] = _linA.pointOn.x;
			g_matrixMarker1LineA[0][1] = _linA.pointOn.y;
			g_matrixMarker1LineA[0][2] = _linA.pointOn.z;
			g_matrixMarker1LineA[1][0] = _linA.vectorDir.x*50.0 + _linA.pointOn.x;
			g_matrixMarker1LineA[1][1] = _linA.vectorDir.y*50.0 + _linA.pointOn.y;
			g_matrixMarker1LineA[1][2] = _linA.vectorDir.z*50.0 + _linA.pointOn.z;
		//end - computing rays from principal point to marker
		}
		if (_iMarkerNubmer == 2){
			////computing rays from principal point to marker
			g_matrixMarker2LineA[0][0] = _linA.pointOn.x;
			g_matrixMarker2LineA[0][1] = _linA.pointOn.y;
			g_matrixMarker2LineA[0][2] = _linA.pointOn.z;
			g_matrixMarker2LineA[1][0] = _linA.vectorDir.x*50.0 + _linA.pointOn.x;
			g_matrixMarker2LineA[1][1] = _linA.vectorDir.y*50.0 + _linA.pointOn.y;
			g_matrixMarker2LineA[1][2] = _linA.vectorDir.z*50.0 + _linA.pointOn.z;
			//end - computing rays from principal point to marker
		}

	// end - creating line A - camera 1

	////creating line B - camera 2
		_linB.pointOn.x = _matrixTranslationHalf[0];
		_linB.pointOn.y = _matrixTranslationHalf[1];
		_linB.pointOn.z = _matrixTranslationHalf[2];

		//vector with start in principle point and end in pixel on imager which is center of marker
			l_ptTemp.x = _dSensorPixelDimensionX2*_dMarkerPositionOnImagerX2;
			l_ptTemp.y = _dSensorPixelDimensionY2*_dMarkerPositionOnImagerY2;
			l_ptTemp.z = _dFocalLenght2;

		//inf camera 2 sing is 'minus' because of opposite rotation direction
		_linB.vectorDir.x = //l_ptTemp.x 
							+ l_ptTemp.x*_matrixRotationHalfMinus[0][0]
							+ l_ptTemp.y*_matrixRotationHalfMinus[1][0]
							+ l_ptTemp.z*_matrixRotationHalfMinus[2][0];
		_linB.vectorDir.y = //l_ptTemp.y
							+ l_ptTemp.x*_matrixRotationHalfMinus[0][1]
							+ l_ptTemp.y*_matrixRotationHalfMinus[1][1]
							+ l_ptTemp.z*_matrixRotationHalfMinus[2][1];
		_linB.vectorDir.z = //l_ptTemp.z
							+ l_ptTemp.x*_matrixRotationHalfMinus[0][2]
							+ l_ptTemp.y*_matrixRotationHalfMinus[1][2]
							+ l_ptTemp.z*_matrixRotationHalfMinus[2][2];


		if (_iMarkerNubmer == 1){
		////computing rays from principal point to marker
			g_matrixMarker1LineB[0][0] = _linB.pointOn.x;
			g_matrixMarker1LineB[0][1] = _linB.pointOn.y;
			g_matrixMarker1LineB[0][2] = _linB.pointOn.z;
			g_matrixMarker1LineB[1][0] = _linB.vectorDir.x*50.0 + _linB.pointOn.x;
			g_matrixMarker1LineB[1][1] = _linB.vectorDir.y*50.0 + _linB.pointOn.y;
			g_matrixMarker1LineB[1][2] = _linB.vectorDir.z*50.0 + _linB.pointOn.z;
		//end - computing rays from principal point to marker
		}
		if (_iMarkerNubmer == 2){
		////computing rays from principal point to marker
			g_matrixMarker2LineB[0][0] = _linB.pointOn.x;
			g_matrixMarker2LineB[0][1] = _linB.pointOn.y;
			g_matrixMarker2LineB[0][2] = _linB.pointOn.z;
			g_matrixMarker2LineB[1][0] = _linB.vectorDir.x*50.0 + _linB.pointOn.x;
			g_matrixMarker2LineB[1][1] = _linB.vectorDir.y*50.0 + _linB.pointOn.y;
			g_matrixMarker2LineB[1][2] = _linB.vectorDir.z*50.0 + _linB.pointOn.z;
		//end - computing rays from principal point to marker
		}

	// end - creating line B - camera 2



	//computing normal vector of plane
	mmIloczWekt(_linA.vectorDir.x, _linA.vectorDir.y, _linA.vectorDir.z,
				 _linB.vectorDir.x, _linB.vectorDir.y, _linB.vectorDir.z,
				 &_linKL.vectorDir.x, &_linKL.vectorDir.y, &_linKL.vectorDir.z);

	//creating lineKL
	mmMakeLineFromPointAndVector(_linA, _linKL, &_linKL);

	//creating plane PI
	mmFindPlaneParameters( cvPoint3D64f(_linB.pointOn.x, _linB.pointOn.y, _linB.pointOn.z),
							cvPoint3D64f(_linKL.vectorDir.x, _linKL.vectorDir.y, _linKL.vectorDir.z),
							&_plPlanePI);

	//finding point L
	mmFindPlaneAndLineCrossPoint(_linKL, _plPlanePI, &_linLG);

	//creating lineLG
	mmMakeLineFromPointAndVector(_linLG, _linA, &_linLG);


	//finding point G
	mmFindLineAndLineCrossPoint(_linLG, _linB, &_linGH);

	//creating lineGH
	mmMakeLineFromPointAndVector(_linGH, _linKL, &_linGH);

	//finding point H
	mmFindLineAndLineCrossPoint(_linGH, _linA, &_linA);

	////before computing new markers positions remeber old ones
		_matrixMarkerPosition3DPrevPrev[0] = _matrixMarkerPosition3DPrev[0];
		_matrixMarkerPosition3DPrevPrev[1] = _matrixMarkerPosition3DPrev[1];
		_matrixMarkerPosition3DPrevPrev[2] = _matrixMarkerPosition3DPrev[2];

		_matrixMarkerPosition3DPrev[0] = _matrixMarkerPosition3D[0];
		_matrixMarkerPosition3DPrev[1] = _matrixMarkerPosition3D[1];
		_matrixMarkerPosition3DPrev[2] = _matrixMarkerPosition3D[2];
	//end - before computing new markers positions remeber old ones

	////computing lines A & B "crosspoint"
		_linTemp.vectorDir.x = _linA.pointOn.x - _linGH.pointOn.x;
		_linTemp.vectorDir.y = _linA.pointOn.y - _linGH.pointOn.y;
		_linTemp.vectorDir.z = _linA.pointOn.z - _linGH.pointOn.z;

		_matrixMarkerPosition3D[0] = _linGH.pointOn.x + _linTemp.vectorDir.x;
		_matrixMarkerPosition3D[1] = _linGH.pointOn.y + _linTemp.vectorDir.y;
		_matrixMarkerPosition3D[2] = _linGH.pointOn.z + _linTemp.vectorDir.z;
	//end - computing lines A & B "crosspoint"



	return 0;
}

void mmIfMarkerCutDrumPlane(mmDrum *_drumTemp, double (&_matrixMarkerPosition3D)[3], double (&_matrixMarkerPosition3Dprev)[3] ){

	mmLine _linMabMcd, _linMbcMda;
	mmLine _linMab, _linMbc, _linMcd, _linMda;	//used "pointOn" only for store points on a drum edges
	mmLine _linTemp, _linTempCrosspoint;
	mmPlane _plTemp;

	_linTemp.pointOn.x = _matrixMarkerPosition3D[0];
	_linTemp.pointOn.y = _matrixMarkerPosition3D[1];
	_linTemp.pointOn.z = _matrixMarkerPosition3D[2];

	_linTemp.vectorDir.x = _matrixMarkerPosition3D[0] - _matrixMarkerPosition3Dprev[0];
	_linTemp.vectorDir.y = _matrixMarkerPosition3D[1] - _matrixMarkerPosition3Dprev[1];
	_linTemp.vectorDir.z = _matrixMarkerPosition3D[2] - _matrixMarkerPosition3Dprev[2];

	//computing cross point 
		mmFindPlaneAndLineCrossPoint(_linTemp, _drumTemp->_plABCDcenterPlane, &_linTempCrosspoint);


	////computing lines parallel to axies and crossing markerPoint
		_linMabMcd.pointOn.x = _matrixMarkerPosition3D[0];
		_linMabMcd.pointOn.y = _matrixMarkerPosition3D[1];
		_linMabMcd.pointOn.z = _matrixMarkerPosition3D[2];

		_linMabMcd.vectorDir.x = _drumTemp->linBC.vectorDir.x;
		_linMabMcd.vectorDir.y = _drumTemp->linBC.vectorDir.y;
		_linMabMcd.vectorDir.z = _drumTemp->linBC.vectorDir.z;


		_linMbcMda.pointOn.x = _matrixMarkerPosition3D[0];
		_linMbcMda.pointOn.y = _matrixMarkerPosition3D[1];
		_linMbcMda.pointOn.z = _matrixMarkerPosition3D[2];

		_linMbcMda.vectorDir.x = _drumTemp->linCD.vectorDir.x;
		_linMbcMda.vectorDir.y = _drumTemp->linCD.vectorDir.y;
		_linMbcMda.vectorDir.z = _drumTemp->linCD.vectorDir.z;
	//end - computing lines parallel to axies and crossing markerPoint

	////computing point of crossing above line with a drum edges
		mmFindLineAndLineCrossPoint(_linMabMcd, _drumTemp->linAB, &_linMab);
		mmFindLineAndLineCrossPoint(_linMabMcd, _drumTemp->linCD, &_linMcd);
		mmFindLineAndLineCrossPoint(_linMbcMda, _drumTemp->linBC, &_linMbc);
		mmFindLineAndLineCrossPoint(_linMbcMda, _drumTemp->linDA, &_linMda);
	//end - computing point of crossing above line with drum planes


	_drumTemp->ptMab.x = _linMab.pointOn.x;
	_drumTemp->ptMab.y = _linMab.pointOn.y;
	_drumTemp->ptMab.z = _linMab.pointOn.z;
	_drumTemp->ptMbc.x = _linMbc.pointOn.x;
	_drumTemp->ptMbc.y = _linMbc.pointOn.y;
	_drumTemp->ptMbc.z = _linMbc.pointOn.z;
	_drumTemp->ptMcd.x = _linMcd.pointOn.x;
	_drumTemp->ptMcd.y = _linMcd.pointOn.y;
	_drumTemp->ptMcd.z = _linMcd.pointOn.z;
	_drumTemp->ptMda.x = _linMda.pointOn.x;
	_drumTemp->ptMda.y = _linMda.pointOn.y;
	_drumTemp->ptMda.z = _linMda.pointOn.z;
	_drumTemp->ptCrossPoint.x = _linTempCrosspoint.pointOn.x;
	_drumTemp->ptCrossPoint.y = _linTempCrosspoint.pointOn.y;
	_drumTemp->ptCrossPoint.z = _linTempCrosspoint.pointOn.z;


	//checking if marker previous and actual positions cuts drums plane
	if ( ((_matrixMarkerPosition3D[1] <= _linTempCrosspoint.pointOn.y) && (_linTempCrosspoint.pointOn.y <= _matrixMarkerPosition3Dprev[1])) &&
		 ((_linMab.pointOn.x <= _linTempCrosspoint.pointOn.x) && (_linTempCrosspoint.pointOn.x <=_linMcd.pointOn.x)) &&
		 ((_linMbc.pointOn.z <= _linTempCrosspoint.pointOn.z) && (_linTempCrosspoint.pointOn.z <=_linMda.pointOn.z)) &&
		 ( (((_linMab.pointOn.y-5) <= _linTempCrosspoint.pointOn.y) && (_linTempCrosspoint.pointOn.y <=(_linMcd.pointOn.y+5))) || (((_linMab.pointOn.y+5) >= _linTempCrosspoint.pointOn.y) && (_linTempCrosspoint.pointOn.y >=(_linMcd.pointOn.y-5))) ) &&
		 ( (((_linMbc.pointOn.y-5) <= _linTempCrosspoint.pointOn.y) && (_linTempCrosspoint.pointOn.y <=(_linMda.pointOn.y+5))) || (((_linMbc.pointOn.y+5) >= _linTempCrosspoint.pointOn.y) && (_linTempCrosspoint.pointOn.y >=(_linMda.pointOn.y-5))) ) ){

		//g_bIfTimeDelayNeedReset=1;

		_drumTemp->ifDrumIsHitted = true;
		_drumTemp->iTimesHitted++;
		_drumTemp->iTimeToLightOff = cvRound(0.15*g_iCamera1FPS);	// setting up time variable 0.15 because we want to light up drum, when hitted, for 0.15 sec
	}


}