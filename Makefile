obj-m += kernel_module.o

build:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install: build
	sudo insmod kernel_module.ko
	gcc -o user_program user_program.c

reinstall: build
	sudo rmmod kernel_module
	sudo insmod kernel_module.ko
	gcc -o user_program user_program.c