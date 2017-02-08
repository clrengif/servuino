make:
	arduino --verify -v --board arduino:avr:esplora sketch/sketch.ino && g++ -I./inc -std=c++11 -O2 servuino.c -o servuino

clean:
	rm servuino
