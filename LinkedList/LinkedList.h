// JayH 2019.02.03 ~

#pragma once

namespace JayH
{

	/* ---------------------------------------------------------------------------------------- */

	template <typename T>
	struct Node
	{
		Node();

		Node<T>* pNextNode;
		Node<T>* pPrevNode;

		T mData;
	};

	/* ---------------------------------------------------------------------------------------- */
	
	template <typename _List>
	class ConstListIterator
	{
		friend _List;

	public:
		using value_type = typename _List::value_type;

		ConstListIterator(const _List* list, Node<value_type>* currentNode);

		const value_type& operator*() const;
		const value_type* operator->() const;
		ConstListIterator<_List>& operator++();
		ConstListIterator<_List> operator++(int);
		ConstListIterator<_List>& operator--();
		ConstListIterator<_List> operator--(int);
		bool operator==(const ConstListIterator<_List>& rhs) const;
		bool operator!=(const ConstListIterator<_List>& rhs) const;

	protected:
		void MoveNextNode();
		void MovePrevNode();

		const _List* pList;
		Node<value_type>* pCurrentNode;

	};

	/* ---------------------------------------------------------------------------------------- */

	template <typename _List>
	class ListIterator : public ConstListIterator<_List>
	{

	public:
		using value_type = typename _List::value_type;

		ListIterator(const _List* list, Node<value_type>* currentNode);

		value_type& operator*();
		value_type* operator->();
		ListIterator<_List>& operator++();
		ListIterator<_List> operator++(int);
		ListIterator<_List>& operator--();
		ListIterator<_List> operator--(int);

	};

	/* ---------------------------------------------------------------------------------------- */

	template <typename T>
	class List
	{

	public:
		using value_type = T;
		using reference = T&;
		using const_reference = const T&;
		using iterator = ListIterator<List<T>>;
		using const_iterator = ConstListIterator<List<T>>;

		friend iterator;
		friend const_iterator;

		List(); virtual ~List();

		List(const List<T>& src);
		List(List<T>&& src) noexcept;
		List<T>& operator=(const List<T>& rhs);
		List<T>& operator=(List<T>&& rhs) noexcept;

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin();
		const_iterator cend();

		iterator Erase(iterator position);
		iterator Erase(iterator first, iterator last);

		size_t Size() const;

		void PushBack(const T& inData);
		iterator Insert(iterator position, const value_type& value);
		void Insert(iterator position, size_t n, const value_type& value);

		reference Front();
		const_reference Front() const;
		reference Back();
		const_reference Back() const;

	private:
		void CreateDummyNode();
		void CopyFrom(const List<T>& src);

		Node<T>* pHead;
		Node<T>* pTail;
		
		size_t mNumOfData;

	};

	/* ---------------------------------------------------------------------------------------- */
	
}

#include "LinkedList.inl"