#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>  
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int slice_string(char* st, int start_index, int end_index, char* buf) {
    int i;
    for (i = start_index; i < end_index; i++) {
        buf[i - start_index] = st[i];
    }
    buf[i - start_index] = 0;
    return 1;
}


int check_key(char* st, int len) {
    if (len != 12) {
        return 0;
    }

    char slice_array[3][5];
    int i;
    for (i = 0; i < 3; i++) {
        slice_string(st, i * 4, i * 4 + 4, slice_array[i]);
    }

    int xor_increase = 0x4f, xor_sum = 0;
    for (i = 0; i < 4; i++) {
        xor_increase += 4;
        slice_array[0][i] = slice_array[0][i] ^ xor_increase;
        xor_sum += slice_array[0][i] - 0x30;
    }


    if (strcmp(slice_array[0], slice_array[1]) != 0) {
        return 0;
    }

    int second_xor_sum = xor_sum + 0xe2;
    char* cmp_3 = (char *)malloc(sizeof(int) + 10);
    sprintf(cmp_3, "%X%X", (BYTE)xor_sum, (BYTE)second_xor_sum);
    if (strcmp(cmp_3, slice_array[2]) != 0) {
        return 0;
    }
	printf("%s%s%s\n",slice_array[0],slice_array[1],slice_array[2]);

    return 1;
}


int main(){
	char *st = "c96a0nm>896B";
	int len = 12;
	printf("%d",check_key(st,len));
}
