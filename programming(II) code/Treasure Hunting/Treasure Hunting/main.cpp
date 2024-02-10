//
//  main.cpp
//  Treasure Hunting
//
//  Created by 顏浩昀 on 2020/6/4.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// G[i] is the neighbor towns of town i
vector<int> diamondTowns;
vector<int> G[100005];
int Dist[100005];

struct node {
    int id;
    int dist;
    node(int id, int l) {
        this->id = id;
        this->dist = l;
    }
};

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for (int i = 0; i < K; i++) {
        int x;
        cin >> x;
        diamondTowns.push_back(x);
    }
    fill(Dist, Dist+100005, -1);

    queue<node> Q;

    // [TODO] complete the task!
    for(auto diamand : diamondTowns){
        Q.push(node(diamand, 0));
    }
    while(!Q.empty()){
        node cur = Q.front();
        Q.pop();
        if(Dist[cur.id] == -1){
            Dist[cur.id] = cur.dist;
            for(auto g : G[cur.id]){
                Q.push(node(g, cur.dist+1));
            }
        }
    }
    // Output
    for (int i = 1; i <= N; i++) {
        cout << Dist[i] << '\n';
    }
    return 0;
}
