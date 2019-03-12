#	$Id: Makefile,v 1.5 2005/09/20 10:56:17 beah Exp $
#CROSS   = ppc_440ep-
#CROSS	 = arm-soft_uclibc-linux-gnu-
#CROSS	= arm-hismall-linux-
CROSS	=
CC		= $(CROSS)gcc
STRIP	= $(CROSS)strip

BINDIR = /usr/local/sbin
MANDIR = /usr/local/man
CFLAGS+= -g -Wall
# CFLAGS+= -DHAS_FGETLN -DHAS_STRLCPY
# CFLAGS+= -Wall -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations
# CFLAGS+= -Wshadow -Wpointer-arith -Wcast-qual -Wsign-compare
LDFLAGS+= -lpthread

all:		interface certy 
	$(STRIP) interface
#	cp interface /tftpboot/
#	cp interface /target/

interface:		interface.o 
	$(CC) $(LDFLAGS) interface.o  $(LDLIBS) -o interface

certy:		certy.o 
	$(CC) $(LDFLAGS) certy.o  $(LDLIBS) -o certy

interface.o:	interface.c
	$(CC) $(CFLAGS) -c interface.c

certy.o:	certy.c
	$(CC) $(CFLAGS) -c certy.c

clean:
	rm -f interface certy *.o
