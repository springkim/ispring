/*
*  Timer.h
*  ispring
*
*  Created by Kimbom on 2017. 05. 23...
*  Copyright 2017 kimbom. All rights reserved.
*
*/
#if !defined(ISPRING_7E1_05_18_TIME_H_INCLUDED)
#define ISPRING_7E1_05_18_TIME_H_INCLUDED
#include<iostream>
#include<vector>
#include<string>
#include<deque>
#include<algorithm>
#include<utility>
#include<ctime>
#include<cstring>
#include<cstdio>
#include<chrono>
#include<typeinfo>
#include<cmath>
#pragma warning(disable:4290)

#include"../Verify.h"
#define INTERVALTIME_ERROR_MSG(MSG)	ISPRING_VERIFY(MSG)

namespace ispring {
	///support types = char, int ,double ,std::string
	using _TimerType = std::chrono::system_clock::time_point;
	using _TimerCount = long long;
	
	class Timer {
		class TimerElement {
		public:
			TimerElement() {
				curr = 0.0;
				avg = 0.0;
				accu = 0.0;
			}
			double curr;
			double avg;
			double accu;
		};
		class GenericType {
			friend class Timer;
		private:
			int idx = -1;
			char _1;
			int _2;
			double _3;
			std::string _4;

			template<typename T>
			void SetObject(T param) {
				if (typeid(this->_1).hash_code() == typeid(param).hash_code()) {
					this->idx = 1;
					memcpy(&this->_1, &param, sizeof(char));
				} else if (typeid(this->_2).hash_code() == typeid(param).hash_code()) {
					this->idx = 2;
					memcpy(&this->_2, &param, sizeof(int));
				} else if (typeid(this->_3).hash_code() == typeid(param).hash_code()) {
					this->idx = 3;
					memcpy(&this->_3, &param, sizeof(double));
				} else if (typeid(char*).hash_code() == typeid(param).hash_code()
						   || typeid(const char*).hash_code() == typeid(param).hash_code()
						   || typeid(std::string).hash_code() == typeid(param).hash_code()
						   ) {
					this->idx = 4;
					char* tmp;
					memcpy(&tmp, &param, sizeof(char*));
					this->_4 = tmp;
				}
			}
		public:
			bool operator==(GenericType& other)const {
				if (this->idx != other.idx) {
					return false;
				} else {
					bool ret = false;
					switch (this->idx) {
						case 1:ret = this->_1 == other._1; break;
						case 2:ret = this->_2 == other._2; break;
						case 3:ret = fabs(this->_3 - other._3) < 0.0001; break;
						case 4:ret = this->_4 == other._4; break;
						default:break;
					}
					return ret;
				}
			}

		};
	private:
		Timer() = delete;
		~Timer() = delete;
	protected:
		static std::vector<GenericType> mapped;
		static std::vector<std::pair<double, _TimerCount>> accumulated;
		static std::vector<_TimerType> temp;
		static std::deque<GenericType> stk;
		template<typename CONTAINER>
		static intptr_t GetPosInContainer(CONTAINER container, const GenericType& pts) {
			intptr_t idx = -1;
			while ((idx++) + 1 < (intptr_t)container.size()) {
				if (pts == container[idx] == true) {
					break;
				}
			}
			if (idx != -1 && idx < (intptr_t)container.size()) {
				return idx;
			} else {
				return -1;
			}
		}
	public:
		template<typename T>
		static void Tick(T param) {
			using GENERIC_TYPE = typename std::enable_if<
				std::is_same<char, T>::value
				|| std::is_same<int, T>::value
				|| std::is_same<float, T>::value
				|| std::is_same<double, T>::value
				|| std::is_same<char*, T>::value
				|| std::is_same<const char*, T>::value
				|| std::is_same<std::string, T>::value
				, T>::type;
			GenericType pts;
			pts.SetObject(param);

			intptr_t stkidx = Timer::GetPosInContainer(Timer::stk, pts);
			if (stkidx != -1) {	//exist
				INTERVALTIME_ERROR_MSG("Startclock and endclock is not matched");
			}
			stk.push_back(pts);

			intptr_t idx = Timer::GetPosInContainer(Timer::mapped, pts);
			if (idx != -1) {
				Timer::temp[idx] = std::chrono::system_clock::now();
			} else {				
				//new parameter
				Timer::temp.push_back(std::chrono::system_clock::now());
				Timer::mapped.push_back(pts);
				accumulated.push_back(std::make_pair(0.0, 0));
			}
		}
		template<typename T>
		static Timer::TimerElement Tock(T param) {
			using GENERIC_TYPE = typename std::enable_if<
				std::is_same<char, T>::value
				|| std::is_same<int, T>::value
				|| std::is_same<float, T>::value
				|| std::is_same<double, T>::value
				|| std::is_same<char*, T>::value
				|| std::is_same<const char*, T>::value
				|| std::is_same<std::string, T>::value
				, T>::type;
			GenericType pts;
			pts.SetObject(param);
			intptr_t stkidx = Timer::GetPosInContainer(Timer::stk, pts);
			if (stkidx == -1) {	//exist
				INTERVALTIME_ERROR_MSG("There is no Tick of this object");
			}
			intptr_t depth = stkidx;
			Timer::stk.erase(Timer::stk.begin() + stkidx);
			intptr_t idx = Timer::GetPosInContainer(Timer::mapped, pts);
			Timer::TimerElement tm;

			if (idx != -1) {
				tm.curr = static_cast<std::chrono::duration<double>>(std::chrono::system_clock::now() - Timer::temp[idx]).count();
				accumulated[idx].first += tm.curr;
				accumulated[idx].second++;
				tm.accu = accumulated[idx].first;
				tm.avg = tm.accu / accumulated[idx].second;
			} else {
				INTERVALTIME_ERROR_MSG("No matched begin entry point");
			}
			return tm;
		}
	};
#ifdef _WIN32
	__declspec(selectany) std::vector<Timer::GenericType> Timer::mapped;
	__declspec(selectany) std::vector<_TimerType> Timer::temp;
	__declspec(selectany) std::deque<Timer::GenericType> Timer::stk;
	__declspec(selectany) std::vector<std::pair<double, _TimerCount>> Timer::accumulated;
#elif defined(__linux__)
	__attribute__((weak) std::vector<Timer::GenericType> Timer::mapped;
	__attribute__((weak) std::vector<_TimerType> Timer::temp;
	__attribute__((weak) std::deque<Timer::GenericType> Timer::stk;
	__attribute__((weak) std::vector<std::pair<double, _TimerCount>> Timer::accumulated;
#endif
}
#endif