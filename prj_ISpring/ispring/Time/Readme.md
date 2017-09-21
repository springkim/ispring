# ISpring/Time


### IntervalTime
<img src="https://maxcdn.icons8.com/Color/PNG/24/Operating_Systems/windows8_copyrighted-24.png" title="Windows8" width="24">
<img src="https://i.imgur.com/awqGbrk.png" width="24">

`#include"ISpring/Time/IntervalTime.h"`
* * *

#### `void IntervalTime::StartClock(T param)`
+ **Parameter**
	+ **param** : 시간 측정 구간의 식별자 입니다. 이 매개변수는 **EndClock** 과 반드시 쌍을 이루어야 하며 **char,int,float,double,std::string** 타입을 지원합니다.

#### `double IntervalTime::EndClock(T param, bool print = true)`
+ **Parameters**
	+ **param** : 시간 측정 구간의 식별자 입니다. 이 매개변수는 **StartClock** 에서 정의 된 인수여야 합니다.
	+ **print** : 지정된 화면에 출력할지를 결정합니다. **true** 로 설정되면 구간시간측정용 콘솔창에 따로 출력 합니다.

+ **Return**
	+ **double** : 현재 경과 시간을 반환 합니다.

#### Example
```cpp
ispring::IntervalTime::StartClock("for");
for (int i = 0; i < 3; i++) {
	ispring::IntervalTime::StartClock("test");
	Sleep(1000);
	ispring::IntervalTime::EndClock("test");
}
ispring::IntervalTime::EndClock("for");
//멈추지 않으면 자식 콘솔 창은 바로 종료 됩니다.
system("pause");	
```