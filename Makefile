SHELL = /bin/bash
ifeq ($(PARAM_FILE), )
	PARAM_FILE:=$(TOP_DIR)/middleware/$(shell echo $(MW_VER))/Makefile.param
	include $(PARAM_FILE)
endif

CHIP_ARCH_L ?= $(shell echo $(CHIP_ARCH) | tr A-Z a-z)

include Makefile.releaseList

MW_SAMPLE_COMMON_PATH=$(TOP_DIR)/middleware/$(MW_VER)/sample/common
include $(BUILD_PATH)/.config
include $(MW_SAMPLE_COMMON_PATH)/../Kbuild

SDIR = $(PWD)/isp_daemon_tool/src
TMP_FOLDER = tmp
ISP_DIR = $(TOP_DIR)/middleware/$(MW_VER)/modules/isp
ISP_COMMON_DIR = $(ISP_DIR)/common
CVI_RTSP_PATH = $(TOP_DIR)/cvi_rtsp

INCS = -I$(KERNEL_INC) -I$(MW_INC) -I$(ISP_INC) -I$(MW_SAMPLE_COMMON_PATH)
INCS += -I$(CVI_RTSP_PATH)/include/cvi_rtsp
INCS += -I$(PWD)/isp_daemon_tool/include
INCS += -I$(ISP_COMMON_DIR)/clog
INCS += -I$(ISP_COMMON_DIR)/raw_dump/inc
INCS += -I$(ISP_COMMON_DIR)/raw_dump/src
INCS += -I$(ISP_COMMON_DIR)/raw_replay_offline
INCS += -I$(ISP_DIR)/$(CHIP_ARCH_L)/isp-daemon2/inc
INCS += -I$(ISP_DIR)/$(CHIP_ARCH_L)/isp-daemon2/prebuilt/include/cvi_json-c
INCS += -I$(TOP_DIR)/libsophon/bmlib/include
INCS += -I$(TOP_DIR)/libsophon/tpu-runtime/include
INCS += -I$(TOP_DIR)/tdl_sdk/include

