//
//  main.cpp
//  Assignment3
//
//  Created by Philip Liou on 3/29/13.
//  Copyright (c) 2013 Philip Liou. All rights reserved.
//

#include "bldg.h"
#include <stdint.h>
using namespace std;
using namespace cv;

int main(int argc, const char * argv[])
{
    cv::Mat map = cv::imread("/Users/Philip/Google Drive/Spring 2013/Visual Interfaces/Assignment 3/ass3-campus.pgm");
 
    FILE * labelFile;
    labelFile = fopen ("ass3-table.txt" , "r");

    cv::Mat map_labeled = cv::imread("/Users/Philip/Google Drive/Spring 2013/Visual Interfaces/Assignment 3/ass3-labeled.pgm", 0        );
    vector<int> areaCounter(28);
    
    for (int i = 0; i < map_labeled.rows; i++) {
        for (int j = 0; j < map_labeled.cols; j++) {
            std::cout << (int)map_labeled.at<bool>(i,j) << std::endl;
            areaCounter[(int)map_labeled.at<bool>(i,j)]++;
        }
    }
    
    for(std::vector<int>::size_type i = 0; i != areaCounter.size(); i++) {
        std::cout << "Building #" << i << " " << areaCounter[i] << endl;
    }
    
//    for (int i = 0; i < map.rows; i++) {
//        for (int j = 0; j < map.cols; j++) {
//            std::cout << (int)map.at<bool>(i,j) << std::endl;
//        }
//    }
    
//    cout << "M = "<< endl << " "  << map_labeled << endl << endl;

//    Bldg *testBuilding = new Bldg(map_labeled, 1);
//    testBuilding->CalcArea();
//    cout << testBuilding->GetBldgno() << endl;
    
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

