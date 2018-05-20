#include <cstring>
#include <fstream>
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
          mvaddstr(0,0,"Input file name (default (press enter) - text.txt)");
       //	printw ("%s\n", "Input file name (default (press enter) - text.txt)");
	char str[100];
       getstr(str); //Считываем строку
        if(strlen(str)>3) //проверяем, если имя не введено - ставим text.txt
              F_Name=str;
	else
              F_Name="text.txt";

   ifstream file(F_Name,ios::in);// открываем поток для чтения 
    if (!file) {// файл не открылся
     printw ("%s\n", "Do not open file. Press enter");
     getstr(str); //Считываем строку
	    return 0;
              }
    current_element=0;
   while(!file.eof())// читаем, пока не достигнем конца файла
   {
   // getline(file,MyNote[current_element]);
  file>> MyNote[current_element];
    current_element++;
   }
   //
        //если читаем бинарный файл (не текст), то стоит делать так:
        //
        //становимся в конец файла
	//file.seekg(0,ios_base::end);
        //Получаем текущую позицию  -  она же размер файла
	//       int File_Size= file.tellg();
	//file.seekg(0);// возвращаем на начало файла
        //Создаем буффер размером в файл (здесь по идее надо разбить на блоки мегабайт по 8-16)
        //если файл большой
        //	char* buffer=new char[File_Size];
        //Читаем в него сразу весь файл (если размер позволяет это сделать)
        //	file.read(buffer,File_Size);
   //
   str_count=current_element;
   file.close();

  curposX=0,curposY=str_count-1;
  Status="Open and read file ";
  for(int i=0;i<sizeof(F_Name);i++)
	  Status+=F_Name[i];
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
//если нажата "BACKSPACE" - не сделано! нажимать нельзя
                case KEY_BACKSPACE: 
		         MyNote[current_element]+=ch;	       
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
