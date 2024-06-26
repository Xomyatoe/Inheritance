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
	//1) ����� ������� �����:
#ifdef WRITE_TO_FILE
	std::ofstream fout;
	//2) ��������� �����
	fout.open("File.txt", std::ios_base::app);//std::ios_base::app - append(�������� ����� �����)
	//3)����� � �����
	//fout << "HelloWorld" << endl;
	//fout << "��� ������!" << endl;
	//4)��������� �����
	time_t now = time(NULL);
	fout << ctime(&now) << endl;

	fout.close();
	//!!!!!!!!������ ��� �����������, ���� ��� �������, �� ����������� ����� �������!
	//! 
	system("notepad File.txt");
#endif // WRITE_TO_FILE

#ifdef READ_FROM_FILE
	//1) ������� � ��������� �����
	std::ifstream fin("File.txt");
		if (fin.is_open())
		{
			//����� ����� ������ ����

			const int SIZE = 256;//������ ������
			char buffer[SIZE]{};//������

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