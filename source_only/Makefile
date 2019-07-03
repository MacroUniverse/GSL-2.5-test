# disable implicit rules
MAKEFLAGS = -r
.SUFFIXES: .c .o

# for intel compiler, use icpc (resembles g++), not icc (resembles icpc), the two are different when linking! icc will give errors "undefined reference to ..."
CC = g++ -g -Wall -I include/ -I source/
# CC = icpc -g -Wall -I include/ -I source/

#.o.c:
#	$(CC) -c $<

Sdir = source/

goal: test.x
clean:
	rm -r *.o *.x

test.x: test.o math.o error.o stream.o coupling.o elementary.o exp.o gamma.o log.o log.o psi.o trig.o zeta.o legendre_P.o coerce.o fdiv.o infnan.o
	$(CC) *.o -o test.x
test.o: test.cpp
	$(CC) -c $<

#cheb_eval.c is a header file! must not be compiled!
#cheb_eval.o: $(Sdir)specfunc/cheb_eval.c
#	$(CC) -c $<

math.o: $(Sdir)complex/math.c
	$(CC) -c $<

error.o: $(Sdir)err/error.c
	$(CC) -c $<
stream.o: $(Sdir)err/stream.c
	$(CC) -c $<

coupling.o: $(Sdir)specfunc/coupling.c
	$(CC) -c $<
elementary.o: $(Sdir)specfunc/elementary.c
	$(CC) -c $<
exp.o: $(Sdir)specfunc/exp.c
	$(CC) -c $<
gamma.o: $(Sdir)specfunc/gamma.c
	$(CC) -c $<
log.o: $(Sdir)specfunc/log.c
	$(CC) -c $<
psi.o: $(Sdir)specfunc/psi.c
	$(CC) -c $<
trig.o: $(Sdir)specfunc/trig.c
	$(CC) -c $<
zeta.o: $(Sdir)specfunc/zeta.c
	$(CC) -c $<
legendre_P.o: $(Sdir)specfunc/legendre_P.c
	$(CC) -c $<

coerce.o: $(Sdir)sys/coerce.c
	$(CC) -c $<
fdiv.o: $(Sdir)sys/fdiv.c
	$(CC) -c $<
infnan.o: $(Sdir)sys/infnan.c
	$(CC) -c $<
