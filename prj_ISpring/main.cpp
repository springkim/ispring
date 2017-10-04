#include<iostream>
#include"unit_test.h"


int main() {
	UnitTest_Console();
	UnitTest_System();
	UnitTest_Time();
	UnitTest_Compression();
	UnitTest_File();
#ifndef MinGW
	UnitTest_CV();
#endif
	

	UnitTest_Basic();
	
	return 0;
}