#include <iostream>
#include <vector>

using namespace std;

void count_alphabet(vector<int>& alphabet_cnt, const string& str)
{
    for(char i : str)
        alphabet_cnt[i-'a']++;
}

void solve()
{
    int n;
    string s, t;
    cin >> n;
    cin >> s >> t;

    vector<int> alphabet_cnt(26);
    count_alphabet(alphabet_cnt, s);
    count_alphabet(alphabet_cnt, t);

    for(int cnt:alphabet_cnt){
        if(cnt%2 != 0){
            cout << "No\n";
            return;
        }
    }

    int cnt = 0;
    vector<pair<int, int>> history;
    for(int i = 0; i<s.size(); i++){
        if(s[i] != t[i]){
            for(int j = i+1; j<s.size(); j++){
                if(s[j] != t[j]){
                    if(s[j] == s[i]){
                        swap(s[j], t[i]);
                        history.emplace_back(j, i);
                        cnt++;
                        break;
                    } else if (t[j] == s[i]) {
                        swap(t[j], s[j]);
                        swap(s[j], t[i]);
                        history.emplace_back(j, j);
                        history.emplace_back(j, i);
                        cnt+=2;
                        break;
                    }
                }
            }
        }
    }
    cout << "Yes\n" << cnt << "\n";
    for(auto h : history){
        cout << h.first+1 << " " << h.second+1 << "\n";
    }
    return;
}

int main()
{
//    freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int k;
    cin >> k;
    while(k--){
        solve();
    }

    return 0;
}