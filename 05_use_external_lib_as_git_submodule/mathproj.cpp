#include <iostream>
#include <nlohmann/json.hpp>

#include "mathlib.h"

int main() {
    std::cout << "Hello Math!" << std::endl;

     std::cout << "JSON Lib Version:" << NLOHMANN_JSON_VERSION_MAJOR << "." << NLOHMANN_JSON_VERSION_MINOR << "."
              << NLOHMANN_JSON_VERSION_PATCH << "\n";

    std::cout << "Sum of 3 and 5 : " << sum(3,5) << std::endl;
    return 0;
}
