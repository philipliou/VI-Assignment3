//
//  utility.h
//  Assignment3
//
//  Created by Philip Liou on 4/6/13.
//  Copyright (c) 2013 Philip Liou. All rights reserved.
//

#ifndef Assignment3_utility_h
#define Assignment3_utility_h
#include <stdio.h>
#include <fstream>
#include <stdint.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <iostream>
#include "bldg.h"
using namespace cv;
using namespace std;

vector<Bldg> InitializeMap () {
	cv::Mat map = cv::imread("/Users/Philip/Google Drive/Spring 2013/Visual Interfaces/Assignment 3/ass3-campus.pgm");
    cv::Mat map_labeled = cv::imread("/Users/Philip/Google Drive/Spring 2013/Visual Interfaces/Assignment 3/ass3-labeled.pgm", 0        );
    ifstream labels ("/Users/Philip/Google Drive/Spring 2013/Visual Interfaces/Assignment 3/ass3-table-changed.txt", ifstream::in);
	vector<Bldg> BldgList;
	for (int i = 0; i < 27; i++) {
        BldgList.push_back(*new Bldg(map_labeled, i+1));
        std::string line;
    }
    
    string line;
    int i = 0;
    while(std::getline(labels, line)) {
        BldgList.at(i).SetName(line);
        i++;
    }
    
    return BldgList;
};

void mouseEvent(int evt, int x, int y, int flags, void* param){
    if(evt==CV_EVENT_LBUTTONDOWN){
        Mat* map = (Mat*) param;
        Mat newMap = *map;
        cout << x << " " << y << " " << newMap.at<Vec3b>(y, x) << endl;
        for (int start_x = x - 10; start_x < x + 10; start_x++) {
            for (int start_y = y - 10; start_y < y + 10; start_y++) {
                newMap.at<Vec3b>(start_y, start_x)[0] = 0;
                newMap.at<Vec3b>(start_y, start_x)[1] = 255;
                newMap.at<Vec3b>(start_y, start_x)[2] = 0;
            }
        }
        
        cout << x << " " << y << " " << newMap.at<Vec3b>(y, x) << endl;
        cv::imshow("Original Map", newMap);
    }
}

/* Define similar IsNorthOf, IsSouthOf, IsEastOf, IsWestOf, IsNearOf for points. i.e. Point.IsNorthOf(bldg);
/* Calculate if this_building is North of target_building */
bool IsNorthOf (Point src, Bldg tgt) {
    // y-coordinate of tgt is greater than y-coordinate of src: true
    if (tgt.GetCenter().y > src.y) {
        return true;
    } else {
        return false;
    }
};

bool IsSouthOf (Point src, Bldg tgt) {
    // y-coordinate of tgt is less than y-coordinate of src: true
    if (tgt.GetCenter().y < src.y) {
        return true;
    } else {
        return false;
    }
};

bool IsEastOf (Point src, Bldg tgt) {
    // x-coordinate of tgt is greater than x-coordinate of src: true
    if (tgt.GetCenter().x > src.x) {
        return true;
    } else {
        return false;
    }
};

bool IsWestOf (Point src, Bldg tgt) {
    // x-coordinate of tgt is less than x-coordinate of src: true
    if (tgt.GetCenter().x < src.x) {
        return true;
    } else {
        return false;
    }
};

bool IsNear (Point src, Bldg tgt) {
    // tgt building overlaps the expanded minimum-bounding rectangle of src: true
    int expand_distance = 34;
    int x_start = 0;
    int x_end = 275;
    int y_start = 0;
    int y_end = 495;
    
    // Set expanded bounding rectangle of point; checking for boundary conditions.
    if (src.x > expand_distance) {
        x_start = src.x - expand_distance;
    }
    
    if (src.x + expand_distance < 275) {
        x_end = src.x + expand_distance;
    }
    
    if (src.y > expand_distance) {
        y_start = src.y - expand_distance;
    }
    
    if (src.y + expand_distance < 495) {
        y_end = src.y + expand_distance;
    }
    
//    cout << "x_start: " << x_start;
//    cout << " x_end: " << x_end;
//    cout << " y_start: " << y_start;
//    cout << " y_end: " << y_end << endl;
    
    Mat tempMap = tgt.GetMap();
    int tgtNum = tgt.GetBldgno();
    
//    cout << "START THE EXTENDED BOUNDING RECTANGLE HERE" << endl;
    for (int i = y_start; i < y_end; i++) {
        for (int j = x_start ; j < x_end; j++) {
//            cout << (int)tempMap.at<bool>(i,j) << " ";
            if ((int)tempMap.at<bool>(i,j) == tgtNum) {
                return true;
            }
        }
    }

    return false;
};

//  Generate EquivClass vector for a point.
// 1. Find the closest building to the point using Euclidean distance.
// 2. Calculate the boolean vector: where
// 		[0] = closest building's number,
// 		[1] = IsNorthOf(closest building's number)
// 		[2] = IsSouthOf(closest building's number)
// 		[3] = IsEastOf(closest building's number)
// 		[4] = IsWestOf(closest building's number)
// 		[5] = IsNear(closest building's number)

vector<bool> CalcEquivClass (Point src, int closeBldg) {
    
};

// Generates a vector<Points> that is the EquivClassSet. 
// 1. For each black pixel in map. 
// 		:Generate the EquivClass vector relative to the given building. 
// 		:Compare that to EquivClass vector of src. If ==, add to result.
vector<Points> CalcEquivClassSet (Point src, int closeBldg) {
	vector<bool> srcEquivClass = CalcEquivClass(src, closeBldg);
};

//  Finally, mouseEvent takes a vector<Points> and changes color on map for each.





#endif
