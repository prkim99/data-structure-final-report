#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
//인접리스트를 활용한 방향그래프
vector<int> adListGraph[50002];
//인접리스트를 활용한 방향그래프의 전치
vector<int> transGraph[50002];
//방문한 vertex정보 저장
bool visit[50002];
//전치 그래프의 방문한 vertex정보 저장
bool transVisit[50002];
//SCC를 찾아 사용자별 그룹 리더 정보 저장
int SCC[50002];
//phase1이 끝난 후 결과물로 나오는 스택
vector<int> s;

//DFS수행시 탐색 우선순위를 결정하는 비교 함수
bool compare(pair<int, int> a, pair<int, int>b) {
	if (a.first == b.first) {
		return a.second < b.second;
	}
	else {
		return a.first > b.first;
	}
}

//첫번째 DFS를 수행하는 함수
void dfs(int cur) {
	visit[cur] = 1;
	if (adListGraph[cur].size() != 0) {
		//현재 vertex에 인접한 vertex들을 리스트에 저장
		vector<pair<int,int>>seq;
		for (int i = 0; i < adListGraph[cur].size(); i++) {
			if (visit[adListGraph[cur][i]] == 1)
				continue;
			seq.push_back(pair<int, int>(transGraph[adListGraph[cur][i]].size(), adListGraph[cur][i]));
		}
		//비교함수에 따라 리스트 정렬
		sort(seq.begin(), seq.end(), compare);
		//정렬한 vertex 리스트에서 원소 순서대로 인접한 vertex 방문
		for (int i = 0; i < seq.size(); i++) {
			if (visit[seq[i].second] == 1)
				continue;
			//재귀함수를 통한 DFS 수행
			dfs(seq[i].second);
		}
	}
	//탐색완료한 vertex 스택에 삽입
	s.push_back(cur);
}

//알고리즘 첫번쨰 단계(phase 1)
void phase1(int N) {
	int j = 1;
	//전체 vertex에 대한 탐색 우선순위 설정
	vector<pair<int, int>>seq;
	while (j <= N) {
		seq.push_back(pair<int, int>(transGraph[j].size(), j));
		j++;
	}
	sort(seq.begin(), seq.end(), compare);
	j = 0;
	//탐색 우선순위에 따라 DFS수행
	while (j < N) {
		int startVertex = seq[j].second;
		if (visit[startVertex] == 1)
			j++;
		else {
			dfs(startVertex);
		}
	}
}

//두번째 DFS 수행하는 함수. 전치 다이그래프에 대해 DFS를 수행하며 SCC를 찾아 사용자별 그룹 리더를 SCC배열에 저장
void dfs2(int leader, int cur) {

	transVisit[cur] = 1;
	//사용자번호를 인덱스로 갖는 배열에 리더 번호 저장
	SCC[cur] = leader;
	if (transGraph[cur].size() != 0) {
		//현재 vertex에 인접한 vertex들을 리스트에 저장
		vector<pair<int, int>>seq;
		for (int i = 0; i < transGraph[cur].size(); i++) {
			if (transVisit[transGraph[cur][i]] == 1)
				continue;
			seq.push_back(pair<int, int>(transGraph[transGraph[cur][i]].size(), transGraph[cur][i]));
		}
		//비교함수에 따라 리스트 정렬
		sort(seq.begin(), seq.end(), compare);
		//탐색 우선순위에 따라 DFS수행
		for (int i = 0; i < seq.size(); i++) {
			if (transVisit[seq[i].second] == 1)
				continue;
			//재귀함수를 통한 DFS 수행
			dfs2(leader, seq[i].second);
		}
	}
}

//알고리즘 두번째 단계(phase2)
void phase2(int N) {
	int j = 0;
	while (j < N) {
		j++;
		//스택에서 pop하는 순서대로 dfs 수행
		int leader = s.back();
		s.pop_back();
		if (transVisit[leader] == 1) continue;
		//dfs탐색을 시작하는 vertex와 함께 리더 번호도 인자로 전달
		dfs2(leader, leader);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//필요한 변수 초기화
	int N, M, k = 0, u1, u2;
	cin >> N >> M;
	//사용자 팔로우관계를 입력받아 다이그래프 작성
	while (k < M) {
		cin >> u1 >> u2;
		adListGraph[u1].push_back(u2);
		transGraph[u2].push_back(u1);
		k++;
	}
	//알고리즘 단계1 수행
	phase1(N);
	k = 0;
	//스택에 저장된 순서대로 출력
	while (k < N) {
		cout << s[k] << " ";
		k++;
	}
	cout << endl;
	//알고리즘 단계2 수행
	phase2(N);
	k = 1;
	//각 사용자별 그룹 리더 출력
	while (k <= N ) {
		cout << SCC[k] << " ";
		k++;
	}
	cout <<endl;
	return 0;
}