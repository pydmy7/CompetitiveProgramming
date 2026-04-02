#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (auto i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        pq.push(x);
    }
    
    while (pq.size() > 1) {
        auto a = pq.top();
        pq.pop();
        auto b = pq.top();
        pq.pop();

        pq.push(a + b - 1);
    }
    
    std::cout << pq.top() << '\n';
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
