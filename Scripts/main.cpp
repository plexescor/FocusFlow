#include <iostream>
#include <thread>
#include <chrono>
#include "WindowTrackerAndShit/Headers/GetCurrentWindow.hpp"

int main()
{
    std::string prevWindow = "";
    std::string currentWindow;
    int windowSwitches = -1; //KEEP IT AT -1, 0 CAUSES INCORRECT READING

    std::cout << "Tracking active windows. Press Ctrl+C to stop.\n";

    while (true)
    {
        currentWindow = getCurrentWindow();

        // skip if no change or empty
        if (currentWindow.empty() || currentWindow == prevWindow)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            continue;
        }

        prevWindow = currentWindow;

        // filter common system/UWP apps
        if (currentWindow != "StartMenuExperienceHost" &&
            currentWindow != "SearchApp" &&
            currentWindow != "ApplicationFrameHost" &&
            currentWindow != "explorer")
        {
            windowSwitches++;
            std::cout << currentWindow << "\n";
            std::cout << "Switches: " << windowSwitches << "\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}
