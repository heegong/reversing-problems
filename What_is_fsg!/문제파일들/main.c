#include <stdio.h>
#include <Windows.h>

int main(){
	int input_num;
	printf("unpack this program.^^^\n");
	printf("Input : ");
	scanf("%d",&input_num);
	
	if(input_num==525125){
		printf("\n\nProb{%d}\n\n",input_num);
	}
	else{
		printf("Wrong!!\n\n");
	}
	
	system("pause");
	return 0;
}
