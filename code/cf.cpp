#include <bits/stdc++.h>
using namespace std;

// class Solution {
// public:
//     int minJumps(vector<int>& nums) {
//
//     }
// };

#define MAXA ((int) 1e6)
bool inited = false;
vector<int> fac[MAXA + 5];
void init() {
    if (inited) return;
    inited = true;
    for (int i = 2; i <= MAXA; i++)
        if (fac[i].empty())
            for (int j = i; j <= MAXA; j += i)
                fac[j].push_back(i);
}

class Solution {
public:
    int minJumps(vector<int>& nums) {
        init();
        int n = nums.size();
        // 把要用到的质数都挑出来
        unordered_map<int, int> mp;
        for (int i = 0; i < n; i++) if (fac[nums[i]].size() == 1) mp[nums[i]] = 1;
        int K = 0;
        for (auto &p : mp) p.second = n + K, K++;

        // 建图
        vector<int> e[n + K], v[n + K];
        for (int i = 0; i < n; i++) {
            // 相邻下标移动
            if (i > 0) e[i].push_back(i - 1), v[i].push_back(1);
            if (i + 1 < n) e[i].push_back(i + 1), v[i].push_back(1);
            // 质数传送：值为质数的下标向特殊点连边
            if (fac[nums[i]].size() == 1) e[i].push_back(mp[nums[i]]), v[i].push_back(1);
            // 质数传送：质因数特殊点向下标连边
            for (int x : fac[nums[i]]) if (mp.count(x)) {
                int idx = mp[x];
                e[idx].push_back(i);
                v[idx].push_back(0);
            }
        }

        // 模板：01 BFS
        int dis[n + K];
        memset(dis, -1, sizeof(dis));
        typedef pair<int, int> pii;
        deque<pii> dq;
        dq.push_back({0, 0}); dis[0] = 0;
        while (!dq.empty()) {
            pii p = dq.front(); dq.pop_front();
            int sn = p.first;
            if (dis[sn] != p.second) continue;
            if (sn == n - 1) return dis[sn];

            auto update = [&](int fn, int val) {
                int d = dis[sn] + val;
                if (dis[fn] == -1 || dis[fn] > d) {
                    dis[fn] = d;
                    if (val == 0) dq.push_front({fn, d});
                    else dq.push_back({fn, d});
                }
            };

            for (int i = 0; i < e[sn].size(); i++) update(e[sn][i], v[sn][i]);
        }
        return -1;
    }
};
