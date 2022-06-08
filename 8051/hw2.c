#include<io51.h>

void init(void){
	P0=0;
	P1=0;
	P2=0;
	P3=0;
}

int main(void){
	unsigned char i;
	
	init();
	
	for(i=0;i<26;i++){
		P3 = 1;
		P0 = i;
		P2 = 1;
		while (P2) {}
		P3 = 0;
	}
}