#include <iostream>

void printHello(){
    std::cout << "Hello CMake from Lib sub-directories!!" << std::endl;

    return;
}

int main()
{
    printHello();
    return 0;
}
