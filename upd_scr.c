#include "func.h"

#include <ncurses.h>

void update_screen()
{
int current_element; //номер текущего элемента
string MyNote[256], Status;
int str_count;
int curposX,curposY;
const char*  F_Name;
  erase(); //чистим экран
//выводим содержимое массива MyNote на экран построчно
  for (size_t i = 0; i < str_count; i++)
      {
           attron (COLOR_PAIR(2));
          // printw ("%s\n", MyNote[i].c_str());// можно так для строки
	   addstr(MyNote[i].c_str());
	   addstr("\n");
         //  printw ("%i\n", strlen(MyNote[i].c_str()));// или так для числа
           attroff (COLOR_PAIR(2));
      }

       // Подписываем функциональные клавиши внизу экрана
           attron (COLOR_PAIR(3));
        	mvaddstr(LINES-2, (COLS/3-sizeof("F1 - Open File"))/2,"F1 - Open File");
           attroff (COLOR_PAIR(3));
           attron (COLOR_PAIR(4));
	        mvaddstr(LINES-2, (COLS/3-sizeof("F2 - Save File"))/2+COLS/3,"F2 - Save File");
           attroff (COLOR_PAIR(4));
           attron (COLOR_PAIR(5));
         	mvaddstr(LINES-2, (COLS/3-sizeof("F3 - Close File"))/2+COLS*2/3,"F3 - Close File");
           attroff (COLOR_PAIR(5));
           mvaddstr(LINES-1,0,Status.c_str());
           move(curposY,curposX);// установка курсора на конец текста для дальнейшего ввода


}
