all:src/main.cpp clean
	g++ -o main src/main.cpp src/cpp/window.cpp src/cpp/tile.cpp -std=c++17 -Isrc/headers -Isrc/precompiled -framework GLUT -framework OpenGL -O2 -lm -lpthread -L/usr/local/lib -lnoise -lglfw -lglew

pch:src/headers/pch.hpp
	rm -rf src/precompiled/pch.hpp.gch
	g++ -o src/precompiled/pch.hpp.gch -c src/headers/pch.hpp -std=c++17

globals:src/headers/globals.hpp
	rm -rf src/precompiled/globals.hpp.gch
	g++ -o src/precompiled/globals.hpp.gch -c src/headers/globals.hpp -std=c++17

precompiles:src/headers/pch.hpp src/headers/globals.hpp clean_precompiles
	g++ -o src/precompiled/pch.hpp.gch -c src/headers/pch.hpp -std=c++17
	g++ -o src/precompiled/globals.hpp.gch -c src/headers/globals.hpp -std=c++17

clean_precompiles:
	rm -rf src/precompiled/*

clean:
	rm -rf build/*
