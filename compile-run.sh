# Comfile main:
clang++ -o python-llvm `llvm-config --cxxflags --ldflags --system-libs --libs core` python-llvm.cpp

# Run main:
./python-llvm

# Execute generated IR:
lli ./out.ll

# Print result:
echo $?

printf "\n"