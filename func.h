#ifndef FUNC_H
#define FUNC_H
#include <cstring>
#include <fstream>
#include <ncurses.h>
#include <clocale>
using namespace std;
extern int current_element=0; //номер текущего элемента
extern string MyNote[256], Status;
extern int str_count;
extern int curposX,curposY;
extern const char*  F_Name;
using namespace std;
//void update_screen(string* MyNote);
int Open_File();
int File_Save();
void update_screen();
#endif
