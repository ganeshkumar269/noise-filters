SFML_LIB_FILES = -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lpthread
SFML_DEPENDENCIES = -lFLAC -lfreetype -logg -lopenal32 -lvorbis -lvorbisenc -lvorbisfile -lopengl32 -lwinmm -lgdi32
INCLUDES = -I./dependencies/include/
LIBS = -L./dependencies/lib/
LOCAL_INCLUDES = -I./include/
all:	main.o	filters.o	mysf.o
	mingw32-g++.exe -std=c++14 -Wall -DSFML_STATIC ./obj/main.o ./obj/mysf.o ./obj/filters.o -o ./bin/main.exe $(LIBS) $(SFML_LIB_FILES) $(SFML_DEPENDENCIES)
main.o: 	
	mingw32-g++.exe -c -std=c++14 -Wall -DSFML_STATIC main.cpp -o ./obj/main.o $(LOCAL_INCLUDES) $(INCLUDES)
filters.o:
	mingw32-g++.exe -c -std=c++14 -Wall -DSFML_STATIC ./src/filters.cpp -o ./obj/filters.o  $(LOCAL_INCLUDES) $(INCLUDES) 
mysf.o:
	mingw32-g++.exe -c -std=c++14 -Wall -DSFML_STATIC ./src/mysf.cpp -o ./obj/mysf.o $(LOCAL_INCLUDES) $(INCLUDES)
rgbToGray.o:
	mingw32-g++.exe -c -std=c++14 -Wall -DSFML_STATIC ./src/rgbToGray.cpp -o ./obj/rgbToGray.o $(LOCAL_INCLUDES) $(INCLUDES)
grayToMono.o:
	mingw32-g++.exe -c -std=c++14 -Wall -DSFML_STATIC ./src/grayToMono.cpp -o ./obj/grayToMono.o $(LOCAL_INCLUDES) $(INCLUDES)
mean.o:
	mingw32-g++.exe -c -std=c++14 -Wall -DSFML_STATIC ./src/mean.cpp -o ./obj/mean.o $(LOCAL_INCLUDES) $(INCLUDES)
clean:
	rm ./bin/main.o ./bin/filters.o ./bin/mysf.o
test:	test.o	mysf.o rgbToGray.o grayToMono.o mean.o 
	mingw32-g++.exe -std=c++14 -Wall -DSFML_STATIC ./obj/test.o ./obj/mysf.o  ./obj/rgbToGray.o ./obj/grayToMono.o ./obj/mean.o -o ./bin/test.exe $(LIBS) $(SFML_LIB_FILES) $(SFML_DEPENDENCIES)
test.o:
	mingw32-g++.exe -c -std=c++14 -Wall -DSFML_STATIC ./test/test.cpp  -o ./obj/test.o $(LOCAL_INCLUDES) $(INCLUDES)