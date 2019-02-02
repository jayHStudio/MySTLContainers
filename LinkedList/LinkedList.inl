
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
		// �ݺ��ڰ� ����Ű�� ��尡 ���ٸ� true�� ��ȯ�Ѵ�.
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
		// ���� ����Ű�� ��尡 �׸��� ���� ����Ų�ٸ� �ű��� �ʰ� �����Ѵ�.
		if (pCurrentNode == pList->pTail)
		{
			return;
		}

		// ���� ����Ű�� ��带 ��ĭ �̵���Ų��.
		pCurrentNode = pCurrentNode->pNextNode;
	}


	template<typename _List>
	void ConstListIterator<_List>::MovePrevNode()
	{
		// ���� ����Ű�� ��尡 �׸��� ó���� ����Ų�ٸ� �ű��� �ʰ� �����Ѵ�.
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

		// �Ӹ�, ������ ����Ű�� ���̳�带 �ٽ� ���� ����Ű���Ѵ�.
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

		// ������ �ִ� ��� �׸���� �� �����.
		// ���̳��� �̹� ������������Ƿ� �ٽ� ���� �ʿ䰡 ����.
		Erase(begin(), end());
		mNumOfData = 0;

		// ��� �׸��� �����Ѵ�.
		CopyFrom(rhs);
	}


	template <typename T>
	List<T>& List<T>::operator=(List<T>&& rhs) noexcept
	{
		// ������ �ִ� ��� �׸���� �� �����.
		// ���̳��� �̹� ������������Ƿ� �ٽ� ���� �ʿ䰡 ����.
		Erase(begin(), end());

		// �������縦 �Ͽ� �̵��Ѵ�.
		pHead = rhs.pHead;
		pTail = rhs.pTail;
		mNumOfData = rhs.mNumOfData;

		// �Ӹ�, ������ ����Ű�� ���̳�带 �ٽ� ���� ����Ű���Ѵ�.
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
		// ���ο� ��带 �����Ѵ�.
		Node<T>* newNode = new Node<T>;
		newNode->mData = inData;

		// ���ο� ��带 �մ´�.
		pTail->pPrevNode->pNextNode = newNode;
		newNode->pPrevNode = pTail->pPrevNode;

		newNode->pNextNode = pTail;
		pTail->pPrevNode = newNode;

		// �׸� ���� �ϳ� �ø���.
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
		// �Ӹ��� ����ų ���̳�带 �����Ѵ�.
		pHead = new Node<T>();

		// ������ ����ų ���̳�带 �����Ѵ�.
		pTail = new Node<T>();

		// ������ ������ �մ´�.
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