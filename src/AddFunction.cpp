#include <iostream> // std::cout

#include "AddFunction.hpp"
#include "InputParser.hpp"
#include "TodoFunction.hpp"

AddFunction::AddFunction(InputParser& ip):
    TodoFunction("add", "Add a normal priority task"),
    input(ip)
{ }

void AddFunction::run()
{
    std::cout << "ADD" << std::endl;
}
