#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "student.h"



const char *fileNames[5] = { "id.txt", "name.txt", "gpa.txt", "semseter.txt", "contact.txt" };


void initializeStreams(std::ofstream *ptr)
{
	for (int i = 0; i < 5; i++)
	{
		ptr[i].open(fileNames[i], std::ios::app);
	}
}

void initializeStreams(std::ifstream *ptr)
{
	for (int i = 0; i < 5; i++)
	{
		ptr[i].open(fileNames[i]);
	}
}

void closeStreams(std::ofstream *ptr)
{
	for (int i = 0; i < 5; i++)
	{
		ptr[i].close();
	}
}

void closeStreams(std::ifstream *ptr)
{
	for (int i = 0; i < 5; i++)
	{
		ptr[i].close();
	}
}

void printMenu()
{
	std::cout << "1. Enter a new Student.\n2. Populate data from file.\n3. Save data to file." << std::endl << std::endl;
	std::cout << "4. Search and Edit data:\n  a. Edit GPA\n  b. Edit Name\n  c. Edit Semester\n  d. Edit Contact Number" << std::endl << std::endl;
	std::cout << "5. Searching criteria\n  a. Search by GPA\n  b. Search by Name\n  c. Search all who are above 3.5 GPA\n  d. Search all who are under serious warning (i.e. CGPA below 1.8)\n  e. Search all who are under warning (i.e. CGPA below 2.0 and above 1.8)" << std::endl;
	std::cout << std::endl << "Enter your choice: ";
}

void deleteData(std::ofstream* ptr)
{
	for (int i = 0; i < 5; i++) // If any file is open, close it.
	{
		if (ptr[i].is_open())
		{
			ptr[i].close();
		}
	}

	for (int i = 0; i < 5; i++) // Open files in truncate mode. Files opened in truncate mode have all of their previous data deleted.
	{
		ptr[i].open(fileNames[i], std::ios::trunc);
	}

	for (int i = 0; i < 5; i++) // Close files opened in truncate mode.
	{
		ptr[i].close();
	}

	for (int i = 0; i < 5; i++) // Open up the file back normally.
	{
		ptr[i].open(fileNames[i], std::ios::app);
	}
}

void writeData(student *argStudent)
{
	std::ofstream files[5];

	initializeStreams(files);

	files[0] << argStudent->getId() << std::endl;
	files[1] << argStudent->getName() << std::endl;
	files[3] << argStudent->getSemester() << std::endl;

	for (int i = 0; i < argStudent->getSemester(); i++)
	{
		files[2] << argStudent->getGpa(i) << std::endl;
	}

	files[4] << argStudent->getContact() << std::endl;

	closeStreams(files);
}

void readData(std::ifstream *ptr, student *argStudent)
{
	std::string inpString;
	std::string inpContact;
	int tempId, tempSemester;
	float tempGpa;

	ptr[0] >> tempId;
	ptr[1] >> inpString;
	ptr[3] >> tempSemester;
	ptr[4] >> inpContact;

	argStudent->setId(tempId);
	argStudent->setName(inpString);
	argStudent->setSemester(tempSemester);

	for (int i = 0; i < argStudent->getSemester(); i++)
	{
		ptr[2] >> tempGpa;
		argStudent->setGpa(tempGpa, i);
	}

	argStudent->setContact(inpContact);
}

void populate(student *ptr, int limit) // Receives file stream and student array pointers and populates them.
{
	std::ifstream files[5];

	initializeStreams(files);

	for (int i = 0; i < limit; i++) // Every file (except gpa.txt) has a one-to-one correspondence of data stored and thus if eof is encountered in even one file, it means that eof will be encountered in other files as well.
	{
		readData(files, &ptr[i]);
	}

	closeStreams(files);
}

int getNumberOFStudents(const char* addr) // Calculate the number of students stored in the files.
{
	int size = 0;
	std::string temp;

	std::ifstream file;

	file.open(addr);

	while (!file.eof())
	{
		file >> temp; // Obtaining useless IDs from id.txt and incrementing size counter. Then checking if these values are spaces/newlines or empty string.

		size++; // Else, increment the student array counter.

		temp = "";
	}

	file.close();

	return size - 1;
}

std::istream& operator >> (std::istream & is, student &obj)
{
	int tempId, tempSemester;
	float tempGpa;
	std::string tempName, tempContact;


	std::cout << std::endl << "Please enter the data of the student: " << std::endl;

	std::cout << "Enter ID: ";
	is >> tempId;
	obj.setId(tempId);

	std::cout << "Enter name: ";
	is >> tempName;
	obj.setName(tempName);

	std::cout << "Enter Contact: ";
	is >> tempContact;
	obj.setContact(tempContact);

	std::cout << "Enter Semester: ";
	is >> tempSemester;
	obj.setSemester(tempSemester);

	for (int i = 0; i < obj.getSemester(); i++)
	{
		std::cout << "Enter GPA for semester " << i + 1 << ": ";
		is >> tempGpa;
		obj.setGpa(tempGpa, i);
	}

	return is;
}


void search(student *studentArray, int studentArraySize)
{
	if(studentArraySize > 0)
	{
		char option;

		std::cout << "What would you like to search by? (a, b, c or d): ";

		std::cin >> option;

		switch (option)
		{
			case 'a':
			{
				float searchGpa;

				std::cout << std::endl << "Enter GPA: ";
				std::cin >> searchGpa;

				for (int i = 0; i < studentArraySize; i++)
				{
					for (int j = 0; j < studentArray[i].getSemester(); j++)
					{
						if (studentArray[i].getGpa(j) == searchGpa)
						{
							studentArray[i].disp();

							break;
						}
					}
				}

				
				std::cin.get();
				std::cin.get();

				break;
			}

			case 'b':
			{
				std::string searchName;

				std::cout << std::endl << "Enter Name: ";
				std::cin >> searchName;

				for (int i = 0; i < studentArraySize; i++)
				{
					if (studentArray[i].getName() == searchName)
					{
						studentArray[i].disp();
					}
				}

				break;
			}

			case 'c':
			{
				int searchSemester;

				std::cout << std::endl << "Enter Semester: ";
				std::cin >> searchSemester;

				for (int i = 0; i < studentArraySize; i++)
				{
					if (studentArray[i].getSemester() == searchSemester)
					{
						studentArray[i].disp();
					}
				}

				break;
			}

			case 'd':
			{
				std::string searchContact;

				std::cout << std::endl << "Enter Contact: ";
				std::cin >> searchContact;

				for (int i = 0; i < studentArraySize; i++)
				{
					if (studentArray[i].getContact() == searchContact)
					{
						studentArray[i].disp();
					}
				}

				break;
			}

			default:
			{
				std::cout << "Invalid choice, returning to main menu." << std::endl;
			}
		}
	}
	
	else
	{
		std::cout << "No data loaded, nothing to search!." << std::endl;
	}

}
