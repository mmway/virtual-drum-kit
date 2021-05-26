#include "stdafx.h"

#define GLUT_DISABLE_ATEXIT_HACK

#include <windows.h>
#include "gl\gl.h"
#include "GL\glut.h"
#include "opencv/cv.h"
#include "opencv/highgui.h"

#include "VirtualDrums_Globals.h"
#include "otherFunctions.h"



#define WINDOW_WIDTH	800		//dimensions of interface3D window
#define WINDOW_HEIGHT	800


int l_winInterface3D;

double l_matrixTemp_3x1[3];
double l_matrixRotationBetweenBothCameras_9x1[9];
double l_dCamera3dSeeingAngle = 60.0;

CvPoint3D64f l_dCameraPosition = cvPoint3D64f(0.0, 300.0, 0.0);
CvPoint3D64f l_dCameraLookAt = cvPoint3D64f(0.0, 0.0, 0.0);




void mmDrawOriginAxis(void){

	glLineWidth(2.0);
	glBegin(GL_LINES);
		glColor3f(0.0, 0.5, 0.0); //green X
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(15.0, 0.0, 0.0);
		
		glColor3f(0.0, 0.0, 0.5); // blue Y
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 15.0, 0.0);
		
		glColor3f(0.5, 0.0, 0.0); // red Z
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 15.0);
	glEnd();

}


void mmDrawCameraSymbol(void){

	glLineWidth(1.0);
	glBegin(GL_TRIANGLES);
		glColor3f(0.0, 0.5, 0.0);
		glVertex3f(-5.0, 0.0, 0.0);
		glVertex3f(5.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 20.0);
	glEnd();

}

// text drawing
void mmRenderBitmapString( double _dPercentePositionSubX,
						    double _dPercentePositionSubZ,
							double _dCameraY,
							double _dCameraZ,
							void *_font, 
							char *_cTextToShow){  

  char *_c;
  double _dA = 0.0;
  double _dSubtitlesDistanceFromCamera = 10.0;

  _dA = 2 * _dSubtitlesDistanceFromCamera * tan(l_dCamera3dSeeingAngle * 2.0 * 3.14 / 360.0 / 2);

  glRasterPos3f( ((_dA-0.05*_dA) * _dPercentePositionSubX/100.0), 
				 _dCameraY - _dSubtitlesDistanceFromCamera , 
				 _dCameraZ + ((_dA-0.05*_dA) * _dPercentePositionSubZ/100.0) );

  for (_c=_cTextToShow; *_c != '\0'; _c++) {
    glutBitmapCharacter(_font, *_c);
  }

}


// text drawing on 3d coordinate
void mmRenderBitmapString3Dcoordinate( double _dX,
									   double _dY,
									   double _dZ,
									   void *_font, 
									   char *_cTextToShow){  

  char *_c;

  glRasterPos3f( _dX, _dY, _dZ );

  for (_c=_cTextToShow; *_c != '\0'; _c++) {
    glutBitmapCharacter(_font, *_c);
  }

}

