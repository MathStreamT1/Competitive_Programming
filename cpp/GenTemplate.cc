/***************************************************************
*             Author : Nguyen Tran                             *
***************************************************************/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <complex>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <stack>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << "," << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

auto random_address = [] { char *p = new char; delete p; return uint64_t (p); };

const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);

// Uniformly distributed real number in [a,b].
double real_rng(double a = 0, double b = 1 )
{
	assert(a <= b );
	return uniform_real_distribution<double>(a, b)(rng);
}

// Uniformly distributed integer in [a,b]
int64_t unif_rng(int64_t a,int64_t b)
{
    assert(a <= b );
	return uniform_int_distribution<int64_t>(a,  b)(rng);	
}


// Log-uniform distributed integer in [a,b], P(a) > P(a+1) > ... > P(b)
int64_t log_rng(int64_t a,int64_t b)
{
	assert(a <= b);
	double min_val = double(a) - 0.5;
	double max_val = double(b) + 0.5;
	int64_t x = int64_t(round(min_val - 1 + exp(real_rng(0,log(max_val - min_val + 1 )))));

	// If x - a is large, randomize the lower bits in order to make up for double imprecision
	static const int UNCHANGED_BITS = 30;

	if(uint64_t(x - a) >= 1LLU << UNCHANGED_BITS)
		x ^= rng() >> (__builtin_clzll(x - a ) + UNCHANGED_BITS);

	return min(max(x , a), b);
}

// Return +1 or -1 with 50% probability.
int sign_rng()
{
	return 2 * int(unif_rng(0,1)) - 1;
}

template<typename T_vector>
void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {
    if (start < 0) start = 0;
    if (end < 0) end = int(v.size());

    for (int i = start; i < end; i++)
        cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');
}

bool log_mode = false;

vector<string> process_args(int argc, char **argv)
{
	vector<string> args;
	for(int i = 1; i < argc; i++)
	{
		string arg = argv[i];
		if(arg.find("-log") != string::npos) log_mode = true;
		else args.push_back(arg);
	}

	return args;
}

int main(int argc, char **argv)
{
	cerr << "SEED = " << SEED << endl;
	vector<string> args = process_args(argc, argv);
	assert(args.size() >= 2);
	int64_t N = stoll(args[0]);
	int64_t AB = stoll(args[1]);
	if (log_mode) {
		N = log_rng(1, N);
		AB = log_rng(1, AB);
	}

    cout << N << '\n';
	vector<int64_t> vec(N);
    
	for(auto &a : vec)
	{
		 a = unif_rng(1,AB);
	}

	output_vector(vec);


}

// lưu ý phần Template của Generate này chạy bằng Command Prompt
// nếu như xuất cái test trong Generate Template thực sự cần thiết
// lưu vào 1 file mới 


