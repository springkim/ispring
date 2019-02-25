/**
* @file		Viz.h
* @author		kimbomm (springnode@gmail.com)
* @date		2018. 11. 06...
* @version	1.0.0
*
*  @brief
*			Visualization 라이브러리
*	@remark
*			Created by kimbom on 2018. 11. 06...
*			Copyright 2017-2018 kimbom.All rights reserved.
*/
#if !defined(ISPRING_7E2_B_6_VIZ_H_HPP_INCLUDED)
#define ISPRING_7E2_B_6_VIZ_H_HPP_INCLUDED
#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>

namespace ispring {
	namespace CV {
		inline cv::Mat HogVisualization(const cv::HOGDescriptor& hog, cv::Mat img, std::vector<float>& features, int scaleFactor, double viz_factor, cv::Scalar rectcolor = cv::Scalar(83, 83, 83), cv::ColormapTypes colormap = cv::COLORMAP_JET) {
			cv::Mat visual_image;
			cv::resize(img, visual_image, cv::Size(img.cols*scaleFactor, img.rows*scaleFactor));
			if (visual_image.channels() == 1) cv::cvtColor(visual_image, visual_image, CV_GRAY2BGR);

			int cellsX = hog.winSize.width / hog.cellSize.width;
			int cellsY = hog.winSize.height / hog.cellSize.height;

			int sizes[] = { cellsY ,cellsX,hog.nbins };
			cv::Mat gradientStrengths(3, sizes, CV_32FC1, cv::Scalar(0));
			cv::Mat cellUpdateCounter(cellsY, cellsX, CV_32FC1, cv::Scalar(0));

			for (int blockx = 0, idx = 0; blockx < cellsX - 1; blockx++) {
				for (int blocky = 0; blocky < cellsY - 1; blocky++) {
					cv::Point apt[4] = { { 0,0 },{ 0,1 },{ 1,0 },{ 1,1 } };
					for (int cellNr = 0; cellNr < 4; cellNr++) {
						int cellx = blockx + apt[cellNr].x;
						int celly = blocky + apt[cellNr].y;
						for (int bin = 0; bin < hog.nbins; bin++)
							gradientStrengths.at<float>(celly, cellx, bin) += features[idx++];
						cellUpdateCounter.at<float>(celly, cellx)++;
					}
				}
			}
			for (int y = 0; y < cellsY; y++)
				for (int x = 0; x < cellsX; x++)
					for (int bin = 0; bin < hog.nbins; bin++)
						gradientStrengths.at<float>(y, x, bin) /= cellUpdateCounter.at<float>(y, x);
			cv::Mat heatmap(1, 256, CV_8UC3);
			for (int i = 0; i < 256; i++) {
				heatmap.at<cv::Vec3b>(0, i) = cv::Vec3b(i, i, i);
			}
			cv::applyColorMap(heatmap, heatmap, colormap);

			for (int celly = 0; celly < cellsY; celly++) {
				for (int cellx = 0; cellx < cellsX; cellx++) {
					int drawX = cellx * hog.cellSize.width;
					int drawY = celly * hog.cellSize.height;
					int mx = drawX + hog.cellSize.width / 2;
					int my = drawY + hog.cellSize.height / 2;
					//cv::rectangle(visual_image, cv::Point(drawX*scaleFactor, drawY*scaleFactor), cv::Point((drawX + hog.cellSize.width)*scaleFactor,(drawY + hog.cellSize.height)*scaleFactor), rectcolor,1,CV_AA);
					for (int bin = 0; bin < hog.nbins; bin++) {
						float currentGradStrength = gradientStrengths.at<float>(celly, cellx, bin);
						if (currentGradStrength == 0) continue;
						float currRad = static_cast<float>(bin * (CV_PI / hog.nbins) + (CV_PI / hog.nbins) / 2);
						float dirVecX = cos(currRad);
						float dirVecY = sin(currRad);
						float maxVecLen = hog.cellSize.width / 2.0F;
						float scale = static_cast<float>(viz_factor);
						float x1 = mx - dirVecX * currentGradStrength * maxVecLen * scale;
						float y1 = my - dirVecY * currentGradStrength * maxVecLen * scale;
						float x2 = mx + dirVecX * currentGradStrength * maxVecLen * scale;
						float y2 = my + dirVecY * currentGradStrength * maxVecLen * scale;
						float dist = static_cast<float>(hypot(x1 - x2, y1 - y2) / hypot(hog.cellSize.width, hog.cellSize.height));
						cv::Vec3b color = heatmap.at<cv::Vec3b>(0, static_cast<int>((1 - std::min(dist, 1.0F)) * 255));
						cv::line(visual_image, cv::Point(static_cast<int>(x1*scaleFactor, y1*scaleFactor))
								 , cv::Point(static_cast<int>(x2*scaleFactor, y2*scaleFactor))
								 , cv::Scalar(color[2], color[1], color[0]), 1, CV_AA);
					}
				}
			}
			return visual_image;
		}
	}
};
#endif  //ISPRING_7E2_B_6_VIZ_H_HPP_INCLUDED