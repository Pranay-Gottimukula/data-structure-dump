#include<bits/stdc++.h>
using namespace std;

class DSU{
public:
    vector<int> size;
    vector<int> par;

    DSU(int n){
        size.resize(n + 1, 1);
        par.resize(n + 1);

        for(int i = 0; i <= n; i++){
            par[i] = i;
        }
    }

    int findp(int u){
        if(par[u] == u) return u;
        return par[u] = findp(par[u]);
    }

    bool unite(int u, int v){
        u = findp(u);
        v = findp(v);

        if(u == v) return false;

        if(v > u) swap(u, v);

        par[v] = u;
        size[u] += size[v];
        return true;
    }
};