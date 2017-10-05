if exist "docs" (
	rmdir /S /Q "docs"
)
if exist "html" (
	rmdir /S /Q "html"
)
call clean.bat
call prj_ISpring\upload.bat
doxygen
ren html docs
git add -A
git commit -m "ispring"
git push origin master

