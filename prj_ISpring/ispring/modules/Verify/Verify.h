/*
*  Verify
*  ISpring
*
*  Created by Kimbom on 2017. 05. 25...
*  Copyright 2017 Sogang CVIP lab. All rights reserved.
*
*/
#if !defined(ISPRING_7E1_05_19_VERIFY_H_INCLUDED)
#define ISPRING_7E1_05_19_VERIFY_H_INCLUDED
#include<string>
#include<sstream>
#include<fstream>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include<Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

#define ISPRING_VERIFY(MSG)	__VerifyError(MSG,__FILE__,__FUNCTION__,__LINE__)
inline void __VerifyError(std::string msg, const char* __file__,const char* __function__, int __line__) {
	std::ostringstream oss;
	oss << "Verify Error : (" << msg << ") in " << __function__ << " , " << __file__ << " , line" << __line__ << std::endl;
	if (MessageBoxA(NULL, oss.str().c_str(), "SCVL Error", MB_RETRYCANCEL) == IDCANCEL) {
		exit(1);
	}
}
#define ISPRING_VERIFY_POINTER(PTR)	__VerifyPointer(PTR,__FILE__,__FUNCTION__,__LINE__)
inline void __VerifyPointer(void* ptr, const char* __file__, const char* __function__, int __line__) {
	if (ptr == nullptr) {
		__VerifyError("Pointer is NULL", __file__, __function__, __line__);
	}
}
#define ISPRING_VERIFY_FILEPATH(PATH)	__VerifyFilePath(PATH,__FILE__,__FUNCTION__,__LINE__)
inline void __VerifyFilePath(std::string path, const char* __file__,const char* __function__, int __line__) {
	if (path.length() == 0) {
		__VerifyError("path is empty", __file__, __function__, __line__);
	}
	if (PathFileExistsA(path.c_str()) != TRUE) {
		__VerifyError("path file is incorrect", __file__, __function__, __line__);
	}
	std::fstream fchk(path, std::ios::in);
	bool can_not_open = fchk.is_open();
	fchk.close();
	if (can_not_open == false) {
		__VerifyError("can't open file", __file__, __function__, __line__);
	}
}

#endif