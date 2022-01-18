#include <bits/stdc++.h>

using namespace std;

pair<int, int> align(string s)
{
    int i = 0;
    int max_conseq = 0;
    int conseq_l = 0;
    int conseq_l_idx = 0;
    int max_conseq_l_idx = -1;
    for(i=0; i < s.length(); i++){
        if(s[i] == ')'){
            if(conseq_l > max_conseq){
                max_conseq = conseq_l;
                max_conseq_l_idx = conseq_l_idx;
            }
            conseq_l = 0;
        } else {
            if(conseq_l == 0)
                conseq_l_idx = i;
            conseq_l++;
        }
    }
    return {max_conseq, max_conseq_l_idx};
}

int count(string &s)
{
    int c = 0;
    int st = 0;
    for(const auto & ch: s){
        if(ch == '('){
            st++;
        } else {
            st--;
            if(st == 0){
                c++;
            }
        }
    }
    return c;
}

int main() {
//    freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n;
    cin >> n;

    string s;
    cin >> s;

    int l_count =0, r_count = 0;
    for(int i = 0; i<n; i++){
        if(s[i] == '(') ++l_count;
        else ++r_count;
    }
    if(l_count != r_count){
        cout << "0\n1 1";
        return 0;
    }
    int max_conseq, start;
    tie(max_conseq, start) = align(s);
    string temp = s.substr(start, s.length()) + s.substr(0, start);
//    cout << temp << "\n";

    if(max_conseq == 1){
        cout << count(temp) << "\n";
        cout << max_conseq << " " << max_conseq;
    }

    temp.erase(temp.begin());
    temp.insert(temp.end()-1, '(');
//    cout << temp << "\n";

    cout << count(temp) << "\n";
    cout << (start != 0 ? start : n) << " " << start+1;

    return 0;
}
