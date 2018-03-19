#include "student.h"
#include <iostream>

student::student()
{
	id = semester = 0;
	gpa = 0;
	name = contact = "NOT ASSIGNED";
}

student::~student()
{
	delete[] gpa;
}

void student::setId(int argId)
{
	id = argId;
}

int student::getId()
{
	return id;
}

void student::setName(std::string argName)
{
	name = argName;
}

std::string student::getName()
{
	return name;
}

void student::setGpa(float argGpa, int index)
{
	gpa[index] = argGpa;
}

float student::getGpa(int index)
{
	return gpa[index];
}

void student::setSemester(int argSemester)
{
	semester = argSemester;

	resizeGpaArray();
}

int student::getSemester()
{
	return semester;
}

void student::setContact(std::string argContact)
{
	contact = argContact;
}

std::string student::getContact()
{
	return contact;
}

void student::resizeGpaArray()
{
	float *temp;

	temp = new float [semester];

	delete [] gpa;

	gpa = temp;
}

void student::disp()
{
	std::cout << "ID: " << id << "| Name: " << name << "| Semester: " << semester << "| Contact: " << contact << std::endl;

	for (int i = 0; i < semester; i++)
	{
		std::cout << "GPA of semester " << i + 1 << ": " << gpa[i] << std::endl;
	}
}
