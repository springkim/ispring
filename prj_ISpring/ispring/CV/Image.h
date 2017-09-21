/*
*  Image
*  ispring
*
*  Created by Kimbom on 2017. 05. 23...
*  Copyright 2017 Sogang CVIP lab. All rights reserved.
*
*/
#if !defined(ISPRING_7E1_05_17_IMAGE_H_INCLUDED)
#define ISPRING_7E1_05_17_IMAGE_H_INCLUDED
#include<opencv2/opencv.hpp>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include<Windows.h>
#include"../Verify.h"
namespace ispring {
	class Image{
	public:
		static cv::Mat Thinning(cv::Mat image) {
			//https://github.com/bsdnoobz/zhang-suen-thinning
			CV_Assert(image.channels() == 1);
			CV_Assert(image.depth() != sizeof(uchar));
			CV_Assert(image.rows > 3 && image.cols > 3);
			cv::Mat ret = image.clone();
			ret /= 255;
			cv::Mat prev_img = cv::Mat::zeros(ret.size(), CV_8UC1);
			cv::Mat marker = cv::Mat::zeros(ret.size(), CV_8UC1);
			cv::Mat diff;
			do {
				for (int iter = 0; iter < 2; iter++) {
					marker.setTo(0);
					int nRows = ret.rows;
					int nCols = ret.cols;
					if (ret.isContinuous() == true) {
						nCols *= nRows;
						nRows = 1;
					}
					int x, y;
					uchar *pAbove;
					uchar *pCurr;
					uchar *pBelow;
					uchar *nw, *no, *ne;    // north (pAbove)
					uchar *we, *me, *ea;
					uchar *sw, *so, *se;    // south (pBelow)
					uchar *pDst;
					pAbove = nullptr;
					pCurr = ret.ptr<uchar>(0);
					pBelow = ret.ptr<uchar>(1);
					for (y = 1; y < ret.rows - 1; ++y) {
						pAbove = pCurr;
						pCurr = pBelow;
						pBelow = ret.ptr<uchar>(y + 1);
						pDst = marker.ptr<uchar>(y);
						no = &(pAbove[0]);
						ne = &(pAbove[1]);
						me = &(pCurr[0]);
						ea = &(pCurr[1]);
						so = &(pBelow[0]);
						se = &(pBelow[1]);
						for (x = 1; x < ret.cols - 1; ++x) {
							nw = no;
							no = ne;
							ne = &(pAbove[x + 1]);
							we = me;
							me = ea;
							ea = &(pCurr[x + 1]);
							sw = so;
							so = se;
							se = &(pBelow[x + 1]);
							int A = (*no == 0 && *ne == 1) + (*ne == 0 && *ea == 1) +
								(*ea == 0 && *se == 1) + (*se == 0 && *so == 1) +
								(*so == 0 && *sw == 1) + (*sw == 0 && *we == 1) +
								(*we == 0 && *nw == 1) + (*nw == 0 && *no == 1);
							int B = *no + *ne + *ea + *se + *so + *sw + *we + *nw;
							int m1 = iter == 0 ? (*no * *ea * *so) : (*no * *ea * *we);
							int m2 = iter == 0 ? (*ea * *so * *we) : (*no * *so * *we);
							if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0)
								pDst[x] = 1;
						}
					}
					ret &= ~marker;
				}
				cv::absdiff(ret, prev_img, diff);
				prev_img = ret.clone();
			} while (cv::countNonZero(diff) > 0);
			ret *= 255;
			for (int y = 1; y < ret.rows - 1; y++) {
				for (int x = 1; x < ret.cols - 1; x++) {
					bool up = ret.at<uchar>(y - 1, x) == 255;
					bool down = ret.at<uchar>(y + 1, x) == 255;
					bool left = ret.at<uchar>(y, x - 1) == 255;
					bool right = ret.at<uchar>(y, x + 1) == 255;
					int c = (up&right) + (up&left) + (down&left) + (down&right);
					if (c==1) {
						ret.at<uchar>(y, x) = 0;
					}
				}
			}
			return ret;
		}
		static cv::Mat AutoCanny(cv::Mat image) {
			cv::Mat gray, edge, dummy;
			if (image.channels() == 3) {
				cv::cvtColor(image, gray, CV_BGR2GRAY);
			}
			else {
				gray = image;
			}
			double high_th = cv::threshold(gray, dummy, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
			double low_th = high_th / 2.;
			cv::Canny(gray, edge, low_th, high_th);
			return edge; 
		}
		static void DisplayImage(cv::Mat image, bool stop = true, bool full = false) {
			cv::Mat rsz;
			cv::Size sz;
			bool op = (image.cols < image.rows);
			double sq = (double)image.cols / image.rows;
			int tmp = GetSystemMetrics(op) / (full ? 1 : 2);
			(op ? sz.height : sz.width) = tmp;
			(op ? sz.width : sz.height) = static_cast<int>(tmp * (op ? sq*sq : 1) / sq);
			cv::resize(image, rsz, sz);
			cv::Mat out;
			rsz.convertTo(out, CV_8UC3);
			cv::imshow("image", out);
			if (stop == true) {
				cv::waitKey();
				cv::destroyAllWindows();
			}
			else {
				if (cv::waitKey(1) == 27) {
					exit(1);
				}
			}
		}
		static void DisplayImage2(cv::Mat image, bool async = false) {
			char _path[MAX_PATH + 1];
			GetTempPathA(MAX_PATH, _path);
			std::string path = _path + std::to_string(clock()) + ".bmp";
			cv::imwrite(path, image);
			if (async) {
				ShellExecuteA(NULL, "open", path.c_str(), NULL, NULL, SW_SHOW);
			} else {
				system(path.c_str());
				DeleteFileA(path.c_str());
			}
		}
		static cv::Mat Zoom(cv::Mat image, double ratio) {
			if (ratio == 1.0F) {
				return image.clone();
			} else if (ratio < 1.0F) {
				cv::Size zsize(static_cast<int>(ratio*image.cols), static_cast<int>(ratio*image.rows));
				cv::Mat zoomed = cv::Mat::zeros(image.size(), CV_8UC3);
				cv::Mat small_img;
				cv::resize(image, small_img, zsize);
				int left_padding = (image.cols - small_img.cols) / 2;
				int top_padding = (image.rows - small_img.rows) / 2;
				small_img.copyTo(zoomed(cv::Rect(left_padding, top_padding, small_img.cols, small_img.rows)));
				return zoomed;
			} else {	//ratio>1.0F
				cv::Size zsize(static_cast<int>(ratio*image.cols), static_cast<int>(ratio*image.rows));
				cv::Mat zoomed = cv::Mat::zeros(image.size(), CV_8UC3);
				cv::Mat large_img;
				cv::resize(image, large_img, zsize);
				int left_margin = (large_img.cols - image.cols) / 2;
				int top_margin = (large_img.rows - image.rows) / 2;
				zoomed = large_img(cv::Rect(left_margin, top_margin, large_img.cols - left_margin * 2, large_img.rows - top_margin * 2));
				return zoomed(cv::Rect(0, 0, image.cols, image.rows));
			}
		}
		static cv::Mat ImageRotateOuter(const cv::Mat image, double degree, cv::Point* out = nullptr) {
			cv::Point2d base(image.cols / 2.0, image.rows / 2.0);
			cv::Mat rot = cv::getRotationMatrix2D(base, degree, 1.0);
			cv::Rect bbox = cv::RotatedRect(base, image.size(),(float) degree).boundingRect();
			rot.at<double>(0, 2) += bbox.width / 2.0 - base.x;
			rot.at<double>(1, 2) += bbox.height / 2.0 - base.y;
			if (out != nullptr) {
				out->x = static_cast<int>(bbox.width / 2.0 - base.x);
				out->y = static_cast<int>( bbox.height / 2.0 - base.y);
			}
			cv::Mat dst;
			cv::warpAffine(image, dst, rot, bbox.size());
			return std::move(dst);
		}
		static cv::Mat ImageRotateInner(const cv::Mat image, double degree, cv::Point2d base=cv::Point2d(-1,-1)) {
			if (base.x == -1 && base.y == -1) {
				base.x = image.cols / 2;
				base.y = image.rows / 2;
			}
			cv::Mat dst = image.clone();
			cv::Mat rot = cv::getRotationMatrix2D(base, degree, 1.0);
			cv::warpAffine(image, dst, rot, image.size());
			return std::move(dst);
		}
		static cv::Mat GlueImage_LR(cv::Mat img1, cv::Mat img2) {
			if (img1.rows != img2.rows) {
				ISPRING_VERIFY("image size is difference");
			}
			cv::Mat _img1, _img2;
			if (img1.channels() == 1) {
				cv::cvtColor(img1, _img1, CV_GRAY2BGR);
			} else {
				_img1 = img1;
			}
			if (img2.channels() == 1) {
				cv::cvtColor(img2, _img2, CV_GRAY2BGR);
			} else {
				_img2 = img2;
			}
			cv::Mat glue;
			cv::hconcat(_img1, _img2, glue);
			return glue;
		}
		static cv::Mat GlueImage_UD(cv::Mat img1, cv::Mat img2) {
			if (img1.cols != img2.cols) {
				ISPRING_VERIFY("image size is difference");
			}
			cv::Mat _img1, _img2;
			if (img1.channels() == 1) {
				cv::cvtColor(img1, _img1, CV_GRAY2BGR);
			} else {
				_img1 = img1;
			}
			if (img2.channels() == 1) {
				cv::cvtColor(img2, _img2, CV_GRAY2BGR);
			} else {
				_img2 = img2;
			}
			cv::Mat glue;
			cv::vconcat(_img1, _img2, glue);
			return glue;
		}
		static cv::Mat GlueImage4(cv::Mat img1, cv::Mat img2, cv::Mat img3, cv::Mat img4) {
			if (img1.size() != img2.size() || img1.size() != img3.size() || img1.size() != img4.size()) {
				ISPRING_VERIFY("image size is difference");
			}
			cv::Mat _img1, _img2, _img3, _img4;
			if (img1.channels() == 1) {
				cv::cvtColor(img1, _img1, CV_GRAY2BGR);
			} else {
				_img1 = img1;
			}
			if (img2.channels() == 1) {
				cv::cvtColor(img2, _img2, CV_GRAY2BGR);
			} else {
				_img2 = img2;
			}
			if (img3.channels() == 1) {
				cv::cvtColor(img3, _img3, CV_GRAY2BGR);
			} else {
				_img3 = img3;
			}
			if (img4.channels() == 1) {
				cv::cvtColor(img4, _img4, CV_GRAY2BGR);
			} else {
				_img4 = img4;
			}
			cv::Mat glue_h1,glue_h2, glue;
			cv::hconcat(_img1, _img2, glue_h1);
			cv::hconcat(_img3, _img4, glue_h2);
			cv::vconcat(glue_h1, glue_h2, glue);
			return glue;
		}
	};
}
#endif