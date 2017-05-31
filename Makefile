########################################
##
## Makefile
## LINUX compilation
##
##############################################


#FLAGS
C++FLAG = -g -std=c++11 -Wall

#Math Library
MATH_LIBS = -lm
EXEC_DIR=.


#Rule for .cpp files
# .SUFFIXES : .cpp.o

.cpp.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@


#Including
INCLUDES=  -I.


LIBS_ALL =  -L/usr/lib -L/usr/local/lib $(MATH_LIBS)


#ZEROTH PROGRAM
ALL_OBJ0=CreateGraphAndTest.o
PROGRAM_0=CreateGraphAndTest
$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ1=FindPath.o
PROGRAM_1=FindPath
$(PROGRAM_1): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ2=TopologicalSort.o
PROGRAM_2=TopologicalSort
$(PROGRAM_2): $(ALL_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ2) $(INCLUDES) $(LIBS_ALL)

#Compiling all

all:
		make $(PROGRAM_0)
		make $(PROGRAM_1)
		make $(PROGRAM_2)

run101:
		./$(PROGRAM_0) Graph1.txt AdjacencyQueries1.txt
run102:
		./$(PROGRAM_0) Graph2.txt AdjacencyQueries.txt
run103:
		./$(PROGRAM_0) Graph3.txt AdjacencyQueries.txt

run201:
		./$(PROGRAM_1) Graph1.txt 1
run202:
		./$(PROGRAM_1) Graph2.txt 1
run203:
		./$(PROGRAM_1) Graph3.txt 1

run301:
		./$(PROGRAM_2) Graph1.txt
run302:
		./$(PROGRAM_2) Graph2.txt
run303:
		./$(PROGRAM_2) Graph3.txt

#Clean obj files

clean:
	(rm -f *.o; rm -f $(PROGRAM_0); rm -f $(PROGRAM_1); rm -f $(PROGRAM_2))


(:
