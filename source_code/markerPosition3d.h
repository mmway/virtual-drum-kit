#ifndef _MARKERPOSITION3D_H
#define	_MARKERPOSITION3D_H

class mmLine{
	public:
		CvPoint3D64f pointOn;	//point on line
		CvPoint3D64f vectorDir;	//line direction vector
};

class mmPlane{
	public:
		double a1,b1,c1,d1;
};

class mmDrum;


int mmFindMarkerPosition( double _dMarkerPositionOnImagerX1, double _dMarkerPositionOnImagerY1, 
						double _dMarkerPositionOnImagerX2, double _dMarkerPositionOnImagerY2, 
						double _dSensorPixelDimensionX1, double _dSensorPixelDimensionY1, 
						double _dSensorPixelDimensionX2, double _dSensorPixelDimensionY2, 
						double _dFocalLenght1, 
						double _dFocalLenght2, 
						double _matrixRotationHalfPlus[][3], double _matrixRotationHalfMinus[][3], double _matrixTranslationHalf[],
						double (&_matrixMarkerPosition3D)[3], double (&_matrixMarkerPosition3DPrev)[3], double (&_matrixMarkerPosition3DPrevPrev)[3],
						int _iMarkerNumber);


int mmComputeDimensionsOfImageOfSensor( int _iImageWidth, int _iImageHeight, 
										double _dAngleOfSeeingInRad, 
										double _dDistanceOfSensorImageD,
										double &_dDimensionOfImgOfSensorX, double &_dDimensionOfImgOfSensorY);

int mmFindPlaneParameters(CvPoint3D64f _ptPointOnPlane, CvPoint3D64f _ptVectorDir, mmPlane *_plPlane);

void mmIfMarkerCutDrumPlane(mmDrum *_drumTemp, double (&_matrixMarkerPosition3D)[3], double (&_matrixMarkerPosition3Dprev)[3] );



#endif	/* _MARKERPOSITION3D_H */