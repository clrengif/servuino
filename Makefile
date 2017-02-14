make:
	g++ -I./inc -std=c++11 -O2 servuino.c -o servuino

clean:
	rm servuino
