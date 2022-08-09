src = $(wildcard ./src/*.cpp)
obj = $(patsubst ./src/%.cpp, ./obj/%.o, $(src))
inc = -I./include/
#inc += -I./interface/
lib = -lpthread

myArgs = -Wall -g

ALL:a.out

a.out: $(obj)
	g++ $^ -o $@ $(myArgs) $(lib)

$(obj):./obj/%.o:./src/%.cpp
	g++ -c $< -o $@ $(myArgs) $(inc)

clean:
	-rm -rf $(obj) a.out

.PHONY: clean ALL

