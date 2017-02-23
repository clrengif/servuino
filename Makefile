make:
	clang++ -g -fsanitize=address -I./inc -std=c++11 -O2 servuino.cpp -o servuino

clean:
	rm servuino
