SFML_LIB_FILES = -lsfml-graphics-s -lsfml-window-s -lsfml-system-s 
SFML_DEPENDENCIES = -lFLAC -lfreetype -logg -lopenal32 -lvorbis -lvorbisenc -lvorbisfile -lopengl32 -lwinmm -lgdi32
INCLUDES = -I./dependencies/include/
LIBS = -L./dependencies/lib/
LOCAL_INCLUDES = -I./include/
all:	main.o	filters.o	mysf.o
	mingw32-g++.exe -std=c++14 -Wall -DSFML_STATIC ./bin/main.o ./bin/mysf.o ./bin/filters.o -o ./bin/main.exe $(LIBS) $(SFML_LIB_FILES) $(SFML_DEPENDENCIES)
main.o: 	
	mingw32-g++.exe -c -std=c++14 -Wall -DSFML_STATIC main.cpp -o ./bin/main.o $(LOCAL_INCLUDES) $(INCLUDES)
filters.o:
	mingw32-g++.exe -c -std=c++14 -Wall -DSFML_STATIC ./src/filters.cpp -o ./bin/filters.o  $(LOCAL_INCLUDES) $(INCLUDES) 
mysf.o:
	mingw32-g++.exe -c -std=c++14 -Wall -DSFML_STATIC ./src/mysf.cpp -o ./bin/mysf.o $(LOCAL_INCLUDES) $(INCLUDES)
clean:
	rm ./bin/main.o ./bin/filters.o ./bin/mysf.o