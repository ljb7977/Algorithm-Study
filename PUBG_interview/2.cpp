#include <iostream>
#include <vector>

using namespace std;

void update(vector<bool>& segtree, int index, int node, int node_left, int node_right)
{
    if(index < node_left || index > node_right)
        return;

    if(node_left == node_right){
        segtree[node] = true;
        return;
    }

    int node_middle = (node_left+node_right) / 2;

    update(segtree, index, node*2, node_left, node_middle);
    update(segtree, index, node*2+1, node_middle+1, node_right);

    segtree[node] = segtree[node*2] && segtree[node*2+1];
}

void turnSwitchOn(vector<bool> &segtree, int a, int n)
{
    //update segtree
    update(segtree, a, 1, 1, n);
}

bool query(vector<bool>& segtree, int l, int r, int node, int node_left, int node_right)
{
    if(r < node_left || l > node_right)
        return true;
    if(l <= node_left && node_right <= r)
        return segtree[node];
    int node_middle = (node_left+node_right) / 2;

    bool left_val = query(segtree, l, r, node*2, node_left, node_middle);
    bool right_val = query(segtree, l, r, node*2+1, node_middle+1, node_right);

    return left_val && right_val;
}

bool areEveryBulbsTurnedOn(vector<bool> &segtree, int n, int max_n)
{
    //query segtree
    return query(segtree, 1, n, 1, 1, max_n);
}

int solution(vector<int> &A) {
    vector<bool> bulbsSegTree(A.size()*4);
    int count = 0;
    for(int i = 0; i < A.size(); i++){
        turnSwitchOn(bulbsSegTree, A[i], A.size());
        if(areEveryBulbsTurnedOn(bulbsSegTree, i+1, A.size()))
            ++count;
    }
    return count;
}

int main() {
    vector<int> v = {1, 3, 4, 2, 5};
    cout << solution(v);
    return 0;
}
