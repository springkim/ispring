# ispring/Zip
<img src="https://i.imgur.com/ElCyyzT.png" title="Windows8" width="48">
<img src="https://i.imgur.com/d67ToiK.png" width="48">
<img src="https://i.imgur.com/O5bye0l.png" width="48">
<img src="https://i.imgur.com/XFJ2SfL.png" width="48">
<img src="https://i.imgur.com/u1NhcaW.jpg" width="48">

### Zip

`#include"ispring/Compression.h"`

#### `void Zip(std::string folder, std::string _password = "",std::atomic<int>* progress=nullptr)`
#### `void Zip(std::string zip_name, std::vector<std::string> files, std::string _password = "",std::atomic<int>* progress=nullptr)`

+ **Parameters**
	+ **folder** : 압축할 폴더의 경로입니다.
	+ **zip_name** : 압축파일의 이름을 지정합니다.
	+ **files** : 압축할 파일들 입니다.
	+ **_password** : 압축파일의 비밀번호를 설정합니다. 없으면 빈 문자열을 삽입합니다.
	+ **progress** : 현재 진행 상태를 나타냅니다. Thread-safe 하게 구현 되 있으며 0-100까지의 상태로 나타납니다.

폴더를 통채로 압축하는 경우는 [Bandizip](https://www.bandisoft.co.kr/bandizip/)의 인터페이스와 같게 최상의 폴더의 경로는 제외하고 압축합니다. 파일들을 압축하는 경우는 그러한 경우를 고려하지 않습니다.
#### Example
```cpp
puts("make zip_test folder...");
_mkdir("zip_test");
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
ispring::File::DeleteDirectory("zip_test");
ispring::Zip::Uncompress("zip_test.zip");
ispring::File::DeleteDirectory("zip_test");
DeleteFileA("zip_test.zip");
```

### Unzip

* * *

#### `void UnZip(std::string file, std::string _password = "",std::atomic<int>* progress=nullptr)`
+ **Parameters**
	+ **file** : 압축해제할 파일의 이름입니다.
	+ **_password** : 압축파일의 비밀번호를 설정합니다. 없으면 빈 문자열을 삽입합니다.
	+ **progress** : 현재 진행 상태를 나타냅니다. Thread-safe 하게 구현 되 있으며 0-100까지의 상태로 나타납니다.
