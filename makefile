all:
	mingw32-g++.exe -std=c++14 -Wall simple-pass-filter.cpp stdsfmllib.cpp -I C:\LIBRARIES -I C:\SFML-2.5.1\include -L C:\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system