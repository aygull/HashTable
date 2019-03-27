#include "phone.h"
#include <string>
#include<fstream>
using namespace std;


phone::phone()
{
}

phone::phone(const string& first_name, const string& last_name, const string& patronymic, const string& phone_number, const string& email, const string& company, const string& position)
{
	this->first_name = first_name;
	this->last_name = last_name;
	this->patronymic = patronymic;
	this->phone_number = phone_number;
	this->email = email;
	this->company = company;
	this->position = position;
}


phone::~phone()
{
}

ofstream& operator<<(ofstream& out, phone& book)
{
	out << book.first_name << " " << book.last_name << " " << book.patronymic << " " << book.phone_number << " " << book.email << " " << book.company << " " << book.position;
	return out;
}

ostream& operator<<(ostream& out, phone& book)
{
	setlocale(LC_ALL, "Russian");
	out << "Имя: " << book.first_name << "\nФамилия: " << book.last_name << "\nОтчество: " << book.patronymic << "\nНомер телефона: " << book.phone_number << "\nEmail: " << book.email << "\nКомпания: " << book.company << "\nДолжность: " << book.position<<endl;
	return out;
}

istream& operator>> (istream& in, phone& book)
{
	in >> book.first_name >> book.last_name >> book.patronymic >> book.phone_number >> book.email >> book.company >> book.position;
	return in;
}
bool phone::operator==(const string& for_phone)const{
	if ((this->first_name == for_phone) || (this->company == for_phone) || (this->email == for_phone) || (this->patronymic == for_phone) || (this->position == for_phone) || (this->phone_number.find(for_phone) != (-1)))
		return true;
	return false;
 }
bool phone::find_2(const string& subStr)
{
	auto pos = first_name.find(subStr);
	if (pos != string::npos) return true;
	pos = last_name.find(subStr);
	if (pos != string::npos) return true;
	pos = patronymic.find(subStr);
	if (pos != string::npos) return true;
	pos = phone_number.find(subStr);
	if (pos != string::npos) return true;
	pos = email.find(subStr);
	if (pos != string::npos) return true;
	pos = company.find(subStr);
	return pos != string::npos;
}

string phone::gett() {
	return (phone_number);
}