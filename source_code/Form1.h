#pragma once

#include <opencv/cv.h>
#include "opencv/highgui.h"
#include <windows.h>
#include "mmsystem.h"

#include "perkusjaMain.h"
#include "VirtualDrums_Globals.h"
#include "interface3d.h"
#include <stdio.h>
#include <dirent.h>
#include "otherFunctions.h"                                 

#include <irrKlang/irrKlang.h>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

#include <vcclr.h>
//#include <atlstr.h>
#include <stdio.h>
#using <mscorlib.dll>

#include <Dshow.h>	//for changing cameras parameters

using namespace System;
using namespace System::Runtime::InteropServices; // for Marshal::





namespace virtualDrums_temp{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}

			if (l_threadMainComputing->IsAlive){		// gives error on close		// THREADING
				//cvDestroyAllWindows();		//when erlaier thred was aborted, so there was not cvDestroyAllWindows() at the end of computing
				l_threadMainComputing->Abort();			// cleans up threading ?	// THREADING
			}
			if (l_threadInterface3D->IsAlive){		// gives error on close		// THREADING
				//cvDestroyAllWindows();		//when erlaier thred was aborted, so there was not cvDestroyAllWindows() at the end of computing
				l_threadInterface3D->Abort();			// cleans up threading ?	// THREADING
			}
			if (l_threadPlaySounds1->IsAlive){		// gives error on close		// THREADING
				//cvDestroyAllWindows();		//when erlaier thred was aborted, so there was not cvDestroyAllWindows() at the end of computing
				l_threadPlaySounds1->Abort();			// cleans up threading ?	// THREADING
			}
			if (l_threadPlaySounds2->IsAlive){		// gives error on close		// THREADING
				//cvDestroyAllWindows();		//when erlaier thred was aborted, so there was not cvDestroyAllWindows() at the end of computing
				l_threadPlaySounds2->Abort();			// cleans up threading ?	// THREADING
			}
			if (l_threadLongTimeRefreshingLoop->IsAlive){		// gives error on close		// THREADING
				//cvDestroyAllWindows();		//when erlaier thred was aborted, so there was not cvDestroyAllWindows() at the end of computing
				l_threadLongTimeRefreshingLoop->Abort();			// cleans up threading ?	// THREADING
			}

		}
	private: System::Windows::Forms::Button^  buttonStart;


























	private: System::Windows::Forms::TextBox^  textBoxColorFactorBounds;

	private: System::Windows::Forms::Label^  labelColorFactorBounds;
	private: System::Windows::Forms::HScrollBar^  scrollbarColorFactorBounds;
	private: System::Windows::Forms::TextBox^  textBoxSaturationFactorBounds;

	private: System::Windows::Forms::Label^  labelSaturationFactorBounds;
	private: System::Windows::Forms::HScrollBar^  scrollbarSaturationFactorBounds;
	private: System::Windows::Forms::Button^  buttonCalibrate;
	private: System::Windows::Forms::Button^  buttonInterface3D;






	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		
		

	private: System::Windows::Forms::TextBox^  textBoxRotationAngleZ;

	private: System::Windows::Forms::Label^  labelRotationAngleZ;
	private: System::Windows::Forms::HScrollBar^  ScrollBarRotationAngleZ;



	private: System::Windows::Forms::TextBox^  textBoxRotationAngleY;

	private: System::Windows::Forms::Label^  labelRotationAngleY;
	private: System::Windows::Forms::HScrollBar^  ScrollBarRotationAngleY;



	private: System::Windows::Forms::TextBox^  textBoxRotationAngleX;

	private: System::Windows::Forms::Label^  labelRotationAngleX;
	private: System::Windows::Forms::HScrollBar^  ScrollBarRotationAngleX;
private: System::Windows::Forms::CheckBox^  checkBoxLeftCameraView;
private: System::Windows::Forms::CheckBox^  checkBoxRightCameraView;







///////////////// START OF MY STUFF

	private: Thread ^l_threadInterface3D;	// THREADING

			 Thread ^l_threadMainComputing;	// THREADING

			 Thread ^l_threadPlaySounds1;	// THREADING
private: System::Windows::Forms::CheckBox^  checkBoxCalibrationType;






private: System::Windows::Forms::MenuStrip^  menuStrip1;
private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
private: System::Windows::Forms::CheckBox^  checkBoxVolumeControl;
private: System::Windows::Forms::CheckBox^  checkBoxCalibrateCamerasIntrinsicDistortion;
private: System::Windows::Forms::ComboBox^  comboBoxCamerasImageSize;
private: System::Windows::Forms::Label^  labelCamerasImageSize;
private: System::Windows::Forms::GroupBox^  groupBoxProcessingParameteres;

private: System::Windows::Forms::GroupBox^  groupBoxInterface3D;
private: System::Windows::Forms::GroupBox^  groupBoxCalibrations;
private: System::Windows::Forms::GroupBox^  groupBoxWindows;
private: System::Windows::Forms::CheckBox^  checkBoxAdvanceSettings;
private: System::Windows::Forms::TextBox^  textBoxNumberOfDrums;
private: System::Windows::Forms::Label^  labelNumberOfDrums;
private: System::Windows::Forms::HScrollBar^  ScrollBarNumberOfDrums;
private: System::Windows::Forms::ComboBox^  comboBoxDrumsAudioSamples;
private: System::Windows::Forms::TextBox^  textBoxNumberOfDrumToChangeProperty;
private: System::Windows::Forms::Label^  labelNumberOfDrumToChangeProperty;
private: System::Windows::Forms::HScrollBar^  ScrollBarNumberOfDrumToChangeProperty;
private: System::Windows::Forms::CheckBox^  checkBoxEditDrums;
private: System::Windows::Forms::TextBox^  textBoxDrumPositionZ;

private: System::Windows::Forms::Label^  labelDrumPositionZ;



private: System::Windows::Forms::TextBox^  textBoxDrumPositionY;

private: System::Windows::Forms::Label^  labelDrumPositionY;

private: System::Windows::Forms::TextBox^  textBoxDrumPositionX;
private: System::Windows::Forms::Label^  labelDrumPositionX;
private: System::Windows::Forms::NumericUpDown^  numericUpDownDrumPositionX;
private: System::Windows::Forms::NumericUpDown^  numericUpDownDrumPositionY;
private: System::Windows::Forms::NumericUpDown^  numericUpDownDrumPositionZ;
private: System::Windows::Forms::ListBox^  listBoxListOfDrums;
private: System::Windows::Forms::GroupBox^  groupBoxDrumsEdition;
private: System::Windows::Forms::Label^  labelDrumSoundSample;
private: System::Windows::Forms::CheckBox^  checkBoxViewColorSeparationWithoutBackgroundClosedSegment;

private: System::Windows::Forms::CheckBox^  checkBoxViewColorSeparationWithoutBackgroundClosed;

private: System::Windows::Forms::CheckBox^  checkBoxViewColorSeparationWithoutBackground;
private: System::Windows::Forms::CheckBox^  checkBoxViewWitoutBackground;
private: System::Windows::Forms::CheckBox^  checkBoxViewValue;

private: System::Windows::Forms::CheckBox^  checkBoxViewSaturation;

private: System::Windows::Forms::CheckBox^  checkBoxViewHue;
private: System::Windows::Forms::CheckBox^  checkBoxViewOnlyMasks;
private: System::Windows::Forms::CheckBox^  checkBoxLookOnMarkerSaturation;

private: System::Windows::Forms::TextBox^  textBoxChessboardSqareSize;

private: System::Windows::Forms::Label^  labelChessboardSqareSize;
private: System::Windows::Forms::HScrollBar^  scrollBarChessboardSqareSize;
private: System::Windows::Forms::TextBox^  textBoxChessboardCornersNumberX;

private: System::Windows::Forms::Label^  labelChessboardCornersNumberX;
private: System::Windows::Forms::HScrollBar^  scrollBarChessboardCornersNumberX;
private: System::Windows::Forms::TextBox^  textBoxChessboardCornersNumberY;





private: System::Windows::Forms::Label^  labelChessboardCornersNumberY;
private: System::Windows::Forms::HScrollBar^  scrollBarChessboardCornersNumberY;
private: System::Windows::Forms::TextBox^  textBoxAngleOfCameraSeeingInDegree;

private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::HScrollBar^  scrollBarAngleOfCameraSeeingInDegree;













private: System::Windows::Forms::TextBox^  textBoxCodebookCbBounds;
private: System::Windows::Forms::CheckBox^  checkBoxUseBackgroundSubtraction;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::HScrollBar^  scrollbarCodebookCbBounds;
private: System::Windows::Forms::TextBox^  textBoxCodebookModMax;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::HScrollBar^  scrollbarCodebookModMax;
private: System::Windows::Forms::TextBox^  textBoxCodebookModMin;
private: System::Windows::Forms::Label^  labelFilterSize;
private: System::Windows::Forms::HScrollBar^  scrollbarCodebookModMin;
private: System::Windows::Forms::GroupBox^  groupBoxAutoAdjustProcessingParameters;
private: System::Windows::Forms::CheckBox^  checkBoxAutoAdjustOnOff;
private: System::Windows::Forms::TextBox^  textBoxDrumsDepth;
private: System::Windows::Forms::Label^  labelDrumsDepth;
private: System::Windows::Forms::HScrollBar^  scrollBarDrumsDepth;
private: System::Windows::Forms::TextBox^  textBoxDrumsWidth;
private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::HScrollBar^  scrollBarDrumsWidth;
private: System::Windows::Forms::TextBox^  textBoxAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust;
private: System::Windows::Forms::Label^  labelAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust;


private: System::Windows::Forms::HScrollBar^  ScrollBarAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust;
private: System::Windows::Forms::TextBox^  textBoxAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust;
private: System::Windows::Forms::Label^  labelAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust;



private: System::Windows::Forms::HScrollBar^  ScrollBarAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust;
private: System::Windows::Forms::Button^  buttonRefreshAutoAdjust;




private: System::Windows::Forms::TextBox^  textBoxAutoAdjustGoodResultsPercentageAfterColorFactorAdjust;

private: System::Windows::Forms::Label^  labelAutoAdjustGoodResultsPercentageAfterColorFactorAdjust;
private: System::Windows::Forms::HScrollBar^  ScrollBarAutoAdjustGoodResultsPercentageAfterColorFactorAdjust;
private: System::Windows::Forms::TextBox^  textBoxAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust;
private: System::Windows::Forms::Label^  labelAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust;





private: System::Windows::Forms::HScrollBar^  ScrollBarAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust;
private: System::Windows::Forms::Button^  buttonSetUpDrumKit;
private: System::Windows::Forms::TextBox^  textBoxNumberFramesToLearnBG;

private: System::Windows::Forms::Label^  labelNumberFramesToLearnBG;

private: System::Windows::Forms::HScrollBar^  ScrollBarNumberFramesToLearnBG;


































			 Thread ^l_threadPlaySounds2;	// THREADING
private: System::Windows::Forms::Button^  buttonMeasurePrecision;
private: System::Windows::Forms::TextBox^  textBoxMeasurePrecision;
private: System::Windows::Forms::GroupBox^  groupBoxMeasurePositionsMarker1;
private: System::Windows::Forms::GroupBox^  groupBoxPositioningDrumsTimesIntervals;
private: System::Windows::Forms::TextBox^  textBoxTimeToSitDownInPlayingSpot;

private: System::Windows::Forms::Label^  labelTimeToSitDownInPlayingSpot;
private: System::Windows::Forms::HScrollBar^  ScrollBarTimeToSitDownInPlayingSpot;
private: System::Windows::Forms::TextBox^  textBoxTimeToWaitForAveragingPositionOfMarker;



private: System::Windows::Forms::Label^  labelTimeToWaitForAveragingPositionOfMarker;
private: System::Windows::Forms::HScrollBar^  ScrollBarTimeToWaitForAveragingPositionOfMarker;


private: System::Windows::Forms::TextBox^  textBoxTimeToPlaceMarkerInDesiredPosition;

private: System::Windows::Forms::Label^  labelTimeToPlaceMarkerInDesiredPosition;
private: System::Windows::Forms::HScrollBar^  ScrollBarTimeToPlaceMarkerInDesiredPosition;
private: System::Windows::Forms::TextBox^  textBoxCalibrationActualProcessNumberOfFrames;

