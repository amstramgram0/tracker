# Usual compilation flags
CFLAGS   = -Wall -Wextra -std=c11 -DDEBUG -g
CPPFLAGS = -I../include
LDFLAGS  = -lcapstone -lcgraph

# Special rules and targets
.PHONY: all clean help

# Rules and targets
all: tracker

tracker: tracker.o trace.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

tracker.o: tracker.c tracker.h ../include/trace.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

trace.o: trace.c ../include/trace.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	@echo "src: Cleaning..."
	@rm -f *~ *.o tracker

help:
	@echo "Usage:"
	@echo "  make [all]\t\tBuild the software"
	@echo "  make clean\t\tRemove all files generated by make"
	@echo "  make help\t\tDisplay this help"
