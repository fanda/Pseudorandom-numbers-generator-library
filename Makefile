################################################################################
# Makefile projektu Generator pseudonahodnych cisel
# Pavel Novotny a Ota Pavelek, FIT VUT v Brne, Prosinec 2010

LIBS =
REMOVE = rm -f
BIN = test
EXEC = ./$(BIN)

CPP  = g++

CXXINCS =
CXXFLAGS = -Wall $(CXXINCS)

################################################################################
# obecny cil kompilace
all: $(BIN)

################################################################################
# linkovani vysledneho souboru
$(BIN):	main.o 
	$(CPP) main.o -o $(BIN) $(LIBS)
#	strip $(BIN)

################################################################################
# kompilace hlavniho souboru
main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

################################################################################
# kompilace testu
#pseudorandom.o: pseudorandom.cpp
#	$(CPP) -c pseudorandom.cpp -o pseudorandom.o $(CXXFLAGS)

################################################################################
# kompilace studentskeho souboru
#mtwister.o: mtwister.cpp
#	$(CPP) -c mtwister.cpp -o mtwister.o $(CXXFLAGS)


################################################################################
# cil vycisteni souboru prekladu
clean: clear
clear:
	$(REMOVE) ~* *.o $(BIN)
	$(REMOVE) tests/generated/* tests/graphs/*

################################################################################
# otestovani rozlozeni
run: 
	$(EXEC) all
################################################################################
