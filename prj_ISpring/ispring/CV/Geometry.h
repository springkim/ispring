/*
*  Geometry.h
*  ISpring
*
*  Created by kimbom on 2017. 9. 13...
*  Copyright 2017 kimbom. All rights reserved.
*
*/
#if !defined(ISPRING_7E1_9_D_GEOMETRY_HPP_INCLUDED)
#define ISPRING_7E1_9_D_GEOMETRY_HPP_INCLUDED
#include<iostream>
#include<vector>
#include<string>
#include<opencv2/opencv.hpp>
namespace ispring {
	class Geometry {
	public:
		static int GetDegree(int x1, int y1, int x2, int y2) {
			int d = static_cast<int>(floor((atan2(y1 - y2, x2 - x1) * 180 / acos(-1)) + 0.5));
			return (d + 180) % 180;//각도 양수화
		}
		static int GetDegree(cv::Point from, cv::Point to) {
			return GetDegree(from.x, from.y, to.x, to.y);
		}
		//isSameDegree
	};
}

#endif  //ISPRING_7E1_9_D_GEOMETRY_HPP_INCLUDED