# Standalone Makefile: ispd2_client — JSON-RPC client for isp daemon2.
# Connects to a running ispd2 server (default 127.0.0.1:5566) to perform
# readall / writeall / dumpyuv / dumpraw / exportbin / importbin.
#
# This Makefile is built standalone via ./build.sh, OR as part of the
# isp-tool-daemon top-level build (which recurses into this directory
# via isp_test/Makefile).

SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
	PARAM_FILE:=$(TOP_DIR)/cvi_mpi/Makefile.param
	include $(PARAM_FILE)
endif
include $(BUILD_PATH)/.config

SDIR = $(CURDIR)

CHIP_ARCH_L ?= $(shell echo $(CHIP_ARCH) | tr A-Z a-z)
ISPD2_JSON_INC := $(MW_PATH)/modules/isp/$(CHIP_ARCH_L)/isp-daemon2/prebuilt/include/cvi_json-c

# ---- sources ---------------------------------------------------------------
CLI_SRCS = $(SDIR)/ispd2_client.c $(SDIR)/ispd2_rpc.c

SRCS = $(CLI_SRCS)
CLI_OBJS = $(CLI_SRCS:.c=.o)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

TARGET_CLI = ispd2_client

# ---- includes --------------------------------------------------------------
INCS = -I$(MW_INC)
INCS += -I$(ISPD2_JSON_INC)
INCS += -I$(SDIR)

# ---- libs ------------------------------------------------------------------
CLI_LIBS = -lcvi_json-c

ccflags-y += $(INCS)
ccflags-y += -ffunction-sections -fdata-sections

ldflags-y += -lpthread -lm -latomic

ifneq ($(CONFIG_ENABLE_SDK_ASAN), y)
ELFFLAGS += -static
endif

.PHONY : clean all install

INSTALL_DIR = ../install

all : $(TARGET_CLI) install

$(SDIR)/%.o: $(SDIR)/%.c
	@$(CC) $(DEPFLAGS) $(CFLAGS) $(ccflags-y) -o $@ -c $<
	@echo [$(notdir $(CC))] $(notdir $@)

$(TARGET_CLI) : $(CLI_OBJS)
	@$(CXX) -o $@ -Wl,--start-group $(CLI_OBJS) $(CLI_LIBS) -Wl,--end-group $(ELFFLAGS) $(ldflags-y)
	@echo [LINK] $(notdir $@)

install: $(TARGET_CLI)
	@mkdir -p $(INSTALL_DIR)
	@cp $(TARGET_CLI) $(INSTALL_DIR)/
	@echo "Installed $(TARGET_CLI) to $(INSTALL_DIR)/"

clean:
	@rm -f $(OBJS) $(DEPS) $(TARGET_CLI)
