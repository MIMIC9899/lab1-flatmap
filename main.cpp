#include <iostream>
#include "flat_map.h"
#include "flat_map_iterator.h"
#include "pair.h"

int main() {
    FlatMap student;
    FlatMap map2;
    student["first_name"] = "Ivan";
    student["last_name"] = "Petrov";
    student["university"] = "NSU";
    student["department"] = "FIT";
    map2 = student;
    student["group"] = "...";
    Iterator it = map2.begin();
    std::cout << (*it).value << std::endl;
    ++it;
    ++it;
    std::cout << "Student: " << student["first_name"] << " " << student["last_name"] << "\n";
    return 0;
}