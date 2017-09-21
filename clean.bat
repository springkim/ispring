IF EXIST "x64" (
	RMDIR /S /Q "x64"
)
IF EXIST "x86" (
	RMDIR /S /Q "x86"
)
IF EXIST "prj_ISpring\Debug" (
	RMDIR /S /Q "prj_ISpring\Debug"
)
IF EXIST "prj_ISpring\Release" (
	RMDIR /S /Q "prj_ISpring\Release"
)
IF EXIST "prj_ISpring\x64" (
	RMDIR /S /Q "prj_ISpring\x64"
)
IF EXIST "install_ispring\Debug" (
	RMDIR /S /Q "install_ispring\Debug"
)
IF EXIST "install_ispring\Release" (
	RMDIR /S /Q "install_ispring\Release"
)