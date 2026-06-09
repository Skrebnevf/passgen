CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -Werror -Wshadow -Wformat=2 -Wstrict-prototypes -Wmissing-prototypes -Wwrite-strings -Wpointer-arith -g
SRCDIR := src
OBJDIR := obj
BUILDDIR := bin

TARGET := $(BUILDDIR)/passgen

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
HEADERS := $(wildcard $(SRCDIR)/*.h)

all: $(TARGET)

$(TARGET): $(OBJS) | $(BUILDDIR)
	$(CC) $(OBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR) $(OBJDIR):
	mkdir -p $@

test: $(TARGET)
	$(CC) $(CFLAGS) tests/password_test.c src/password.c $(shell pkg-config --cflags --libs check) -o $(BUILDDIR)/password_test
	$(CC) $(CFLAGS) tests/helpers_test.c src/helpers.c $(shell pkg-config --cflags --libs check) -o $(BUILDDIR)/helpers_test
	./$(BUILDDIR)/password_test
	./$(BUILDDIR)/helpers_test

clean:
	rm -rf $(OBJDIR) $(BUILDDIR)

PREFIX ?= /usr/local
BINDIR := $(PREFIX)/bin

install: $(TARGET)
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)/passgen

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/passgen

.PHONY: all clean test install uninstall
