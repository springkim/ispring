# ISpring/Time


### Timer
<img src="https://i.imgur.com/ElCyyzT.png" title="Windows8" width="48">
<br/>
<img src="https://i.imgur.com/d67ToiK.png" width="48"><img src="https://i.imgur.com/O5bye0l.png" width="48"><img src="https://i.imgur.com/XFJ2SfL.png" width="48"><img src="https://i.imgur.com/u1NhcaW.jpg" width="48"><img src="https://i.imgur.com/zhdD9BY.png" width="48">


`#include"ispring/Time.h"`
* * *

#### `void Timer::Tick(T param)`
+ **Parameter**
	+ **param** : 시간 측정 구간의 식별자 입니다. 이 매개변수는 **EndClock** 과 반드시 쌍을 이루어야 하며 **char,int,float,double,std::string** 타입을 지원합니다.

#### `TimerElement Timer::Tock(T param)`
+ **Parameters**
	+ **param** : 시간 측정 구간의 식별자 입니다. 이 매개변수는 **StartClock** 에서 정의 된 인수여야 합니다.
+ **Return**
	+ **TimerElement** : 현재 경과시간, 누적시간, 평균시간을 반환합니다. 

#### Example
```cpp
ispring::Timer::Tick("for");
for (int i = 0; i < 5; i++) {
	ispring::Timer::Tick(1234);
	Sleep(100);
	std::cout << "elem : " << ispring::Timer::Tock(1234).accu << std::endl;
}
std::cout << "for : " << ispring::Timer::Tock("for").curr << std::endl;
```