@echo off
echo ===========================
echo   Building
echo ===========================
if exist build (
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

    echo ===========================
    echo   Running.... 
    echo ===========================

    cd Debug/
    ViraChrono.exe

)
