#ifndef FUNC_H
#define FUNC_H
#include <string.h>
#include <ncurses.h>
#include <stdio.h>
//extern int current_element; //номер текущего элемента
struct My_Note {
	char note[256][1024];// собственно блокнот
	int str_count;// число строк в блокноте
        const char*  F_Name;// исходный файл
        const  char* Status;
               }; 
//extern int curposX,curposY;
struct My_Note  Open_File();
struct My_Note  File_Save(struct My_Note);
void update_screen(struct My_Note);
#endif
