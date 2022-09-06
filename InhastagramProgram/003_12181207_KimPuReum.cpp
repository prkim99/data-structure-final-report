#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
//��������Ʈ�� Ȱ���� ����׷���
vector<int> adListGraph[50002];
//��������Ʈ�� Ȱ���� ����׷����� ��ġ
vector<int> transGraph[50002];
//�湮�� vertex���� ����
bool visit[50002];
//��ġ �׷����� �湮�� vertex���� ����
bool transVisit[50002];
//SCC�� ã�� ����ں� �׷� ���� ���� ����
int SCC[50002];
//phase1�� ���� �� ������� ������ ����
vector<int> s;

//DFS����� Ž�� �켱������ �����ϴ� �� �Լ�
bool compare(pair<int, int> a, pair<int, int>b) {
	if (a.first == b.first) {
		return a.second < b.second;
	}
	else {
		return a.first > b.first;
	}
}

//ù��° DFS�� �����ϴ� �Լ�
void dfs(int cur) {
	visit[cur] = 1;
	if (adListGraph[cur].size() != 0) {
		//���� vertex�� ������ vertex���� ����Ʈ�� ����
		vector<pair<int,int>>seq;
		for (int i = 0; i < adListGraph[cur].size(); i++) {
			if (visit[adListGraph[cur][i]] == 1)
				continue;
			seq.push_back(pair<int, int>(transGraph[adListGraph[cur][i]].size(), adListGraph[cur][i]));
		}
		//���Լ��� ���� ����Ʈ ����
		sort(seq.begin(), seq.end(), compare);
		//������ vertex ����Ʈ���� ���� ������� ������ vertex �湮
		for (int i = 0; i < seq.size(); i++) {
			if (visit[seq[i].second] == 1)
				continue;
			//����Լ��� ���� DFS ����
			dfs(seq[i].second);
		}
	}
	//Ž���Ϸ��� vertex ���ÿ� ����
	s.push_back(cur);
}

//�˰��� ù���� �ܰ�(phase 1)
void phase1(int N) {
	int j = 1;
	//��ü vertex�� ���� Ž�� �켱���� ����
	vector<pair<int, int>>seq;
	while (j <= N) {
		seq.push_back(pair<int, int>(transGraph[j].size(), j));
		j++;
	}
	sort(seq.begin(), seq.end(), compare);
	j = 0;
	//Ž�� �켱������ ���� DFS����
	while (j < N) {
		int startVertex = seq[j].second;
		if (visit[startVertex] == 1)
			j++;
		else {
			dfs(startVertex);
		}
	}
}

//�ι�° DFS �����ϴ� �Լ�. ��ġ ���̱׷����� ���� DFS�� �����ϸ� SCC�� ã�� ����ں� �׷� ������ SCC�迭�� ����
void dfs2(int leader, int cur) {

	transVisit[cur] = 1;
	//����ڹ�ȣ�� �ε����� ���� �迭�� ���� ��ȣ ����
	SCC[cur] = leader;
	if (transGraph[cur].size() != 0) {
		//���� vertex�� ������ vertex���� ����Ʈ�� ����
		vector<pair<int, int>>seq;
		for (int i = 0; i < transGraph[cur].size(); i++) {
			if (transVisit[transGraph[cur][i]] == 1)
				continue;
			seq.push_back(pair<int, int>(transGraph[transGraph[cur][i]].size(), transGraph[cur][i]));
		}
		//���Լ��� ���� ����Ʈ ����
		sort(seq.begin(), seq.end(), compare);
		//Ž�� �켱������ ���� DFS����
		for (int i = 0; i < seq.size(); i++) {
			if (transVisit[seq[i].second] == 1)
				continue;
			//����Լ��� ���� DFS ����
			dfs2(leader, seq[i].second);
		}
	}
}

//�˰��� �ι�° �ܰ�(phase2)
void phase2(int N) {
	int j = 0;
	while (j < N) {
		j++;
		//���ÿ��� pop�ϴ� ������� dfs ����
		int leader = s.back();
		s.pop_back();
		if (transVisit[leader] == 1) continue;
		//dfsŽ���� �����ϴ� vertex�� �Բ� ���� ��ȣ�� ���ڷ� ����
		dfs2(leader, leader);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//�ʿ��� ���� �ʱ�ȭ
	int N, M, k = 0, u1, u2;
	cin >> N >> M;
	//����� �ȷο���踦 �Է¹޾� ���̱׷��� �ۼ�
	while (k < M) {
		cin >> u1 >> u2;
		adListGraph[u1].push_back(u2);
		transGraph[u2].push_back(u1);
		k++;
	}
	//�˰��� �ܰ�1 ����
	phase1(N);
	k = 0;
	//���ÿ� ����� ������� ���
	while (k < N) {
		cout << s[k] << " ";
		k++;
	}
	cout << endl;
	//�˰��� �ܰ�2 ����
	phase2(N);
	k = 1;
	//�� ����ں� �׷� ���� ���
	while (k <= N ) {
		cout << SCC[k] << " ";
		k++;
	}
	cout <<endl;
	return 0;
}