// JayH 2019.02.03 ~
// STL 컨테이너 list를 직접 구현해본다.

#pragma once

#include <initializer_list>

namespace JayH
{

	/* ---------------------------------------------------------------------------------------- */

	template <typename T>
	struct Node
	{

	public:
		Node();

		Node<T>* pNextNode;
		Node<T>* pPrevNode;

		T mData;

	};

	/* ---------------------------------------------------------------------------------------- */

	template <typename _List>
	class ConstListIterator
	{

	public:
		using value_type = typename _List::value_type;

		friend _List;

		ConstListIterator();
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

		virtual ~List();

		List();
		List(const List<T>& src);
		List(std::initializer_list<value_type> il);
		template <typename InputIterator> List(InputIterator first, InputIterator last);
		List(List<T>&& src) noexcept;

		List<T>& operator=(const List<T>& rhs);
		List<T>& operator=(List<T>&& rhs) noexcept;
		List<T>& operator=(std::initializer_list<value_type> il);

		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;

		iterator end();
		const_iterator end() const;
		const_iterator cend() const;

		void push_back(const T& inData);
		iterator insert(iterator position, const value_type& value);
		void insert(iterator position, size_t n, const value_type& value);
		template <typename InputIterator> void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		void clear();
		size_t size() const;

	private:
		void CreateDmyNodesNConcatenate();
		void CopyFrom(const List<T>& src);

		Node<T>* pHead;
		Node<T>* pTail;

		size_t mSize;

	};

	/* ---------------------------------------------------------------------------------------- */

}

#include "LinkedList.inl"