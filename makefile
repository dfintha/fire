BINARY=bin/fire
OBJECTS=obj/animation.o obj/program.o obj/settings.o

CXX=clang++
CXXFLAGS=-std=c++14 -Wall -Wextra -O2 -Iinclude `sdl-config --cflags`
LDFLAGS=`sdl-config --libs`

.PHONY: all clean

all: $(BINARY)

run: $(BINARY)
	@./$(BINARY)

$(BINARY): $(OBJECTS)
	@mkdir -p bin
	@printf "[L] $(BINARY)\n"
	@$(CXX) $(OBJECTS) -o $(BINARY) $(LDFLAGS)
	@printf "[+] Build Succeeded!\n"

obj/%.o: src/%.cpp
	@mkdir -p obj
	@printf "[C] $<\n"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf bin obj
