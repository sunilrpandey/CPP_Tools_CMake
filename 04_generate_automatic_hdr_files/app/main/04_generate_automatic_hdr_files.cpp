#include <iostream>
#include "config.h"
#include "fun_lib.h"
int main()
{
    std::cout << "project info is being taken from config file"  << std::endl;
    std::cout << "project name : " << project_name << std::endl;
    std::cout << "project version : " << project_version << std::endl;

    printMessage();
    return 0;
}
