#!/bin/bash

for ((variant=1; variant < 26; variant++))
do
	echo $(cp	/mnt/c/Users/Aleks/Desktop/Организация\ доклада/Задание-Вариант$variant ./Индивидуальное_Задание/)
	./script_Create_Tesk.sh ../Индивидуальное_Задание
	echo $?
	cp -r ../Magma ./ET
	ls ./ET
	echo $(tar cf Задание-Вариант$variant.tar ./ET)
	rm -r ./ET
	ls ./Индивидуальное_Задание/
	echo $(rm ./Индивидуальное_Задание/Задание-Вариант$variant)
done

