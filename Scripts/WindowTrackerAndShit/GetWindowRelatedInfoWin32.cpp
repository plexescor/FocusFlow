#include <iostream>
#include "Headers/GetWindowRelatedInfoWin32.hpp"
//THIS IS THE GetWindowRelatedInfoWin32.cpp
//-------------------------------------------------------
//WINDOWS IMPLEMENTATION
//-------------------------------------------------------

#ifdef _WIN32
#include <Windows.h>
void getCurrentWindow()
{
    HWND hwnd = GetForegroundWindow();
    std::cout << hwnd;
}
#endif