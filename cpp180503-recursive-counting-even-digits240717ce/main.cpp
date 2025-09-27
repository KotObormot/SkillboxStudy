#include <iostream>

void evendigits(long long& n, int& ans) {
	if(n == 0) {
		return;
	}

	if((n % 10) % 2 == 0) {
		ans++;
	}
	n = n / 10;
	evendigits(n, ans);
}

int main() {
	long long n = 9223372036854775806;
	int ans = 0;
	evendigits(n, ans);
	std::cout << "The number of even digits " << " = " << ans << ".\n";
	return 0;
}
