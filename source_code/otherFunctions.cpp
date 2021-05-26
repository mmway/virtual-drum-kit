#include "stdafx.h"

#include <math.h>

#include "opencv/cvaux.h"
#include "opencv/cxmisc.h"
#include "opencv/highgui.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



void drawBox( IplImage* _Imask, CvRect _Box, int _howFilled ) {

    cvRectangle (
                _Imask,
                cvPoint(_Box.x,_Box.y),
                cvPoint(_Box.x+_Box.width,_Box.y+_Box.height),
                cvScalar(0xff,0xff,0xff), /* red */
                _howFilled
                );
}


std::string mmToStdString(System::String^ source){
    std::string result;
    int len = source->Length;
    for(int i=0; i<len; i++)
        result += (char)source[i];
    return result;
}


System::String^ mmToSysString(std::string source){
    System::String^ result;
    int len = (int)source.length();
    for(int i=0; i<len; i++)
        result += (wchar_t)source[i];
    return result;
}


void mmHSVtoRGB(double _dHue, double _dSat, double _dVal, double &_dRed, double &_dGrn, double &_dBlu){

	if(_dVal == 0) {
		_dRed=0; 
		_dGrn=0; 
		_dBlu=0;
	}
	else{
	 _dHue /= 60;
	 int _i = cvFloor(_dHue);
	 double _dF = _dHue-_i;
	 double _dP = _dVal* (1 - _dSat);
	 double _dQ = _dVal* (1 - (_dSat * _dF));
	 double _dT = _dVal* (1 - (_dSat * (1 - _dF)));

	 if (_i==0)		 {_dRed = _dVal;	_dGrn = _dT;	_dBlu = _dP;}
	 else if (_i==1) {_dRed = _dQ;		_dGrn = _dVal;	_dBlu = _dP;}
	 else if (_i==2) {_dRed = _dP;		_dGrn = _dVal;	_dBlu = _dT;}
	 else if (_i==3) {_dRed = _dP;		_dGrn = _dQ;	_dBlu = _dVal;}
	 else if (_i==4) {_dRed = _dT;		_dGrn = _dP;	_dBlu = _dVal;}
	 else if (_i==5) {_dRed = _dVal;	_dGrn = _dP;	_dBlu = _dQ;}
	}

}


void mmIloczWekt(double ux, double uy, double uz,
			   double wx, double wy, double wz,
			   double *qx, double *qy, double *qz){

	*qx=(uy*wz)-(uz*wy);
	*qy=(uz*wx)-(ux*wz);
	*qz=(ux*wy)-(uy*wx);
}


double mmVectorLenght(double ux, double uy, double uz){

	double scalar = pow(ux,2) + pow(uy,2) + pow(uz,2);

	return sqrt(scalar);
}
