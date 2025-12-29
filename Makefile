# Makefile

# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= -std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment

etracker.exe: src/main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.SUFFIXES:

.PHONY: clean

clean:
	rm -rvf *.out *.exe *.dSYM *.stackdump

# Style check
CPD ?= /usr/um/pmd-6.0.1/bin/run.sh cpd
OCLINT ?= /usr/um/oclint-22.02/bin/oclint
