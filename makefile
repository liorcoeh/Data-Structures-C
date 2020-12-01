DS = libds
TESTPATH = ./test/
TEST = scheduler_test
UTIL = libutility
TESTNAME = main_test

C_FILES:= $(shell find ./src -name *.c)
INCLUDES:= -I ./include
DEPS = ./include/*.h

C_UTILITY = ../utility/src/*.c
UTILPATH = -I ../utility/include 
UTILHEADER = ../utility/include/*.h

VALGRIND = valgrind --leak-check=yes --track-origins=yes

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g			# For Debbuging
LDFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 # Not Debbug

test: $(DS).so $(UTIL).so $(TESTPATH)$(TEST).c $(DEPS)
	@ $(CC) -L./lib -Wl,-rpath=./lib/ $(INCLUDES) $(LDFLAGS) -o $(TESTNAME) $(TESTPATH)$(TEST).c -lds -lutility -lm
	@ mv $(TESTNAME) ./$@/bin
	@ ./test/bin/$(TESTNAME)

debug: $(DS).so $(UTIL).so $(TESTPATH)$(TEST).c $(DEPS)
	@ $(CC) -L./lib -Wl,-rpath=./lib/ $(INCLUDES) $(CFLAGS) -o $(TESTNAME) $(TESTPATH)$(TEST).c -lds -lutility -lm
	@ mv $(TESTNAME) ./test/bin

$(DS).so: $(C_FILES) $(DEPS)
	@ $(CC) $(INCLUDES) $(CFLAGS) $(C_FILES) -fPIC -shared -o $@
	@ mv $(DS).so ./lib

$(UTIL).so: $(C_UTILITY)
	@ $(CC) $(UTILPATH) $(CFLAGS) $(C_UTILITY) -fPIC -shared -o $@
	@ mv $(UTIL).so ./lib

vlg: ./$@/bin/test
	VALGRIND ./$@/bin/test

.PHONY: clean

clean:
	 @rm -f -R *.o *.so $(TEST)_test
