CPP=clang++
CFLAGS=-std=c++11 -O3
EXECUTABLE=./ccdr2
LIBROOT=./lib
INCLUDE=-I/Users/Zigmund-2/code/daglearn/lib/ -I/Users/Zigmund-2/code/daglearn/ccdr2/lib/
HEADERDEPS=$(LIBROOT)/*.h

all: $(EXECUTABLE) run

ccdr2: main.o 
	$(CPP) $(CFLAGS) $(INCLUDE) $< -o $@
	$(EXECUTABLE)

sandbox: sandbox.o 
	$(CPP) $(CFLAGS) $(INCLUDE) $< -o $@
	./sandbox

main.o: main.cpp
	$(CPP) $(CFLAGS) $(INCLUDE) -c $<

sandbox.o: sandbox.cpp
	$(CPP) $(CFLAGS) $(INCLUDE) -c sandbox.cpp

clean:
	rm -fv *o ccdr sandbox

run:
	$(EXECUTABLE)
