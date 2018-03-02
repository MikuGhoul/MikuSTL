#ifndef TINYSTRING_H__
#define TINYSTRING_H__
#include <ostream>

class TinyString {
public:
	// Member functions
	TinyString();
	TinyString(std::size_t, char);
	TinyString(const char*);

	TinyString& operator=(const TinyString&);

	// Element access
	char& operator[](std::size_t);
	const char& operator[](std::size_t) const;

	char& front();
	const char& front() const;
	char& back();
	const char& back() const;

	// Iterators
	char* begin();
	const char* begin() const;
	char* end();
	const char* end() const;

	// Capacity
	bool empty() const;
	std::size_t size() const;
	std::size_t length() const;

	// Operations
	void clear();
	TinyString& erase(std::size_t, std::size_t);
	char* erase(char*);
	char* erase(char* , char*);

	//Non-member functions
	friend std::ostream& operator<<(std::ostream&, const TinyString&);

private:
	// char* const data_;
	char* begin_;
	char* end_;
};

#endif // !TINYSTRING_H__
