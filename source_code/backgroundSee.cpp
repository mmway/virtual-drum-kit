//Global storage
//
//Float, 3-channel images
//


#include "stdafx.h"

#include <stdlib.h>
//#include <iostream.h>
#include <cv.h>
#include <highgui.h>
#include "cv.h"
#include "highgui.h"
#include "cvaux.h"
#include "cxcore.h"


//IplImage *IavgF;//*IdiffF, *IprevF, *IhiF, *IlowF;

IplImage *Iscratch, *IaccBg, *ImaskBG1; // *Iscratch2,*Iscratch3;
//Float, 1-channel images
//
//IplImage *Igray1,*Igray2, *Igray3;
//IplImage *Ilow1, *Ilow2, *Ilow3;
//IplImage *Ihi1, *Ihi2, *Ihi3;
IplImage *IdiffLuminanceF; // *IscratchF1, *IscratchF2, *IscratchF3, *IscratchF;
IplImage *Idiff1F, *Idiff2F, *Idiff3F;
// Byte, 1-channel image
//
//IplImage *Imaskt,*g_8uImaskt1,*g_8uImaskt2,*g_8uImaskt3;
IplImage *Iscratch_8u;
IplImage *IoneChannelMaskt;
//Counts number of images learned for averaging later.
//

//double g_dDark = 0;
//double g_dLight = 0;


float Icount;

// I is just a sample image for allocation purposes
// (passed in for sizing)
//
void AllocateImagesBG( IplImage* I ){
CvSize sz = cvGetSize( I );
//IavgF = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
//IdiffF = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
//IprevF = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
//IhiF = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
//IlowF = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
//Ilow1 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
//Ilow2 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
//Ilow3 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
//Ihi1 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
//Ihi2 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
//Ihi3 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
Idiff1F = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
Idiff2F = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
Idiff3F = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
IdiffLuminanceF = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
ImaskBG1 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
//IscratchF1 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
//IscratchF2 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
//IscratchF3 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
//IscratchF = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
//cvZero( IavgF );
//cvZero( IdiffF );
cvZero( IdiffLuminanceF );
//cvZero( IprevF );
//cvZero( IhiF );
//cvZero( IlowF );
//cvZero( IscratchF1 );
//cvZero( IscratchF2 );
//cvZero( IscratchF3 );
//cvZero( IscratchF );
Icount = 0.00001; //Protect against divide by zero
Iscratch = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
//Iscratch2 = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
//Iscratch3 = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
IaccBg = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
//Igray1 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
//Igray2 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
//Igray3 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
//Imaskt = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
//g_8uImaskt1 = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
//g_8uImaskt2 = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
//g_8uImaskt3 = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
Iscratch_8u = cvCreateImage( sz, IPL_DEPTH_8U, 3 );
IoneChannelMaskt = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
cvZero( Iscratch );
cvZero( Iscratch_8u );
//cvZero( Iscratch2 );
//cvZero( Iscratch3 );
cvZero( IaccBg );
}



void accumulateBackground( IplImage *IprevF, IplImage *I, IplImage *IdiffF, IplImage *IavgF, int __iFrameCount ){

//    static int first = 1; // nb. Not thread safe

//    IplImage *Itemp, *Itemp2;
    //cvZero(Itemp);
    //cvZero(Itemp2);

//    CvSize sz = cvGetSize( I );
//    Itemp = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
//    Itemp2 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );

    cvCvtScale( I, IaccBg, 1, 0 ); // convert to float
    
//
//    cvCvtColor(IaccBg,Itemp,CV_RGB2GRAY);
//    cvCvtColor(IaccBg,Itemp2,CV_RGB2GRAY);
//
//    cvInRangeS(Itemp, cvScalar(g_dDark*255), cvScalar(g_dLight*255), g_8uImaskt1);
//    cvThreshold(g_8uImaskt1, g_8uImaskt1, 100, 1, CV_THRESH_BINARY); // because 255->1 and 0->0
//    cvCvtScale(g_8uImaskt1, Itemp, 1, 0);
//
//    cvMul(Itemp2,Itemp,Itemp2,1);
//
//    cvCvtColor(Itemp2,IaccBg,CV_GRAY2RGB);

    cvAcc( IaccBg, IavgF );


    if( __iFrameCount > 0 ){

    cvScale(IavgF, IavgF, 0.5);

    cvAbsDiff( IaccBg, IprevF, Iscratch );


    cvAcc( Iscratch, IdiffF );
    Icount += 1.0;
    
    }

//    first = 0;
    //cvCopy( IaccBg, IprevF );

    //cvScale(IaccBg, IaccBg, 0.00392, 0);    //change to cvShowImage

    //cvSaveImage("x.jpg", IdiffF);

//    cvReleaseImage(&Itemp);
//    cvReleaseImage(&Itemp2);

}

