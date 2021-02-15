CXX = gcc
CXXFLAGS = -Wall 


OBJECTS = SymbolTable.o Parser.o Lexan.o Error.o

main: main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) *.o main


