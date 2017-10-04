#pragma once
#include"ispring\All.h"

#ifndef MinGW
#include"ispring/CV.h"
#endif
#define UNITTEST(NAME)	do{ std::cout << "=========="<<#NAME << "==========\n";}while(false)
void UnitTest_Console() {
	UNITTEST(Console);
	ispring::xout.Create("window1");
	ispring::xout.Create("window2");
	ispring::xout.Create("window3");

	std::cout << ispring::xout.light_green << "hello, world" << std::endl;
	ispring::xout["window1"] << ispring::xout.light_red << "hello, world" << std::endl;
	ispring::xout["window2"] << ispring::xout.light_aqua << "hello, world" << std::endl;
	ispring::xout["window3"] << ispring::xout.light_yellow << "hello, world" << std::endl;
	std::cout << ispring::xout.white;
}
void UnitTest_System() { 
	UNITTEST(System);
	
	if (ispring::OS::isAdmin()==true) {
		puts("Admin");
	} else {
		puts("Not-Admin");
	}
	if (ispring::OS::is64BitOS() == true) {
		puts("x64 OS");
	} else {
		puts("x86 OS");
	}
	if (ispring::OS::is64BitProcess() == true) {
		puts("x64 process");
	} else {
		puts("x86 process");
	}
}
void UnitTest_Time() {
	UNITTEST(Time);
	ispring::Timer::Tick("for");
	for (int i = 0; i < 5; i++) {
		ispring::Timer::Tick(1234);
		Sleep(100);
		std::cout << "elem : " << ispring::Timer::Tock(1234).accu << std::endl;
	}
	std::cout << "for : " << ispring::Timer::Tock("for").curr << std::endl;
}
void UnitTest_Compression() {
	UNITTEST(Compression);
	puts("make zip_test folder...");
	ispring::File::DirectoryMake("zip_test");
	for (int i = 0; i < 100; i++) {
		std::ofstream fout("zip_test/" + std::to_string(i) + ".txt");
		for (int j = 0; j < 10000; j++) {
			fout << i << "\t" << j << std::endl;
		}
		fout.close();
	}
	puts("zip test...");
	ispring::Zip::Compress("zip_test");
	puts("unzip test...");
	ispring::File::DirectoryErase("zip_test");
	ispring::Zip::Uncompress("zip_test.zip");
	ispring::File::DirectoryErase("zip_test");
	ispring::File::FileErase("zip_test.zip");
	
}
void UnitTest_File() {
	UNITTEST(File);
	std::string dir = "file_test";
	if (ispring::File::DirectoryExist(dir) == TRUE) {
		std::cerr << "Error" << std::endl;
	}
	if (ispring::File::FileExist(dir + "/0.txt") == TRUE) {
		std::cerr << "Error" << std::endl;
	}
	ispring::File::DirectoryMake(dir);
	for (int i = 0; i < 100; i++) {
		std::ofstream fout(dir+"/" + std::to_string(i) + ".txt");
		for (int j = 0; j < 100; j++) {
			fout << i << "\t" << j << std::endl;
		}
		fout.close();
	}
	if (ispring::File::DirectoryExist(dir) == FALSE) {
		std::cerr << "Error" << std::endl;
	}
	if (ispring::File::FileExist(dir + "/0.txt") == FALSE) {
		std::cerr << "Error" << std::endl;
	}
	if (ispring::File::FileCopy(dir + "/0.txt", dir + "/aaa.txt") == FALSE) {
		std::cerr << "Error" << std::endl;
	}
	std::vector<std::string> files = ispring::File::FileList("file_test","*.txt");
	if (files.size() != 101) {
		std::cerr << "Error" << std::endl;
	}
	ispring::File::DirectoryCopy(dir, dir+"2");
	if (ispring::File::DirectoryExist(dir+"2") == FALSE) {
		std::cerr << "Error" << std::endl;
	}
	ispring::File::DirectoryErase(dir);
	ispring::File::DirectoryErase(dir+"2");
	if (ispring::File::DirectoryExist(dir) == TRUE) {
		std::cerr << "Error" << std::endl;
	}
	if (ispring::File::DirectoryExist(dir+"2") == TRUE) {
		std::cerr << "Error" << std::endl;
	}
}
#ifndef MinGW
void UnitTest_CV() {
	UNITTEST(CV);
	{
		cv::Mat img = cv::imread("../../img/test0001.png", 0);
		cv::Mat thinn = ispring::Image::Thinning(img);
		cv::Mat glue = ispring::Image::GlueImage_LR(img, thinn);
		cv::imwrite("thinning.jpg", glue);
	}
	{
		cv::Mat img = cv::imread("../../img/test0002.jpg");
		cv::Mat edge = ispring::Image::AutoCanny(img);
		cv::Mat glue = ispring::Image::GlueImage_LR(img, edge);
		cv::imwrite("edge.jpg", glue);
	}
	{
		cv::Mat img = cv::imread("../../img/test0002.jpg");
		//ispring::Image::DisplayImage(img);
		//ispring::Image::DisplayImage2(img);
		cv::Mat z1=ispring::Image::Zoom(img, 0.5);
		cv::Mat z2 = ispring::Image::Zoom(img, 0.7);
		cv::Mat z3 = ispring::Image::Zoom(img, 1.2);
		cv::Mat z4 = ispring::Image::Zoom(img, 1.5);
		cv::Mat last=ispring::Image::GlueImage_LR(ispring::Image::GlueImage_LR(ispring::Image::GlueImage_LR(z1, z2), img), ispring::Image::GlueImage_LR(z3, z4));
		cv::imwrite("zoom.jpg", last);
	}
	{
		cv::Mat img = cv::imread("../../img/test0002.jpg");
		cv::imwrite("rotate1.jpg", ispring::Image::ImageRotateOuter(img, 45));
		cv::imwrite("rotate2.jpg", ispring::Image::ImageRotateInner(img, 45));
	}
}
#endif
void UnitTest_Basic() {
	std::string plane = ";*.cpp;*.h;*.c;*.jpg;;;;;";
	std::vector<std::string> words = ispring::String::Tokenizer(plane, ";");
	for (auto&word : words) {
		std::cout << word << std::endl;
	}
	std::string filename = "C:/Users/spring/Documents/SourceTree/ISpring/install_ispring.exe";
	//std::string filename = "install_ispring.exe";
	std::cout << ispring::String::GetExtOfFile(filename) << std::endl;
	std::cout << ispring::String::GetNameOfFile(filename) << std::endl;
	std::cout << ispring::String::GetPureNameOfFile(filename) << std::endl;

	std::cout << ispring::String::PadNum(4, 4) << std::endl;
	std::cout << ispring::String::PadNum(12, 4) << std::endl;
	std::cout << ispring::String::PadNum(144, 4) << std::endl;
	std::cout << ispring::String::PadNum(2144, 4) << std::endl;
}