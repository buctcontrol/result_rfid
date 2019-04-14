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

IOBJS = interface.o results.o report.o global.o riders.o utils.o points_rule.o racing_info.o

all:		interface certy 
	$(STRIP) interface
#	cp interface /tftpboot/
#	cp interface /target/

interface:	$(IOBJS)
	$(CC) $(LDFLAGS) $(IOBJS) $(LDLIBS) -o interface

certy:		certy.o 
	$(CC) $(LDFLAGS) certy.o  $(LDLIBS) -o certy

interface.o:	interface.c racing_info.h results.h report.h
	$(CC) $(CFLAGS) -c interface.c

riderc.o:	riderc.c  utils.h
	$(CC) $(CFLAGS) -c riderc.c

report.o:	report.c global.h points_rule.h riders.h utils.h interface.h
	$(CC) $(CFLAGS) -c report.c

results.o:	results.c global.h riders.h utils.h interface.h
	$(CC) $(CFLAGS) -c results.c

points_rule.o:	points_rule.c global.h utils.h
	$(CC) $(CFLAGS) -c points_rule.c

racing_info.o:	racing_info.c utils.h
	$(CC) $(CFLAGS) -c racing_info.c

global.o:	global.c
	$(CC) $(CFLAGS) -c global.c

utils.o:	utils.c
	$(CC) $(CFLAGS) -c utils.c interface.h

certy.o:	certy.c
	$(CC) $(CFLAGS) -c certy.c

clean:
	rm -f interface certy *.o
