#ifndef MYLIST_H
#define MYLIST_H


#include <exception>

/// <summary>
/// Шаблонный класс для двусвязного циклического списка
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T> class MyList {
private:
	struct ListNode
	{
		T* info;
		ListNode *prev, *next;
	};
	ListNode *root;
	int _size;
public:
	//Итератор MyList
	class Iterator {
		template <class T> friend class MyList;
	protected:
		ListNode* node;
	public:
		Iterator(ListNode*);
		Iterator(const Iterator&);
		
		Iterator operator++(int);
		Iterator operator++();
		Iterator operator--(int);
		Iterator operator--();
		Iterator& operator=(const Iterator&);
		T& operator*();

		bool IsNull() const;
		bool operator==(const Iterator&) const;
		bool operator!=(const Iterator&) const;

		~Iterator();
	};
	MyList();
	MyList(const T&);
	/// <summary>
	/// Конструктор, создающий список из массива
	/// </summary>
	/// <param name="Указатель на массив"></param>
	/// <param name="Кол-во объектов"></param>
	MyList(const T*, int);
	MyList(const MyList&);

	//Добавление в конец
	void push_back(const T&);
	//Добавление в начало
	void push_front(const T&);
	//Удаление последнего элемента
	void pop_back();
	//Удаление первого элемента
	void pop_front();
	//Добавление элемента на произвольную позицию
	void insert(const T&, int) throw(std::out_of_range);
	/// <summary>
	/// Добавление элемента на позицию, указанную итератором
	/// </summary>
	/// <returns>Итератор на добавленный элемент</returns>
	Iterator insert(const T&, Iterator);
	// Удаляет элемент по заданному индексу
	void erase(int) throw(std::out_of_range);
	/// <summary>
	/// Удаляет элемент по заданному итератору
	/// </summary>
	/// <returns>Итератор на следующий за удалённым элемент. "Пустой" итератор, если элементов больше нет</returns>
	Iterator erase(Iterator);
	//Очищение списка
	void clear();

	//Возвращает итератор на первый элемент
	Iterator begin();
	//Возвращает итератор на последний элемент
	Iterator end();
	//Возвращает итератор на элемент по указанному индексу
	Iterator get(int) throw(std::out_of_range);

	/// <summary>
	/// Поиск элемента в списке
	/// </summary>
	/// <returns>Индекс первого вхождения элемента в список. -1 в случае отстутсвия элемента в списке</returns>
	int find(const T&) const;
	//Размер списка
	int size() const;
	/// <summary>
	/// Проверка на пустоту
	/// </summary>
	/// <returns>true, если список пуст. false в противном случае</returns>
	bool empty() const;
	

	~MyList();

	T& operator[](int) throw(std::out_of_range);
	void operator=(const MyList&);
	
};

/// <summary>
/// Специализация шаблона MyList для C-style строк
/// </summary>
template <> class MyList<char*> {
private:
	struct ListNode
	{
		char* info;
		ListNode* prev, * next;
	};
	ListNode* root;
	int _size;
public:
	//Итератор MyList
	class Iterator {
		friend class MyList<char*>;
	protected:
		ListNode* node;
	public:
		Iterator(ListNode*);
		Iterator(const Iterator&);

		Iterator operator++(int);
		Iterator operator++();
		Iterator operator--(int);
		Iterator operator--();
		Iterator& operator=(const Iterator&);
		char* operator*();

		bool IsNull() const;
		bool operator==(const Iterator&) const;
		bool operator!=(const Iterator&) const;

		~Iterator();
	};
	MyList();
	MyList(const char*);
	MyList(const MyList&);

	//Добавление в конец
	void push_back(const char*);
	//Добавление в начало
	void push_front(const char*);
	//Удаление последнего элемента
	void pop_back();
	//Удаление первого элемента
	void pop_front();
	//Добавление элемента на произвольную позицию
	void insert(const char*, int ) throw(std::out_of_range);
	/// <summary>
	/// Добавление элемента на позицию, указанную итератором
	/// </summary>
	/// <returns>Итератор на добавленный элемент</returns>
	Iterator insert(const char*, Iterator);
	// Удаляет элемент по заданному индексу
	void erase(int) throw(std::out_of_range);
	/// <summary>
	/// Удаляет элемент по заданному итератору
	/// </summary>
	/// <returns>Итератор на следующий за удалённым элемент. "Пустой" итератор, если элементов больше нет</returns>
	Iterator erase(Iterator);
	//Очищение списка
	void clear();

	//Возвращает итератор на первый элемент
	Iterator begin();
	//Возвращает итератор на последний элемент
	Iterator end();
	//Возвращает итератор на элемент по указанному индексу
	Iterator get(int) throw(std::out_of_range);

	/// <summary>
	/// Поиск элемента в списке
	/// </summary>
	/// <returns>Индекс первого вхождения элемента в список. -1 в случае отстутсвия элемента в списке</returns>
	int find(const char*) const;
	//Размер списка
	int size() const;
	/// <summary>
	/// Проверка на пустоту
	/// </summary>
	/// <returns>true, если список пуст. false в противном случае</returns>
	bool empty() const;


	~MyList();

	char* operator[](int) throw(std::out_of_range);
	void operator=(const MyList&);


};


