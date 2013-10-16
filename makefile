CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := -lm -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window 
CC_FLAGS := -Wall -Wextra -pedantic -std=c++11 -Werror

Dron: $(OBJ_FILES)
	g++ $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<