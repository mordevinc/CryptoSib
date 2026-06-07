#include "mathFunctions.h"
int evk(int base, int mod) {
	int a = base;
	int b = mod;
	int oldB = 0;
	while (b > 0) {
		oldB = b;
		b = a % b;
		a = oldB;
	}
	return a;
}

int ObrEvk(int a, int b, char ret) {
	int oldU = 1;
	int oldV = 0;
	int u = 0;
	int v = 1;
	int d = 0;
	int q = 0;
	int r = 0;
	int c = a;
	int m = b;
	int tempU = 0;
	int tempV = 0;
	do {
		r = c % m;
		q = c / m;
		c = m;
		m = r;
		if (r <= 0) break;
		tempU = u;
		tempV = v;
		u = oldU - (q * tempU);
		v = oldV - (q * tempV);
		oldU = tempU;
		oldV = tempV;
	} while (r > 0);
	if (u < 0) u += b;
	if (ret == 'u') return u;
	if (ret == 'r') return c;
	if (ret == 'v') return v;
	return 0;
}

int sqrtZ(int m) {
	if (m < 0) return -1;
	if (m == 0 || m == 1) return m;

	for (int i = 1; i <= m / i; ++i) {
		if (i * i == m) {
			return i;
		}
	}
	return -1;
}