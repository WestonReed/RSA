CPP = g++
CFLAGS = -g -Wall -Wextra -Werror -pedantic
LDLIBS = -lgmp -lgmpxx
VERSION = --std=c++2a
BINARY = rsa

all: $(BINARY)

%.o: %.cpp %.h
	$(CPP) $(CFLAGS) $(VERSION) $(LDLIBS) -c $< -o $@

$(BINARY): driver.cpp rsa.o
	$(CPP) $(CFLAGS) $(VERSION) $(LDLIBS) -o $(BINARY) driver.cpp rsa.o

clean:
	rm -rf *.o $(BINARY)
