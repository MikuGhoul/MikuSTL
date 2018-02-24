#include "TinyString.h";

#include <cstring>
#include <iostream>

TinyString::TinyString() : begin_(new char[1]), end_(begin_){
	*begin_= '\0';
}

TinyString::TinyString(size_t count, char ch) : begin_(new char[count + 1]), end_(begin_ + count){
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

std::ostream& operator<<(std::ostream& os, const TinyString& str) {
	os << str.begin_;
	return os;
}