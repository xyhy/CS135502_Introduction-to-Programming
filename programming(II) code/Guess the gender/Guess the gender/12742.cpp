//
//  main.cpp
//  Guess the gender
//
//  Created by 顏浩昀 on 2020/4/28.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

// Author: justin0u0
#include <iostream>
#include "12742.h"
using namespace std;

int main() {
	// iostream optimize
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;
	Graph G(n);
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		G.addEdge(x, y);
		G.addEdge(y, x);
	}
	if (G.solver())
		cout << "Possible" << endl;
	else
		cout << "Not Possible" << endl;
	return 0;
}
