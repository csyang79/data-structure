// 输入一个字符串最小需要敲击键盘的次数，1.caps切换 2.shift + letter

#include <iostream>
#include <cctype>
#include <string>
using namespace std;

int minPress(const string& str) {
	int len = str.length();
	int on[len + 1] = { 0 };
	int off[len + 1] = { 0 };
	on[0] = 1;
	for (int i = 0; i < len; ++i) {
		if (islower(str[i])) {
			on[i + 1] = std::min(on[i] + 2, off[i] + 2);
			off[i + 1] = std::min(on[i] + 2, off[i] + 1);
		} else {
			on[i + 1] = std::min(on[i] + 1, off[i] + 2);
			off[i + 1] = std::min(on[i] + 2, off[i] + 2);
		}
	}
	return std::min(on[len], off[len]);
}

int main(int argc, char **argv) {
	for (int i = 1; i < argc; ++i) {
		cout << minPress(argv[i]) << "\n";
	}
}
