EXEC=./jpeg_qt
SRCDIR=src
CFLAGS=-O3
LIB=-lpng -ltiff -ljpeg -lm
SRC_FILES=$(wildcard $(SRCDIR)/*.c)

all: $(EXEC)

$(EXEC): $(SRC_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LIB)

test: $(EXEC)
	@echo
	@echo test on roma.png
	@echo ================
	$(EXEC) roma.png
	@echo
	@echo test on roma95.jpg
	@echo ==================
	$(EXEC) roma95.jpg

clean:
	$(RM) -rf $(EXEC)

.PHONY: clean
