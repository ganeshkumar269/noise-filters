SFML_LIB_FILES = -lsfml-graphics -lsfml-window -lsfml-system 
INCLUDES = -I./dependencies/include/
LIBS = -L./dependencies/lib/
LOCAL_INCLUDES = -I./include/
all:	main.o	filters.o	mysf.o
	mingw32-g++.exe -std=c++14 -Wall ./bin/main.o ./bin/mysf.o ./bin/filters.o -o ./bin/main.exe $(LIBS) $(SFML_LIB_FILES)
main.o: 	
	mingw32-g++.exe -c -std=c++14 -Wall main.cpp -o ./bin/main.o $(LOCAL_INCLUDES) $(INCLUDES)
filters.o:
	mingw32-g++.exe -c -std=c++14 -Wall ./src/filters.cpp -o ./bin/filters.o  $(LOCAL_INCLUDES) $(INCLUDES) 
mysf.o:
	mingw32-g++.exe -c -std=c++14 -Wall ./src/mysf.cpp -o ./bin/mysf.o $(LOCAL_INCLUDES) $(INCLUDES)
clean:
	rm ./bin/main.o ./bin/filters.o ./bin/mysf.o