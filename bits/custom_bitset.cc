#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,lzcnt,mmx,abm,avx,avx2,tune=native")

// Note: for purely unrolling loops, also try running with just the first line only
// Note: also try running without unroll-loops (not for bitset)

// Hirchsberg's algorithm for the subset sum problem. See https://en.wikipedia.org/wiki/Hirschberg%27s_algorithm
// The goal is to solve the provlem and provide a reconstruction in O(NT) time and O(T) space, rather than O(NT) space.
// The main idea is to compute the knapsack from 0 to N/2 and from N to N/2. Then find any optimal point S at N/2 and 
// recurse on (N/2, S) and (N/2, T - S). We're recursing on two rectangles whose area is NT/2, so the runtime is O(NT)

#include<algorithm>
#include<array>
#include<cassert>
#include<chrono>
#include<cmath>
#include<cstring>
#include<functional>
#include<iomanip>
#include<iostream>
#include<map>
#include<numeric>
#include<queue>
#include<random>
#include<set>
#include<vector>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << "," << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifndef NguyenTran_DEBUG
#define dbg(...) cerr << '[' << "Run Test Line" << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

struct custom_bitset {
    vector<uint64_t> bits;
    int64_t b, n;
 
    custom_bitset(int64_t _b = 0) {
        init(_b);
    }
 
    void init(int64_t _b) {
        b = _b;
        n = (b + 63) / 64;
        bits.assign(n, 0);
    }
 
    void clear() {
        b = n = 0;
        bits.clear();
    }
 
    void reset() {
        bits.assign(n, 0);
    }
 
    void _clean() {
        // Reset all bits after `b`.
        if (b != 64 * n)
            bits.back() &= (1LLU << (b - 64 * (n - 1))) - 1;
    }
 
    bool get(int64_t index) const {
        return bits[index / 64] >> (index % 64) & 1;
    }
 
    void set(int64_t index, bool value) {
        assert(0 <= index && index < b);
        bits[index / 64] &= ~(1LLU << (index % 64));
        bits[index / 64] |= uint64_t(value) << (index % 64);
    }
 
    // Simulates `bs |= bs << shift;`
    void or_shift(int64_t shift) {
        int64_t div = shift / 64, mod = shift % 64;
 
        if (mod == 0) {
            for (int64_t i = n - 1; i >= div; i--)
                bits[i] |= bits[i - div];
 
            return;
        }
 
        for (int64_t i = n - 1; i >= div + 1; i--)
            bits[i] |= bits[i - (div + 1)] >> (64 - mod) | bits[i - div] << mod;
 
        if (div < n)
            bits[div] |= bits[0] << mod;
 
        _clean();
    }
 
    // Simulates `bs |= bs >> shift;`
    void or_shift_down(int64_t shift) {
        int64_t div = shift / 64, mod = shift % 64;
 
        if (mod == 0) {
            for (int64_t i = div; i < n; i++)
                bits[i - div] |= bits[i];
 
            return;
        }
 
        for (int64_t i = 0; i < n - (div + 1); i++)
            bits[i] |= bits[i + (div + 1)] << (64 - mod) | bits[i + div] >> mod;
 
        if (div < n)
            bits[n - div - 1] |= bits[n - 1] >> mod;
 
        _clean();
    }
 
    int64_t find_first() const {
        for (int i = 0; i < n; i++)
            if (bits[i] != 0)
                return 64 * i + __builtin_ctzll(bits[i]);
 
        return -1;
    }
 
    custom_bitset& operator&=(const custom_bitset &other) {
        assert(b == other.b);
 
        for (int i = 0; i < n; i++)
            bits[i] &= other.bits[i];
 
        return *this;
    }
};

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    int64_t T;
    cin >> N >> T;

    vector<int64_t> A(N);
    
    for(auto &a : A) cin >> a;

    vector<custom_bitset> knapsack(N + 1);

    knapsack[0].init(T + 1);
    knapsack[0].set(0,true);

    for(int i = 0; i < N; i++)
    {
        knapsack[i+1]= knapsack[i];
        knapsack[i+1].or_shift(A[i]);
    }

    if(!knapsack[N].get(T))
    {
        cout << "NO" << '\n';
        return 0;
    }

    cout <<"YES" << '\n';
    vector<bool> included(N,false);
    int64_t current = T;
    for (int i = N - 1; i >= 0; i--)
    {
        assert(knapsack[i+1].get(current));
        if(!knapsack[i].get(current)){
            current -= A[i];
            assert(current >=0 && knapsack[i].get(current));
            included[i]= true;
        }
    }

    for(const auto &x : included)
    {
        cout << x;
    }

    cout << "\n";
    return 0;
}
