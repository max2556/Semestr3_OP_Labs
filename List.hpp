#pragma once
#include <initializer_list>

template<class T>
class Node
{
public:
	explicit Node(const T& data)
	{
		this->data = data;
		next = nullptr;
	}

	void set_next(Node* new_next)
	{
		next = new_next;
	}
	~Node()
	{
		data = 0;
		next = 0;
	}

	T data;
	Node* next = nullptr;
};

template<class T>
class List
{
private:
	size_t length = 0;			//���������� ������ 0
	Node<T>* head = nullptr;	//���������� ������� �������� ���
	Node<T>* tail = nullptr;	//� ���������� �������� ���

	Node<T>* get_prev_last()
	{
		Node<T>* current_node = head;

		//����� ���� �����, ��� ������ ����, ����� ����� ���������� nullptr
		if (!head) return nullptr;

		//��� � ������ ����� ���� ������� - ���������� ���� �� ���� head ��� tail, �� ����� �������
		if (head == tail) return nullptr;

		//��� ��� ������ ����������� ����� ����� ������������� ������� � �����
		while (current_node->next != tail)  //��� ������ ��������� �� ������� ��������� = ������, ������ ������� �������������
			current_node = current_node->next;

		//���������� �������������
		return current_node;
	}
public:
	explicit List()
	{
		length = 0;
	}

	explicit List(std::initializer_list<T> init_list)
	{
		for (auto& obj : init_list)
		{
			push_back(obj);
		}
	}
	~List()
	{
		length = 0;
		Node<T>* next = nullptr;
		if (head)
			next = head->next;
		while (head)
		{
			delete head;
			head = next;
			if (head)
				next = head->next;
		}
		tail = nullptr;
	}

	void push_back(Node<T>* new_node)
	{
		if (!new_node) return;
		//���� ��� ������, �� ��� ������, ��� ��� � ������
		if (!head) {
			head = new_node;    //������� ����� ������
			tail = head;	   //������ - ������������ �������, ������ � ��������� ����
			length++;
			return;
		}

		tail->next = new_node;  //������� ����� �������, ��������� �� ���� � �����
		tail = tail->next;		//����� ������� ������ ���������, �� �����

		length++;
	}

	void push_back(const T& new_element)
	{
		push_back(new Node(new_element));
	}

	void push_front(Node<T>* new_node)
	{
		if (!new_node) return;

		if (!head) {
			head = new_node;
			tail = head;
			length++;
			return;
		}

		new_node->next = head;
		head = new_node;

		length++;
	}

	void push_front(const T& new_element)
	{
		Node<T>* new_node = new Node(new_element);  //������� ����� �������, ��������� �� ���� � �����
		push_front(new_node);
	}

	void push_at(Node<T>* new_node, size_t pos)
	{
		if (pos > length) return;

		if (pos == 0) {
			push_front(new_node);
			return;
		}

		if (pos == length)
		{
			push_back(new_node);
			return;
		}

		Node<T>* cursor = head;
		for (size_t i = 0; i < pos - 1; ++i)
			cursor = cursor->next;

		new_node->next = cursor->next;
		cursor->next = new_node;

		length++;
	}

	T pop_back()
	{
		T result = tail->data;		//���������� ������ �� ���������� ��������
		Node<T>* prev_tail = get_prev_last(); //���� �������������

		delete tail;				//������� ���������
		tail = prev_tail;		    //��� ��� ��������� �������, ������������� ������ ���������
		if (tail)
			tail->next = nullptr;
		else {
			head = tail;
		}

		length--;
		return result;				//
	}

	T pop_front()
	{
		T result = head->data;			//���������� ������ �� ������� ��������
		Node<T>* new_head = head->next; //����� ������ ������� = ������� ��������� �� ������

		delete head;
		head = new_head;

		length--;
		return result;
	}

	size_t Length()
	{
		return length;
	}

	void merge(List<T>* another_list)
	{
		List<T>* resultList = new List<T>();

		auto cursorLeft = getHead();
		auto cursorRight = another_list->getHead();

		while (cursorLeft != nullptr && cursorRight != nullptr)
		{
			if (cursorLeft->data > cursorRight->data)
			{
				resultList->push_back(cursorRight->data);
				cursorRight = cursorRight->next;
			}
			else {
				resultList->push_back(cursorLeft->data);
				cursorLeft = cursorLeft->next;
			}
		}

		while (cursorLeft)
		{
			resultList->push_back(cursorLeft->data);
			cursorLeft = cursorLeft->next;
		}

		while (cursorRight)
		{
			resultList->push_back(cursorRight->data);
			cursorRight = cursorRight->next;
		}

		*this = *resultList;
	}

	Node<T>* getHead() {
		return head;
	}
	Node<T>* getTail() {
		return tail;
	}
};

