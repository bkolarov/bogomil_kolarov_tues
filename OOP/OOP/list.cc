#include <iostream>

using namespace std;

class ListError{};

template <class T>
class List {
	struct Node {
		T data_;
		Node* next_;
		Node* previous_;

		Node(T val) 
		:	data_(val),
			next_(0),
			previous_(0)
		{}
	};

	Node* head_;
	Node* tail_;

	int length;
public:
	List()
	:	head_(NULL),
		tail_(NULL),
		length(0)
	{}

	~List() {
		while(head_ != NULL){
			Node* temp = head_->next_;
			delete head_;
			head_ = temp;
			length--;
		}
	}

	List(const List& other) {
		head_ = NULL;
		tail_ = NULL;
		length = 0;

		*this = (other);
		// a = b = c = d = e 
	}

	bool empty() {
		return length == 0;
	}

	void push_back(const T& data) {
		Node *new_node = new Node(data);

		new_node -> next_ = NULL;
		new_node -> previous_ = ((empty()) ? NULL : tail_);

		if(tail_) {
			tail_ -> next_ = new_node;
		}

		tail_ = new_node;

		if(!head_) {
			head_ = new_node;
		}

		length++;
	}

	void pop_back() {

		if(length == 1) {
			delete tail_;
			tail_ = head_ = NULL;
			length = 0;
			return;
		}

		Node* new_node = tail_ -> previous_;
		new_node -> next_ = NULL;
		delete tail_;
		tail_ = new_node;
		length--;
	}

	void push_front(const T& data) {
		Node* new_node = new Node(data);

		new_node -> next_ = ((empty() ? NULL : head_));
		new_node -> previous_ = NULL;

		if(head_) {
			head_ -> previous_ = new_node;
		}

		head_ = new_node;

		if(!tail_) {
			tail_ = new_node;
		}

		++length;
	}

	void pop_front() {
		if(empty()) {
			throw ListError();
		}

		if(length == 1) {
			this->clear();
			return;
		}		

		Node* new_node = head_ -> next_;
		new_node -> previous_ = NULL;
		delete head_;
		head_ = new_node;
		length--;
	}

	void print() {
		cout << endl;
		recursive(head_);
		cout << endl;
	}

	void recursive(Node* elem) {
		cout << elem -> data_ << " ";
		if(elem -> next_ != NULL) {
			recursive(elem -> next_);
		}else {
			return;
		}
	}

	T& front() {
		if(empty()) {
			throw ListError();
		}

		return head_ -> data_;
	}

	const T& front() const {
		if(empty()) {
			throw ListError();
		}
		
		return head_ -> data_;
	}

	T& back() {
		if(empty()) {
			throw ListError();
		}
		
		return tail_ -> data_;
	}
 
	const T& back() const {
		if(empty()) {
			throw ListError();
		}
		
		return tail_ -> data_;
	}

	int size() const {
		return length;
	}

	void clear() {
		while(!empty()) {
			pop_back();
		}
	}

	void swap(List& other) {
		List<T> temp = other;
		other = *this;
		*this = temp;
		temp.~List();
	}

	List& operator=(const List& other) {
		if(this != &other) {
			this->clear();
			Node* tmp = other.head_;

			for(int i = 0; i < other.size(); i++) {
				this->push_back(tmp->data_);
				tmp = tmp->next_;
			}

			return *this;
		}
	}

	class iterator {
		friend class List;

		List* list_;
		Node* current_;

		iterator(const List* l, Node* current)
		:	list_(const_cast<List*>(l)),
			current_(current)
		{}

	public:

	};

};
/// !!!!
/// A x ;;; x == *this ;;; &x == this ;; 
/// !!!!
int main() {
	cout << "Welcome to my implementation of list :)" << endl;
	
	List<int> l1;

	l1.push_back(1);
	cout << "l1.empty() - " << boolalpha << l1.empty() << endl;

	l1.push_back(2);

	l1.pop_back();
	l1.pop_back();
	cout << "l1.empty() - " << boolalpha << l1.empty() << endl;

	l1.push_front(1);
	cout << "l1.empty() - " << boolalpha << l1.empty() << endl;

	l1.pop_front();
	cout << "l1.empty() - " << boolalpha << l1.empty() << endl;

	l1.push_back(2);
	l1.push_back(3);
	l1.push_front(1);
	l1.print();

	l1.pop_front();
	l1.pop_front();
	l1.pop_back();
	cout << "l1.empty() - " << boolalpha << l1.empty() << endl;

	l1.push_front(55);
	l1.push_back(56);
	cout << l1.front() << endl;
	cout << l1.back() << endl;
	cout << "size = " << l1.size() << endl;

	l1.clear();
	cout << "l1.empty() - " << boolalpha << l1.empty() << endl;
	cout << "size = " << l1.size() << endl;	

	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);

	List<int> l2, l3, l4, l5;
	l2.push_back(4);
	l2.push_back(5);
	l2.push_back(6);
	l2.push_back(7);
	//l1 = l2;
	l1.swap(l2);
	//l2 = l3 = l1;
//	cout << l3.front();
	//cout << l1.front() << l2.front() << l3.front() << l4.front() << l5.front();
	//cout << "segfault" << endl;
	cout << "l1:";
	l1.print();
	cout << "l2:";
	l2.print();

	l1.clear();
	l1.push_back(1);
	l1.push_back(2);
	l1.pop_front();
	cout << "empty() - " << l1.empty() << endl;

	return 0;
}