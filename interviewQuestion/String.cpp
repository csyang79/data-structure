#include <unistd.h>
#include <cstring>

class String {
public:
	String(const char *str = nullptr);
	String(const String &rhs);
	String& operator=(const String& rhs);
	~String();
private:
	char *data;
};

String::String(const char *str) {
	if (str == nullptr) {
		data = new char[1];
		data[0] = '\0';
	} else {
		data = new char[strlen(str) + 1];
		strcpy(data, str);
	}
}

String::String(const String &rhs) {
	data = new char[strlen(rhs.data) + 1];
	strcpy(data, rhs.data);
}

String::operator=(const String &rhs) {
	if (this == &rhs)
		return *this;
	delete []data;
	data = new char[strlen(rhs.data) + 1];
	strcpy(data, rhs.data);
	return *this;
}

String::~String() {
	delete []data;
}
int main() {
	
}