void mmDrawDrumSymbol(mmDrum _drumTemp){

	if (_drumTemp.iTimeToLightOff > 0)
		glLineWidth(3.0);
	else
		glLineWidth(1.0);

	glBegin(GL_LINE_STRIP);
		glColor3f(1.0, 0.5, 0.5);

		//upper plane
		glVertex3d(+double(_drumTemp.width)/2.0, 
				   +double(_drumTemp.height)/2.0,
				   +double(_drumTemp.depth)/2.0);

		glVertex3d(-double(_drumTemp.width)/2.0, 
				   +double(_drumTemp.height)/2.0,
				   +double(_drumTemp.depth)/2.0);
		
		glVertex3d(-double(_drumTemp.width)/2.0, 
				   +double(_drumTemp.height)/2.0,
				   -double(_drumTemp.depth)/2.0);

		glVertex3d(+double(_drumTemp.width)/2.0, 
				   +double(_drumTemp.height)/2.0,
				   -double(_drumTemp.depth)/2.0);

		glVertex3d(+double(_drumTemp.width)/2.0, 
				   +double(_drumTemp.height)/2.0,
				   +double(_drumTemp.depth)/2.0);

		//lower plane & links beteween lowe and upper plane
		glVertex3d(+double(_drumTemp.width)/2.0, 
				   -double(_drumTemp.height)/2.0,
				   +double(_drumTemp.depth)/2.0);

		glVertex3d(-double(_drumTemp.width)/2.0,	//
				   -double(_drumTemp.height)/2.0,	//
				   +double(_drumTemp.depth)/2.0);	//
													//
		glVertex3d(-double(_drumTemp.width)/2.0,	//
				   +double(_drumTemp.height)/2.0,	//link to upper plane
				   +double(_drumTemp.depth)/2.0);	//
													//
		glVertex3d(-double(_drumTemp.width)/2.0,	//
				   -double(_drumTemp.height)/2.0,	//
				   +double(_drumTemp.depth)/2.0);	//
		
		glVertex3d(-double(_drumTemp.width)/2.0,	//
				   -double(_drumTemp.height)/2.0,	//
				   -double(_drumTemp.depth)/2.0);	//
													//
		glVertex3d(-double(_drumTemp.width)/2.0,	//
				   +double(_drumTemp.height)/2.0,	//link to uppper plane
				   -double(_drumTemp.depth)/2.0);	//
													//
		glVertex3d(-double(_drumTemp.width)/2.0,	//
				   -double(_drumTemp.height)/2.0,	//
				   -double(_drumTemp.depth)/2.0);	//

		glVertex3d(+double(_drumTemp.width)/2.0,	//
				   -double(_drumTemp.height)/2.0,	//
				   -double(_drumTemp.depth)/2.0);	//
													//
		glVertex3d(+double(_drumTemp.width)/2.0,	//
				   +double(_drumTemp.height)/2.0,	//link to upper plane
				   -double(_drumTemp.depth)/2.0);	//
													//
		glVertex3d(+double(_drumTemp.width)/2.0,	//
				   -double(_drumTemp.height)/2.0,	//
				   -double(_drumTemp.depth)/2.0);	//

		glVertex3d(+double(_drumTemp.width)/2.0, 
				   -double(_drumTemp.height)/2.0,
				   +double(_drumTemp.depth)/2.0);

	glEnd();

}


void mmDrawDrumSymbolPlane(mmDrum _drumTemp){

	if (_drumTemp.iTimeToLightOff > 0)
		glLineWidth(3.0);
	else
		glLineWidth(1.0);

	glBegin(GL_LINE_STRIP);
		glColor3f(1.0, 0.5, 0.5);

		glVertex3d(_drumTemp.A.x, _drumTemp.A.y, _drumTemp.A.z);
		glVertex3d(_drumTemp.B.x, _drumTemp.B.y, _drumTemp.B.z);
		glVertex3d(_drumTemp.C.x, _drumTemp.C.y, _drumTemp.C.z);
		glVertex3d(_drumTemp.D.x, _drumTemp.D.y, _drumTemp.D.z);
		glVertex3d(_drumTemp.A.x, _drumTemp.A.y, _drumTemp.A.z);

	glEnd();

}




void reshapeCB(int p_iWidth,int p_iHeight){

	l_dCameraPosition.z = 1.5 * mmVectorLenght(g_matrixTranslationBetweenBothCameras[0], g_matrixTranslationBetweenBothCameras[1], g_matrixTranslationBetweenBothCameras[2]);
	l_dCameraLookAt.z = l_dCameraPosition.z;

	//computing vector that look in camera 1 direction
	mmIloczWekt(0.0, 1.0, 0.0, 
				g_matrixTranslationBetweenBothCameras[0], 0.0, g_matrixTranslationBetweenBothCameras[2], 
				&l_matrixTemp_3x1[0], &l_matrixTemp_3x1[1], &l_matrixTemp_3x1[2]);


	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(l_dCamera3dSeeingAngle, 1.0, 0.1, 400.0);

		//look at space between cameras
		gluLookAt( l_dCameraPosition.x, l_dCameraPosition.y, l_dCameraPosition.z,
				   0.0, 0.0, l_dCameraLookAt.z,
				   0.0, 0.0, -1.0);

	glMatrixMode(GL_MODELVIEW);

}



