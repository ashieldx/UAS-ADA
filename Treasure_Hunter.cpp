#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9, MAX = 55;
char map[MAX][MAX];
int dist[MAX][MAX];
int DP[MAX][MAX];
int X[] = {-1, 1, 0, 0};
int Y[] = {0, 0, -1, 1};
bool visited[MAX][MAX];
int N, M, T;
int x1, y1;

bool check(int x, int y, int i){
	return(x+X[i] >=0 && x+X[i] < N && y+Y[i] >=0 && y+Y[i] < M);
}

int bitmask(int s, int n, int mask){
	if(!mask) return 0;	
	int ans = INF;
	for(int i = 0; i < T; i++){
		if(mask & (1 << i)){
			ans = min(ans, bitmask(i, n, (mask ^ (1 << i))) + DP[s][i]);
		}
	}
	return ans;
}

void bfs(int x, int y){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			dist[i][j] = INF;
		}
	}
	dist[x][y] = 0;
	queue<pair<int, int> > q;
	
	q.push(make_pair(x, y));
	
	while(!q.empty()){
		int u = q.front().first;
		int v = q.front().second;
		q.pop();
		
		for(int i = 0; i < 4; i++){
			if(check(u, v, i) && map[u+X[i]][v+Y[i]] != '#' && dist[u+X[i]][v+Y[i]] == INF){
				dist[u+X[i]][v+Y[i]] = dist[u][v] + 1;
				q.push(make_pair(u+X[i], v+Y[i]));
			}
		}
	}
}

int main(){
	cin >> N >> M >> T;
	cin >> x1 >> y1;
	
	vector<pair<int, int> > treasure;
	
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			cin >> map[i][j];
			if(map[i][j] == '*' || (i == x1-1 && j == y1-1)){
				treasure.push_back(make_pair(i, j));
			}
			DP[i][j] = INF;		
		}
	}
	T++;
	int s;
	for(int i = 0; i < T; i++){
		int x = treasure[i].first, y = treasure[i].second;
		if(x == x1-1 && y == y1-1) s = i;
		bfs(x, y);
		for(int j = 0; j < T; j++){
			int u = treasure[j].first, v = treasure[j].second;
			DP[i][j] = dist[u][v];
			if(DP[i][j] == INF){
				cout << -1 << endl;
				return 0;
			}
		}
	}
	
	int mask = ((1 << T) - 1);
	mask = (mask ^ (1 << s));
	
	int steps = bitmask(s, T, mask);
	cout << steps << endl;
	
	return 0;
}





