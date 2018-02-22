#include "TinyString.h";

#include <cstring>

TinyString::TinyString() : data_(new char){
	*data_ = '\0';
}

TinyString::TinyString(size_t count, char ch) : data_(new char[count + 1]){
	char* t = data_;
	while (count--) {
		*t++ = ch;
	}
	*t = '\0';
}

TinyString::TinyString(const char* s) : data_(new char[strlen(s) + 1]) {
	// strcpy 操作包括'\0'
	strcpy(data_, s);
}

char& TinyString::front() {
	return data_[0];
}

const char& TinyString::front() const {
	return data_[0];
}