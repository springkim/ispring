# ispring/Verify
### Support OS
<img src="https://i.imgur.com/ElCyyzT.png" title="Windows8" width="48">

### Support Compiler
<img src="https://i.imgur.com/d67ToiK.png" width="48"><img src="https://i.imgur.com/O5bye0l.png" width="48"><img src="https://i.imgur.com/XFJ2SfL.png" width="48"><img src="https://i.imgur.com/u1NhcaW.jpg" width="48"><img src="https://i.imgur.com/zhdD9BY.png" width="48">

### Verify

`#include"ispring/Verify.h"`
* * *

#### `ISPRING_VERIFY(message)`
화면에 메세지 박스를 띄우고, 프로그램을 종료할지 계속진행할지 선택합니다.

#### `ISPRING_VERIFY_POINTER(pointer)`
포인터가 NULL 일경우 에러 메세지를 출력합니다.

#### `ISPRING_VERIFY_FILEPATH(path)`
파일이 존재하지 않을경우 에러 메세지를 출력합니다.

