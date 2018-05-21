
#include "func.h"

#include <ncurses.h>
// int current_element=0; //номер текущего элемента
// string MyNote[256], Status;
// int str_count;
// int curposX,curposY;
// const char*  F_Name;
//главная функция
int main (int argc, char *argv[])
{
int current_element; //номер текущего элемента
string MyNote[256], Status;
int str_count;
int curposX,curposY;
const char*  F_Name;
//всё инициализируем
  initscr();
  setlocale(LC_ALL, "Russian");// Почему-то не работает русский.
  start_color();
  keypad (stdscr, TRUE); 
  noecho();

MEVENT event;
//создаем цветовые пары  
  init_pair (1, COLOR_RED, COLOR_BLACK);
  init_pair (2, COLOR_WHITE, COLOR_BLACK);
  init_pair (3,  COLOR_BLACK,   COLOR_GREEN);
  init_pair (4, COLOR_WHITE,   COLOR_BLUE);
  init_pair (5,  COLOR_WHITE,   COLOR_RED);
  
//текущий элемент сбрасываем в ноль
  current_element = 0;
//объявляем переменную для хранения нажатой клавиши
  int ch = 0;
//считываем клавиши, пока не будет нажата 'F3' (по F3 - выход) 
  while (ch != KEY_F(3))
        {
         //обновляем экран
         update_screen();
         mousemask (ALL_MOUSE_EVENTS, NULL);// инициализируем считывание мыши
         //ожидаем нажатия на клавишу и 
         //получаем её код в ch
         ch = getch();
 
         switch (ch)
                {
//если нажата "F1", то открываем файл
                 case KEY_F(1): 
                             Open_File();
                             break;
//если нажата "F2", то сохраняем файл
                 case KEY_F(2): 
			     File_Save();
                             break;
//если нажата "вверх"
                 case KEY_UP: 
			    if ( curposY>0)
				    curposY--;
                             break;
//если нажата "вниз"
                case KEY_DOWN: 
			    if ( curposY<str_count-1)
				    curposY++;
                             break;
//если нажата "влево"
                case KEY_LEFT: 
			    if ( curposX>0)
				    curposX--;
                             break;
//если нажата "вправо"
                case KEY_RIGHT: 
			    if ( curposX<strlen(MyNote[curposY].c_str()))// дальше конца строки не заходим
				    curposX++;
                             break;
//если нажата "BACKSPACE" - сделано!, но работает криво
                case KEY_BACKSPACE: 
			       for(int i=curposX;i<strlen(MyNote[curposY].c_str());i++)
				       MyNote[curposY][i]=MyNote[curposY][i+1];
                               curposX--;
		      //   MyNote[current_element]+=ch;	       
                                break;
//обработка нажатия Enter - только добавление строки в конец, так не раздвинет строки
                 case '\n': 
                               str_count++;
                               break;
// обработка нажатия мыши - не контролирует, какая клавиши нажата, только факт нажатия			       
	         case  KEY_MOUSE:
                               if (getmouse(&event) == OK)
			          if(event.y==LINES-2) // попали в функциональные клавиши
				     if(event.x<COLS/3) // F1
                                        Open_File();
				     if((event.x>COLS/3)&&(event.x<COLS*2/3)) // F2
                                        File_Save();
				     if(event.x>COLS*2/3) // F3
                                        ch = KEY_F(3);
				  else	 // просто установим курсор туда, куда попала мышь 
				   {                                        
                                    curposY=event.y;
			            curposX=event.x;
				   }
                              break;
// все остальные клавиши			      
		default  :
			      if(curposX<(strlen(MyNote[curposY].c_str())))// если в строке - то заменяем
				      MyNote[curposY][curposX]=ch;	      
			      else
				   MyNote[curposY]+=ch;   // в конец строки - дописываем
			       curposX++; 
                               break;
                }
        }     
  endwin();// разрушаем окно
  return 0;
}
