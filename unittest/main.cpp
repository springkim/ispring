#include<iostream>
#include<thread>
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
	//MainUnitTest();
	ispring::xout.Create("win1");
	ispring::xout.Create("win2");
	while (true) {
		std::cout << ispring::xout.aqua<< "hello, world" << std::endl;
		std::cout << ispring::xout.light_purple << "hello, world" << std::endl;
		ispring::xout["win1"] << ispring::xout.light_purple << "hello, c++" <<  ispring::xout.light_aqua << "hhhhhh" <<  std::endl;

		ispring::xout["win2"] << ispring::xout.light_yellow << "hello, c#" << std::endl;
	}
	return 0;
}