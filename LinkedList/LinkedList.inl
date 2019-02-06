#include "LinkedList.h"

namespace JayH
{

	/* ---------------------------------------------------------------------------------------- */
#pragma region NodeClassImpl

	template <typename T>
	Node<T>::Node()
		: mData(T())
		, pNextNode(nullptr)
		, pPrevNode(nullptr)
	{
	}

#pragma endregion
	/* ---------------------------------------------------------------------------------------- */
#pragma region ConstListIteratorClassImpl

	// 디폴트 생성자를 만드는 이유는
	// List<T>::const_iterator iterator; 와 같이 초기화 없이 선언 할 수 있게 하는게 목적이다.
	template<typename _List>
	ConstListIterator<_List>::ConstListIterator()
		: pList(nullptr)
		, pCurrentNode(nullptr)
	{
	}


	template <typename _List>
	ConstListIterator<_List>::ConstListIterator(const _List* list, Node<value_type>* currentNode)
		: pList(list)
		, pCurrentNode(currentNode)
	{
	}


	template <typename _List>
	typename const ConstListIterator<_List>::value_type& ConstListIterator<_List>::operator*() const
	{
		return pCurrentNode->mData;
	}


	template <typename _List>
	typename const ConstListIterator<_List>::value_type* ConstListIterator<_List>::operator->() const
	{
		return &(pCurrentNode->mData);
	}


	template <typename _List>
	ConstListIterator<_List>& ConstListIterator<_List>::operator++()
	{
		MoveNextNode();

		return *this;
	}


	template<typename _List>
	ConstListIterator<_List> ConstListIterator<_List>::operator++(int)
	{
		auto oldIt = *this;

		MoveNextNode();

		return oldIt;
	}


	template<typename _List>
	ConstListIterator<_List>& ConstListIterator<_List>::operator--()
	{
		MovePrevNode();

		return *this;
	}


	template<typename _List>
	ConstListIterator<_List> ConstListIterator<_List>::operator--(int)
	{
		auto oldIt = *this;

		MovePrevNode();

		return oldIt;
	}


