GPP = g++ -O3 -Wall


M = Main.o
I = Interpreter.o

Aprog: $(P) $(M) $(I)
	$(GPP) -o findNearestPairs $(M) $(I)

Main.o: Main.h Main.cpp
	$(GPP) -o Main.o -c -DEBUGMAIN Main.cpp

Interpreter.o: Interpreter.h Interpreter.cpp
	$(GPP) -o Interpreter.o -c -DEBUGMAIN Interpreter.cpp

clean:
	rm findNearestPairs
	rm Main.o
	rm Interpreter.o
	clean

