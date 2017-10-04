/*
*  String.h
*  ispring
*
*  Created by kimbom on 2017. 10. 3...
*  Copyright 2017 kimbom. All rights reserved.
*
*/
#if !defined(ISPRING_7E1_A_3_STRING_HPP_INCLUDED)
#define ISPRING_7E1_A_3_STRING_HPP_INCLUDED
#include<iostream>
#include<vector>
#include<string>
namespace ispring {
	/**
	*	@class String : Provides string manipulation function.
	*	@author kimbomm
	*	@date 2017-10-03
	*/
	class String {
	public:
		/**
		*	@breif Split string by token
		*	@param std::string str : source string
		*	@param std::string token : token
		*	@return Divided words
		*	@warnings Remove 0-length string automatically
		*	@detail ( ";*.cpp;*.h;*.c;*.jpg;;;;;") -> ([*.cpp],[*.h],[*.c],[*.jpg])
		*/
		static std::vector<std::string> Tokenizer(std::string str, std::string token) {
			std::vector<std::string> ret;
			std::string::size_type offset = 0;
			while (offset < str.length()) {
				std::string word = str.substr(offset, str.find(token, offset) - offset);
				offset += word.length() + 1;
				if (word.length() > 0) {
					ret.push_back(word);
				}
			}
			return ret;
		}
		static std::string GetExtOfFile(std::string path) {
			std::string::size_type dot = path.find_last_of('.');
			if (dot == std::string::npos) {
				return "";
			}
			std::string ext = path.substr(dot+1, path.length() - dot-1);
			return ext;
		}
		static std::string GetNameOfFile(std::string path) {
			std::string::size_type slash = path.find_last_of("/\\");
			if (slash == std::string::npos) {
				slash = -1;
			}
			std::string name = path.substr(slash + 1, path.length() - slash - 1);
			return name;
		}
		static std::string GetPureNameOfFile(std::string path) {
			std::string::size_type slash = path.find_last_of("/\\");
			if (slash == std::string::npos) {
				slash = -1;
			}
			std::string::size_type dot = path.find_last_of(".");
			if (dot == std::string::npos) {
				dot = path.length();
			}
			std::string pure = path.substr(slash+1, dot - slash-1);
			return pure;
		}
		static std::string PadNum(unsigned int num,unsigned int pad) {
			std::ostringstream oss;
			oss.width(pad);
			oss.fill('0');
			oss << num;
			return oss.str();
		}
	};
}
#endif  //ISPRING_7E1_A_3_STRING_HPP_INCLUDED