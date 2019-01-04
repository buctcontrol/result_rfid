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

all:		interface 
	$(STRIP) interface
#	cp interface /tftpboot/
#	cp interface /target/

interface:		interface.o 
	$(CC) $(LDFLAGS) interface.o  $(LDLIBS) -o interface

interface.o:	interface.c
	$(CC) $(CFLAGS) -c interface.c


install:	all
	install -o root -g bin -m 0555 interface $(BINDIR)
#	install -o root -g wheel -m 0755 -d $(MANDIR)/man8
#	install -o root -g bin -m 0444 interface.8 $(MANDIR)/man8

clean:
	rm -f interface *.o
