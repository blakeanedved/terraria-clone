all:src/main.cpp clean
	g++ -o main src/main.cpp -std=c++11 -Isrc/headers -Isrc/precompiled -framework GLUT -framework OpenGL -O2 -lm -lpthread -L/usr/local/lib -lnoise -lglfw -lglew

pch:src/headers/pch.hpp
	rm -rf src/precompiled/pch.hpp.gch
	g++ -o src/precompiled/pch.hpp.gch -c src/headers/pch.hpp -std=c++11

globals:src/headers/globals.hpp
	rm -rf src/precompiled/globals.hpp.gch
	g++ -o src/precompiled/globals.hpp.gch -c src/headers/globals.hpp -std=c++11

precompiles:src/headers/pch.hpp src/headers/globals.hpp clean_precompiles
	g++ -o src/precompiled/pch.hpp.gch -c src/headers/pch.hpp -std=c++11
	g++ -o src/precompiled/globals.hpp.gch -c src/headers/globals.hpp -std=c++11

clean_precompiles:
	rm -rf src/precompiled/*

clean:
	rm -rf build/*

temp:temp.cpp
	g++ -std=c++17 -Wall -g temp.cpp -o temp
