#include<iostream>
#include<thread>
#define USE_7Z
#include"unit_test.h"
#include"../Web.h"
#include"../Console.h"
void MainUnitTest(){
	UnitTest_Basic();
	UnitTest_Console();
	UnitTest_File();
	UnitTest_System();
	UnitTest_Time();
	UnitTest_Compression();
	UnitTest_Web();
}
int main() {
	MainUnitTest();
	return 0;
}