g++ -c main.cpp -o build\bin.o -IC:\SFML\include
g++ build\bin.o -o build\bin.exe -LC:\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lwinmm -lgdi32