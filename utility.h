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




#endif
