#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>


int slice_int(char *st,int index1,int index2){
	char later_int[5];
	
	int i;
	for (i = index1;i < index2; i++){
		later_int[i-index1] = st[i];
	}
	return atoi(later_int);	
}





int index_xor(int *qu,int index){
	int array[10] = {0x213,0x514,0x1fa,0x124,0xa23,0xe93,0x892,0x952,0xd76,0x114};
	char char_qu[5];
	sprintf(char_qu, "%d", *qu);
	
	int i;
	for(i=0;i<index;i++){
		*qu = *qu ^ array[char_qu[i]-0x30];
	}
	return 0;
}



int main(){
	char pwd[10];

	
	
	puts("Hi, This is HeegongItSecure loginer\n\n");

	
	printf("What is your password >>> ");
	scanf("%s",pwd);
	
	if (pwd[4]!='-'){
		fail();
	}
	
	
	int first_slice = slice_int(pwd,0,4);
	int second_slice = slice_int(pwd,5,strlen(pwd));
	int qu = ((first_slice * 2)^0x23f);
	if (!qu%2){
		qu /= 2;
	}

	index_xor(&qu,4);
	
	char qu_st[6];
	char second_st[6];
	
	sprintf(qu_st,"%d",qu);
	sprintf(second_st,"%d",second_slice);
	int i;
	for(i=0;i<4;i++){
		if (qu_st[i]!=second_st[i]){
			fail();
		}
	}
	success();
	
	return 0;

}


int fail(){
	printf("You are not heegong\n");
	system("pause");
	exit(0);
}

int success(){
	printf("Oh, You are heegong!!\n");
	system("pause");
}
