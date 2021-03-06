# A sample Makefile for building Google Test and using it in user
# tests.  Please tweak it to suit your environment and project.  You
# may want to move it to your project's root directory.
#
# SYNOPSIS:
#
#   make [all]  - makes everything.
#   make TARGET - makes the given target.
#   make clean  - removes all files generated by make.

# Please tweak the following variable definitions as needed by your
# project, except GTEST_HEADERS, which you can use in your own targets
# but shouldn't modify.

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = ..

# Where to find user code.
USER_DIR = ../../..

# Where to find user tests.
USER_TEST_DIR = ../..

# Flags passed to the preprocessor.
CPPFLAGS += -I$(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = unittests

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.

all : $(TESTS)

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

# Class files
CheckersBoard.o : $(USER_DIR)/CheckersBoard.cpp $(USER_DIR)/CheckersBoard.h \
                  $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/CheckersBoard.cpp

CheckersMove.o : $(USER_DIR)/CheckersMove.cpp $(USER_DIR)/CheckersMove.h \
                 $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/CheckersMove.cpp

CheckersView.o : $(USER_DIR)/CheckersView.cpp $(USER_DIR)/CheckersView.h \
                 $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/CheckersView.cpp

CheckersDlg.o : $(USER_DIR)/CheckersDlg.cpp $(USER_DIR)/CheckersDlg.h \
                 $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/CheckersDlg.cpp

Dialog.o : $(USER_DIR)/Dialog.cpp $(USER_DIR)/Dialog.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Dialog.cpp

Board.o : $(USER_DIR)/Board.cpp $(USER_DIR)/Board.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Board.cpp

Class.o : $(USER_DIR)/Class.cpp $(USER_DIR)/Class.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Class.cpp

# Test files
CheckersBoardTest.o : $(USER_TEST_DIR)/CheckersBoardTest.cpp \
                     		$(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_TEST_DIR)/CheckersBoardTest.cpp

CheckersMoveTest.o : $(USER_TEST_DIR)/CheckersMoveTest.cpp \
                     		$(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_TEST_DIR)/CheckersMoveTest.cpp

# Targets
unittests : CheckersBoard.o CheckersMove.o CheckersView.o CheckersDlg.o \
	         Dialog.o Board.o Class.o \
				CheckersBoardTest.o \
				CheckersMoveTest.o \
				gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@ -lpthread
