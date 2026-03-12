//implementacja bcc

void find_bcc(int v) {
	pre[v] = low[v] = tick++;
	for (auto ch : g[v]) if(ch != par[v]) {
		if (pre[ch] == -1) { // krawedz drzewowa
			par[ch] = v;
			stack.push_back(MP(v, ch));
			find_bcc(ch);
			low[v] = std::min(low[v], low[ch]);
			if (low[ch] >= pre[v]) {
				// z tego poddrzewa nie da sie wyskoczyc do gory
				// wiec znalezlismy dwuspojna
				bcc.emplace_back();
				do {
					bcc.back().push_back(stack.back());
					stack.pop_back();
				} while(bcc.back().back() != MP(v, ch));
			}
		} else if(pre[ch] < pre[v]) { // krawedz niedrzewowa w gore
			low[v] = std::min(low[v], pre[ch]);
			stack.push_back(MP(v, ch));
		}
	}
}