GPP = g++ -O3 -Wall


M = Main.o
P = FileParser.o
I = Interpreter.o

Aprog: $(P) $(M) $(I)
	$(GPP) -o findNearestPairs $(P) $(M) $(I)

Main.o: Main.h Main.cpp
	$(GPP) -o Main.o -c -DEBUGMAIN Main.cpp

FileParser.o: FileParser.h FileParser.cpp
	$(GPP) -o FileParser.o -c -DEBUGMAIN FileParser.cpp

Interpreter.o: Interpreter.h Interpreter.cpp
	$(GPP) -o Interpreter.o -c -DEBUGMAIN Interpreter.cpp

clean:
	rm findNearestPairs
	clean

