/**
 * Python to LLVM IR compiler.
*/

#pragma once

#include <string>

#include "llvm-14/llvm/IR/IRBuilder.h"
#include "llvm-14/llvm/IR/LLVMContext.h"
#include "llvm-14/llvm/IR/Module.h"

class PythonLLVM {
public:
    PythonLLVM()
    {
        moduleInit();
    }

    /**
     * Execute compiler
    */
    void exec(const std::string& program)
    {
        module->print(llvm::outs(), nullptr);

        saveModuleToFile("./out.ll");
    }

private:

    /**
     * Initialize the module
    */
    void moduleInit()
    {
        ctx = std::make_unique<llvm::LLVMContext>();
        module = std::make_unique<llvm::Module>("PythonLLVM", *ctx);

        builder = std::make_unique<llvm::IRBuilder<>>(*ctx);
    }

    /**
     * Save IR to a file
    */
    void saveModuleToFile(const std::string& fileName)
    {
        std::error_code errorCode;
        llvm::raw_fd_ostream outLL(fileName, errorCode);
        module->print(outLL, nullptr);
    }

    /**
     * Global LLVM context.
     * It owns and manages the core "global" data of LLVM's core
     * infrastructure, including the type and constant unique tables
    */
    std::unique_ptr<llvm::LLVMContext> ctx;

    /**
     * A Module instance is used to store all the information related to an
     * LLVM module. Modules are the top level container of all other LLVM
     * Intermediate Representation (IR) objects. Each module directly contains
     * a list of globals variables, a list of functions, a list of libraries
     * (or other modules) this module depends on, a symbol table, and various
     * data about the target's characteristics
     * 
     * A module maintains a GlobalList object that is used to hold all
     * constant references to global variables in the module. When a global
     * variable is destroyed, it should have no entries in the GlobalList.
     * The main container class for the LLVM Intermediate Representation
    */
   std::unique_ptr<llvm::Module> module;

   /**
    * IR Builder.
    * 
    * This provides a uniform API for creating instructions and inserting
    * them into a basic block: either at the end of a BasicBlock, or at a 
    * specific iterator location in a block
   */
  std::unique_ptr<llvm::IRBuilder<>> builder;

};