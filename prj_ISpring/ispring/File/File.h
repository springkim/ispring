/*
*  File
*  ispring
*
*  Created by Kimbom on 2017. 05. 23...
*  Copyright 2017 kimbom. All rights reserved.
*
*/
#if !defined(ISPRING_7E1_05_17_FILE_H_INCLUDED)
#define ISPRING_7E1_05_17_FILE_H_INCLUDED
#include<vector>
#include<string>
#include<algorithm>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include<Windows.h>
#include<direct.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include"../Verify.h"
namespace ispring {
	class File {
	public:
		static std::vector<std::string> FileList(std::string dir_path, std::string ext, bool recursive = false) {
			std::vector<std::string> paths; //return value
			if (dir_path.back() != '/' && dir_path.back() != '\\') {
				dir_path.push_back('/');
			}
			std::string str_exp = dir_path + "*.*";
			std::vector<std::string> allow_ext;
			std::string::size_type offset = 0;
			while (offset < ext.length()) {
				std::string str = ext.substr(offset, ext.find(';', offset) - offset);
				std::transform(str.begin(), str.end(), str.begin(), toupper);
				offset += str.length() + 1;
				std::string::size_type pos = str.find_last_of('.');
				pos = pos == std::string::npos ? 0 : pos + 1;
				allow_ext.push_back(str.substr(pos, str.length()));
			}
			WIN32_FIND_DATAA fd;
			HANDLE hFind = ::FindFirstFileA(str_exp.c_str(), &fd);
			if (hFind == INVALID_HANDLE_VALUE) {
				return paths;
			}
			do {
				std::string path = fd.cFileName;
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) { //if this is file
					std::string path_ext = path.substr(path.find_last_of('.') + 1, path.length());  //파일의 확장자 추출
					std::transform(path_ext.begin(), path_ext.end(), path_ext.begin(), toupper);
					int i = -1;
					while (++i < (int)allow_ext.size() && allow_ext[i] != path_ext);
					if (i < (int)allow_ext.size() || allow_ext.front() == "*") {    //allow_ext에 포함되어있으면
						paths.push_back(dir_path + path);
					}
				}
				else if (recursive == true && path != "." && path != "..") {
					std::vector<std::string> temps = FileList(dir_path + path, ext, recursive);
					for (auto&temp : temps) {
						paths.push_back(temp);
					}
				}
			} while (::FindNextFileA(hFind, &fd));
			::FindClose(hFind);
			return paths;   //RVO
		}
		static bool FileExist(std::string file) {
			return PathFileExistsA(file.c_str()) == TRUE;
		}
		static bool FileErase(std::string file) {
			return DeleteFileA(file.c_str()) == TRUE;
		}
		static bool FileCopy(std::string src, std::string dst) {
			return CopyFileA(src.c_str(), dst.c_str(), FALSE) == TRUE;
		}
		static bool DirectoryErase(std::string dir_path, bool noRecycleBin = true) {
			char *pszFrom = new char[dir_path.length() + 2];
#ifdef _MSC_VER
			strcpy_s(pszFrom, dir_path.length() + 2, dir_path.c_str());
#elif __GNUC__
			strcpy(pszFrom, dir_path.c_str());
#endif
			pszFrom[dir_path.length()] = '\0';       // double-null termination
			pszFrom[dir_path.length() + 1] = '\0';   // double-null termination
			SHFILEOPSTRUCTA	FileOp;
			FileOp.hwnd = NULL;
			FileOp.wFunc = FO_DELETE;
			FileOp.pFrom = pszFrom;
			FileOp.pTo = NULL;
			FileOp.fFlags = FOF_NOCONFIRMATION | FOF_SILENT;
			if (noRecycleBin == false) {
				FileOp.fFlags |= FOF_ALLOWUNDO;
			}
			FileOp.fAnyOperationsAborted = FALSE;
			FileOp.lpszProgressTitle = NULL;
			FileOp.hNameMappings = NULL;
			int ret = SHFileOperationA(&FileOp);
			delete[] pszFrom;
			return (ret == 0);
		}
		
		static bool DirectoryCopy(std::string src, std::string dst) {
			std::string new_sf = src + "\\*";
			char sf[MAX_PATH + 1];
			char tf[MAX_PATH + 1];
#ifdef _MSC_VER
			strcpy_s(sf, MAX_PATH, new_sf.c_str());
			strcpy_s(tf, MAX_PATH, dst.c_str());
#elif __GNUC__
			strcpy(sf,  new_sf.c_str());
			strcpy(tf, dst.c_str());
#endif
			sf[strlen(sf) + 1] = 0;
			tf[strlen(tf) + 1] = 0;
			SHFILEOPSTRUCTA s = { 0 };
			s.wFunc = FO_COPY;
			s.pTo = tf;
			s.pFrom = sf;
			s.fFlags = FOF_SILENT | FOF_NOCONFIRMMKDIR | FOF_NOCONFIRMATION | FOF_NOERRORUI;
			int res = SHFileOperationA(&s);
			return res == 0;
		}
		static bool DirectoryMake(std::string dir) {
			int r=_mkdir(dir.c_str());;
			if (r == ENOENT) {
				ISPRING_VERIFY("Path was not found.");
			}
			return r == 0;
		}
		static bool DirectoryExist(std::string dir) {
			DWORD ftyp = GetFileAttributesA(dir.c_str());
			return ftyp == FILE_ATTRIBUTE_DIRECTORY;
		}
		
	};
};
#endif