/*
void setHighThreshold( float scale )
{
cvConvertScale( IdiffF, Iscratch, scale );
cvAdd( Iscratch, IavgF, IhiF );
cvSplit( IhiF, Ihi1, Ihi2, Ihi3, 0 );
}
void setLowThreshold( float scale )
{
cvConvertScale( IdiffF, Iscratch, scale );
cvSub( IavgF, Iscratch, IlowF );
cvSplit( IlowF, Ilow1, Ilow2, Ilow3, 0 );
}
*/

/*void createModelsfromStats() {
cvConvertScale( IavgF, IavgF,( double)(1.0/Icount) );
cvConvertScale( IdiffF, IdiffF,(double)(1.0/Icount) );
//Make sure diff is always something
//
cvAddS( IdiffF, cvScalar( 1.0, 1.0, 1.0), IdiffF );
setHighThreshold( 7.0 );
setLowThreshold( 6.0 );
}*/

void findConstPix( IplImage *I, int _iMaxWantedRel ){
    double _dMinVal, _dMaxVal, _dMaxWanted;     //, val0, val1, val2, val3;
    //unsigned int _uiMinValRel, _uiMaxValRel;


    cvSplit(I,Idiff1F,Idiff2F,Idiff3F,NULL);


    cvAcc(Idiff1F, IdiffLuminanceF, NULL);
    cvAcc(Idiff2F, IdiffLuminanceF, NULL);
    cvAcc(Idiff3F, IdiffLuminanceF, NULL);

    cvScale(IdiffLuminanceF, IdiffLuminanceF, 0.33334, 0);

    //cvSaveImage("z.jpg", IdiffLuminanceF);

    cvMinMaxLoc(IdiffLuminanceF, &_dMinVal, &_dMaxVal, NULL, NULL, NULL);
    _dMaxWanted = (static_cast<float>(_iMaxWantedRel)/1000)*_dMaxVal/0.3;


    cvInRangeS(IdiffLuminanceF, cvScalar(_dMinVal), cvScalar(_dMaxWanted), IoneChannelMaskt);

    
    cvThreshold(IoneChannelMaskt, IoneChannelMaskt, 100, 1, CV_THRESH_BINARY); // because 255->1 and 0->0

    
    //cvSplit(IoneChannelMaskt, IoneChannelMaskt, 0, 0, 0);

    //cvDilate( IoneChannelMaskt, IoneChannelMaskt, NULL, 1);
    //cvErode( IoneChannelMaskt, IoneChannelMaskt, NULL, 1);
    //cvDilate( IoneChannelMaskt, IoneChannelMaskt, NULL, 1);

    //cvSaveImage("constantPixMask.jpg", IoneChannelMaskt);

}


