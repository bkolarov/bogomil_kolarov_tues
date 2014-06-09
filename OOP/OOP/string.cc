#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class StringError{};

class String {
	int capacity_;
	int size_;

	char* buffer_;

public:
	String(int capacity)
	:	capacity_(capacity),
		size_(0),
		buffer_(new char[capacity_]) 
	{}

	 String(const char* str)
	 :	capacity_(0),
		size_(0),
		buffer_(0) 
	{
		size_ = strlen(str);
		capacity_ = size_ + 1;
		buffer_ = new char[capacity_];
		strcpy(buffer_, str);
	}

	String(const String& other)
	:	size_(0),
		capacity_(0),
		buffer_(0)
	{
		*this = other;
	}

	~String() {
		capacity_ = 0;
		size_ = 0;
		delete [] buffer_;
	}

	String& operator=(const String& other) {
		delete [] buffer_;
		capacity_ = other.capacity();
		size_ = other.size();
		buffer_ = new char[capacity_];
		strcpy(buffer_, other.get_buffer());
	}

	int size() const {
		return size_;
	}

	int length() const {
		return size_;
	}

	int capacity() const {
		return capacity_;
	}

	bool empty() {
		return size_ == 0;
	}

	bool clear() {
		capacity_ = 0;
		size_ = 0;
		buffer_ = 0;
	}

	char* get_buffer() {
		return buffer_;
	}

	char* get_buffer() const {
		return buffer_;
	}

	char& operator[](int index) {
		return buffer_[index];
	}

	char& operator[](int index) const {
		return buffer_[index];
	}

	char& at(int index) {
		if(size_ < index) {
			throw StringError();
		} else {
			return buffer_[index];
		}
	}

	char& at(int index) const {
		if(size_ < index) {
			throw StringError();
		} else {
			return buffer_[index];
		}
	}

	bool operator==(const String& other) {
		return strcmp(buffer_, other.get_buffer()) == 0;
	}

	bool operator!=(const String& other) {
		return strcmp(buffer_, other.get_buffer()) != 0;
	}

	bool operator<(const String& other) {
		return strcmp(buffer_, other.get_buffer()) < 0;
	}

	bool operator>(const String& other) {
		return strcmp(buffer_, other.get_buffer()) > 0;
	}

	bool operator<=(const String& other) {
		return strcmp(buffer_, other.get_buffer()) < 0 ||
			strcmp(buffer_, other.get_buffer()) != 0;
	}

	bool operator>=(const String& other) {
		return strcmp(buffer_, other.get_buffer()) > 0 ||
			strcmp(buffer_, other.get_buffer()) != 0;
	}

	String& append(const String& other) {
		char* tmp = new char[capacity_];
		strcpy(tmp, buffer_);
		delete [] buffer_;

		capacity_ += other.capacity();
		size_ += other.size();
		buffer_ = new char[capacity_];
		strcpy(buffer_, tmp);
		strcat(buffer_, other.get_buffer());

		delete [] tmp;
		return *this;
	}

	String& operator+=(const String& other) {
		append(other);
		return *this;
	}

	void push_back(char ch) {
		if(capacity_ > size_ + 1) {
			buffer_[++size_] = ch;
		} else {
			String tmp(ch);
			*this += tmp;
		}
	}

};

ostream& operator<<(ostream& out, const String& str) {
	for(int i = 0; i < str.size(); ++i) {
		out << str.at(i);
	}

	return out;
}

int main() {
	String str("hello");
	String str2("hello");
	
	cout << str << endl;
	
	int i = str == str2;
	cout << i << endl;

	String str3(str2);
	cout << str3 << endl;

	return 0;
}