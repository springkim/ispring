# SCVL
**Sogang Computer Vision Library**
version 1.0.4
```
1.0.0 : First release.
1.0.1 : SCVL/All 추가.
1.0.2 : 링커 에러 수정.
1.0.3 : Zoom 메소드 추가.
1.0.4 : DisplayImage2 추가(사진을 시스템 뷰어로 보여줍니다)
```
## Usage
`install/include/` 의 `SCVL` 폴더를 프로젝트에 넣고, 추가 포함 디렉터리에서 경로를 지정합니다.
아래와 같은 형식으로 **include** 하여 사용합니다.
```cpp
#include<SCVL/All>
```

**SCVL** 을 사용하기 위해서는 **opencv** 가 필요합니다.
* * *

## All
**All** 헤더는 아래의 모든 헤더를 포함합니다.
* * *

## File
```
File::GetFileList
```
디렉토리내의 파일 리스트를 가져 옵니다.
**C++:** std::vector<std::string> **GetFileList**(std::string **dir_path**, std::string **ext**, bool **recursive** = false)

+ **Parameters**
	+ **dir_path** : 폴더의 경로 입니다.
	+ **ext** : 가져올 파일의 확장자를 지정 합니다.
		+ 확장자가 `jpg` 인 파일들만 가져오고 싶으면 `"*.jpg"` 또는 `"jpg"` 를 넣으면 됩니다.
		+ 모든 파일을 가져오고 싶다면 `"*.*"` 이나 `"*"` 을 입력하면 됩니다.
		+ 여러개의 확장자는 `;` 로 구분합니다. ex) `"jpg;bmp;pnb"`
		+ 정규식은 지원하지 않습니다.
	+ **recursive** : 재귀적으로 폴더내 파일들을 가져오려면 **true** 로 설정합니다. 기본적으로 **false** 값을 가집니다.

```
File::DeleteDirectory
```
**C++:** bool **DeleteDirectory**(std::string **dir_path**, bool **noRecycleBin** = true)
+ **Parameters**
	+ **dir_path** : 폴더의 경로 입니다.
	+ **noRecycleBin** : 삭제한 파일을 휴지통에 넣지 않을지를 결정합니다. **true** 일 경우 휴지통에 넣지 않습니다.
* * *

## Console
```
Console [class]
```
**C++:** void Console.**Create**(std::string **window**)
+ **Parameter**
	+ **window** : 새로 만들 콘솔 창의 이름입니다. 이 값은 고유해야 합니다.

**C++:** **cstream&** Console.**operator<<**(std::string **window**)
+ **Parameter**
	+ **window** : 출력할 창을 입력 받습니다.
+ **return**
	+ **cstream&** : window 이름을 가진 고유한 콘솔창 입니다.
	
**C++:** : **cstream&** cstream.operator<<(char **val**)
**C++:** : **cstream&** cstream.operator<<(int **val**)
**C++:** : **cstream&** cstream.operator<<(float **val**)
**C++:** : **cstream&** cstream.operator<<(double **val**)
**C++:** : **cstream&** cstream.operator<<(std::string **val**)

#### Example
```cpp
//abc라는 콘솔 창을 생성
scvl::Console.Create("abc");	
//abc라는 콘솔에다 "hello, world"를 출력하고 개행
scvl::Console << "abc" << "hello, world" << std::endl;
```
* * *
## Image
```
Image::AutoCanny
```
**C++:** cv::Mat **AutoCanny**(cv::Mat **image**)
+ **Parameter**
	+ **image** : Mat 이미지.
+ **return**
	+ **cv::Mat** : Canny edge가 적용된 이미지.

이 함수는 일반적인 이미지에서 적절한 문턱치 값으로 **cv::Canny** 를 수행한 결과를 반환합니다.
현재 이진 이미지에서는 제대로 동작하지 않습니다.
```
Image::Thinning
```
**C++:** cv::Mat **Thinning**(cv::Mat **image**)
+ **Parameter**
	+ **image** : Mat 이미지.
+ **return**
	+ **cv::Mat** : Zhang-suen 의 세선화 알고리즘이 적용된 이미지.

```
Image::DisplayImage
```
**C++:** void **DisplayImage**(cv::Mat **image**, bool **stop**=true, bool **full** = false)
+ **Parameter**
	+ **image** : 화면에 출력할 Mat 이미지.
	+ **stop** : 이 값이 **true** 일 경우 하나의 이미지를 출력하고 대기를 합니다. **false**일 경우 동영상 처럼 화면을 계속 갱신합니다. **ESC** 키를 누르면 프로세스를 종료 합니다.
	+ **full** : 이 값이 "false" 이면 화면에 적절한 크기로 출력됩니다. **true** 일 경우 전체화면으로 출력됩니다.

```
Image::DisplayImage2
```
**C++:** void **DisplayImage2**(cv::Mat **image**, bool **async**=false)
+ **Parameter**
	+ **image** : 화면에 출력할 Mat 이미지.
	+ **async** : 이 값이 **true** 일 경우 새 프로세스는 이미지를 출력하고 기존 프로세스는 그대로 진행됩니다. **False** 일 경우 해당 뷰어가 종료할때까지 대기합니다.
	
