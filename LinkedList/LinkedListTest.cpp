// JayH

#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include <list>

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

void Test()
{

}

int main(void)
{
	// 디버그 모드일때 메모리릭이 발생하는지 로그를 찍는다.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	Test();

	
	system("pause");
}