#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
int SS(int n,int Mas[n]){ // Функция сортировки слиянием 
    if (n<2){
    	return Mas; // возвращает массив из одного элемента
	}else{
		int ArrL[n/2]; // создание левой части массива
		for (int i = 0; i<n/2; i++){
        	ArrL[i] = Mas[i];
    	}
		int *L = SS(n/2, ArrL); // вызов функции и принятие отсортированной левой части 
		for (int i = 0; i<n/2; i++){
        	ArrL[i] = *(L + i); // запись в старый массив, чтобы легче было работать с данными(перезаписывать)
    	}
		int ArrR[n - n/2]; // Схожим образом делаем с правой частью
		for (int i = n/2; i<n; i++){
        	ArrR[ i - n/2 ] = Mas[i];
        	
    	}
    	int *R = SS(n-n/2,ArrR);
    	for (int i = 0; i<n/2; i++){
        	ArrR[i] = *(R + i);
    	}
		int Control = 0; // Сортировка левой и правой части
    	if (n/2 != 1){
    		while (Control != 1 ){
    		int control = 1;
    		for (int i = 0; i<n/2-1; i++){
    			if ( ArrL[i] > ArrL[i+1]){
    				int mem = ArrL[i+1];
    				ArrL[i+1] = ArrL[i];
    				ArrL[i] = mem;
    				control = 0;
				}
			}
			if (control == 1) Control = 1;
			}
		}
		Control = 0;
		if (n-n/2 != 1){
			while (Control != 1 ){
    		int control = 1;
    		for (int i = 0; i<n - n/2-1; i++){
    			if ( ArrR[i] > ArrR[i+1]){
    				int mem = ArrR[i+1];
    				ArrR[i+1] = ArrR[i];
    				ArrR[i] = mem;
    				control = 0;
				}
			}
			if (control == 1) Control = 1;
			}
		}
		for (int i = 0; i < n; i++){ // Соединение 2 массивов
			if (i < n/2){
				Mas[i] = ArrL[i];
			}else{
				Mas[i] = ArrR[i-n/2];
			}
		}
		Control = 0; // Их сортировка
		while (Control != 1 ){
    		int control = 1;
    		for (int i = 0; i<n-1; i++){
    			if ( Mas[i] > Mas[i+1]){
    				int mem = Mas[i+1];
    				Mas[i+1] = Mas[i];
    				Mas[i] = mem;
    				control = 0;
				}
			}
			if (control == 1) Control = 1;
		}	
	}
    return Mas;
}
int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Rus"); // Русский язык
    int kol; // Объявление переменной, хранящей в себе количество элементов в массиве
	printf("Введите количество элементов в массиве\n"); 
	scanf("%d", &kol);
	while (kol == 0){ // проверка ввода данных
		printf("Значение не подходит для массива, введите другой размер\n");
		scanf("%d", &kol);
	}
	kol = kol*2;
    int Numbers[kol] ; // Первоначальный массив
	int index = 0;
	srand(time(NULL)); // Обращение к функции псевдорандомных чисел по времени
    while (index < kol){ //Ввод чисел
        Numbers[index] = rand()%(kol);
		index++;
    }
    int *a = SS(kol ,Numbers); // Обращение к функции
    printf("Введите число, которое нужно найти\n");
    int number = 0;
    scanf("%d", &number);
    for (int i = 0; i<kol; i++){
        printf("<индекс '%d' : %d>\n",i, *(a + i));// Вывод массива через указатель
        Numbers[i] = *(a + i);
    }
    int L = 0; //  Индекс левой границы бинарного поиска
    int R = kol-1;// Индекс правой границы
    int M = kol/2; // Индекс середины
    int KolProv = 1;// Счётчик чтобы выйти из цикла ниже
    int rav = 0; // проверка на существование числа в массиве
    if (number == Numbers[L]){ // Проверка начальных границ
    	M = L;
    	rav = 1;
	}else if (number == Numbers[R]){
    	M = R;
    	rav = 1;
	}else{
		while(KolProv != 1001){ // Цикл поиска числа
		KolProv++;
        if (number > Numbers[M]) {
        	L = M; 
        	M = L + (R-L)/2;
		} else if (number < Numbers[M]){
			R = M;
			M = L + (R-L)/2;
		} else if ( Numbers[M] == number){
			if ( Numbers[M-1] == number){
				M = M-1;
				rav = 1;
			}else{
				rav = 1;
				break;
			}
		} else {
			break;
		} 
    	}
	}
    if (rav == 1 ) printf("Индекс искомого элемента - %d\n", M);
    else printf("Числа в массиве нет\n");
	system("pause");
	return 0;
}
