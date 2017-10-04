if exist "docs" (
	rmdir /S /Q "docs"
)
if exist "html" (
	rmdir /S /Q "html"
)
doxygen
ren html docs
