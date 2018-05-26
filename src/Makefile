IDIR = ../include
CXX = g++ -std=c++11
CXXFLAGS = -I$(IDIR) -g

ODIR = obj
LDIR = ../lib

_DEPS = Lista.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Lista.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
<<<<<<< HEAD
rm -f $(ODIR)/*.o $(ODIR)/*.gcno *~ core $(INCDIR)/*~ 
=======
	rm -f $(ODIR)/*.o $(ODIR)/*.gcno *~ core $(INCDIR)/*~ 
>>>>>>> 99afd874a9d0e268c0aa0c23be1bc4f9e6361de3
