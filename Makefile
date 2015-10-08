FILES = */main.cpp

all:
	g++ $(FILES) -o bin/risk -Iinclude -Llib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
