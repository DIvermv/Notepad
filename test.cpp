#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
//#include <vector>
#include <ncurses.h>
using namespace std;
int current_element=0; //номер текущего элемента
string MyNote[256], Status;
int str_count;
int curposX,curposY;
MEVENT event;
const char*  F_Name;


int Open_File()
{
//	const char* F_Name="zenity --file-selection";
       // const char* F_Name="text.txt";
          mvaddstr(0,0,"Input file name (default (press enter) - text.txt)");
       //	printw ("%s\n", "Input file name (default (press enter) - text.txt)");
	char str[100];
       getstr(str); //Считываем строку
        if(strlen(str)>3)
              F_Name=str;
	else
              F_Name="text.txt";
//	FILE * ptrFile = fopen("file.txt", "w");

   ifstream file(F_Name,ios::in); 
  // ifstream file("zenity --file-selection",ios::in); 
    if (!file) {// файл не открылся
     printw ("%s\n", "Do not open file. Press enter");
     getstr(str); //Считываем строку
	    return 0;
              }
    current_element=0;
   while(!file.eof())
   {
   // getline(file,MyNote[current_element]);
  file>> MyNote[current_element];
    current_element++;
   }
   str_count=current_element;
   file.close();

  curposX=0,curposY=str_count-1;
  Status="Open and read file ";
  for(int i=0;i<sizeof(F_Name);i++)
	  Status+=F_Name[i];
 // strcat(Status,F_Name);
  //     mvaddstr(LINES-1,0,"Open and read file text.txt");
return 0;
}


int File_Save()
{
ofstream file(F_Name,ios::out);
     current_element=0;
     while(current_element<str_count)
     {
      file<<MyNote[current_element]<<endl;
      current_element++;
     }
     file.close();
     Status="Text saved to file ";
  for(int i=0;i<sizeof(F_Name);i++)
	  Status+=F_Name[i];
}


void update_screen()
{
  erase(); //чистим экран
//выводим все элементы вектора
  for (size_t i = 0; i < str_count; i++)
      {
//если счетчик равен текущему элементу
           attron (COLOR_PAIR(2));
          // printw ("%s\n", MyNote[i].c_str());
	   addstr(MyNote[i].c_str());
	   addstr("\n");
         //  printw ("%i\n", strlen(MyNote[i].c_str()));
           attroff (COLOR_PAIR(2));
      }

       // Подписываем функциональные клавиши
        char funk_key1[] = "F1 - Open File";
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
           move(curposY,curposX);// установка курсора на начало текста

}
//главная функция
int main (int argc, char *argv[])
{
//всё инициализируем
  initscr();
  start_color();
  keypad (stdscr, TRUE); 
  noecho();

//создаем цветовые пары  
  init_pair (1, COLOR_RED, COLOR_BLACK);
  init_pair (2, COLOR_WHITE, COLOR_BLACK);
  init_pair (3,  COLOR_BLACK,   COLOR_GREEN);
  init_pair (4, COLOR_WHITE,   COLOR_BLUE);
  init_pair (5,  COLOR_WHITE,   COLOR_RED);
  
  
  //заполняем вектор тремя элементами
 // MyNote[0]="One";
 // MyNote[1]="Two";
 // MyNote[2]="Three";
 // str_count=3;
//текущий элемент сбрасываем в ноль
  current_element = 0;
//объявляем переменную для хранения нажатой клавиши
  int ch = 0;
  // WINDOW *win = newwin(height, width, offsety, offsetx);

//   WINDOW *win = newwin(10, 10, 10, 10);

  //  box(win, 5, 5);

   // wrefresh(win);
   // getch(); 
//считываем клавиши, пока не будет нажата 'F3'  
  while (ch != KEY_F(3))
        {
         //обновляем экран
         update_screen();
         
         //ожидаем нажатия на клавишу и 
         //получаем её код в ch
           mousemask (ALL_MOUSE_EVENTS, NULL);
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
			    if ( curposX<sizeof(MyNote[curposY]))
				    curposX++;
                             break;
//если нажата "вниз", то увеличиваем current_element
                case KEY_BACKSPACE: 
		         MyNote[current_element]+=ch;	       
                                break;
//обработка нажатия Enter
                 case '\n': 
                               str_count++;
                              // list[current_element];//пользователь выбрал элемент
                               break;
	         case  KEY_MOUSE:
                               if (getmouse(&event) == OK)
                               //    if (event.bstate & BUTTON1_PRESSED)
			          if(event.y==LINES-2) // попали в функциональные клавиши
				     if(event.x<COLS/3) // F1
                                        Open_File();

				     if((event.x>COLS/3)&&(event.x<COLS*2/3)) // F2
                                        File_Save();
				     if(event.x>COLS*2/3) // F3
                                        ch = KEY_F(3);
				  else	  
				   {                                        
                                    curposY=event.y;
			            curposX=event.x;
				   }
                              break;
		default  :
			      if(curposX<(strlen(MyNote[curposY].c_str())))
				      MyNote[curposY][curposX]=ch;	      
			      else
				   MyNote[curposY]+=ch;   
			       curposX++; 
                               break;
                }
        }     
  endwin();
  return 0;
}