void displayCB(void) //function showed in moment of showing the window
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	
		glLoadIdentity();

		glRotated(g_dInterface3dRotX, 1.0, 0.0, 0.0);
		glRotated(g_dInterface3dRotY, 0.0, 1.0, 0.0);
		glRotated(g_dInterface3dRotZ, 0.0, 0.0, 1.0);

		mmDrawOriginAxis();	//drawing origin

		////Marker 1 drawing rays from cameras
			glLineWidth(2.0);

			glColor3f(g_matrixMarker1color[0], g_matrixMarker1color[1], g_matrixMarker1color[2]);
			glBegin(GL_LINES);
				glVertex3d(g_matrixMarker1LineA[0][0], 
						   g_matrixMarker1LineA[0][1], 
						   g_matrixMarker1LineA[0][2]);
				glVertex3d(g_matrixMarker1LineA[1][0], 
						   g_matrixMarker1LineA[1][1], 
						   g_matrixMarker1LineA[1][2]);
			glEnd();

			glBegin(GL_LINES);
				glVertex3d(g_matrixMarker1LineB[0][0], 
						   g_matrixMarker1LineB[0][1], 
						   g_matrixMarker1LineB[0][2]);
				glVertex3d(g_matrixMarker1LineB[1][0], 
						   g_matrixMarker1LineB[1][1], 
						   g_matrixMarker1LineB[1][2]);
			glEnd();
		//end - Marker 1 drawing rays from cameras

		////Marker 2 drawing rays from cameras
			glLineWidth(2.0);

			glColor3f(g_matrixMarker2color[0], g_matrixMarker2color[1], g_matrixMarker2color[2]);
			glBegin(GL_LINES);
				glVertex3d(g_matrixMarker2LineA[0][0], 
						   g_matrixMarker2LineA[0][1], 
						   g_matrixMarker2LineA[0][2]);
				glVertex3d(g_matrixMarker2LineA[1][0], 
						   g_matrixMarker2LineA[1][1], 
						   g_matrixMarker2LineA[1][2]);
			glEnd();

			glBegin(GL_LINES);
				glVertex3d(g_matrixMarker2LineB[0][0], 
						   g_matrixMarker2LineB[0][1], 
						   g_matrixMarker2LineB[0][2]);
				glVertex3d(g_matrixMarker2LineB[1][0], 
						   g_matrixMarker2LineB[1][1], 
						   g_matrixMarker2LineB[1][2]);
			glEnd();
		//end - Marker 2 drawing rays from cameras


		////camera 1 drawing
		glPushMatrix();
			//glLoadIdentity();

			glTranslatef(-g_matrixTranslationBetweenBothCamerasHalf[0],-g_matrixTranslationBetweenBothCamerasHalf[1],-g_matrixTranslationBetweenBothCamerasHalf[2]);
			glRotatef(-360.0*mmVectorLenght(g_matrixRotationBetweenBothCameras3x1Half[0], g_matrixRotationBetweenBothCameras3x1Half[1], g_matrixRotationBetweenBothCameras3x1Half[2])/2.0/3.14,
					g_matrixRotationBetweenBothCameras3x1Half[0]/mmVectorLenght(g_matrixRotationBetweenBothCameras3x1Half[0], g_matrixRotationBetweenBothCameras3x1Half[1], g_matrixRotationBetweenBothCameras3x1Half[2]),
					g_matrixRotationBetweenBothCameras3x1Half[1]/mmVectorLenght(g_matrixRotationBetweenBothCameras3x1Half[0], g_matrixRotationBetweenBothCameras3x1Half[1], g_matrixRotationBetweenBothCameras3x1Half[2]), 
					g_matrixRotationBetweenBothCameras3x1Half[2]/mmVectorLenght(g_matrixRotationBetweenBothCameras3x1Half[0], g_matrixRotationBetweenBothCameras3x1Half[1], g_matrixRotationBetweenBothCameras3x1Half[2]));

			mmDrawCameraSymbol();

		glPopMatrix();//end - camera 1 drawing
		

		////camera 2 drawing
		glPushMatrix();
			//glLoadIdentity();
			
			glTranslatef(g_matrixTranslationBetweenBothCamerasHalf[0],g_matrixTranslationBetweenBothCamerasHalf[1],g_matrixTranslationBetweenBothCamerasHalf[2]);

			glRotatef(360.0*mmVectorLenght(g_matrixRotationBetweenBothCameras3x1Half[0], g_matrixRotationBetweenBothCameras3x1Half[1], g_matrixRotationBetweenBothCameras3x1Half[2])/2.0/3.14,
					g_matrixRotationBetweenBothCameras3x1Half[0]/mmVectorLenght(g_matrixRotationBetweenBothCameras3x1Half[0], g_matrixRotationBetweenBothCameras3x1Half[1], g_matrixRotationBetweenBothCameras3x1Half[2]),
					g_matrixRotationBetweenBothCameras3x1Half[1]/mmVectorLenght(g_matrixRotationBetweenBothCameras3x1Half[0], g_matrixRotationBetweenBothCameras3x1Half[1], g_matrixRotationBetweenBothCameras3x1Half[2]), 
					g_matrixRotationBetweenBothCameras3x1Half[2]/mmVectorLenght(g_matrixRotationBetweenBothCameras3x1Half[0], g_matrixRotationBetweenBothCameras3x1Half[1], g_matrixRotationBetweenBothCameras3x1Half[2]));
			
			mmDrawCameraSymbol();
			
		glPopMatrix();//end - camera 2 drawing


		////drums drawing
		if (g_vecDrums1.size()>=1){
			char _cTemp[10];
			for (int i=0; i<=(g_vecDrums1.size()-1); i++){
				glPushMatrix();

					mmDrawDrumSymbolPlane(g_vecDrums1[i]);
					mmDrawDrumSymbolPlane(g_vecDrums2[i]);

					sprintf( _cTemp, "%d", i+1 );
					mmRenderBitmapString3Dcoordinate(g_vecDrums1[i].x, g_vecDrums1[i].y, g_vecDrums1[i].z,
														GLUT_BITMAP_HELVETICA_18,
														_cTemp );


					////TEST - drawing control points on edge of a drum
					switch (i){
						case 0: glColor3f(1.0, 1.0, 1.0); break;
						case 1: glColor3f(1.0, 1.0, 0.0); break;
						case 2: glColor3f(1.0, 0.0, 0.0); break;
						case 3: glColor3f(0.0, 1.0, 1.0); break;
						default: break;
					}


					//////TEST - drawing point on edge of a drum
					//glPushMatrix();
					//	glTranslatef(g_vecDrums1[i].ptMab.x, g_vecDrums1[i].ptMab.y, g_vecDrums1[i].ptMab.z);
					//	glutSolidSphere(1.5,10,10);
					//glPopMatrix();//end - TEST - drawing point on edge of a drum

					//////TEST - drawing point on edge of a drum
					//glPushMatrix();
					//	glTranslatef(g_vecDrums1[i].ptMbc.x, g_vecDrums1[i].ptMbc.y, g_vecDrums1[i].ptMbc.z);
					//	glutSolidSphere(1.5,10,10);
					//glPopMatrix();//end - TEST - drawing point on edge of a drum

					//////TEST - drawing point on edge of a drum
					//glPushMatrix();
					//	glTranslatef(g_vecDrums1[i].ptMcd.x, g_vecDrums1[i].ptMcd.y, g_vecDrums1[i].ptMcd.z);
					//	glutSolidSphere(1.5,10,10);
					//glPopMatrix();//end - TEST - drawing point on edge of a drum

					//////TEST - drawing point on edge of a drum
					//glPushMatrix();
					//	glTranslatef(g_vecDrums1[i].ptMda.x, g_vecDrums1[i].ptMda.y, g_vecDrums1[i].ptMda.z);
					//	glutSolidSphere(1.5,10,10);
					//glPopMatrix();//end - TEST - drawing point on edge of a drum

					//////TEST - drawing point on edge of a drum
					//glPushMatrix();
					//	glTranslatef(g_vecDrums1[i].ptCrossPoint.x, g_vecDrums1[i].ptCrossPoint.y, g_vecDrums1[i].ptCrossPoint.z);
					//	glColor3f(0.0, 1.0, 0.0);		//changing color of spheres
					//	glutSolidSphere(2.5,10,10);
					//glPopMatrix();//end - TEST - drawing point on edge of a drum

				glPopMatrix();
			}
		}//end - drums drawing


		////marker 1 position drawing
		glPushMatrix();
			glTranslatef(g_matrixMarker1Position3D[0],g_matrixMarker1Position3D[1],g_matrixMarker1Position3D[2]);
			glColor3d(g_matrixMarker1color[0], g_matrixMarker1color[1], g_matrixMarker1color[2]);
			glutSolidSphere(5,10,10);
		glPopMatrix();//end - marker 1 position drawin

		////marker 2 position drawing
		glPushMatrix();
			glTranslatef(g_matrixMarker2Position3D[0],g_matrixMarker2Position3D[1],g_matrixMarker2Position3D[2]);
			glColor3d(g_matrixMarker2color[0], g_matrixMarker2color[1], g_matrixMarker2color[2]);
			glutSolidSphere(5,10,10);
		glPopMatrix();//end - marker 2 position drawin

	
	glPopMatrix();

	////drawing text
	glPushMatrix();
		glColor3f(1.0,1.0,1.0);
		mmRenderBitmapString(-50.0, -50.0, l_dCameraPosition.y, l_dCameraPosition.z, GLUT_BITMAP_TIMES_ROMAN_24, g_cDrumsPositioningText0);
		mmRenderBitmapString(-50.0, -45.0, l_dCameraPosition.y, l_dCameraPosition.z, GLUT_BITMAP_HELVETICA_18, g_cDrumsPositioningText1);
		mmRenderBitmapString(-50.0, -40.0, l_dCameraPosition.y, l_dCameraPosition.z, GLUT_BITMAP_HELVETICA_18, g_cDrumsPositioningText2);
		mmRenderBitmapString(-50.0, 45.0, l_dCameraPosition.y, l_dCameraPosition.z, GLUT_BITMAP_HELVETICA_18, g_cDrumsPositioningText3);
		mmRenderBitmapString(-50.0, 50.0, l_dCameraPosition.y, l_dCameraPosition.z, GLUT_BITMAP_HELVETICA_18, g_cDrumsPositioningText4);
		mmRenderBitmapString(-50.0, 40.0, l_dCameraPosition.y, l_dCameraPosition.z, GLUT_BITMAP_HELVETICA_18, g_cDrumsPositioningText5);
		mmRenderBitmapString(-50.0, 35.0, l_dCameraPosition.y, l_dCameraPosition.z, GLUT_BITMAP_HELVETICA_18, g_cDrumsPositioningText6);
	glPopMatrix();
	//end - drawing text
	
	glFlush();
	glutSwapBuffers();	//to avoid window3D flickering



}


