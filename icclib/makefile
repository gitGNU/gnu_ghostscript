# Dumbo UNIX style makefile, for icclib and friends.

CFLAGS= -O
CC = cc
DOCC = $(CC) -c $(CFLAGS)
OF =  -o 
O = o

LNFLAGS= -lm
LN = cc
LPATH = 
DOLN = $(LN) $(LNFLAGS)
EXE = 

LIB = ar -r
LOF = -o 
A = a


###############################

all:: libicc.$(A) icctest$(EXE) lutest$(EXE) icclu$(EXE) iccdump$(EXE) iccrw$(EXE) fbtest$(EXE)


icc.$(O): icc.c icc.h
	$(DOCC) $(OF)icc.$(O) icc.c

libicc.$(A): icc.$(O)
	$(LIB)  libicc.$(A) icc.$(O)


icctest.$(O): icctest.c icc.h
	$(DOCC) $(OF)icctest.$(O) icctest.c

icctest$(EXE): icctest.$(O) libicc.$(A)
	$(DOLN) $(LOF)icctest icctest.$(O) libicc.$(A)


lutest.$(O): lutest.c icc.h
	$(DOCC) $(OF)lutest.$(O) lutest.c

lutest$(EXE): lutest.$(O) libicc.$(A)
	$(DOLN) $(LOF)lutest lutest.$(O) libicc.$(A)


icclu.$(O): icclu.c icc.h
	$(DOCC) $(OF)icclu.$(O) icclu.c

icclu$(EXE): icclu.$(O) libicc.$(A)
	$(DOLN) $(LOF)icclu icclu.$(O) libicc.$(A)


iccdump.$(O): iccdump.c icc.h
	$(DOCC) $(OF)iccdump.$(O) iccdump.c

iccdump$(EXE): iccdump.$(O) libicc.$(A)
	$(DOLN) $(LOF)iccdump iccdump.$(O) libicc.$(A)


iccrw.$(O): iccrw.c icc.h
	$(DOCC) $(OF)iccrw.$(O) iccrw.c

iccrw$(EXE): iccrw.$(O) libicc.$(A)
	$(DOLN) $(LOF)iccrw iccrw.$(O) libicc.$(A)


fbtest.$(O): fbtest.c icc.h
	$(DOCC) $(OF)fbtest.$(O) fbtest.c

fbtest$(EXE): fbtest.$(O) libicc.$(A)
	$(DOLN) $(LOF)fbtest fbtest.$(O) libicc.$(A)


