/**
* @file		7zext.h
* @author	kimbomm (springnode@gmail.com)
* @date		2020. 03. 05...
* @version	1.0.0
*
*  @brief
*			7z를 이용한 압축, 압축 해제 라이브러리
*	@remark
*			Created by kimbom on 2020. 03. 05...
*			Copyright 2020 kimbom.All rights reserved.
*/
#include<atomic>
#include<string>
#include<fstream>
#include<vector>
#include"../Verify/VerifyError.h"
#include"../defines.h"
#include"../Basic/String.h"
#if defined(ISPRING_WINDOWS)
#include<Windows.h>
#include<urlmon.h> //URLDownloadToFileA
#include<Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "urlmon.lib")
#elif defined(ISPRING_LINUX)


#endif
namespace ispring {
	namespace Zip{
		inline std::string check7z() {
#if defined(ISPRING_WINDOWS)
			std::string path;
			char c_temp_path[MAX_PATH + 1];
			GetTempPathA(MAX_PATH, c_temp_path);
			std::string temp_path = c_temp_path;
			std::string exe[2] = { temp_path + "7z.exe", temp_path + "7z.dll" };
			int filesize[2] = {455168,1656832 };
			std::string url[2] = {"7z.exe","7z.dll"};
			for (int i = 0; i < 2; i++) {
				std::ifstream fin(exe[i], std::ifstream::ate | std::ifstream::binary);
				int result = 1;
				if (PathFileExistsA(exe[i].c_str()) == FALSE || static_cast<int>(fin.tellg()) != filesize[i])
					result = (URLDownloadToFileA(nullptr,
						std::string("https://github.com/springkim/ispring/releases/download/bin/"+url[i]).c_str(),
						exe[i].c_str(), 0, 0) == S_OK);
			}
			return exe[0];
#elif defined(ISPRING_LINUX)
			return "7z";
#endif
		}
		/**
		*	@brief 폴더를 압축 합니다.
		*	@param folder 압축할 폴더의 경로
		*	@param _password 압축 파일에 설정할 비밀번호. (기본값은 비밀번호 없음)
		*	@param progress 압축의 진행 상황을 외부에서 알아올 수 있음.
		*	@return void
		*	@warning 이 압축 함수는 Bandizip의 기본 포맷을 따릅니다. 폴더를 압축하는 경우 폴더는 압축에 포함하지 않습니다.
		*	@remark
		*	@code{.cpp}
		*		puts("make zip_test folder...");
		*		_mkdir("zip_test");
		*		for (int i = 0; i < 100; i++) {
		*		std::ofstream fout("zip_test/" + std::to_string(i) + ".txt");
		*		for (int j = 0; j < 10000; j++) {
		*		fout << i << "\t" << j << std::endl;
		*		}
		*		fout.close();
		*		}
		*		puts("zip test...");
		*		ispring::Zip::Compress("zip_test");
		*		puts("unzip test...");
		*		ispring::File::DeleteDirectory("zip_test");
		*		ispring::Zip::Uncompress("zip_test.zip");
		*		ispring::File::DeleteDirectory("zip_test");
		*		DeleteFileA("zip_test.zip");
		*	@endcode
		*/
		inline void Compress(std::string folder, std::string _password = "", std::atomic<int>* progress = nullptr) {
			std::string _7z=check7z();
			//7z a -tzip img.zip .\img\*
			std::string cmd = "\""+_7z + "\"" + " a -tzip " + folder + ".zip .\\" + folder + "\\* ";
			if (_password == "")
				cmd += ">NUL 2>&1";
			else
				cmd += "-p" + _password;
			system(cmd.c_str());
		}
		/**
		*	@brief 파일들을 압축 합니다.
		*	@param zip_name 압축 파일의 이름
		*	@param files 압축될 파일의 경로들
		*	@param _password 압축 파일에 설정할 비밀번호. (기본값은 비밀번호 없음)
		*	@param progress 압축의 진행 상황을 외부에서 알아올 수 있음.
		*	@return void
		*/
		inline void Compress(std::string zip_name, std::vector<std::string> files, std::string _password = "", std::atomic<int>* progress = nullptr) {
			ISPRING_VERIFY("Not Implemented");
		}
		/**
		*	@brief 압축을 해제 합니다.
		*	@param file 해제할 압축 파일의 이름
		*	@param _password 압축해제에 필요한 비밀번호
		*	@param progress 압축해제의 진행 상황을 외부에서 알아올 수 있음.
		*	@return void
		*/
		inline void Uncompress(std::string file, std::string _password = "", std::atomic<int>* progress = nullptr) {
			std::string _7z = check7z();
			std::string dir=file.substr(0,file.find_last_of("."));
			std::string cmd = "\"" + _7z + "\"" + " x " + file + " -o" + dir + " ";
			if (_password == "")
				cmd += ">NUL 2>&1";
			else
				cmd += "-p" + _password;
			system(cmd.c_str());
		}
	};
}

