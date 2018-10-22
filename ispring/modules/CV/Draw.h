/**
* @file		Draw.h
* @author		kimbomm (springnode@gmail.com)
* @date		2018. 10. 22...
* @version	1.0.0
*
*  @brief
*			OpenCV drawing extension
*	@remark
*			Created by kimbom on 2018. 10. 22...
*			Copyright 2017 kimbom.All rights reserved.
*/
#if !defined(ISPRING_7E1_05_17_IMAGE_H_INCLUDED)
#define ISPRING_7E1_05_17_IMAGE_H_INCLUDED
#include<opencv2/opencv.hpp>
#include"../defines.h"
#include"rgb.h"

#ifndef DOXYGEN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif
#ifdef ISPRING_WINDOWS
#include<Windows.h>
#endif
#include"../Verify/VerifyError.h"
#include"../System/OS.h"
namespace ispring {
	/**
	*	@brief 이 정적 클래스는 이미지 처리 함수를 포함합니다.
	*	@author kimbomm
	*	@date 2017-05-23
	*/
	namespace CV{
		inline void DrawEllipseA(cv::Mat& image, cv::RotatedRect ellipse, cv::Scalar color, float alpha) {
			cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC1);
			cv::ellipse(mask, ellipse, cv::Scalar(255), CV_FILLED);
			for (size_t y = 0; y < image.rows; y++) {
				for (size_t x = 0; x < image.cols; x++) {
					if (mask.at<uchar>(y, x) != 0) {
						image.at<cv::Vec3b>(y, x) = image.at<cv::Vec3b>(y, x)*(1 - alpha) + cv::Vec3b(color[0], color[1], color[2])*(alpha);
					}
				}
			}
		}
		inline void DrawRectangleA(cv::Mat& image, cv::Rect rect, cv::Scalar color, float alpha) {
			cv::Mat crop = img(rect);
			cv::Mat box = cv::Mat::zeros(rect.height, rect.width, CV_8UC3) + c;
			crop = (1-alpha)*crop + alpha*box;
		}
		inline void DrawAnonBox(cv::Mat& img, cv::Rect rect, std::string text) {
			auto ShadowRect = [](cv::Rect rect)->cv::Rect {
				rect.x++;
				rect.y++;
				return rect;
			};
			auto CaptureBox = [](cv::Mat& img, cv::Rect rect, cv::Scalar color, double ratio)->void {
				cv::Point tl = rect.tl();
				cv::Point tr = cv::Point(rect.x + rect.width, rect.y);
				cv::Point bl = cv::Point(rect.x, rect.y + rect.height);
				cv::Point br = rect.br();
				cv::Point wrto = cv::Point(rect.width*ratio, 0);
				cv::Point hrto = cv::Point(0, rect.height*ratio);

				cv::line(img, tl, tl + wrto, color, 1, CV_AA);
				cv::line(img, tr, tr - wrto, color, 1, CV_AA);
				cv::line(img, bl, bl + wrto, color, 1, CV_AA);
				cv::line(img, br, br - wrto, color, 1, CV_AA);
				cv::line(img, tl, tl + hrto, color, 1, CV_AA);
				cv::line(img, bl, bl - hrto, color, 1, CV_AA);
				cv::line(img, tr, tr + hrto, color, 1, CV_AA);
				cv::line(img, br, br - hrto, color, 1, CV_AA);
			};
			std::deque<std::string> texts;
			std::string::size_type offset = 0;
			while (offset<text.length()) {
				std::string str = text.substr(offset, text.find("\n", offset) - offset);
				texts.push_front(str);
				offset += str.length() + 1;
			}
			cv::Scalar shadow = cv::Scalar(123, 123, 123);
			cv::Scalar white = cv::Scalar(243, 243, 255);
			int font_face = cv::FONT_HERSHEY_DUPLEX;
			double scale = 0.5F;
			int pos = 0;
			for (int i = 0; i < texts.size(); i++) {
				if (i + 1 == texts.size()) {
					scale = 0.6F;
				}
				int baseline = 0;
				cv::Size sz = cv::getTextSize(texts[i], font_face, scale, 1, &baseline);
				cv::putText(img, texts[i], cv::Point(rect.x + 1, rect.y - 2 + 1 - pos), font_face, scale, shadow, 1, CV_AA);
				cv::putText(img, texts[i], cv::Point(rect.x, rect.y - 2 - pos), font_face, scale, white, 1, CV_AA);
				pos += sz.height + 1;
			}
			CaptureBox(img, ShadowRect(rect), shadow, 0.3);
			CaptureBox(img, rect, white, 0.3);
		}

	};
}
#endif