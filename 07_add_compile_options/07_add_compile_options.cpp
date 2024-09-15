#include <iostream>
#include "fun_lib1.h"
#include "fun_lib2.h"


int main()
{

    // warning demo
    int i;


    //sanitizer demo : run the exe to view this issue
    int arr[10];
    arr[100]= 1234;

    std::cout << "Demo : add compile options!" << std::endl;
    printMessage1();
    printMessage2();
    return 0;
}
