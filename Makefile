# Makefile - build chuong trinh nhan da thuc trong GF(2^n)

CC     = gcc
CFLAGS = -std=c99 -Wall -Wextra -O2

ifeq ($(OS),Windows_NT)
    EXE = .exe
    RM  = del /Q
else
    EXE =
    RM  = rm -f
endif

APP  = gfmul$(EXE)
TEST = test_gf$(EXE)

.PHONY: all test clean

all: $(APP)

$(APP): src/main.c src/gf.c src/gf.h
	$(CC) $(CFLAGS) -o $@ src/main.c src/gf.c

$(TEST): tests/test_gf.c src/gf.c src/gf.h
	$(CC) $(CFLAGS) -Isrc -o $@ tests/test_gf.c src/gf.c

test: $(TEST)
	"$(CURDIR)/$(TEST)"

clean:
	-$(RM) $(APP) $(TEST)