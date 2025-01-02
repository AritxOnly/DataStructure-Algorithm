#include <iostream>
#include <cstring>

#define MAX 10000005

using namespace std;

int a[MAX], b[MAX], c[MAX];

int MyMax(int, int);
int Add(int, int);
int Multiply(int, int);
int Judge(int);

int main() {
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(c, 0, sizeof(c));
	int len_a, len_b;
    cin >> len_a >> len_b;
    for (int i = 1; i <= len_a; i++)
        cin >> a[i];
    for (int i = 1; i <= len_b; i++)
        cin >> b[i];
	int final_len = Multiply(len_a, len_b);
	int flag = Judge(final_len);
	if (flag)
		for (int i = final_len; i > 0; i--)
			cout << c[i];
	else
		cout << 0;
	return 0;
}

int MyMax(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

int Add(int lena, int lenb) {
	int lenmax = MyMax(lena, lenb);
	int flag = 0;
	for (int i = 1; i <= lenmax; i++) {
		c[i] += a[i] + b[i];
		if (c[i] >= 10) {
			c[i + 1]++;
			c[i] -= 10;
			if (i == lenmax)
				flag++;
		}
	}
	return lenmax + flag;
}

int Multiply(int lena, int lenb) {
	for(int i = 1; i <= lena; i++) {
		for (int j = 1; j <= lenb; j++) {
			c[i + j - 1] += a[i] * b[j];
		}
	}
	int len = lena + lenb - 1;
	for (int i = 1; i <= len; i++) {
		if (c[i] >= 10) {
			int temp = c[i] / 10;
			c[i] = c[i] % 10;
			c[i + 1] += temp;
			if (i == len) {
				len++;
			}
		}
	}
	return len;
}

int Judge(int len) {
	int flag = 0;
	for (int i = 1; i <= len; i++) {
		flag = 1;
		if (c[i] == 0)
			flag = 0;
	}
	return flag;
}