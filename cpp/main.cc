/****************************************************************************************************************
*             Author : Nguyen Tran                                                                              *
*             Created: 19/05/2024 12:55:26                                                                      *
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
void solve()
{
    
}

int main(int argc, char const *argv[])
{
    fast;

    #ifdef ONLINE_JUDGE
      freopen("input.txt", "r", stdin);
      freopen("output.txt", "w", stdout);
    #endif
    
    int64_t tests = 1;
    while(tests--) solve();
    return 0;
}