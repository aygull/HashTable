#pragma once
#include"iostream"
#include"string"
#include<fstream>
using namespace std;

class phone
{
private:
	
public:
	
	string first_name, last_name, patronymic, phone_number, email, company, position;
	phone();
	phone(const string& first_name, const string& last_name, const string& patronymic, const string& phone_number, const string& email, const string& company, const string& position);
	~phone();
	bool find_2(const string&);
	friend ostream& operator<<(ostream&, phone&);
	friend istream& operator>>(istream&, phone&);
	friend ofstream& operator<< (ofstream&, phone&);
	bool operator==(const string&)const;
	string gett();

	template <typename T>
	friend bool operator==(const T&, const phone& right) {
		return true;
	}
};