private: System::Windows::Forms::Label^  labelCalibrationActualProcessNumberOfFrames;
private: System::Windows::Forms::HScrollBar^  ScrollBarCalibrationActualProcessNumberOfFrames;




		 Thread ^l_threadLongTimeRefreshingLoop;	// THREADING
			 
			 

		///////////////// END OF MY STUFF



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->buttonStart = (gcnew System::Windows::Forms::Button());
			this->textBoxColorFactorBounds = (gcnew System::Windows::Forms::TextBox());
			this->labelColorFactorBounds = (gcnew System::Windows::Forms::Label());
			this->scrollbarColorFactorBounds = (gcnew System::Windows::Forms::HScrollBar());
			this->textBoxSaturationFactorBounds = (gcnew System::Windows::Forms::TextBox());
			this->labelSaturationFactorBounds = (gcnew System::Windows::Forms::Label());
			this->scrollbarSaturationFactorBounds = (gcnew System::Windows::Forms::HScrollBar());
			this->buttonCalibrate = (gcnew System::Windows::Forms::Button());
			this->buttonInterface3D = (gcnew System::Windows::Forms::Button());
			this->textBoxRotationAngleZ = (gcnew System::Windows::Forms::TextBox());
			this->labelRotationAngleZ = (gcnew System::Windows::Forms::Label());
			this->ScrollBarRotationAngleZ = (gcnew System::Windows::Forms::HScrollBar());
			this->textBoxRotationAngleY = (gcnew System::Windows::Forms::TextBox());
			this->labelRotationAngleY = (gcnew System::Windows::Forms::Label());
			this->ScrollBarRotationAngleY = (gcnew System::Windows::Forms::HScrollBar());
			this->textBoxRotationAngleX = (gcnew System::Windows::Forms::TextBox());
			this->labelRotationAngleX = (gcnew System::Windows::Forms::Label());
			this->ScrollBarRotationAngleX = (gcnew System::Windows::Forms::HScrollBar());
			this->checkBoxLeftCameraView = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxRightCameraView = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxCalibrationType = (gcnew System::Windows::Forms::CheckBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->checkBoxVolumeControl = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxCalibrateCamerasIntrinsicDistortion = (gcnew System::Windows::Forms::CheckBox());
			this->comboBoxCamerasImageSize = (gcnew System::Windows::Forms::ComboBox());
			this->labelCamerasImageSize = (gcnew System::Windows::Forms::Label());
			this->groupBoxProcessingParameteres = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxNumberFramesToLearnBG = (gcnew System::Windows::Forms::TextBox());
			this->labelNumberFramesToLearnBG = (gcnew System::Windows::Forms::Label());
			this->ScrollBarNumberFramesToLearnBG = (gcnew System::Windows::Forms::HScrollBar());
			this->textBoxCodebookCbBounds = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxUseBackgroundSubtraction = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxLookOnMarkerSaturation = (gcnew System::Windows::Forms::CheckBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->scrollbarCodebookCbBounds = (gcnew System::Windows::Forms::HScrollBar());
			this->textBoxCodebookModMax = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->checkBoxAutoAdjustOnOff = (gcnew System::Windows::Forms::CheckBox());
			this->scrollbarCodebookModMax = (gcnew System::Windows::Forms::HScrollBar());
			this->textBoxCodebookModMin = (gcnew System::Windows::Forms::TextBox());
			this->labelFilterSize = (gcnew System::Windows::Forms::Label());
			this->scrollbarCodebookModMin = (gcnew System::Windows::Forms::HScrollBar());
			this->groupBoxInterface3D = (gcnew System::Windows::Forms::GroupBox());
			this->groupBoxCalibrations = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxCalibrationActualProcessNumberOfFrames = (gcnew System::Windows::Forms::TextBox());
			this->labelCalibrationActualProcessNumberOfFrames = (gcnew System::Windows::Forms::Label());
			this->ScrollBarCalibrationActualProcessNumberOfFrames = (gcnew System::Windows::Forms::HScrollBar());
			this->scrollBarChessboardCornersNumberX = (gcnew System::Windows::Forms::HScrollBar());
			this->labelChessboardCornersNumberX = (gcnew System::Windows::Forms::Label());
			this->textBoxChessboardCornersNumberX = (gcnew System::Windows::Forms::TextBox());
			this->textBoxAngleOfCameraSeeingInDegree = (gcnew System::Windows::Forms::TextBox());
			this->textBoxChessboardCornersNumberY = (gcnew System::Windows::Forms::TextBox());
			this->scrollBarChessboardCornersNumberY = (gcnew System::Windows::Forms::HScrollBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->labelChessboardCornersNumberY = (gcnew System::Windows::Forms::Label());
			this->scrollBarAngleOfCameraSeeingInDegree = (gcnew System::Windows::Forms::HScrollBar());
			this->labelChessboardSqareSize = (gcnew System::Windows::Forms::Label());
			this->scrollBarChessboardSqareSize = (gcnew System::Windows::Forms::HScrollBar());
			this->textBoxChessboardSqareSize = (gcnew System::Windows::Forms::TextBox());
			this->groupBoxWindows = (gcnew System::Windows::Forms::GroupBox());
			this->checkBoxViewOnlyMasks = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxViewValue = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxViewSaturation = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxViewHue = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxViewColorSeparationWithoutBackgroundClosedSegment = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxViewColorSeparationWithoutBackgroundClosed = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxViewColorSeparationWithoutBackground = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxViewWitoutBackground = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxAdvanceSettings = (gcnew System::Windows::Forms::CheckBox());
			this->textBoxNumberOfDrums = (gcnew System::Windows::Forms::TextBox());
			this->labelNumberOfDrums = (gcnew System::Windows::Forms::Label());
			this->ScrollBarNumberOfDrums = (gcnew System::Windows::Forms::HScrollBar());
			this->comboBoxDrumsAudioSamples = (gcnew System::Windows::Forms::ComboBox());
			this->textBoxNumberOfDrumToChangeProperty = (gcnew System::Windows::Forms::TextBox());
			this->labelNumberOfDrumToChangeProperty = (gcnew System::Windows::Forms::Label());
			this->ScrollBarNumberOfDrumToChangeProperty = (gcnew System::Windows::Forms::HScrollBar());
			this->checkBoxEditDrums = (gcnew System::Windows::Forms::CheckBox());
			this->textBoxDrumPositionZ = (gcnew System::Windows::Forms::TextBox());
			this->labelDrumPositionZ = (gcnew System::Windows::Forms::Label());
			this->textBoxDrumPositionY = (gcnew System::Windows::Forms::TextBox());
			this->labelDrumPositionY = (gcnew System::Windows::Forms::Label());
			this->textBoxDrumPositionX = (gcnew System::Windows::Forms::TextBox());
			this->labelDrumPositionX = (gcnew System::Windows::Forms::Label());
			this->numericUpDownDrumPositionX = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDownDrumPositionY = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDownDrumPositionZ = (gcnew System::Windows::Forms::NumericUpDown());
			this->listBoxListOfDrums = (gcnew System::Windows::Forms::ListBox());
			this->groupBoxDrumsEdition = (gcnew System::Windows::Forms::GroupBox());
			this->buttonSetUpDrumKit = (gcnew System::Windows::Forms::Button());
			this->textBoxDrumsDepth = (gcnew System::Windows::Forms::TextBox());
			this->labelDrumSoundSample = (gcnew System::Windows::Forms::Label());
			this->labelDrumsDepth = (gcnew System::Windows::Forms::Label());
			this->scrollBarDrumsDepth = (gcnew System::Windows::Forms::HScrollBar());
			this->textBoxDrumsWidth = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->scrollBarDrumsWidth = (gcnew System::Windows::Forms::HScrollBar());
			this->groupBoxAutoAdjustProcessingParameters = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxAutoAdjustGoodResultsPercentageAfterColorFactorAdjust = (gcnew System::Windows::Forms::TextBox());
			this->labelAutoAdjustGoodResultsPercentageAfterColorFactorAdjust = (gcnew System::Windows::Forms::Label());
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterColorFactorAdjust = (gcnew System::Windows::Forms::HScrollBar());
			this->textBoxAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust = (gcnew System::Windows::Forms::TextBox());
			this->labelAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust = (gcnew System::Windows::Forms::Label());
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust = (gcnew System::Windows::Forms::HScrollBar());
			this->textBoxAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust = (gcnew System::Windows::Forms::TextBox());
			this->labelAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust = (gcnew System::Windows::Forms::Label());
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust = (gcnew System::Windows::Forms::HScrollBar());
			this->textBoxAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust = (gcnew System::Windows::Forms::TextBox());
			this->labelAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust = (gcnew System::Windows::Forms::Label());
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust = (gcnew System::Windows::Forms::HScrollBar());
			this->buttonRefreshAutoAdjust = (gcnew System::Windows::Forms::Button());
			this->buttonMeasurePrecision = (gcnew System::Windows::Forms::Button());
			this->textBoxMeasurePrecision = (gcnew System::Windows::Forms::TextBox());
			this->groupBoxMeasurePositionsMarker1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBoxPositioningDrumsTimesIntervals = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxTimeToWaitForAveragingPositionOfMarker = (gcnew System::Windows::Forms::TextBox());
			this->labelTimeToWaitForAveragingPositionOfMarker = (gcnew System::Windows::Forms::Label());
			this->ScrollBarTimeToWaitForAveragingPositionOfMarker = (gcnew System::Windows::Forms::HScrollBar());
			this->textBoxTimeToPlaceMarkerInDesiredPosition = (gcnew System::Windows::Forms::TextBox());
			this->labelTimeToPlaceMarkerInDesiredPosition = (gcnew System::Windows::Forms::Label());
			this->ScrollBarTimeToPlaceMarkerInDesiredPosition = (gcnew System::Windows::Forms::HScrollBar());
			this->textBoxTimeToSitDownInPlayingSpot = (gcnew System::Windows::Forms::TextBox());
			this->labelTimeToSitDownInPlayingSpot = (gcnew System::Windows::Forms::Label());
			this->ScrollBarTimeToSitDownInPlayingSpot = (gcnew System::Windows::Forms::HScrollBar());
			this->menuStrip1->SuspendLayout();
			this->groupBoxProcessingParameteres->SuspendLayout();
			this->groupBoxInterface3D->SuspendLayout();
			this->groupBoxCalibrations->SuspendLayout();
			this->groupBoxWindows->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownDrumPositionX))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownDrumPositionY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownDrumPositionZ))->BeginInit();
			this->groupBoxDrumsEdition->SuspendLayout();
			this->groupBoxAutoAdjustProcessingParameters->SuspendLayout();
			this->groupBoxMeasurePositionsMarker1->SuspendLayout();
			this->groupBoxPositioningDrumsTimesIntervals->SuspendLayout();
			this->SuspendLayout();
			// 
			// buttonStart
			// 
			this->buttonStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->buttonStart->Location = System::Drawing::Point(12, 27);
			this->buttonStart->Name = L"buttonStart";
			this->buttonStart->Size = System::Drawing::Size(132, 30);
			this->buttonStart->TabIndex = 0;
			this->buttonStart->Text = L"START";
			this->buttonStart->UseVisualStyleBackColor = true;
			this->buttonStart->Click += gcnew System::EventHandler(this, &Form1::buttonStart_Click);
			// 
			// textBoxColorFactorBounds
			// 
			this->textBoxColorFactorBounds->Location = System::Drawing::Point(153, 84);
			this->textBoxColorFactorBounds->Name = L"textBoxColorFactorBounds";
			this->textBoxColorFactorBounds->ReadOnly = true;
			this->textBoxColorFactorBounds->Size = System::Drawing::Size(33, 20);
			this->textBoxColorFactorBounds->TabIndex = 42;
			this->textBoxColorFactorBounds->Text = L"3";
			// 
			// labelColorFactorBounds
			// 
			this->labelColorFactorBounds->AutoSize = true;
			this->labelColorFactorBounds->Location = System::Drawing::Point(6, 71);
			this->labelColorFactorBounds->Name = L"labelColorFactorBounds";
			this->labelColorFactorBounds->Size = System::Drawing::Size(156, 13);
			this->labelColorFactorBounds->TabIndex = 40;
			this->labelColorFactorBounds->Text = L"Color factor bounds (factor*sdv)";
			// 
			// scrollbarColorFactorBounds
			// 
			this->scrollbarColorFactorBounds->LargeChange = 4;
			this->scrollbarColorFactorBounds->Location = System::Drawing::Point(9, 84);
			this->scrollbarColorFactorBounds->Maximum = 50;
			this->scrollbarColorFactorBounds->Minimum = 1;
			this->scrollbarColorFactorBounds->Name = L"scrollbarColorFactorBounds";
			this->scrollbarColorFactorBounds->Size = System::Drawing::Size(130, 20);
			this->scrollbarColorFactorBounds->TabIndex = 41;
			this->scrollbarColorFactorBounds->Value = 3;
			this->scrollbarColorFactorBounds->ValueChanged += gcnew System::EventHandler(this, &Form1::scrollbarColorFactorBounds_ValueChanged);
			// 
			// textBoxSaturationFactorBounds
			// 
			this->textBoxSaturationFactorBounds->Location = System::Drawing::Point(153, 129);
			this->textBoxSaturationFactorBounds->Name = L"textBoxSaturationFactorBounds";
			this->textBoxSaturationFactorBounds->ReadOnly = true;
			this->textBoxSaturationFactorBounds->Size = System::Drawing::Size(33, 20);
			this->textBoxSaturationFactorBounds->TabIndex = 45;
			this->textBoxSaturationFactorBounds->Text = L"3";
			// 
			// labelSaturationFactorBounds
			// 
			this->labelSaturationFactorBounds->AutoSize = true;
			this->labelSaturationFactorBounds->Location = System::Drawing::Point(6, 116);
			this->labelSaturationFactorBounds->Name = L"labelSaturationFactorBounds";
			this->labelSaturationFactorBounds->Size = System::Drawing::Size(180, 13);
			this->labelSaturationFactorBounds->TabIndex = 43;
			this->labelSaturationFactorBounds->Text = L"Saturation factor bounds (factor*sdv)";
			// 
			// scrollbarSaturationFactorBounds
			// 
			this->scrollbarSaturationFactorBounds->LargeChange = 4;
			this->scrollbarSaturationFactorBounds->Location = System::Drawing::Point(9, 129);
			this->scrollbarSaturationFactorBounds->Maximum = 50;
			this->scrollbarSaturationFactorBounds->Name = L"scrollbarSaturationFactorBounds";
			this->scrollbarSaturationFactorBounds->Size = System::Drawing::Size(130, 20);
			this->scrollbarSaturationFactorBounds->TabIndex = 44;
			this->scrollbarSaturationFactorBounds->ValueChanged += gcnew System::EventHandler(this, &Form1::scrollbarSaturationFactorBounds_ValueChanged);
			// 
			// buttonCalibrate
			// 
			this->buttonCalibrate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->buttonCalibrate->Location = System::Drawing::Point(119, 325);
			this->buttonCalibrate->Name = L"buttonCalibrate";
			this->buttonCalibrate->Size = System::Drawing::Size(100, 25);
			this->buttonCalibrate->TabIndex = 46;
			this->buttonCalibrate->Text = L"Calibrate";
			this->buttonCalibrate->UseVisualStyleBackColor = true;
			this->buttonCalibrate->Click += gcnew System::EventHandler(this, &Form1::buttonCalibrate_Click);
			// 
			// buttonInterface3D
			// 
			this->buttonInterface3D->Enabled = false;
			this->buttonInterface3D->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->buttonInterface3D->Location = System::Drawing::Point(49, 16);
			this->buttonInterface3D->Name = L"buttonInterface3D";
			this->buttonInterface3D->Size = System::Drawing::Size(100, 25);
			this->buttonInterface3D->TabIndex = 47;
			this->buttonInterface3D->Text = L"Interface 3D";
			this->buttonInterface3D->UseVisualStyleBackColor = true;
			this->buttonInterface3D->Visible = false;
			this->buttonInterface3D->Click += gcnew System::EventHandler(this, &Form1::buttonInterface3D_Click);
			// 
			// textBoxRotationAngleZ
			// 
			this->textBoxRotationAngleZ->Location = System::Drawing::Point(147, 150);
			this->textBoxRotationAngleZ->Name = L"textBoxRotationAngleZ";
			this->textBoxRotationAngleZ->ReadOnly = true;
			this->textBoxRotationAngleZ->Size = System::Drawing::Size(33, 20);
			this->textBoxRotationAngleZ->TabIndex = 56;
			this->textBoxRotationAngleZ->Text = L"0";
			// 
			// labelRotationAngleZ
			// 
			this->labelRotationAngleZ->AutoSize = true;
			this->labelRotationAngleZ->Location = System::Drawing::Point(5, 137);
			this->labelRotationAngleZ->Name = L"labelRotationAngleZ";
			this->labelRotationAngleZ->Size = System::Drawing::Size(128, 13);
			this->labelRotationAngleZ->TabIndex = 54;
			this->labelRotationAngleZ->Text = L"Rotation angle Z (degree)";
			// 
			// ScrollBarRotationAngleZ
			// 
			this->ScrollBarRotationAngleZ->Location = System::Drawing::Point(8, 150);
			this->ScrollBarRotationAngleZ->Maximum = 180;
			this->ScrollBarRotationAngleZ->Minimum = -180;
			this->ScrollBarRotationAngleZ->Name = L"ScrollBarRotationAngleZ";
			this->ScrollBarRotationAngleZ->Size = System::Drawing::Size(130, 20);
			this->ScrollBarRotationAngleZ->TabIndex = 55;
			this->ScrollBarRotationAngleZ->ValueChanged += gcnew System::EventHandler(this, &Form1::ScrollBarRotationAngleZ_ValueChanged);
			// 
			// textBoxRotationAngleY
			// 
			this->textBoxRotationAngleY->Location = System::Drawing::Point(147, 105);
			this->textBoxRotationAngleY->Name = L"textBoxRotationAngleY";
			this->textBoxRotationAngleY->ReadOnly = true;
			this->textBoxRotationAngleY->Size = System::Drawing::Size(33, 20);
			this->textBoxRotationAngleY->TabIndex = 53;
			this->textBoxRotationAngleY->Text = L"0";
			// 
			// labelRotationAngleY
			// 
			this->labelRotationAngleY->AutoSize = true;
			this->labelRotationAngleY->Location = System::Drawing::Point(5, 92);
			this->labelRotationAngleY->Name = L"labelRotationAngleY";
			this->labelRotationAngleY->Size = System::Drawing::Size(128, 13);
			this->labelRotationAngleY->TabIndex = 51;
			this->labelRotationAngleY->Text = L"Rotation angle Y (degree)";
			// 
			// ScrollBarRotationAngleY
			// 
			this->ScrollBarRotationAngleY->Location = System::Drawing::Point(8, 105);
			this->ScrollBarRotationAngleY->Maximum = 180;
			this->ScrollBarRotationAngleY->Minimum = -180;
			this->ScrollBarRotationAngleY->Name = L"ScrollBarRotationAngleY";
			this->ScrollBarRotationAngleY->Size = System::Drawing::Size(130, 20);
			this->ScrollBarRotationAngleY->TabIndex = 52;
			this->ScrollBarRotationAngleY->ValueChanged += gcnew System::EventHandler(this, &Form1::ScrollBarRotationAngleY_ValueChanged);
			// 
			// textBoxRotationAngleX
			// 
			this->textBoxRotationAngleX->Location = System::Drawing::Point(147, 61);
			this->textBoxRotationAngleX->Name = L"textBoxRotationAngleX";
			this->textBoxRotationAngleX->ReadOnly = true;
			this->textBoxRotationAngleX->Size = System::Drawing::Size(33, 20);
			this->textBoxRotationAngleX->TabIndex = 50;
			this->textBoxRotationAngleX->Text = L"0";
			// 
			// labelRotationAngleX
			// 
			this->labelRotationAngleX->AutoSize = true;
			this->labelRotationAngleX->Location = System::Drawing::Point(5, 48);
			this->labelRotationAngleX->Name = L"labelRotationAngleX";
			this->labelRotationAngleX->Size = System::Drawing::Size(128, 13);
			this->labelRotationAngleX->TabIndex = 48;
			this->labelRotationAngleX->Text = L"Rotation angle X (degree)";
			// 
			// ScrollBarRotationAngleX
			// 
			this->ScrollBarRotationAngleX->Location = System::Drawing::Point(8, 61);
			this->ScrollBarRotationAngleX->Maximum = 180;
			this->ScrollBarRotationAngleX->Minimum = -180;
			this->ScrollBarRotationAngleX->Name = L"ScrollBarRotationAngleX";
			this->ScrollBarRotationAngleX->Size = System::Drawing::Size(130, 20);
			this->ScrollBarRotationAngleX->TabIndex = 49;
			this->ScrollBarRotationAngleX->ValueChanged += gcnew System::EventHandler(this, &Form1::ScrollBarRotationAngleX_ValueChanged);
			// 
			// checkBoxLeftCameraView
			// 
			this->checkBoxLeftCameraView->AutoSize = true;
			this->checkBoxLeftCameraView->Checked = true;
			this->checkBoxLeftCameraView->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxLeftCameraView->Enabled = false;
			this->checkBoxLeftCameraView->Location = System::Drawing::Point(6, 19);
			this->checkBoxLeftCameraView->Name = L"checkBoxLeftCameraView";
			this->checkBoxLeftCameraView->Size = System::Drawing::Size(107, 17);
			this->checkBoxLeftCameraView->TabIndex = 57;
			this->checkBoxLeftCameraView->Text = L"Left camera view";
			this->checkBoxLeftCameraView->UseVisualStyleBackColor = true;
			this->checkBoxLeftCameraView->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxLeftCameraView_CheckedChanged);
			// 
			// checkBoxRightCameraView
			// 
			this->checkBoxRightCameraView->AutoSize = true;
			this->checkBoxRightCameraView->Location = System::Drawing::Point(159, 19);
			this->checkBoxRightCameraView->Name = L"checkBoxRightCameraView";
			this->checkBoxRightCameraView->Size = System::Drawing::Size(114, 17);
			this->checkBoxRightCameraView->TabIndex = 58;
			this->checkBoxRightCameraView->Text = L"Right camera view";
			this->checkBoxRightCameraView->UseVisualStyleBackColor = true;
			this->checkBoxRightCameraView->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxRightCameraView_CheckedChanged);
			// 
			// checkBoxCalibrationType
			// 
			this->checkBoxCalibrationType->AutoSize = true;
			this->checkBoxCalibrationType->Location = System::Drawing::Point(7, 303);
			this->checkBoxCalibrationType->Name = L"checkBoxCalibrationType";
			this->checkBoxCalibrationType->Size = System::Drawing::Size(144, 30);
			this->checkBoxCalibrationType->TabIndex = 62;
			this->checkBoxCalibrationType->Text = L"Cameras calibration type:\r\n- Saved calibration";
			this->checkBoxCalibrationType->UseVisualStyleBackColor = true;
			this->checkBoxCalibrationType->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxCalibrationType_CheckedChanged);
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->aboutToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1175, 24);
			this->menuStrip1->TabIndex = 68;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(62, 20);
			this->aboutToolStripMenuItem->Text = L"Readme";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::aboutToolStripMenuItem_Click);
			// 
			// checkBoxVolumeControl
			// 
			this->checkBoxVolumeControl->AutoSize = true;
			this->checkBoxVolumeControl->Checked = true;
			this->checkBoxVolumeControl->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxVolumeControl->Location = System::Drawing::Point(12, 63);
			this->checkBoxVolumeControl->Name = L"checkBoxVolumeControl";
			this->checkBoxVolumeControl->Size = System::Drawing::Size(100, 56);
			this->checkBoxVolumeControl->TabIndex = 69;
			this->checkBoxVolumeControl->Text = L"Volume control\r\n    On - dynamic\r\n    Mid - static\r\n    Off - mute";
			this->checkBoxVolumeControl->ThreeState = true;
			this->checkBoxVolumeControl->UseVisualStyleBackColor = true;
			// 
			// checkBoxCalibrateCamerasIntrinsicDistortion
			// 
			this->checkBoxCalibrateCamerasIntrinsicDistortion->AutoSize = true;
			this->checkBoxCalibrateCamerasIntrinsicDistortion->Location = System::Drawing::Point(7, 267);
			this->checkBoxCalibrateCamerasIntrinsicDistortion->Name = L"checkBoxCalibrateCamerasIntrinsicDistortion";
			this->checkBoxCalibrateCamerasIntrinsicDistortion->Size = System::Drawing::Size(219, 30);
			this->checkBoxCalibrateCamerasIntrinsicDistortion->TabIndex = 70;
			this->checkBoxCalibrateCamerasIntrinsicDistortion->Text = L"Calibrate cameras intrinsic and distorions:\r\n - No";
			this->checkBoxCalibrateCamerasIntrinsicDistortion->UseVisualStyleBackColor = true;
			this->checkBoxCalibrateCamerasIntrinsicDistortion->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxCalibrateCamerasIntrinsicDistortion_CheckedChanged);
			// 
			// comboBoxCamerasImageSize
			// 
			this->comboBoxCamerasImageSize->DisplayMember = L"2";
			this->comboBoxCamerasImageSize->FormattingEnabled = true;
			this->comboBoxCamerasImageSize->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"800 x 600 (not recommended)", 
				L"640 x 480", L"320 x 240 (default)"});
			this->comboBoxCamerasImageSize->Location = System::Drawing::Point(9, 34);
			this->comboBoxCamerasImageSize->Name = L"comboBoxCamerasImageSize";
			this->comboBoxCamerasImageSize->Size = System::Drawing::Size(121, 21);
			this->comboBoxCamerasImageSize->TabIndex = 71;
			this->comboBoxCamerasImageSize->Text = L"320 x 240 (default)";
			this->comboBoxCamerasImageSize->ValueMember = L"2";
			this->comboBoxCamerasImageSize->TextUpdate += gcnew System::EventHandler(this, &Form1::comboBoxCamerasImageSize_TextUpdate);
			this->comboBoxCamerasImageSize->TextChanged += gcnew System::EventHandler(this, &Form1::comboBoxCamerasImageSize_TextChanged);
			// 
			// labelCamerasImageSize
			// 
			this->labelCamerasImageSize->AutoSize = true;
			this->labelCamerasImageSize->Location = System::Drawing::Point(6, 17);
			this->labelCamerasImageSize->Name = L"labelCamerasImageSize";
			this->labelCamerasImageSize->Size = System::Drawing::Size(103, 13);
			this->labelCamerasImageSize->TabIndex = 72;
			this->labelCamerasImageSize->Text = L"Cameras image size:";
			// 
			// groupBoxProcessingParameteres
			// 
			this->groupBoxProcessingParameteres->BackColor = System::Drawing::SystemColors::ControlLight;
			this->groupBoxProcessingParameteres->Controls->Add(this->textBoxNumberFramesToLearnBG);
			this->groupBoxProcessingParameteres->Controls->Add(this->labelNumberFramesToLearnBG);
			this->groupBoxProcessingParameteres->Controls->Add(this->ScrollBarNumberFramesToLearnBG);
			this->groupBoxProcessingParameteres->Controls->Add(this->textBoxCodebookCbBounds);
			this->groupBoxProcessingParameteres->Controls->Add(this->checkBoxUseBackgroundSubtraction);
			this->groupBoxProcessingParameteres->Controls->Add(this->checkBoxLookOnMarkerSaturation);
			this->groupBoxProcessingParameteres->Controls->Add(this->label2);
			this->groupBoxProcessingParameteres->Controls->Add(this->textBoxSaturationFactorBounds);
			this->groupBoxProcessingParameteres->Controls->Add(this->scrollbarCodebookCbBounds);
			this->groupBoxProcessingParameteres->Controls->Add(this->labelSaturationFactorBounds);
			this->groupBoxProcessingParameteres->Controls->Add(this->labelCamerasImageSize);
			this->groupBoxProcessingParameteres->Controls->Add(this->comboBoxCamerasImageSize);
			this->groupBoxProcessingParameteres->Controls->Add(this->textBoxCodebookModMax);
			this->groupBoxProcessingParameteres->Controls->Add(this->scrollbarSaturationFactorBounds);
			this->groupBoxProcessingParameteres->Controls->Add(this->label1);
			this->groupBoxProcessingParameteres->Controls->Add(this->textBoxColorFactorBounds);
			this->groupBoxProcessingParameteres->Controls->Add(this->checkBoxAutoAdjustOnOff);
			this->groupBoxProcessingParameteres->Controls->Add(this->scrollbarCodebookModMax);
			this->groupBoxProcessingParameteres->Controls->Add(this->labelColorFactorBounds);
			this->groupBoxProcessingParameteres->Controls->Add(this->textBoxCodebookModMin);
			this->groupBoxProcessingParameteres->Controls->Add(this->scrollbarColorFactorBounds);
			this->groupBoxProcessingParameteres->Controls->Add(this->labelFilterSize);
			this->groupBoxProcessingParameteres->Controls->Add(this->scrollbarCodebookModMin);
			this->groupBoxProcessingParameteres->Location = System::Drawing::Point(369, 275);
			this->groupBoxProcessingParameteres->Name = L"groupBoxProcessingParameteres";
			this->groupBoxProcessingParameteres->Size = System::Drawing::Size(303, 370);
			this->groupBoxProcessingParameteres->TabIndex = 73;
			this->groupBoxProcessingParameteres->TabStop = false;
			this->groupBoxProcessingParameteres->Text = L"Processing parameters";
			// 
			// textBoxNumberFramesToLearnBG
			// 
			this->textBoxNumberFramesToLearnBG->Location = System::Drawing::Point(153, 339);
			this->textBoxNumberFramesToLearnBG->Name = L"textBoxNumberFramesToLearnBG";
			this->textBoxNumberFramesToLearnBG->ReadOnly = true;
			this->textBoxNumberFramesToLearnBG->Size = System::Drawing::Size(33, 20);
			this->textBoxNumberFramesToLearnBG->TabIndex = 75;
			this->textBoxNumberFramesToLearnBG->Text = L"200";
			// 
			// labelNumberFramesToLearnBG
			// 
			this->labelNumberFramesToLearnBG->AutoSize = true;
			this->labelNumberFramesToLearnBG->Location = System::Drawing::Point(6, 326);
			this->labelNumberFramesToLearnBG->Name = L"labelNumberFramesToLearnBG";
			this->labelNumberFramesToLearnBG->Size = System::Drawing::Size(188, 13);
			this->labelNumberFramesToLearnBG->TabIndex = 73;
			this->labelNumberFramesToLearnBG->Text = L"Number of frames to learn background";
			// 
			// ScrollBarNumberFramesToLearnBG
			// 
			this->ScrollBarNumberFramesToLearnBG->LargeChange = 50;
			this->ScrollBarNumberFramesToLearnBG->Location = System::Drawing::Point(9, 339);
			this->ScrollBarNumberFramesToLearnBG->Maximum = 2000;
			this->ScrollBarNumberFramesToLearnBG->Minimum = 40;
			this->ScrollBarNumberFramesToLearnBG->Name = L"ScrollBarNumberFramesToLearnBG";
			this->ScrollBarNumberFramesToLearnBG->Size = System::Drawing::Size(130, 20);
			this->ScrollBarNumberFramesToLearnBG->SmallChange = 5;
			this->ScrollBarNumberFramesToLearnBG->TabIndex = 74;
			this->ScrollBarNumberFramesToLearnBG->Value = 200;
			this->ScrollBarNumberFramesToLearnBG->ValueChanged += gcnew System::EventHandler(this, &Form1::ScrollBarNumberFramesToLearnBG_ValueChanged);
			// 
			// textBoxCodebookCbBounds
			// 
			this->textBoxCodebookCbBounds->Location = System::Drawing::Point(153, 280);
			this->textBoxCodebookCbBounds->Name = L"textBoxCodebookCbBounds";
			this->textBoxCodebookCbBounds->ReadOnly = true;
			this->textBoxCodebookCbBounds->Size = System::Drawing::Size(33, 20);
			this->textBoxCodebookCbBounds->TabIndex = 39;
			this->textBoxCodebookCbBounds->Text = L"10";
			// 
			// checkBoxUseBackgroundSubtraction
			// 
			this->checkBoxUseBackgroundSubtraction->AutoSize = true;
			this->checkBoxUseBackgroundSubtraction->Checked = true;
			this->checkBoxUseBackgroundSubtraction->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxUseBackgroundSubtraction->Location = System::Drawing::Point(192, 235);
			this->checkBoxUseBackgroundSubtraction->Name = L"checkBoxUseBackgroundSubtraction";
			this->checkBoxUseBackgroundSubtraction->Size = System::Drawing::Size(108, 30);
			this->checkBoxUseBackgroundSubtraction->TabIndex = 68;
			this->checkBoxUseBackgroundSubtraction->Text = L"Use background \r\nsubtraction";
			this->checkBoxUseBackgroundSubtraction->UseVisualStyleBackColor = true;
			this->checkBoxUseBackgroundSubtraction->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxUseBackgroundSubtraction_CheckedChanged);
			// 
			// checkBoxLookOnMarkerSaturation
			// 
			this->checkBoxLookOnMarkerSaturation->AutoSize = true;
			this->checkBoxLookOnMarkerSaturation->Location = System::Drawing::Point(192, 126);
			this->checkBoxLookOnMarkerSaturation->Name = L"checkBoxLookOnMarkerSaturation";
			this->checkBoxLookOnMarkerSaturation->Size = System::Drawing::Size(103, 30);
			this->checkBoxLookOnMarkerSaturation->TabIndex = 67;
			this->checkBoxLookOnMarkerSaturation->Text = L"Look on marker \r\nsaturation";
			this->checkBoxLookOnMarkerSaturation->UseVisualStyleBackColor = true;
			this->checkBoxLookOnMarkerSaturation->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxLookOnMarkerSaturation_CheckedChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 267);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(109, 13);
			this->label2->TabIndex = 37;
			this->label2->Text = L"Codebook cb bounds";
			// 
			// scrollbarCodebookCbBounds
			// 
			this->scrollbarCodebookCbBounds->LargeChange = 4;
			this->scrollbarCodebookCbBounds->Location = System::Drawing::Point(9, 280);
			this->scrollbarCodebookCbBounds->Maximum = 30;
			this->scrollbarCodebookCbBounds->Minimum = 1;
			this->scrollbarCodebookCbBounds->Name = L"scrollbarCodebookCbBounds";
			this->scrollbarCodebookCbBounds->Size = System::Drawing::Size(130, 20);
			this->scrollbarCodebookCbBounds->TabIndex = 38;
			this->scrollbarCodebookCbBounds->Value = 12;
			this->scrollbarCodebookCbBounds->ValueChanged += gcnew System::EventHandler(this, &Form1::scrollbarCodebookCbBounds_ValueChanged);
			// 
			// textBoxCodebookModMax
			// 
			this->textBoxCodebookModMax->Location = System::Drawing::Point(153, 238);
			this->textBoxCodebookModMax->Name = L"textBoxCodebookModMax";
			this->textBoxCodebookModMax->ReadOnly = true;
			this->textBoxCodebookModMax->Size = System::Drawing::Size(33, 20);
			this->textBoxCodebookModMax->TabIndex = 36;
			this->textBoxCodebookModMax->Text = L"6";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 225);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(101, 13);
			this->label1->TabIndex = 34;
			this->label1->Text = L"Codebook mod max";
			// 
			// checkBoxAutoAdjustOnOff
			// 
			this->checkBoxAutoAdjustOnOff->AutoSize = true;
			this->checkBoxAutoAdjustOnOff->Checked = true;
			this->checkBoxAutoAdjustOnOff->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxAutoAdjustOnOff->Location = System::Drawing::Point(165, 19);
			this->checkBoxAutoAdjustOnOff->Name = L"checkBoxAutoAdjustOnOff";
			this->checkBoxAutoAdjustOnOff->Size = System::Drawing::Size(132, 30);
			this->checkBoxAutoAdjustOnOff->TabIndex = 70;
			this->checkBoxAutoAdjustOnOff->Text = L"Manual / Auto adjust \r\nprocessing parameters";
			this->checkBoxAutoAdjustOnOff->UseVisualStyleBackColor = true;
			this->checkBoxAutoAdjustOnOff->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxAutoAdjustOnOff_CheckedChanged);
			// 
			// scrollbarCodebookModMax
			// 
			this->scrollbarCodebookModMax->LargeChange = 2;
			this->scrollbarCodebookModMax->Location = System::Drawing::Point(9, 238);
			this->scrollbarCodebookModMax->Maximum = 20;
			this->scrollbarCodebookModMax->Minimum = 1;
			this->scrollbarCodebookModMax->Name = L"scrollbarCodebookModMax";
			this->scrollbarCodebookModMax->Size = System::Drawing::Size(130, 20);
			this->scrollbarCodebookModMax->TabIndex = 35;
			this->scrollbarCodebookModMax->Value = 6;
			this->scrollbarCodebookModMax->ValueChanged += gcnew System::EventHandler(this, &Form1::scrollbarCodebookModMax_ValueChanged);
			// 
			// textBoxCodebookModMin
			// 
			this->textBoxCodebookModMin->Location = System::Drawing::Point(153, 196);
			this->textBoxCodebookModMin->Name = L"textBoxCodebookModMin";
			this->textBoxCodebookModMin->ReadOnly = true;
			this->textBoxCodebookModMin->Size = System::Drawing::Size(33, 20);
			this->textBoxCodebookModMin->TabIndex = 33;
			this->textBoxCodebookModMin->Text = L"6";
			// 
			// labelFilterSize
			// 
			this->labelFilterSize->AutoSize = true;
			this->labelFilterSize->Location = System::Drawing::Point(6, 183);
			this->labelFilterSize->Name = L"labelFilterSize";
			this->labelFilterSize->Size = System::Drawing::Size(98, 13);
			this->labelFilterSize->TabIndex = 31;
			this->labelFilterSize->Text = L"Codebook mod min";
			// 
			// scrollbarCodebookModMin
			// 
			this->scrollbarCodebookModMin->LargeChange = 2;
			this->scrollbarCodebookModMin->Location = System::Drawing::Point(9, 196);
			this->scrollbarCodebookModMin->Maximum = 20;
			this->scrollbarCodebookModMin->Minimum = 1;
			this->scrollbarCodebookModMin->Name = L"scrollbarCodebookModMin";
			this->scrollbarCodebookModMin->Size = System::Drawing::Size(130, 20);
			this->scrollbarCodebookModMin->TabIndex = 32;
			this->scrollbarCodebookModMin->Value = 6;
			this->scrollbarCodebookModMin->ValueChanged += gcnew System::EventHandler(this, &Form1::scrollbarCodebookModMin_ValueChanged);
			// 
			// groupBoxInterface3D
			// 
			this->groupBoxInterface3D->BackColor = System::Drawing::SystemColors::ControlLight;
			this->groupBoxInterface3D->Controls->Add(this->textBoxRotationAngleZ);
			this->groupBoxInterface3D->Controls->Add(this->labelRotationAngleZ);
			this->groupBoxInterface3D->Controls->Add(this->ScrollBarRotationAngleZ);
			this->groupBoxInterface3D->Controls->Add(this->textBoxRotationAngleY);
			this->groupBoxInterface3D->Controls->Add(this->labelRotationAngleY);
			this->groupBoxInterface3D->Controls->Add(this->ScrollBarRotationAngleY);
			this->groupBoxInterface3D->Controls->Add(this->textBoxRotationAngleX);
			this->groupBoxInterface3D->Controls->Add(this->labelRotationAngleX);
			this->groupBoxInterface3D->Controls->Add(this->ScrollBarRotationAngleX);
			this->groupBoxInterface3D->Controls->Add(this->buttonInterface3D);
			this->groupBoxInterface3D->Location = System::Drawing::Point(165, 82);
			this->groupBoxInterface3D->Name = L"groupBoxInterface3D";
			this->groupBoxInterface3D->Size = System::Drawing::Size(191, 187);
			this->groupBoxInterface3D->TabIndex = 74;
			this->groupBoxInterface3D->TabStop = false;
			this->groupBoxInterface3D->Text = L"Interface 3D view";
			// 
			// groupBoxCalibrations
			// 
			this->groupBoxCalibrations->BackColor = System::Drawing::SystemColors::ControlLight;
			this->groupBoxCalibrations->Controls->Add(this->textBoxCalibrationActualProcessNumberOfFrames);
			this->groupBoxCalibrations->Controls->Add(this->labelCalibrationActualProcessNumberOfFrames);
			this->groupBoxCalibrations->Controls->Add(this->ScrollBarCalibrationActualProcessNumberOfFrames);
			this->groupBoxCalibrations->Controls->Add(this->buttonCalibrate);
			this->groupBoxCalibrations->Controls->Add(this->scrollBarChessboardCornersNumberX);
			this->groupBoxCalibrations->Controls->Add(this->labelChessboardCornersNumberX);
			this->groupBoxCalibrations->Controls->Add(this->textBoxChessboardCornersNumberX);
			this->groupBoxCalibrations->Controls->Add(this->textBoxAngleOfCameraSeeingInDegree);
			this->groupBoxCalibrations->Controls->Add(this->textBoxChessboardCornersNumberY);
			this->groupBoxCalibrations->Controls->Add(this->checkBoxCalibrateCamerasIntrinsicDistortion);
			this->groupBoxCalibrations->Controls->Add(this->scrollBarChessboardCornersNumberY);
			this->groupBoxCalibrations->Controls->Add(this->label3);
			this->groupBoxCalibrations->Controls->Add(this->labelChessboardCornersNumberY);
			this->groupBoxCalibrations->Controls->Add(this->scrollBarAngleOfCameraSeeingInDegree);
			this->groupBoxCalibrations->Controls->Add(this->checkBoxCalibrationType);
			this->groupBoxCalibrations->Controls->Add(this->labelChessboardSqareSize);
			this->groupBoxCalibrations->Controls->Add(this->scrollBarChessboardSqareSize);
			this->groupBoxCalibrations->Controls->Add(this->textBoxChessboardSqareSize);
			this->groupBoxCalibrations->Location = System::Drawing::Point(678, 40);
			this->groupBoxCalibrations->Name = L"groupBoxCalibrations";
			this->groupBoxCalibrations->Size = System::Drawing::Size(225, 356);
			this->groupBoxCalibrations->TabIndex = 75;
			this->groupBoxCalibrations->TabStop = false;
			this->groupBoxCalibrations->Text = L"Calibrations";
			// 
			// textBoxCalibrationActualProcessNumberOfFrames
			// 
			this->textBoxCalibrationActualProcessNumberOfFrames->Location = System::Drawing::Point(153, 239);
			this->textBoxCalibrationActualProcessNumberOfFrames->Name = L"textBoxCalibrationActualProcessNumberOfFrames";
			this->textBoxCalibrationActualProcessNumberOfFrames->ReadOnly = true;
			this->textBoxCalibrationActualProcessNumberOfFrames->Size = System::Drawing::Size(33, 20);
			this->textBoxCalibrationActualProcessNumberOfFrames->TabIndex = 99;
			this->textBoxCalibrationActualProcessNumberOfFrames->Text = L"25";
			// 
			// labelCalibrationActualProcessNumberOfFrames
			// 
			this->labelCalibrationActualProcessNumberOfFrames->AutoSize = true;
			this->labelCalibrationActualProcessNumberOfFrames->Location = System::Drawing::Point(6, 226);
			this->labelCalibrationActualProcessNumberOfFrames->Name = L"labelCalibrationActualProcessNumberOfFrames";
			this->labelCalibrationActualProcessNumberOfFrames->Size = System::Drawing::Size(213, 13);
			this->labelCalibrationActualProcessNumberOfFrames->TabIndex = 97;
			this->labelCalibrationActualProcessNumberOfFrames->Text = L"Number of frames actual calibration process";
			// 
			// ScrollBarCalibrationActualProcessNumberOfFrames
			// 
			this->ScrollBarCalibrationActualProcessNumberOfFrames->Location = System::Drawing::Point(9, 239);
			this->ScrollBarCalibrationActualProcessNumberOfFrames->Maximum = 59;
			this->ScrollBarCalibrationActualProcessNumberOfFrames->Minimum = 10;
			this->ScrollBarCalibrationActualProcessNumberOfFrames->Name = L"ScrollBarCalibrationActualProcessNumberOfFrames";
			this->ScrollBarCalibrationActualProcessNumberOfFrames->Size = System::Drawing::Size(130, 20);
			this->ScrollBarCalibrationActualProcessNumberOfFrames->TabIndex = 98;
			this->ScrollBarCalibrationActualProcessNumberOfFrames->Value = 25;
			this->ScrollBarCalibrationActualProcessNumberOfFrames->ValueChanged += gcnew System::EventHandler(this, &Form1::ScrollBarCalibrationActualProcessNumberOfFrames_ValueChanged);
			// 
			// scrollBarChessboardCornersNumberX
			// 
			this->scrollBarChessboardCornersNumberX->Location = System::Drawing::Point(9, 83);
			this->scrollBarChessboardCornersNumberX->Maximum = 30;
			this->scrollBarChessboardCornersNumberX->Minimum = 3;
			this->scrollBarChessboardCornersNumberX->Name = L"scrollBarChessboardCornersNumberX";
			this->scrollBarChessboardCornersNumberX->Size = System::Drawing::Size(130, 20);
			this->scrollBarChessboardCornersNumberX->TabIndex = 89;
			this->scrollBarChessboardCornersNumberX->Value = 9;
			this->scrollBarChessboardCornersNumberX->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form1::scrollBarChessboardCornersNumberX_Scroll);
			// 
			// labelChessboardCornersNumberX
			// 
			this->labelChessboardCornersNumberX->AutoSize = true;
			this->labelChessboardCornersNumberX->Location = System::Drawing::Point(6, 70);
			this->labelChessboardCornersNumberX->Name = L"labelChessboardCornersNumberX";
			this->labelChessboardCornersNumberX->Size = System::Drawing::Size(149, 13);
			this->labelChessboardCornersNumberX->TabIndex = 88;
			this->labelChessboardCornersNumberX->Text = L"Chessboard corners number X";
			// 
			// textBoxChessboardCornersNumberX
			// 
			this->textBoxChessboardCornersNumberX->Location = System::Drawing::Point(148, 83);
			this->textBoxChessboardCornersNumberX->Name = L"textBoxChessboardCornersNumberX";
			this->textBoxChessboardCornersNumberX->ReadOnly = true;
			this->textBoxChessboardCornersNumberX->Size = System::Drawing::Size(33, 20);
			this->textBoxChessboardCornersNumberX->TabIndex = 90;
			this->textBoxChessboardCornersNumberX->Text = L"9";
			// 
			// textBoxAngleOfCameraSeeingInDegree
			// 
			this->textBoxAngleOfCameraSeeingInDegree->Location = System::Drawing::Point(153, 184);
			this->textBoxAngleOfCameraSeeingInDegree->Name = L"textBoxAngleOfCameraSeeingInDegree";
			this->textBoxAngleOfCameraSeeingInDegree->ReadOnly = true;
			this->textBoxAngleOfCameraSeeingInDegree->Size = System::Drawing::Size(33, 20);
			this->textBoxAngleOfCameraSeeingInDegree->TabIndex = 96;
			this->textBoxAngleOfCameraSeeingInDegree->Text = L"80";
			// 
			// textBoxChessboardCornersNumberY
			// 
			this->textBoxChessboardCornersNumberY->Location = System::Drawing::Point(148, 122);
			this->textBoxChessboardCornersNumberY->Name = L"textBoxChessboardCornersNumberY";
			this->textBoxChessboardCornersNumberY->ReadOnly = true;
			this->textBoxChessboardCornersNumberY->Size = System::Drawing::Size(33, 20);
			this->textBoxChessboardCornersNumberY->TabIndex = 93;
			this->textBoxChessboardCornersNumberY->Text = L"6";
			// 
			// scrollBarChessboardCornersNumberY
			// 
			this->scrollBarChessboardCornersNumberY->Location = System::Drawing::Point(9, 122);
			this->scrollBarChessboardCornersNumberY->Maximum = 30;
			this->scrollBarChessboardCornersNumberY->Minimum = 3;
			this->scrollBarChessboardCornersNumberY->Name = L"scrollBarChessboardCornersNumberY";
			this->scrollBarChessboardCornersNumberY->Size = System::Drawing::Size(130, 20);
			this->scrollBarChessboardCornersNumberY->TabIndex = 92;
			this->scrollBarChessboardCornersNumberY->Value = 6;
			this->scrollBarChessboardCornersNumberY->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form1::scrollBarChessboardCornersNumberY_Scroll);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 171);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(166, 13);
			this->label3->TabIndex = 94;
			this->label3->Text = L"Seeing angle of cameras (degree)";
			// 
			// labelChessboardCornersNumberY
			// 
			this->labelChessboardCornersNumberY->AutoSize = true;
			this->labelChessboardCornersNumberY->Location = System::Drawing::Point(6, 109);
			this->labelChessboardCornersNumberY->Name = L"labelChessboardCornersNumberY";
			this->labelChessboardCornersNumberY->Size = System::Drawing::Size(149, 13);
			this->labelChessboardCornersNumberY->TabIndex = 91;
			this->labelChessboardCornersNumberY->Text = L"Chessboard corners number Y";
			// 
			// scrollBarAngleOfCameraSeeingInDegree
			// 
			this->scrollBarAngleOfCameraSeeingInDegree->Location = System::Drawing::Point(9, 184);
			this->scrollBarAngleOfCameraSeeingInDegree->Minimum = 30;
			this->scrollBarAngleOfCameraSeeingInDegree->Name = L"scrollBarAngleOfCameraSeeingInDegree";
			this->scrollBarAngleOfCameraSeeingInDegree->Size = System::Drawing::Size(130, 20);
			this->scrollBarAngleOfCameraSeeingInDegree->TabIndex = 95;
			this->scrollBarAngleOfCameraSeeingInDegree->Value = 80;
			this->scrollBarAngleOfCameraSeeingInDegree->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form1::scrollBarAngleOfCameraSeeingInDegree_Scroll);
			// 
			// labelChessboardSqareSize
			// 
			this->labelChessboardSqareSize->AutoSize = true;
			this->labelChessboardSqareSize->Location = System::Drawing::Point(6, 16);
			this->labelChessboardSqareSize->Name = L"labelChessboardSqareSize";
			this->labelChessboardSqareSize->Size = System::Drawing::Size(136, 13);
			this->labelChessboardSqareSize->TabIndex = 69;
			this->labelChessboardSqareSize->Text = L"Chessboard sqare size (cm)";
			// 
			// scrollBarChessboardSqareSize
			// 
			this->scrollBarChessboardSqareSize->LargeChange = 100;
			this->scrollBarChessboardSqareSize->Location = System::Drawing::Point(9, 29);
			this->scrollBarChessboardSqareSize->Maximum = 700;
			this->scrollBarChessboardSqareSize->Minimum = 1;
			this->scrollBarChessboardSqareSize->Name = L"scrollBarChessboardSqareSize";
			this->scrollBarChessboardSqareSize->Size = System::Drawing::Size(130, 20);
			this->scrollBarChessboardSqareSize->TabIndex = 70;
			this->scrollBarChessboardSqareSize->Value = 300;
			this->scrollBarChessboardSqareSize->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form1::scrollBarChessboardSqareSize_Scroll);
			// 
			// textBoxChessboardSqareSize
			// 
			this->textBoxChessboardSqareSize->Location = System::Drawing::Point(148, 29);
			this->textBoxChessboardSqareSize->Name = L"textBoxChessboardSqareSize";
			this->textBoxChessboardSqareSize->ReadOnly = true;
			this->textBoxChessboardSqareSize->Size = System::Drawing::Size(33, 20);
			this->textBoxChessboardSqareSize->TabIndex = 71;
			this->textBoxChessboardSqareSize->Text = L"30";
			// 
			// groupBoxWindows
			// 
			this->groupBoxWindows->BackColor = System::Drawing::SystemColors::ControlLight;
			this->groupBoxWindows->Controls->Add(this->checkBoxViewOnlyMasks);
			this->groupBoxWindows->Controls->Add(this->checkBoxViewValue);
			this->groupBoxWindows->Controls->Add(this->checkBoxViewSaturation);
			this->groupBoxWindows->Controls->Add(this->checkBoxViewHue);
			this->groupBoxWindows->Controls->Add(this->checkBoxViewColorSeparationWithoutBackgroundClosedSegment);
			this->groupBoxWindows->Controls->Add(this->checkBoxViewColorSeparationWithoutBackgroundClosed);
			this->groupBoxWindows->Controls->Add(this->checkBoxViewColorSeparationWithoutBackground);
			this->groupBoxWindows->Controls->Add(this->checkBoxViewWitoutBackground);
			this->groupBoxWindows->Controls->Add(this->checkBoxRightCameraView);
			this->groupBoxWindows->Controls->Add(this->checkBoxLeftCameraView);
			this->groupBoxWindows->Location = System::Drawing::Point(369, 40);
			this->groupBoxWindows->Name = L"groupBoxWindows";
			this->groupBoxWindows->Size = System::Drawing::Size(303, 229);
			this->groupBoxWindows->TabIndex = 76;
			this->groupBoxWindows->TabStop = false;
			this->groupBoxWindows->Text = L"Windows";
			// 
			// checkBoxViewOnlyMasks
			// 
			this->checkBoxViewOnlyMasks->AutoSize = true;
			this->checkBoxViewOnlyMasks->Location = System::Drawing::Point(159, 180);
			this->checkBoxViewOnlyMasks->Name = L"checkBoxViewOnlyMasks";
			this->checkBoxViewOnlyMasks->Size = System::Drawing::Size(80, 17);
			this->checkBoxViewOnlyMasks->TabIndex = 66;
			this->checkBoxViewOnlyMasks->Text = L"Only masks";
			this->checkBoxViewOnlyMasks->UseVisualStyleBackColor = true;
			this->checkBoxViewOnlyMasks->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxViewOnlyMasks_CheckedChanged);
			// 
			// checkBoxViewValue
			// 
			this->checkBoxViewValue->AutoSize = true;
			this->checkBoxViewValue->Location = System::Drawing::Point(6, 203);
			this->checkBoxViewValue->Name = L"checkBoxViewValue";
			this->checkBoxViewValue->Size = System::Drawing::Size(53, 17);
			this->checkBoxViewValue->TabIndex = 65;
			this->checkBoxViewValue->Text = L"Value";
			this->checkBoxViewValue->UseVisualStyleBackColor = true;
			this->checkBoxViewValue->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxViewValue_CheckedChanged);
			// 
			// checkBoxViewSaturation
			// 
			this->checkBoxViewSaturation->AutoSize = true;
			this->checkBoxViewSaturation->Location = System::Drawing::Point(6, 180);
			this->checkBoxViewSaturation->Name = L"checkBoxViewSaturation";
			this->checkBoxViewSaturation->Size = System::Drawing::Size(74, 17);
			this->checkBoxViewSaturation->TabIndex = 64;
			this->checkBoxViewSaturation->Text = L"Saturation";
			this->checkBoxViewSaturation->UseVisualStyleBackColor = true;
			this->checkBoxViewSaturation->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxViewSaturation_CheckedChanged);
			// 
			// checkBoxViewHue
			// 
			this->checkBoxViewHue->AutoSize = true;
			this->checkBoxViewHue->Location = System::Drawing::Point(6, 157);
			this->checkBoxViewHue->Name = L"checkBoxViewHue";
			this->checkBoxViewHue->Size = System::Drawing::Size(46, 17);
			this->checkBoxViewHue->TabIndex = 63;
			this->checkBoxViewHue->Text = L"Hue";
			this->checkBoxViewHue->UseVisualStyleBackColor = true;
			this->checkBoxViewHue->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxViewHue_CheckedChanged);
			// 
			// checkBoxViewColorSeparationWithoutBackgroundClosedSegment
			// 
			this->checkBoxViewColorSeparationWithoutBackgroundClosedSegment->AutoSize = true;
			this->checkBoxViewColorSeparationWithoutBackgroundClosedSegment->Location = System::Drawing::Point(6, 120);
			this->checkBoxViewColorSeparationWithoutBackgroundClosedSegment->Name = L"checkBoxViewColorSeparationWithoutBackgroundClosedSegment";
			this->checkBoxViewColorSeparationWithoutBackgroundClosedSegment->Size = System::Drawing::Size(294, 17);
			this->checkBoxViewColorSeparationWithoutBackgroundClosedSegment->TabIndex = 62;
			this->checkBoxViewColorSeparationWithoutBackgroundClosedSegment->Text = L"Color separation without background, closed, segmented";
			this->checkBoxViewColorSeparationWithoutBackgroundClosedSegment->UseVisualStyleBackColor = true;
			this->checkBoxViewColorSeparationWithoutBackgroundClosedSegment->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxViewColorSeparationWithoutBackgroundClosedSegment_CheckedChanged);
			// 
			// checkBoxViewColorSeparationWithoutBackgroundClosed
			// 
			this->checkBoxViewColorSeparationWithoutBackgroundClosed->AutoSize = true;
			this->checkBoxViewColorSeparationWithoutBackgroundClosed->Location = System::Drawing::Point(6, 97);
			this->checkBoxViewColorSeparationWithoutBackgroundClosed->Name = L"checkBoxViewColorSeparationWithoutBackgroundClosed";
			this->checkBoxViewColorSeparationWithoutBackgroundClosed->Size = System::Drawing::Size(236, 17);
			this->checkBoxViewColorSeparationWithoutBackgroundClosed->TabIndex = 61;
			this->checkBoxViewColorSeparationWithoutBackgroundClosed->Text = L"Color separation without background, closed";
			this->checkBoxViewColorSeparationWithoutBackgroundClosed->UseVisualStyleBackColor = true;
			this->checkBoxViewColorSeparationWithoutBackgroundClosed->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxViewColorSeparationWithoutBackgroundClosed_CheckedChanged);
			// 
			// checkBoxViewColorSeparationWithoutBackground
			// 
			this->checkBoxViewColorSeparationWithoutBackground->AutoSize = true;
			this->checkBoxViewColorSeparationWithoutBackground->Location = System::Drawing::Point(6, 74);
			this->checkBoxViewColorSeparationWithoutBackground->Name = L"checkBoxViewColorSeparationWithoutBackground";
			this->checkBoxViewColorSeparationWithoutBackground->Size = System::Drawing::Size(224, 17);
			this->checkBoxViewColorSeparationWithoutBackground->TabIndex = 60;
			this->checkBoxViewColorSeparationWithoutBackground->Text = L"View color separation without background";
			this->checkBoxViewColorSeparationWithoutBackground->UseVisualStyleBackColor = true;
			this->checkBoxViewColorSeparationWithoutBackground->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxViewColorSeparationWithoutBackground_CheckedChanged);
			// 
			// checkBoxViewWitoutBackground
			// 
			this->checkBoxViewWitoutBackground->AutoSize = true;
			this->checkBoxViewWitoutBackground->Location = System::Drawing::Point(6, 51);
			this->checkBoxViewWitoutBackground->Name = L"checkBoxViewWitoutBackground";
			this->checkBoxViewWitoutBackground->Size = System::Drawing::Size(146, 17);
			this->checkBoxViewWitoutBackground->TabIndex = 59;
			this->checkBoxViewWitoutBackground->Text = L"View without background";
			this->checkBoxViewWitoutBackground->UseVisualStyleBackColor = true;
			this->checkBoxViewWitoutBackground->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxg_bInterfaceShowViewWitoutBackground_CheckedChanged);
			// 
			// checkBoxAdvanceSettings
			// 
			this->checkBoxAdvanceSettings->AutoSize = true;
			this->checkBoxAdvanceSettings->Checked = true;
			this->checkBoxAdvanceSettings->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxAdvanceSettings->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->checkBoxAdvanceSettings->Location = System::Drawing::Point(221, 31);
			this->checkBoxAdvanceSettings->Name = L"checkBoxAdvanceSettings";
			this->checkBoxAdvanceSettings->Size = System::Drawing::Size(133, 36);
			this->checkBoxAdvanceSettings->TabIndex = 77;
			this->checkBoxAdvanceSettings->Text = L"Advance settings:\r\n - Hide";
			this->checkBoxAdvanceSettings->UseVisualStyleBackColor = true;
			this->checkBoxAdvanceSettings->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxAdvanceSettings_CheckedChanged);
			// 
			// textBoxNumberOfDrums
			// 
			this->textBoxNumberOfDrums->Location = System::Drawing::Point(305, 32);
			this->textBoxNumberOfDrums->Name = L"textBoxNumberOfDrums";
			this->textBoxNumberOfDrums->ReadOnly = true;
			this->textBoxNumberOfDrums->Size = System::Drawing::Size(33, 20);
			this->textBoxNumberOfDrums->TabIndex = 59;
			this->textBoxNumberOfDrums->Text = L"2";
			// 
			// labelNumberOfDrums
			// 
			this->labelNumberOfDrums->AutoSize = true;
			this->labelNumberOfDrums->Location = System::Drawing::Point(219, 16);
			this->labelNumberOfDrums->Name = L"labelNumberOfDrums";
			this->labelNumberOfDrums->Size = System::Drawing::Size(100, 13);
			this->labelNumberOfDrums->TabIndex = 57;
			this->labelNumberOfDrums->Text = L"Number of all drums";
			// 
			// ScrollBarNumberOfDrums
			// 
			this->ScrollBarNumberOfDrums->Location = System::Drawing::Point(222, 32);
			this->ScrollBarNumberOfDrums->Maximum = 30;
			this->ScrollBarNumberOfDrums->Minimum = 2;
			this->ScrollBarNumberOfDrums->Name = L"ScrollBarNumberOfDrums";
			this->ScrollBarNumberOfDrums->Size = System::Drawing::Size(70, 20);
			this->ScrollBarNumberOfDrums->TabIndex = 58;
			this->ScrollBarNumberOfDrums->Value = 2;
			this->ScrollBarNumberOfDrums->ValueChanged += gcnew System::EventHandler(this, &Form1::ScrollBarNumberOfDrums_ValueChanged);
			// 
			// comboBoxDrumsAudioSamples
			// 
			this->comboBoxDrumsAudioSamples->DisplayMember = L"0";
			this->comboBoxDrumsAudioSamples->FormattingEnabled = true;
			this->comboBoxDrumsAudioSamples->Location = System::Drawing::Point(6, 150);
			this->comboBoxDrumsAudioSamples->Name = L"comboBoxDrumsAudioSamples";
			this->comboBoxDrumsAudioSamples->Size = System::Drawing::Size(208, 21);
			this->comboBoxDrumsAudioSamples->TabIndex = 78;
			this->comboBoxDrumsAudioSamples->ValueMember = L"0";
			this->comboBoxDrumsAudioSamples->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBoxDrumsAudioSamples_SelectedIndexChanged);
			this->comboBoxDrumsAudioSamples->TextChanged += gcnew System::EventHandler(this, &Form1::comboBoxDrumsAudioSamples_TextChanged);
			this->comboBoxDrumsAudioSamples->Click += gcnew System::EventHandler(this, &Form1::comboBoxDrumsAudioSamples_Click);
			// 
			// textBoxNumberOfDrumToChangeProperty
			// 
			this->textBoxNumberOfDrumToChangeProperty->Location = System::Drawing::Point(182, 112);
			this->textBoxNumberOfDrumToChangeProperty->Name = L"textBoxNumberOfDrumToChangeProperty";
			this->textBoxNumberOfDrumToChangeProperty->ReadOnly = true;
			this->textBoxNumberOfDrumToChangeProperty->Size = System::Drawing::Size(33, 20);
			this->textBoxNumberOfDrumToChangeProperty->TabIndex = 81;
			this->textBoxNumberOfDrumToChangeProperty->Text = L"2";
			// 
			// labelNumberOfDrumToChangeProperty
			// 
			this->labelNumberOfDrumToChangeProperty->AutoSize = true;
			this->labelNumberOfDrumToChangeProperty->Location = System::Drawing::Point(7, 96);
			this->labelNumberOfDrumToChangeProperty->Name = L"labelNumberOfDrumToChangeProperty";
			this->labelNumberOfDrumToChangeProperty->Size = System::Drawing::Size(174, 13);
			this->labelNumberOfDrumToChangeProperty->TabIndex = 79;
			this->labelNumberOfDrumToChangeProperty->Text = L"Number of drum to change property";
			// 
			// ScrollBarNumberOfDrumToChangeProperty
			// 
			this->ScrollBarNumberOfDrumToChangeProperty->Enabled = false;
			this->ScrollBarNumberOfDrumToChangeProperty->LargeChange = 1;
			this->ScrollBarNumberOfDrumToChangeProperty->Location = System::Drawing::Point(10, 112);
			this->ScrollBarNumberOfDrumToChangeProperty->Maximum = 2;
			this->ScrollBarNumberOfDrumToChangeProperty->Minimum = 1;
			this->ScrollBarNumberOfDrumToChangeProperty->Name = L"ScrollBarNumberOfDrumToChangeProperty";
			this->ScrollBarNumberOfDrumToChangeProperty->Size = System::Drawing::Size(159, 20);
			this->ScrollBarNumberOfDrumToChangeProperty->TabIndex = 80;
			this->ScrollBarNumberOfDrumToChangeProperty->Value = 2;
			this->ScrollBarNumberOfDrumToChangeProperty->ValueChanged += gcnew System::EventHandler(this, &Form1::ScrollBarNumberOfDrumToChangeProperty_ValueChanged);
			// 
			// checkBoxEditDrums
			// 
			this->checkBoxEditDrums->AutoSize = true;
			this->checkBoxEditDrums->Checked = true;
			this->checkBoxEditDrums->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxEditDrums->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->checkBoxEditDrums->Location = System::Drawing::Point(8, 233);
			this->checkBoxEditDrums->Name = L"checkBoxEditDrums";
			this->checkBoxEditDrums->Size = System::Drawing::Size(93, 36);
			this->checkBoxEditDrums->TabIndex = 82;
			this->checkBoxEditDrums->Text = L"Edit drums:\r\n - Enabled";
			this->checkBoxEditDrums->UseVisualStyleBackColor = true;
			this->checkBoxEditDrums->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxEditDrums_CheckedChanged);
			// 
			// textBoxDrumPositionZ
			// 
			this->textBoxDrumPositionZ->Location = System::Drawing::Point(165, 199);
			this->textBoxDrumPositionZ->Name = L"textBoxDrumPositionZ";
			this->textBoxDrumPositionZ->ReadOnly = true;
			this->textBoxDrumPositionZ->Size = System::Drawing::Size(33, 20);
			this->textBoxDrumPositionZ->TabIndex = 65;
			this->textBoxDrumPositionZ->Text = L"0";
			// 
			// labelDrumPositionZ
			// 
			this->labelDrumPositionZ->AutoSize = true;
			this->labelDrumPositionZ->Location = System::Drawing::Point(138, 183);
			this->labelDrumPositionZ->Name = L"labelDrumPositionZ";
			this->labelDrumPositionZ->Size = System::Drawing::Size(54, 13);
			this->labelDrumPositionZ->TabIndex = 63;
			this->labelDrumPositionZ->Text = L"Position Z";
			// 
			// textBoxDrumPositionY
			// 
			this->textBoxDrumPositionY->Location = System::Drawing::Point(105, 199);
			this->textBoxDrumPositionY->Name = L"textBoxDrumPositionY";
			this->textBoxDrumPositionY->ReadOnly = true;
			this->textBoxDrumPositionY->Size = System::Drawing::Size(33, 20);
			this->textBoxDrumPositionY->TabIndex = 62;
			this->textBoxDrumPositionY->Text = L"0";
			// 
			// labelDrumPositionY
			// 
			this->labelDrumPositionY->AutoSize = true;
			this->labelDrumPositionY->Location = System::Drawing::Point(78, 183);
			this->labelDrumPositionY->Name = L"labelDrumPositionY";
			this->labelDrumPositionY->Size = System::Drawing::Size(54, 13);
			this->labelDrumPositionY->TabIndex = 60;
			this->labelDrumPositionY->Text = L"Position Y";
			// 
			// textBoxDrumPositionX
			// 
			this->textBoxDrumPositionX->Location = System::Drawing::Point(46, 199);
			this->textBoxDrumPositionX->Name = L"textBoxDrumPositionX";
			this->textBoxDrumPositionX->ReadOnly = true;
			this->textBoxDrumPositionX->Size = System::Drawing::Size(33, 20);
			this->textBoxDrumPositionX->TabIndex = 59;
			this->textBoxDrumPositionX->Text = L"0";
			// 
			// labelDrumPositionX
			// 
			this->labelDrumPositionX->AutoSize = true;
			this->labelDrumPositionX->Location = System::Drawing::Point(19, 183);
			this->labelDrumPositionX->Name = L"labelDrumPositionX";
			this->labelDrumPositionX->Size = System::Drawing::Size(54, 13);
			this->labelDrumPositionX->TabIndex = 57;
			this->labelDrumPositionX->Text = L"Position X";
			// 
			// numericUpDownDrumPositionX
			// 
			this->numericUpDownDrumPositionX->Enabled = false;
			this->numericUpDownDrumPositionX->Location = System::Drawing::Point(17, 199);
			this->numericUpDownDrumPositionX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {10000, 0, 0, 0});
			this->numericUpDownDrumPositionX->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {10000, 0, 0, System::Int32::MinValue});
			this->numericUpDownDrumPositionX->Name = L"numericUpDownDrumPositionX";
			this->numericUpDownDrumPositionX->Size = System::Drawing::Size(18, 20);
			this->numericUpDownDrumPositionX->TabIndex = 83;
			this->numericUpDownDrumPositionX->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDownDrumPositionX_ValueChanged);
			// 
			// numericUpDownDrumPositionY
			// 
			this->numericUpDownDrumPositionY->Enabled = false;
			this->numericUpDownDrumPositionY->Location = System::Drawing::Point(81, 199);
			this->numericUpDownDrumPositionY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {10000, 0, 0, 0});
			this->numericUpDownDrumPositionY->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {10000, 0, 0, System::Int32::MinValue});
			this->numericUpDownDrumPositionY->Name = L"numericUpDownDrumPositionY";
			this->numericUpDownDrumPositionY->Size = System::Drawing::Size(18, 20);
			this->numericUpDownDrumPositionY->TabIndex = 84;
			this->numericUpDownDrumPositionY->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDownDrumPositionY_ValueChanged);
			// 
			// numericUpDownDrumPositionZ
			// 
			this->numericUpDownDrumPositionZ->Enabled = false;
			this->numericUpDownDrumPositionZ->Location = System::Drawing::Point(141, 199);
			this->numericUpDownDrumPositionZ->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {10000, 0, 0, 0});
			this->numericUpDownDrumPositionZ->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {10000, 0, 0, System::Int32::MinValue});
			this->numericUpDownDrumPositionZ->Name = L"numericUpDownDrumPositionZ";
			this->numericUpDownDrumPositionZ->Size = System::Drawing::Size(18, 20);
			this->numericUpDownDrumPositionZ->TabIndex = 85;
			this->numericUpDownDrumPositionZ->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDownDrumPositionZ_ValueChanged);
			// 
			// listBoxListOfDrums
			// 
			this->listBoxListOfDrums->FormattingEnabled = true;
			this->listBoxListOfDrums->HorizontalScrollbar = true;
			this->listBoxListOfDrums->Items->AddRange(gcnew cli::array< System::Object^  >(1) {L"Here will be list of drums:"});
			this->listBoxListOfDrums->Location = System::Drawing::Point(222, 65);
			this->listBoxListOfDrums->Name = L"listBoxListOfDrums";
			this->listBoxListOfDrums->SelectionMode = System::Windows::Forms::SelectionMode::MultiExtended;
			this->listBoxListOfDrums->Size = System::Drawing::Size(120, 290);
			this->listBoxListOfDrums->TabIndex = 86;
			// 
			// groupBoxDrumsEdition
			// 
			this->groupBoxDrumsEdition->BackColor = System::Drawing::SystemColors::ControlLight;
			this->groupBoxDrumsEdition->Controls->Add(this->buttonSetUpDrumKit);
			this->groupBoxDrumsEdition->Controls->Add(this->textBoxDrumsDepth);
			this->groupBoxDrumsEdition->Controls->Add(this->labelDrumSoundSample);
			this->groupBoxDrumsEdition->Controls->Add(this->labelDrumsDepth);
			this->groupBoxDrumsEdition->Controls->Add(this->textBoxNumberOfDrums);
			this->groupBoxDrumsEdition->Controls->Add(this->scrollBarDrumsDepth);
			this->groupBoxDrumsEdition->Controls->Add(this->listBoxListOfDrums);
			this->groupBoxDrumsEdition->Controls->Add(this->textBoxDrumsWidth);
			this->groupBoxDrumsEdition->Controls->Add(this->numericUpDownDrumPositionZ);
			this->groupBoxDrumsEdition->Controls->Add(this->label5);
			this->groupBoxDrumsEdition->Controls->Add(this->scrollBarDrumsWidth);
			this->groupBoxDrumsEdition->Controls->Add(this->labelNumberOfDrums);
			this->groupBoxDrumsEdition->Controls->Add(this->ScrollBarNumberOfDrums);
			this->groupBoxDrumsEdition->Controls->Add(this->numericUpDownDrumPositionY);
			this->groupBoxDrumsEdition->Controls->Add(this->numericUpDownDrumPositionX);
			this->groupBoxDrumsEdition->Controls->Add(this->textBoxDrumPositionZ);
			this->groupBoxDrumsEdition->Controls->Add(this->labelDrumPositionZ);
			this->groupBoxDrumsEdition->Controls->Add(this->textBoxNumberOfDrumToChangeProperty);
			this->groupBoxDrumsEdition->Controls->Add(this->labelNumberOfDrumToChangeProperty);
			this->groupBoxDrumsEdition->Controls->Add(this->textBoxDrumPositionY);
			this->groupBoxDrumsEdition->Controls->Add(this->ScrollBarNumberOfDrumToChangeProperty);
			this->groupBoxDrumsEdition->Controls->Add(this->labelDrumPositionY);
			this->groupBoxDrumsEdition->Controls->Add(this->comboBoxDrumsAudioSamples);
			this->groupBoxDrumsEdition->Controls->Add(this->textBoxDrumPositionX);
			this->groupBoxDrumsEdition->Controls->Add(this->labelDrumPositionX);
			this->groupBoxDrumsEdition->Location = System::Drawing::Point(8, 275);
			this->groupBoxDrumsEdition->Name = L"groupBoxDrumsEdition";
			this->groupBoxDrumsEdition->Size = System::Drawing::Size(348, 370);
			this->groupBoxDrumsEdition->TabIndex = 87;
			this->groupBoxDrumsEdition->TabStop = false;
			this->groupBoxDrumsEdition->Text = L"Drums editon panel";
			// 
			// buttonSetUpDrumKit
			// 
			this->buttonSetUpDrumKit->Enabled = false;
			this->buttonSetUpDrumKit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->buttonSetUpDrumKit->Location = System::Drawing::Point(46, 34);
			this->buttonSetUpDrumKit->Name = L"buttonSetUpDrumKit";
			this->buttonSetUpDrumKit->Size = System::Drawing::Size(114, 25);
			this->buttonSetUpDrumKit->TabIndex = 103;
			this->buttonSetUpDrumKit->Text = L"Set up drum kit";
			this->buttonSetUpDrumKit->UseVisualStyleBackColor = true;
			this->buttonSetUpDrumKit->Click += gcnew System::EventHandler(this, &Form1::buttonSetUpDrumKit_Click);
			// 
			// textBoxDrumsDepth
			// 
			this->textBoxDrumsDepth->Location = System::Drawing::Point(150, 339);
			this->textBoxDrumsDepth->Name = L"textBoxDrumsDepth";
			this->textBoxDrumsDepth->ReadOnly = true;
			this->textBoxDrumsDepth->Size = System::Drawing::Size(33, 20);
			this->textBoxDrumsDepth->TabIndex = 102;
			this->textBoxDrumsDepth->Text = L"30";
			// 
			// labelDrumSoundSample
			// 
			this->labelDrumSoundSample->AutoSize = true;
			this->labelDrumSoundSample->Location = System::Drawing::Point(3, 134);
			this->labelDrumSoundSample->Name = L"labelDrumSoundSample";
			this->labelDrumSoundSample->Size = System::Drawing::Size(103, 13);
			this->labelDrumSoundSample->TabIndex = 87;
			this->labelDrumSoundSample->Text = L"Drum sound sample:";
			// 
			// labelDrumsDepth
			// 
			this->labelDrumsDepth->AutoSize = true;
			this->labelDrumsDepth->Location = System::Drawing::Point(3, 326);
			this->labelDrumsDepth->Name = L"labelDrumsDepth";
			this->labelDrumsDepth->Size = System::Drawing::Size(90, 13);
			this->labelDrumsDepth->TabIndex = 100;
			this->labelDrumsDepth->Text = L"Drums detph (cm)";
			// 
			// scrollBarDrumsDepth
			// 
			this->scrollBarDrumsDepth->Location = System::Drawing::Point(6, 339);
			this->scrollBarDrumsDepth->Maximum = 70;
			this->scrollBarDrumsDepth->Minimum = 3;
			this->scrollBarDrumsDepth->Name = L"scrollBarDrumsDepth";
			this->scrollBarDrumsDepth->Size = System::Drawing::Size(130, 20);
			this->scrollBarDrumsDepth->TabIndex = 101;
			this->scrollBarDrumsDepth->Value = 30;
			this->scrollBarDrumsDepth->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form1::scrollBarDrumsDepth_Scroll);
			// 
			// textBoxDrumsWidth
			// 
			this->textBoxDrumsWidth->Location = System::Drawing::Point(150, 297);
			this->textBoxDrumsWidth->Name = L"textBoxDrumsWidth";
			this->textBoxDrumsWidth->ReadOnly = true;
			this->textBoxDrumsWidth->Size = System::Drawing::Size(33, 20);
			this->textBoxDrumsWidth->TabIndex = 99;
			this->textBoxDrumsWidth->Text = L"30";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(3, 284);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(88, 13);
			this->label5->TabIndex = 97;
			this->label5->Text = L"Drums width (cm)";
			// 
			// scrollBarDrumsWidth
			// 
			this->scrollBarDrumsWidth->Location = System::Drawing::Point(6, 297);
			this->scrollBarDrumsWidth->Maximum = 70;
			this->scrollBarDrumsWidth->Minimum = 1;
			this->scrollBarDrumsWidth->Name = L"scrollBarDrumsWidth";
			this->scrollBarDrumsWidth->Size = System::Drawing::Size(130, 20);
			this->scrollBarDrumsWidth->TabIndex = 98;
			this->scrollBarDrumsWidth->Value = 30;
			this->scrollBarDrumsWidth->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form1::scrollBarDrumsWidth_Scroll);
			// 
			// groupBoxAutoAdjustProcessingParameters
			// 
			this->groupBoxAutoAdjustProcessingParameters->BackColor = System::Drawing::SystemColors::ControlLight;
			this->groupBoxAutoAdjustProcessingParameters->Controls->Add(this->textBoxAutoAdjustGoodResultsPercentageAfterColorFactorAdjust);
			this->groupBoxAutoAdjustProcessingParameters->Controls->Add(this->labelAutoAdjustGoodResultsPercentageAfterColorFactorAdjust);
			this->groupBoxAutoAdjustProcessingParameters->Controls->Add(this->ScrollBarAutoAdjustGoodResultsPercentageAfterColorFactorAdjust);
			this->groupBoxAutoAdjustProcessingParameters->Controls->Add(this->textBoxAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust);
			this->groupBoxAutoAdjustProcessingParameters->Controls->Add(this->labelAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust);
			this->groupBoxAutoAdjustProcessingParameters->Controls->Add(this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust);
			this->groupBoxAutoAdjustProcessingParameters->Controls->Add(this->textBoxAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust);
			this->groupBoxAutoAdjustProcessingParameters->Controls->Add(this->labelAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust);
			this->groupBoxAutoAdjustProcessingParameters->Controls->Add(this->ScrollBarAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust);
			this->groupBoxAutoAdjustProcessingParameters->Controls->Add(this->textBoxAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust);
			this->groupBoxAutoAdjustProcessingParameters->Controls->Add(this->labelAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust);
			this->groupBoxAutoAdjustProcessingParameters->Controls->Add(this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust);
			this->groupBoxAutoAdjustProcessingParameters->Controls->Add(this->buttonRefreshAutoAdjust);
			this->groupBoxAutoAdjustProcessingParameters->Location = System::Drawing::Point(678, 402);
			this->groupBoxAutoAdjustProcessingParameters->Name = L"groupBoxAutoAdjustProcessingParameters";
			this->groupBoxAutoAdjustProcessingParameters->Size = System::Drawing::Size(225, 243);
			this->groupBoxAutoAdjustProcessingParameters->TabIndex = 88;
			this->groupBoxAutoAdjustProcessingParameters->TabStop = false;
			this->groupBoxAutoAdjustProcessingParameters->Text = L"Auto adjust processing parameters";
			// 
			// textBoxAutoAdjustGoodResultsPercentageAfterColorFactorAdjust
			// 
			this->textBoxAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->Location = System::Drawing::Point(153, 215);
			this->textBoxAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->Name = L"textBoxAutoAdjustGoodResultsPercentageAfterColorFactorAdjust";
			this->textBoxAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->ReadOnly = true;
			this->textBoxAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->Size = System::Drawing::Size(47, 20);
			this->textBoxAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->TabIndex = 114;
			this->textBoxAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->Text = L"85";
			// 
			// labelAutoAdjustGoodResultsPercentageAfterColorFactorAdjust
			// 
			this->labelAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->AutoSize = true;
			this->labelAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->Location = System::Drawing::Point(6, 202);
			this->labelAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->Name = L"labelAutoAdjustGoodResultsPercentageAfterColorFactorAdjust";
			this->labelAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->Size = System::Drawing::Size(194, 13);
			this->labelAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->TabIndex = 112;
			this->labelAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->Text = L"Good results after color factor adjust (%)";
			// 
			// ScrollBarAutoAdjustGoodResultsPercentageAfterColorFactorAdjust
			// 
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->Location = System::Drawing::Point(9, 215);
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->Maximum = 107;
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->Minimum = 30;
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->Name = L"ScrollBarAutoAdjustGoodResultsPercentageAfterColorFactorAdjust";
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->Size = System::Drawing::Size(130, 20);
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->TabIndex = 113;
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->Value = 85;
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->ValueChanged += gcnew System::EventHandler(this, &Form1::ScrollBarAutoAdjustGoodResultsPercentageAfterColorFactorAdjust_ValueChanged);
			// 
			// textBoxAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust
			// 
			this->textBoxAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->Location = System::Drawing::Point(153, 173);
			this->textBoxAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->Name = L"textBoxAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust";
			this->textBoxAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->ReadOnly = true;
			this->textBoxAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->Size = System::Drawing::Size(47, 20);
			this->textBoxAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->TabIndex = 111;
			this->textBoxAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->Text = L"0.002";
			// 
			// labelAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust
			// 
			this->labelAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->AutoSize = true;
			this->labelAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->Location = System::Drawing::Point(6, 160);
			this->labelAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->Name = L"labelAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust";
			this->labelAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->Size = System::Drawing::Size(204, 13);
			this->labelAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->TabIndex = 109;
			this->labelAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->Text = L"Nonzero pixels after color factor adjust (%)";
			// 
			// ScrollBarAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust
			// 
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->Location = System::Drawing::Point(9, 173);
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->Maximum = 110;
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->Minimum = 10;
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->Name = L"ScrollBarAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust";
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->Size = System::Drawing::Size(130, 20);
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->TabIndex = 110;
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->Value = 20;
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->ValueChanged += gcnew System::EventHandler(this, &Form1::ScrollBarAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust_ValueChanged);
			// 
			// textBoxAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust
			// 
			this->textBoxAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->Location = System::Drawing::Point(153, 132);
			this->textBoxAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->Name = L"textBoxAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust";
			this->textBoxAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->ReadOnly = true;
			this->textBoxAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->Size = System::Drawing::Size(47, 20);
			this->textBoxAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->TabIndex = 108;
			this->textBoxAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->Text = L"60";
			// 
			// labelAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust
			// 
			this->labelAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->AutoSize = true;
			this->labelAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->Location = System::Drawing::Point(6, 119);
			this->labelAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->Name = L"labelAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust";
			this->labelAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->Size = System::Drawing::Size(202, 13);
			this->labelAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->TabIndex = 106;
			this->labelAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->Text = L"Good results after mod min max adjust (%)";
			// 
			// ScrollBarAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust
			// 
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->Location = System::Drawing::Point(9, 132);
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->Maximum = 107;
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->Minimum = 30;
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->Name = L"ScrollBarAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust";
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->Size = System::Drawing::Size(130, 20);
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->TabIndex = 107;
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->Value = 60;
			this->ScrollBarAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->ValueChanged += gcnew System::EventHandler(this, &Form1::ScrollBarAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust_ValueChanged);
			// 
			// textBoxAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust
			// 
			this->textBoxAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->Location = System::Drawing::Point(153, 90);
			this->textBoxAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->Name = L"textBoxAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust";
			this->textBoxAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->ReadOnly = true;
			this->textBoxAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->Size = System::Drawing::Size(47, 20);
			this->textBoxAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->TabIndex = 105;
			this->textBoxAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->Text = L"0.005";
			// 
			// labelAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust
			// 
			this->labelAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->AutoSize = true;
			this->labelAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->Location = System::Drawing::Point(6, 77);
			this->labelAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->Name = L"labelAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust";
			this->labelAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->Size = System::Drawing::Size(212, 13);
			this->labelAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->TabIndex = 103;
			this->labelAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->Text = L"Nonzero pixels after mod min max adjust (%)";
			// 
			// ScrollBarAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust
			// 
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->Location = System::Drawing::Point(9, 90);
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->Maximum = 160;
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->Minimum = 20;
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->Name = L"ScrollBarAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust";
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->Size = System::Drawing::Size(130, 20);
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->TabIndex = 104;
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->Value = 50;
			this->ScrollBarAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->ValueChanged += gcnew System::EventHandler(this, &Form1::ScrollBarAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust_ValueChanged);
			// 
			// buttonRefreshAutoAdjust
			// 
			this->buttonRefreshAutoAdjust->Enabled = false;
			this->buttonRefreshAutoAdjust->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->buttonRefreshAutoAdjust->Location = System::Drawing::Point(67, 25);
			this->buttonRefreshAutoAdjust->Name = L"buttonRefreshAutoAdjust";
			this->buttonRefreshAutoAdjust->Size = System::Drawing::Size(114, 25);
			this->buttonRefreshAutoAdjust->TabIndex = 71;
			this->buttonRefreshAutoAdjust->Text = L"Refesh auto adjust";
			this->buttonRefreshAutoAdjust->UseVisualStyleBackColor = true;
			this->buttonRefreshAutoAdjust->Click += gcnew System::EventHandler(this, &Form1::buttonRefreshAutoAdjust_Click);
			// 
			// buttonMeasurePrecision
			// 
			this->buttonMeasurePrecision->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->buttonMeasurePrecision->Location = System::Drawing::Point(60, 33);
			this->buttonMeasurePrecision->Name = L"buttonMeasurePrecision";
			this->buttonMeasurePrecision->Size = System::Drawing::Size(134, 24);
			this->buttonMeasurePrecision->TabIndex = 89;
			this->buttonMeasurePrecision->Text = L"Measure precision";
			this->buttonMeasurePrecision->UseVisualStyleBackColor = true;
			this->buttonMeasurePrecision->Click += gcnew System::EventHandler(this, &Form1::buttonMeasurePrecision_Click);
			// 
			// textBoxMeasurePrecision
			// 
			this->textBoxMeasurePrecision->BackColor = System::Drawing::SystemColors::Window;
			this->textBoxMeasurePrecision->Location = System::Drawing::Point(6, 74);
			this->textBoxMeasurePrecision->Multiline = true;
			this->textBoxMeasurePrecision->Name = L"textBoxMeasurePrecision";
			this->textBoxMeasurePrecision->ReadOnly = true;
			this->textBoxMeasurePrecision->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBoxMeasurePrecision->Size = System::Drawing::Size(240, 357);
			this->textBoxMeasurePrecision->TabIndex = 90;
			// 
			// groupBoxMeasurePositionsMarker1
			// 
			this->groupBoxMeasurePositionsMarker1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->groupBoxMeasurePositionsMarker1->Controls->Add(this->buttonMeasurePrecision);
			this->groupBoxMeasurePositionsMarker1->Controls->Add(this->textBoxMeasurePrecision);
			this->groupBoxMeasurePositionsMarker1->Enabled = false;
			this->groupBoxMeasurePositionsMarker1->Location = System::Drawing::Point(909, 39);
			this->groupBoxMeasurePositionsMarker1->Name = L"groupBoxMeasurePositionsMarker1";
			this->groupBoxMeasurePositionsMarker1->Size = System::Drawing::Size(254, 437);
			this->groupBoxMeasurePositionsMarker1->TabIndex = 91;
			this->groupBoxMeasurePositionsMarker1->TabStop = false;
			this->groupBoxMeasurePositionsMarker1->Text = L"Measure positions marker1";
			// 
			// groupBoxPositioningDrumsTimesIntervals
			// 
			this->groupBoxPositioningDrumsTimesIntervals->BackColor = System::Drawing::SystemColors::ControlLight;
			this->groupBoxPositioningDrumsTimesIntervals->Controls->Add(this->textBoxTimeToWaitForAveragingPositionOfMarker);
			this->groupBoxPositioningDrumsTimesIntervals->Controls->Add(this->labelTimeToWaitForAveragingPositionOfMarker);
			this->groupBoxPositioningDrumsTimesIntervals->Controls->Add(this->ScrollBarTimeToWaitForAveragingPositionOfMarker);
			this->groupBoxPositioningDrumsTimesIntervals->Controls->Add(this->textBoxTimeToPlaceMarkerInDesiredPosition);
			this->groupBoxPositioningDrumsTimesIntervals->Controls->Add(this->labelTimeToPlaceMarkerInDesiredPosition);
			this->groupBoxPositioningDrumsTimesIntervals->Controls->Add(this->ScrollBarTimeToPlaceMarkerInDesiredPosition);
			this->groupBoxPositioningDrumsTimesIntervals->Controls->Add(this->textBoxTimeToSitDownInPlayingSpot);
			this->groupBoxPositioningDrumsTimesIntervals->Controls->Add(this->labelTimeToSitDownInPlayingSpot);
			this->groupBoxPositioningDrumsTimesIntervals->Controls->Add(this->ScrollBarTimeToSitDownInPlayingSpot);
			this->groupBoxPositioningDrumsTimesIntervals->Location = System::Drawing::Point(909, 482);
			this->groupBoxPositioningDrumsTimesIntervals->Name = L"groupBoxPositioningDrumsTimesIntervals";
			this->groupBoxPositioningDrumsTimesIntervals->Size = System::Drawing::Size(254, 163);
			this->groupBoxPositioningDrumsTimesIntervals->TabIndex = 92;
			this->groupBoxPositioningDrumsTimesIntervals->TabStop = false;
			this->groupBoxPositioningDrumsTimesIntervals->Text = L"Positioning drums times intervals";
			// 
			// textBoxTimeToWaitForAveragingPositionOfMarker
			// 
			this->textBoxTimeToWaitForAveragingPositionOfMarker->Location = System::Drawing::Point(152, 122);
			this->textBoxTimeToWaitForAveragingPositionOfMarker->Name = L"textBoxTimeToWaitForAveragingPositionOfMarker";
			this->textBoxTimeToWaitForAveragingPositionOfMarker->ReadOnly = true;
			this->textBoxTimeToWaitForAveragingPositionOfMarker->Size = System::Drawing::Size(33, 20);
			this->textBoxTimeToWaitForAveragingPositionOfMarker->TabIndex = 42;
			this->textBoxTimeToWaitForAveragingPositionOfMarker->Text = L"1";
			// 
			// labelTimeToWaitForAveragingPositionOfMarker
			// 
			this->labelTimeToWaitForAveragingPositionOfMarker->AutoSize = true;
			this->labelTimeToWaitForAveragingPositionOfMarker->Location = System::Drawing::Point(5, 109);
			this->labelTimeToWaitForAveragingPositionOfMarker->Name = L"labelTimeToWaitForAveragingPositionOfMarker";
			this->labelTimeToWaitForAveragingPositionOfMarker->Size = System::Drawing::Size(241, 13);
			this->labelTimeToWaitForAveragingPositionOfMarker->TabIndex = 40;
			this->labelTimeToWaitForAveragingPositionOfMarker->Text = L"Time to wait for averaging position of marker (sec)";
			// 
			// ScrollBarTimeToWaitForAveragingPositionOfMarker
			// 
			this->ScrollBarTimeToWaitForAveragingPositionOfMarker->LargeChange = 2;
			this->ScrollBarTimeToWaitForAveragingPositionOfMarker->Location = System::Drawing::Point(8, 122);
			this->ScrollBarTimeToWaitForAveragingPositionOfMarker->Maximum = 4;
			this->ScrollBarTimeToWaitForAveragingPositionOfMarker->Minimum = 1;
			this->ScrollBarTimeToWaitForAveragingPositionOfMarker->Name = L"ScrollBarTimeToWaitForAveragingPositionOfMarker";
			this->ScrollBarTimeToWaitForAveragingPositionOfMarker->Size = System::Drawing::Size(130, 20);
			this->ScrollBarTimeToWaitForAveragingPositionOfMarker->TabIndex = 41;
			this->ScrollBarTimeToWaitForAveragingPositionOfMarker->Value = 1;
			this->ScrollBarTimeToWaitForAveragingPositionOfMarker->ValueChanged += gcnew System::EventHandler(this, &Form1::ScrollBarTimeToWaitForAveragingPositionOfMarker_ValueChanged);
			// 
			// textBoxTimeToPlaceMarkerInDesiredPosition
			// 
			this->textBoxTimeToPlaceMarkerInDesiredPosition->Location = System::Drawing::Point(152, 80);
			this->textBoxTimeToPlaceMarkerInDesiredPosition->Name = L"textBoxTimeToPlaceMarkerInDesiredPosition";
			this->textBoxTimeToPlaceMarkerInDesiredPosition->ReadOnly = true;
			this->textBoxTimeToPlaceMarkerInDesiredPosition->Size = System::Drawing::Size(33, 20);
			this->textBoxTimeToPlaceMarkerInDesiredPosition->TabIndex = 39;
			this->textBoxTimeToPlaceMarkerInDesiredPosition->Text = L"2";
			// 
			// labelTimeToPlaceMarkerInDesiredPosition
			// 
			this->labelTimeToPlaceMarkerInDesiredPosition->AutoSize = true;
			this->labelTimeToPlaceMarkerInDesiredPosition->Location = System::Drawing::Point(5, 67);
			this->labelTimeToPlaceMarkerInDesiredPosition->Name = L"labelTimeToPlaceMarkerInDesiredPosition";
			this->labelTimeToPlaceMarkerInDesiredPosition->Size = System::Drawing::Size(245, 13);
			this->labelTimeToPlaceMarkerInDesiredPosition->TabIndex = 37;
			this->labelTimeToPlaceMarkerInDesiredPosition->Text = L"Time to place marker in desired drum position (sec)";
			// 
			// ScrollBarTimeToPlaceMarkerInDesiredPosition
			// 
			this->ScrollBarTimeToPlaceMarkerInDesiredPosition->LargeChange = 2;
			this->ScrollBarTimeToPlaceMarkerInDesiredPosition->Location = System::Drawing::Point(8, 80);
			this->ScrollBarTimeToPlaceMarkerInDesiredPosition->Maximum = 11;
			this->ScrollBarTimeToPlaceMarkerInDesiredPosition->Minimum = 1;
			this->ScrollBarTimeToPlaceMarkerInDesiredPosition->Name = L"ScrollBarTimeToPlaceMarkerInDesiredPosition";
			this->ScrollBarTimeToPlaceMarkerInDesiredPosition->Size = System::Drawing::Size(130, 20);
			this->ScrollBarTimeToPlaceMarkerInDesiredPosition->TabIndex = 38;
			this->ScrollBarTimeToPlaceMarkerInDesiredPosition->Value = 2;
			this->ScrollBarTimeToPlaceMarkerInDesiredPosition->ValueChanged += gcnew System::EventHandler(this, &Form1::ScrollBarTimeToPlaceMarkerInDesiredPosition_ValueChanged);
			// 
			// textBoxTimeToSitDownInPlayingSpot
			// 
			this->textBoxTimeToSitDownInPlayingSpot->Location = System::Drawing::Point(152, 40);
			this->textBoxTimeToSitDownInPlayingSpot->Name = L"textBoxTimeToSitDownInPlayingSpot";
			this->textBoxTimeToSitDownInPlayingSpot->ReadOnly = true;
			this->textBoxTimeToSitDownInPlayingSpot->Size = System::Drawing::Size(33, 20);
			this->textBoxTimeToSitDownInPlayingSpot->TabIndex = 36;
			this->textBoxTimeToSitDownInPlayingSpot->Text = L"4";
			// 
			// labelTimeToSitDownInPlayingSpot
			// 
			this->labelTimeToSitDownInPlayingSpot->AutoSize = true;
			this->labelTimeToSitDownInPlayingSpot->Location = System::Drawing::Point(5, 27);
			this->labelTimeToSitDownInPlayingSpot->Name = L"labelTimeToSitDownInPlayingSpot";
			this->labelTimeToSitDownInPlayingSpot->Size = System::Drawing::Size(180, 13);
			this->labelTimeToSitDownInPlayingSpot->TabIndex = 34;
			this->labelTimeToSitDownInPlayingSpot->Text = L"Time to sit down in playing spot (sec)";
			// 
			// ScrollBarTimeToSitDownInPlayingSpot
			// 
			this->ScrollBarTimeToSitDownInPlayingSpot->LargeChange = 2;
			this->ScrollBarTimeToSitDownInPlayingSpot->Location = System::Drawing::Point(8, 40);
			this->ScrollBarTimeToSitDownInPlayingSpot->Maximum = 20;
			this->ScrollBarTimeToSitDownInPlayingSpot->Minimum = 1;
			this->ScrollBarTimeToSitDownInPlayingSpot->Name = L"ScrollBarTimeToSitDownInPlayingSpot";
			this->ScrollBarTimeToSitDownInPlayingSpot->Size = System::Drawing::Size(130, 20);
			this->ScrollBarTimeToSitDownInPlayingSpot->TabIndex = 35;
			this->ScrollBarTimeToSitDownInPlayingSpot->Value = 4;
			this->ScrollBarTimeToSitDownInPlayingSpot->ValueChanged += gcnew System::EventHandler(this, &Form1::ScrollBarTimeToSitDownInPlayingSpot_ValueChanged);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1175, 653);
			this->Controls->Add(this->groupBoxPositioningDrumsTimesIntervals);
			this->Controls->Add(this->groupBoxMeasurePositionsMarker1);
			this->Controls->Add(this->groupBoxAutoAdjustProcessingParameters);
			this->Controls->Add(this->groupBoxDrumsEdition);
			this->Controls->Add(this->checkBoxAdvanceSettings);
			this->Controls->Add(this->groupBoxWindows);
			this->Controls->Add(this->checkBoxEditDrums);
			this->Controls->Add(this->groupBoxCalibrations);
			this->Controls->Add(this->groupBoxInterface3D);
			this->Controls->Add(this->groupBoxProcessingParameteres);
			this->Controls->Add(this->checkBoxVolumeControl);
			this->Controls->Add(this->buttonStart);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Location = System::Drawing::Point(810, 0);
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Virtual Drums - by majksoft";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->Shown += gcnew System::EventHandler(this, &Form1::Form1_Shown);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseMove);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBoxProcessingParameteres->ResumeLayout(false);
			this->groupBoxProcessingParameteres->PerformLayout();
			this->groupBoxInterface3D->ResumeLayout(false);
			this->groupBoxInterface3D->PerformLayout();
			this->groupBoxCalibrations->ResumeLayout(false);
			this->groupBoxCalibrations->PerformLayout();
			this->groupBoxWindows->ResumeLayout(false);
			this->groupBoxWindows->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownDrumPositionX))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownDrumPositionY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownDrumPositionZ))->EndInit();
			this->groupBoxDrumsEdition->ResumeLayout(false);
			this->groupBoxDrumsEdition->PerformLayout();
			this->groupBoxAutoAdjustProcessingParameters->ResumeLayout(false);
			this->groupBoxAutoAdjustProcessingParameters->PerformLayout();
			this->groupBoxMeasurePositionsMarker1->ResumeLayout(false);
			this->groupBoxMeasurePositionsMarker1->PerformLayout();
			this->groupBoxPositioningDrumsTimesIntervals->ResumeLayout(false);
			this->groupBoxPositioningDrumsTimesIntervals->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
