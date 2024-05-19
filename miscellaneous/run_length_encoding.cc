/****************************************************************************************************************
*             Author : Nguyen Tran                                                                              *
*             Created: 03/04/2024 21:26:09                                                                      *
****************************************************************************************************************/
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

template<typename T, typename T_iterable>
vector<pair<T, int>> run_length_encoding(const T_iterable &items) {
    vector<pair<T, int>> runs;
    T previous;
    int count = 0;
 
    for (const T &item : items)
        if (item == previous) {
            count++;
        } else {
            if (count > 0)
                runs.emplace_back(previous, count);
 
            previous = item;
            count = 1;
        }
 
    if (count > 0)
        runs.emplace_back(previous, count);
 
    return runs;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str;
    cin >> str;

    vector<pair<char,int>> runs = run_length_encoding<char> (str);

    for(auto &pr : runs)
       cout << pr.first << ' ' << pr.second << '\n';
    return 0;
}

