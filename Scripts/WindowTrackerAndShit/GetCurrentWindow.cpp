#include <Windows.h>
#include "Headers/GetCurrentWindow.hpp"

// -------------------------------------------------------
// WINDOWS IMPLEMENTATION
// -------------------------------------------------------

std::string getCurrentWindow()
{
    HWND currWindow = GetForegroundWindow(); // get focused window
    if (!currWindow) return "";               // nothing focused

    DWORD pid = 0; //GEtting pid for the currWindow
    GetWindowThreadProcessId(currWindow, &pid);
    if (pid == 0) return "";

    //Get the handle for the above pid
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!hProcess) return "";                // cannot open, skip

    //Make a buffer for the full path of exe
    char fullPath[MAX_PATH] = {0};
    DWORD size = MAX_PATH;

    // Query full executable path, fail silently if blocked
    if (QueryFullProcessImageNameA(hProcess, 0, fullPath, &size) == 0)
    {
        CloseHandle(hProcess);
        return "";
    }

    CloseHandle(hProcess); //Close safely, prevents weird behaviour

    std::string pathStr(fullPath); //initialize pathStr with the full path
    size_t pos = pathStr.find_last_of("\\/"); //Find last /
    std::string exeName = (pos != std::string::npos) ? pathStr.substr(pos + 1) : pathStr; //Get everything AFTER the slash

    // strip extension, find the dot
    size_t dotPos = exeName.find_last_of(".");
    //Get everything before the exe
    std::string baseName = (dotPos != std::string::npos) ? exeName.substr(0, dotPos) : exeName;

    return baseName;
}
