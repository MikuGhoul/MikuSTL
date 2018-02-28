#ifndef TESTMACRO_H__
#define TESTMACRO_H__

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_BASE(equality, actual, expect) \
	do {\
		test_count++;\
		if(equality)\
			test_pass++;\
		else {\
			std::cerr << __FILE__ << ":" << __LINE__ << ":  actual: " << actual << ", expect: " << expect << std::endl;\
			main_ret = 1;\
		}\
	} while(0)

#define EXPECT_CHAR(actual, expect) EXPECT_BASE((actual == expect), actual, expect)

#define

#endif // !TESTMACRO_H__