private:
			//AUDIO
			 irrklang::ISoundEngine *l_soundEngine1, *l_soundEngine2;
			 irrklang::ISoundSource *l_soundSampleEng1_bassdrum_foot, *l_soundSampleEng1_hihat_closed, *l_soundSampleEng1_hihat_open, *l_soundSampleEng1_hihat_foot,
									*l_soundSampleEng2_bassdrum_foot, *l_soundSampleEng2_hihat_closed, *l_soundSampleEng2_hihat_open, *l_soundSampleEng2_hihat_foot;
			 

/////////////////////////////////////////////
//FORM LOAD
/////////////////////////////////////////////
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {


			 l_threadInterface3D = gcnew Thread(gcnew ThreadStart(this, &virtualDrums_temp::Form1::ThreadTaskInterface3D));
			 l_threadInterface3D->IsBackground = true;

			 l_threadMainComputing = gcnew Thread(gcnew ThreadStart(this, &virtualDrums_temp::Form1::ThreadTaskMainComputing));
			 l_threadMainComputing->IsBackground = false;

			 l_threadPlaySounds1 = gcnew Thread(gcnew ThreadStart(this, &virtualDrums_temp::Form1::ThreadTaskPlaySounds1));
			 l_threadPlaySounds1->IsBackground = false;

			 l_threadPlaySounds2 = gcnew Thread(gcnew ThreadStart(this, &virtualDrums_temp::Form1::ThreadTaskPlaySounds2));
			 l_threadPlaySounds2->IsBackground = false;

			 l_threadLongTimeRefreshingLoop = gcnew Thread(gcnew ThreadStart(this, &virtualDrums_temp::Form1::ThreadLongTimeRefreshingLoop));
			 l_threadLongTimeRefreshingLoop->IsBackground = true;


			 //codebook parameters
			 scrollbarCodebookModMin->Value = g_iCodeBookModMin;
			 scrollbarCodebookModMax->Value = g_iCodeBookModMax;
			 scrollbarCodebookCbBounds->Value = g_iCodeBookCbBounds;
			 textBoxCodebookModMin->Text = g_iCodeBookModMin.ToString();
			 textBoxCodebookModMax->Text = g_iCodeBookModMax.ToString();
			 textBoxCodebookCbBounds->Text = g_iCodeBookCbBounds.ToString();

			 scrollbarColorFactorBounds->Value = cvRound(g_dColorFactorBounds * 10);
			 scrollbarSaturationFactorBounds->Value = cvRound(g_dSaturationFactorBounds * 10);

			 ScrollBarNumberOfDrums->Value = g_iDrumsNumber; 

			 ScrollBarNumberFramesToLearnBG->Value = g_iNumberFramesToLearnBG;

			 ScrollBarNumberOfDrumToChangeProperty->Maximum = g_iDrumsNumber;
			 ScrollBarNumberOfDrumToChangeProperty->Value = 2;


			 groupBoxAutoAdjustProcessingParameters->Enabled = !checkBoxAutoAdjustOnOff->Checked;

			 //will be enabled after starting playing
			 buttonRefreshAutoAdjust->Enabled = false;

			 //will be enabled when we will know colors of markers
			 buttonSetUpDrumKit->Enabled = false;




			 //hit-hat sound preparing
				 l_soundEngine1 = irrklang::createIrrKlangDevice();
				 l_soundSampleEng1_bassdrum_foot = l_soundEngine1->addSoundSourceFromFile(".\\audioSamples\\bassdrum_foot.wav"); 
				 l_soundSampleEng1_hihat_closed = l_soundEngine1->addSoundSourceFromFile(".\\audioSamples\\hihat_closed.wav"); 
				 l_soundSampleEng1_hihat_open = l_soundEngine1->addSoundSourceFromFile(".\\audioSamples\\hihat_open.wav"); 
				 l_soundSampleEng1_hihat_foot = l_soundEngine1->addSoundSourceFromFile(".\\audioSamples\\hihat_foot.wav"); 

				 l_soundEngine2 = irrklang::createIrrKlangDevice();
				 l_soundSampleEng2_bassdrum_foot = l_soundEngine2->addSoundSourceFromFile(".\\audioSamples\\bassdrum_foot.wav"); 
				 l_soundSampleEng2_hihat_closed = l_soundEngine2->addSoundSourceFromFile(".\\audioSamples\\hihat_closed.wav"); 
				 l_soundSampleEng2_hihat_open = l_soundEngine2->addSoundSourceFromFile(".\\audioSamples\\hihat_open.wav"); 
				 l_soundSampleEng2_hihat_foot = l_soundEngine2->addSoundSourceFromFile(".\\audioSamples\\hihat_foot.wav"); 



			 // could not start engine
			 if (!l_soundEngine1) 
				 MessageBox::Show("could not start audio engine1");
			 if (!l_soundEngine2) 
				 MessageBox::Show("could not start audio engine2");


			 ////reading audio samples from dir ..\audioSamples\*.wav
				 int _i=0;
				 array<Char>^_cArraySeparatorDot = gcnew array<Char>{'.'};
				 char _cTempFileName[100];
				 array<System::String^>^ _strArraySplitedFilename;
				 System::String^ _strFileNameTemp;
				 System::String^ _strFileNameTemp2;
				 DIR	*_dirAudio;
				 struct dirent *_direntAudio;
				 _dirAudio = opendir(".\\audioSamples\\.");
				 if (_dirAudio){
					while ((_direntAudio = readdir(_dirAudio)) != NULL){
						
						sprintf(_cTempFileName, "%s", _direntAudio->d_name );

						_strFileNameTemp = gcnew System::String(_cTempFileName);
						_strArraySplitedFilename = _strFileNameTemp->ToString()->Split( _cArraySeparatorDot, StringSplitOptions::RemoveEmptyEntries );
						if (_i>1){
							_strFileNameTemp2 = _strArraySplitedFilename[1];
							if (_strFileNameTemp2->ToString() == gcnew System::String("wav")){
								comboBoxDrumsAudioSamples->Text = "snaredrum.wav";
								comboBoxDrumsAudioSamples->Items->Add(_strFileNameTemp);
							}
						}
						_i++;
					}

					closedir(_dirAudio);
				 }
			 //end - reading audio samples from dir ..\audioSamples\*.wav


}

