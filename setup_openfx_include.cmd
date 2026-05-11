@echo off

git clone https://github.com/AcademySoftwareFoundation/openfx.git

if exist "include" (
    rmdir /S /Q "include"
)

move "openfx\include" "include"

rmdir /S /Q "openfx"

pause

