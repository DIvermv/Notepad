
#include "func.h"

int main (int argc, char *argv[])
{
int current_element; //номер текущего элемента
struct My_Note MyNote;
       MyNote.str_count=0;
       MyNote.Status=NULL;
int curposX,curposY;
//всё инициализируем
  initscr();
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
         update_screen(MyNote);  
         mousemask (ALL_MOUSE_EVENTS, NULL);// инициализируем считывание мыши
	 move(curposY,curposX);// выставляем курсор
         //ожидаем нажатия на клавишу и 
         //получаем её код в ch
         ch = getch();
 
         switch (ch)
                {
//если нажата "F1", то открываем файл
                 case KEY_F(1): 
                            MyNote=Open_File();
                             break;
//если нажата "F2", то сохраняем файл
                 case KEY_F(2): 
			   MyNote= File_Save(MyNote);
                             break;
//если нажата "вверх"
                 case KEY_UP: 
			    if ( curposY>0)
				    curposY--;
                             break;
//если нажата "вниз"
                case KEY_DOWN: 
			    if ( curposY<MyNote.str_count-1)
				    curposY++;
                             break;
//если нажата "влево"
                case KEY_LEFT: 
			    if ( curposX>0)
				    curposX--;
                             break;
//если нажата "вправо"
                case KEY_RIGHT: 
			    if (curposX<strlen(MyNote.note[curposY])-1)// дальше конца строки не заходим
				    curposX++;
                             break;
//если нажата "BACKSPACE"
                case KEY_BACKSPACE: 
			     if(curposX>0)
			     {     
			       for(int i=(curposX-1);i<strlen(MyNote.note[curposY]);i++)
				       MyNote.note[curposY][i]=MyNote.note[curposY][i+1];
                               curposX--;
			     }
                                break;
//обработка нажатия Enter - только добавление строки в конец, так не раздвинет строки
                 case '\n': 
                              MyNote.str_count++;
                               break;
// обработка нажатия мыши - не контролирует, какая клавиши нажата, только факт нажатия			       
	         case  KEY_MOUSE:
                               if (getmouse(&event) == OK)
			          if(event.y==LINES-2) // попали в функциональные клавиши
				     if(event.x<COLS/3) // F1
                                         MyNote=Open_File();
				     if((event.x>COLS/3)&&(event.x<COLS*2/3)) // F2
			                 MyNote= File_Save(MyNote);
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
			      if(curposX<(strlen(MyNote.note[curposY])-1))// если в строке - то заменяем
				      MyNote.note[curposY][curposX]=ch;	      
			      else{
				      MyNote.note[curposY][curposX+1]=MyNote.note[curposY][curposX];
                                      MyNote.note[curposY][curposX]=ch;
				  // MyNote.note[curposY]+=ch;   // в конец строки - дописываем
			           }
			       curposX++; 
                               break;
                }
        }     
  endwin();// разрушаем окно
  return 0;
}
