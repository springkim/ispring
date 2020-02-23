#define UNITTEST(NAME)	do{ std::cout << "=========="<<#NAME << "==========\n";}while(false)


#include<iostream>
#include<fstream>

#include"../../ispring/Basic.h"
#include"../../ispring/File.h"
#include "../../ispring/Console.h"
#include "../../ispring/System.h"
#include"../../ispring/Time.h"
#include"../../ispring/Compression.h"
#include"../../ISpring/Verify.h"
#include"../../ISpring/Web.h"

void UnitTest_Web() {
	if (ispring::Web::isOnline() == true) {
		auto html = ispring::Web::GetHtml("https://github.com/springkim/ispring");
		std::cout << html.length() << std::endl;
		ispring::Web::Download("https://github.com/springkim/ispring/releases/download/test/testfile.txt","testfile.txt");
		ispring::File::DirectoryErase("testfile.txt");
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