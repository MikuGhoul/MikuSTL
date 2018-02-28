#ifndef TINYSTRING_H__
#define TINYSTRING_H__
#include <ostream>

class TinyString {
public:
	TinyString();
	TinyString(std::size_t, char);
	TinyString(const char*);

	TinyString& operator=(const TinyString&);

	char& operator[](std::size_t);
	const char& operator[](std::size_t) const;

	char& front();
	const char& front() const;
	char& back();
	const char& back() const;

	friend std::ostream& operator<<(std::ostream&, const TinyString&);

private:
	//char* const data_;
	char* const begin_;
	char* end_;
};

#endif // !TINYSTRING_H__
