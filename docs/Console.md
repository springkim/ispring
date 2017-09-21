# ISpring/Console





### Support OS

<img src="https://i.imgur.com/ElCyyzT.png" title="Windows8" width="48"><img src="https://i.imgur.com/WUmFQlx.png" width="48">



### Support Compiler

<img src="https://i.imgur.com/d67ToiK.png" width="48"><img src="https://i.imgur.com/O5bye0l.png" width="48"><img src="https://i.imgur.com/XFJ2SfL.png" width="48"><img src="https://i.imgur.com/u1NhcaW.jpg" width="48"><img src="https://i.imgur.com/zhdD9BY.png" width="48">



* * *

## xout

`#include"ISpring/Console.h"`

* * *



전역 객체 xout 은 새 Console 창을 만들고 출력할수 있습니다.



#### `void xout::Create(std::string window,_xout_color bk=x_out_color(0),DWORD bufsize=1000)`

새로운 콘솔창을 생성 합니다.

* **Parameter**

	* **window** : 새로 만들 콘솔 창의 이름입니다. 이 값은 고유한 값이여야 합니다.

    * **bk** : 새 콘솔 창의 배경 색상입니다. 이 값은 **xout** 의 색상 멤버변수를 넣을 수 있으며 종류는 아래와 같습니다.

    * <img src="https://i.imgur.com/d0tylUn.png" height="48">

    * `black`, `blue`, `green`, `aqua`, `red`, `purple`, `yellow`, `white`, `gray`, `light_blue`, `light_green`, `light_aqua`,`light_red`,`light_purple`, `light_yellow`,`light_white`

    * **bufsize** : 사용될 공유메모리의 크기 입니다. 기본값은 1000 입니다.



#### `xstream& Console::operator[](std::string window)`

출력할 Console window를 지정합니다. 



#### `xstream& Console::operator<<(TYPE val)`

화면에 메세지를 출력하거나 색을 지정합니다.

#### Example

```cpp

ispring::xout.Create("window1");

ispring::xout.Create("window2");

ispring::xout.Create("window3");



std::cout << ispring::xout.light_green << "hello, world" << std::endl;

ispring::xout["window1"] << ispring::xout.light_red << "hello, world" << std::endl;

ispring::xout["window2"] << ispring::xout.light_aqua << "hello, world" << std::endl;

ispring::xout["window3"] << ispring::xout.light_yellow << "hello, world" << std::endl;

std::cout << ispring::xout.white;

```

![](https://i.imgur.com/W8YbAqT.png)



