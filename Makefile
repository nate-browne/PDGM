########################################################################
# Makefile for interacting with the makefile inside of the
# directory with the actual code in it. This is purely for
# convenience of not having to `cd` into the inner directory.
########################################################################

TEST      = tester

# Create the actual engine executable
# calls the inner makefile target (see other file for explanation)
$(EXE):
	@make -C ./PDGM/ PDGM

# create the perft test executable
# calls the inner makefile target (see other file for explanation)
$(TEST):
	@make -C ./PDGM/ $(TEST)

# Create and run the engine executable in a command line debugger
# calls the inner makefile target (see other file for explanation)
debug:
	@make -C ./PDGM/ debug

# Create and run the engine exectuable in a memory safety checker
# calls the inner makefile target (see other file for explanation)
memcheck:
	@make -C ./PDGM/ memcheck

# Clean up everything
# calls the inner makefile target (see other file for explanation)
clean:
	@make -C ./PDGM/ clean

# Recompile the engine from scratch
# calls the inner makefile target (see other file for explanation)
new:
	@make -C ./PDGM/ new