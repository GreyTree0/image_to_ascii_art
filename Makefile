#o_files := ascii_converter.o image_parser.o color.o 
#h_files := (wildcard src/*.h)
c_files := $(wildcard ./src/*.c)
o_files = $(c_files:./src/%.c=./build/%.o)
dependencies = $(o_files:.o=.d)

all: $(o_files)
	gcc $^ -ljpeg -o jpeg_to_ascii

./build/%.o: ./src/%.c 
	mkdir -p ./build/
	gcc -MMD -MP -c $< -o $@ 
	
-include $(dependencies)

clean:
	rm -fr ./build jpeg_to_ascii


