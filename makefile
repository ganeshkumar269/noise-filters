all:
	mingw32-g++.exe -std=c++14 -Wall main.cpp stdsfmllib.cpp -o main.exe -I C:\LIBRARIES -I C:\SFML-2.5.1\include -L C:\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system