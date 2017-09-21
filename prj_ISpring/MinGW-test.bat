g++ main.cpp -O2 -o MinGW-test.exe -lshlwapi -std=c++11
IF EXIST MinGW-test.exe (
	MinGW-test.exe
	
	DEL MinGW-test.exe
)
pause