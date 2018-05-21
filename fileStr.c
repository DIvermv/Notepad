#include "func.h"



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
