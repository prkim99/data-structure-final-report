//#include <iostream>
//#include <algorithm>
//#include <stack>
//#include <vector>
//using namespace std;
//vector<int> adListGraph[50001];
//vector<int> transGraph[50001];
//bool visit[50001];
//bool transVisit[50001];
//int SCC[50000];
//vector<int> s;
//
//void dfs(int cur) {
//	visit[cur] = 1;
//	if (adListGraph[cur].size() != 0) {
//		int k = 0;
//		while (k < adListGraph[cur].size()) {
//			k++;
//			int next = -1;
//			int maxfollower = -1;
//			for (int i = 0; i < adListGraph[cur].size(); i++) {
//				if (visit[adListGraph[cur][i]] == 1)
//					continue;
//				int nextCandidate = adListGraph[cur][i];
//				int candidateFollower = transGraph[nextCandidate].size();
//
//				if (maxfollower < candidateFollower) {
//					next = nextCandidate;
//					maxfollower = candidateFollower;
//				}
//				else if (maxfollower == candidateFollower) {
//					if (next > nextCandidate) {
//						next = nextCandidate;
//						maxfollower = candidateFollower;
//					}
//				}
//			}
//			if (next == -1)	continue;
//			dfs(next);
//		}
//	}
//	s.push_back(cur);
//}
//void phase1(int N) {
//	int j = 0;
//	while (j < N) {
//		j++;
//		int maxfollower = -1;
//		int startVertex = -1;
//		for (int i = 1; i < N+1; i++) {
//			if (visit[i] == 1) continue;
//			int a = transGraph[i].size();
//			if (maxfollower < a) {
//				maxfollower = transGraph[i].size();
//				startVertex = i;
//			}
//		}
//		if (startVertex == -1)continue;
//		dfs(startVertex);
//	}
//}
//
//void dfs2(int leader, int cur) {
//	transVisit[cur] = 1;
//	SCC[cur] = leader;
//	if (transGraph[cur].size() != 0) {
//		int k = 0;
//		while (k < transGraph[cur].size()) {
//			k++;
//			int next = -1;
//			int maxfollower = -1;
//			for (int i = 0; i < transGraph[cur].size(); i++) {
//				if (transVisit[transGraph[cur][i]] == 1)
//					continue;
//				
//				int nextCandidate = transGraph[cur][i];
//				int candidateFollower = transGraph[nextCandidate].size();
//
//				if (maxfollower < candidateFollower) {
//					next = nextCandidate;
//					maxfollower = candidateFollower;
//				}
//				else if (maxfollower == candidateFollower) {
//					if (next > nextCandidate) {
//						next = nextCandidate;
//						maxfollower = candidateFollower;
//					}
//				}
//			}
//			if (next == -1)	continue;
//			dfs2(leader, next);
//		}
//	}
//
//}
//void phase2(int N) {
//	int j = 0;
//	while (j<N) {
//		j++;
//		int leader = s.back();
//		s.pop_back();
//		if (transVisit[leader] == 1) continue;
//		dfs2(leader, leader);
//	}
//}
//
//int main() {
//
//	ios::sync_with_stdio(false);
//	cin.tie(NULL);
//	cout.tie(NULL);
//
//	int N, M, k = 0, u1, u2;
//	cin >> N>> M;
//	while (k < M) {
//		cin >> u1 >> u2;
//		adListGraph[u1].push_back(u2);
//		transGraph[u2].push_back(u1);
//		visit[u1] = 0;
//		transVisit[u2] = 0;
//		k++;
//	}
//
//	phase1(N);
//	k = 0;
//	while (k < N) {
//		cout << s[k] << " ";
//		k++;
//	}
//	cout << endl;
//	phase2(N);
//	k = 1;
//	while (k < N+1) {
//		cout << SCC[k] << " ";
//		k++;
//	}
//	cout << endl;
//	return 0;
//}