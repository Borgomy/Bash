#!/bin/bash
if [ -z $1 ] # узнаём полный путь до папки с индивидуальным заданием
then read -p "input name dir with task:" direction
else direction=$1
fi

if mkdir "ET" # создаём папку для общего задания с зашифрованным индивидуальм
then echo Dir create +
else echo Dir not create - ; rm -r ET ; exit
fi

if cd "ET"
then echo Cd is Ok +
else echo Cd is not ok - ; rm -r ET ; exit
fi

if $(tar cf Индивидуальное_задание.tar $direction) # архивируем
then echo Tar IndTask +
else echo Tar IndTask - ; cd ../ ; rm -r ET ; exit
fi

numberKey=1

if $(mkdir Key.$numberKey) # создаём папку для первого ключа и его частей
then echo Dir create +
else echo Dir not create - ; cd ../ ; rm -r ET ; exit
fi

if cd Key.$numberKey
then echo Cd is Ok + ;
else echo Cd is not ok - ; cd ../ ; rm -r ET ; exit
fi

if $(../../createKey.exe) # создаём ключ и его части 
then echo "Key.$numberKey" +
else echo "Key.$numberKey" - ; cd ../../ ; rm -r ET ; exit
fi

./../../Magma.exe -i ../Индивидуальное_задание.tar -k key.key -c e -o ../Индивидуальное_задание  # шифруем индивидуальное задание

rm key.key
rm ../Индивидуальное_задание.tar

cd ../

for  ((indexKey=2; indexKey < 6; indexKey++))
do
	if $(tar cf Key.$numberKey.tar Key.$numberKey) # архивируем  
	then echo Tar IndTask +
	else echo Tar IndTask - ; cd ../ ; rm -r ET ; exit
	fi

	rm -r "Key.$numberKey"

	if $(mkdir Key.$indexKey) # создаём папку для следующего ключа и его частей
	then echo Dir create +
	else echo Dir not create - ; cd ../ ; rm -r ET ; exit
	fi

	if cd Key.$indexKey
	then echo Cd is Ok +
	else echo Cd is not ok - ; cd ../ ; rm -r ET ; exit
	fi

	if $(../../createKey.exe) # создаём ключ и его части 
	then echo "Key.$indexKey" +
	else echo "Key.$indexKey" - ; cd ../../ ; rm -r ET ; exit
	fi

./../../Magma.exe -i ../Key.$numberKey.tar -k key.key -c e -o ../Key.$numberKey  # шифруем индивидуальное задание
	
	rm key.key
	rm ../Key.$numberKey.tar
	cd ../

	numberKey=$indexKey
done
