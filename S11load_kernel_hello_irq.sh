#!/bin/bash
echo ====my load script arg=$1========
if [ "$1" = "start" ]
then
	echo "start"
	insmod /lib/modules/`uname -r`/extra/kernel_hello_irq.ko prints_count=5
fi
