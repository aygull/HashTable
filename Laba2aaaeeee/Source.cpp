#include <iostream>
#include <fstream>
#include "hash_table.h"
#include "phone.h"
#include<cstdlib>
#include<ctime>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	HashTab<string, phone> myTable;
	phone my_phone;
	int count, search;
	string string_1, string_2, key;
	count = -1;
	search = -1;
	ifstream in("g.txt");
	in >> myTable;
	in.close();
	ofstream out("g.txt");
	HashTab<string, phone>::hash_iterator it;
	srand(time(NULL));
	while (count != 0) {
		cout << "�������:\n1-�������� ������ � �����\n2-�����\n3-�������� ������\n4-����� �����\n5-������\n0-�����\n";
		cin >> count;
		switch (count) {
		case 1: {
			cout << "������� �������: ���: ��������: �����: ��������: �����: ���������" << endl;
			cin >> my_phone;
			myTable.insert(my_phone.gett(), my_phone);
			break;
		}
		case 2: {
			cout << "������� ��������" << endl;
			cin >> string_1;
			it = myTable.find_2(string_1);
			cout << *it <<endl;
			break;
		}
		case 3: {
			cout << "������� ����";
			cin >> key;
			myTable.remove(key);
			cout << "�������  �������: ���: ��������: �����: ��������: �����: ���������\n";
			cin >> my_phone;
			myTable.insert(key, my_phone);
			break;
		}
		case 4: {
			cout << myTable;
			break;
		}
		case 5: {
			myTable.cancelFunc(1);
			break;
		}
		case 0: {
			out << myTable;
			out.close();
			break;
			//exit(1);
		}
		}
	}

	cin.get();
	return 0;
}