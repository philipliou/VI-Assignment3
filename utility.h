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
    cv::Mat map_labeled = cv::imread("/Users/Philip/Google Drive/Spring 2013/Visual Interfaces/Assignment 3/ass3-labeled.pgm", 0);
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

/* Define similar IsNorthOf, IsSouthOf, IsEastOf, IsWestOf, IsNearOf for points. i.e. Point.IsNorthOf(bldg);
/* Calculate if this_building is North of target_building */
bool IsNorthOf (Point src, Bldg *tgt) {
    // y-coordinate of tgt is greater than y-coordinate of src: true
    if (tgt->GetCenter().y > src.y) {
        return true;
    } else {
        return false;
    }

};

bool IsSouthOf (Point src, Bldg *tgt) {
    // y-coordinate of tgt is less than y-coordinate of src: true
    if (tgt->GetCenter().y < src.y) {
        return true;
    } else {
        return false;
    }
};

bool IsEastOf (Point src, Bldg *tgt) {
    // x-coordinate of tgt is greater than x-coordinate of src: true
    if (tgt->GetCenter().x > src.x) {
        return true;
    } else {
        return false;
    }
};

bool IsWestOf (Point src, Bldg *tgt) {
    // x-coordinate of tgt is less than x-coordinate of src: true
    if (tgt->GetCenter().x < src.x) {
        return true;
    } else {
        return false;
    }
};