//void brightRange(IplImage *v_frameI){
//
//    int g_iDarkPosition = 400;
//    int g_iLightPosition = 700;
//
//    cvNamedWindow("Setup dark/light", CV_WINDOW_AUTOSIZE);
//    cvCreateTrackbar("Dark Bar", "Setup dark/light",
//                                &g_iDarkPosition, 1000,
//                                NULL);
//    cvCreateTrackbar( "Light Bar", "Setup dark/light",
//                                &g_iLightPosition, 1000,
//                                NULL);
//
//
//        cvCvtScale(v_frameI,Iscratch,1,0); // To float;
//        cvScale(Iscratch, Iscratch, 0.00392, 0);
//
//
//
//        while(1){               // setup - how bright/dark should be dirts
//
//
//                cvZero( IscratchF );
//                cvZero( Idiff1F );
//                cvZero( Idiff2F );
//                cvZero( Idiff3F );
//                cvZero( g_8uImaskt1 );
//                cvZero( IscratchF1 );
//                cvZero( Iscratch3 );
//
//                cvSplit(Iscratch, Idiff1F, Idiff2F, Idiff3F, NULL);
//
//
//                cvAcc(Idiff1F, IscratchF, NULL);
//                cvAcc(Idiff2F, IscratchF, NULL);
//                cvAcc(Idiff3F, IscratchF, NULL);
//                cvScale(IscratchF, IscratchF, 0.333, 0);
//
//
//                cvMinMaxLoc(IscratchF, &g_dDark, &g_dLight, NULL, NULL, NULL);
//                g_dDark = (static_cast<float>(g_iDarkPosition)/1000)*g_dLight;
//                g_dLight = (static_cast<float>(g_iLightPosition)/1000)*g_dLight;
//
//
//                cvInRangeS(IscratchF, cvScalar(g_dDark), cvScalar(g_dLight), g_8uImaskt1);
//                cvThreshold(g_8uImaskt1, g_8uImaskt1, 100, 1, CV_THRESH_BINARY); // because 255->1 and 0->0
//                cvCvtScale(g_8uImaskt1, IscratchF1, 1, 0);
//                cvMul(Idiff1F,IscratchF1,Idiff1F,1);
//                cvMul(Idiff2F,IscratchF1,Idiff2F,1);
//                cvMul(Idiff3F,IscratchF1,Idiff3F,1);
//
//                cvMerge(Idiff1F,Idiff2F,Idiff3F,NULL,Iscratch3);
//
//                cvShowImage( "Setup dark/light", Iscratch3);
//
//                cvSaveImage("IscratchF1po.jpg", Iscratch3 );
//
//
//                char c = cvWaitKey(33);
//                if( c == 27 ) break;
//        }
//
//        cvDestroyWindow( "Setup dark/light" );
//}


/*void backgroundDiff(
IplImage *I,
IplImage *Imask
) {



cvCvtScale(I,Iscratch,1,0); // To float;
cvSplit( Iscratch, Igray1,Igray2,Igray3, 0 );
//Channel 1
//
cvInRange(Igray1,Ilow1,Ihi1,Imask);

//Channel 2
//
cvInRange(Igray2,Ilow2,Ihi2,Imaskt);
cvOr(Imask,Imaskt,Imask);
//Channel 3
//
cvInRange(Igray3,Ilow3,Ihi3,Imaskt);
cvOr(Imask,Imaskt,Imask);

cvSave("averaging_backgorund_openCV.txt", Imask);
cvSplit(Imask, IoneChannelMaskt, 0, 0, 0);
cvSaveImage("x.jpg", IoneChannelMaskt);
//Finally, invert the results
//
//cvSubRS( Imask, 255, Imask);
}
*/


