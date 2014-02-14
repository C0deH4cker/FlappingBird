GAME := flappingbird

BUILD := build
SRCS := $(wildcard *.cpp)
OBJS := $(addprefix $(BUILD)/, $(SRCS:.cpp=.o))

SGE := SimpleGameEngine
LIBSGE := $(SGE)/build/libsge.a

CXXFLAGS := -Wall \
	-Wextra \
	-Wwrite-strings \
	-Winit-self \
	-Wcast-align \
	-Wcast-qual \
	-Wpointer-arith \
	-Wstrict-aliasing \
	-Wformat=2 \
	-Wmissing-declarations \
	-Wmissing-include-dirs \
	-Wno-unused-parameter \
	-Wuninitialized \
	-Wno-reorder

override CXXFLAGS += -std=c++11 -I./$(SGE)/include

GLFWDEPS = $(shell grep Libs.private $(SGE)/glfw/src/glfw3.pc | cut -d' ' -f2-)
LDFLAGS := -L/opt/local/lib -lpng

all: $(GAME)

$(BUILD):
	mkdir -p $(BUILD)

spritesheet.png:
	curl -o $@ http://www.spriters-resource.com/resources/sheets/56/59537.png

sge:
	git submodule update --init

$(LIBSGE): sge
	$(MAKE) -C $(SGE)

$(GAME): $(LIBSGE) $(OBJS) | spritesheet.png
	$(CXX) -o $@ $^ $(GLFWDEPS) $(LDFLAGS)

$(BUILD)/%.o: %.cpp | $(BUILD)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

gitupdate:
	git pull
	git submodule update --init

update: gitupdate all

clean:
	rm -rf $(BUILD) flappingbird

.PHONY: all clean gitupdate sge update

