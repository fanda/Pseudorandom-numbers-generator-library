
ifeq ($(OS), Windows_NT)
  LIBS =
  REMOVE = del
  BIN = test.exe
else
  LIBS =
  REMOVE = rm -f
  BIN = test
endif

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
################################################################################
