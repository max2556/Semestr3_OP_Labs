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
	explicit List() {}

	explicit List(std::initializer_list<T> init_list)
	{
		for (auto& obj : init_list)
		{
			push_back(obj);
		}
	}
	
	void push_back(Node<T>* new_node)
	{
		if (!new_node) return;
		//���� ��� ������, �� ��� ������, ��� ��� � ������
		if (!head) {
			head = new_node;    //������� ����� ������
			tail = head;	   //������ - ������������ �������, ������ � ��������� ����
			return;
		}

		tail->next = new_node;  //������� ����� �������, ��������� �� ���� � �����
		tail = tail->next;		//����� ������� ������ ���������, �� �����

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
			return;
		}

		new_node->next = head;
		head = new_node;
	}

	void push_front(const T& new_element)
	{
		Node<T>* new_node = new Node(new_element);  //������� ����� �������, ��������� �� ���� � �����
		push_front(new_node);
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

		return result;				//
	}

	T pop_front()
	{
		T result = head->data;			//���������� ������ �� ������� ��������
		Node<T>* new_head = head->next; //����� ������ ������� = ������� ��������� �� ������

		delete head;
		head = new_head;

		return result;
	}

	void merge(List<T>* another_list)
	{
		auto cursorLeft = getHead();
		auto cursorRight = another_list->getHead();

		Node<T>* ptr_to_next = nullptr;

		while (cursorLeft != nullptr && cursorRight != nullptr)
		{
			if (cursorLeft->data >= cursorRight->data)
			{
				ptr_to_next = cursorRight->next; //���������

				cursorRight->next = cursorLeft; //������� ������
				head = cursorRight;

				cursorRight = ptr_to_next; //�������� ������
				cursorLeft = head;
			}
			else if ((cursorLeft->data <= cursorRight->data) && 
				((cursorLeft->next != nullptr) <= 
					(cursorLeft->next!=nullptr && cursorLeft->next->data >= cursorRight->data)))
			{
				ptr_to_next = cursorRight->next; //��������� ��������� �� ������

				//�������� � ������
				cursorRight->next = cursorLeft->next;
				cursorLeft->next = cursorRight;

				cursorRight = ptr_to_next;
			}
			else {
				cursorLeft = cursorLeft->next;
			}
		}
		

		while (cursorLeft->next)
			cursorLeft = cursorLeft->next;

		tail = cursorLeft;

	}

	Node<T>* getHead() {
		return head;
	}
	Node<T>* getTail() {
		return tail;
	}
};

