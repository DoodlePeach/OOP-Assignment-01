#pragma once

#include <string>
#include <iostream>

class student
{
public:
	student();
	~student();

	void setId(int);
	int getId();

	void setName(std::string);
	std::string getName();

	void setGpa(float, int);
	float getGpa(int);

	void setSemester(int);
	int getSemester();

	void setContact(std::string);
	std::string getContact();

	void resizeGpaArray();
	void disp();

	friend std::istream& operator >> (std::istream& is, student &obj);

protected:

private:
	int id;
	std::string name;
	float *gpa;
	int semester;
	std::string contact;
};

