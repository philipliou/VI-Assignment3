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
    
//    for (int i = 0; i < map_labeled.rows; i++) {
//        for (int j = 0; j < map_labeled.cols; j++) {
//            std::cout << (int)map_labeled.at<bool>(i,j) << std::endl;
//            areaCounter[(int)map_labeled.at<bool>(i,j)]++;
//        }
//    }
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
  
    BldgList.at(0).printBldg();
    BldgList.at(1).printBldg();
    BldgList.at(26).printBldg();
    
    Bldg bldg1 = BldgList.at(0);
    Bldg bldg2 = BldgList.at(1);
    Bldg bldg27 = BldgList.at(26);
    
    cout << bldg1.IsNorthOf(bldg2) << bldg1.IsSouthOf(bldg2) << bldg1.IsEastOf(bldg2) << bldg1.IsWestOf(bldg2) << endl;
    
    cout << map.cols/8 << endl;
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
    
//    cv::namedWindow("Original Map", cv::WINDOW_AUTOSIZE);
//    cv::imshow("Original Map", testBuilding->GetMap());
//    cv::waitKey();
    
    return 0;
}

