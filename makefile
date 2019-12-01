CPP = g++
CFLAGS = -g -w -lgmp
VERSION = --std=c++2a
BINARY = rsa

all: $(BINARY)

%.o: %.cpp %.h
	$(CPP) $(CFLAGS) $(VERSION) -c $< -o $@

$(BINARY): driver.cpp rsa.o
	$(CPP) $(CFLAGS) $(VERSION) -o $(BINARY) driver.cpp rsa.o

clean:
	rm -rf *.o $(BINARY)
