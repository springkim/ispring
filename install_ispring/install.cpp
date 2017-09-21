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

#include<WinInet.h>
#pragma comment(lib, "wininet.lib")

std::string url_gist = "https://gist.github.com/springkim/8429bb12102fc14cdd58cc11ee7bd273";


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
void Fail(std::string str) {
	std::cerr << str << std::endl;
	system("pause");
	exit(EXIT_FAILURE);
}

int main() {
	std::string html=GetHtml(url_gist);
	std::string tag_begin = "&lt;ispring-version&gt;";
	std::string tag_end= "&lt;/ispring-version&gt;";
	size_t pos_beg = html.find(tag_begin) + tag_begin.length();
	size_t pos_end = html.find(tag_end);
	std::string version = html.substr(pos_beg, pos_end-pos_beg);
	std::cout << version << std::endl;
	/*char _temp[MAX_PATH];
	GetTempPathA(MAX_PATH - 1, _temp);
	std::string temp = _temp;

	std::string file = temp + "ISpring.zip";
	std::cout << "Downloading ISpring lastest version..." << std::endl;
	if (PathFileExistsA(file.c_str()) == TRUE) {
		std::cout << "Remove current version..." << std::endl;
		DeleteFileA("MSpring.zip");
	}
	HRESULT r = URLDownloadToFileA(nullptr, "https://github.com/springkim/MSpring_repo/archive/master.zip", file.c_str(), 0, 0);
	if (r != S_OK) {
		Fail("File download fail!!");
	}
	std::cout << "installing MSpring..." << std::endl;
	ispring::Zip::Uncompress(file.c_str());
	std::string src = file.substr(0, file.find_last_of('.')) + "\\MSpring_repo-master";

	if (CopyFolder(src, ".\\") == FALSE) {
		Fail("Move file fail");
	}
	std::cout << "Successfully updated" << std::endl;*/
	return 0;
}