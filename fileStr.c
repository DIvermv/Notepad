#include "func.h"

//#include <fstream>

//#include <ncurses.h>

struct My_Note  Open_File()
{
struct My_Note MyNote;	
int current_element; //номер текущего элемента
int curposX,curposY;
FILE *Notefile;
getsyx(curposY, curposX);
          mvaddstr(0,0,"Input file name (default (press enter) - text.txt)");
       //	printw ("%s\n", "Input file name (default (press enter) - text.txt)");
	char str[100];
       getstr(str); //Считываем строку
        if(strlen(str)>3) //проверяем, если имя не введено - ставим text.txt
             MyNote.F_Name=str;
	else
             MyNote.F_Name="text.txt";
     Notefile = fopen (MyNote.F_Name, "r");
     if(Notefile==NULL)// файл не открылся
            { printw ("%s\n", "Do not open file. Press enter");
               getstr(str); //Считываем строку
	    return MyNote;}
    current_element=0;
   while(fgets (MyNote.note[current_element], 256,Notefile) != NULL)// читаем, пока не достигнем конца файла
   {
   // getline(file,MyNote[current_element]);
 // file>> MyNote[current_element];
    current_element++;
   }
   MyNote.str_count=current_element;
   fclose(Notefile);

  curposX=0,curposY=MyNote.str_count-1;
 
    MyNote.Status="Open and read file ";
return MyNote;
}


 struct My_Note  File_Save(struct My_Note MyNote)
{
FILE *Notefile;
int current_element; //номер текущего элемента
int curposX,curposY;
     Notefile = fopen (MyNote.F_Name, "w");
     if(Notefile==NULL)// файл не открылся
            { printw ("%s\n", "Do not open file. Press enter");
		    char *str;
               getstr(str); //Считываем строку
	    return MyNote;}
    current_element=0;
     while(current_element<MyNote.str_count)
     {
                fputs(MyNote.note[current_element],Notefile);
                 current_element++;
     }
     fclose(Notefile);
    MyNote.Status="Text saved to file ";
	    return MyNote;
}
