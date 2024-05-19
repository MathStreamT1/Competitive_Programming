#include<bits/stdc++.h>
using namespace std;

struct barrett_reduction {
    unsigned mod;
    uint64_t div;
 
    barrett_reduction(unsigned m) : mod(m), div(-1LLU / m) {}
 
    unsigned operator()(uint64_t a) const {
#ifdef __SIZEOF_INT128__
        uint64_t q = uint64_t(__uint128_t(div) * a >> 64);
        uint64_t r = a - q * mod;
        return unsigned(r < mod ? r : r - mod);
#endif
        return unsigned(a % mod);
    }
};
 
template<const int &MOD, const barrett_reduction &barrett>
struct _b_int {
    int val;
 
    _b_int(int64_t v = 0) {
        if (v < 0) v = v % MOD + MOD;
        if (v >= MOD) v %= MOD;
        val = int(v);
    }
 
    _b_int(uint64_t v) {
        if (v >= uint64_t(MOD)) v %= MOD;
        val = int(v);
    }
 
    _b_int(int v) : _b_int(int64_t(v)) {}
    _b_int(unsigned v) : _b_int(uint64_t(v)) {}
 
    static int inv_mod(int a, int m = MOD) {
        // https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Example
        int g = m, r = a, x = 0, y = 1;
 
        while (r != 0) {
            int q = g / r;
            g %= r; swap(g, r);
            x -= q * y; swap(x, y);
        }
 
        return x < 0 ? x + m : x;
    }
 
    explicit operator int() const { return val; }
    explicit operator unsigned() const { return val; }
    explicit operator int64_t() const { return val; }
    explicit operator uint64_t() const { return val; }
    explicit operator double() const { return val; }
    explicit operator long double() const { return val; }
 
    _b_int& operator+=(const _b_int &other) {
        val -= MOD - other.val;
        if (val < 0) val += MOD;
        return *this;
    }
 
    _b_int& operator-=(const _b_int &other) {
        val -= other.val;
        if (val < 0) val += MOD;
        return *this;
    }
 
    static unsigned fast_mod(uint64_t x) {
#if !defined(_WIN32) || defined(_WIN64)
        return barrett(x);
#endif
        // Optimized mod for Codeforces 32-bit machines.
        // x must be less than 2^32 * MOD for this to work, so that x / MOD fits in an unsigned 32-bit int.
        unsigned x_high = unsigned(x >> 32), x_low = unsigned(x);
        unsigned quot, rem;
        asm("divl %4\n"
            : "=a" (quot), "=d" (rem)
            : "d" (x_high), "a" (x_low), "r" (MOD));
        return rem;
    }
 
    _b_int& operator*=(const _b_int &other) {
        val = fast_mod(uint64_t(val) * other.val);
        return *this;
    }
 
    _b_int& operator/=(const _b_int &other) {
        return *this *= other.inv();
    }
 
    friend _b_int operator+(const _b_int &a, const _b_int &b) { return _b_int(a) += b; }
    friend _b_int operator-(const _b_int &a, const _b_int &b) { return _b_int(a) -= b; }
    friend _b_int operator*(const _b_int &a, const _b_int &b) { return _b_int(a) *= b; }
    friend _b_int operator/(const _b_int &a, const _b_int &b) { return _b_int(a) /= b; }
 
    _b_int& operator++() {
        val = val == MOD - 1 ? 0 : val + 1;
        return *this;
    }
 
    _b_int& operator--() {
        val = val == 0 ? MOD - 1 : val - 1;
        return *this;
    }
 
    _b_int operator++(int) { _b_int before = *this; ++*this; return before; }
    _b_int operator--(int) { _b_int before = *this; --*this; return before; }
 
    _b_int operator-() const {
        return val == 0 ? 0 : MOD - val;
    }
 
    friend bool operator==(const _b_int &a, const _b_int &b) { return a.val == b.val; }
    friend bool operator!=(const _b_int &a, const _b_int &b) { return a.val != b.val; }
    friend bool operator<(const _b_int &a, const _b_int &b) { return a.val < b.val; }
    friend bool operator>(const _b_int &a, const _b_int &b) { return a.val > b.val; }
    friend bool operator<=(const _b_int &a, const _b_int &b) { return a.val <= b.val; }
    friend bool operator>=(const _b_int &a, const _b_int &b) { return a.val >= b.val; }
 
    _b_int inv() const {
        return inv_mod(val);
    }
 
    _b_int pow(int64_t p) const {
        if (p < 0)
            return inv().pow(-p);
 
        _b_int a = *this, result = 1;
 
        while (p > 0) {
            if (p & 1)
                result *= a;
 
            p >>= 1;
 
            if (p > 0)
                a *= a;
        }
 
        return result;
    }
 
    friend ostream& operator<<(ostream &os, const _b_int &m) {
        return os << m.val;
    }
 
    friend istream& operator>>(istream &is, _b_int &m) {
        int64_t x;
        is >> x;
        m = x;
        return is;
    }
};
 
int MOD = int(1e9) + 7;
barrett_reduction barrett(MOD);
using barrett_int = _b_int<MOD, barrett>;