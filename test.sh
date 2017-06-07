#!/bin/sh

arg_class=kerncalc_arg-class
b=_________________

fail="$b fail"
right="$b success"
echo '+' op 
echo 12 > /sys/class/$arg_class/argument1
echo 23 > /sys/class/$arg_class/argument2
echo + > /dev/operand
res=`cat /dev/result`
if [ "$res" -eq 35 ]
then
	echo $right
else
	echo $fail
fi
