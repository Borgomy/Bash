#!/bin/bash

createKey () # $1 name file with full key
{
	for ((indexByte=0; indexByte < 8; indexByte++))
	do
		cat FileWithByteNumber$indexByte >> $1
	done
	return 0;
}

decryptionIndTask ()
{
	cd Key.1
	touch key.key
	
	if createKey key.key
	then echo 'createKey +'
	else echo 'createKey -' ; exit
	fi 
	
	./../Magma.exe -i ../Индивидуальное_задание -k key.key -c d -o ../Индивидуальное_задание.tar
	if [[ $? -eq 0 ]]
	then echo Magma +
	else echo Magma - ; exit
	fi 

	cd ../
	rm Индивидуальное_задание
	tar xf Индивидуальное_задание.tar
	rm Индивидуальное_задание.tar
	return 0;
}

for ((numberKey=5; numberKey > 1; numberKey--))
do
	cd Key.$numberKey
	touch key.key
	
	createKey key.key
 
	
	./../Magma.exe -i ../Key.$(($numberKey-1)) -k key.key -c d -o ../Key.$(($numberKey-1)).tar
	if [[ $? -eq 0 ]]
	then echo Magma +
	else echo Magma - ; exit
	fi 
	
	echo $numberKey # самопроверка

	cd ../
	rm Key.$(($numberKey-1))
	tar xf Key.$(($numberKey-1)).tar
	rm Key.$(($numberKey-1)).tar
done

decryptionIndTask

exit 0
