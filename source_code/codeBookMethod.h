#ifndef _CODEBOOKMETHOD_H
#define	_CODEBOOKMETHOD_H

void mmLearnBackgroundCodeBook (CvCapture* capture, CvBGCodeBookModel* model, IplImage *_IundistortMapX, IplImage *_IundistortMapY );

void mmUpdateBackgroundCodeBook (IplImage* _I, IplImage* _ImaskMarkers, CvBGCodeBookModel* model, int _iFrameCount, int _iFps );

void mmChangeCodeBookParam(CvBGCodeBookModel* _model, int _iModMin, int _iModMax, int _iCbBounds);

bool mmAutoAdjustImagesProcessingPrameters(IplImage *_I1maskMarkersFinal, IplImage *_I2maskMarkersFinal,
										int _iFrameCount, int _iFps, 
										CvBGCodeBookModel* _backgroundModelCamera1, CvBGCodeBookModel* _backgroundModelCamera2,
										int &_iCodeBookModMin, int &_iCodeBookModMax, double &_dColorFactorBounds);

#endif	/* _CODEBOOKMETHOD_H */

