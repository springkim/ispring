#include<iostream>
#include<thread>
#include<opencv2/opencv.hpp>
//#include"unit_test.h"
#include"../Web.h"
void MainUnitTest(){
	/*UnitTest_Basic();
	UnitTest_Console();
	UnitTest_File();
	UnitTest_System();
	UnitTest_Time();
	UnitTest_Compression();
	
	UnitTest_CV();

	UnitTest_CVEval();
	UnitTest_CVPlot();
	UnitTest_CVViz();*/
}
int main() {
	//MainUnitTest();
	auto html = ispring::Web::GetHtml("https://github.com/springkim/ISpring");
	std::cout << html << std::endl;
	
	
	return 0;
}