#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

struct cartesian_node {
    // parent and children are indices of the tree. [start, end) is the range that this node is the min/max of.
    int parent = -1, children[2] = {-1, -1};
    int start, end;
};
 
// Use compare = less<T>() for a min heap and compare = greater<T>() for a max heap.
// When there are ties, the left value will be the parent of the right value.
template<typename T, typename Compare>
vector<cartesian_node> build_cartesian_tree(const vector<T> &A, Compare &&compare) {
    int n = int(A.size());
    vector<cartesian_node> nodes(n);
    vector<int> stack;
 
    auto add_edge = [&](int p, int c, int index) -> void {
        if (p >= 0) nodes[p].children[index] = c;
        if (c >= 0) nodes[c].parent = p;
    };
 
    for (int i = 0; i < n; i++) {
        int erased = -1;
 
        while (!stack.empty() && compare(A[i], A[stack.back()])) {
            nodes[stack.back()].end = i;
            erased = stack.back();
            stack.pop_back();
        }
 
        add_edge(stack.empty() ? -1 : stack.back(), i, 1);
        add_edge(i, erased, 0);
        nodes[i].start = nodes[i].parent + 1;
        stack.push_back(i);
    }
 
    while (!stack.empty()) {
        nodes[stack.back()].end = n;
        stack.pop_back();
    }
 
    return nodes;
}
 
int find_cartesian_tree_root(const vector<cartesian_node> &nodes) {
    int n = int(nodes.size());
 
    for (int i = 0; i < n; i++)
        if (nodes[i].parent < 0)
            return i;
 
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int N;
    cin >> N;
    vector<int> A(N);

    for (auto &a : A)
        cin >> a;

    vector<cartesian_node> min_heap_tree = build_cartesian_tree(A, less<int>());
    vector<cartesian_node> max_heap_tree = build_cartesian_tree(A, greater<int>());

    for (int i = 0; i < N; i++)
        cout << min_heap_tree[i].parent + 1 << (i < N - 1 ? ' ' : '\n');

    for (int i = 0; i < N; i++)
        cout << max_heap_tree[i].parent + 1 << (i < N - 1 ? ' ' : '\n');
}
