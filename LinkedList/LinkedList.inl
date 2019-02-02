
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
	List<T>::List()
		: mNumOfData(0)
	{
		CreateDummyNode();
	}


	template <typename T>
	List<T>::~List()
	{
		if (mNumOfData != 0)
		{
			Erase(begin(), end());
		}

		delete pHead;
		delete pTail;
	}


	template <typename T>
	List<T>::List(const List<T>& src)
	{
		CreateDummyNode();

		CopyFrom(src);
	}


	template <typename T>
	List<T>::List(List<T>&& src) noexcept
	{
		pHead = src.pHead;
		pTail = src.pTail;
		mNumOfData = src.mNumOfData;

		// 머리, 꼬리가 가르키는 더미노드를 다시 만들어서 가르키게한다.
		src.CreateDummyNode();
		src.mNumOfData = 0;
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
		Erase(begin(), end());
		mNumOfData = 0;

		// 모든 항목을 복사한다.
		CopyFrom(rhs);
	}


	template <typename T>
	List<T>& List<T>::operator=(List<T>&& rhs) noexcept
	{
		// 기존에 있던 모든 항목들을 다 지운다.
		// 더미노드는 이미 만들어져있으므로 다시 만들 필요가 없다.
		Erase(begin(), end());

		// 얕은복사를 하여 이동한다.
		pHead = rhs.pHead;
		pTail = rhs.pTail;
		mNumOfData = rhs.mNumOfData;

		// 머리, 꼬리가 가르키는 더미노드를 다시 만들어서 가르키게한다.
		rhs.CreateDummyNode();
		rhs.mNumOfData = 0;
	}


	template<typename T>
	typename List<T>::iterator List<T>::begin()
	{
		return ListIterator<List<T>>(this, pHead->pNextNode);
	}


	template<typename T>
	typename List<T>::iterator List<T>::end()
	{
		return ListIterator<List<T>>(this, pTail);

	}


	template<typename T>
	typename List<T>::const_iterator List<T>::begin() const
	{
		return ConstListIterator<List<T>>(this, pHead->pNextNode);
	}


	template<typename T>
	typename List<T>::const_iterator List<T>::end() const
	{
		return ConstListIterator<List<T>>(this, pTail);
	}


	template<typename T>
	typename List<T>::const_iterator List<T>::cbegin()
	{
		return ConstListIterator<List<T>>(this, pHead->pNextNode);
	}


	template<typename T>
	typename List<T>::const_iterator List<T>::cend()
	{
		return ConstListIterator<List<T>>(this, pTail);
	}


	template<typename T>
	typename List<T>::iterator List<T>::Erase(iterator position)
	{
		iterator newIt(this, position.pCurrentNode);

		Node<T>* deleteNode = position.pCurrentNode;

		newIt.pCurrentNode->pPrevNode->pNextNode = position.pCurrentNode->pNextNode;
		newIt.pCurrentNode->pNextNode->pPrevNode = position.pCurrentNode->pPrevNode;

		newIt.pCurrentNode = position.pCurrentNode->pNextNode;

		delete deleteNode;
		mNumOfData--;

		return newIt;
	}


	template<typename T>
	typename List<T>::iterator List<T>::Erase(iterator first, iterator last)
	{
		for (auto& it = first; it != last;)
		{
			it = Erase(it);
		}

		return first;
	}


	template<typename T>
	size_t List<T>::Size() const
	{
		return mNumOfData;
	}


	template<typename T>
	void List<T>::PushBack(const T & inData)
	{
		// 새로운 노드를 생성한다.
		Node<T>* newNode = new Node<T>;
		newNode->mData = inData;

		// 새로운 노드를 잇는다.
		pTail->pPrevNode->pNextNode = newNode;
		newNode->pPrevNode = pTail->pPrevNode;

		newNode->pNextNode = pTail;
		pTail->pPrevNode = newNode;

		// 항목 수를 하나 늘린다.
		mNumOfData++;
	}


	template<typename T>
	typename List<T>::iterator List<T>::Insert(iterator position, const value_type& val)
	{
		Node<T>* newNode = new Node<T>();
		newNode->mData = val;

		position.pCurrentNode->pPrevNode->pNextNode = newNode;
		newNode->pPrevNode = position.pCurrentNode->pPrevNode;

		newNode->pNextNode = position.pCurrentNode;
		position.pCurrentNode->pPrevNode = newNode;

		mNumOfData++;

		return position;
	}


	template <typename T>
	void List<T>::Insert(iterator position, size_t n, const value_type& value)
	{
		for (size_t i = 0; i < n; i++)
		{
			Insert(position, value);
		}
	}


	template <typename T>
	typename List<T>::reference List<T>::Front()
	{
		return pHead->pNextNode->mData;
	}


	template <typename T>
	typename List<T>::const_reference List<T>::Front() const
	{
		return pHead->pNextNode->mData;
	}


	template <typename T>
	typename List<T>::reference List<T>::Back()
	{
		return pTail->pPrevNode->mData;
	}


	template <typename T>
	typename List<T>::const_reference List<T>::Back() const
	{
		return pTail->pPrevNode->mData;
	}


	template <typename T>
	void List<T>::CreateDummyNode()
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
			PushBack(*it);
		}
	}

#pragma endregion
	/* ---------------------------------------------------------------------------------------- */

}