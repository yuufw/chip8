CC ?= gcc
CFLAGS ?= -O2 -Wall -I./src -std=c11
LDFLAGS ?=
SDL_LIBS ?= -lSDL2 -lSDL2_ttf

SRCDIR ?= src
OBJDIR ?= obj
BINDIR ?= bin

TARGET ?= $(BINDIR)/chip8

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: sdl

build: CFLAGS += -DHEADLESS
build: prepare clean_objs $(TARGET)

sdl: CFLAGS += -DUSE_SDL
sdl: LDFLAGS += $(SDL_LIBS)
sdl: prepare clean_objs $(TARGET)

prepare:
	@mkdir -p $(OBJDIR) $(BINDIR)

clean_objs:
	@rm -f $(OBJDIR)/*.o

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	@echo "Linking $@..."
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	@rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all build sdl clean prepare clean_objs
