install cURL, OpenSSL, SSH and then Git
                                                                                               git config --global http.sslVerify false

#a00
-> git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/
-> make & make modules_install
-> cp arch/x86/boot/bzImage /boot/vmlinuz-torvalds-6.9
-> vim /boot/grub/grub.cfg
menuentry "GNU/Linux, Linux torvalds" {
        linux   /boot/vmlinuz-torvalds root=/dev/sda2 ro
} 

#a01

##Makefile
obj-m += main.o

all:
        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

##main.c
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("MIT");
MODULE_AUTHOR("jperrier");
MODULE_DESCRIPTION("Hello World module");

int init_module(void)
{
        printk(KERN_INFO "Hello world !\n");
        return 0;
}

void cleanup_module(void)
{
        printk(KERN_INFO "Cleaning up module.\n");
}

insmod main.ko
dmesg | tail -1
rmmod main.ko

#a02
-> add -thor_kernel to EXTRAVERSION
-> use git format-patch -1 HEAD
-> cp arch/x86/boot/bzImage /boot/vmlinuz-torvalds
-> boot on it and get /var/log/kern.log

#a03
/usr/src/kernel-6.4.12/scripts/checkpatch.pl module.c -no-tree -file --strict

#a04
-> rules /etc/udev/rules.d
ACTION=="add", SUBSYSTEM=="usb", ATTR{bInterfaceProtocol}=="01" RUN+="insmod /root/ft_penguin//a04/keyboard_dd.ko"



