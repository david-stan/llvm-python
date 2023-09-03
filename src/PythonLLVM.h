/**
 * Python to LLVM IR compiler.
*/

#pragma once

#include <string>

#include "llvm-14/llvm/IR/IRBuilder.h"
#include "llvm-14/llvm/IR/LLVMContext.h"
#include "llvm-14/llvm/IR/Module.h"
#include "llvm-14/llvm/IR/Verifier.h"

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
        // 1. Parse the program
        // auto ast = parser->parser(program)

        // 2. Compile to LLVM IR:
        // compile(ast);
        compile();

        module->print(llvm::outs(), nullptr);

        saveModuleToFile("./out.ll");
    }

private:
    /**
     * Compiles an expression
    */
    void compile(/* TODO: ast*/)
    {
        fn = createFunction("main", llvm::FunctionType::get(builder->getInt32Ty(), false));

        // 2. Compile main body:
        auto result = gen(/* ast  */);
        
        auto i32Result = 
            builder->CreateIntCast(result, builder->getInt32Ty(), true);

        builder->CreateRet(i32Result);
    }

    /**
     * Main compile loop
    */
    llvm::Value* gen()
    {
        return builder->getInt32(42);
    }

    /**
     * Create function
    */
    llvm::Function* createFunction(const std::string& fnName,
                                   llvm::FunctionType* fnType)
    {
        // Check if already defined
        auto fn = module->getFunction(fnName);

        // If not, allocate new function
        if (fn == nullptr)
        {
            fn = createFunctionProto(fnName, fnType);
        }

        createFunctionBlock(fn);
        return fn;
    }

    /**
     * Create function prototype whithout the body
    */
    llvm::Function* createFunctionProto(const std::string& fnName,
                                        llvm::FunctionType* fnType)
    {
        auto fn = llvm::Function::Create(fnType, llvm::Function::ExternalLinkage, fnName, *module);  

        llvm::verifyFunction(*fn);  

        return fn;                                
    }

    /**
     * Create function block
    */
    void createFunctionBlock(llvm::Function* fn)
    {
        auto entry = createBB("entry", fn);
        builder->SetInsertPoint(entry);
    }

    /**
     * Creates a basic block. If the `fn` is passed, the block is
     * automatically appended to the parent function. Otherwise,
     * the block should later be appended manually via
     * fn->getBasicBlockList().push_back(block);
    */
    llvm::BasicBlock* createBB(std::string name, llvm::Function* fn = nullptr)
    {
        return llvm::BasicBlock::Create(*ctx, name, fn); 
    }

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

    llvm::Function* fn;

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