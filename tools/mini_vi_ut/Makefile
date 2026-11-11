# Standalone Makefile: isp_ut — merged VI+ISP unit test.
# Supports two modes via command line argument:
#   ./isp_ut pattern   (VI pattern generator, no MIPI, no sensor)
#   ./isp_ut sensor    (real sensor with MIPI, default)
#
# Build: make all
# Install: installs to ../install/

SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
	PARAM_FILE:=$(TOP_DIR)/cvi_mpi/Makefile.param
	include $(PARAM_FILE)
endif
include $(BUILD_PATH)/.config

SDIR = $(CURDIR)

CHIP_ARCH_L ?= $(shell echo $(CHIP_ARCH) | tr A-Z a-z)
ISP_INC := $(MW_PATH)/include/isp
ISPD2_JSON_INC := $(MW_PATH)/modules/isp/$(CHIP_ARCH_L)/isp-daemon2/prebuilt/include/cvi_json-c

# ---- sources ---------------------------------------------------------------
SRCS = $(SDIR)/isp_ut_wrapper.c $(SDIR)/isp_pattern_impl.c $(SDIR)/isp_sensor_impl.c $(SDIR)/isp_pattern_isp.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

TARGET = isp_ut

# ---- includes --------------------------------------------------------------
INCS = -I$(MW_INC) -I$(MW_INC)/sensor -I$(MW_PATH)/modules/vi/include/
INCS += -I$(ISP_INC)
INCS += -I$(MW_PATH)/modules/isp/$(CHIP_ARCH_L)/isp-daemon2/inc
INCS += -I$(ISPD2_JSON_INC)
INCS += -I$(SDIR)

# ---- libs ------------------------------------------------------------------
ISP_LIBS = -lae -lawb -laf -lcvi_ispd2 -lisp -ldl
ifeq ($(OS_TYPE), LINUX)
	ISP_LIBS += -lisp_algo
endif

VI_LIBS = -lvi -lvpss -lcvi_bin -lini -lsns_full -lsensor -lgdc -lsys
VI_LIBS += $(ISP_LIBS)

ccflags-y += $(INCS)
ccflags-y += -ffunction-sections -fdata-sections

ldflags-y += -lpthread -lm -latomic -lmipi

ifneq ($(CONFIG_ENABLE_SDK_ASAN), y)
ELFFLAGS += -static
endif

.PHONY : clean all install

INSTALL_DIR = ../install

all : $(TARGET) install

$(SDIR)/%.o: $(SDIR)/%.c
	@$(CC) $(DEPFLAGS) $(CFLAGS) $(ccflags-y) -o $@ -c $<
	@echo [$(notdir $(CC))] $(notdir $@)

$(TARGET) : $(OBJS) $(MW_LIB)/libsys.a
	@$(CXX) -o $@ -Wl,--start-group $(OBJS) $(MW_LIB)/libsys.a $(VI_LIBS) -Wl,--end-group $(ELFFLAGS) $(ldflags-y)
	@echo [LINK] $(notdir $@)

install: $(TARGET)
	@mkdir -p $(INSTALL_DIR)
	@cp $(TARGET) $(INSTALL_DIR)/
	@echo "Installed $(TARGET) to $(INSTALL_DIR)/"

clean:
	@rm -f $(OBJS) $(DEPS) $(TARGET)
