// JayH

#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include <list>
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
	for (auto it = list.cbegin(); it != list.cend(); ++it)
	{
		cout << *it << " ";
	}

	cout << endl;
}

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	constexpr size_t setwNum = 90;

	List<int> myList1;

	cout << setiosflags(ios::left);
	cout << setfill('-');
	cout << setw(setwNum) << " [myList생성] " << endl;
	cout << setw(setwNum) << " [PushBack 5, 10, 13, 11] " << endl;
	myList1.push_back(5);
	myList1.push_back(10);
	myList1.push_back(13);
	myList1.push_back(11);

	cout << endl;

	/* ---------------------------------------------------------------------------------------- */

	cout << setw(setwNum) << " [반복자를 통한 for문 테스트] " << endl;
	cout << "   myList1 : ";
	for (List<int>::const_iterator it = myList1.cbegin(); it != myList1.cend(); ++it)
	{
		cout << *it << " ";
	}
	cout << "\n\n";

	/* ---------------------------------------------------------------------------------------- */

	cout << setw(setwNum) << " [STL전역 템플릿 메소드 begin() end() 테스트] " << endl;
	cout << "   myList1 : ";
	for (auto it = begin(myList1); it != end(myList1); ++it)
	{
		cout << *it << " ";
	}
	cout << "\n\n";

	/* ---------------------------------------------------------------------------------------- */

	cout << setw(setwNum) << " [구간 지정 반복문 테스트] " << endl;
	cout << "   myList1 : ";
	for (auto& it : myList1)
	{
		cout << it << " ";
	}
	cout << "\n\n";

	system("PAUSE");
}