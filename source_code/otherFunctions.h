#ifndef _OTHERFUNCTIONS_H
#define	_OTHERFUNCTIONS_H


void drawBox( IplImage* _Imask, CvRect _Box, int _howFilled );

System::String^ mmToSysString(std::string source);
std::string mmToStdString(System::String^ source);

double mmVectorLenght(double ux, double uy, double uz);

void mmIloczWekt(double ux, double uy, double uz,
			   double wx, double wy, double wz,
			   double *qx, double *qy, double *qz);

void mmHSVtoRGB(double _dHue, double _dSat, double _dVal, double &_dRed, double &_dGrn, double &_dBlu);


#endif	/* _OTHERFUNCTIONS_H */

