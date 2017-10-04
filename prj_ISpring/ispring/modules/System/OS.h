/**
* @file		OS.h
* @author		kimbomm (springnode@gmail.com)
* @date		2017. 9. 17...
* @version	1.0.0
*
*  @brief
*			운영체제 관련 라이브러리
*	@remark
*			Created by kimbom on 2017. 9. 17...
*			Copyright 2017 kimbom.All rights reserved.
*/
#if !defined(ISPRING_7E1_9_11_WINDOWS_HPP_INCLUDED)
#define ISPRING_7E1_9_11_WINDOWS_HPP_INCLUDED
#include"../defines.h"
#if defined(ISPRING_WINDOWS) ||defined(DOXYGEN)
#include<iostream>
#include<vector>
#include<string>
#include<Windows.h>
namespace ispring {
	/**
	*	@brief 이 정적 클래스는 운영체제의 정보나 프로세스의 정보를 다룹니다.
	*	@author kimbomm
	*	@date 2017-09-17
	*/
	class OS {
	public:
		/**
		*	@brief 관리자 권한인지 확인합니다.
		*	@return 관리자 권한인경우 true
		*/
		static bool isAdmin() {
			BOOL b;
			SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
			PSID AdministratorsGroup;
			b = AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID
										 , DOMAIN_ALIAS_RID_ADMINS
										 , 0, 0, 0, 0, 0, 0, &AdministratorsGroup);
			if (b) {
				if (!CheckTokenMembership(NULL, AdministratorsGroup, &b)) {
					b = FALSE;
				}
				FreeSid(AdministratorsGroup);
			}
			return b == TRUE;
		}
		/**
		*	@brief 64bit 운영체제인지 확인합니다.
		*	@return 64bit OS 일경우 true
		*/
		static bool is64BitOS() {
#if defined(_WIN64)
			return true;
#elif defined(_WIN32) && defined(_MSC_VER)
			BOOL f64 = FALSE;
			return IsWow64Process(GetCurrentProcess(), &f64) && f64;
#elif defined(_WIN32) 
			return system("reg Query \"HKLM\\Hardware\\Description\\System\\CentralProcessor\\0\" | find /i \"x86\" > NUL && exit /b 0 || exit /b 1");
#else
			return false;
#endif
		}
		/**
		*	@brief 64bit 프로세스인지 확인합니다.
		*	@return 64bit 프로세스 일경우 true
		*/
		static bool is64BitProcess() {
			typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
			LPFN_ISWOW64PROCESS fnIsWow64Process;
			BOOL bIsWow64 = FALSE;
			fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "IsWow64Process");
			if (fnIsWow64Process != NULL) {
				if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64)) {
					return false;
				}
			}
			return bIsWow64 != TRUE;
		}
	};
}
#elif

#endif
#endif  //ISPRING_7E1_9_11_WINDOWS_HPP_INCLUDED