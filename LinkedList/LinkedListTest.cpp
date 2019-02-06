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

	/* ---------------------------------------------------------------------------------------- */

	cout << setw(setwNum) << " [다른 컨테이너의 반복자구간으로의 생성자 호출 테스트] " << endl;
	
	vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// vec의 처음부터 끝까지 반복자를 순회해서 myList2 컨테이너를 초기화한다.
	List<int> myList2(cbegin(vec), cend(vec));
	
	cout << "   myList2 : ";
	PrintListElements(myList2);

	/* ---------------------------------------------------------------------------------------- */

	cout << setw(setwNum) << " [Initialize_list를 이용한 초기화 테스트] " << endl;

	List<int> myList3 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	cout << "   myList3 : ";
	PrintListElements(myList3);

	/* ---------------------------------------------------------------------------------------- */

	cout << setw(setwNum) << " [반복자 구간으로의 Insert 테스트] " << endl;
	
	vector<int> vecSrc1 = { 3, 2, 1 };

	auto it = begin(myList3);
	++it;
	++it;
	++it;

	myList3.insert(it, cbegin(vecSrc1), cend(vecSrc1));
	PrintListElements(myList3);

	/* ---------------------------------------------------------------------------------------- */

	cout << setw(setwNum) << " [clear() 테스트] " << endl;

	myList3.clear();

	PrintListElements(myList3);

	/* ---------------------------------------------------------------------------------------- */

	cout << setw(setwNum) << " [initialize_list를 우항으로 받는 대입연산자] " << endl;

	myList3.push_back(5);

	myList3 = { 5, 4, 3, 2, 1 };
	
	PrintListElements(myList3);

	system("PAUSE");
}