/**
* @file		FileSaver.h
* @author		kimbomm (springnode@gmail.com)
* @date		2018. 11. 08...
* @version	1.0.0
*
*  @brief
*			파일 쓰기 라이브러리
*	@remark
*			Created by kimbom on 2018. 11. 08...
*			Copyright 2018 kimbom.All rights reserved.
*/
#if !defined(ISPRING_7E2_B_8_FILESAVER_HPP_INCLUDED)
#define ISPRING_7E2_B_8_FILESAVER_HPP_INCLUDED
#include"../defines.h"
#if defined(ISPRING_WINDOWS) || defined(DOXYGEN)
#include<vector>
#include<string>
#include<algorithm>
#ifndef DOXYGEN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif
#include<Windows.h>
#include<direct.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include"../Verify/VerifyError.h"
#include"../Basic/String.h"
namespace ispring {
	namespace File {
		inline std::string GetNextSequantialName(std::string dir,std::string ext) {
			static std::map<std::string, std::pair<int, int>> cache;
			char _adir[MAX_PATH + 1] = { 0 };
			GetFullPathNameA(dir.c_str(), MAX_PATH, _adir, NULL);
			std::string adir = _adir;
			//[자리수(2)]i[번호(variance)]
			std::pair<int, int> value;
			auto it = cache.find(adir);
			if (it == cache.end()) {
				auto files = FileList(adir, ext);
				if(files.empty()==false)
					files.erase(std::remove_if(files.begin(), files.end(), [](std::string& e)->bool {
						return ispring::String::GetNameOfFile(e)[2] != 'i';
					}));
				std::sort(files.begin(), files.end());
				value.first = files.size() ? std::atoi(files.back().c_str()) : 1;
				value.second = files.size() ? std::atoi(files.back().c_str() + 3) : 0;
				cache.insert(std::make_pair(adir, value));
			} else {
				it->second.second++;
				if (std::to_string(it->second.second).length() > it->second.first) {
					it->second.first++;
				}
				value = it->second;
			}
			std::string::size_type dot = ext.find_last_of('.') ;
			std::string ext2 = dot != std::string::npos ? ext.substr(dot + 1, ext.length() - dot - 1) : ext;
			std::ostringstream oss;
			oss.fill('0');
			oss.width(2);
			oss << value.first << "i" << value.second << "." << ext2;
			if (adir.back() != '/' && adir.back() != '\\')adir.push_back('\\');
			return adir + oss.str();
		}
	}
};
#elif defined(ISPRING_LINUX)
#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
namespace ispring {
	namespace File {

	}
}
#endif
#endif