///*
// * File:   backgroundSeeCodeBook.h
// * Author: Majk
// *
// * Created on 1 czerwiec 2010, 23:07
// */
//
//#ifndef _BACKGROUNDSEECODEBOOK_H
//#define	_BACKGROUNDSEECODEBOOK_H
//
//
//#define CHANNELS 3
//typedef struct ce {
//uchar learnHigh[CHANNELS]; //High side threshold for learning
//uchar learnLow[CHANNELS]; //Low side threshold for learning
//uchar max[CHANNELS]; //High side of box boundary
//uchar min[CHANNELS]; //Low side of box boundary
//int t_last_update; //Allow us to kill stale entries
//int stale; //max negative run (longest period of inactivity)
//} code_element;
//
//
//
//
//typedef struct code_book {
//code_element **cb;
//int numEntries;
//int t; //count every access
//} codeBook;
//
//
//
//int update_codebook(
//                    uchar* p,
//                    codeBook& c,
//                    unsigned* cbBounds,
//                    int numChannels
//                    );
//
//
//
//
//
//
/////////////////////////////////////////////////////////////////////
//// void find_connected_components(IplImage *mask, int poly1_hull0,
//// float perimScale, int *num,
//// CvRect *bbs, CvPoint *centers)
//// This cleans up the foreground segmentation mask derived from calls
//// to backgroundDiff
////
//// mask Is a grayscale (8-bit depth) “raw” mask image that
//// will be cleaned up
////
//// OPTIONAL PARAMETERS:
//// poly1_hull0 If set, approximate connected component by
//// (DEFAULT) polygon, or else convex hull (0)
//// perimScale Len = image (width+height)/perimScale. If contour
//// len < this, delete that contour (DEFAULT: 4)
//// num Maximum number of rectangles and/or centers to
//// return; on return, will contain number filled
//// (DEFAULT: NULL)
//// bbs Pointer to bounding box rectangle vector of
//// length num. (DEFAULT SETTING: NULL)
//// centers Pointer to contour centers vector of length
//// num (DEFAULT: NULL)
////
//
////void find_connected_components(
////                                IplImage* mask,
////                                int poly1_hull0 = 1,
////                                float perimScale = 4,
////                                int* num = NULL,
////                                CvRect* bbs = NULL,
////                                CvPoint* centers = NULL
////                                );
//
//void find_connected_components(
//                                IplImage *mask,
//                                int poly1_hull0,
//                                float perimScale,
//                                int *num,
//                                CvRect *bbs,
//                                CvPoint *centers
//                                );
//
//
//
//
//#endif	/* _BACKGROUNDSEECODEBOOK_H */
//