/////////////////////////////////////////////
//FORM MOVE MOUSE
/////////////////////////////////////////////
private: System::Void Form1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		 //refreshing DrumsList
		 if (g_bIfDrumsListNeedToRefresh == 1){
	 		System::String^ _strDrumInfoTemp;

			listBoxListOfDrums->Items->Clear();
			listBoxListOfDrums->Items->Add( "List of drums:" );

			for (int i=0; i<g_vecDrums2.size(); i++){
				_strDrumInfoTemp = (i+1).ToString() + " " + mmToSysString( g_vecDrums2[i].voice );	//if drum is no hi-hat
				listBoxListOfDrums->Items->Add( _strDrumInfoTemp );
			}
			g_bIfDrumsListNeedToRefresh = 0;
		 }

	 	////refreshing interface values values
			scrollbarCodebookModMax->Value = g_iCodeBookModMax;
			scrollbarCodebookModMin->Value = g_iCodeBookModMin;
			scrollbarColorFactorBounds->Value = g_dColorFactorBounds*10.0;
		//end - refreshing interface values values

		if (g_bIfMarkersColorMarkingIsDone){

			groupBoxMeasurePositionsMarker1->Enabled = true;

			if (g_bIfDrumsPositioning)
				groupBoxPositioningDrumsTimesIntervals->Enabled = false;
			
			//enable only one time after marking color markers and started to looking for markers is on
			if (!checkBoxEditDrums->Enabled){
				buttonRefreshAutoAdjust->Enabled = 1;
			}

			//enabling after playing functions and learning background was done
				checkBoxEditDrums->Enabled = true;
				checkBoxEditDrums->Checked = true;
				groupBoxProcessingParameteres->Enabled = true;
				groupBoxInterface3D->Enabled = true;
				if ( (!g_bIfDrumsAllArePlaced) && (!g_bIfDrumsPositioning) )
					buttonSetUpDrumKit->Enabled = 1;

			if (g_bIfDrumsAllArePlaced){
				ScrollBarNumberOfDrumToChangeProperty->Enabled = true;
				numericUpDownDrumPositionX->Enabled = true;
				numericUpDownDrumPositionY->Enabled = true;
				numericUpDownDrumPositionZ->Enabled = true;
			}

			if (!g_bRefreshingAutoProcessingParameters)
				buttonRefreshAutoAdjust->Enabled = true;

		}

		if (!g_bIfPositionMarker1Measure)
			buttonMeasurePrecision->Enabled = true;

		



		 }

