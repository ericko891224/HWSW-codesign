#include<io51.h>

void init(void){
	P0=0;
	P1=0;
	P2=1;
	P3=0;
}

int main(void){
	unsigned int i;
	// SAO JIE CHEN IS HANDSOME	
	int sentence[24] = {18, 0, 14, 26, 9, 8, 4, 26, 2, 7, 4, 13, 26, 8, 18, 26, 7, 0, 13, 3, 18, 14, 12, 4};
	init();
	
	for(i=0;i<26;i++){
		P3 = 1;
		P0 = i;
		P2 = 1;
		while (P2) {}
		P3 = 0;
	}

	for(i=0;i<24;i++){
		P3 = 1;
		P0 = sentence[i];
		P2 = 1;
		while (P2) {}
		P3 = 0;
	}
}