#include<iostream>
#include<thread>
#include"unit_test.h"
#include"ispring/modules/File/FileManager.h"
void MainUnitTest(){
	UnitTest_Basic();
	UnitTest_Console();
	UnitTest_File();
	UnitTest_System();
	UnitTest_Time();
	UnitTest_Compression();
	
	UnitTest_CV();

	UnitTest_CVEval();
	UnitTest_CVPlot();
}
int main() {
	
	MainUnitTest();
	
	
	
	return 0;
}