/////////////////////////////////////////////
//FORM SHOWN
/////////////////////////////////////////////
private: System::Void Form1_Shown(System::Object^  sender, System::EventArgs^  e) {			 
}

/////////////////////////////////////////////
//FORM CLOSING
/////////////////////////////////////////////
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {

			 g_bIfProgramClosing = true;

			 if (l_threadMainComputing->IsAlive)
				while(1){
					if (g_bIfMainLoopStopped)
						break;

					Sleep(10);
				}

			 l_threadInterface3D->Abort();
			 l_threadMainComputing->Abort();
			 l_threadPlaySounds1->Abort();
			 l_threadPlaySounds2->Abort();
			 l_threadLongTimeRefreshingLoop->Abort();


			 ////sound stuff cleaning
				 if (l_soundSampleEng1_bassdrum_foot){
					 l_soundSampleEng1_bassdrum_foot->drop(); // release the pointer, no longer needed
					 l_soundSampleEng1_bassdrum_foot = 0;
				 }

				 if (l_soundSampleEng1_hihat_closed){
					 l_soundSampleEng1_hihat_closed->drop(); // release the pointer, no longer needed
					 l_soundSampleEng1_hihat_closed = 0;
				 }

				 if (l_soundSampleEng1_hihat_open){
					 l_soundSampleEng1_hihat_open->drop(); // release the pointer, no longer needed
					 l_soundSampleEng1_hihat_open = 0;
				 
				 }

				 if (l_soundSampleEng1_hihat_foot){
					 l_soundSampleEng1_hihat_foot->drop(); // release the pointer, no longer needed
					 l_soundSampleEng1_hihat_foot = 0;
				 }

			 //end - sound stuff cleaning

		 }



