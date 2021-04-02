#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <Windows.h>

#include <encrypt.h>

std::string s;
std::string s1 = "";
std::string s2 = "";
std::string res;
std::vector<std::string> k;

void toClipboard(const std::string& s) {
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + sizeof(s[0]));
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

int main() {
	std::ifstream file;

	start: {

	file.open("k.cryptork");
	std::string line;
	while (std::getline(file, line)) {
		k.push_back(line);
		std::cout << line << "\n";
	}

	s = "";

	std::cout << "\ncryptor\n";
	std::cout << "(-c) -d -s:\n";
	std::cin >> s;

	if (s[0] == '-') {
		if (s[1] == 'c')
			goto encr;
		else if (s[1] == 's')
			goto save;
		else if (s[1] == 'd')
			goto decr;
	}
	else {
		goto encr;
	}

	}

	encr: {
	std::cout << "\nencrypt\n";
	if (s[0] == '-') {
		std::cout << "p:\n";
		std::cin >> s1;
	}
	else s1 = s;

	std::cout << "k:\n";
	std::cin >> s2;

	s1 += s2;

	res = encrypt(s1, s2);
	toClipboard(res);

	goto finish;

	}

	decr: {
	std::cout << "\ndecrypt\n";
	std::cout << "ep:\n";
	std::cin >> s1;

	std::cout << "k:\n";
	std::cin >> s2;

	res = decrypt(s1, s2);

	goto finish;

	}

save: {
	std::cout << "\nsave\n";
	std::cout << "k:\n";
	std::cin >> s1;
	std::ofstream write("k.cryptork");
	std::string str;
	for (int i = 0; i < k.size(); i++) {
		str += k[i] + "\n";
	}
	str += s1;
	write << str;

	res = "saved " + s1;

	goto finish;

	}

	finish: {
	std::cout << "\nresult:\n";
	std::cout << "\n" << res << "\n\n";
	system("pause");
	}

	return 0;
}