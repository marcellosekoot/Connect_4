all: programme


programme: main.cpp Fonc/fonctions.cpp
	g++ main.cpp Fonc/fonctions.cpp -o executable -lsfml-graphics -lsfml-window -lsfml-system




clean:
	rm -rf *.o
	rm -rf Fonc/*.o

mrproper: clean
	rm -rf executable
