#ifndef TESTHEADER_H__
#define TESTHEADER_H__

//static int main_ret = 0;
//static int test_count = 0;
//static int test_pass = 0;

bool expect_char(char actual, char expect) {
	return actual == expect;
}

bool expect_string(TinyString& actual, std::string& expect) {
	char* first1 = actual.begin();
	char* end1 = actual.end();
	std::string::iterator first2 = expect.begin();
	std::string::iterator end2 = expect.end();

	for (; first1 != end1 && first2 != end2; ++first1, ++first2) {
		if (*first1 != *first2)
			return false;
	}
	// return true;
	return first1 == end1 && first2 == end2;
}


#endif // !TESTHEADER_H__
