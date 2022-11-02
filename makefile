# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3

all	: bin/mps
	@echo -n ""

# optimized version
bin/mps			: fillTable_opt.o main_opt.o lib
			# $(CC) $(OPTFLAGS) fillTable_opt.o main_opt.o -ltm_usage -Llib -o bin/mps
			$(CC) $(OPTFLAGS) fillTable_opt.o main_opt.o -o bin/mps
main_opt.o 	   	: src/main.cpp lib/tm_usage.h
			$(CC) $(CFLAGS) $< -Ilib -o $@
fillTable_opt.o	: src/fillTable.cpp src/fillTable.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# DEBUG Version
dbg : bin/mps_dbg
	@echo -n ""

bin/mps_dbg		: fillTable_dbg.o main_dbg.o lib
			$(CC) $(DBGFLAGS) fillTable_dbg.o main_dbg.o -ltm_usage -Llib -o bin/mps_dbg
main_dbg.o 	   	: src/main.cpp lib/tm_usage.h
			$(CC) $(CFLAGS) $< -Ilib -o $@
fillTable_dbg.o	: src/fillTable.cpp src/fillTable.h
			$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

lib: lib/libtm_usage.a

lib/libtm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<
tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $<

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*

