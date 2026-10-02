CC      ?= cc
CFLAGS  ?= -std=c11 -O2 -Wall -Wextra -D_DEFAULT_SOURCE
BUILD   ?= build
BIN_DIR ?= bin

ifeq ($(OS),Windows_NT)
  EXE := .exe
else
  EXE :=
endif

TARGET = $(BIN_DIR)/snl$(EXE)

.PHONY: all clean

all: $(TARGET)

$(TARGET): src/main.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ src/main.c
	@echo "snl written to $(TARGET)"

$(BIN_DIR):
ifeq ($(OS),Windows_NT)
	@powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "if (-not (Test-Path '$(BIN_DIR)')) { New-Item -ItemType Directory -Path '$(BIN_DIR)' | Out-Null }"
else
	mkdir -p $(BIN_DIR)
endif

clean:
ifeq ($(OS),Windows_NT)
	@powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "if (Test-Path '$(BIN_DIR)') { Remove-Item -Path '$(BIN_DIR)' -Recurse -Force }"
else
	rm -rf $(BIN_DIR)
endif
