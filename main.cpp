#include <iostream>
#include <fstream>
#include "student.h"
#include <windows.h>

using namespace std;

void initializeStreams(ifstream*);
void initializeStreams(ofstream*);
void printMenu();
void writeData(std::ofstream *ptr, student *argStudent);
void readData(std::ifstream *ptr, student *argStudent);
void deleteData(std::ofstream* ptr);
int getNumberOFStudents(const char* addr);
void populate(std::ifstream *files, student *ptr, int limit);
std::istream& operator >> (istream & is, student &obj);

int main()
{
	int size = 0, option = 0;

	bool pendingSave = false;

	student *ptr = 0;
	student obj;

	ifstream getStream[5];
	ofstream saveStream[5];

	while (option != 6)
	{
		initializeStreams(getStream);
		initializeStreams(saveStream);

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

				obj.disp();

				//Sleep(1000000);

				break;
			}

			case 2:
			{
				size = getNumberOFStudents("id.txt");

				cout << size;

				if (size > 0)
				{
					ptr = new student [size];

					populate(getStream, ptr, size);

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
					writeData(saveStream, &obj);
					pendingSave = false;
				}

				else
				{
					cout << "Nothing to be saved!" << endl;
				}

				Sleep(1200);

				break;
			}
		}

		system("CLS");
	}

	for (int i = 0; i < size; i++)
	{
		ptr[i].disp();
	}

	delete[] ptr;

	return 0;
}
