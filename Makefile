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
	-Wno-reorder \

LDFLAGS := -pthread -lGL -lGLU -lX11 -lXext -lm -lXxf86vm -lXrandr -lXi
override CXXFLAGS += -std=c++11 -I./$(SGE)/build/include

GLFWDEPS = $(shell grep Libs.private $(SGE)/build/glfw/src/glfw3.pc | cut -d' ' -f2-)

all: $(GAME)

$(BUILD):
	mkdir -p $(BUILD)

spritesheet.png:
	curl -o $@ http://www.spriters-resource.com/resources/sheets/56/59537.png

$(LIBSGE):
	$(MAKE) -C $(SGE)

$(GAME): $(LIBSGE) $(OBJS) | spritesheet.png
	$(CXX) -o $@ $^ $(GLFWDEPS) $(LDFLAGS) $(LIBSGE)

$(BUILD)/%.o: %.cpp | $(BUILD)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	rm -rf $(BUILD) flappingbird

.PHONY: all clean

