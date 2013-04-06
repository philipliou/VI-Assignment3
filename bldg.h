//
//  bldg.h
//  Assignment3
//
//  Created by Philip Liou on 3/31/13.
//  Copyright (c) 2013 Philip Liou. All rights reserved.
//

#ifndef Assignment3_bldg_h
#define Assignment3_bldg_h
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <iostream>
using namespace cv;
using namespace std;

class Bldg
{
private:
    std::string name_;                            // name
    int bldgNo_;                                 // building number
    cv::Mat soloMap_;                            // map of the building
    cv::Point center_;                           // center of mass
    int area_;                                   // area
    cv::Point upLeft_;                           // MBR (upper-left coordinate)
    cv::Point lowRight_;                         // MBR (lower-right coordinate)
    vector<string> shapeDesc_;           // geometric description
    vector<string> sizeDesc_;          // size description
    vector<string> orientDesc_;        // orientation description

public:
    Bldg(cv::Mat map, int bldgNo);
    void CalcArea (void);            // calculate area: just count black pixels
    void CalcCOM (void);             // calculate center of mass
    void CalcMBR (void);             // calculate minimum bounding rectangle: loop and find the top-left, lower-right black coordinates
    void CalcShapeDesc (void);         // define functions to generate geoDescriptions
    void CalcSizeDesc (Mat map);        // define functions to generate sizeDescriptions
    void CalcOrientDesc (void);
    
    /* Basic Getter Functions */
    string GetName(void) {
        return name_;
    };
    
    int GetBldgno() {
        return bldgNo_;
    };
    
    cv::Mat GetMap() {
        return soloMap_;
    };
    
    cv::Point GetCenter() {
        return center_;
    };
    
    int GetArea() {
        return area_;
    };
    cv::Point GetUpLeft() {
        return upLeft_;
    };
    
    cv::Point GetLowRight() {
        return lowRight_;
    };
    
    string GetShapeDesc() {
        return shapeDesc_.at(0);
    };
    
    string GetSizeDesc() {
        return sizeDesc_.at(0);
    };
    
    string GetOrientDesc() {
        return orientDesc_.at(0);
    }
    
    void printBldg() {
        cout << "Name: " << GetName() << endl;
        cout << "bldgNo: " << GetBldgno() << endl;
        cout << "Center: " << GetCenter() << endl;
        cout << "Area: " << GetArea() << endl;
        cout << "upLeft: " << GetUpLeft() << endl;
        cout << "lowRight: " << GetLowRight() << endl;
        cout << "shapeDesc_: " << GetShapeDesc() << endl;
        cout << "sizeDesc: " << GetSizeDesc() << endl;
        cout << "orientDesc: " << GetOrientDesc() << endl;
    };
};


// If using namespace, then don't need to do namespace::
// Define short functions like getters and setters in .h file too. 
// Have another file for utility fucitons like utility.h
// Have another file to operates ON buil

#endif
