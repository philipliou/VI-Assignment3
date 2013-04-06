//
//  bldg.cpp
//  Assignment3
//
//  Created by Philip Liou on 3/31/13.
//  Copyright (c) 2013 Philip Liou. All rights reserved.
//

#include "bldg.h"

// Constructor
Bldg::Bldg(cv::Mat map, int bldgNo){
    Mat copyMap = map;
    int area = 0;
    for (int i = 0; i < copyMap.rows; i++) {
        for (int j = 0; j < copyMap.cols; j++) {
//            cout << (int)copyMap.at<bool>(i,j) << endl;
            if ((int)copyMap.at<bool>(i,j) != bldgNo) {
                copyMap.at<bool>(i,j) = 0;
            } else {
                copyMap.at<bool>(i,j) = 1;
                area++;
            }
        }
    }
    
    name_ = "Default Name";
    bldgNo_ = bldgNo;
    soloMap_ = copyMap;
    CalcCOM();
    area_ = area;
    CalcMBR();
    CalcShapeDesc();
    CalcSizeDesc(map);
    CalcOrientDesc();
};

// Calculate Area by counting black pixels
void Bldg::CalcArea () {
    int pixelCount = 0;
    for (int i = 0; i < soloMap_.rows; i++) {
        for (int j = 0; j < soloMap_.cols; j++) {
            if (soloMap_.at<int>(i,j) == bldgNo_) {
                pixelCount++;
            }
        }
    }
    area_ = pixelCount;
};

// calculate center of mass
void Bldg::CalcCOM () {
    int sumX = 0;
    int sumY = 0;
    int area = 0;

    for (int i = 0; i < soloMap_.rows; i++) {
        for (int j = 0; j < soloMap_.cols; j++) {
            if (soloMap_.at<bool>(i,j) == 1) {
                sumX += j;
                sumY += i;
                area++;
            }
        }
    }
    int centerX = sumX/area;
    int centerY = sumY/area;
    center_ = cv::Point_<int> (centerX, centerY);
};


// Calculate minimum bounding rectangle.
void Bldg::CalcMBR () {
    int minX = soloMap_.cols;
    int minY = soloMap_.rows;
    int maxX = 0;
    int maxY = 0;
    
    for (int i = 0; i < soloMap_.rows; i++) {
        for (int j = 0; j < soloMap_.cols; j++) {
            if (soloMap_.at<bool>(i,j) == 1) {
                minX = min(minX, j);
                minY = min(minY, i);
                maxX = max(maxX, j);
                maxY = max(maxY, i);
            }
        }
    }
    
    upLeft_ = Point(minX, minY);
    lowRight_ = Point(maxX, maxY);
    
};

// Calculate shapeDesc_
// Vocablary: "SQUARE", "RECTANGLE"
void Bldg::CalcShapeDesc () {
    float width = lowRight_.x - upLeft_.x;
    float height = lowRight_.y - upLeft_.y;
    
    if (width/height < 1/1.3 || width/height > 1.3) {
        shapeDesc_.push_back("RECTANGLE");
    } else {
        shapeDesc_.push_back("SQUARE");
    }
    
};

// Calculate sizeDesc_
// "SMALL", "MEDIUM", "LARGE"
void Bldg::CalcSizeDesc (Mat map) {
    // get size of all the other buildings and SUM them
    // then break out by size into SMALL, MEDIUM, LARGE using percentages
    int sizeCount = 0;
    for (int i = 0; i < map.rows; i++) {
        for (int j = 0; j < map.cols; j++) {
            if ((int)map.at<bool>(i,j) != 0 ) {
                sizeCount++;
            }
        }
    }
    
    int avgSize = sizeCount/27;
    cout << sizeCount << " " << avgSize << endl;
    
    if (area_ <= (avgSize * 0.5)) {
        sizeDesc_.push_back("SMALL");
    } else if (area_ >= (avgSize * 1.5)) {
        sizeDesc_.push_back("LARGE");
    } else {
        sizeDesc_.push_back("MEDIUM");
    }
};

// Calculate orientDesc_
// "TALL", "HORIZONTAL", "SYMMETRICAL"
void Bldg::CalcOrientDesc () {
    float width = lowRight_.x - upLeft_.x;
    float height = lowRight_.y - upLeft_.y;
    
    if (width/height < 1/1.3) {
        orientDesc_.push_back("WIDE");
    } else if (width/height > 1.3){
        shapeDesc_.push_back("TALL");
    } else {
        orientDesc_.push_back("SYMMETRICAL");
    }
};
/*
// 
void doShitToBuilding (Bldg *b, int *x) {
    //Change b's area
    b->area = 100;

    //
    int temp = *x;
};

*/