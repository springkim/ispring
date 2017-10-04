if exist "docs" (
	rmdir /S /Q "docs"
)
doxygen
ren html docs
git add -A
git commit -m "ispring"
git push origin master

