#include <string>
#include <ctime>
using namespace std;
#include "../Types of variables/TYPES.h"
#include "../Types of variables/BASE_data.h"
#include "ADMIN_data.h"

extern const u8 months_days[NUMBER_OF_MONTHS];

bool Admin_C::SET_Name(string Name)
{
	u8 size = Name.length();
	do
	{
		size--;
		if (Name[size] != ' ' && (Name[size] < 65 || Name[size] > 90) && (Name[size] < 97 || Name[size] > 122))
		{
			return true;
		}
	} while (size != 0);
	Head_Ref->Name = Name;
	Head_Ref->Name.shrink_to_fit();
	return false;
}

bool Admin_C::SET_Username(string Username)
{
	u8 size = Username.length();
	do
	{
		size--;
		if (Username[size] != '_' && (Username[size] < 48 || Username[size] > 57) && (Username[size] < 65 || Username[size] > 90) && (Username[size] < 97 || Username[size] > 122))
		{
			return true;
		}
	} while (size != 0);
	Head_Ref->Username = Username;
	Head_Ref->Username.shrink_to_fit();
	return false;
}

bool Admin_C::SET_Password(string Password)
{
	if (Password.length() > 50 || Password.length() < 8)
	{
		return true;
	}
	Head_Ref->Password = Password;
	Head_Ref->Password.shrink_to_fit();
	return false;
}

bool Admin_C::SET_Phone_number(string Phone_number)
{
	u8 size = Phone_number.length();
	if (Phone_number[0] != '0' || Phone_number[1] != '1' || ((Phone_number[2] < '0' || Phone_number[2] > '2') && Phone_number[2] != '5') || size != 11)
	{
		return true;
	}
	do
	{
		size--;
		if (Phone_number[size] < 48 || Phone_number[size] > 57)
		{
			return true;
		}
	} while (size > 3);
	Head_Ref->Phone_number = Phone_number;
	Head_Ref->Phone_number.shrink_to_fit();
	return false;
}

bool Admin_C::SET_Email(string Email)
{
	u8 size = Email.length(), counter, temp = 0,temp2 = 0;
	for (counter = 0; counter < size; counter++)
	{
		if (Email[counter] == '@')
		{
			break;
		}
		else if ((Email[counter] < 48 || Email[counter] > 57) && (Email[counter] < 65 || Email[counter] > 90) && (Email[counter] < 97 || Email[counter] > 122))
		{
			return true;
		}
	}
	if (counter + 1 >= size || counter == 0)
	{
		return true;
	}
	for (counter++; counter < size; counter++)
	{
		if (Email[counter] == '.')
		{
			temp = counter;
		}
		else if (Email[counter] != '-' && (Email[counter] < 48 || Email[counter] > 57) && (Email[counter] < 65 || Email[counter] > 90) && (Email[counter] < 97 || Email[counter] > 122))
		{
			return true;
		}
		if (temp == 0)
		{
			temp2++;
		}
	}
	if (temp == 0 || temp2 < 2)
	{
		return true;
	}
	for (counter = temp + 1; counter < size; counter++)
	{
		if ((Email[counter] < 65 || Email[counter] > 90) && (Email[counter] < 97 || Email[counter] > 122))
		{
			return true;
		}
	}
	if (temp > (size - 3))
	{
		return true;
	}
	Head_Ref->Email = Email;
	Head_Ref->Email.shrink_to_fit();
	return false;
}

bool Admin_C::SET_Birth_Date(string Date_Of_Birth)
{
	u8 leap_year, day, month, counter, size = Date_Of_Birth.length(), temp1 = 0, temp2 = 0;
	u16 year;
	string temp = "";
	if (size > 10 || size < 8)
	{
		return true;
	}
	for (counter = 0; counter < size; counter++)
	{
		if (Date_Of_Birth[counter] != '/' && (Date_Of_Birth[counter] < 48 || Date_Of_Birth[counter] > 57))
		{
			return true;
		}
		if (Date_Of_Birth[counter] == '/' && temp1 == 0)
		{
			if (counter != 1 && counter != 2)
			{
				return true;
			}
			temp1 = counter;
		}
		else if (temp1 != 0 && Date_Of_Birth[counter] == '/')
		{
			if (counter != 3 && counter != 4 && counter != 5)
			{
				return true;
			}
			temp2 = counter;
		}
	}
	if (temp1 == 0 || temp2 == 0)
	{
		return true;
	}
	for (counter = 0; counter < temp1; counter++)
	{
		temp += Date_Of_Birth[counter];
	}
	day = stoi(temp);
	temp = "";
	for (counter = temp1 + 1; counter < temp2; counter++)
	{
		temp += Date_Of_Birth[counter];
	}
	month = stoi(temp);
	temp = "";
	for (counter = temp2 + 1; counter < size; counter++)
	{
		temp += Date_Of_Birth[counter];
	}
	year = stoi(temp);
	time_t time_now = time(0);
	#pragma warning(suppress : 4996)
	tm* Now_date = localtime(&time_now);
	if (year > (1900 + Now_date->tm_year) || year == (1900 + Now_date->tm_year) && month >= Now_date->tm_mon + 1 && day >= Now_date->tm_mday)
	{
		return true;
	}
	if (month < 13 && year > 1910 && month != 0 && day != 0)
	{
		if (month == 2)
		{
			leap_year = (year % 4 ? 0 : (year % 100 ? 1 : (year % 400 ? 0 : 1)));
			if (day > months_days[1] + leap_year)
			{
				return true;
			}
		}
		else
		{
			if (day > months_days[month - 1])
			{
				return true;
			}
		}

	}
	else
	{
		return true;
	}
	Head_Ref->Date_Of_Birth = Date_Of_Birth;
	Head_Ref->Date_Of_Birth.shrink_to_fit();
	Head_Ref->Age = (1900 + Now_date->tm_year) - year + ((Now_date->tm_mon + 1) > month ? 0 : (((Now_date->tm_mon + 1) == month) ? (((Now_date->tm_mday) >= day) ? 0 : -1) : -1));
	return false;
}

bool Admin_C::SET_Gender(string Gender)
{
	u8 counter, size = Gender.length();
	for (counter = 0; counter < size; counter++)
	{
		if (Gender[counter] >= 97 && Gender[counter] <= 122)
		{
			Gender[counter] -= 32;
		}
		else if (Gender[counter] < 65 || Gender[counter] > 90)
		{
			return true;
		}
	}
	if (Gender == "MALE")
	{
		Head_Ref->Gender = 0;
		return false;
	}
	else if (Gender == "FEMALE")
	{
		Head_Ref->Gender = 1;
		return false;
	}
	else
	{
		return true;
	}
}


string Admin_C::GET_Name() const
{
	return Head_Ref->Name;
}

string Admin_C::GET_Username() const
{
	return Head_Ref->Username;
}

string Admin_C::GET_Password() const
{
	return Head_Ref->Password;
}

string Admin_C::GET_Phone_number() const
{
	return Head_Ref->Phone_number;
}

string Admin_C::GET_Email() const
{
	return Head_Ref->Email;
}

string Admin_C::GET_Birth_Date() const
{
	return Head_Ref->Date_Of_Birth;
}

u16 Admin_C::GET_Age() const
{
	return Head_Ref->Age;
}

u16 Admin_C::GET_Gender() const
{
	return Head_Ref->Gender;
}