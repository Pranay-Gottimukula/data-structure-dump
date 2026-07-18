#include<bits/stdc++.h>
using namespace std;

class Node{
public:
    Node* links[2] = {nullptr, nullptr};
    bool flag = false;
};

class Trie{
public:
    Node* root;

    Trie(){
        root = new Node();
    }

    void insert(int x){
        Node* node = root;

        for(int i = 31; i >= 0; i--){
            int bit = (x >> i) & 1;

            if(!node->links[bit]) node->links[bit] = new Node();

            node = node->links[bit];
        }

        node->flag = true;
    }

    int checkmax(int x){
        Node* node = root;
        int res = 0;

        for(int i = 31; i >= 0; i--){
            int bit = (x >> i) & 1;
            int needed = 1 - bit;

            if(!node->links[needed]){
                node = node->links[bit];
            }
            else{
                res = res | (1 << i);
                node = node->links[needed];
            }
        }

        return res;
    }
};

int main(){
    int n;
    cin >> n;

    vector<int> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    Trie trie;

    for(int i = 0; i < n; i++){
        trie.insert(arr[i]);
    }

    int ans = 0;
    for(int i = 0; i < n; i++){
        ans = max(ans, trie.checkmax(arr[i]));
    }

    cout << ans << endl;
    return 0;
}