void mmRefreshingView3D(void){

	Sleep(20);
	glutPostRedisplay();

}


void keyCBdown(unsigned char _key, int _x, int _y){
	if (_key == 32){	//checking if 'zero' button was pushed
		g_bDrumPedalStateChange = true;
		g_bDrumPedalHihatState = true;
	}

	if (_key == 48){	//checking if 'space' button was pushed
		g_bDrumBassHitted = true;
	}
}


void keyCBup(unsigned char _key, int _x, int _y){
	if (_key == 32){	//checking if 'zero' button was pushed
		g_bDrumPedalStateChange = true;
		g_bDrumPedalHihatState = false;
	}

}

void mmSetupOpenGL(){
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	l_winInterface3D = glutCreateWindow("3D interface");
  
	reshapeCB(WINDOW_WIDTH,WINDOW_HEIGHT);
  
  	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_DEPTH_TEST);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////// MAIN ///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int mmInterface3D(){
  
	int argc=1;
	char *argv[] = {"virtualDrums_MGR",NULL};

	glutInit(&argc, argv);	//inicialization of GLUT
	
	mmSetupOpenGL();					//inicialization starting values of GLUT

	glShadeModel (GL_SMOOTH);
	
	glutReshapeFunc(reshapeCB);
	glutDisplayFunc(displayCB);		//function callback type to showing a window
	glutIgnoreKeyRepeat(1);			//no repeat hitting keyboard after key wasn't realesed
	glutKeyboardFunc(keyCBdown);		//function callback type to controling keyboard key-down actions
	glutKeyboardUpFunc(keyCBup);		//function callback type to controling keyboard key-up actions
	glutIdleFunc(mmRefreshingView3D);			//function callback type to animation loop
  
	glutMainLoop();			//main GLUT loop

  return 0;
}