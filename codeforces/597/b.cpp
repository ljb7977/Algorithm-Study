#include <bits/stdc++.h>

using namespace std;

int main() {
//    freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        int n;
//        int a, b, c;
        int cand[3];
        cin >> n;
        cin >> cand[0] >> cand[1] >> cand[2];
        string s;
        cin >> s;

        int win=0;
        char my[3] = {'R', 'P', 'S'};
        char your[3] = {'S', 'R', 'P'};
        int num[3] = {0};
        vector<char> win_seq(n, 'X');

        for (char ch : s) {
            if(ch == 'R') {
                ++num[1];
            } else if (ch == 'P') {
                ++num[2];
            } else if (ch == 'S') {
                ++num[0];
            }
        }

        vector<int> positive;
        vector<int> negative;
        for(int i = 0; i <3; i++){
            if (num[i] <= cand[i]) positive.push_back(i);
            else negative.push_back(i);
            win += min(num[i], cand[i]);
        }

        if(win < (n+1)/2){
            cout << "NO\n";
            continue;
        }

        for(int i: positive){
            for(int j = 0; j<s.size(); j++){
                if(s[j] == your[i]){
                    win_seq[j] = my[i];
                    --cand[i];
                }
            }
        }
        for(int i: negative){
            for(int j = 0; j<s.size(); j++){
                if(s[j] == your[i]){
                    if(cand[i] > 0){
                        win_seq[j] = my[i];
                        --cand[i];
                    }
                }
            }
        }

        for(int j = 0; j<s.size(); j++){
            if(win_seq[j] == 'X'){
                int i;
                for(i = 0; i<3; i++)
                    if(cand[i] > 0)
                        break;

                win_seq[j] = my[i];
                --cand[i];
            }
        }

        cout << "YES\n";
        for(char ch: win_seq){
            cout << ch;
        }
        cout << '\n';
    }
    return 0;
}
