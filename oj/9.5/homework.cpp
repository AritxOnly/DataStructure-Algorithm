#include <cstring>
#include <iostream>

const int MAXN = 101;

int mtrx[MAXN][MAXN];

int main() {
	memset(mtrx, 0, sizeof(mtrx));
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cin >> mtrx[i][j];
		}
	}

	// 判断矩阵类型:下三角
	bool is_lower = true;
	for (int i = 0; i < n && is_lower; i++) {
		for (int j = i + 1; j < n && is_lower; j++) {
			if (mtrx[i][j] != 0) {
				is_lower = false;
			}
		}
	}

	// 判断矩阵类型:上三角
	bool is_upper = true;
	for (int i = 0; i < n && is_upper; i++) {
		for (int j = 0; j < i && is_upper; j++) {
			if (mtrx[i][j] != 0) {
				is_upper = false;
			}
		}
	}

	if (is_upper) {
		if (is_lower) {
			std::cout << "diagonal";
		} else {
			std::cout << "upper";
		}
	} else {
		if (is_lower) {
			std::cout << "lower";
		} else {
			std::cout << "none";
		}
	}
	return 0;
}
