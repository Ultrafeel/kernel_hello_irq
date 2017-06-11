obj-m := kernel_hello_irq.o
kernel_hello_irq-objs := timer.o

CFLAGS_timer.o := -DDEBUG
KERNEL_VERSION:=4.9.6
#$(shell uname -r)
#

KERNEL_SRCS:=../fuse/buildroot-2017.02.2/output/build/linux-4.9.6

#/lib/modules/$(KERNEL_VERSION)/build
#/home/unencr/Prog_projects/fuse/Linux_kernel/linux1
LINUXDIR=KERNEL_SRCS
BUILDROOT1=/home/unencr/Prog_projects/fuse/buildroot-2017.02.2

TARGETDIR=target_bin

#$(PWD)/../buildroot-2017.02.2
BUILDROOT1_BIN=$(BUILDROOT1)/output/host/usr/bin

#/home/unencr/Prog_projects/fuse/buildroot-2017.02.2
#arm-arm926t-linux-gnueabihf
#arm-buildroot-linux-uclibcgnueabi-
MAKE_OPTIONS=ARCH=arm CROSS_COMPILE=arm-linux- PATH=$(BUILDROOT1_BIN):$(PATH)
#arm-arm926t-linux-gnueabif-
#arm-cortex_a8-linux-gnueabihf-
#cd $(BUILDROOT1_BIN) 	SET PATH=$(BUILDROOT1_BIN):$(PATH)
PATH:=$(BUILDROOT1_BIN):$(PATH)

all: BRBIN
	make -C $(KERNEL_SRCS) $(MAKE_OPTIONS) M=$(PWD) modules
	mkdir -p ./$(TARGETDIR)/lib/modules/$(KERNEL_VERSION)/
	cp kernel_hello_irq.ko ./$(TARGETDIR)/lib/modules/$(KERNEL_VERSION)/
	mkdir -p ./$(TARGETDIR)/etc/init.d/
	cp S11load_kernel_hello_irq.sh ./$(TARGETDIR)/etc/init.d/
	mkdir -p ./$(TARGETDIR)/root/
	cp test.sh ./$(TARGETDIR)/root/

BRBIN:
	echo MAKE_OPTIONS = $(MAKE_OPTIONS)

clean:
	make -C $(KERNEL_SRCS)  $(MAKE_OPTIONS) M=$(PWD) clean
	-rm  -rfv  ./$(TARGETDIR)