/////////////////////////////////////////////
//FORM PAINT
/////////////////////////////////////////////
private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {

 			 //refreshing DrumsList
			 if (g_bIfDrumsListNeedToRefresh == 1){
	 			System::String^ _strDrumInfoTemp;

				listBoxListOfDrums->Items->Clear();
				listBoxListOfDrums->Items->Add( "List of drums:" );

				for (int i=0; i<g_vecDrums2.size(); i++){
					_strDrumInfoTemp = (i+1).ToString() + " " + mmToSysString( g_vecDrums2[i].voice );
					listBoxListOfDrums->Items->Add( _strDrumInfoTemp );
				}
				g_bIfDrumsListNeedToRefresh = 0;
			 }


		 }



/////////////////////////////////////////////
//BUTTONS
/////////////////////////////////////////////
private: System::Void buttonStart_Click(System::Object^  sender, System::EventArgs^  e) {

			//only for checking if there are this files
				CvFileStorage* _fsCalibrationCfgFile = cvOpenFileStorage( "_calibrationCfg.xml", 0, CV_STORAGE_READ );
				CvFileStorage* _fsCalibIntrinsicDistFile = cvOpenFileStorage("_calibIntrinsicDist.xml", 0, CV_STORAGE_READ);

			 //checking if there are this files
			 if ( (_fsCalibrationCfgFile) && (_fsCalibIntrinsicDistFile) ){

				//to make calibration only reading from file (data from previous calibrations)
					checkBoxCalibrationType->Checked = false;
					checkBoxCalibrateCamerasIntrinsicDistortion->Checked = false;

				//off this boxes to the end of program because if playing is started there is no need to change this parameters
					groupBoxCalibrations->Enabled = false;
					comboBoxCamerasImageSize->Enabled = false;
					ScrollBarNumberOfDrums->Enabled = false;
					scrollBarDrumsDepth->Enabled = false;
					scrollBarDrumsWidth->Enabled = false;

				//disabling only for starting playing functions and learning background
					checkBoxEditDrums->Checked = false;
					checkBoxEditDrums->Enabled = false;
					groupBoxProcessingParameteres->Enabled = false;
					groupBoxInterface3D->Enabled = false;

				//function and threading starting
					mmStartCalibration();
					l_threadInterface3D->Start();
					l_threadMainComputing->Start();
					l_threadPlaySounds1->Start();
					l_threadPlaySounds2->Start();
					l_threadLongTimeRefreshingLoop->Start();

			 }
			 else{
				 sprintf(g_cMessages, "There was no calibration of(one or both):\n-cameras intrinsic and distortion parameters\n-calibration process of finding cameras positions\n\nor files was deleted (one or both):\n-_calibrationCfg.xml\n-_calibIntrinsicDist.xml\n\nIn both case simply do calibrations process.");
				 System::String^ _sysstringMessages = gcnew String(g_cMessages);
				MessageBox::Show(_sysstringMessages);
			 }

			 //realising pointers so files can be used in next part of program
			 cvReleaseFileStorage( &_fsCalibrationCfgFile );
			 cvReleaseFileStorage( &_fsCalibIntrinsicDistFile );

		 }
