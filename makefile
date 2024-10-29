CC = gcc
CFLAGS = -I$(IDIR)

SRCDIR = ./src/
IDIR = ./include/
BINDIR = ./bin/

SOURCES = $(wildcard $(SRCDIR)*.c)

EXEC = $(BINDIR)Server

all: $(EXEC)

$(EXEC): $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXEC)

run:
	$(EXEC)

clean:
	rm -f $(EXEC)
