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
    cv::Mat map = cv::imread("/Users/Philip/Google Drive/Spring 2013/Visual Interfaces/Assignment 3/ass3-campus.pgm");
    cv::Mat map_labeled = cv::imread("/Users/Philip/Google Drive/Spring 2013/Visual Interfaces/Assignment 3/ass3-labeled.pgm", 0        );
    ifstream labels ("/Users/Philip/Google Drive/Spring 2013/Visual Interfaces/Assignment 3/ass3-table-changed.txt", ifstream::in);
    
//    cout << "M = "<< endl << " "  << map_labeled << endl << endl;
    
//  Create vector of buildings (including zeroes) and initialize all of them
    vector<Bldg> BldgList;
    for (int i = 0; i < 27; i++) {
        BldgList.push_back(*new Bldg(map_labeled, i+1));
    }
    std::string line;
    int i = 0;
    while(std::getline(labels, line)) {
        BldgList.at(i).SetName(line);
        i++;
    }
    
    Bldg bldg1 = BldgList.at(0);
    Bldg bldg2 = BldgList.at(1);
    Bldg bldg3 = BldgList.at(2);
    Bldg bldg9 = BldgList.at(8);
    Bldg bldg10 = BldgList.at(9);
    Bldg bldg12 = BldgList.at(11);
    Bldg bldg13 = BldgList.at(12);
    Bldg bldg27 = BldgList.at(26);
    
//    Mat tempMap = bldg2.GetMap();
    
//    int counter = 0;
//    for (int i = 0; i < tempMap.cols; i++) {
//        for (int j = 0; j < tempMap.rows; j++) {
//            cout << "(" << i << ", " << j << ")" << endl; 
//            if ((int)tempMap.at<bool>(i,j) != 0) {
//                counter++;
//            }
//        }
//    }
    
//    cout << "Counted area: " << counter << endl;

    
//    cv::namedWindow("Original Map", cv::WINDOW_AUTOSIZE);
//    cv::imshow("Original Map", map_labeled);
//    cv::waitKey();
    
    
//    cout << bldg1.IsNorthOf(bldg2) << bldg1.IsSouthOf(bldg2) << bldg1.IsEastOf(bldg2) << bldg1.IsWestOf(bldg2) << endl;
//    bldg2.printBldg();
//    bldg3.printBldg();
    
    cout << bldg1.IsNear(bldg2) << " should be 1." << endl;
    cout << bldg2.IsNear(bldg2) << " should be 1." << endl;
    cout << bldg12.IsNear(bldg27) << " should be 0." << endl;
    cout << bldg9.IsNear(bldg13) << " should be 1." << endl;
    cout << bldg13.IsNear(bldg10) << " should be 1." << endl;
    cout << bldg9.IsNear(bldg27) << " should be 0." << endl;
    cout << bldg12.IsNear(bldg13) << " should be 1." << endl;
    cout << bldg13.IsNear(bldg12) << " should be 1." << endl;
    
    bldg12.printBldg();
    bldg13.printBldg();
//
//    Bldg *testBuilding = new Bldg(map_labeled, 10);
//    testBuilding->printBldg();
    
    
    // Convention
//    Bldg *testBuilding = new Bldg(map_labeled, 27);
//    testBuilding->calcArea(a, b, c);

//    Bldg testBuilding2 (map_labeled, 27);
//    testBuilding2.calcArea(a, b, c);
//
//    &testBuilding2;
    
    return 0;
}

