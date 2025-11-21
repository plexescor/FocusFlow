#include <iostream>
#include "WindowTrackerAndShit/Headers/GetWindowRelatedInfoWin32.hpp"

int main()
{
    std::string choice;
    std::cout << "Enter true or false: ";
    std::cin>>choice;
    if (choice == "true")
    {
        getCurrentWindow();
    }
}
