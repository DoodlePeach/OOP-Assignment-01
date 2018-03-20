#include <iostream>
#include <fstream>
#include "student.h"
#include <windows.h>

using namespace std;

void initializeStreams(ifstream*);
void initializeStreams(ofstream*);
void closeStreams(std::ofstream*);
void closeStreams(std::ifstream*);
void printMenu();
void writeData(student *argStudent);
void readData(std::ifstream *ptr, student *argStudent);
void deleteData(std::ofstream* ptr);
void search(student *studentArray, int size);
int getNumberOFStudents(const char* addr);
void populate(student *ptr, int limit);
std::istream& operator >> (istream & is, student &obj);

int main()
{
	int size = 0, option = 0;

	bool pendingSave = false;

	student *ptrStudentArray = 0;
	student obj;

	ifstream getStream[5];
	ofstream saveStream[5];

	while (option != 6)
	{
		if (pendingSave)
		{
			cout << "[*] Some data is waiting to be saved! Please press 2 to save." << endl;
		}

		printMenu();
		cin >> option;

		switch (option)
		{
			case 1:
			{
				cin >> obj;

				pendingSave = true;

				break;
			}

			case 2:
			{
				size = getNumberOFStudents("id.txt");

				if (size > 0)
				{
					ptrStudentArray = new student [size];

					populate(ptrStudentArray, size);

					cout << "Populated " << size << " students!" << endl;

					Sleep(1200);
				}

				else
				{
					cout << "No data found in files." << endl;
					Sleep(1200);
				}

				break;
			}

			case 3:
			{
				if (pendingSave)
				{
					writeData(&obj);
					pendingSave = false;
				}

				else
				{
					cout << "Nothing to be saved!" << endl;
				}

				Sleep(1200);

				break;
			}

			case 5:
			{
				search(ptrStudentArray, size);


				break;
			}

			case 7:
			{
				for (int i = 0; i < size; i++)
				{
					ptrStudentArray[i].disp();
				}

				Sleep(1200);
			}
		}

		system("CLS");
	}

	delete[] ptrStudentArray;

	return 0;
}
