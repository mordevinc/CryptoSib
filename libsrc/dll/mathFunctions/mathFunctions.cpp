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

int extendEvk(int a, int b, char ret) {
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

uint64_t evk64(uint64_t base, uint64_t mod) {
	while (mod != 0) {
		uint64_t temp = mod;
		mod = base % mod;
		base = temp;
	}
	return base;
}

uint64_t modPow(uint64_t base, uint64_t exp, uint64_t mod) {
	uint64_t result = 1;
	base %= mod;
	while (exp > 0) {
		if (exp & 1) result = (result * base) % mod;
		base = (base * base) % mod;
		exp >>= 1;
	}
	return result;
}

bool isPrime(uint64_t n) {
	if (n < 2) return false;
	if (n == 2 || n == 3) return true;
	if (n % 2 == 0) return false;
	for (uint64_t i = 3; i * i <= n; i += 2) {
		if (n % i == 0) return false;
	}
	return true;
}

uint64_t generatePrime(int bits) {
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<uint64_t> dist(1ULL << (bits - 1), (1ULL << bits) - 1);
	uint64_t candidate;
	do {
		candidate = dist(gen);
		if (candidate % 2 == 0) candidate++;
	} while (!isPrime(candidate));
	return candidate;
}