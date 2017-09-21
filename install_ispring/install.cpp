#ifdef _WIN64
#error support only x86
#endif
#ifdef _DEBUG
#error support only release
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

void Fail(std::string str) {
	std::cerr << str << std::endl;
	system("pause");
	exit(EXIT_FAILURE);
}
int main() {
	char _temp[MAX_PATH];
	GetTempPathA(MAX_PATH - 1, _temp);
	std::string temp = _temp;

	std::string file = temp + "MSpring.zip";
	std::cout << "Downloading MSpring lastest version..." << std::endl;
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
	std::cout << "Successfully updated" << std::endl;
	return 0;
}