private: System::Void buttonCalibrate_Click(System::Object^  sender, System::EventArgs^  e) {

			this->Enabled = false;

			if (checkBoxCalibrateCamerasIntrinsicDistortion->Checked){

				//message with instruction of how calibrate cameras intrinsic and distortion parameters
				sprintf(g_cMessages, "Starting calibration process of cameras intrinsic and distortion parameters.\n\n\nAfter click 'OK' please wait a moment to show window with camera view\nand then put chessboard in a way to cover maximum area view of the first camera\nand then move it slightly but keep whole chessboard in a view of camera.\n\nWhen it's done (when program will close view window of first camera),\ndo the same with second camera.");
				System::String^ _sysstringMessages = gcnew String(g_cMessages);
				MessageBox::Show(_sysstringMessages);

				mmStartCalibrationCameraIntrinsicDistortion();
			}

			if (checkBoxCalibrationType->Checked){

				//message with instruction of how calibrate cameras positions
				sprintf(g_cMessages, "Starting calibration process of finding cameras positions.\n\n\nAfter click 'OK' please wait a moment to show windows with cameras view\nand then put chessboard in a way to see it in both views - left and right camera\nand then try to move and rotate it but keep whole chessboard in both views of cameras.\n\nWhen it's done program will close those windows.");
				System::String^ _sysstringMessages = gcnew String(g_cMessages);
				MessageBox::Show(_sysstringMessages);

				mmStartCalibration();
			
			}

			this->Enabled = true;

			checkBoxCalibrateCamerasIntrinsicDistortion->Checked = false;
			checkBoxCalibrationType->Checked = false;
		 }
private: System::Void buttonInterface3D_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 l_threadInterface3D->Start();

		 }
private: System::Void buttonSetUpDrumKit_Click(System::Object^  sender, System::EventArgs^  e) {
			 g_bIfDrumsPositioning = true;
			
			 //disable to the end of program - because we only ones setup drum kit per one run program
			 buttonSetUpDrumKit->Enabled = 0;
		 }
private: System::Void buttonRefreshAutoAdjust_Click(System::Object^  sender, System::EventArgs^  e) {

			 sprintf(g_cMessages, "After click OK program will try to auto adjust processing parameters.\n\nPlease do:\n- LEAVE drum sticks away from cameras view area\n- be in your playing spot all over this time\n- make moves like you will be doing in playing drums ( simply move your arms;) )\n\nPLEASE DO THIS UNTIL NEXT MESSAGE APPEAR");
			 System::String^ _sysstringMessages = gcnew String(g_cMessages);
			MessageBox::Show(_sysstringMessages);

			 g_bRefreshingAutoProcessingParameters = true;

			 //disable to the end of refreshing parameters
			 buttonRefreshAutoAdjust->Enabled = 0;
		 }
private: System::Void buttonMeasurePrecision_Click(System::Object^  sender, System::EventArgs^  e) {
			 g_bIfPositionMarker1Measure = true;
			 buttonMeasurePrecision->Enabled = false;

			int _iPositionMarker1FramesNumberOnOneMeasure = 60;
			int _iPositionMarker1FramesCounterOnOneMeasure = 0;

			textBoxMeasurePrecision->Clear();
			textBoxMeasurePrecision->Text += mmToSysString( "\n\nMarker 1 x, y, z - next measure:\n" );

			while(1){

					if ( (g_bIfPositionMarker1Measure) ){

						if (_iPositionMarker1FramesCounterOnOneMeasure <= _iPositionMarker1FramesNumberOnOneMeasure){
							
							textBoxMeasurePrecision->Text += mmToSysString( "\n" ) + g_matrixMarker1Position3D[0] + ", " + 
																		g_matrixMarker1Position3D[1] + ", " + 
																		g_matrixMarker1Position3D[2] ;

							_iPositionMarker1FramesCounterOnOneMeasure++;
						}
						else{
							g_bIfPositionMarker1Measure = false;
							_iPositionMarker1FramesCounterOnOneMeasure = 0;
							break;
						}
						

					}

				Sleep(100);	//time to wait to next signal from keyboard that key 'zero' was pressed 

			}

		 }



/////////////////////////////////////////////
//SCROLLBARS
/////////////////////////////////////////////
private: System::Void scrollbarCodebookModMin_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->textBoxCodebookModMin->Text = this->scrollbarCodebookModMin->Value.ToString();
			 g_iCodeBookModMin = this->scrollbarCodebookModMin->Value;
		 }
private: System::Void scrollbarCodebookModMax_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->textBoxCodebookModMax->Text = this->scrollbarCodebookModMax->Value.ToString();
			 g_iCodeBookModMax = this->scrollbarCodebookModMax->Value;
		 }
private: System::Void scrollbarCodebookCbBounds_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->textBoxCodebookCbBounds->Text = this->scrollbarCodebookCbBounds->Value.ToString();
			 g_iCodeBookCbBounds = this->scrollbarCodebookCbBounds->Value;
		 }
private: System::Void scrollbarColorFactorBounds_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_dColorFactorBounds = double(scrollbarColorFactorBounds->Value) / double(10);
			 textBoxColorFactorBounds->Text = g_dColorFactorBounds.ToString();
		 }
private: System::Void scrollbarSaturationFactorBounds_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_dSaturationFactorBounds = double(scrollbarSaturationFactorBounds->Value) / double(10);
			 textBoxSaturationFactorBounds->Text = g_dSaturationFactorBounds.ToString();
		 }
private: System::Void ScrollBarRotationAngleX_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_dInterface3dRotX = ScrollBarRotationAngleX->Value;
			 textBoxRotationAngleX->Text = g_dInterface3dRotX.ToString();
		 }
private: System::Void ScrollBarRotationAngleY_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_dInterface3dRotY = ScrollBarRotationAngleY->Value;
			 textBoxRotationAngleY->Text = g_dInterface3dRotY.ToString();
		 }
private: System::Void ScrollBarRotationAngleZ_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_dInterface3dRotZ = ScrollBarRotationAngleZ->Value;
			 textBoxRotationAngleZ->Text = g_dInterface3dRotZ.ToString();
		 }
private: System::Void ScrollBarNumberOfDrums_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_iDrumsNumber = ScrollBarNumberOfDrums->Value;
			 textBoxNumberOfDrums->Text = g_iDrumsNumber.ToString();
			 ScrollBarNumberOfDrumToChangeProperty->Maximum = g_iDrumsNumber;
		 }
private: System::Void ScrollBarNumberOfDrumToChangeProperty_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 System::String^ _strFileNameTemp;

			 g_iDrumNumberToChangeProperty = ScrollBarNumberOfDrumToChangeProperty->Value;
			 textBoxNumberOfDrumToChangeProperty->Text = g_iDrumNumberToChangeProperty.ToString();

			 _strFileNameTemp = gcnew System::String( g_vecDrums1[g_iDrumNumberToChangeProperty-1].voice.c_str() );
			 comboBoxDrumsAudioSamples->Text = _strFileNameTemp;

			 textBoxDrumPositionX->Text = cvRound( g_vecDrums1[g_iDrumNumberToChangeProperty -1].x ).ToString();
			 textBoxDrumPositionY->Text = cvRound( g_vecDrums1[g_iDrumNumberToChangeProperty -1].y ).ToString();
			 textBoxDrumPositionZ->Text = cvRound( g_vecDrums1[g_iDrumNumberToChangeProperty -1].z ).ToString();

			 g_bIfDrumsListNeedToRefresh = 1;
		 }

private: System::Void scrollBarChessboardSqareSize_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
			 g_dChessboardSquareSize = double((scrollBarChessboardSqareSize->Value)/10.0);
			 textBoxChessboardSqareSize->Text = g_dChessboardSquareSize.ToString();
		 }
private: System::Void scrollBarChessboardCornersNumberX_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
			 this->textBoxChessboardCornersNumberX->Text = this->scrollBarChessboardCornersNumberX->Value.ToString();
			 g_iChessboardCornersNumberX = this->scrollBarChessboardCornersNumberX->Value;
		 }
private: System::Void scrollBarChessboardCornersNumberY_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
			 this->textBoxChessboardCornersNumberY->Text = this->scrollBarChessboardCornersNumberY->Value.ToString();
			 g_iChessboardCornersNumberY = this->scrollBarChessboardCornersNumberY->Value;
		 }
private: System::Void scrollBarAngleOfCameraSeeingInDegree_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
			 this->textBoxAngleOfCameraSeeingInDegree->Text = this->scrollBarAngleOfCameraSeeingInDegree->Value.ToString();
			 g_dAngleOfCameraSeeingInDegree = double(this->scrollBarAngleOfCameraSeeingInDegree->Value);
		 }
private: System::Void scrollBarDrumsWidth_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
			 this->textBoxDrumsWidth->Text = this->scrollBarDrumsWidth->Value.ToString();
			 g_iDrumsWidth = this->scrollBarDrumsWidth->Value;
		 }
private: System::Void scrollBarDrumsDepth_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
			 this->textBoxDrumsDepth->Text = this->scrollBarDrumsDepth->Value.ToString();
			 g_iDrumsDepth = this->scrollBarDrumsDepth->Value;
		 }

private: System::Void ScrollBarAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust_ValueChanged(System::Object^  sender, 
			 System::EventArgs^  e) {

			g_dAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust = double((ScrollBarAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->Value)/10000.0);
			textBoxAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust->Text = g_dAutoAdjustNonZeroPixelsPercentageAfterModMinMaxAdjust.ToString();
		 }
private: System::Void ScrollBarAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust_ValueChanged(System::Object^  sender, 
			 System::EventArgs^  e) {

			g_dAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust = double((ScrollBarAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->Value)/100.0);
			textBoxAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust->Text = (g_dAutoAdjustGoodResultsPercentageAfterModMinMaxAdjust*100.0).ToString();
		 }
private: System::Void ScrollBarAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust_ValueChanged(System::Object^  sender, 
			 System::EventArgs^  e) {

			g_dAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust = double((ScrollBarAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->Value)/10000.0);
			textBoxAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust->Text = g_dAutoAdjustNonZeroPixelsPercentageAfterColorFactorAdjust.ToString();
		 }
private: System::Void ScrollBarAutoAdjustGoodResultsPercentageAfterColorFactorAdjust_ValueChanged(System::Object^  sender, 
			 System::EventArgs^  e) {

			g_dAutoAdjustGoodResultsPercentageAfterColorFactorAdjust = double((ScrollBarAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->Value)/100.0);
			textBoxAutoAdjustGoodResultsPercentageAfterColorFactorAdjust->Text = (g_dAutoAdjustGoodResultsPercentageAfterColorFactorAdjust*100.0).ToString();
		 }
private: System::Void ScrollBarNumberFramesToLearnBG_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->textBoxNumberFramesToLearnBG->Text = this->ScrollBarNumberFramesToLearnBG->Value.ToString();
			 g_iNumberFramesToLearnBG = this->ScrollBarNumberFramesToLearnBG->Value;
		 }

private: System::Void ScrollBarTimeToSitDownInPlayingSpot_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 textBoxTimeToSitDownInPlayingSpot->Text = ScrollBarTimeToSitDownInPlayingSpot->Value.ToString();
			 g_iTimeToSitDownInPlayingSpot = ScrollBarTimeToSitDownInPlayingSpot->Value;
		 }
private: System::Void ScrollBarTimeToPlaceMarkerInDesiredPosition_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 textBoxTimeToPlaceMarkerInDesiredPosition->Text = ScrollBarTimeToPlaceMarkerInDesiredPosition->Value.ToString();
			 g_iTimeToPlaceMarkerInDesiredPosition = ScrollBarTimeToPlaceMarkerInDesiredPosition->Value;
		 }
private: System::Void ScrollBarTimeToWaitForAveragingPositionOfMarker_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 textBoxTimeToWaitForAveragingPositionOfMarker->Text = ScrollBarTimeToWaitForAveragingPositionOfMarker->Value.ToString();
			 g_iTimeToWaitForAveragingPositionOfMarker = ScrollBarTimeToWaitForAveragingPositionOfMarker->Value;
		 }
