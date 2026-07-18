#include<bits/stdc++.h>
using namespace std;

class segtree{
public:
    vector<int> seg;

    segtree(int n){
        seg.resize(4 * n);
    }

    void build(int ind, int low, int high, vector<int>& arr){
        if(low == high){
            seg[ind] = arr[low];
            return;
        }

        int mid = low + (high - low) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);

        seg[ind] = max(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    int query(int ind, int low, int high, int l, int r){
        if(l <= low && high <= r){
            return seg[ind];
        }
        if(l > high || r < low){
            return INT_MIN;
        }

        int mid = low + (high - low) / 2;
        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);

        return max(left, right);
    }

    void update(int ind, int low, int high, int i, int val){
        if(low == high){
            seg[ind] = val;
            return;
        }

        int mid = low + (high - low) / 2;

        if(i <= mid){
            update(2 * ind + 1, low, mid, i, val);
        }
        else{
            update(2* ind + 2, mid + 1, high, i, val);
        }

        seg[ind] = max(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
};