void DeallocateImagesBG()
{
//cvReleaseImage( &IavgF);
//cvReleaseImage( &IdiffF );
cvReleaseImage( &Idiff1F );
cvReleaseImage( &Idiff2F );
cvReleaseImage( &Idiff3F );
//cvReleaseImage( &IprevF );
//cvReleaseImage( &IhiF );
//cvReleaseImage( &IlowF );
//cvReleaseImage( &Ilow1 );
//cvReleaseImage( &Ilow2 );
//cvReleaseImage( &Ilow3 );
//cvReleaseImage( &Ihi1 );
//cvReleaseImage( &Ihi2 );
//cvReleaseImage( &Ihi3 );
cvReleaseImage( &Iscratch );
cvReleaseImage( &Iscratch_8u );
cvReleaseImage( &ImaskBG1 );
cvReleaseImage( &IoneChannelMaskt );
cvReleaseImage( &IaccBg );
//cvReleaseImage( &Iscratch2 );
//cvReleaseImage( &Igray1 );
//cvReleaseImage( &Igray2 );
//cvReleaseImage( &Igray3 );
//cvReleaseImage( &Imaskt);
//cvReleaseImage( &IscratchF1);
//cvReleaseImage( &IscratchF2);
//cvReleaseImage( &IscratchF3);
//cvReleaseImage( &IscratchF);
cvReleaseImage( &IdiffLuminanceF);
//cvReleaseImage( &Iscratch3 );
//cvReleaseImage( &g_8uImaskt1 );
//cvReleaseImage( &g_8uImaskt2 );
//cvReleaseImage( &g_8uImaskt3 );


}


/////////////////////////////////////////////////////////////////////////////

void backgroundSee(IplImage *_IprevFrame, IplImage *_I, IplImage *_IdiffFrame, IplImage *_IbackgroundMask, IplImage *_IavgFrame, int _iConstTresholdPosition, int _iFrameCount)
{

//        int g_iProgressPosition = 0;
//
//        cvNamedWindow( "Frames progress", CV_WINDOW_AUTOSIZE );
//        cvCreateTrackbar( "FramesProgressBar", "Frames progress",
//                                &g_iProgressPosition, 100,
//                                NULL);
//
//        CvCapture* capture = cvCreateFileCapture("Averaging_Video.avi");
//        IplImage *frame;

//	int frameCount = 0;
//	while(1) {
//		frameCount++;
//		frame = cvQueryFrame( capture );
//                if( !frame ) break;

                //if(_iFrameCount == 0){

        AllocateImagesBG( _I );

                    //brightRange(frame);
                //}

        accumulateBackground( _IprevFrame, _I, _IdiffFrame, _IavgFrame, _iFrameCount );

//		cvShowImage( "Frames progress", IaccBg );
//                g_iProgressPosition = static_cast<int>(100*cvGetCaptureProperty( capture, CV_CAP_PROP_POS_AVI_RATIO));  //określa bieżącą pozycję w filmie 0-1, do progressbar
//                cvSetTrackbarPos("FramesProgressBar",
//                                "Frames progress",
//                                 g_iProgressPosition);


//		if( g_iProgressPosition >= 100 ) break;
//                char c = cvWaitKey(33);
//                if( c == 27 ) break;
//
//	}

//        cvDestroyWindow( "Frames progress" );

        findConstPix(_IdiffFrame, _iConstTresholdPosition);

        cvMerge(IoneChannelMaskt, IoneChannelMaskt, IoneChannelMaskt, NULL, Iscratch_8u);
        cvMerge(IoneChannelMaskt, IoneChannelMaskt, IoneChannelMaskt, NULL, _IbackgroundMask);

        //cvSave("i.txt",Iscratch_8u);
        cvMul(_I, Iscratch_8u, _I, 1.0);

//        cvNamedWindow( "Constant treshold", CV_WINDOW_AUTOSIZE );
//        cvCreateTrackbar( "ConstantTreshold", "Constant treshold",
//                            &g_iConstTresholdPosition, 1000,
//                            NULL
//        );
//
//
//        while(1){
//
//            g_iConstTresholdPosition = cvGetTrackbarPos("ConstantTreshold", "Constant treshold");
//
//            findConstPix(IdiffF, g_iConstTresholdPosition);
//
//            cvShowImage( "Constant treshold", IoneChannelMaskt );
//
//            char c = cvWaitKey(33);
//            if( c == 27 ) break;
//        }
//
//
//        cvDestroyWindow( "Constant treshold" );
//	cvReleaseCapture( &capture );
	DeallocateImagesBG();
        
}
