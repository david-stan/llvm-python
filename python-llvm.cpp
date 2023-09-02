/**
 * Python LLVM executable.
*/

#include "./src/PythonLLVM.h"

int main(int argc, char const *argv[])
{
    /**
     * Program to execute
    */
    std::string program = R"(

        42

    )";

    /**
     * Compiler instance
    */
    PythonLLVM vm;

    /**
     * Generate LLVM IR
    */
    vm.exec(program);

    return 0;
}