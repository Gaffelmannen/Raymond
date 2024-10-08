#CC=clang++
CXXFLAGS=-g -Wall -std=c++17
SRC_DIR=./src
LIB_DIR=./lib
TEST_DIR=./tests
SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp $(LIB_DIR)/*.cpp)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
EXECUTABLE=raymond
TESTABLE=raymond_test
TEST_OBJS=$(SRCS:.cpp=.o)
INCLUDES=-I$(TEST_DIR)

ifeq ($(TARGET),mac)
	CC = clang++
else
	CC = g++
endif

.PHONY : clean cleanall cleanobj test all

default: clean all

clean : cleanall

cleanall : cleanobj
	    rm -f $(EXECUTABLE)

cleanobj :
	    rm -f *.o
	    rm -rf ${EXECUTABLE}.dSYM/

$(OBJ_DIR):
	  mkdir $(OBJ_DIR)

test:
		@$(CC) $(CXXFLAGS) $(INCLUDES) -o $(TESTABLE) $(TEST_OBJS) $(TEST_SRC)
		@./run_test

all :
	    $(CC) $(CXXFLAGS) -o $(EXECUTABLE) $(SRC_FILES)
	    @mkdir -p data
   
