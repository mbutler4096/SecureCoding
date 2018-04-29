#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <cstdarg>


#define LOG_INPUT_SIZE 40

int add(int first, int second, ...)
{
	int r = first + second;
	va_list va;
	va_start(va, second);

	while (int v = va_arg(va, int))
	{
		r += v;
	}
	va_end(va);

	return r;
}


void f2(const std::vector<int> &src)
{
	std::vector<int> dest;
	std::copy(src.begin(), src.end(), dest.begin());
	// ...
}

enum EnumType {
	First,
	Second,
	Third
};

void f(int intVar)
{
	EnumType enumVar = static_cast<EnumType>(intVar);

	if (enumVar < First || enumVar > Third)
	{
		// Handle error
	}
}

int saveToLogFile(const char* buf)
{
	return 1;
}

// saves the file name to a log file
int outputFilenameToLog(char *filename, int length)
{
	int success;
	// buffer with size set to maximum size for input to log file
	char buf[LOG_INPUT_SIZE];

	// copy filename to buffer
	strncpy_s(buf, filename, length);

	// save to log file
	success = saveToLogFile(buf);

	return success;
}

auto g() {
	int i = 12;
	return [&] {
		i = 100;
		return i;
	};
}

void f3() {
	int j = g()();
}


int main()
{
	char fname[] = "This is my very long filename that is over 40 chars";
	outputFilenameToLog(fname, strlen(fname));

	f(12);

	std::vector<int> foo = { 1,2,3,4,5,6,7,8,9 };
	f2(foo);

	f3();

	return 0;
}


#include <type_traits>

template <typename Arg,
	typename std::enable_if<std::is_integral<Arg>::value>::type * = nullptr>
	int add(Arg f, Arg s) {
	return f + s;
}

template <typename Arg,
	typename... Ts,
	typename std::enable_if<std::is_integral<Arg>::value>::type * = nullptr>
	int add(Arg f, Ts... rest) {
	return f + add(rest...);
}

#include <type_traits>

template <typename Arg,
	typename... Ts,
	typename std::enable_if<std::is_integral<Arg>::value>::type * = nullptr>
	int add(Arg i, Arg j, Ts... all) {
		int values[] = { j, all... };
		int r = i;
		
		for (auto v : values) {
			r += v;
		}
		
		return r;
}

//auto g() {
//int i = 12;
//return [=]() mutable {
//i = 100;
//return i;
//};
//}
//
//void f() {
//int j = g()();
//}
//
//int vuln_function(char *str)
//{
//	char buffer[500];
//
//	//oooops
//	strcpy(buffer, str);
//}
//
//int main(int argc, char** argv)
//{
//	char buffer[500];
//	FILE* input_file = fopen("my_file", "r");
//
//	fread(buffer, sizeof(char), 500, input_file);
//	vuln_function(argv[1]);
//	fclose(input_file);
//
//	printf("Returned Properly\n");
//	
//	return 1;
//}