#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <conio.h>
#include <Windows.h>


char exes[20][20];



int system_down() {
    system("pause");
    exit(0);
}


int exe_return(int *count) {
    struct _finddata_t fd;
    long handle;
    int result = 1;
    handle = _findfirst(".\\*.exe", &fd); 

    if (handle == -1){
        return 0;
    }


    int loop_count = 0;

    while (result != -1){
        strcpy(exes[loop_count], fd.name);      // 고치고
        result = _findnext(handle, &fd);
        loop_count++;
    }

    _findclose(handle);
    *count = loop_count;
    return 1;
}


int main() {
    char xor_key[256];
    printf("Hi, I'm heegong. If you input right answer, files will decrypt.\nInput key : ");
    scanf("%s", xor_key);
    fflush(stdin);
    int count;
    if (!exe_return(&count)) {
        system_down();
    }
    int i;
    for (i = 0; i < count; i++) {

        FILE* fp;
        fp = fopen(exes[i], "rb");
        if (fp == NULL) {
            system_down();
        }
        fseek(fp, 0, SEEK_END);             // 위치를 0으로
        long fp_size = ftell(fp);             // 총 사이즈 반환 

        rewind(fp);                             // 위치를 0으로

        char* buffer = (char*)malloc(fp_size);      // ftell반환값 만큼 동적 할당
        size_t result = fread(buffer, 1, fp_size, fp);

        int xor_key_len = strlen(xor_key),j;
        for (j = 0; j < fp_size; j++) {
            buffer[j] = (BYTE)buffer[j] ^ xor_key[j % xor_key_len] ^ 0x2f;
        }

        fclose(fp);

        FILE* fp2;
        fp2 = fopen(exes[i], "wb");
        if (fp2 == NULL) {
            system_down();
        }
        fwrite(buffer, 1, fp_size, fp2);
        
        fclose(fp2);
        free(buffer);


        printf("\nYour files are encrypted or decrypted.\n");
    }
}