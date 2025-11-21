#include <iostream>
#include <chrono>
#include <thread>

#include "WindowTrackerAndShit/Headers/GetWindowRelatedInfoWin32.hpp" 

int main()
{
    std::string choice;
    std::cout << "Enter true or false: ";
    std::cin >> choice;

    if (choice == "true")
    {
        for (;;) 
        { 
            std::cout << getCurrentWindow() << "\n";
            
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    return 0;
}