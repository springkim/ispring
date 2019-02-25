/**
* @file		VerifyOutput.h
* @author		kimbomm (springnode@gmail.com)
* @date		2019. 02. 25...
* @version	1.0.0
*
*  @brief
*			에러 출력 라이브러리
*	@remark
*			Created by kimbom on 2019. 02. 25...
*			Copyright 2019 kimbom.All rights reserved.
*/
#if !defined(ISPRING_7E3_2_19_VERIFYOUTPUT_H_INCLUDED)
#define ISPRING_7E3_2_19_VERIFYOUTPUT_H_INCLUDED
#include<string>
#include<sstream>
#include<fstream>
#include"../defines.h"
#ifndef DOXYGEN
#ifndef NOMINMAX
#define NOMINMAX
#endif		//NOMINMAX
#endif		//DOXYGEN

#ifndef DOXYGEN
#if defined(ISPRING_WINDOWS)
#include<Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")


#elif defined(ISPRING_LINUX)

#endif
#endif		//DOXYGEN


#ifndef REMINDER
#define STRINGIZE(l)    #l
#define REMINDER(l, m)  __FILE__ "(" STRINGIZE(l) "): "m

/**
*	@brief XXX 태그를 출력합니다.
*	@param MSG 화면에 출력할 에러 메세지 입니다.
*	@details 해당 부분에 대해서는 더 생각해볼 필요성이 있을 때. 
		또는 해당 부분에 질문이 생길 때. 또는 코드에서 문제가 일어날만한 부분을 강조 표기할때. 
		완벽하게 정확히 구현되지 않은 부분이 있을 때. 나중에 고쳐야만하는 부분일 때
*/
#define XXX        REMINDER(__LINE__, "!!!!!!!!!! XXX !!!!!!!!!! ")
/**
*	@brief TODO 태그를 출력합니다.
*	@param MSG 화면에 출력할 에러 메세지 입니다.
*	@details 좀더 최적화시키고 리팩토링시킬 수 있을만한 구석이 있을때. 
		미래에 뭔가 의미있는 작업을 더 해야 할 필요성을 느낄때.
*/
#define TODO            REMINDER(__LINE__, "<<<<<TODO : ")
/**
*	@brief FIXME 태그를 출력합니다.
*	@param MSG 화면에 출력할 에러 메세지 입니다.
*	@details 문제가 있는것이 확실하지만, 그걸 지금 당장 그것을 수정할 필요는 없을 때.
*/
#define FIXME             REMINDER(__LINE__, "<<<<<FIXME : ")
#endif


#endif