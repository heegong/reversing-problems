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
        free(cmp_3);
        return 0;
    }

    free(cmp_3);

    return 1;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = 0;
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
                switch (HIWORD(wParam)){
                    case BN_CLICKED:
                        char buf[256];
                        GetDlgItemText(hwnd, 0, buf, 13);
                        int check = check_key(buf, 12);
                        if (check) {
                            MessageBoxA(0, "Correct", "I am De", 0);
                        }
                        else {
                            MessageBoxA(0, "Wrong", "I am De", 0);
                        }
                        break;
                    }
            }
            break;

        default:
            result = DefWindowProc(hwnd, msg, wParam, lParam);
            break;
    }
    return result;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE phInstance, LPSTR CmdLine, int CmdShow){

    LPSTR className = (char *)"Window";

    WNDCLASS wc = { 0 };
    wc.lpszClassName = className;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;

    RegisterClass(&wc);


    int x_size = 300;
    int y_size = 300;

    HWND hwnd = CreateWindow(className, "Keygen_heegong", WS_OVERLAPPEDWINDOW, 0, 0, x_size, y_size, NULL, NULL, hInstance, 0);
    if (hwnd == NULL) {
        exit(-1);
    }
    HWND TextBox = CreateWindow("edit", "input....", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 0, 30, x_size, 20, hwnd, (HMENU)0, NULL, NULL);

    int button_x = (int)(x_size / 2) - (int)(100 / 1.6);
    int button_y = (int)(y_size / 4) * 2;
    CreateWindow(TEXT("button"), TEXT("push me"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD, button_x, button_y, 100, 50, hwnd, (HMENU)1, 0, NULL);




    ShowWindow(hwnd, CmdShow);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}