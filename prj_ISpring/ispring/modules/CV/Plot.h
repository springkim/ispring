/**
* @file		Plot.h
* @author		kimbomm (springnode@gmail.com)
* @date		2017. 12. 16...
* @version	1.0.0
*
*  @brief
*			Plot 라이브러리
*	@remark
*			Created by kimbom on 2017. 12. 16...
*			Copyright 2017 kimbom.All rights reserved.
*/
#if !defined(ISPRING_7E1_C_F_PLOT_HPP_INCLUDED)
#define ISPRING_7E1_C_F_PLOT_HPP_INCLUDED
#include<iostream>
#include<vector>
#include<iomanip>
#include<opencv2/opencv.hpp>

namespace ispring {
	/**
	*	@brief 이 구조체는 Plot 클래스의 데이터를 표현하기 위해 사용됩니다.
	*	@author kimbomm
	*	@date 2017-12-16
	*/
	struct PlotElement {
		cv::Scalar m_color;					/*그래프의 선 색 입니다.*/
		std::string m_name;					/*그래프의 이름 입니다.*/
		std::vector<cv::Point2d> m_data;	/*그래프의 2차원 이산 데이터들 입니다.*/
	};
	/**
	*	@brief 이 클래스는 2차원 이산 데이터들을 그래프로 그려 줍니다.
	*	@author kimbomm
	*	@date 2017-12-16
	*/
	class Plot {
		cv::Size m_size;							/*그래프(cv::Mat) 의 크기를 지정 합니다.*/
		std::vector<PlotElement> m_elem;		/*PlotElement들을 저장합니다.*/
		size_t m_maxinfo = 11;					/* x,y 축에 표시할 정보의 개수를 나타냅니다.*/
		size_t m_thickness = 1;					/*그래프의 두께를 지정 합니다.*/
		bool b_graph_only = false;				/*그래프 만을 표시할지 지정 합니다.*/
		cv::Scalar m_text_color;					/*텍스트의 색상을 지정 합니다.*/
		cv::Scalar m_bg_color;					/*그래프의 배경색을 지정 합니다.*/
	public:
		Plot() {
			m_size.width = 640;
			m_size.height = 320;
			m_text_color = cv::Scalar(0, 0, 0);
			m_bg_color = cv::Scalar(255, 255, 255);
		}
	public:
		/**
		*	@brief 그래프의 x,y 축에 표기할 정보의 최대 개수를 지정 합니다.
		*	@param info 최대 축 정보 개수
		*	@warning 그래프의 크기가 작을 경우, 모든 정보가 표기되지 않을 수 도 있습니다.
		*/
		void SetMaxInfo(size_t info) {
			m_maxinfo = info;
		}
		/**
		*	@brief 그래프 선의 두께를 지정 합니다.
		*	@param thickness 그래프 선의 두께
		*/
		void SetThickness(size_t thickness) {
			m_thickness = thickness;
		}
		/**
		*	@brief 그래프만 출력할지를 지정 합니다.
		*	@param b 참이면 그래프만 출력, 거짓이면 그래프와 부가정보를 같이 출력.
		*/
		void ShowGraphOnly(bool b) {
			b_graph_only = b;
		}
		/**
		*	@brief 글자색을 지정 합니다. 기본 값은 검정색 입니다.
		*	@param color 글자색
		*/
		void SetTextColor(cv::Scalar color) {
			m_text_color = color;
		}
		/**
		*	@brief 배경색을 지정 합니다. 기본 값은 흰색 입니다.
		*	@param color 배경색
		*/
		void SetBGColor(cv::Scalar color) {
			m_bg_color = color;
		}
		/**
		*	@brief 그래프의 실제 크기를 지정합니다.
		*	@param w 가로길이
		*	@param h 세로길이
		*/
		void SetSize(int w, int h) {
			m_size.width = w;
			m_size.height = h;
		}
		/**
		*	@brief 실제 그려질 데이터를 추가 합니다.
		*	@param elem 그려질 그래프 데이터
		*/
		void Add(PlotElement elem) {
			m_elem.push_back(elem);
		}
		/**
		*	@brief 모든 그래프 데이터를 삭제합니다.
		*/
		void Clear() {
			m_elem.clear();
		}
		/**
		*	@brief 그래프를 그립니다.
		*	@return 그려진 그래프 이미지.
		*	@details 부가적인 정보를 포함할경우 W와 H는 200씩 더 커지게 됩니다.
		*/
		cv::Mat Draw() {
			int fontface = cv::FONT_HERSHEY_COMPLEX;
			double fontscale = 0.5;
			cv::Scalar fontcolor = m_text_color;
			int fontthickness = 1;

			cv::Mat info = cv::Mat::zeros(cv::Size(m_size.width + 100 + 100, m_size.height + 100 + 100), CV_8UC3) + m_bg_color;
			cv::Mat plot = info(cv::Rect(100, 100, m_size.width, m_size.height));
			cv::Mat x_info = info(cv::Rect(0, m_size.height + 100, m_size.width + 200, 100));
			cv::Mat y_info = info(cv::Rect(0, 0, 100, m_size.height + 200));
			cv::Mat title = info(cv::Rect(100, 0, m_size.width + 100, 100));
			auto xcmp = [](cv::Point2d first, cv::Point2d found)->bool {return first.x < found.x; };
			auto ycmp = [](cv::Point2d first, cv::Point2d found)->bool {return first.y < found.y; };
			double x_min = std::numeric_limits<double>::max();
			double x_max = std::numeric_limits<double>::min();
			double y_min = std::numeric_limits<double>::max();
			double y_max = std::numeric_limits<double>::min();
			for (size_t i = 0; i < m_elem.size(); i++) {
				x_min = std::min(x_min, std::min_element(m_elem[i].m_data.begin(), m_elem[i].m_data.end(), xcmp)->x);
				x_max = std::max(x_max, std::max_element(m_elem[i].m_data.begin(), m_elem[i].m_data.end(), xcmp)->x);
				y_min = std::min(y_min, std::min_element(m_elem[i].m_data.begin(), m_elem[i].m_data.end(), ycmp)->y);
				y_max = std::max(y_max, std::max_element(m_elem[i].m_data.begin(), m_elem[i].m_data.end(), ycmp)->y);
			}

			std::vector<double> vx, vy;
			for (auto&elem : m_elem) {
				for (auto&data : elem.m_data) {
					vx.push_back(data.x);
					vy.push_back(data.y);
				}
			}
			std::sort(vx.begin(), vx.end());
			std::sort(vy.begin(), vy.end());
			int baseline = 0;
			cv::Size sz = cv::getTextSize("0000000000", fontface, fontscale, fontthickness, &baseline);
			int x_numOfInfo = m_maxinfo;
			if (sz.width*x_numOfInfo > m_size.width) {
				x_numOfInfo = m_size.width / sz.width;
			}
			//Draw x
			cv::line(x_info, cv::Point(100, 0), cv::Point(x_info.cols - 100, 0), fontcolor, 1);
			for (int i = 0; i < x_numOfInfo; i++) {
				int idx = (vx.size() - 1)*i / (x_numOfInfo - 1);
				int beg_pt = (x_info.cols - 1 - 200)*idx / (vx.size() - 1);

				std::ostringstream oss;
				oss << std::setprecision(5) << vx[idx];
				int baseline = 0;
				cv::Size sz = cv::getTextSize(oss.str(), fontface, fontscale, fontthickness, &baseline);
				cv::putText(x_info, oss.str(), cv::Point(100 + beg_pt - sz.width / 2, 50 - sz.height / 2), fontface, fontscale, fontcolor, fontthickness);
			}
			//Draw y
			int y_numOfInfo = m_maxinfo;
			if (sz.height*y_numOfInfo > m_size.height) {
				y_numOfInfo = m_size.height / sz.height;
			}
			cv::line(y_info, cv::Point(100 - 1, 100 - 1), cv::Point(100 - 1, y_info.rows - 100 - 1), fontcolor, 1);
			for (int i = 0; i < y_numOfInfo; i++) {
				int idx = (vy.size() - 1)*i / (y_numOfInfo - 1);
				int beg_pt = (y_info.rows - 1 - 100) - ((y_info.rows - 1 - 200)*idx / (vy.size() - 1));
				std::ostringstream oss;
				oss << std::setprecision(5) << vy[idx];
				int baseline = 0;
				cv::Size sz = cv::getTextSize(oss.str(), fontface, fontscale, fontthickness, &baseline);
				cv::putText(y_info, oss.str(), cv::Point(50 - sz.width / 2, beg_pt + sz.height / 2), fontface, fontscale, fontcolor, fontthickness);
			}
			//Draw graph
			int pos = 0;
			for (int i = 0; i < m_elem.size(); i++) {
				auto& data = m_elem[i].m_data;
				cv::Scalar& color = m_elem[i].m_color;

				cv::Size sz = cv::getTextSize(m_elem[i].m_name, fontface, fontscale, fontthickness, &baseline);
				cv::putText(title, m_elem[i].m_name, cv::Point(pos, 35), fontface, fontscale, fontcolor, fontthickness);
				cv::line(title, cv::Point(pos, 65), cv::Point(pos + sz.width, 65), color, m_thickness + 1);
				pos += sz.width + 50;

				std::vector<cv::Point2d> graph;
				for (size_t j = 0; j < data.size(); j++) {
					cv::Point2d rpt;
					rpt.x = (data[j].x - x_min) / (x_max - x_min)*(plot.cols - 1);
					rpt.y = plot.rows - ((data[j].y - y_min) / (y_max - y_min)*(plot.rows - 1));
					//cv::circle(plot, rpt, 3, cv::Scalar(0, 0, 255));
					graph.push_back(rpt);
				}
				for (size_t j = 0; j < graph.size() - 1; j++) {
					cv::line(plot, graph[j], graph[j + 1], color, m_thickness);
				}
			}
			return info;
		}
	};
};
#endif  //ISPRING_7E1_C_F_PLOT_HPP_INCLUDED