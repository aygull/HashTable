#pragma once

#include <vector>
#include <string>
#include <list>
#include <fstream>

#define DEFAULT_SIZE 128

using namespace std;

template <typename tKey, typename tData>
class HashTab
{
public:
	HashTab() { myTable.resize(DEFAULT_SIZE); }
	HashTab(int size) { myTable.resize(size); }
	~HashTab() = default;

	int hashFunc(const string&) const;
	int hashFunc(const int&) const;
	void insert(const tKey&, const tData&);

	class hash_iterator
	{
	public:
		hash_iterator() = default;
		hash_iterator(const HashTab*, int, int);
		bool operator== (const hash_iterator&) const;
		bool operator!= (const hash_iterator&) const;
		hash_iterator& operator++ (int n);
		tData operator*();
	private:
		tData curStruct;
		const HashTab<tKey, tData> *curTable;
		int curIndexVec = 0, curIndexList = 0;
	};

	hash_iterator begin() const;
	hash_iterator end() const;
	list<tData> operator[](const tKey&) const;
	hash_iterator find(const tKey&) const;
	hash_iterator find_2(const string&) const;
	friend ofstream& operator<< <tKey, tData>(ofstream&, const HashTab&);
	friend ifstream& operator>> <tKey, tData>(ifstream&, HashTab&);
	friend ostream& operator<< <tKey, tData>(ostream&, const HashTab&);
//	friend istream& operator >> <tKey, tData>(istream&, hash_table&);
	void remove(const tKey&);
	void cancelFunc(int m);
	vector<int> cancelArr;
	vector<pair<tKey, tData>> for_ins;
	vector<pair<tKey, tData>> for_remove;
private:
	vector<list<tData>> myTable;
};

template<typename tKey, typename tData>
ostream& operator<<(ostream& out, const HashTab<tKey, tData>& table)
{
	for (auto i = table.myTable.begin(); i != table.myTable.end(); i++) {
		if (!(*i).empty()) {
			for (auto j : (*i)) {
				out << j << " ";
			}
			out << endl;
		}
	}
	return out;
}

template<typename tKey, typename tData>
ifstream& operator>> (ifstream& file_in, HashTab<tKey, tData>& table)
{
	tData tmp_data;
	tKey tmp_key;
	while (file_in >> tmp_data >>  tmp_key)
		table.insert(tmp_key, tmp_data);
	return file_in;
}

template <typename tKey, typename tData>
int HashTab<tKey, tData>::hashFunc(const string& key) const
{
	int result = 0;
	for (auto i = 0; i < key.length(); i++)
		result += key[i] * key.length() - 10;
	return result % myTable.size();
}

template <typename tKey, typename tData>
int HashTab<tKey, tData>::hashFunc(const int& key) const
{
	return key % myTable.size();
}

template <typename tKey, typename tData>
ofstream& operator<<(ofstream& file_out, const HashTab<tKey, tData>& table)
{
	for (auto i = table.myTable.begin(); i != table.myTable.end(); i++) {
		for (auto j : (*i)) {
			file_out << j << " ";
		}
		file_out << endl;
	}
	return file_out;
}

template <typename tKey, typename tData>
void HashTab<tKey, tData>::insert(const tKey& key, const tData& data)
{
	int hashKey = hashFunc(key);
	tData myStruct = data;
	typename list<tData>::iterator findIter = std::find(myTable[hashKey].begin(),
		myTable[hashKey].end(), data);
	if (findIter == myTable[hashKey].end()) //метод цепочек
		myTable[hashKey].push_back(myStruct);
	else
		*findIter = data;
	cancelArr.push_back(1);
	pair<tKey, tData> tmpPair(key, data);
	for_ins.push_back(tmpPair);
}

template <typename tKey, typename tData>
typename HashTab<tKey, tData>::hash_iterator HashTab<tKey, tData>::begin() const
{
	int beginIndex = 0, size = myTable.size();
	for (int i = 0; i < size; i++)
	{
		if (!myTable[i].empty())
		{
			beginIndex = i;
			break;
		}
	}
	return hash_iterator(this, beginIndex, 0);
}

