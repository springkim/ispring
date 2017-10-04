/**
* @file String.h
* @author kimbomm
* @date 2017. 10. 3...
*
*  @brief Created by kimbom on 2017. 10. 3...\n
*  Copyright 2017 kimbom. All rights reserved.\n
*/
#if !defined(ISPRING_7E1_A_3_STRING_HPP_INCLUDED)
#define ISPRING_7E1_A_3_STRING_HPP_INCLUDED
#include<iostream>
#include<vector>
#include<string>
namespace ispring {
	/**
	*	@breif String : 이 정적 클래스는 문자열을 조작하는 함수를 포함합니다.
	*	@author kimbomm
	*	@date 2017-10-03
	*/
	class String {
	public:
		/**
		*	@breif 문자열을 토큰을 기준으로 분리합니다.
		*	@param std::string str : 입력 문자열
		*	@param std::string token : 토큰
		*	@return 잘려진 문자열들이 std::vector에 담겨서 반환됩니다.
		*	@warning 길이가 0인 문자열은 추가되지 않습니다.
		*	@details 예시 입력 :  ";*.cpp;*.h;*.c;*.jpg;;;;;" \n
				      예시 출력 :  {"*.cpp","*.h","*.c","*.jpg"}
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