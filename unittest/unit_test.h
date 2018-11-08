#define UNITTEST(NAME)	do{ std::cout << "=========="<<#NAME << "==========\n";}while(false)


#include<iostream>
#include<fstream>

#include"../../ispring/Basic.h"
#include"../../ispring/File.h"
#include "../../ispring/Console.h"
#include "../../ispring/System.h"
#include"../../ispring/Time.h"
#include"../../ispring/Compression.h"
#include"../../ispring/CV.h"
void UnitTest_CVPlot() {
	UNITTEST(CVPlot);
	ispring::Plot plot;
	ispring::PlotElement elem1,elem2;
	elem1.m_color = cv::Scalar(0, 0, 255);
	elem1.m_name = "sin";
	elem2.m_color = cv::Scalar(0, 255, 0);
	elem2.m_name = "cos";
	for (int i = 0; i <= 1000; i += 1) {
		cv::Point2d pt;
		pt.x = i;
		pt.y = sin(i*CV_PI / 180);
		elem1.m_data.push_back(pt);
		pt.y = cos(i*CV_PI / 180);
		elem2.m_data.push_back(pt);
	}

	plot.Add(elem1);
	plot.Add(elem2);
	plot.SetBGColor(cv::Scalar(33, 33, 33));
	plot.SetTextColor(cv::Scalar(233, 233, 233));
	plot.SetMaxInfo(25);
	plot.SetThickness(2);
	plot.SetSize(1000, 600);
	cv::Mat img = plot.Draw();
	cv::imwrite("plot.png", img);
}
void UnitTest_CVViz() {
	UNITTEST(CVViz);
	cv::Mat img = cv::imread("img/test0002.jpg",cv::IMREAD_GRAYSCALE);
	
	
	cv::HOGDescriptor hog;
	cv::Size winsize(128, 128);
	cv::Size cellsize(4, 4);
	hog.winSize = winsize;
	hog.blockSize = cellsize * 2;;
	hog.blockStride = cellsize;
	hog.cellSize = cellsize;
	hog.nbins = 9;
	std::vector<float> hog_features;
	std::vector<cv::Point> loc;
	cv::Mat hog_img;
	cv::resize(img, hog_img, winsize, 0, 0, cv::INTER_AREA);
	hog.compute(img, hog_features, cv::Size(0, 0), cv::Size(0, 0), loc);
	cv::Mat hog_viz = ispring::CV::HogVisualization(hog, hog_img, hog_features, 5, 3, cv::Scalar(255, 255, 255));
	cv::resize(hog_viz, img, img.size());
	cv::imshow("hog visualization", img);
	cv::waitKey(1000);
	cv::destroyWindow("hog visualization");
}
void UnitTest_CVEval() {
	UNITTEST(CVEval);
	std::vector<BoxSE> predict;
	predict.push_back(BoxSE(0, 0.9F, 10, 200, 400, 400));
	predict.push_back(BoxSE(0, 0.86F, 450, 140, 750 - 480, 420 - 150));
	
	std::vector<BoxSE> ground_truth;
	ground_truth.push_back(BoxSE(0, -1, 0, 180, 430, 400));
	ground_truth.push_back(BoxSE(0, -1, 480, 150, 750-480, 420-150));
	
	cv::Mat img = cv::imread("img/test0002.jpg");
	
	for (auto&e : predict) {
		ispring::CV::DrawBoxSE(img, e,cv::Scalar(0,0,255));
	}
	for (auto&e : ground_truth) {
		ispring::CV::DrawBoxSE(img, e, cv::Scalar(0, 0, 255));
	}
	
	/*std::map<int, std::pair<float, float>> rp = ispring::CV::GetRecallPrecisionMultiClass(ground_truth, predict, 0.5F);
	std::cout << "Recall : " << rp[0].first << std::endl;
	std::cout << "Precision : " << rp[0].second << std::endl;*/
	cv::imwrite("draw.png", img);
}
void UnitTest_CV() {
	UNITTEST(CV);
	{
		cv::Mat img = cv::imread("img/test0001.png", 0);
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
		cv::Mat img = cv::imread("img/test0002.jpg");
		cv::Mat edge = ispring::CV::AutoCanny(img);
		cv::Mat glue = ispring::CV::GlueImage({ img, edge });
		cv::imwrite("edge.jpg", glue);
	}
	{
		cv::Mat img = cv::imread("img/test0002.jpg");
		cv::Mat z1=ispring::CV::Zoom(img, 0.5);
		cv::Mat z2 = ispring::CV::Zoom(img, 0.7);
		cv::Mat z3 = ispring::CV::Zoom(img, 1.2);
		cv::Mat z4 = ispring::CV::Zoom(img, 1.5);
		cv::Mat glue =ispring::CV::GlueImage({ z1,z2,z3,z4,z1 });
		cv::imwrite("zoom.jpg", glue);
	}
	{
		cv::Mat img = cv::imread("img/test0002.jpg");
		cv::imwrite("rotate1.jpg", ispring::CV::ImageRotateOuter(img, 45));
		cv::imwrite("rotate2.jpg", ispring::CV::ImageRotateInner(img, 45));
	}
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
void UnitTest_Time() {
	UNITTEST(Time);
	for (int i = 0; i < 5; i++) {
		ispring::Timer::Tick(1234);
		#ifdef ISPRING_WINDOWS
		Sleep(1000);
		#elif defined(ISPRING_LINUX)
		usleep(1000000);
		#endif
		ispring::Timer::Tock(1234);
	}
	std::cout << ispring::Timer::Watch(1234).avg << std::endl;
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
void UnitTest_Console() {
	UNITTEST(Console);
	std::cout << ispring::xout.aqua << "aqua" << std::endl;
	std::cout << ispring::xout.black << "black" << std::endl;
	std::cout << ispring::xout.blue << "blue" << std::endl;
	std::cout << ispring::xout.gray << "gray" << std::endl;
	std::cout << ispring::xout.green << "green" << std::endl;
	std::cout << ispring::xout.white << "white" << std::endl;
	std::cout << ispring::xout.purple << "purple" << std::endl;
	std::cout << ispring::xout.red << "red" << std::endl;
	std::cout << ispring::xout.yellow << "yellow" << std::endl;

	std::cout << ispring::xout.light_aqua << "light_aqua" << std::endl;
	std::cout << ispring::xout.light_blue << "light_blue" << std::endl;
	std::cout << ispring::xout.light_green << "light_green" << std::endl;
	std::cout << ispring::xout.light_purple << "light_purple" << std::endl;
	std::cout << ispring::xout.light_red << "light_red" << std::endl;
	std::cout << ispring::xout.light_white << "light_white" << std::endl;
	std::cout << ispring::xout.light_yellow << "light_yellow" << std::endl;

	ispring::xout.Create("window1");
	ispring::xout.Create("window2");
	ispring::xout.Create("window3");
	
	ispring::xout["window1"] << ispring::xout.light_red << "hello, world 1" << std::endl;
	ispring::xout["window2"] << ispring::xout.light_aqua << "hello, world 2" << std::endl;
	ispring::xout["window3"] << ispring::xout.light_yellow << "hello, world 3" << std::endl;
	std::cout << ispring::xout.light_white;
}
void UnitTest_File() {
    UNITTEST(File);
    std::string dir = "file_test";
    if (ispring::File::DirectoryExist(dir) == true) {
        std::cerr << "Error" << std::endl;
    }
    if (ispring::File::FileExist(dir + "/0.txt") == true) {
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
    if (ispring::File::DirectoryExist(dir) == false) {
        std::cerr << "Error" << std::endl;
    }
    if (ispring::File::FileExist(dir + "/0.txt") == false) {
        std::cerr << "Error" << std::endl;
    }
    if (ispring::File::FileCopy(dir + "/0.txt", dir + "/aaa.txt") == false) {
        std::cerr << "Error" << std::endl;
    }
    std::vector<std::string> files = ispring::File::FileList("file_test","*.txt");
    if (files.size() != 101) {
        std::cerr << "Error" << std::endl;
    }
    ispring::File::DirectoryCopy(dir, dir+"2");
    if (ispring::File::DirectoryExist(dir+"2") == false) {
        std::cerr << "Error" << std::endl;
    }
    ispring::File::DirectoryErase(dir);
    ispring::File::DirectoryErase(dir+"2");
    if (ispring::File::DirectoryExist(dir) == true) {
        std::cerr << "Error" << std::endl;
    }
    if (ispring::File::DirectoryExist(dir+"2") == true) {
        std::cerr << "Error" << std::endl;
    }
	ispring::File::DirectoryErase("sequantial");
	ispring::File::DirectoryMake("sequantial");
	cv::Mat test = cv::Mat::zeros(500, 500, CV_8UC3);
	cv::Point ppt(test.cols / 2, test.rows/2);
	for (int i = 0; i < 10000; i+=100) {
		cv::Point pt(i/360.0*10, 0);
		cv::Point cpt;
		float rad = (i % 360) * CV_PI / 180;
		cpt.x = pt.x*cos(rad) - pt.y*sin(rad) + test.cols/2;
		cpt.y = pt.x*sin(rad) + pt.y*cos(rad) + test.rows/2;
		cv::line(test, ppt, cpt, cv::Scalar(0, 0, 255), 1, CV_AA);
		ppt = cpt;
		cv::imshow("test", test);
		std::string name=ispring::File::GetNextSequantialName("sequantial", "*.jpg");
		cv::imwrite(name, test);
		cv::waitKey(10);
	}
	cv::destroyWindow("test");


}
void UnitTest_Basic() {
	std::string plane = ";*.cpp;*.h;*.c;*.jpg;;;;;";
	std::vector<std::string> words = ispring::String::Tokenizer(plane, ";");
	for (auto&word : words) {
		std::cout << word << std::endl;
	}
	std::string filename = "C:/Users/spring/Documents/SourceTree/ISpring/install_ispring.exe";
	std::cout << ispring::String::GetExtOfFile(filename) << std::endl;
	std::cout << ispring::String::GetNameOfFile(filename) << std::endl;
	std::cout << ispring::String::GetPureNameOfFile(filename) << std::endl;

	std::cout << ispring::String::PadNum(4, 4) << std::endl;
	std::cout << ispring::String::PadNum(12, 4) << std::endl;
	std::cout << ispring::String::PadNum(144, 4) << std::endl;
	std::cout << ispring::String::PadNum(2144, 4) << std::endl;
}