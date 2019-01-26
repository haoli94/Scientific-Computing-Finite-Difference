#--writeup_1
#--The compile statement is done in one line instead of broken up over multiple rules.
#--START
CXX := g++
CXXFLAGS := -O3 -std=c++11 -Wall -Wextra -Wconversion 
main: main.cpp CGSolver.cpp CGSolver.hpp COO2CSR.cpp COO2CSR.hpp matvecops.cpp matvecops.hpp heat.cpp heat.hpp sparse.cpp sparse.hpp
	$(CXX) $(CXXFLAGS) -o main main.cpp CGSolver.cpp COO2CSR.cpp matvecops.cpp heat.cpp sparse.cpp
.PHONY: clean
clean:
	$(RM) main
#--END

