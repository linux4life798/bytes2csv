CC = gcc
CFLAGS = -Wall -Wextra -pedantic
LDFLAGS = 

BIN_PATH = $(HOME)/bin

.PHONY: all clean install uninstall

all: bytes2csv

bytes2csv: bytes2csv.o

bytes2csv.o: main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o bytes2csv.o main.c

clean:
	$(RM) bytes2csv bytes2csv.o

install: bytes2csv
	[ -d $(BIN_PATH) ] || { echo "### Creating local bin ($(HOME)/bin)"; mkdir -p $(BIN_PATH); }
	[ ! -e $(BIN_PATH)/bytes2csv ] || { echo "### Removing existing file"; rm -i $(BIN_PATH)/bytes2csv; }
	cp bytes2csv $(BIN_PATH)/
	which bytes2csv >/dev/null || echo "!!! $(HOME)/bin not in PATH"

uninstall:
	rm -i $(BIN_PATH)/bytes2csv
