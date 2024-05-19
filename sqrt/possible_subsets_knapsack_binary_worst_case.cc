#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    cout << fixed << setprecision(9);

    int64_t n;
    cin >> n;

    int cutoff = int(sqrt(n)) + 1;

    vector<int64_t> heap;
    for (int i = 1; i <= cutoff; i++)
    {
        heap.push_back(i);

        for (int x = 1; x <= cutoff; x *= 2)
        {
            heap.push_back(x);
        }
    }

    make_heap(heap.begin(), heap.end(), greater<int>());
    int64_t sum = 0, cost = 0;

    while (sum + heap.front() <= n)
    {
        sum += heap.front();
        pop_heap(heap.begin(), heap.end(), greater<int>());
        heap.pop_back();

        cost++;
    }

    cout << "front =" << heap.front() << '\n';
    cout << "cost =" << cost << '\n';
    cout << "ratio =" << cost / sqrt(n) << '\n';
    cout << "sqrt(6)" << sqrt(6) << '\n';
    return 0;
}
