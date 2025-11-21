@echo off
echo ===========================
echo   CLEANING BUILD FOLDER
echo ===========================
if exist build (
    rmdir /s /q build
)

echo ===========================
echo   RECREATING BUILD FOLDER
echo ===========================
mkdir build
cd build

echo ===========================
echo   RUNNING CMAKE CONFIGURE
echo ===========================
cmake ..

echo ===========================
echo   BUILDING PROJECT
echo ===========================
cmake --build .

echo ===========================
echo   DONE!
echo ===========================
pause
