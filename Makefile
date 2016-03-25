# Compiler/linker setup ------------------------------------------------------

# Mac OS X-specific flags.  Comment these out if using Linux.
#PLATFORM = osx
#CC       = gcc
#CFLAGS   = -fast -Wall
#OSLIBS   = -Wl,-framework -Wl,IOKit
#LDFLAGS  =Acknowledgments

# Linux-specific flags.  Comment these out if using Mac OS X.
PLATFORM = linux
CC       = gcc
CFLAGS   = -O3 -Wall
OSLIBS   =
LDFLAGS  =

# Example programs -----------------------------------------------------------

mcp: mcp.o i2c.o
	$(CC) $(LDFLAGS) mcp.o i2c.o $(OSLIBS) -o mcp

# I2C library i2c.o ----------------------------------------------------------

i2c.o: i2c-$(PLATFORM).c i2c.h
	$(CC) $(CFLAGS) i2c-$(PLATFORM).c -c -o i2c.o

# Maintenance and stuff ------------------------------------------------------

clean:
	rm -f i2c.o mcp.o mcp 

*.o: i2c.h

.c.o:
	$(CC) $(CFLAGS) -c $*.c
