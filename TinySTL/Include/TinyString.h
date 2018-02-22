#ifndef TINYSTRING_H__
#define TINYSTRING_H__

class TinyString {
public:
	TinyString();
	TinyString(size_t, char);
	TinyString(const char*);
	char& front();
	const char& front() const;
private:
	char* const data_;
};

#endif // !TINYSTRING_H__
