/**
* @file		Geometry.h
* @author		kimbomm (springnode@gmail.com)
* @date		2017. 9. 13...
* @version	1.0.0
*
*  @brief
*			간단한 기하학 라이브러리
*	@remark
*			Created by kimbom on 2017. 9. 13...
*			Copyright 2017 kimbom.All rights reserved.
*/
#if !defined(ISPRING_7E1_9_D_GEOMETRY_HPP_INCLUDED)
#define ISPRING_7E1_9_D_GEOMETRY_HPP_INCLUDED
#include"../Verify/Verify.h"
#include<iostream>
#include<vector>
#include<string>
#include<opencv2/opencv.hpp>
namespace ispring {
	/**
	*	@brief 이 정적 클래스는 좌표 계산을 도와 줍니다.
	*	@author kimbomm
	*	@date 2017-09-13
	*/
	class CVGeometry {
	public:
		/**
		*	@brief 두점 사이의 각도를 계산 합니다.
		*	@param x1 첫번째 x좌표
		*	@param y1 첫번째 y좌표
		*	@param x2 두번째 x좌표
		*	@param y2 두번째 y좌표
		*	@warning 결과는 0~179 사이만 출력 합니다.
		*/
		static int GetDegree(int x1, int y1, int x2, int y2) {
			int d = static_cast<int>(floor((atan2(y1 - y2, x2 - x1) * 180 / acos(-1)) + 0.5));
			return (d + 180) % 180;//각도 양수화
		}
		/**
		*	@brief 두점 사이의 각도를 계산 합니다.
		*	@param from 첫번째 좌표
		*	@param to 두번째 좌표
		*	@warning 결과는 0~179 사이만 출력 합니다.
		*/
		static int GetDegree(cv::Point from, cv::Point to) {
			return GetDegree(from.x, from.y, to.x, to.y);
		}
		/**
		*	@brief 두 각도의 차이를 계산합니다.
		*	@param d1 첫번째 각도
		*	@param d2 두번째 각도
		*	@remark
		*		<img src="https://i.imgur.com/ec4bEjV.png" width="640">
		*/
		static bool GetDegreeDistance(int d1, int d2) {
			if (d1 < 0 || d1>179) {
				ISPRING_VERIFY("degree(d1) is less than 0 or greater than 179");
			}
			if (d2 < 0 || d2>179) {
				ISPRING_VERIFY("degree(d2) is less than 0 or greater than 179");
			}
			int dist1=std::max(d1, d2) - std::min(d1, d2);	//first dist
			int dist2 = 180 - std::max(d1, d2) + std::min(d1, d2);	//second dist
			return std::min(dist1, dist2);
		}
	};
}

#endif  //ISPRING_7E1_9_D_GEOMETRY_HPP_INCLUDED