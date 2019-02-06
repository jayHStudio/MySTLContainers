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

	// ����Ʈ �����ڸ� ����� ������
	// List<T>::const_iterator iterator; �� ���� �ʱ�ȭ ���� ���� �� �� �ְ� �ϴ°� �����̴�.
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
	List<T>::~List()
	{
		// �׸��� �ϳ��� ���ٸ� ������ �ʴ´�.
		if (mSize != 0)
		{
			erase(begin(), end());
		}

		// ���̳��� ������ �����ǹǷ� �׸��� ������ ���̳����� �޸𸮸� �ݵ�� ��������� �Ѵ�.
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
		// ������ ���� �����Ѵ�.
		pHead = src.pHead;
		pTail = src.pTail;
		mSize = src.mSize;

		// �Ӹ�, ������ ����Ű�� ���̳�带 �ٽ� ���� ����Ű���Ѵ�.
		// ���⼭ src.pHead�� src.pTail�� NullNode�� ����Ű�Եȴ�.
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

		// ������ �ִ� ��� �׸���� �� �����.
		// ���̳��� �̹� ������������Ƿ� �ٽ� ���� �ʿ䰡 ����.
		erase(begin(), end());

		// ��� �׸��� �����Ѵ�.
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

		// ������ �ִ� ��� �׸���� �� �����.
		// ���̳��� �̹� ������������Ƿ� �ٽ� ���� �ʿ䰡 ����.
		erase(begin(), end());

		// �������縦 �Ͽ� �̵��Ѵ�.
		pHead = rhs.pHead;
		pTail = rhs.pTail;
		mSize = rhs.mSize;

		// �Ӹ�, ������ ����Ű�� ���̳�带 �ٽ� ���� ����Ű���Ѵ�.
		rhs.CreateDmyNodesNConcatenate();
		rhs.mSize = 0;

		return *this;
	}


	template<typename T>
	List<T>& List<T>::operator=(std::initializer_list<value_type> il)
	{
		// ������ �ִ� ��� �׸��� �� �����.
		erase(begin(), end());

		insert(begin(), std::cbegin(il), std::cend(il));

		return *this;
	}

	
	template<typename T>
	typename List<T>::iterator List<T>::begin()
	{
		// �׸��� ����ִٸ� end()�� ����Ű�� �ݺ��ڸ� �����ؾ��Ѵ�.
		if (mSize == 0)
		{
			return end();
		}

		// begin()�� ��ġ�� Head�� ����Ű�� ���̳���� �����׸��̴�.
		return ListIterator<List<T>>(this, pHead->pNextNode);
	}


	template<typename T>
	typename List<T>::iterator List<T>::end()
	{
		// end()�� ��ġ�� ������ �׸��� ��ĭ ����ģ �׸�, ��, ������ ����Ű�� ���̳�尡 end()�� ��ġ�� �ȴ�.
		return ListIterator<List<T>>(this, pTail);
	}


	template<typename T>
	typename List<T>::const_iterator List<T>::begin() const
	{
		// non-const begin() �޼��带 ȣ���ϱ� ���� constĳ������ ����.
		// ���ϵ� iterator �� Ÿ���� const_iterator�� �Ͻ��� ��ĳ���õȴ�.
		return const_cast<List<T>*>(this)->begin();
	}


	template<typename T>
	typename List<T>::const_iterator List<T>::end() const
	{
		// non-const end() �޼��带 ȣ���ϱ� ���� constĳ������ ����.
		// ���ϵ� iterator �� Ÿ���� const_iterator�� �Ͻ��� ��ĳ���õȴ�.
		return const_cast<List<T>*>(this)->end();
	}


	template<typename T>
	typename List<T>::const_iterator List<T>::cbegin() const
	{
		// ���ϵ� iterator �� Ÿ���� const_iterator�� �Ͻ��� ��ĳ���õȴ�.
		return begin();
	}


	template<typename T>
	typename List<T>::const_iterator List<T>::cend() const
	{
		// ���ϵ� iterator �� Ÿ���� const_iterator�� �Ͻ��� ��ĳ���õȴ�.
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
		// ���ο� ��带 �����Ѵ�.
		Node<T>* newNode = new Node<T>;
		newNode->mData = data;

		// ���ο� ��带 �մ´�.
		pTail->pPrevNode->pNextNode = newNode;
		newNode->pPrevNode = pTail->pPrevNode;

		newNode->pNextNode = pTail;
		pTail->pPrevNode = newNode;

		// �׸� ���� �ϳ� �ø���.
		mSize++;
	}


	template<typename T>
	typename List<T>::iterator List<T>::insert(iterator position, const value_type& val)
	{
		// ���ο� ��带 �����Ѵ�.
		Node<T>* newNode = new Node<T>();
		newNode->mData = val;

		// position�� ����Ű�� ��忡 ���ο� ��带 �մ´�.
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
			push_back(*it);
		}
	}

#pragma endregion
	/* ---------------------------------------------------------------------------------------- */

}