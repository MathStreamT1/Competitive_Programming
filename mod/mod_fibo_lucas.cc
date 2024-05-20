#include <algorithm>
#include <array>
/****************************************************************************************************************
*             Author : Nguyen Tran                                                                              *
*             Created: 20/05/2024 12:16:24                                                                      *
****************************************************************************************************************/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

//****************************** TEMPLATE CODE ******************************//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
//https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html

//****************************** Fast I/O ******************************//
#define fast ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)
//****************************** PAIR ******************************//
#define fi first
#define se second
#define mp make_pair
using p64 = pair<int64_t,int64_t>;
using pdd = pair<double,double>;
#define nl '\n'

//****************************** LOOP ******************************//
#define FOR1(i,a,b) for (int64_t i =(a);i <(b);i++)
#define FOR2(i,a,b) for (int64_t i =(a);i <=(b);i++)
#define FOR3(i, a, b, c) for(int64_t i = (a); i < (b); i += (c))
#define REP1(i,a,b) for (int64_t i =(a);i >(b);i--)
#define REP2(i,a,b) for (int64_t i =(a);i >=(b);i--)
#define REP3(i, a, b, c) for(int64_t i = (a)-1; i >= (b); i -= (c))
#define each(a, x) for (auto &&a : x)

//****************************** VECTOR ******************************//
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int64_t)(x).size())
#define pb push_back
#define eb emplace_back
using v64 = vector<int64_t>;
using vv64 = vector<vector<int64_t>>;
using vp64 = vector<p64>;
using vvp64 = vector<vector<p64>>;

//****************************** OTHERS ******************************//
#define MEM(p, v) memset(p, v, sizeof(p))
#define ceil(n, m) (((n) / (m)) + ((n) % (m) ? 1 : 0))
const int64_t maxn = 1e5 + 5;

template<class Fun> class y_combinator_result {
    Fun fun_;
public:
    template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }
 
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << "," << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

template<class T> bool minimize(T &a, const T &b) { return b < a ? a = b, 1 : 0; } // set a = min(a,b)
template<class T> bool maximize(T &a, const T &b) { return a < b ? a = b, 1 : 0; } // set a = max(a,b)

#define db(val) "["#val " = "<< (val) << "] " 
void dbg_out() { cerr << endl; }
#define dbg(...) cerr << '[' << "Run Test Line" << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

     /*------ MAIN CODE ------*/
//=======================================//
template<const int &MOD>
struct _m_int {
    int val;
 
    _m_int(int64_t v = 0) {
        if (v < 0) v = v % MOD + MOD;
        if (v >= MOD) v %= MOD;
        val = int(v);
    }
 
    _m_int(uint64_t v) {
        if (v >= MOD) v %= MOD;
        val = int(v);
    }
 
    _m_int(int v) : _m_int(int64_t(v)) {}
    _m_int(unsigned v) : _m_int(uint64_t(v)) {}
 
    explicit operator int() const { return val; }
    explicit operator unsigned() const { return val; }
    explicit operator int64_t() const { return val; }
    explicit operator uint64_t() const { return val; }
    explicit operator double() const { return val; }
    explicit operator long double() const { return val; }
 
    _m_int& operator+=(const _m_int &other) {
        val -= MOD - other.val;
        if (val < 0) val += MOD;
        return *this;
    }
 
    _m_int& operator-=(const _m_int &other) {
        val -= other.val;
        if (val < 0) val += MOD;
        return *this;
    }
 
    static unsigned fast_mod(uint64_t x, unsigned m = MOD) {
#if !defined(_WIN32) || defined(_WIN64)
        return unsigned(x % m);
#endif
        // Optimized mod for Codeforces 32-bit machines.
        // x must be less than 2^32 * m for this to work, so that x / m fits in an unsigned 32-bit int.
        unsigned x_high = unsigned(x >> 32), x_low = unsigned(x);
        unsigned quot, rem;
        asm("divl %4\n"
            : "=a" (quot), "=d" (rem)
            : "d" (x_high), "a" (x_low), "r" (m));
        return rem;
    }
 
    _m_int& operator*=(const _m_int &other) {
        val = fast_mod(uint64_t(val) * other.val);
        return *this;
    }
 
    _m_int& operator/=(const _m_int &other) {
        return *this *= other.inv();
    }
 
    friend _m_int operator+(const _m_int &a, const _m_int &b) { return _m_int(a) += b; }
    friend _m_int operator-(const _m_int &a, const _m_int &b) { return _m_int(a) -= b; }
    friend _m_int operator*(const _m_int &a, const _m_int &b) { return _m_int(a) *= b; }
    friend _m_int operator/(const _m_int &a, const _m_int &b) { return _m_int(a) /= b; }
 
    _m_int& operator++() {
        val = val == MOD - 1 ? 0 : val + 1;
        return *this;
    }
 
    _m_int& operator--() {
        val = val == 0 ? MOD - 1 : val - 1;
        return *this;
    }
 
    _m_int operator++(int) { _m_int before = *this; ++*this; return before; }
    _m_int operator--(int) { _m_int before = *this; --*this; return before; }
 
    _m_int operator-() const {
        return val == 0 ? 0 : MOD - val;
    }
 
    friend bool operator==(const _m_int &a, const _m_int &b) { return a.val == b.val; }
    friend bool operator!=(const _m_int &a, const _m_int &b) { return a.val != b.val; }
    friend bool operator<(const _m_int &a, const _m_int &b) { return a.val < b.val; }
    friend bool operator>(const _m_int &a, const _m_int &b) { return a.val > b.val; }
    friend bool operator<=(const _m_int &a, const _m_int &b) { return a.val <= b.val; }
    friend bool operator>=(const _m_int &a, const _m_int &b) { return a.val >= b.val; }
 
