#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
int SS(int n,int Mas[n]){ // ������� ���������� �������� 
    if (n<2){
    	return Mas; // ���������� ������ �� ������ ��������
	}else{
		int ArrL[n/2]; // �������� ����� ����� �������
		for (int i = 0; i<n/2; i++){
        	ArrL[i] = Mas[i];
    	}
		int *L = SS(n/2, ArrL); // ����� ������� � �������� ��������������� ����� ����� 
		for (int i = 0; i<n/2; i++){
        	ArrL[i] = *(L + i); // ������ � ������ ������, ����� ����� ���� �������� � �������(��������������)
    	}
		int ArrR[n - n/2]; // ������ ������� ������ � ������ ������
		for (int i = n/2; i<n; i++){
        	ArrR[ i - n/2 ] = Mas[i];
        	
    	}
    	int *R = SS(n-n/2,ArrR);
    	for (int i = 0; i<n/2; i++){
        	ArrR[i] = *(R + i);
    	}
		int Control = 0; // ���������� ����� � ������ �����
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
		for (int i = 0; i < n; i++){ // ���������� 2 ��������
			if (i < n/2){
				Mas[i] = ArrL[i];
			}else{
				Mas[i] = ArrR[i-n/2];
			}
		}
		Control = 0; // �� ����������
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
	setlocale(LC_ALL, "Rus"); // ������� ����
    int kol; // ���������� ����������, �������� � ���� ���������� ��������� � �������
	printf("������� ���������� ��������� � �������\n"); 
	scanf("%d", &kol);
	while (kol == 0){ // �������� ����� ������
		printf("�������� �� �������� ��� �������, ������� ������ ������\n");
		scanf("%d", &kol);
	}
	kol = kol*2;
    int Numbers[kol] ; // �������������� ������
	int index = 0;
	srand(time(NULL)); // ��������� � ������� ��������������� ����� �� �������
    while (index < kol){ //���� �����
        Numbers[index] = rand()%(kol);
		index++;
    }
    int *a = SS(kol ,Numbers); // ��������� � �������
    printf("������� �����, ������� ����� �����\n");
    int number = 0;
    scanf("%d", &number);
    for (int i = 0; i<kol; i++){
        printf("<������ '%d' : %d>\n",i, *(a + i));// ����� ������� ����� ���������
        Numbers[i] = *(a + i);
    }
    int L = 0; //  ������ ����� ������� ��������� ������
    int R = kol-1;// ������ ������ �������
    int M = kol/2; // ������ ��������
    int KolProv = 1;// ������� ����� ����� �� ����� ����
    int rav = 0; // �������� �� ������������� ����� � �������
    if (number == Numbers[L]){ // �������� ��������� ������
    	M = L;
    	rav = 1;
	}else if (number == Numbers[R]){
    	M = R;
    	rav = 1;
	}else{
		while(KolProv != 1001){ // ���� ������ �����
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
    if (rav == 1 ) printf("������ �������� �������� - %d\n", M);
    else printf("����� � ������� ���\n");
	system("pause");
	return 0;
}
