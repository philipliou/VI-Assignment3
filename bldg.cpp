//
//  bldg.cpp
//  Assignment3
//
//  Created by Philip Liou on 3/31/13.
//  Copyright (c) 2013 Philip Liou. All rights reserved.
//

#include "bldg.h"

// Constructor
Bldg::Bldg(Mat map, int bldgNo){
    Mat copyMap = map.clone();
    int area = 0;
    for (int i = 0; i < copyMap.rows; i++) {
        for (int j = 0; j < copyMap.cols; j++) {
            if ((int)copyMap.at<bool>(i,j) != bldgNo) {
                copyMap.at<bool>(i,j) = 0;
            } else {
                area++;
            }
//            cout << (int)copyMap.at<bool>(i,j) << " ";
        }
//        cout << endl;
    }
    
    name_ = "Default Name";
    bldgNo_ = bldgNo;
    soloMap_ = copyMap.clone();
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
    int bldgNum = bldgNo_;
    Mat map = GetMap();

    for (int i = 0; i < soloMap_.rows; i++) {
        for (int j = 0; j < soloMap_.cols; j++) {
//            cout << (int)soloMap_.at<bool>(i,j) << " " ;
            if ((int)map.at<bool>(i,j) == bldgNum) {
                sumX += j;
                sumY += i;
                area++;
            }
        }
    }
    
//    cout << area << endl;
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
    int bldgNum = bldgNo_;
    Mat map = GetMap();    
    
    for (int i = 0; i < map.rows; i++) {
        for (int j = 0; j < map.cols; j++) {
            if ((int)map.at<bool>(i,j) == bldgNum) {
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
        orientDesc_.push_back("TALL");
        
    } else if (width/height > 1.3) {
        orientDesc_.push_back("WIDE");
        
    } else {
        orientDesc_.push_back("SYMMETRICAL");
        
    }
};

/* Calculate if this_building is North of target_building */
bool Bldg::IsNorthOf (Bldg tgt) {
    // y-coordinate of tgt is greater than y-coordinate of src: true
    if (tgt.GetCenter().y > GetCenter().y) {
        return true;
    } else {
        return false;
    }
};

bool Bldg::IsSouthOf (Bldg tgt) {
    // y-coordinate of tgt is less than y-coordinate of src: true
    if (tgt.GetCenter().y < GetCenter().y) {
        return true;
    } else {
        return false;
    }
};

bool Bldg::IsEastOf (Bldg tgt) {
    // x-coordinate of tgt is greater than x-coordinate of src: true
    if (tgt.GetCenter().x > GetCenter().x) {
        return true;
    } else {
        return false;
    }
};

bool Bldg::IsWestOf (Bldg tgt) {
    // x-coordinate of tgt is less than x-coordinate of src: true
    if (tgt.GetCenter().x < GetCenter().x) {
        return true;
    } else {
        return false;
    }
};

bool Bldg::IsNear (Bldg tgt) {
    // tgt building overlaps the expanded minimum-bounding rectangle of src: true
    int expand_distance = 34;
    int x_start = 0;
    int x_end = soloMap_.cols;
    int y_start = 0;
    int y_end = soloMap_.rows;
    
    // Set expanded bounding rectangle; checking for boundary conditions.
    if (upLeft_.x > expand_distance) {
        x_start = upLeft_.x - expand_distance;
    }
    
    if (lowRight_.x + expand_distance < soloMap_.cols) {
        x_end = lowRight_.x + expand_distance;
    }
    
    if (upLeft_.y > expand_distance) {
        y_start = upLeft_.y - expand_distance;
    }
    
    if (lowRight_.y + expand_distance < soloMap_.rows) {
        y_end = lowRight_.y + expand_distance;
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

/*
// 
void doShitToBuilding (Bldg *b, int *x) {
    //Change b's area
    b->area = 100;

    //
    int temp = *x;
};

*/