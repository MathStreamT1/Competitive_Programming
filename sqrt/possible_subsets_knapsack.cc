/****************************************************************************************************************
*             Author : Nguyen Tran                                                                              *
*             Created: 19/05/2024 11:41:55                                                                      *
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
namespace IO {
    const int BUFFER_SIZE = 1 << 15;
 
    char input_buffer[BUFFER_SIZE];
    size_t input_pos = 0, input_len = 0;
 
    void _update_input_buffer() {
        input_len = fread(input_buffer, sizeof(char), BUFFER_SIZE, stdin);
        input_pos = 0;
 
        if (input_len == 0)
            input_buffer[0] = EOF;
    }
 
    inline char next_char(bool advance = true) {
        if (input_pos >= input_len)
            _update_input_buffer();
 
        return input_buffer[advance ? input_pos++ : input_pos];
    }
 
    template<typename T>
    inline void read_int(T &number) {
        bool negative = false;
        number = 0;
 
        while (!isdigit(next_char(false)))
            if (next_char() == '-')
                negative = true;
 
        do {
            number = 10 * number + (next_char() - '0');
        } while (isdigit(next_char(false)));
 
        if (negative)
            number = -number;
    }
 
    template<typename T, typename... Args>
    inline void read_int(T &number, Args &... args) {
        read_int(number);
        read_int(args...);
    }
}
 
struct union_find {
    // When data[x] < 0, x is a root and -data[x] is its tree size. When data[x] >= 0, data[x] is x's parent.
    vector<int> data;
    int components = 0;
 
    union_find(int n = -1) {
        if (n >= 0)
            init(n);
    }
 
    void init(int n) {
        data.assign(n + 1, -1);
        components = n;
    }
 
    int find(int x) {
        return data[x] < 0 ? x : data[x] = find(data[x]);
    }
 
    int get_size(int x) {
        return -data[find(x)];
    }
 
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
 
        if (x == y)
            return false;
 
        if (-data[x] < -data[y])
            swap(x, y);
 
        data[x] += data[y];
        data[y] = x;
        components--;
        return true;
    }
};
 
int highest_bit(unsigned x) {
    return x == 0 ? -1 : 31 - __builtin_clz(x);
}
 
// Computes all possible subset sums from 0 to n that can be made using values from sizes. Runs in O(n sqrt n / 64) if
// the sum of sizes is bounded by n, and O(n^2 / 64) otherwise.
template<int N_MAX>
bitset<N_MAX> possible_subsets_knapsack(int n, const vector<int> &sizes) {
    vector<int> freq(n + 1, 0);
 
    for (int s : sizes)
        if (1 <= s && s <= n)
            freq[s]++;
 
    bitset<N_MAX> knapsack;
    knapsack[0] = 1;
 
    // Note that this is actually O(sqrt n) bitset operations and not just O(sqrt n * log n) bitset operations.
    for (int s = 1; s <= n; s++)
        if (freq[s] > 0) {
            freq[s] = min(freq[s], n / s);
            freq[s]++;
 
            auto apply_shift = [&](int shift) -> void {
                if (shift != 0)
                    knapsack |= knapsack << (shift * s);
            };
 
            int high = 1 << highest_bit(freq[s]);
 
            for (int p = 1; p < high; p *= 2)
                apply_shift(p);
 
            apply_shift(freq[s] - high);
        }
 
    return knapsack;
}
 
 
#ifdef NguyenTran
const int N_MAX = int(1e6) + 5;
#else
const int N_MAX = int(1e5) + 5;
#endif
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
    int N, M;
    IO::read_int(N, M);
    union_find UF(N);
 
    for (int i = 0; i < M; i++) {
        int a, b;
        IO::read_int(a, b);
        a--; b--;
        UF.unite(a, b);
    }
 
    vector<int> sizes;
 
    for (int i = 0; i < N; i++)
        if (UF.find(i) == i)
            sizes.push_back(UF.get_size(i));
 
    bitset<N_MAX> knapsack = possible_subsets_knapsack<N_MAX>(N, sizes);
 
    for (int i = 1; i <= N; i++)
        cout << knapsack[i];
 
    cout << '\n';
}