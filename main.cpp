//
//  main.cpp
//  Assignment3
//
//  Created by Philip Liou on 3/29/13.
//  Copyright (c) 2013 Philip Liou. All rights reserved.
//

#include "bldg.h"
#include "utility.h"
#include <fstream>
#include <stdint.h>
using namespace std;
using namespace cv;

int main(int argc, const char * argv[])
{
    cv::Mat map = cv::imread("/Users/Philip/Google Drive/Spring 2013/Visual Interfaces/Assignment 3/ass3-campus.pgm", 1);
    cv::Mat map_bw = cv::imread("/Users/Philip/Google Drive/Spring 2013/Visual Interfaces/Assignment 3/ass3-campus.pgm", 0);
    
    vector<Bldg> BldgList;
    BldgList = InitializeMap();
    
//    BldgList.at(0).printBldg();
//    BldgList.at(0).CalcSpaceRel(BldgList);
//    BldgList.at(0).printSpaceRel();

//    vector<bool> CalcEquivClass (Point src, vector<Bldg> *BldgList);
    
    Point testPt = cv::Point_<int> (135, 221);
    
//    cout << IsNorthOf(testPt, &(BldgList.at(11)));
//    cout << IsSouthOf(testPt, &(BldgList.at(11)));
//    cout << IsEastOf(testPt, &(BldgList.at(11)));
//    cout << IsWestOf(testPt, &(BldgList.at(11)));
//    cout << IsNear(testPt, &(BldgList.at(11)));
    
    
//    CalcEquivClass(Point_<int> (1, 1), &BldgList);
//    CalcEquivClass(Point_<int> (135, 221), &BldgList);
//    CalcEquivClass(Point_<int> (0, 243), &BldgList);
//    CalcEquivClass(Point_<int> (274, 243), &BldgList);
//    CalcEquivClass(Point_<int> (140, 1), &BldgList);
//    CalcEquivClass(Point_<int> (140, 495), &BldgList);
//    CalcEquivClass(Point_<int> (275, 495), &BldgList);
//    printPointDesc(Point_<int> (124, 372), &BldgList);

    CalcEquivClassSet(Point_<int> (1, 1), &BldgList, &map_bw);
//    CalcEquivClassSet(Point_<int> (135, 221), &BldgList, &map_bw);
//    CalcEquivClassSet(Point_<int> (0, 243), &BldgList, &map_bw);
//    CalcEquivClassSet(Point_<int> (274, 243), &BldgList, &map_bw);
//    CalcEquivClassSet(Point_<int> (140, 1), &BldgList, &map_bw);
//    CalcEquivClassSet(Point_<int> (140, 495), &BldgList, &map_bw);
//    CalcEquivClassSet(Point_<int> (275, 495), &BldgList, &map_bw);    
    
//   cv::namedWindow("Original Map", cv::WINDOW_AUTOSIZE);
//   cv::imshow("Original Map", map);
//   cvSetMouseCallback("Original Map", mouseEvent, &map);
//   cv::waitKey();
    
/**** Code that might be useful ****/
//   cout << "M = "<< endl << " "  << map_labeled << endl << endl;
    
//    for (int i = 0; i < tempMap.cols; i++) {
//        for (int j = 0; j < tempMap.rows; j++) {
//            cout << "(" << i << ", " << j << ")" << endl; 
//            if ((int)tempMap.at<bool>(i,j) != 0) {
//                counter++;
//            }
//        }
//    }
//    bldg2.printBldg();
//    bldg3.printBldg();
// cout << bldg1.IsNear(bldg2) << " should be 1." << endl;
// cout << bldg2.IsNear(bldg2) << " should be 1." << endl;
// cout << bldg12.IsNear(bldg27) << " should be 0." << endl;
// cout << bldg9.IsNear(bldg13) << " should be 1." << endl;
// cout << bldg13.IsNear(bldg10) << " should be 1." << endl;
// cout << bldg9.IsNear(bldg27) << " should be 0." << endl;
// cout << bldg12.IsNear(bldg13) << " should be 1." << endl;
// cout << bldg13.IsNear(bldg12) << " should be 1." << endl;
    
//    cout << bldg1.IsNorthOf(bldg2) << bldg1.IsSouthOf(bldg2) << bldg1.IsEastOf(bldg2) << bldg1.IsWestOf(bldg2) << endl;
//    cout << bldg1.IsNorthOf(bldg23) << bldg1.IsSouthOf(bldg23) << bldg1.IsEastOf(bldg23) << bldg1.IsWestOf(bldg23) << endl;
//    cout << bldg12.IsNorthOf(bldg18) << bldg12.IsSouthOf(bldg18) << bldg12.IsEastOf(bldg18) << bldg12.IsWestOf(bldg18) << endl;
    
//   cv::namedWindow("Original Map", cv::WINDOW_AUTOSIZE);
//   cv::imshow("Original Map", map_labeled);
//   cv::waitKey();
    
//    Bldg bldg1 = BldgList.at(0);
//    Bldg bldg2 = BldgList.at(1);
//    Bldg bldg3 = BldgList.at(2);
//    Bldg bldg9 = BldgList.at(8);
//    Bldg bldg10 = BldgList.at(9);
//    Bldg bldg12 = BldgList.at(11);
//    Bldg bldg13 = BldgList.at(12);
//    Bldg bldg18 = BldgList.at(17);
//    Bldg bldg23 = BldgList.at(22);
//
//    bldg1.printBldg();
//    bldg12.printBldg();
//    bldg18.printBldg();
//    bldg23.printBldg();
 
    
/**** Convention ****/
//    Bldg *testBuilding = new Bldg(map_labeled, 27);
//    testBuilding->calcArea(a, b, c);

//    Bldg testBuilding2 (map_labeled, 27);
//    testBuilding2.calcArea(a, b, c);
//
//    &testBuilding2;
    
    return 0;
}

