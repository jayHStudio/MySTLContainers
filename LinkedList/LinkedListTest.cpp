// JayH

#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include <list>
#include <vector>
#include <iostream>
#include <iomanip>

#include "LinkedList.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif
#endif

using namespace JayH;
using namespace std;

template <typename T>
void PrintListElements(const List<T>& list)
{
	cout << "[Size : " << list.size() << "]  ";
	for (auto it = list.cbegin(); it != list.cend(); ++it)
	{
		cout << *it << " ";
	}

	cout << "\n\n\n";
}

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	constexpr size_t setwNum = 90;

	List<int> myList1;

	cout << setiosflags(ios::left);
	cout << setfill('-');
	cout << setw(setwNum) << " [myList����] " << endl;
	cout << setw(setwNum) << " [PushBack 5, 10, 13, 11] " << endl;
	myList1.push_back(5);
	myList1.push_back(10);
	myList1.push_back(13);
	myList1.push_back(11);

	cout << endl;

	/* ---------------------------------------------------------------------------------------- */

	cout << setw(setwNum) << " [�ݺ��ڸ� ���� for�� �׽�Ʈ] " << endl;
	cout << "   myList1 : ";
	for (List<int>::const_iterator it = myList1.cbegin(); it != myList1.cend(); ++it)
	{
		cout << *it << " ";
	}
	cout << "\n\n";

	/* ---------------------------------------------------------------------------------------- */

	cout << setw(setwNum) << " [STL���� ���ø� �޼ҵ� begin() end() �׽�Ʈ] " << endl;
	cout << "   myList1 : ";
	for (auto it = begin(myList1); it != end(myList1); ++it)
	{
		cout << *it << " ";
	}
	cout << "\n\n";

	/* ---------------------------------------------------------------------------------------- */

	cout << setw(setwNum) << " [���� ���� �ݺ��� �׽�Ʈ] " << endl;
	cout << "   myList1 : ";
	for (auto& it : myList1)
	{
		cout << it << " ";
	}
	cout << "\n\n";

	/* ---------------------------------------------------------------------------------------- */

	cout << setw(setwNum) << " [�ٸ� �����̳��� �ݺ��ڱ��������� ������ ȣ�� �׽�Ʈ] " << endl;
	
	vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// vec�� ó������ ������ �ݺ��ڸ� ��ȸ�ؼ� myList2 �����̳ʸ� �ʱ�ȭ�Ѵ�.
	List<int> myList2(cbegin(vec), cend(vec));
	
	cout << "   myList2 : ";
	PrintListElements(myList2);

	/* ---------------------------------------------------------------------------------------- */

	cout << setw(setwNum) << " [Initialize_list�� �̿��� �ʱ�ȭ �׽�Ʈ] " << endl;

	List<int> myList3 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	cout << "   myList3 : ";
	PrintListElements(myList3);

	/* ---------------------------------------------------------------------------------------- */

	cout << setw(setwNum) << " [�ݺ��� ���������� Insert �׽�Ʈ] " << endl;
	
	vector<int> vecSrc1 = { 3, 2, 1 };

	auto it = begin(myList3);
	++it;
	++it;
	++it;

	myList3.insert(it, cbegin(vecSrc1), cend(vecSrc1));
	PrintListElements(myList3);

	/* ---------------------------------------------------------------------------------------- */

	cout << setw(setwNum) << " [clear() �׽�Ʈ] " << endl;

	myList3.clear();

	PrintListElements(myList3);

	/* ---------------------------------------------------------------------------------------- */

	cout << setw(setwNum) << " [initialize_list�� �������� �޴� ���Կ�����] " << endl;

	myList3.push_back(5);

	myList3 = { 5, 4, 3, 2, 1 };
	
	PrintListElements(myList3);

	system("PAUSE");
}