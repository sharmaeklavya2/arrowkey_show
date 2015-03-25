OBJS = key.c
LINKER_FLAGS = -lSDL2
OUTPUT = key

all: $(OBJS)
	gcc $(OBJS) $(LINKER_FLAGS) -o $(OUTPUT)