이 함수는 윈도우의 기본 사진앱에 **Mat** 영상을 출력합니다.
```
Image::Zoom
```
**C++** cv::Mat **Zoom**(cv::Mat **image**, float **ratio**)
+ **Parameters**
	+ **image** : 입력 원본 이미지.
	+ **ratio** : 확대 또는 축소할 비율. 이 값이 1.0F 미만이면 작게 축소되며, 1.0F 이상이면 크게 확대됨.
* * *
## Time
```
IntervalTime [class]
```
**C++:** void **IntervalTime::StartClock**(T **param**)
+ **Parameter**
	+ **param** : 시간 측정 구간의 식별자 입니다. 이 매개변수는 **EndClock** 과 반드시 쌍을 이루어야 하며 **char,int,float,double,std::string** 타입을 지원합니다.

**C++:** double **IntervalTime::EndClock**(T **param**, bool **print** = true)
+ **Parameters**
	+ **param** : 시간 측정 구간의 식별자 입니다. 이 매개변수는 **StartClock** 에서 정의 된 인수여야 합니다.
	+ **print** : 지정된 화면에 출력할지를 결정합니다. **true** 로 설정되면 구간시간측정용 콘솔창에 따로 출력 합니다.

+ **Return**
	+ **double** : 현재 경과 시간을 반환 합니다.

#### Example
```cpp
int main() {
	std::cout << "Main console print" << std::endl;
	scvl::IntervalTime::StartClock("for");
	for (int i = 0; i < 3; i++) {
		scvl::IntervalTime::StartClock("test");
		Sleep(1000);
		scvl::IntervalTime::EndClock("test");
	}
	scvl::IntervalTime::EndClock("for");
	//멈추지 않으면 자식 콘솔 창은 바로 종료 됩니다.
	system("pause");	
	return 0;
}
```
![](http://i63.tinypic.com/5cby40.png)
* * *
## Verify
```
SCVL_VERIFY(MSG) [macro]
```
+ **Parameter**
	+ **MSG** : 문자열 타입이며, 메세지 박스로 해당 에러를 출력하고 계속할지 프로그램을 종료할지 묻습니다. 계속하기를 누르면 해당 에러를 무시하고 프로그램을 진행합니다.

```
SCVL_VERIFY_POINTER(PTR) [macro]
```
+ **Parameter**
	+ **PTR** : 포인터 타입이며, 해당 포인터가 NULL일 경우 **SCVL_VERIFY**를 호출하고 아닌경우 아무 작업도 하지 않습니다.

```
SCVL_VERIFY_FILEPATH(PATH)
```
+ **Parameter**
	+ **PATH** : 문자열 타입이며, 파일의 경로를 받습니다. 경로가 없거나,파일이 존재하지 않거나, 파일을 열 수 없는경우 **SCVL_VERIFY**를 호출하고 아닌경우 아무 작업도 하지 않습니다.

* * *
## Zip
```
Zip
```
**C++:** `void Zip(std::string folder, std::string _password = "",std::atomic<int>* progress=nullptr)`

**C++:** `void Zip(std::string zip_name, std::vector<std::string> files, std::string _password = "",std::atomic<int>* progress=nullptr)`
+ **Parameters**
	+ **folder** : 압축할 폴더의 경로입니다.
	+ **zip_name** : 압축파일의 이름을 지정합니다.
	+ **files** : 압축할 파일들 입니다.
	+ ** _password** : 압축파일의 비밀번호를 설정합니다. 없으면 빈 문자열을 삽입합니다.
	+ **progress** : 현재 진행 상태를 나타냅니다. Thread-safe 하게 구현 되 있으며 0-100까지의 상태로 나타납니다.

폴더를 통채로 압축하는 경우는 [Bandizip](https://www.bandisoft.co.kr/bandizip/)의 인터페이스와 같게 최상의 폴더의 경로는 제외하고 압축합니다. 파일들을 압축하는 경우는 그러한 경우를 고려하지 않습니다.
#### Example(압축의 진행상황을 알아오기)
```cpp
#include<thread>
std::atomic<int> progress = 0;
void ThreadFunc() {
	scvl::Zip("install", "", &progress);
}
int main() {
	std::thread th1(ThreadFunc);
	while (progress != 100) {
		std::cout << progress << std::endl;
	}

	th1.join();
	system("pause");	
	return 0;
}
```
* * *
## Unzip
```
Unzip
```
**C++:** `void UnZip(std::string file, std::string _password = "",std::atomic<int>* progress=nullptr)`
+ **Parameters**
	+ **file** : 압축해제할 파일의 이름입니다.
	+ ** _password** : 압축파일의 비밀번호를 설정합니다. 없으면 빈 문자열을 삽입합니다.
	+ **progress** : 현재 진행 상태를 나타냅니다. Thread-safe 하게 구현 되 있으며 0-100까지의 상태로 나타납니다.