template <typename tKey, typename tData>
typename HashTab<tKey, tData>::hash_iterator HashTab<tKey, tData>::end() const{
	return hash_iterator(this, myTable.size(), 0);
}

template <typename tKey, typename tData>
HashTab<tKey, tData>::hash_iterator::hash_iterator(const HashTab* table, int indexVec, int indexList)
{
	curTable = table;
	if (indexVec == curTable->myTable.size())
	{
		return;
	}
	if (curTable->myTable[indexVec].begin() != curTable->myTable[indexVec].end())
		curStruct = *next(curTable->myTable[indexVec].begin(), indexList);
	curIndexVec = indexVec;
	curIndexList = indexList;
}

template <typename tKey, typename tData>
bool HashTab<tKey, tData>::hash_iterator::operator== (const hash_iterator& right) const
{
	return (curStruct == right.curStruct);
}

template <typename tKey, typename tData>
bool HashTab<tKey, tData>::hash_iterator::operator!= (const hash_iterator& right) const
{
	return (curStruct != right.curStruct);
}

template <typename tKey, typename tData>
typename HashTab<tKey, tData>::hash_iterator& HashTab<tKey, tData>::hash_iterator::operator++ (int n)
{
	if (curTable->myTable[curIndexVec].size() - 1 == curIndexList)
	{
		int tmpIndex = curIndexVec;
		for (int i = curIndexVec + 1; i < curTable->myTable.size(); i++)
		{
			if (!curTable->myTable[i].empty())
			{
				curIndexVec = i;
				break;
			}
		}
		if (tmpIndex == curIndexVec)
		{
			curStruct = nullptr;
			return *this;
		}
		curIndexList = 0;
	}
	else
		curIndexList++;
	if (curStruct == nullptr)
		return *this;
	curStruct = &(*next(curTable->myTable[curIndexVec].begin(), curIndexList));
	return *this;
}

template <typename tKey, typename tData>
void HashTab<tKey, tData>::cancelFunc(int m)
{
	int n = 0, k = 0, f = 0;
	for (int i = 0; i < m && i < cancelArr.size(); i += 2)
	{
		if (cancelArr[i] == 2)
			insert(for_remove[n].first, for_ins[n++].second);
		else
			remove(for_ins[k++].first);
		f++;
	}
	cancelArr.clear();
	for_remove.clear();
	for_ins.clear();
}

template <typename tKey, typename tData>
tData HashTab<tKey, tData>::hash_iterator::operator*()
{
	return curStruct;
}

template <typename tKey, typename tData>
list<tData> HashTab<tKey, tData>::operator[](const tKey& key) const
{
	return myTable[hashFunc(key)];
}

template <typename tKey, typename tData>
typename HashTab<tKey, tData>::hash_iterator HashTab<tKey, tData>::find(const tKey& key) const
{
	int hashKey = hashFunc(key), indexList = 0;
	for (auto jt : myTable[hashKey])
	{
		indexList++;
		if (jt.key == key)
			return hash_iterator(this, hashKey, indexList-1);
	}
	return hash_iterator(this, myTable.size(), 0);
}

template <typename tKey, typename tData>
typename HashTab<tKey, tData>::hash_iterator HashTab<tKey, tData>::find_2(const string& string_1) const
{

	for (int hashKey = 0; hashKey < myTable.size(); hashKey++)
	{
		int indexList = 0;
		for (auto jt : myTable[hashKey])
		{
			indexList++;
			if (jt.find_2(string_1))
				return hash_iterator(this, hashKey, indexList-1);
		}
	}
	return hash_iterator(this, myTable.size(), 0);
}
template <typename tKey, typename tData>
void HashTab<tKey, tData>::remove(const tKey& key)
{
	int hashKey = hashFunc(key);
	for (auto jt : myTable[hashKey])
	{
		myTable[hashKey].remove(jt);
		return;
	}
}