//Определения MyList

template<class T>
inline MyList<T>::MyList() : _size(0), root(nullptr)
{
}

template<class T>
inline MyList<T>::MyList(const T& data) : MyList()
{
	push_back(data);
}

template<class T>
inline MyList<T>::MyList(const T* arr, int count) : MyList()
{
	for (int i = 0; i < count; i++) push_back(arr[i]);
}

template<class T>
inline MyList<T>::MyList(const MyList& List2) : MyList()
{
	ListNode* buf = List2.root;
	for (int i = 0; i < List2._size; i++) { 
		push_back(*(buf->info));
		buf = buf->next;
	}
}

template<class T>
inline void MyList<T>::push_back(const T& data)
{
	insert(data, _size);
}

template<class T>
inline void MyList<T>::push_front(const T& data)
{
	insert(data, 0);
}

template<class T>
inline void MyList<T>::pop_back()
{
	erase(_size - 1);
}

template<class T>
inline void MyList<T>::pop_front()
{
	erase(0);
}

template<class T>
inline void MyList<T>::insert(const T& data, int position) 
{
	//assert(position >= 0 && position <= _size);
	if (position < 0 || position > _size) throw std::out_of_range("Выход за пределы списка");

	ListNode* NewNode = new ListNode;
	NewNode->info = new T;
	*(NewNode->info) = data;

	if (!root) {
		NewNode->prev = NewNode;
		NewNode->next = NewNode;
	}
	else {
		ListNode* buf = root;
		for (int i = 0; i < position; i++) buf = buf->next;

		NewNode->prev = buf->prev;
		NewNode->next = buf;
		buf->prev->next = NewNode;
		buf->prev = NewNode;
	}

	if (position == 0) root = NewNode;
	_size++;
}

template<class T>
inline typename MyList<T>::Iterator  MyList<T>::insert(const T& data, Iterator iter)
{
	ListNode* NewNode = new ListNode;
	NewNode->info = new T;
	*(NewNode->info) = data;

	if (!iter.node) {
		NewNode->prev = NewNode;
		NewNode->next = NewNode;
	}
	else {
		NewNode->prev = iter.node->prev;
		NewNode->next = iter.node;
		iter.node->prev->next = NewNode;
		iter.node->prev = NewNode;
	}
	if (iter == this->begin()) root = NewNode;
	_size++;
	return Iterator(NewNode);
}

template<class T>
inline void MyList<T>::erase(int position)
{
	if (!root) return;
	//assert(position >= 0 && position < _size);
	if (position < 0 || position >= _size) throw std::out_of_range("Выход за пределы списка");

	ListNode* buf = root;
	for (int i = 0; i < position; i++) buf = buf->next;
	delete buf->info;
	buf->prev->next = buf->next;
	buf->next->prev = buf->prev;
	if (position == 0) root = root->next;
	delete buf;

	_size--;
	if (_size == 0) root = nullptr;
}

template<class T>
inline typename MyList<T>::Iterator  MyList<T>::erase(Iterator iter)
{
	if (!iter.node) return iter;
	Iterator buf = iter.node->next;
	iter.node->prev->next = iter.node->next;
	iter.node->next->prev = iter.node->prev;
	delete iter.node->info;
	if (iter == this->begin()) root = iter.node->next;
	delete iter.node;
	_size--;
	if (_size == 0) {
		root = nullptr;
		return Iterator(root);
	}
	return buf;
}

template<class T>
inline void MyList<T>::clear()
{
	for (int i = _size-1; i >= 0; i--) erase(i);
}

template<class T>
inline typename MyList<T>::Iterator MyList<T>::begin()
{
	return Iterator(root);
}

template<class T>
inline typename MyList<T>::Iterator MyList<T>::end()
{
	if (!root) return Iterator(root);
	return Iterator(root->prev);
}

template<class T>
inline typename MyList<T>::Iterator MyList<T>::get(int index)
{
	//assert(index >= 0 && index < _size);
	if (index < 0 || index >= _size) throw std::out_of_range("Выход за пределы списка");
	Iterator iter = this->begin();
	for (int i = 0; i < index; i++, iter++);
	return iter;
}

