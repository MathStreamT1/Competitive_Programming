#include<bits/stdc++.h>

using namespace std;

// For every mask, computes the sum of `values[sub]` where `sub` is a submask of mask.
template<typename T_out, typename T_in>
vector<T_out> submask_sums(const vector<T_in> &values) {
    int n = __builtin_ctz(int(values.size()));
    assert(int(values.size()) == 1 << n);
    vector<T_out> dp(values.begin(), values.end());

    // Broken profile DP where the intermediate DP state consists of the i-th suffix of the previous row and the i-th
    // prefix of the current row.
    for (int i = 0; i < n; i++)
        for (int base = 0; base < 1 << n; base += 1 << (i + 1))
            for (int mask = base; mask < base + (1 << i); mask++)
                dp[mask + (1 << i)] += dp[mask];

    return dp;
}

// For every mask, computes the sum of `values[sup]` where mask is a submask of `sup`.
template<typename T_out, typename T_in>
vector<T_out> supermask_sums(vector<T_in> values) {
    reverse(values.begin(), values.end());
    vector<T_out> result = submask_sums<T_out>(values);
    reverse(result.begin(), result.end());
    return result;
}

// Does the inverse of `submask_sums`; returns the input that produces the given output.
// Note that this also computes bitmask inclusion-exclusion.
template<typename T_out, typename T_in>
vector<T_out> mobius_transform(const vector<T_in> &values) {
    int n = __builtin_ctz(int(values.size()));
    assert(int(values.size()) == 1 << n);
    vector<T_out> dp(values.begin(), values.end());

    for (int i = 0; i < n; i++)
        for (int base = 0; base < 1 << n; base += 1 << (i + 1))
            for (int mask = base; mask < base + (1 << i); mask++)
                dp[mask + (1 << i)] -= dp[mask];

    return dp;
}

// Does the inverse of `supermask_sums`; returns the input that produces the given output.
template<typename T_out, typename T_in>
vector<T_out> super_mobius_transform(vector<T_in> values) {
    reverse(values.begin(), values.end());
    vector<T_out> result = mobius_transform<T_out>(values);
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> A(1 << N);

    for (int &a : A)
        cin >> a;

    long double begin = clock();
    vector<int64_t> sums = submask_sums<int64_t>(A);
    cerr << "submask_sums: " << (clock() - begin) / CLOCKS_PER_SEC << 's' << endl;

    for (int i = 0; i < 1 << N; i++)
        cout << sums[i] << (i < (1 << N) - 1 ? ' ' : '\n');

    vector<int64_t> super_sums = supermask_sums<int64_t>(A);

    for (int i = 0; i < 1 << N; i++)
        cout << super_sums[i] << (i < (1 << N) - 1 ? ' ' : '\n');

    vector<int64_t> A64 = mobius_transform<int64_t>(sums);
    assert(vector<int64_t>(A.begin(), A.end()) == A64);
    A64 = super_mobius_transform<int64_t>(super_sums);
    assert(vector<int64_t>(A.begin(), A.end()) == A64);
}
