#include "TinyString.h";

#include <cstring>
#include <iostream>
#include <cassert>


// Member functions
TinyString::TinyString() : begin_(new char[1]), end_(begin_){
	*begin_= '\0';
}

TinyString::TinyString(std::size_t count, char ch) : begin_(new char[count + 1]), end_(begin_ + count){
	char* t = begin_;
	while (count--) {
		*t++ = ch;
	}
	*t = '\0';
}

TinyString::TinyString(const char* s) : begin_(new char[strlen(s) + 1]), end_(begin_ + strlen(s)) {
	// strcpy 操作包括'\0'
	strcpy(begin_, s);
}

TinyString& TinyString::operator=(const TinyString& str) {
	strcpy(begin_, str.begin_);
	return *this;
}

// Element access
char& TinyString::operator[](std::size_t pos) {
	return begin_[pos];
}

const char& TinyString::operator[](std::size_t pos) const {
	return begin_[pos];
}

char& TinyString::front() {
	return begin_[0];
}

const char& TinyString::front() const {
	return begin_[0];
}

char& TinyString::back() {
	return *(end_ - 1);
}

const char& TinyString::back() const {
	return *(end_ - 1);
}

// Iterators
char* TinyString::begin(){
	return begin_;
}

const char* TinyString::begin() const {
	return begin_;
}

char* TinyString::end() {
	return end_;
}

const char* TinyString::end() const {
	return end_;
}

// Capacity
bool TinyString::empty() const {
	return begin_ == end_;
}

std::size_t TinyString::size() const {
	return end_ - begin_;
}

std::size_t TinyString::length() const {
	return end_ - begin_;
}

// Operations
void TinyString::clear() {
	erase(begin_, end_);
}

TinyString& TinyString::erase(std::size_t index, std::size_t npos) {
	strcpy(begin_ + index, begin_ + index + npos);
	end_ -= npos;
	return *this;
}

char* TinyString::erase(char* position) {
	strcpy(position, position + 1);
	end_ -= 1;
	return position;
}

char* TinyString::erase(char* first, char* last) {
	strcpy(first, last);
	end_ -= last - first;
	return first;
}

void TinyString::strTransform(std::size_t index, std::size_t count) {
	int ind_to_end = end_ - (begin_ + index - 1);
	char* p = end_;
	while (ind_to_end--) {
		*(p + count) = *p;
		--p;
	}
	end_ += count;
	// p += count;
}

TinyString& TinyString::insert(std::size_t index, std::size_t count, char ch) {
	strTransform(index, count);

	char* q = begin_ + index;
	for (int i = 0; i < count; ++i) {
		*(q + i) = ch;
	}
	return *this;
}

TinyString& TinyString::insert(std::size_t index, const char* s) {
	return insert(index, s, strlen(s));
}

TinyString& TinyString::insert(std::size_t index, const char* s, std::size_t count) {
	strTransform(index, count);

	strncpy(begin_ + index, s, count);
	return *this;
}

TinyString& TinyString::insert(std::size_t index, const TinyString& str) {
	int count = str.length();
	strTransform(index, count);

	strncpy(begin_ + index, str.begin(), count);
	return *this;
}

//Non-member functions
std::ostream& operator<<(std::ostream& os, const TinyString& str) {
	os << str.begin_;
	return os;
}