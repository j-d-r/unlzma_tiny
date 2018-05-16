PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

CPPFLAGS := -MMD #-DDEBUG
CFLAGS := -Wall -Wextra -g -Os -std=c11
LDFLAGS := 

OBJS = unlzma.o unlzma_tiny.o
BIN = unlzma

all: unlzma

$(BIN):	$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: $(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr $(BIN) $(OBJS) $(wildcard *.d)

### DEPS ###
$(OBJS): $(PROJECT_ROOT)Makefile
-include $(wildcard *.d)