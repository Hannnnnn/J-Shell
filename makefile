CC = gcc
CXX = g++


TARGET = jsh
OBJ = main.o parser.o terminal.o command.o

$(TARGET): $(OBJ)
	$(CXX) -g -o $@  $^  


%.o: %.c
	$(CC) -g -c $< -o $@ 

%.o: %.cpp
	$(CXX) -g -c $< -o $@ 

.PHONY: clean
	
clean: 
	-rm -f *.o
	-rm -f $(TARGET)
