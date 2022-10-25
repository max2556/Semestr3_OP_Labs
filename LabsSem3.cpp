/*
Дан текст, составленный из строк.
Под словом текста понимается последовательность букв алфавита.
Между соседними словами - не менее одного пробела.
Перед первым и за последним словом каждой строки произвольное число пробелов.
Удалить в каждом слове все последующие вхождения его первой буквы.
Строчные и прописные буквы считать эквивалентными.
*/

#include<fstream>
#include<iostream>
#include<stdlib.h>
#include <locale>
#include<string.h>

using namespace std;

#define FNAME_I "given.txt"	                                //имя исх. файла задано константной строкой
#define FNAME_R "result.txt"	                                //имя рез. файла задано константной строкой
const int RAZ = 80;			                                    //максимальная длина строки
const char PR_R[] = "r";		                                //признак открытия файла на чтение
const char PR_W[] = "w";		                                //признак открытия файла на запись
void make_file(string& filename);			                    //функция создания файла
void obrabotka_file(string& inputFile, string& resultFile);	    //обработка содержимого
void vivod_file(string& filename);	                            //вывод содержимого файла на печать
int glasn(char ch);		                                        //проверка, является ли символ гласной буквой


//main_Begin______________________________________________________________
int main()
{
	string inputFilename = FNAME_I;
	string resultFilename = FNAME_R;
	setlocale(LC_ALL, "Russian");
	cout << " Программа создает файл строк." << endl <<
		" Затем файл построчно читается, при этом слова в каждой строке," << endl <<
		" очищаются от повторных вхождений первой буквы" << endl <<
		" Создаем исходный файл:" << endl;
	//создаем исходный файл
	make_file(inputFilename);

	//выводим его содержимое
	cout << " Содержимое исходного файла:" << endl;
	vivod_file(inputFilename);

	//обрабатываем файл
	obrabotka_file(inputFilename, resultFilename);

	//выводим содержимое результата
	cout << " Результат (в каждом слове удалены повторения первой буквы" << endl;
	vivod_file(resultFilename);

	cout << endl << " Для завершения нажмите <Enter>";
	cin.get();
	return 0;
}
//main_End________________________________________________________________

//make_file_ Begin________________________________________________________
void make_file(string& fname_i)
{
	char st[RAZ];		//исходная строка
	char otv;			//ответ пользователя

	/*Открываем файл в режиме чтения.
	Если файл с таким именем уже есть, то либо пользователь вводит
	новое имя, либо новые записи будут дописаны поверх старых*/
	ifstream in_p(fname_i);
	/*создание объекта in_p класса входных
	файловых потоков, открытие файла с именем fname_i
	для чтения и связывание объекта с файлом*/

	while (in_p)		//ошибки открытия файла на чтение нет
	{
		cout << " Файл с заданным именем уже есть! Зададите новое имя Y/N? ";
		cin.get(otv);
		if (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н')
		{
			cout << " Введите новое имя:" << endl;
			cin >> fname_i;
			cin.get();	//убираем символ '\n' из потока
		}
		else {
			cin.get(); 	//убираем символ '\n' из потока
			break;
		}
	}
	in_p.close();		//используем метод close для закрытия потока
	ofstream in(fname_i, ios::out | ios::trunc);
	/*создание объекта in класса выходных
	файловых потоков, открытие файла для записи
	и связывание объекта с файлом*/
	/*проверяем возможность открытия файла для записи
	поскольку полное имя файла могло быть задано с ошибкой*/
	if (!in)
	{
		cout << " Ошибка открытия файла " << fname_i << " на запись" << endl <<
			" Нажмите <Enter>" << endl;
		cin.get();
		exit(0);
	}
	cout << " Создание файла." << endl <<
		" Признак окончания ввода - ввод пустой строки" << endl <<
		" Введите строку и нажмите <Enter>" << endl << " ->";
	cin.getline(st, RAZ);	/*функция вводит строку целиком, включая
					   пробелы и символ \n*/
	while (strlen(st))
	{
		in << st << endl;		//записываем строку в файл
		cout << " Введите строку и нажмите <Enter>" << endl << " ->";
		cin.getline(st, RAZ);
	}
	in.close();			//закрываем поток
}
//make_file_End___________________________________________________________

//obrabotka_file_Begin____________________________________________________
//обработка содержимого файла
void obrabotka_file(string& fname_i, string& fname_r)
{
	char inputStr[RAZ];				//исходная строка
	string resultStr;				//результирующая строка
	string word;					//выделенное слово
	
	/*создание объекта in класса входных
	файловых потоков, открытие файла для чтения
	и связывание объекта с файлом*/
	ifstream in(fname_i);

	/*создание объекта out класса выходных
	файловых потоков, открытие файла для записи
	и связывание объекта с файлом*/
	ofstream out(fname_r);

	char* inputStrRemain = NULL;

	in.getline(inputStr, RAZ);									//читаем строку из файла in
	while (!in.eof()){
		word = strtok_s(inputStr, " \n\0", &inputStrRemain);	//выделяем первое слово (лексему)
		while (!word.empty())									//если очередное слово выделено
		{
			//обрабатываем 
			char firstLetter = tolower(word[0]);
			int letterPos = word.find_last_of(firstLetter);
			while (letterPos > 0)								//string::find() возвращает -1, если не находит подстроку 
			{
				word.erase(letterPos, 1);
				letterPos = word.find_last_of(firstLetter);
			}

			firstLetter = toupper(firstLetter);
			letterPos = word.find_last_of(firstLetter);
			while (letterPos > 0)								//string::find() возвращает -1, если не находит подстроку 
			{
				word.erase(letterPos, 1);
				letterPos = word.find_last_of(firstLetter);
			}

			word.push_back(' ');
			resultStr.append(word);

			char* nextword = strtok_s(NULL, " \n\0", &inputStrRemain);
			word = "";
			if(nextword)
				word = nextword;
		}
		resultStr.pop_back();	//убираем последний пробел
		if (resultStr.length()) out << resultStr << endl;
		resultStr = "";
		in.getline(inputStr, RAZ);
	}//while
	in.close();		//Закрываем поток in
	out.close();		//Закрываем поток out
}
//obrabotka_file_End______________________________________________________

//vivod_file_Begin________________________________________________________
//вывод содержимого файла на экран
void vivod_file(string& filename)
{
	char st[RAZ];			//считанная строка
	/*создание объекта in_out класса входных
	файловых потоков, открытие файла для чтения
	и связывание объекта с файлом*/
	ifstream in_out(filename);

	in_out.getline(st, RAZ);	//читаем строку из потока in_out
	while (!in_out.eof())
	{
		cout << st << endl;	//выводим очередную строку на экран
		in_out.getline(st, RAZ);
	}
	in_out.close();
}
//vivod_file_End__________________________________________________________