COBJS = $(patsubst $(SDIR)/%.c, $(TMP_FOLDER)/%.o, $(wildcard $(SDIR)/*.c))
CDEPS = $(patsubst $(SDIR)/%.c, $(TMP_FOLDER)/%.d, $(wildcard $(SDIR)/*.c))
COBJS += $(patsubst $(SDIR)/module/%.c, $(TMP_FOLDER)/module/%.o, $(wildcard $(SDIR)/module/*.c))
CDEPS += $(patsubst $(SDIR)/module/%.c, $(TMP_FOLDER)/module/%.d, $(wildcard $(SDIR)/module/*.c))

# mw sample common
SAMPLE_SRCS = $(wildcard $(MW_SAMPLE_COMMON_PATH)/*.c)
SAMPLE_OBJS = $(SAMPLE_SRCS:.c=.o)
SAMPLE_DEPS = $(SAMPLE_SRCS:.c=.d)
PANEL_INC = $(TOP_DIR)/middleware/$(MW_VER)/component/panel/$(shell echo $(CVIARCH) | tr A-Z a-z)
MW_SAMPLE_CFLAGS = -I$(MW_SAMPLE_COMMON_PATH) -I$(MW_INC) -I$(ISP_INC) -I$(KERNEL_INC) -I$(PANEL_INC)
MW_SAMPLE_CFLAGS += -I$(MW_PATH)/component/isp/common -I$(MW_PATH)/3rdparty/inih
MW_SAMPLE_CFLAGS += -MMD -MP
MW_SAMPLE_CFLAGS += $(KBUILD_DEFINES)

AI_SDK_PATH = $(OUTPUT_DIR)/tpu_$(SDK_VER)/cvitek_ai_sdk
TPU_SDK_PATH = $(TOP_DIR)/libsophon/install/libsophon-0.4.9/lib

AI_SDK_PATH_EXIST = $(shell if [ -d $(AI_SDK_PATH) ]; then echo "exist"; else echo "noexist"; fi)
TPU_SDK_PATH_EXIST = $(shell if [ -d $(TPU_SDK_PATH) ]; then echo "exist"; else echo "noexist"; fi)

TARGET = isp_tool_daemon
OUT_TARBALL = isp_tool_daemon.tar.gz

PKG_CONFIG_PATH = $(MW_PATH)/pkgconfig
REQUIRES = cvi_common cvi_sample cvi_vdec cvi_misc
MW_LIBS = $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs --define-variable=mw_dir=$(MW_PATH) $(REQUIRES))

LIBS += $(MW_LIBS) -latomic
LIBS += -lcvi_bin -lini
LIBS += -lcvi_ispd2
LIBS += -lraw_dump
LIBS += -ldl -lcvi_rtsp
LIBS += -lraw_replay_offline
LIBS += -lteaisp -lbmlib -lbmrt
LIBS += -lsns_full

LOCAL_CFLAGS = $(DEFS) $(INCS) -DSDK_VER=$(SDK_VER)
LOCAL_CFLAGS += -MMD -MP
LOCAL_CFLAGS += -DENABLE_TEAISP_PQ -DENABLE_FACE_AE
LOCAL_LDFLAGS = $(LIBS) -lm -lpthread
LOCAL_LDFLAGS += -L$(CVI_RTSP_PATH)/install/lib
LOCAL_LDFLAGS += -L$(TPU_SDK_PATH)
LOCAL_LDFLAGS += -L$(ISP_DIR)/$(CHIP_ARCH_L)/isp-daemon2/prebuilt/$(SDK_VER)

.PHONY: clean all package test
all: prepare $(TARGET)

prepare:
	-@mkdir -p $(TMP_FOLDER)
	-@mkdir -p $(TMP_FOLDER)/module
	@cp $(MW_SNS_INC)/sensor_cfg/*.h $(MW_INC)

$(TMP_FOLDER)/%.o: $(SDIR)/%.c | prepare
	$(CC) $(CFLAGS) $(LOCAL_CFLAGS) -c $< -o $@
	@echo [$(notdir $(CC))] $(notdir $@)

$(MW_SAMPLE_COMMON_PATH)/%.o: $(MW_SAMPLE_COMMON_PATH)/%.c
	$(CC) $(CFLAGS) $(MW_SAMPLE_CFLAGS) -c $< -o $@
	@echo [$(notdir $(CC))] $(notdir $@)

$(TARGET): $(COBJS) $(SAMPLE_OBJS) | prepare
	$(CC) -o $@ $(COBJS) $(SAMPLE_OBJS) $(ELFFLAGS) $(LOCAL_LDFLAGS)
	@echo -e $(BLUE)[LINK]$(END)[$(notdir $(CXX))] $(notdir $@)

$(TMP_FOLDER)/%.o: $(CTRL_SRC_DIR)/%.c | prepare
	$(CC) $(CFLAGS) $(LOCAL_CFLAGS) $(LOCAL_CPPFLAGS) -c $< -o $@
	@echo [$(notdir $(CXX))] $(notdir $@)

package: $(TARGET)
	@rm -rf install/*
	@mkdir -p install/lib
	@cp $(TARGET) install/
	@cp isp_daemon_tool/CviIspTool.sh install/
	@cp isp_daemon_tool/daemon_cfg/* install/
	@cp res/* install/ -rf
	@cp isp_test/scripts/*.sh install/

	@mkdir install/lib/ai
ifeq "$(AI_SDK_PATH_EXIST)" "noexist"
	$(info cvitek_ai_sdk not exist, please export TPU_REL=1 run build_all !!)
else ifeq "$(TPU_SDK_PATH_EXIST)" "noexist"
	$(info cvitek_tpu_sdk not exist, please export TPU_REL=1 run build_all !!)
else
	@cp $(AI_SDK_PATH)/lib/*.so* install/lib/ai -rf
	@cp $(TPU_SDK_PATH)/lib/*.so* install/lib/ai -rf
	@rm install/lib/ai/libcvi_rtsp.so
endif

	@for so in $(file); \
	do \
		cp -Lrf $$so install/lib > /dev/null 2>&1; \
	done

	@tar -zcf $(OUT_TARBALL) install

clean:
	@cd isp_test; make clean
	@rm -f $(COBJS) $(SAMPLE_OBJS) $(CDEPS) $(TARGET) $(SAMPLE_DEPS)
	@rm -rf install $(TMP_FOLDER)
	@rm -rf $(OUT_TARBALL)
	@rm -f $(MW_INC)/sensor_cfg.h

test:
	@echo "mw sample objectd: " $(SAMPLE_OBJS)
	@echo "mw sample cflags: "  $(MW_SAMPLE_CFLAGS)

-include $(CDEPS) $(SAMPLE_DEPS)
