all:
	mingw32-g++.exe -std=c++14 -Wall main.cpp stdsfmllib.cpp -o main.exe -I ./dependencies/ -I ./dependencies/SFML/include/ -L./dependencies/SFML/lib/ -lsfml-graphics -lsfml-window -lsfml-system
