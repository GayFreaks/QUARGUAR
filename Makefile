default: build

BIN = bin
SOURCES = src/*.cpp

$(BIN):
	mkdir -p $(BIN)

build: $(BIN)
	gcc -lstdc++ `pkg-config --cflags gtk+-3.0` -o bin/Quarguar $(SOURCES) `pkg-config --libs gtk+-3.0` `pkg-config --libs --cflags cairo`

run: $(BIN) build
	bin/Quarguar