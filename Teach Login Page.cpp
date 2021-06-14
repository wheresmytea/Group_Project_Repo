// Teacher Login.cpp : This file contains the 'main' function. Program execution begins and ends there.
//teacher_files.dat

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct teacher // Teacher structure
{
	char full_name[60];
	char gender[2];
	char DOB[15];
	char email[51];
	char phone_number[20];
	char classroom[15];
	char year_teach[10];
	char username[15];
	char password[15];
};

struct parent //Parent Structure
{
	char first_name[30];
	char last_name[30]; //Using First Name last name instead of just full name. Makes it easier to match parent and child
	char gender[2];
	char DOB[15];
	char email[51];
	char phone_number[20];
	char child_fname[60];
	char child_class[15];
	char emer_contactname[60];
	char emer_contactnum[20];
	char username[15];
	char password[15];
};

void teacher_registration(struct teacher&); //function to input and write teacher information into teacher.dat file
void parent_registration(struct parent&); //function to input and write parent information into teacher.dat file
void teacher_login(char[], char[]); //function to match user input with teacher information from file
void parent_login(char[], char[]); //function to match user input with parent information from file
char username_t[15];	//teacher username
char password_t[15];	//teacher password
char username_p[15];	//parent username
char password_p[15];	//parent password
bool flag = false;

int main()
{
	teacher teach;
	parent paren;
	int login_selection;
	bool login_done = false;

	do // Using do while to simulate menu
	{

		cout << "\n      +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
		cout << "\n\n\t\tLogin Screen";
		cout << "\n\t1. New Teacher Sign Up.";
		cout << "\n\t2. New Parent Sign up.";
		cout << "\n\t3. Teacher Sign In.";
		cout << "\n\t4. Parent Sign In.";
		cout << "\n\t5. Return to Home Page.";
		cout << "\n\n      +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
		cout << "\n\tPlease enter choice : ";
		cin >> login_selection;

		switch (login_selection)
		{
		case 1: teacher_registration(teach); //reading new teacher record
			break;
		case 2: parent_registration(paren); //reading new parent record
			break;
		case 3: teacher_login(username_t, password_t); // calling find record teacher
			break;
		case 4: parent_login(username_p, password_p);// calling find record parent
			break;
		case 5: login_done = true; // This will return user to home menu screen
			break;
		default: cout << "\n\tPlease enter correct option.\n";
			break;
		}
	} while (!login_done);

	cout << "\n\n";
	return 0;
}

void teacher_registration(struct teacher& teach)
{
	fstream file;
	file.open("teacher_files.dat", ios::out | ios::app | ios::binary);

	cout << "\n\tTeacher Sign Up";
	cout << "\n\tPlease Enter your information.";
	cin.ignore();

	cout << "\n\n\tFull Name : ";
	cin.getline(teach.full_name, 60);
	cout << "\tGender(M/F/O) : ";
	cin.getline(teach.gender, 2);
	cout << "\tDate of Birth (xx/xx/xxxx) : ";
	cin.getline(teach.DOB, 15);
	cout << "\tEmail : ";
	cin.getline(teach.email, 51);
	cout << "\tPhone Number (Max 9 digits): ";
	cin.getline(teach.phone_number, 20);
	cout << "\tClass room (Class xxx) : ";
	cin.getline(teach.classroom, 15);
	cout << "\tYear teaching (Year xx) : ";
	cin.getline(teach.year_teach, 10);
	cout << "\tUsername (Max 15 letters): ";
	cin.getline(teach.username, 15);
	cout << "\tPassword (Max 15 letters): ";
	cin.getline(teach.password, 15);
	cout << "\n\n\tTeacher record successfully.\n";

	file.write(reinterpret_cast<char*>(&teach), sizeof(teach)); // storing record in binary

	file.close();
}

void parent_registration(struct parent& paren)
{
	fstream file;
	file.open("parent_files.dat", ios::out | ios::app | ios::binary);

	cout << "\n\tParent Sign Up";
	cout << "\n\tPlease Enter your information.";
	cin.ignore();

	cout << "\n\n\tFirst Name : ";
	cin.getline(paren.first_name, 30);
	cout << "\n\n\tLast Name : ";
	cin.getline(paren.last_name, 30);
	cout << "\tGender(M/F/O) : ";
	cin.getline(paren.gender, 2);
	cout << "\tDate of Birth (xx/xx/xxxx) : ";
	cin.getline(paren.DOB, 15);
	cout << "\tEmail : ";
	cin.getline(paren.email, 51);
	cout << "\tPhone Number : ";
	cin.getline(paren.phone_number, 20);
	cout << "\tChild Full Name : ";
	cin.getline(paren.child_fname, 60);
	cout << "\tChild Class room (Class xxx) : ";
	cin.getline(paren.child_class, 15);
	cout << "\tEmergency Contact Name : ";
	cin.getline(paren.emer_contactname, 60);
	cout << "\tEmergency Contact Number (Max 9 digits) : ";
	cin.getline(paren.emer_contactnum, 20);
	cout << "\tUsername (Max 15 letters): ";
	cin.getline(paren.username, 15);
	cout << "\tPassword (Max 15 letters): ";
	cin.getline(paren.password, 15);


	file.write(reinterpret_cast<char*>(&paren), sizeof(paren)); // storing record in binary

	file.close();
}

void teacher_login(char username_t[15], char password_t[15])
{
	teacher teach;
	fstream file;

	file.open("teacher_files.dat", ios::in | ios::binary); // opening in read mode

	if (file.is_open())
	{
		cin.ignore();
		cout << "\n\n\tEnter Teacher Username : ";
		cin.getline(username_t, 15);
		cout << "\n\tEnter Teacher Password : ";
		cin.getline(password_t, 15);

		while (!file.eof())
		{
			file.read(reinterpret_cast<char*>(&teach), sizeof(teach)); // reading the content from the file 
			if ((strcmp(username_t, teach.username) == 0) && (strcmp(password_t, teach.password) == 0)) // matching user input with information stored on file
			{ 
				// this will be where we put student read/write/edit/delete record function
				cout << "\n\n\tThat's all the information in the file for the search key provided!\n";
				flag = false;
				break;
			}
			else
			{
				flag = true;
			}
		}
	}
	else
	{
		cout << "\nNo record found in the file for the search key provided!\n";
	}

	if (flag)
	{
		cout << "\nNo record found in the file for the search key provided!\n";

	}
}

void parent_login(char username_p[15], char password_p[15])
{
	fstream file;
	parent paren;

	file.open("parent_files.dat", ios::in | ios::binary); // opening in read mode

	if (file.is_open())
	{
		cin.ignore();
		cout << "\n\n\tEnter Parent Username : ";
		cin.getline(username_t, 15);
		cout << "\n\tEnter Parent Password : ";
		cin.getline(password_t, 15);

		while (!file.eof())
		{
			file.read(reinterpret_cast<char*>(&paren), sizeof(paren)); // reading the content from the file 
			if ((strcmp(username_p, paren.username) == 0) && (strcmp(password_p, paren.password) == 0)) // matching user input with information stored on file
			{
				// this will be where we put student read record function
				cout << "\n\nThat's all the information in the file for the search key provided!\n"; 
				flag = false;
				break;
			}
			else
			{
				flag = true;
			}
		}
	}
	else
	{
		cout << "\n\tNo record found in the file for the search key provided!\n";
	}

	if (flag)
	{
		cout << "\n\tNo record found in the file for the search key provided!\n";

	}
}
