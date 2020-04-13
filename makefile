all:
	g++ object.cpp cell.cpp window.cpp player.cpp menu.cpp CASSE-BRIQUE.cpp -o jeu -lncurses
clean:
	rm -f hello