    static const int SAVE_INV = int(1e6) + 5;
    static _m_int save_inv[SAVE_INV];
 
    static void prepare_inv() {
        // Make sure MOD is prime, which is necessary for the inverse algorithm below.
        for (int64_t p = 2; p * p <= MOD; p += p % 2 + 1)
            assert(MOD % p != 0);
 
        save_inv[0] = 0;
        save_inv[1] = 1;
 
        for (int i = 2; i < SAVE_INV; i++)
            save_inv[i] = save_inv[MOD % i] * (MOD - MOD / i);
    }
 
    _m_int inv() const {
        if (save_inv[1] == 0)
            prepare_inv();
 
        if (val < SAVE_INV)
            return save_inv[val];
 
        _m_int product = 1;
        int v = val;
 
        while (v >= SAVE_INV) {
            product *= MOD - MOD / v;
            v = MOD % v;
        }
 
        return product * save_inv[v];
    }
 
    _m_int pow(int64_t p) const {
        if (p < 0)
            return inv().pow(-p);
 
        _m_int a = *this, result = 1;
 
        while (p > 0) {
            if (p & 1)
                result *= a;
 
            p >>= 1;
 
            if (p > 0)
                a *= a;
        }
 
        return result;
    }
 
    friend ostream& operator<<(ostream &os, const _m_int &m) {
        return os << m.val;
    }
};
 
template<const int &MOD> _m_int<MOD> _m_int<MOD>::save_inv[_m_int<MOD>::SAVE_INV];
 
extern const int MOD = int(1e9) + 7;
using mod_int = _m_int<MOD>;
 
 
template<int SIZE>
struct mod_matrix_fixed_size {
    static mod_matrix_fixed_size IDENTITY() {
        mod_matrix_fixed_size identity;
 
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                identity[i][j] = i == j;
 
        return identity;
    }
 
    mod_int values[SIZE][SIZE];
 
    mod_matrix_fixed_size() {
        memset(values, 0, sizeof(values));
    }
 
    template<typename T>
    mod_matrix_fixed_size(const vector<vector<T>> &v) {
        init(v);
    }
 
    template<typename T>
    void init(const vector<vector<T>> &v) {
        assert(int(v.size()) == SIZE);
 
        for (int i = 0; i < SIZE; i++) {
            assert(int(v[i].size()) == SIZE);
            copy(v[i].begin(), v[i].end(), values[i]);
        }
    }
 
    mod_int *operator[](int index) { return values[index]; }
    const mod_int *operator[](int index) const { return values[index]; }
 
    mod_matrix_fixed_size operator*(const mod_matrix_fixed_size &other) const {
        mod_matrix_fixed_size product;
 
        for (int i = 0; i < SIZE; i++)
            for (int k = 0; k < SIZE; k++) {
                uint64_t result = 0;
 
                for (int j = 0; j < SIZE; j++)
                    result += uint64_t(values[i][j]) * uint64_t(other[j][k]);
 
                product[i][k] = result;
            }
 
        return product;
    }
 
    mod_matrix_fixed_size& operator*=(const mod_matrix_fixed_size &other) {
        return *this = *this * other;
    }
 
    mod_matrix_fixed_size operator*(mod_int mult) const {
        mod_matrix_fixed_size product;
 
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                product[i][j] = values[i][j] * mult;
 
        return product;
    }
 
    mod_matrix_fixed_size& operator*=(mod_int mult) {
        return *this = *this * mult;
    }
 
    mod_matrix_fixed_size operator+(const mod_matrix_fixed_size &other) const {
        mod_matrix_fixed_size result;
 
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                result[i][j] = values[i][j] + other[i][j];
 
        return result;
    }
 
    mod_matrix_fixed_size& operator+=(const mod_matrix_fixed_size &other) {
        return *this = *this + other;
    }
 
    mod_matrix_fixed_size operator-(const mod_matrix_fixed_size &other) const {
        mod_matrix_fixed_size result;
 
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                result[i][j] = values[i][j] - other[i][j];
 
        return result;
    }
 
    mod_matrix_fixed_size& operator-=(const mod_matrix_fixed_size &other) {
        return *this = *this - other;
    }
 
    mod_matrix_fixed_size power(int64_t p) const {
        assert(p >= 0);
        mod_matrix_fixed_size m = *this, result = IDENTITY();
 
        while (p > 0) {
            if (p & 1)
                result *= m;
 
            p >>= 1;
 
            if (p > 0)
                m *= m;
        }
 
        return result;
    }
 
    void print() const {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                cerr << values[i][j] << (j < SIZE - 1 ? ' ' : '\n');
 
        cerr << endl;
    }
};
 
const mod_matrix_fixed_size<2> FIB_MATRIX = vector<vector<int>>{{0, 1}, {1, 1}};
 
mod_int fibonacci(int64_t n) {
    // F_0 = 0, F_1 = 1
    mod_matrix_fixed_size<2> powered = FIB_MATRIX.power(n);
    return powered[0][1];
}
 
mod_int lucas(int64_t n) {
    // L_n = F_{n - 1} + F_{n + 1}
    mod_matrix_fixed_size<2> powered = FIB_MATRIX.power(n);
    return powered[0][0] + powered[1][1];
}
 
 
int main() {
    int64_t n;
    cin >> n;
    cout << fibonacci(n) << '\n';
}