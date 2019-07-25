#ifeq ($(KERNELRELEASE),)
#export MMZ_SRC_BASE=$(PWD)
#endif
DATE = $(shell date '+%y%m%d_%H%M%S')

ifeq ($(PARAM_FILE), )
		PARAM_FILE:=../../linksdk/mpp/Makefile.param
		include $(PARAM_FILE)
endif
obj-m := raptor3.o
raptor3-objs := raptor3_drv.o video_output.o video_input.o video_auto_detect.o clock.o coax_protocol.o motion.o audio.o video_eq.o

EXTRA_CFLAGS+=-I$(PWD)/../gpio-i2c 

ifeq ($(HIARCH),hi3520D)
EXTRA_CFLAGS += -DHI_GPIO_I2C
EXTRA_CFLAGS += -I$(PWD)/../gpio_i2c
EXTRA_CFLAGS += -DSUPPORT_HI3520D
endif
ifeq ($(HIARCH),hi3521a)
EXTRA_CFLAGS += -DHI_CHIP_HI3521A
#EXTRA_CFLAGS += -DI2C_INTERNAL 
EXTRA_CFLAGS += -DHI_I2C
EXTRA_CFLAGS += -I$(REL_INC)
EXTRA_CFLAGS += -I$(PWD)/../hi_i2c
EXTRA_CFLAGS += $(DRV_CFLAGS)
EXTRA_CFLAGS += -DSUPPORT_3520D_6158C
endif
ifeq ($(HIARCH),hi3531)
EXTRA_CFLAGS += -DHI_GPIO_I2C
EXTRA_CFLAGS += -I$(PWD)/../gpio_i2c_8b
endif
ifeq ($(HIARCH),hi3531a)
EXTRA_CFLAGS += -DHI_CHIP_HI3531A
EXTRA_CFLAGS += -DI2C_INTERNAL
EXTRA_CFLAGS += -I$(REL_INC)
EXTRA_CFLAGS += $(DRV_CFLAGS)
endif
EXTRA_CFLAGS += -Wframe-larger-than=4096

VIDEO_DECODER_PATH:=$(PWD)/

# add Show/hide NVP6134(C) function (2016-09-10, sat)
EXTRA_CFLAGS += -D__DEC_HIDE_SHOW_FUNCTION

# add enhancing video quality(AHD 4M/5M) (2016-11-23, wed)
EXTRA_CFLAGS += -D__ENHANCING_VIDEO_QUALITY_OF_AHD

EXTRA_CFLAGS += -I$(VIDEO_DECODER_PATH)

EXTRA_CFLAGS += -Wno-error=date-time       # Fix compile error on gcc 4.9 and later   不做错误报出
EXTRA_CFLAGS +=-Wno-date-time     #不做警告报出
default:
	@make -C $(LINUX_ROOT) M=$(PWD) modules
	rm *.o .*.cmd
clean: 
	@make -C $(LINUX_ROOT) M=$(PWD) clean 