private: System::Void ScrollBarCalibrationActualProcessNumberOfFrames_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 textBoxCalibrationActualProcessNumberOfFrames->Text = ScrollBarCalibrationActualProcessNumberOfFrames->Value.ToString();
			 g_iCalibrationActualProcessNumberOfFrames = ScrollBarCalibrationActualProcessNumberOfFrames->Value;
		 }

/////////////////////////////////////////////
//NUMERIC_UP_DOWN
/////////////////////////////////////////////
private: System::Void numericUpDownDrumPositionX_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (numericUpDownDrumPositionX->Value == 1){
				 g_vecDrums1[g_iDrumNumberToChangeProperty -1].x += 1.0;
				 g_vecDrums2[g_iDrumNumberToChangeProperty -1].x += 1.0;

				 g_vecDrums1[g_iDrumNumberToChangeProperty -1].refresingDrumPlaneCornersAndABCDcenterPlane();
				 g_vecDrums2[g_iDrumNumberToChangeProperty -1].refresingDrumPlaneCornersAndABCDcenterPlane();

				 textBoxDrumPositionX->Text = cvRound( g_vecDrums1[g_iDrumNumberToChangeProperty -1].x ).ToString();
			 }
			 if (numericUpDownDrumPositionX->Value == -1){
				 g_vecDrums1[g_iDrumNumberToChangeProperty -1].x -= 1.0;
				 g_vecDrums2[g_iDrumNumberToChangeProperty -1].x -= 1.0;

				 g_vecDrums1[g_iDrumNumberToChangeProperty -1].refresingDrumPlaneCornersAndABCDcenterPlane();
				 g_vecDrums2[g_iDrumNumberToChangeProperty -1].refresingDrumPlaneCornersAndABCDcenterPlane();

				 textBoxDrumPositionX->Text = cvRound( g_vecDrums1[g_iDrumNumberToChangeProperty -1].x ).ToString();
			 }
			 numericUpDownDrumPositionX->Value = 0;
		 }
private: System::Void numericUpDownDrumPositionY_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (numericUpDownDrumPositionY->Value == 1){
				 g_vecDrums1[g_iDrumNumberToChangeProperty -1].y += 1.0;
				 g_vecDrums2[g_iDrumNumberToChangeProperty -1].y += 1.0;
				 
				 g_vecDrums1[g_iDrumNumberToChangeProperty -1].refresingDrumPlaneCornersAndABCDcenterPlane();
				 g_vecDrums2[g_iDrumNumberToChangeProperty -1].refresingDrumPlaneCornersAndABCDcenterPlane();

				 textBoxDrumPositionY->Text = cvRound( g_vecDrums1[g_iDrumNumberToChangeProperty -1].y ).ToString();
			 }
			 if (numericUpDownDrumPositionY->Value == -1){
				 g_vecDrums1[g_iDrumNumberToChangeProperty -1].y -= 1.0;
				 g_vecDrums2[g_iDrumNumberToChangeProperty -1].y -= 1.0;
				 
				 g_vecDrums1[g_iDrumNumberToChangeProperty -1].refresingDrumPlaneCornersAndABCDcenterPlane();
				 g_vecDrums2[g_iDrumNumberToChangeProperty -1].refresingDrumPlaneCornersAndABCDcenterPlane();

				 textBoxDrumPositionY->Text = cvRound( g_vecDrums1[g_iDrumNumberToChangeProperty -1].y ).ToString();
			 }
			 numericUpDownDrumPositionY->Value = 0;
		 }
private: System::Void numericUpDownDrumPositionZ_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (numericUpDownDrumPositionZ->Value == 1){
				 g_vecDrums1[g_iDrumNumberToChangeProperty -1].z += 1.0;
				 g_vecDrums2[g_iDrumNumberToChangeProperty -1].z += 1.0;
				 
				 g_vecDrums1[g_iDrumNumberToChangeProperty -1].refresingDrumPlaneCornersAndABCDcenterPlane();
				 g_vecDrums2[g_iDrumNumberToChangeProperty -1].refresingDrumPlaneCornersAndABCDcenterPlane();

				 textBoxDrumPositionZ->Text = cvRound( g_vecDrums1[g_iDrumNumberToChangeProperty -1].z ).ToString();
			 }
			 if (numericUpDownDrumPositionZ->Value == -1){
				 g_vecDrums1[g_iDrumNumberToChangeProperty -1].z -= 1.0;
				 g_vecDrums2[g_iDrumNumberToChangeProperty -1].z -= 1.0;
				 
				 g_vecDrums1[g_iDrumNumberToChangeProperty -1].refresingDrumPlaneCornersAndABCDcenterPlane();
				 g_vecDrums2[g_iDrumNumberToChangeProperty -1].refresingDrumPlaneCornersAndABCDcenterPlane();

				 textBoxDrumPositionZ->Text = cvRound( g_vecDrums1[g_iDrumNumberToChangeProperty -1].z ).ToString();
			 }
			 numericUpDownDrumPositionZ->Value = 0;
		 }


/////////////////////////////////////////////
//CHECKBOX
/////////////////////////////////////////////
private: System::Void checkBoxLeftCameraView_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_bInterfaceShowOpenCVWinLeftView = checkBoxLeftCameraView->Checked;
		 }
private: System::Void checkBoxRightCameraView_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_bInterfaceShowOpenCVWinRightView = checkBoxRightCameraView->Checked;
		 }
private: System::Void checkBoxViewOnlyMasks_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_bInterfaceShowViewOnlyMasks = checkBoxViewOnlyMasks->Checked;
		 }
private: System::Void checkBoxg_bInterfaceShowViewWitoutBackground_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_bInterfaceShowViewWithoutBackground = checkBoxViewWitoutBackground->Checked;
		 }
private: System::Void checkBoxViewColorSeparationWithoutBackground_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_bInterfaceShowViewColorSeparationWithoutBackground = checkBoxViewColorSeparationWithoutBackground->Checked;
		 }
private: System::Void checkBoxViewColorSeparationWithoutBackgroundClosed_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_bInterfaceShowViewColorSeparationWithoutBackgroundClosed = checkBoxViewColorSeparationWithoutBackgroundClosed->Checked;
		 }
private: System::Void checkBoxViewColorSeparationWithoutBackgroundClosedSegment_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_bInterfaceShowViewColorSeparationWithoutBackgroundClosedSegment = checkBoxViewColorSeparationWithoutBackgroundClosedSegment->Checked;
		 }
private: System::Void checkBoxViewHue_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_bInterfaceShowViewHue = checkBoxViewHue->Checked;
		 }
private: System::Void checkBoxViewSaturation_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_bInterfaceShowViewSaturation = checkBoxViewSaturation->Checked;
		 }
private: System::Void checkBoxViewValue_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_bInterfaceShowViewValue = checkBoxViewValue->Checked;
		 }

private: System::Void checkBoxLookOnMarkerSaturation_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_bLookOnMarkerSaturation = checkBoxLookOnMarkerSaturation->Checked;
		 }
private: System::Void checkBoxUseBackgroundSubtraction_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_bUseBackgroundSubtraction = checkBoxUseBackgroundSubtraction->Checked;
		 }

private: System::Void checkBoxCalibrationType_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_iCalibrationType = checkBoxCalibrationType->Checked;

			 if (g_iCalibrationType == 1){

				 checkBoxCalibrateCamerasIntrinsicDistortion->Checked = false;
				 checkBoxCalibrateCamerasIntrinsicDistortion->Text = "Calibrate cameras intrinsic and distorions:\n - No";

				 checkBoxCalibrationType->Text = "Cameras calibration type:\n - New calibration";
			 }
			 else
				 checkBoxCalibrationType->Text = "Cameras calibration type:\n - Saved calibration";
		 }
private: System::Void checkBoxCalibrateCamerasIntrinsicDistortion_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (checkBoxCalibrateCamerasIntrinsicDistortion->Checked == 1){

				 checkBoxCalibrationType->Checked = false;
				 checkBoxCalibrationType->Text = "Cameras calibration type:\n - Saved calibration";

				 checkBoxCalibrateCamerasIntrinsicDistortion->Text = "Calibrate cameras intrinsic and distorions:\n - Yes";
			 }
			 else
				 checkBoxCalibrateCamerasIntrinsicDistortion->Text = "Calibrate cameras intrinsic and distorions:\n - No";
		 }
private: System::Void checkBoxAdvanceSettings_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (checkBoxAdvanceSettings->Checked == 1){
				 checkBoxAdvanceSettings->Text = "Advance settings:\n - Hide";
				 this->Size = System::Drawing::Size(1185, 685);
			 }
			 else{
				 checkBoxAdvanceSettings->Text = "Advance settings:\n - Show";
				 this->Size = System::Drawing::Size(377, 685);
			 }

		 }
private: System::Void checkBoxEditDrums_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (checkBoxEditDrums->Checked == 1)
				 groupBoxDrumsEdition->Enabled = 1;

			 if (checkBoxEditDrums->Checked == 0)
				 groupBoxDrumsEdition->Enabled = 0;
		 }
private: System::Void checkBoxAutoAdjustOnOff_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (checkBoxAutoAdjustOnOff->Checked == 1){	//if manual adjust processing parameters
				 groupBoxAutoAdjustProcessingParameters->Enabled = 0;
				 scrollbarCodebookCbBounds->Enabled = 1;
				 scrollbarCodebookModMax->Enabled = 1;
				 scrollbarCodebookModMin->Enabled = 1;
				 scrollbarColorFactorBounds->Enabled = 1;
				 scrollbarSaturationFactorBounds->Enabled = 1;
				 checkBoxUseBackgroundSubtraction->Checked = 1;
				 checkBoxLookOnMarkerSaturation->Checked = 0;
				 checkBoxUseBackgroundSubtraction->Enabled = 1;
				 checkBoxLookOnMarkerSaturation->Enabled = 1;
			 }

			 if (checkBoxAutoAdjustOnOff->Checked == 0){	//if auto adjust processing parameters
				 groupBoxAutoAdjustProcessingParameters->Enabled = 1;
				 scrollbarCodebookCbBounds->Enabled = 0;
				 scrollbarCodebookModMax->Enabled = 0;
				 scrollbarCodebookModMin->Enabled = 0;
				 scrollbarColorFactorBounds->Enabled = 0;
				 scrollbarSaturationFactorBounds->Enabled = 0;
				 checkBoxUseBackgroundSubtraction->Checked = 1;
				 checkBoxLookOnMarkerSaturation->Checked = 0;
				 checkBoxUseBackgroundSubtraction->Enabled = 0;
				 checkBoxLookOnMarkerSaturation->Enabled = 0;
			 }
		 }


/////////////////////////////////////////////
//COMBOBOX
/////////////////////////////////////////////
private: System::Void comboBoxCamerasImageSize_TextUpdate(System::Object^  sender, System::EventArgs^  e) {
			 
		 }

private: System::Void comboBoxCamerasImageSize_TextChanged(System::Object^  sender, System::EventArgs^  e) {

			 if (comboBoxCamerasImageSize->Text == "800 x 600 (not recommended)"){
				 g_iCamerasMainLoopResolutionHeight = 600;
				 g_iCamerasMainLoopResolutionWidth = 800;
			 }

			 if (comboBoxCamerasImageSize->Text == "640 x 480"){
				 g_iCamerasMainLoopResolutionHeight = 480;
				 g_iCamerasMainLoopResolutionWidth = 640;
			 }

			 if (comboBoxCamerasImageSize->Text == "320 x 240 (default)"){
				 g_iCamerasMainLoopResolutionHeight = 240;
				 g_iCamerasMainLoopResolutionWidth = 320;
			 }
		 }

private: System::Void comboBoxDrumsAudioSamples_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (g_vecDrums1.size() == g_iDrumsNumber){
				 l_threadInterface3D->Suspend();
				 l_threadMainComputing->Suspend();
				 l_threadPlaySounds1->Suspend();
				 l_threadPlaySounds2->Suspend();
				 l_threadLongTimeRefreshingLoop->Suspend();

				 g_vecDrums1[g_iDrumNumberToChangeProperty-1].voice = mmToStdString(comboBoxDrumsAudioSamples->Text);
				 g_vecDrums2[g_iDrumNumberToChangeProperty-1].voice = mmToStdString(comboBoxDrumsAudioSamples->Text);

				 char* _cStr = (char*)(void*)Marshal::StringToHGlobalAnsi( gcnew System::String("audioSamples\\" + comboBoxDrumsAudioSamples->Text) );
				 g_vecDrums1[g_iDrumNumberToChangeProperty-1].soundEngine->removeAllSoundSources();
				 g_vecDrums2[g_iDrumNumberToChangeProperty-1].soundEngine->removeAllSoundSources();
				 g_vecDrums1[g_iDrumNumberToChangeProperty-1].soundSampleEng = g_vecDrums1[g_iDrumNumberToChangeProperty-1].soundEngine->addSoundSourceFromFile( _cStr );
				 g_vecDrums1[g_iDrumNumberToChangeProperty-1].soundEngine->removeAllSoundSources();
				 g_vecDrums2[g_iDrumNumberToChangeProperty-1].soundEngine->removeAllSoundSources();
				 g_vecDrums2[g_iDrumNumberToChangeProperty-1].soundSampleEng = g_vecDrums2[g_iDrumNumberToChangeProperty-1].soundEngine->addSoundSourceFromFile( _cStr );


				 l_threadInterface3D->Resume();
				 l_threadMainComputing->Resume();
				 l_threadPlaySounds1->Resume();
				 l_threadPlaySounds2->Resume();
				 l_threadLongTimeRefreshingLoop->Resume();

			 }

			 g_bIfDrumsListNeedToRefresh = 1;
		 }

private: System::Void comboBoxDrumsAudioSamples_Click(System::Object^  sender, System::EventArgs^  e) {
			 g_bIfDrumsListNeedToRefresh = 1;
		 }

private: System::Void comboBoxDrumsAudioSamples_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 g_bIfDrumsListNeedToRefresh = 1;
		 }

		 
/////////////////////////////////////////////
//TEXTBOXES
/////////////////////////////////////////////


//////////////START OF THREAD STUFF

private: 

void ThreadTaskInterface3D(){

	mmInterface3D();
	Sleep(1);
	
}

void ThreadTaskMainComputing(){

	mmStartMain();
	Sleep(1);
	
}

void ThreadTaskPlaySounds1(){

	while (1){

		////marker 1 playing suond
		if ( ( g_bIfMarker1GoingDown ) ){
			for (int i=0; i<g_vecDrums1.size(); i++){
				if (g_vecDrums1[i].ifDrumIsHitted){

					//g_iTimeDelay = GetTickCount() - g_iTimeDelay;
					//g_iTimeDelayAvg = g_iTimeDelayAvg + g_iTimeDelay;
					//g_iTimeDelayAvg = cvRound(g_iTimeDelayAvg/2);
					//g_iTimeDelay = 0;
					//g_bIfTimeDelayNeedReset=0;

					float _fVolume = 0;

					if (checkBoxVolumeControl->CheckState == System::Windows::Forms::CheckState::Indeterminate){	//static volume
						_fVolume = 1.0;
					}

					if (checkBoxVolumeControl->CheckState == System::Windows::Forms::CheckState::Checked)		//dynamic volume
						_fVolume = (g_dMarker1DistanceFromLastChangeDirY/60.0) < 0.05 ? 0.05 : (g_dMarker1DistanceFromLastChangeDirY/60.0);

					if (checkBoxVolumeControl->CheckState == System::Windows::Forms::CheckState::Unchecked){	//mute
						_fVolume = 0.0;
					}

					g_vecDrums1[i].soundEngine->setSoundVolume(_fVolume);


					if (g_vecDrums1[i].voice == "hi-hat"){	//checking if drum is hi-hat
						////hi-hat playing by stick	
						if (g_bDrumPedalHihatState){	//closed hi-hat hited by stick - so play sound
							l_soundEngine1->setSoundVolume(_fVolume);
							l_soundEngine1->play2D(l_soundSampleEng1_hihat_closed);
						}
						else{							//open hi-hat hited by stick - so play sound
							l_soundEngine1->setSoundVolume(_fVolume);
							l_soundEngine1->play2D(l_soundSampleEng1_hihat_open);
						}
					}
					else{	//if drum is not hi-hat
						g_vecDrums1[i].soundEngine->play2D(g_vecDrums1[i].soundSampleEng);
					}

					sprintf (g_cDrumsPositioningText6,"drum 2 hitted: %d", g_vecDrums1[1].iTimesHitted);
					g_vecDrums1[i].ifDrumIsHitted = false;

				}
			}
		}//end - marker 1 playing sound

		l_soundEngine1->setSoundVolume(1.0);

		////bussdrum playing
		if( g_bDrumBassHitted ){
			l_soundEngine1->play2D(l_soundSampleEng1_bassdrum_foot);
			g_bDrumBassHitted = false;
		}


		//hihat playing by foot only
		if (g_bDrumPedalStateChange){		//
			if (g_bDrumPedalHihatState){	//closing hi-hat by foot - so play sound
				l_soundEngine1->play2D(l_soundSampleEng1_hihat_foot);
			}
			else{
				;	//only opening hi-hat - no sound
			}
			g_bDrumPedalStateChange = false;

		}


		Sleep(2);
	}		
}


void ThreadTaskPlaySounds2(){

	while (1){
	
		////marker 2 playing
		if ( (g_bIfMarker2GoingDown) ){
			for (int i=0; i<g_vecDrums2.size(); i++){
				if (g_vecDrums2[i].ifDrumIsHitted){

					float _fVolume = 0;

					if (checkBoxVolumeControl->CheckState == System::Windows::Forms::CheckState::Indeterminate)	//static volume
						_fVolume = 1.0;

					if (checkBoxVolumeControl->CheckState == System::Windows::Forms::CheckState::Checked)		//dynamic volume
						_fVolume = (g_dMarker2DistanceFromLastChangeDirY/60.0) < 0.05 ? 0.05 : (g_dMarker2DistanceFromLastChangeDirY/60.0);

					if (checkBoxVolumeControl->CheckState == System::Windows::Forms::CheckState::Unchecked){	//mute
						_fVolume = 0.0;
					}

					g_vecDrums2[i].soundEngine->setSoundVolume(_fVolume);


					if (g_vecDrums2[i].voice == "hi-hat"){	//checking if drum is hi-hat
						////hi-hat playing by stick	
						if (g_bDrumPedalHihatState){	//closed hi-hat hited by stick - so play sound
							l_soundEngine2->setSoundVolume(_fVolume);
							l_soundEngine2->play2D(l_soundSampleEng2_hihat_closed);
						}
						else{							//open hi-hat hited by stick - so play sound
							l_soundEngine2->setSoundVolume(_fVolume);
							l_soundEngine2->play2D(l_soundSampleEng2_hihat_open);
						}
					}
					else{	//if drum is not hi-hat
						g_vecDrums2[i].soundEngine->play2D(g_vecDrums2[i].soundSampleEng);
					}


					g_vecDrums2[i].ifDrumIsHitted = false;

				}
			}
		}//end - marker 2 playing sound

		Sleep(2);
	}
}

void ThreadLongTimeRefreshingLoop(){

	while(1){


		Sleep(100);	//
	}
}


//////////////END OF THREAD STUFF


//README
private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 MessageBox::Show("Virtual Drums NRC (NOT Release Candidate ;) )\n by Majksoft from Poland\n\nversion 0.2.0.||.0.01.0333.3.05.0.9.... ;)\n\n\nQuestions...\nBugs(there are many of them now because it's not finished;) ) \nSuggestion... \nWant to buy? \nWant to cooperate with building this game for sale?\nWant to sale this game when it will be finished?\nAnd any other reason... \n\nPlease feel free to contact: \ne-mail: majkelmaciek@gmail.com\n\n\nPLEASE DO NOT COPY THIS PROGRAM\nWITHOUT INFORMING ME AND WITHOUT MY PERMISSION",
							"Readme",
							MessageBoxButtons::OK,
							MessageBoxIcon::Asterisk,
							MessageBoxDefaultButton::Button1,
							MessageBoxOptions::ServiceNotification);
		 }









};
}

