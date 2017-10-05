#pragma once
#include"ispring/All.h"

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
		cv::Mat thinn = ispring::CV::Thinning(img);
		cv::Mat glue = ispring::CV::GlueImage({ img, thinn });
		cv::imwrite("thinning.jpg", glue);
		cv::Mat disct = ispring::CV::PixelDisconnect(thinn);
		cv::imwrite("disconnected.png", disct);
		std::vector<std::vector<cv::Point>> chain = ispring::CV::PixelChain(disct);
		cv::Mat out;
		cv::cvtColor(disct, out, CV_GRAY2BGR);
		int i = 0;
		for (auto&F1:chain) {
			cv::Vec3b color;
			color[0] = (uchar)ispring::CV::GetRGB(i)[0];
			color[1] = (uchar)ispring::CV::GetRGB(i)[1];
			color[2] = (uchar)ispring::CV::GetRGB(i)[2];
			for (auto& F2 : F1) {
				out.at<cv::Vec3b>(F2.y, F2.x) = color;
			}
			i++;
		}
		cv::imwrite("pixel-chain.png", out);
	}
	{
		cv::Mat img = cv::imread("../../img/test0002.jpg");
		cv::Mat edge = ispring::CV::AutoCanny(img);
		cv::Mat glue = ispring::CV::GlueImage({ img, edge });
		cv::imwrite("edge.jpg", glue);
	}
	{
		cv::Mat img = cv::imread("../../img/test0002.jpg");
		cv::Mat z1=ispring::CV::Zoom(img, 0.5);
		cv::Mat z2 = ispring::CV::Zoom(img, 0.7);
		cv::Mat z3 = ispring::CV::Zoom(img, 1.2);
		cv::Mat z4 = ispring::CV::Zoom(img, 1.5);
		cv::Mat glue =ispring::CV::GlueImage({ z1,z2,z3,z4,z1 });
		cv::imwrite("zoom.jpg", glue);
	}
	{
		cv::Mat img = cv::imread("../../img/test0002.jpg");
		cv::imwrite("rotate1.jpg", ispring::CV::ImageRotateOuter(img, 45));
		cv::imwrite("rotate2.jpg", ispring::CV::ImageRotateInner(img, 45));
	}
}
void UnitTest_CVEval() {
	UNITTEST(CVEval);
	std::vector<BoxSE> predict;
	predict.push_back(BoxSE(0, 0.9F, 10, 200, 400, 400));
	predict.push_back(BoxSE(0, 0.86F, 450, 140, 750 - 480, 420 - 150));

	std::vector<BoxSE> ground_truth;
	ground_truth.push_back(BoxSE(0, -1, 0, 180, 430, 400));
	ground_truth.push_back(BoxSE(0, -1, 480, 150, 750-480, 420-150));
	
	cv::Mat img = cv::imread("../../img/test0002.jpg");

	for (auto&e : predict) {
		ispring::CVEval::DrawBoxSE(img, e,cv::Scalar(0,0,255));
	}
	for (auto&e : ground_truth) {
		ispring::CVEval::DrawBoxSE(img, e, cv::Scalar(0, 0, 255));
	}
	
	std::map<int, std::pair<float, float>> rp = ispring::CVEval::GetRecallPrecisionMultiClass(ground_truth, predict, 0.5F);
	std::cout << "Recall : " << rp[0].first << std::endl;
	std::cout << "Precision : " << rp[0].second << std::endl;
	cv::imwrite("draw.png", img);
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