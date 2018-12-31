# disable implicit rules
MAKEFLAGS = -r
.SUFFIXES: .c .o

CC = gcc -g -Wall -I include/ -I source/

#.o.c:
#	$(CC) -c $<

Sdir = source/

goal: coupling.o test.o test.x

test.x: *.o
	g++ -g -Wall -I include/ -I source/ *.o -o test.x
test.o: test.cpp
	g++ -g -Wall -I include/ -I source/ -c test.cpp

#cheb_eval.c is a header file! must not be compiled!
#cheb_eval.o: $(Sdir)specfunc/cheb_eval.c
#	$(CC) -c $<

math.o: $(Sdir)complex/math.c
	$(CC) -c $<

error.o: $(Sdir)err/error.c stream.o
	$(CC) -c $<
stream.o: $(Sdir)err/stream.c
	$(CC) -c $<

coupling.o: $(Sdir)specfunc/coupling.c exp.o infnan.o gamma.o error.o
	$(CC) -c $<
elementary.o: $(Sdir)specfunc/elementary.c error.o infnan.o coerce.o
	$(CC) -c $<
exp.o: $(Sdir)specfunc/exp.c infnan.o error.o gamma.o
	$(CC) -c $<
gamma.o: $(Sdir)specfunc/gamma.c psi.o error.o trig.o exp.o log.o infnan.o
	$(CC) -c $<
log.o: $(Sdir)specfunc/log.c infnan.o error.o
	$(CC) -c $<
psi.o: $(Sdir)specfunc/psi.c error.o zeta.o math.o exp.o gamma.o infnan.o
	$(CC) -c $<
trig.o: $(Sdir)specfunc/trig.c infnan.o log.o error.o
	$(CC) -c $<
zeta.o: $(Sdir)specfunc/zeta.c error.o elementary.o exp.o gamma.o infnan.o
	$(CC) -c $<

coerce.o: $(Sdir)sys/coerce.c
	$(CC) -c $<
fdiv.o: $(Sdir)sys/fdiv.c
	$(CC) -c $<
infnan.o: $(Sdir)sys/infnan.c fdiv.o
	$(CC) -c $<
