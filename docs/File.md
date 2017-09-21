# ispring/File
<img src="https://i.imgur.com/ElCyyzT.png" title="Windows8" width="48">
<br/>
<img src="https://i.imgur.com/d67ToiK.png" width="48"><img src="https://i.imgur.com/O5bye0l.png" width="48"><img src="https://i.imgur.com/XFJ2SfL.png" width="48"><img src="https://i.imgur.com/u1NhcaW.jpg" width="48"><img src="https://i.imgur.com/zhdD9BY.png" width="48">

### File

`#include"ispring/File.h"`

#### `std::vector<std::string> FileList(std::string dir_path, std::string ext, bool recursive = false)`
폴더내의 파일 리스트를 가져 옵니다.

+ **Parameters**
	+ **dir_path** : 폴더의 경로 입니다.
	+ **ext** : 가져올 파일의 확장자를 지정 합니다.
		+ 확장자가 `jpg` 인 파일들만 가져오고 싶으면 `"*.jpg"` 또는 `"jpg"` 를 넣으면 됩니다.
		+ 모든 파일을 가져오고 싶다면 `"*.*"` 이나 `"*"` 을 입력하면 됩니다.
		+ 여러개의 확장자는 `;` 로 구분합니다. ex) `"jpg;bmp;pnb"`
		+ 정규식은 지원하지 않습니다.
	+ **recursive** : 재귀적으로 폴더내 파일들을 가져오려면 **true** 로 설정합니다. 기본적으로 **false** 값을 가집니다.

#### `bool FileExist(std::string file)`
파일이 존재하는지 확인 합니다.
+ **Parameters**
	+ **file** : 파일 이름

#### `bool FileErase(std::string file)`
파일을 삭제합니다.
+ **Parameters**
	+ **file** : 파일 이름

#### `bool FileCopy(std::string src, std::string dst)`
파일을 복사합니다.
+ **Parameters**
	+ **src** : 복사할 파일 이름
    + **dst** : 목적 파일 이름


#### `bool DirectoryErase(std::string dir_path, bool noRecycleBin = true)`
디렉토리를 전부 삭제합니다.
+ **Parameters**
	+ **dir_path** : 폴더의 경로 입니다.
	+ **noRecycleBin** : 삭제한 파일을 휴지통에 넣지 않을지를 결정합니다. **true** 일 경우 휴지통에 넣지 않습니다.

#### `bool DirectoryCopy(std::string src, std::string dst)`
디렉토리를 복사합니다.
+ **Parameters**
	+ **src** : 복사할 폴더의 경로
	+ **dst** : 목적 폴더의 경로

#### `bool DirectoryMake(std::string dir)`
디렉토리를 생성합니다.
+ **Parameters**
	+ **dir** : 디렉토리 이름

#### `bool DirectoryExist(std::string dir)`
디렉토리가 존재하는지 확인 합니다.
+ **Parameters**
	+ **dir** : 디렉토리 이름