template<class T>
inline int MyList<T>::find(const T& data) const
{
	if (!root) return -1;
	
	ListNode* buf = root;
	for (int i = 0; i < _size; i++) {
		if (*(buf->info) == data) return i;
		buf = buf->next;
	}
	return -1;
}

template<class T>
inline int MyList<T>::size() const
{
	return _size;
}

template<class T>
inline bool MyList<T>::empty() const
{
	return _size == 0;
}

template<class T>
inline MyList<T>::~MyList()
{
	clear();
}

template<class T>
inline T& MyList<T>::operator[](int index)
{
	//assert(index >= 0 && index < _size);
	if (index < 0 || index >= _size) throw std::out_of_range("Выход за пределы списка");
	ListNode* buf = root;
	for (int i = 0; i < index; i++) buf = buf->next;
	return *(buf->info);
}

template<class T>
inline void MyList<T>::operator=(const MyList& List2)
{
	clear();
	ListNode* buf = List2.root;
	for (int i = 0; i < List2._size; i++) {
		push_back(*(buf->info));
		buf = buf->next;
	}
}

//Определения методов Итератора

template<class T>
inline MyList<T>::Iterator::Iterator(ListNode* list_node) : node(list_node)
{
}

template<class T>
inline MyList<T>::Iterator::Iterator(const Iterator& iter) : node(iter.node)
{
}

template<class T>
inline typename MyList<T>::Iterator MyList<T>::Iterator::operator++(int)
{
	Iterator temp(*this);
	node = node->next;
	return temp;
}

template<class T>
inline typename MyList<T>::Iterator MyList<T>::Iterator::operator++()
{
	node = node->next;
	return *this;
}

template<class T>
inline typename MyList<T>::Iterator MyList<T>::Iterator::operator--(int)
{
	Iterator temp(*this);
	node = node->prev;
	return temp;
}

template<class T>
inline typename MyList<T>::Iterator MyList<T>::Iterator::operator--()
{
	node = node->prev;
	return *this;
}

template<class T>
inline typename MyList<T>::Iterator& MyList<T>::Iterator::operator=(const Iterator& iter)
{
	node = iter.node;
	return *this;
}

template<class T>
inline T& MyList<T>::Iterator::operator*()
{
	return *(node->info);
}

template<class T>
inline bool MyList<T>::Iterator::IsNull() const
{
	return !(this->node);
}

template<class T>
inline bool MyList<T>::Iterator::operator==(const Iterator& iter) const
{
	return iter.node == node;
}

template<class T>
inline bool MyList<T>::Iterator::operator!=(const Iterator& iter) const
{
	return !(*this == iter);
}

template<class T>
inline MyList<T>::Iterator::~Iterator()
{
}

//Определения MyList для C-style строк

inline MyList<char*>::MyList() : _size(0)
{
	root = nullptr;
}

inline MyList<char*>::MyList(const char* str) : MyList()
{
	push_back(str);
}

inline void MyList<char*>::push_back(const char* str) 
{
	insert(str, _size);
}

inline void MyList<char*>::push_front(const char* str)
{
	insert(str, 0);
}

inline void MyList<char*>::pop_back()
{
	erase(_size - 1);
}

inline void MyList<char*>::pop_front()
{
	erase(0);
}

inline void MyList<char*>::insert(const char* str, int index)
{
	//assert(index >= 0 && index <= _size);
	if (index < 0 || index > _size) throw std::out_of_range("Выход за пределы списка");
	int str_size = 1;
	for (int i = 0; str[i] != '\0'; i++, str_size++);
	
	ListNode* NewNode = new ListNode;
	NewNode->info = new char[str_size];
	strcpy_s(NewNode->info, str_size, str);


	if (!root) {
		NewNode->prev = NewNode;
		NewNode->next = NewNode;
	}
	else {
		ListNode* buf = root;
		for (int i = 0; i < index; i++) buf = buf->next;

		NewNode->prev = buf->prev;
		NewNode->next = buf;
		buf->prev->next = NewNode;
		buf->prev = NewNode;
	}

	if (index == 0) root = NewNode;
	_size++;


}