	template <typename _List>
	bool ConstListIterator<_List>::operator==(const ConstListIterator<_List>& rhs) const
	{
		// 반복자가 가르키는 노드가 같다면 true를 반환한다.
		if (pCurrentNode == rhs.pCurrentNode && pList == rhs.pList)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	template <typename _List>
	bool ConstListIterator<_List>::operator!=(const ConstListIterator<_List>& rhs) const
	{
		return !(*this == rhs);
	}


	template<typename _List>
	void ConstListIterator<_List>::MoveNextNode()
	{
		// 현재 가르키는 노드가 항목의 끝을 가르킨다면 옮기지 않고 리턴한다.
		if (pCurrentNode == pList->pTail)
		{
			return;
		}

		// 현재 가르키는 노드를 한칸 이동시킨다.
		pCurrentNode = pCurrentNode->pNextNode;
	}


	template<typename _List>
	void ConstListIterator<_List>::MovePrevNode()
	{
		// 현재 가르키는 노드가 항목의 처음을 가르킨다면 옮기지 않고 리턴한다.
		if (pCurrentNode->pPrevNode == pList->pHead)
		{
			return;
		}

		pCurrentNode = pCurrentNode->pPrevNode;
	}

#pragma endregion
	/* ---------------------------------------------------------------------------------------- */
#pragma region ListIteratorClassImpl

	template<typename _List>
	ListIterator<_List>::ListIterator(const _List* list, Node<value_type>* currentNode)
		: ConstListIterator<_List>(list, currentNode)
	{
	}


	template<typename _List>
	typename ListIterator<_List>::value_type& ListIterator<_List>::operator*()
	{
		return const_cast<value_type&>(this->pCurrentNode->mData);
	}


	template<typename _List>
	typename ListIterator<_List>::value_type* ListIterator<_List>::operator->()
	{
		return const_cast<value_type*>(&(this->pCurrentNode->mData));
	}


	template<typename _List>
	ListIterator<_List>& ListIterator<_List>::operator++()
	{
		this->MoveNextNode();

		return *this;
	}


	template<typename _List>
	ListIterator<_List> ListIterator<_List>::operator++(int)
	{
		auto oldIt = *this;

		this->MoveNextNode();

		return oldIt;
	}


	template<typename _List>
	ListIterator<_List>& ListIterator<_List>::operator--()
	{
		this->MovePrevNode();

		return *this;
	}


	template<typename _List>
	ListIterator<_List> ListIterator<_List>::operator--(int)
	{
		auto oldIt = *this;

		this->MovePrevNode();

		return oldIt;
	}

#pragma endregion
	/* ---------------------------------------------------------------------------------------- */
#pragma region ListClassImpl

	template <typename T>
	List<T>::~List()
	{
		// 항목이 하나도 없다면 지우지 않는다.
		if (mSize != 0)
		{
			erase(begin(), end());
		}

		// 더미노드는 무조건 생성되므로 항목이 없더라도 더미노드들의 메모리를 반드시 해제해줘야 한다.
		delete pHead;
		delete pTail;
	}


	template <typename T>
	List<T>::List()
		: mSize(0)
	{
		CreateDmyNodesNConcatenate();
	}


	template<typename T>
	template<typename InputIterator>
	List<T>::List(InputIterator first, InputIterator last)
	{
		CreateDmyNodesNConcatenate();

		insert(begin(), first, last);
	}

	
	template <typename T>
	List<T>::List(const List<T>& src)
	{
		CreateDmyNodesNConcatenate();

		CopyFrom(src);
	}


	template<typename T>
	List<T>::List(std::initializer_list<value_type> il)
	{
		CreateDmyNodesNConcatenate();

		insert(begin(), std::cbegin(il), std::cend(il));
	}


	template <typename T>
	List<T>::List(List<T>&& src) noexcept
	{
		// 변수의 값을 이전한다.
		pHead = src.pHead;
		pTail = src.pTail;
		mSize = src.mSize;

		// 머리, 꼬리가 가르키는 더미노드를 다시 만들어서 가르키게한다.
		// 여기서 src.pHead와 src.pTail은 NullNode를 가르키게된다.
		src.CreateDmyNodesNConcatenate();
		src.mSize = 0;
	}


	template <typename T>
	List<T>& List<T>::operator=(const List<T>& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		// 기존에 있던 모든 항목들을 다 지운다.
		// 더미노드는 이미 만들어져있으므로 다시 만들 필요가 없다.
		erase(begin(), end());

		// 모든 항목을 복사한다.
		CopyFrom(rhs);

		return *this;
	}


	template <typename T>
	List<T>& List<T>::operator=(List<T>&& rhs) noexcept
	{
		if (this == &rhs)
		{
			return *this;
		}

		// 기존에 있던 모든 항목들을 다 지운다.
		// 더미노드는 이미 만들어져있으므로 다시 만들 필요가 없다.
		erase(begin(), end());

		// 얕은복사를 하여 이동한다.
		pHead = rhs.pHead;
		pTail = rhs.pTail;
		mSize = rhs.mSize;

		// 머리, 꼬리가 가르키는 더미노드를 다시 만들어서 가르키게한다.
		rhs.CreateDmyNodesNConcatenate();
		rhs.mSize = 0;

		return *this;
	}


	template<typename T>
	List<T>& List<T>::operator=(std::initializer_list<value_type> il)
	{
		// 기존에 있던 모든 항목을 다 지운다.
		erase(begin(), end());

		insert(begin(), std::cbegin(il), std::cend(il));

		return *this;
	}

	
	template<typename T>
	typename List<T>::iterator List<T>::begin()
	{
		// 항목이 비어있다면 end()가 가르키는 반복자를 리턴해야한다.
		if (mSize == 0)
		{
			return end();
		}

		// begin()의 위치는 Head가 가르키는 더미노드의 다음항목이다.
		return ListIterator<List<T>>(this, pHead->pNextNode);
	}


	template<typename T>
	typename List<T>::iterator List<T>::end()
	{
		// end()의 위치는 마지막 항목을 한칸 지나친 항목, 즉, 꼬리가 가르키는 더미노드가 end()의 위치가 된다.
		return ListIterator<List<T>>(this, pTail);
	}


	template<typename T>
	typename List<T>::const_iterator List<T>::begin() const
	{
		// non-const begin() 메서드를 호출하기 위해 const캐스팅을 쓴다.
		// 리턴된 iterator 형 타입은 const_iterator로 암시적 업캐스팅된다.
		return const_cast<List<T>*>(this)->begin();
	}


	template<typename T>
	typename List<T>::const_iterator List<T>::end() const
	{
		// non-const end() 메서드를 호출하기 위해 const캐스팅을 쓴다.
		// 리턴된 iterator 형 타입은 const_iterator로 암시적 업캐스팅된다.
		return const_cast<List<T>*>(this)->end();
	}


	template<typename T>
	typename List<T>::const_iterator List<T>::cbegin() const
	{
		// 리턴된 iterator 형 타입은 const_iterator로 암시적 업캐스팅된다.
		return begin();
	}


	template<typename T>
	typename List<T>::const_iterator List<T>::cend() const
	{
		// 리턴된 iterator 형 타입은 const_iterator로 암시적 업캐스팅된다.
		return end();
	}


	template<typename T>
	typename List<T>::iterator List<T>::erase(iterator position)
	{
		iterator newIt(this, position.pCurrentNode);

		Node<T>* deleteNode = position.pCurrentNode;

		newIt.pCurrentNode->pPrevNode->pNextNode = position.pCurrentNode->pNextNode;
		newIt.pCurrentNode->pNextNode->pPrevNode = position.pCurrentNode->pPrevNode;

		newIt.pCurrentNode = position.pCurrentNode->pNextNode;

		delete deleteNode;
		mSize--;

		return newIt;
	}


	template<typename T>
	typename List<T>::iterator List<T>::erase(iterator first, iterator last)
	{
		for (auto& it = first; it != last;)
		{
			it = erase(it);
		}

		return first;
	}


	template<typename T>
	void List<T>::clear()
	{
		erase(begin(), end());
	}


	template<typename T>
	size_t List<T>::size() const
	{
		return mSize;
	}


	template<typename T>
	void List<T>::push_back(const T& data)
	{
		// 새로운 노드를 생성한다.
		Node<T>* newNode = new Node<T>;
		newNode->mData = data;

		// 새로운 노드를 잇는다.
		pTail->pPrevNode->pNextNode = newNode;
		newNode->pPrevNode = pTail->pPrevNode;

		newNode->pNextNode = pTail;
		pTail->pPrevNode = newNode;

		// 항목 수를 하나 늘린다.
		mSize++;
	}


	template<typename T>
	typename List<T>::iterator List<T>::insert(iterator position, const value_type& val)
	{
		// 새로운 노드를 생성한다.
		Node<T>* newNode = new Node<T>();
		newNode->mData = val;

		// position이 가르키는 노드에 새로운 노드를 잇는다.
		position.pCurrentNode->pPrevNode->pNextNode = newNode;
		newNode->pPrevNode = position.pCurrentNode->pPrevNode;

		newNode->pNextNode = position.pCurrentNode;
		position.pCurrentNode->pPrevNode = newNode;

		mSize++;

		return position;
	}


	template <typename T>
	void List<T>::insert(iterator position, size_t n, const value_type& value)
	{
		for (size_t i = 0; i < n; i++)
		{
			insert(position, value);
		}
	}


	template<typename T>
	template<typename InputIterator>
	void List<T>::insert(iterator position, InputIterator first, InputIterator last)
	{
		for (auto it = first; it != last; ++it)
		{
			insert(position, *it);
		}
	}


	template <typename T>
	typename List<T>::reference List<T>::front()
	{
		return pHead->pNextNode->mData;
	}


	template <typename T>
	typename List<T>::const_reference List<T>::front() const
	{
		return pHead->pNextNode->mData;
	}


	template <typename T>
	typename List<T>::reference List<T>::back()
	{
		return pTail->pPrevNode->mData;
	}


	template <typename T>
	typename List<T>::const_reference List<T>::back() const
	{
		return pTail->pPrevNode->mData;
	}


	template <typename T>
	void List<T>::CreateDmyNodesNConcatenate()
	{
		// 머리가 가르킬 더미노드를 생성한다.
		pHead = new Node<T>();

		// 꼬리가 가르킬 더미노드를 생성한다.
		pTail = new Node<T>();

		// 생성된 노드들을 잇는다.
		pHead->pPrevNode = nullptr;
		pHead->pNextNode = pTail;

		pTail->pPrevNode = pHead;
		pTail->pNextNode = nullptr;
	}


	template <typename T>
	void List<T>::CopyFrom(const List<T>& src)
	{
		for (auto it = src.begin(); it != src.end(); ++it)
		{
			push_back(*it);
		}
	}

#pragma endregion
	/* ---------------------------------------------------------------------------------------- */

}