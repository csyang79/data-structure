#include <iostream>
#include <cstring>
#include <unistd.h>
class String{
public:
	String(const char *str = nullptr);
	String(const String& rhs);
	~String();
	String& operator=(const String& rhs);
private:
	char *item;
};

String::String(const char* str) {
	if (str == nullptr) {
		item = new char[1];
		item[0] = '\0';
	} else {
		item = new char[strlen(str) + 1];
		strcpy(item, str);
	}
	printf("constructor char * is called\n");
}

String::String(const String& rhs) {
	item = new char[strlen(rhs.item) + 1];
	strcpy(item, rhs.item);
	printf("constructor String is called\n");
}

String::~String() {
	delete []item;
	printf("destructor is called\n");
}

String& String::operator=(const String& rhs) {
	if (this == &rhs)
		return *this;
	delete []item;
	item = new char[strlen(rhs.item) + 1];
	strcpy(item, rhs.item);
	printf("operator = is called\n");
	return *this;
}

int main() {
	String str = "nihao";
	String another = "hello";
	another = str;
}
