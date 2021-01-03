CPPFLAGS=$(CPPFLAGS_EXTRA)
CFLAGS=-Wall -Wextra -Os -std=c11 -fno-exceptions -fno-asynchronous-unwind-tables -fno-lto $(CFLAGS_EXTRA)
LDFLAGS=-s $(LDFLAGS_EXTRA)
SIZE=size

BIN=unlzma_test

VPATH=$(dir $(abspath $(lastword $(MAKEFILE_LIST))))

all: $(BIN) size

%.os: CPPFLAGS_EXTRA=-DUNSAFE_TRUNCATED_INPUT
%.od: CPPFLAGS_EXTRA=-DDEBUG

unlzma_tiny.od unlzma_tiny.os: unlzma_tiny.c unlzma_tiny.h unlzma_tiny_config.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(BIN):	unlzma.o unlzma_tiny.od
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^

size: unlzma_tiny.os
	@echo
	@echo "*** binary size: $(shell $(SIZE) $^ -B | tail -n 1 | awk '{print $$4}') ***"

clean:
	-rm -f $(BIN) unlzma_tiny.os unlzma_tiny.od unlzma.o test-1.dec test-1.lzma test-2.lzma test-2.dec

test: $(BIN)
	xz --format=lzma -z -c $(BIN) > test-1.lzma
	./$(BIN) test-1.lzma test-1.dec $(shell stat -c "%s" $(BIN))
	cmp $(BIN) test-1.dec
	dd if=test-1.lzma of=test-2.lzma bs=2000 count=1
	@echo "Must failed:"
	! ./$(BIN) test-2.lzma test-2.dec $(shell stat -c "%s" $(BIN))
	@echo
	@echo "*** Test sucessful ***"

.PHONY: all size clean test
