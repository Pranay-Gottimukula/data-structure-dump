#include<bits/stdc++.h>
using namespace std;

class segtree{
public:
    vector<int> seg;
    vector<int> lazy;

    segtree(int n){
        seg.resize(4 * n);
        lazy.resize(4 * n);
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

    // To fix lazy updation
    void push(int ind, int low, int high){
        if(lazy[ind] != 0){
            seg[ind] += lazy[ind];

            if(low != high){
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }

            lazy[ind] = 0;
        }
    }

    int query(int ind, int low, int high, int l, int r){

        push(ind, low, high);   // For Lazy updation
    
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

    // Point update, updates value at index i to val
    void update(int ind, int low, int high, int i, int val){

        push(ind, low, high);

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

    // range addition, for i in range l to r, it updates arr[i] = arr[i] + val
    void updatelazy(int ind, int low, int high, int l, int r, int val){

        push(ind, low, high);

        if(r < low || l > high){
            return;
        }

        if(l <= low && high <= r){
            seg[ind] += val;

            if(low != high){
                lazy[2 * ind + 1] += val;
                lazy[2 * ind + 2] += val;
            }

            return;
        }

        int mid = low + (high - low) / 2;
        updatelazy(2 * ind + 1, low, mid, l, r, val);
        updatelazy(2 * ind + 2, mid + 1, high, l, r, val);

        seg[ind] = max(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
};