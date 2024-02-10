//
//  main.cpp
//  Parentheses Matching
//
//  Created by 顏浩昀 on 2020/6/18.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include <map>

using namespace std;

map<char, char> mapping {
    {'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}
};

int main() {
    string input;
    int T = 0;
    cin>>T;
    getline(cin, input);
    for (int i = 1; i <= T; i++) {
        stack<char> par;
        bool valid = true;
        getline(cin, input);
        for(char c : input){
            if(c == '(' || c == '[' || c == '{' || c == '<')    par.push(c);
            else if(c==')' || c == ']' || c == '}' || c == '>'){
                if(par.empty()){
                    valid = false;                    break;
                }else if(mapping[par.top()] != c){
                    valid = false;
                    break;
                }else{
                    par.pop();
                }
            }
        }
        if(!par.empty())    valid = false;
        cout<<"Case " <<i<<": ";
        if(valid)   cout<<"Yes\n";
        else    cout<<"No\n";
    }
    return 0;
}