bool IsNear (Point src, Bldg *tgt) {
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
    
    Mat tempMap = tgt->GetMap();
    int tgtNum = tgt->GetBldgno();
    
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
double euclideanDist(Point p, Point q) {
    Point diff = p - q;
    return sqrt(diff.x*diff.x + diff.y*diff.y);
};

vector<int> CalcEquivClass (Point src, vector<Bldg> *BldgList) {
    
    static const cv::Mat map_labeled = cv::imread("/Users/Philip/Google Drive/Spring 2013/Visual Interfaces/Assignment 3/ass3-labeled.pgm", 0);
    
    int closeBldg = 0;
    double minDistance = euclideanDist(src, BldgList->at(0).GetCenter());
    vector<int> equivclass;

//    for (int i = 0; i < 27; i++ ) {
//        // cout << "Euclidean distance: " << euclideanDist(src, BldgList->at(i).GetCenter()) << endl;
//    	if (euclideanDist(src, BldgList->at(i).GetCenter()) < minDistance) {
//    		closeBldg = i;
//    		minDistance = euclideanDist(src, BldgList->at(i).GetCenter());
//    	}
//    }
    
    // Check if the point is actually in the building, if it is, then same equivalence class as points in the building.
    
    if (map_labeled.at<bool>(src.y, src.x) != 0) {
        closeBldg = map_labeled.at<bool>(src.y, src.x) - 1;
    	equivclass.push_back(closeBldg);
    	equivclass.push_back(0);
    	equivclass.push_back(0);
    	equivclass.push_back(0);
    	equivclass.push_back(0);
    	equivclass.push_back(1);
        
    } else {
        for (int i = 0; i < 27; i++ ) {
            // cout << "Euclidean distance: " << euclideanDist(src, BldgList->at(i).GetCenter()) << endl;
            if (euclideanDist(src, BldgList->at(i).GetCenter()) < minDistance) {
                closeBldg = i;
                minDistance = euclideanDist(src, BldgList->at(i).GetCenter());
            }
        }
    // Otherwise, find closest building to determine equivalence class.
    	equivclass.push_back(closeBldg);
	    equivclass.push_back(IsNorthOf(src, &BldgList->at(closeBldg)));
		equivclass.push_back(IsSouthOf(src, &BldgList->at(closeBldg)));
		equivclass.push_back(IsEastOf(src, &BldgList->at(closeBldg)));
		equivclass.push_back(IsWestOf(src, &BldgList->at(closeBldg)));
		equivclass.push_back(IsNear(src, &BldgList->at(closeBldg)));
    }

    // cout << src << " is closest to building # " << closeBldg + 1 << "with distance: " << minDistance << endl;

 //   cout << src << " is close to " << closeBldg << " : " ;
	// for(int i = 1; i < 6; i++) {
 //   	cout << equivclass.at(i);
 //   }
 //   cout << endl;
    
    return equivclass;
};

void printPointDesc(Point src, vector<Bldg> *BldgList) {
   vector<int> holder = CalcEquivClass(src, BldgList);
   int closeBldg = holder.at(0);
	
   cout << src << " is" ;

   if (holder.at(1)) {
   	cout << " north of (called " << BldgList->at(closeBldg).GetName() << " )";
   }

   if (holder.at(2)) {
   	cout << " south of (called " << BldgList->at(closeBldg).GetName() << " )";
   }

   if (holder.at(3)) {
   	cout << " east of (called " << BldgList->at(closeBldg).GetName() << " )";
   }

   if (holder.at(4)) {
   	cout << " west of (called " << BldgList->at(closeBldg).GetName() << " )";
   }

   if (holder.at(5)) {
   	cout << " near of (called " << BldgList->at(closeBldg).GetName() << " )";
   }

   cout << endl;

};

// Generates a vector<Points> that is the EquivClassSet. 
// 1. For each black pixel in map. 
// 		:Generate the EquivClass vector relative to the given building. 
// 		:Compare that to EquivClass vector of src. If ==, add to result.

vector<Point> CalcEquivClassSet (Point src, vector<Bldg> *BldgList, Mat *map) {
	// *map is a color_map
	vector<Point> EquivClassSet;
	vector<int> srcEquivClass = CalcEquivClass(src, BldgList);

	Point_<int> tempPt;

	for (int i = 0; i < map->rows; i++) {
		for (int j = 0; j < map->cols; j++) {
			// if (map->at<bool>(i,j) == 0) {
			if (true) {
                tempPt = Point_<int> (j,i);
				vector<int> tempEquivClass = CalcEquivClass(tempPt, BldgList);
				if (tempEquivClass == srcEquivClass) {
					EquivClassSet.push_back(tempPt);
				}
			}
		}
	}
    
 // cout << "These are the points that are in the EquivClassSet for point: " << src << endl;
 // for(vector<Point>::iterator it = EquivClassSet.begin(); it != EquivClassSet.end(); ++it) {
 //     cout << *it << endl;
 // }

	return EquivClassSet;
};

//  Finally, mouseEvent takes a vector<Points> and changes color on map for each
void mouseEventOriginal(int evt, int x, int y, int flags, void* param){
    if(evt==CV_EVENT_LBUTTONDOWN){
        Mat* map = (Mat*) param;
        Mat newMap = *map;
       cout << x << " " << y << " " << newMap.at<Vec3b>(y, x) << endl;
        for (int start_x = x - 10; start_x < x + 10; start_x++) {
            for (int start_y = y - 10; start_y < y + 10; start_y++) {
                newMap.at<Vec3b>(start_y, start_x)[0] = 255;
                newMap.at<Vec3b>(start_y, start_x)[1] = 0;
                newMap.at<Vec3b>(start_y, start_x)[2] = 0;
            }
        }
        
//        cout << x << " " << y << " " << newMap.at<Vec3b>(y, x) << endl;
        cv::imshow("Original Map", newMap);
    }
}

void mouseEvent(int evt, int x, int y, int flags, void* param){

    // Map_bw that persists throughtout the program
    static cv::Mat map_bw = cv::imread("/Users/Philip/Google Drive/Spring 2013/Visual Interfaces/Assignment 3/ass3-campus.pgm", 0);
    static cv::Mat map_color = cv::imread("/Users/Philip/Google Drive/Spring 2013/Visual Interfaces/Assignment 3/ass3-campus.pgm", 1);
    static cv::Mat map_labeled = cv::imread("/Users/Philip/Google Drive/Spring 2013/Visual Interfaces/Assignment 3/ass3-labeled.pgm", 0);
    
    // Get the building list that is passed. Used for CalcEquivClassSet call.
    vector<Bldg>* BldgList = (vector<Bldg>*) param;
    
    // Create point that user clicked.
    Point clickedPt = Point_<int>(x, y);

    // Get the points that you want to color.
    vector<Point> PointsToColor = CalcEquivClassSet (clickedPt, BldgList, &map_color);
    cout << "size of equivalence set: " << PointsToColor.size() << endl;
    
    if(evt==CV_EVENT_LBUTTONDOWN){

    	cout << "Point clicked: " << clickedPt << endl;
    	printPointDesc(clickedPt, BldgList);
        Mat tempMap = map_color.clone();

        // Color the map green for every point that is in the equivalence class.

        int ptsColored = 0;
        for(vector<Point>::iterator it = PointsToColor.begin(); it != PointsToColor.end(); ++it) {
        	ptsColored++;
       	// cout << it->y << " " << it->x << " " << endl;     

            tempMap.at<Vec3b>(it->y, it->x)[0] = 0;
            tempMap.at<Vec3b>(it->y, it->x)[1] = 255;
            tempMap.at<Vec3b>(it->y, it->x)[2] = 0;
        }

        cout << "Color of pt clicked: " << tempMap.at<Vec3b>(clickedPt.y, clickedPt.x) << endl;

        cout << "Pts colored: " << ptsColored << endl;
       
        cv::imshow("Original Map", tempMap);
    }
}


#endif
