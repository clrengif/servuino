make:
	arduino --verify -v --board arduino:avr:esplora sketch/sketch.ino && g++ -I./inc -O2 servuino.c -o servuino

clean:
	rm servuino
