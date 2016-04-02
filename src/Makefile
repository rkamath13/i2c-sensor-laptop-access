# Compiler/linker setup ------------------------------------------------------
PLATFORM = linux
CC       = gcc
CFLAGS   = -O3 -Wall
OSLIBS   =
LDFLAGS  =

all: mcp sensor-template

# MCP9808 program -----------------------------------------------------------

mcp: mcp.o i2c.o
	$(CC) $(LDFLAGS) mcp.o i2c.o $(OSLIBS) -o mcp

# sensor-template program -----------------------------------------------------------

sensor-template: sensor-template.o i2c.o
	$(CC) $(LDFLAGS) sensor-template.o i2c.o $(OSLIBS) -o sensor-template


# I2C library i2c.o ----------------------------------------------------------

i2c.o: i2c-linux.c i2c.h
	$(CC) $(CFLAGS) i2c-linux.c -c -o i2c.o

# Maintenance and stuff ------------------------------------------------------

clean:
	rm -f i2c.o mcp.o mcp sensor-template.o sensor-template

*.o: i2c.h

.c.o:
	$(CC) $(CFLAGS) -c $*.c
