CC == gcc
CFLAGS = -lncursesw -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/
SOURCES = $(SRCDIR)*.c

all: clean rogue start

rogue:
	$(CC) $(SOURCES) $(CFLAGS) -o $@

clean:
	del rogue.exe

start:
	start rogue.exe