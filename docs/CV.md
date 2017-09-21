# ISpring/CV



## Require Library
<img src="https://i.imgur.com/JVmb02s.png" width="48">
## Support OS
<img src="https://i.imgur.com/ElCyyzT.png" title="Windows8" width="48"><img src="https://i.imgur.com/WUmFQlx.png" width="48">

## Support Compiler
<img src="https://i.imgur.com/d67ToiK.png" width="48"><img src="https://i.imgur.com/O5bye0l.png" width="48"><img src="https://i.imgur.com/XFJ2SfL.png" width="48"><img src="https://i.imgur.com/u1NhcaW.jpg" width="48"><img src="https://i.imgur.com/zhdD9BY.png" width="48">

## Image
`#include"ISpring/CV.h"`
* * *

#### `cv::Mat Thinning(cv::Mat image)`
이진 이미지를 세선화 합니다. 
+ **Parameter**
	+ **image** : Mat 이미지.
+ **return**
	+ **cv::Mat** : Zhang-suen 의 세선화 알고리즘이 적용된 이미지.

<img src="https://i.imgur.com/qCUoy5U.jpg" width="640">

#### `cv::Mat AutoCanny(cv::Mat image)`

+ **Parameter**
	+ **image** : Mat 이미지.
+ **return**
	+ **cv::Mat** : Canny edge가 적용된 이미지.

이 함수는 일반적인 이미지에서 적절한 문턱치 값으로 **cv::Canny** 를 수행한 결과를 반환합니다.
현재 이진 이미지에서는 제대로 동작하지 않습니다.
<img src="https://i.imgur.com/M0LxN7q.jpg" width="640">

#### `void DisplayImage(cv::Mat image, bool stop = true, bool full = false)`
적절한 크기로 화면에 이미지를 출력합니다.
+ **Parameter**
	+ **image** : 화면에 출력할 Mat 이미지.
	+ **stop** : 이 값이 **true** 일 경우 하나의 이미지를 출력하고 대기를 합니다. **false**일 경우 동영상 처럼 화면을 계속 갱신합니다. **ESC** 키를 누르면 프로세스를 종료 합니다.
	+ **full** : 이 값이 "false" 이면 화면에 적절한 크기로 출력됩니다. **true** 일 경우 전체화면으로 출력됩니다.


<img src="https://i.imgur.com/ga1KZYi.jpg" width="640">

#### `void DisplayImage2(cv::Mat image, bool async = false)`
+ **Parameter**
	+ **image** : 화면에 출력할 Mat 이미지.
	+ **async** : 이 값이 **true** 일 경우 새 프로세스는 이미지를 출력하고 기존 프로세스는 그대로 진행됩니다. **False** 일 경우 해당 뷰어가 종료할때까지 대기합니다.
	
이 함수는 윈도우의 기본 사진앱에 **Mat** 영상을 출력합니다.

<img src="https://i.imgur.com/k56TpJF.jpg" width="640">

#### `cv::Mat Zoom(cv::Mat image, float ratio)`
이미지를 확대하거나 축소합니다.
+ **Parameters**
	+ **image** : 입력 원본 이미지.
	+ **ratio** : 확대 또는 축소할 비율. 이 값이 1.0F 미만이면 작게 축소되며, 1.0F 이상이면 크게 확대됨.


<img src="https://i.imgur.com/CZVTaZh.jpg" width="640">

#### `cv::Mat ImageRotateOuter(const cv::Mat image, double degree, cv::Point* out = nullptr)`
이미지를 잘리지 않고 회전 시킵니다.
+ **Parameters**
	+ **image** : 입력 원본 이미지.
	+ **degree** : 회전할각도. 시계방향
    + **out** : 회전 중심점을 반환함.


<img src="https://i.imgur.com/5uHt0Eb.jpg" width="640">

#### `cv::Mat ImageRotateInner(const cv::Mat image, double degree, cv::Point2d base=cv::Point2d(-1,-1))`
이미지를 원래 크기에 맞게 회전 시킵니다.
+ **Parameters**
	+ **image** : 입력 원본 이미지.
	+ **degree** : 회전할각도. 시계방향
    + **base** : 회전 중심점. 기본 매개변수를 사용하면 이미지의 중점으로 회전
<img src="https://i.imgur.com/evXPXAt.jpg" width="640">