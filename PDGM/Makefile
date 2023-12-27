########################################################################
# This inner makefile actually does the work of the compilation.
# See line 36 for the only reason this makefile should be edited (probably).
########################################################################

# STEP 1: Create variables used
# why so many warnings flags? because it's good practice to be warning and error free
# the -Werror flag turns any compiler warnings into errors, stopping compilation
C_FLAGS   = -c -std=c99 -pedantic -Wall -Wextra -D__EXTENSIONS__
OPT       = -O3 -Werror -Wno-unused-but-set-variable
D_FLAG    = -g
LD_FLAGS  = -Wall -Wextra
EXE       = PDGM
TEST      = tester
GCC       = gcc
RM        = rm

# This section determines which tools should be used for debugging
# memory checking, depending on the system. Windows users, I'm sorry.
UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
	DEBUGGER=gdb
	LEAKER=valgrind --leak-check=full --read-var-info=yes --show-reachable=yes
else
ifeq ($(UNAME),Darwin)
	DEBUGGER=lldb
	LEAKER=leaks -quiet -atExit --
endif
endif

HEADERS   = functions.h pdgm.h
SRCS      = pdgm.c rand.c init.c message.c
TEST_SRCS = pdgm.c rand.c init.c message.c test.c

# Generic variable for converting the engine source files into object files
OBJS      = $(SRCS:.c=.o)

# Generic variable for converting the perft test source files into object files
TEST_OBJS = $(TEST_SRCS:.c=.o)

# NOTE: In the below makefile targets, replace $(D_FLAG) with $(OPT)
# to enable optimizations and turn off debugging info

# Generic (hidden) target for compiling C files into object files
# Used by the OBJS and TEST_OBJS targets below
.c.o:
	@echo "Compiling each C source file separately..."
	$(GCC) $(C_FLAGS) $(OPT) $<
	@echo ""

# Target for creating the engine exectuable
# First compiles all object files, then links them together,
# moves the exectuable to the bin directory, and echos the results out.
$(EXE): $(OBJS)
	@echo "Creating executable..."
	$(GCC) -o $(EXE) $(LD_FLAGS) $(OPT) $(OBJS)
	@mv $(EXE) ../bin
	@echo ""
	@echo "Compilation successful!"

# Target for creating the perft testing exectuable
# First compiles all object files, then links them together,
# moves the exectuable to the bin directory, and echos the results out.
$(TEST): $(TEST_OBJS)
	@echo "Creating executable..."
	$(GCC) -o $(TEST) $(LD_FLAGS) $(OPT) $(TEST_OBJS)
	@mv $(TEST) ../bin
	@echo ""
	@echo "Compilation successful!"

# Target for compiling the engine source files
# First creates the bin directory (see `start` target below)
# then uses the generic .c.o target above to compile each C
# file one by one
$(OBJS): start $(HEADERS)

# Target for compiling the perft testing source files
# First creates the bin directory (see `start` target below)
# then uses the generic .c.o target above to compile each C
# file one by one
$(TEST_OBJS): start $(HEADERS)

# Target that creates the bin directory (if it doesn't already exist)
start:
	@[ -d ../bin ] || mkdir ../bin

# Target to run the debug tool on the engine executable
# Compiles the engine first
debug: $(EXE)
	$(DEBUGGER) ../bin/$(EXE)

# Target to run the memory safety tool on the engine executable
# Compiles the engine first
memcheck: $(EXE)
	$(LEAKER) ../bin/$(EXE)

# Target to reset the directories. Removes the bin directory
# (and everything in it) and removes any other lingering,
# unnecessary files
clean:
	@echo "Cleaning up"
	$(RM) -rf ../bin *.o .DS_Store ../*.debug ../log.*
	@echo ""
	@echo "Clean."

# Recompile the engine from scratch
# First removes everything via the `clean` target, then recompiles
new:
	@make clean
	@make
