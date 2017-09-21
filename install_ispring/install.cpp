#ifdef _WIN64
#error support only x86
#endif
#ifdef _DEBUG
//#error support only release
#endif
/*
*  install.cpp
*  ispring
*
*  Created by kimbom on 2017. 9. 21...
*  Copyright 2017 kimbom. All rights reserved.
*
*/
#include<iostream>
#include<string>
#include<urlmon.h>            //URLDownloadToFileA
#include<vector>
#include<Windows.h>
#pragma comment(lib,"urlmon.lib")
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include<sstream>
#include"../prj_ISpring/ispring/Compression.h"
#include"../prj_ISpring/ispring/File.h"
#include"../prj_ISpring/ispring/Console.h"
#include<WinInet.h>
#pragma comment(lib, "wininet.lib")


std::string GetHtml(std::string url) {
	std::string html;
	HINTERNET hInternet = InternetOpen(TEXT("HTTP"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);	//인터넷 관련 DLL을 초기화한다.
	if (hInternet) {
		HINTERNET hUrl = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);	//url에 걸린 파일을 연다.
		if (hUrl) {
			DWORD realSize = 0;
			DWORD possibleSize = 0;
			DWORD recv = 0;
			char* buffer = new char[2000000];
			char* tempBuffer = new char[2000000];
			memset(buffer, 0, 2000000 * sizeof(char));
			memset(tempBuffer, 0, 2000000 * sizeof(char));
			do {
				InternetQueryDataAvailable(hUrl, &possibleSize, 0, 0);
				InternetReadFile(hUrl, buffer, possibleSize, &realSize);
				if (possibleSize>0) {
					memcpy(tempBuffer + recv, buffer, possibleSize * sizeof(char));
				}
				recv += possibleSize;
			} while (realSize != 0);
			html.resize(realSize);
			html = tempBuffer;
			delete[] buffer;
			delete[] tempBuffer;
		}
	}
	return html;
}
std::string GetNewVersion() {
	std::string url_git = "https://github.com/springkim/ISpring/blob/master/prj_ISpring/ispring/version_info.txt";
	std::string html = GetHtml(url_git);
	std::string tag_begin = "&lt;ispring-version&gt;";
	std::string tag_end = "&lt;/ispring-version&gt;";
	size_t pos_beg = html.find(tag_begin) + tag_begin.length();
	size_t pos_end = html.find(tag_end);
	std::string version = html.substr(pos_beg, pos_end - pos_beg);
	if (version.length() == 0) {
		version = "Can't load new version information";
	}
	return version;
}
std::string GetCurrentVersion() {
	std::ifstream fin;
	std::string version = "Not installed";
	if (ispring::File::DirectoryExist("ispring")) {
		std::ifstream fin;
		fin.open("ispring/version_info.txt");
		if (fin.is_open() == true) {
			std::string str;
			str.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
			std::string tag_begin = "<ispring-version>";
			std::string tag_end = "</ispring-version>";
			size_t pos_beg = str.find(tag_begin) + tag_begin.length();
			size_t pos_end = str.find(tag_end);
			version = str.substr(pos_beg, pos_end - pos_beg);
		}
	}
	return version;
}

void Fail(std::string str) {
	std::cerr << str << std::endl;
	system("pause");
	exit(EXIT_FAILURE);
}

int main() {
	std::string curr_version = GetCurrentVersion();
	std::string new_version = GetNewVersion();

	std::cout << ispring::xout.light_red << "Current version : " << curr_version << std::endl;
	std::cout << ispring::xout.light_green <<"New version : " << new_version << std::endl;
	if (curr_version != new_version) {
		std::cout << ispring::xout.light_white;
		char _temp[MAX_PATH];
		GetTempPathA(MAX_PATH - 1, _temp);
		std::string temp = _temp;

		std::string file = temp + "ISpring.zip";
		std::cout << "Downloading ISpring lastest version..." << std::endl;

		if (ispring::File::DirectoryExist(file) == true) {
			DeleteFileA("MSpring.zip");
		}
		HRESULT r = URLDownloadToFileA(nullptr, "https://github.com/springkim/ISpring_repo/archive/master.zip", file.c_str(), 0, 0);
		if (r != S_OK) {
			Fail("File download fail!!");
		}
		std::cout << "installing ISpring..." << std::endl;
		ispring::Zip::Uncompress(file.c_str());
		ispring::File::DirectoryCopy(temp + "ISpring/ISpring_repo-master/ispring", "./ispring/");
		ispring::File::DirectoryErase(temp+"ISpring");
		ispring::File::FileErase(file);
		std::cout << "Successfully updated!!" << std::endl;
	} else {
		std::cout << "already installed!" << std::endl;
	}
	system("pause");
	return 0;
}