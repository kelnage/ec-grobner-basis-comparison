CFLAGS := -m64 -g
CFLAGS := -m64 
CC:=gcc $(CFLAGS)
CPP:=g++ $(CFLAGS)
LIBDIR := macosx
LIBDIR := x64

# ----------------------------------------------------------------------
#
# Use FGb as a library: demo files
#
# ----------------------------------------------------------------------


# --------------------------------------------------

main:main.o gb1.o  gb2.o
	$(CPP)  -o $@ main.o gb1.o gb2.o -L$(LIBDIR) -lfgb -lfgbexp -lgb -lgbexp -lminpoly -lminpolyvgf -lgmp -lm -fopenmp

main.static:main.o gb1.o  gb2.o
	$(CPP) -static -o $@ main.o gb1.o gb2.o -L$(LIBDIR) -lfgb -lfgbexp -lgb -lgbexp -lminpoly -lminpolyvgf -L$(GMP_STATIC_DIR) -lgmp -lm -fopenmp

main.o:main.c
	$(CC) -I ../../protocol -I ../../int  -c $<

gb1.o:gb1.c
	$(CC) -I ../../protocol -I ../../int  -c $<

gb2.o:gb2.c
	$(CC) -I ../../protocol -I ../../int  -c $<

clean:
	-rm main main.o gb2.o gb1.o

veryclean:
	-rm main main.o gb2.o gb1.o *~

test:main
	@echo "======================================================================"
	./main 1
	@echo "======================================================================"

