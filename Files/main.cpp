#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<fstream>
#include<ctime>
using std::cin;
using std::cout;
using std::endl;;

//#define WRITE_TO_FILE
#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");
	//1) Нужно создать поток:
#ifdef WRITE_TO_FILE
	std::ofstream fout;
	//2) открываем поток
	fout.open("File.txt", std::ios_base::app);//std::ios_base::app - append(дописать конец файла)
	//3)Пишем в поток
	//fout << "HelloWorld" << endl;
	//fout << "Сам Привет!" << endl;
	//4)Закрываем поток
	time_t now = time(NULL);
	fout << ctime(&now) << endl;

	fout.close();
	//!!!!!!!!ПОТОКИ КАК ХОЛОДИЛЬНИК, ЕСЛИ ОНИ ОТКРЫТЫ, ИХ ОБЯЗАТЕЛЬНО НУЖНО ЗАКРЫТЬ!
	//! 
	system("notepad File.txt");
#endif // WRITE_TO_FILE

#ifdef READ_FROM_FILE
	//1) Создаем и открываем поток
	std::ifstream fin("File.txt");
		if (fin.is_open())
		{
			//здесь будем читать файл

			const int SIZE = 256;//размер буфера
			char buffer[SIZE]{};//буффер

			while (!fin.eof()) //NOT EndOfFile
			{
				//fin >> buffer;
				fin.getline(buffer, SIZE);
				cout << buffer << endl;
			}

			fin.close();

		}
		else
		{
			std::cerr << "Error: File not found" << endl;
		}
#endif
}