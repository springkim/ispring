/*
*  Windows.h
*  ISpring
*
*  Created by kimbom on 2017. 9. 17...
*  Copyright 2017 kimbom. All rights reserved.
*
*/
#if !defined(ISPRING_7E1_9_11_WINDOWS_HPP_INCLUDED)
#define ISPRING_7E1_9_11_WINDOWS_HPP_INCLUDED
#if defined(_WIN32) || defined(_WIN64)
#include<iostream>
#include<vector>
#include<string>
#include<Windows.h>
namespace ispring {
	class OS {
	public:
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