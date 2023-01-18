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
	Node<T>* head = nullptr;	//Изначально первого элемента нет
	Node<T>* tail = nullptr;	//И последнего элемента нет

	Node<T>* get_prev_last()
	{
		Node<T>* current_node = head;

		//Может быть такое, что список пуст, тогда сразу возвращаем nullptr
		if (!head) return nullptr;

		//Или в списке всего один элемент - возвращаем одно из двух head или tail, не имеет разницы
		if (head == tail) return nullptr;

		//Так как список односвязный нужно найти предпоследний элемент в цикле
		while (current_node->next != tail)  //как только следующий за текущим элементом = хвосту, значит текущий предпоследний
			current_node = current_node->next;

		//возвращаем предпоследний
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
		//Если нет головы, то это значит, что нет и хвоста
		if (!head) {
			head = new_node;    //создаем новую голову
			tail = head;	   //голова - единственный элемент, значит и последний тоже
			return;
		}

		tail->next = new_node;  //создаем новый элемент, указываем на него с конца
		tail = tail->next;		//новый элемент теперь последний, он хвост

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
		Node<T>* new_node = new Node(new_element);  //создаем новый элемент, указываем на него с конца
		push_front(new_node);
	}

	T pop_back()
	{
		T result = tail->data;		//Запоминаем данные из последнего элемента
		Node<T>* prev_tail = get_prev_last(); //Ищем предпоследний

		delete tail;				//Удаляем последний
		tail = prev_tail;		    //Так как последний удаляем, предпоследний теперь последний
		if (tail)
			tail->next = nullptr;
		else {
			head = tail;
		}

		return result;				//
	}

	T pop_front()
	{
		T result = head->data;			//Запоминаем данные из первого элемента
		Node<T>* new_head = head->next; //новый первый элемент = элемент следующий за первым

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
				ptr_to_next = cursorRight->next; //Запомнили

				cursorRight->next = cursorLeft; //сменили голову
				head = cursorRight;

				cursorRight = ptr_to_next; //сдвинули курсор
				cursorLeft = head;
			}
			else if ((cursorLeft->data <= cursorRight->data) && 
				((cursorLeft->next != nullptr) <= 
					(cursorLeft->next!=nullptr && cursorLeft->next->data >= cursorRight->data)))
			{
				ptr_to_next = cursorRight->next; //Запомнили следующий за правым

				//Добавили в список
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

