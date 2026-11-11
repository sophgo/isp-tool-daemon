SHELL = /bin/bash

# Get top directory
ifeq ($(TOP_DIR),)
	TOP_DIR := $(shell cd ../../.. && pwd)
endif

ifeq ($(PARAM_FILE), )
	PARAM_FILE:=$(TOP_DIR)/cvi_mpi/Makefile.param
	include $(PARAM_FILE)
endif

SDIR = .
TMP_FOLDER = tmp

COBJS = $(patsubst $(SDIR)/%.c, $(TMP_FOLDER)/%.o, $(wildcard $(SDIR)/*.c))
CDEPS = $(patsubst $(SDIR)/%.c, $(TMP_FOLDER)/%.d, $(wildcard $(SDIR)/*.c))

TARGET = file_transport_daemon

LOCAL_CFLAGS = -Wall -Wextra -O2 -std=c11
LOCAL_CFLAGS += -MMD -MP
LOCAL_LDFLAGS = -static

INSTALL_DIR = ../install

.PHONY: clean all install
all: prepare $(TARGET) install

prepare:
	@mkdir -p $(TMP_FOLDER)

$(TMP_FOLDER)/%.o: $(SDIR)/%.c
	@$(CC) $(CFLAGS) $(LOCAL_CFLAGS) -c $< -o $@
	@echo "[CC] $(notdir $@)"

$(TARGET): $(COBJS)
	@$(CC) -o $@ $(COBJS) $(LOCAL_LDFLAGS)
	@echo "[LINK] $(notdir $@)"

install: $(TARGET)
	@mkdir -p $(INSTALL_DIR)
	@cp $(TARGET) $(INSTALL_DIR)/
	@echo "Installed $(TARGET) to $(INSTALL_DIR)/"

clean:
	@rm -f $(COBJS) $(CDEPS) $(TARGET)
	@rm -rf $(TMP_FOLDER)

-include $(CDEPS)
