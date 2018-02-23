CXXFLAGS = -Wall -O3 --std=c++1z -lgmp -lntl -L. -lfmt

%: lib.h %.cpp
	g++ $(CXXFLAGS) $@.cpp -o $@