inline typename MyList<char*>::Iterator MyList<char*>::insert(const char* str, typename MyList<char*>::Iterator iter)
{
	int str_size = 1;
	for (int i = 0; str[i] != '\0'; i++, str_size++);

	ListNode* NewNode = new ListNode;
	NewNode->info = new char[str_size];
	strcpy_s(NewNode->info, str_size, str);

	if (!iter.node) {
		NewNode->prev = NewNode;
		NewNode->next = NewNode;
	}
	else {
		NewNode->prev = iter.node->prev;
		NewNode->next = iter.node;
		iter.node->prev->next = NewNode;
		iter.node->prev = NewNode;
	}
	if (iter == this->begin()) root = NewNode;
	_size++;
	return Iterator(NewNode);
}

inline void MyList<char*>::erase(int index)
{
	if (!root) return;
	//assert(index >= 0 && index < _size);
	if (index < 0 || index >= _size) throw std::out_of_range("Выход за пределы списка");

	ListNode* buf = root;
	for (int i = 0; i < index; i++) buf = buf->next;
	delete[] buf->info;
	buf->prev->next = buf->next;
	buf->next->prev = buf->prev;
	if (index == 0) root = root->next;
	delete buf;

	_size--;
	if (_size == 0) root = nullptr;
}

inline typename MyList<char*>::Iterator MyList<char*>::erase(typename MyList<char*>::Iterator iter)
{
	if (!iter.node) return iter;
	Iterator buf = iter.node->next;
	iter.node->prev->next = iter.node->next;
	iter.node->next->prev = iter.node->prev;
	delete[] iter.node->info;
	if (iter == this->begin()) root = iter.node->next;
	delete iter.node;
	_size--;
	if (_size == 0) {
		root = nullptr;
		return Iterator(root);
	}
	return buf;
}

inline void MyList<char*>::clear()
{
	for (int i = 0; i < _size; i++) erase(0);
}

inline typename MyList<char*>::Iterator MyList<char*>::begin()
{
	return Iterator(root);
}

inline typename MyList<char*>::Iterator MyList<char*>::end()
{
	if (root)return Iterator(root->prev);
	return Iterator(root);
}

inline typename MyList<char*>::Iterator MyList<char*>::get(int index)
{
	//assert(index >= 0 && index < _size);
	if (index < 0 || index >= _size) throw std::out_of_range("Выход за пределы списка");

	Iterator iter = this->begin();
	for (int i = 0; i < index; i++, iter++);
	return iter;
}

inline int MyList<char*>::find(const char* str) const
{
	if (!root) return -1;

	ListNode* buf = root;
	for (int i = 0; i < _size; i++) {
		if (!strcmp(str, buf->info)) return i;
		buf = buf->next;
	}
	return -1;
}

inline int MyList<char*>::size() const
{
	return _size;
}

inline bool MyList<char*>::empty() const
{
	return _size == 0;
}

inline MyList<char*>::~MyList()
{
	clear();
}

inline char* MyList<char*>::operator[](int index)
{
	//assert(index >= 0 && index < _size);
	if (index < 0 || index >= _size) throw std::out_of_range("Выход за пределы списка");
	ListNode* buf = root;
	for (int i = 0; i < index; i++) buf = buf->next;
	return buf->info;
}

inline void MyList<char*>::operator=(const MyList& list2)
{
	clear();
	ListNode* buf = list2.root;
	for (int i = 0; i < list2._size; i++) {
		push_back(buf->info);
		buf = buf->next;
	}
}

//Итератор C-style

inline MyList<char*>::Iterator::Iterator(ListNode* node2)
{
	node = node2;
}

inline MyList<char*>::Iterator::Iterator(const Iterator& iter)
{
	node = iter.node;
}

inline typename MyList<char*>::Iterator MyList<char*>::Iterator::operator++(int) 
{
	Iterator temp(*this);
	node = node->next;
	return temp;
}

inline typename MyList<char*>::Iterator MyList<char*>::Iterator::operator++() 
{
	node = node->next;
	return *this;
}

inline typename MyList<char*>::Iterator MyList<char*>::Iterator::operator--(int) 
{
	Iterator temp(*this);
	node = node->prev;
	return temp;
}

inline typename MyList<char*>::Iterator MyList<char*>::Iterator::operator--() 
{
	node = node->prev;
	return *this;
}

inline typename MyList<char*>::Iterator& MyList<char*>::Iterator::operator=(const Iterator& iter) 
{
	node = iter.node;
	return *this;
}

inline char* MyList<char*>::Iterator::operator*() 
{
	return node->info;
}

inline bool MyList<char*>::Iterator::IsNull() const 
{
	return !(this->node);
}

inline bool MyList<char*>::Iterator::operator==(const Iterator& iter) const 
{
	return iter.node == node;
}

inline bool MyList<char*>::Iterator::operator!=(const Iterator& iter) const 
{
	return !(*this == iter);
}

inline MyList<char*>::Iterator::~Iterator()
{
}
#endif