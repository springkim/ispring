/**
* @file		www.h
* @author		kimbomm (springnode@gmail.com)
* @date		2017. 10. 05...
* @version	1.0.0
*
*  @brief
*			HTML 처리 라이브러리
*	@remark
*			Created by kimbom on 2017. 10. 05...
*			Copyright 2017 kimbom.All rights reserved.
*/
#if !defined(ISPRING_7E1_A_4_HTML_HPP_INCLUDED)
#define ISPRING_7E1_A_4_HTML_HPP_INCLUDED
#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<sstream>
#include"../defines.h"
#if defined(ISPRING_WINDOWS)
#include<Windows.h>
#include<WinInet.h>
#include<urlmon.h>            //URLDownloadToFileA
#pragma comment(lib,"urlmon.lib")
#pragma comment(lib,"wininet.lib")
#elif defined(ISPRING_LINUX)

#endif
namespace ispring {
	/**
	*	@brief 이 정적 클래스는 웹을 다루는 함수를 포함합니다.
	*	@author kimbomm
	*	@date 2017-10-05
	*/
	namespace Web {
		/**
		*	@brief url의 html을 가져 옵니다.
		*	@param url URL
		*	@return html
		*/
		inline std::string GetHtml(std::string url) {
			std::string html;
#if defined(ISPRING_WINDOWS)
			HINTERNET hInternet = InternetOpenA("HTTP", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);	//인터넷 관련 DLL을 초기화한다.
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
#elif defined(ISPRING_LINUX)
			std::ostringstream cmd;
			cmd << "wget -O - " << url << " 2>/dev/null";
            FILE* fp=popen(cmd.str().c_str(),"r");
            char c;
            while(fread(&c,1,1,fp)==1 && c!=EOF) {
                html.push_back(c);
            }
            pclose(fp);
#endif
			return html;
		}
		/**
		*	@brief url의 파일을 다운로드 합니다.
		*	@param url URL
		*	@param file 저장할 파일 명
		*	@return 다운로드에 성공하면 true
		*/
		inline bool Download(std::string url,std::string file) {
#if defined(ISPRING_WINDOWS)
			HRESULT r = URLDownloadToFileA(nullptr, url.c_str(), file.c_str(), 0, 0);
			return r == S_OK;
#elif defined(ISPRING_LINUX)
            std::ostringstream cmd;
            cmd << "wget -O " << file << " " << url << " 2>/dev/null";
            FILE* fp=popen(cmd.str().c_str(),"r");
            if(fp==NULL)return false;
            else{
                pclose(fp);
                return true;
            }
#endif
		}
		inline bool isOnline() {
#if defined(ISPRING_WINDOWS)
			DWORD dwFlag;
			TCHAR szName[MAX_PATH];
			return ::InternetGetConnectedStateEx(&dwFlag, szName, MAX_PATH, 0);
#elif defined(ISPRING_LINUX)
            FILE* fp=popen("wget --spider --quiet http://example.com","r");
            return WEXITSTATUS(pclose(fp))==0;
#endif
		}
	};
}

#endif  //ISPRING_7E1_A_4_HTML_HPP_INCLUDED