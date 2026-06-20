#include "Graph.h"
#include <queue>
#include <limits>
#include <algorithm>

// ─────────────────────────────────────────────
//  Graph.cpp : 그래프 자료구조의 실제 동작 구현부
// ─────────────────────────────────────────────

// 역(노드)을 그래프에 추가한다.
int Graph::addStation(const std::string& name, const std::string& line, int x, int y) {
    auto it = nameToIdx_.find(name);
    if (it != nameToIdx_.end()) return it->second;  // 이미 존재하면 그 인덱스 재사용
    int idx = (int)stations_.size();                // 새 인덱스는 현재 크기
    stations_.push_back({name, line, x, y});        // 노드 정보 저장
    adj_.emplace_back();                            // 이 노드의 빈 인접 리스트 생성
    nameToIdx_[name] = idx;                         // 이름->인덱스 매핑 등록
    return idx;
}

// 인덱스 기반 간선 추가 — 무방향이므로 양쪽 모두 등록
void Graph::addEdge(int u, int v, int weight) {
    adj_[u].push_back({v, weight});   // u -> v
    adj_[v].push_back({u, weight});   // v -> u (양방향)
}

// 이름 기반 간선 추가 — 이름을 인덱스로 바꿔서 위 함수 호출
void Graph::addEdge(const std::string& a, const std::string& b, int weight) {
    addEdge(findIndex(a), findIndex(b), weight);
}

// 역 이름으로 인덱스를 찾는다. 없으면 -1.
int Graph::findIndex(const std::string& name) const {
    auto it = nameToIdx_.find(name);
    return it == nameToIdx_.end() ? -1 : it->second;
}

// 다익스트라 알고리즘으로 최단(최소 소요시간) 경로를 구한다.
std::vector<int> Graph::shortestPath(int start, int end, int& totalTime) const {
    const int INF = std::numeric_limits<int>::max();  // 도달 불가 표시값
    int n = size();
    std::vector<int> dist(n, INF);   // dist[i] = start에서 i까지 현재까지의 최단시간
    std::vector<int> prev(n, -1);    // prev[i] = 최단경로에서 i의 직전 역(경로 복원용)

    // (거리, 노드) 쌍을 거리가 작은 순으로 꺼내는 최소 힙
    using P = std::pair<int,int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;

    dist[start] = 0;          // 시작역까지 거리는 0
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();  // 가장 가까운 미확정 노드 꺼냄
        if (d > dist[u]) continue;         // 이미 더 짧은 경로로 확정된 노드면 무시
        if (u == end) break;               // 도착역 확정되면 조기 종료
        for (const Edge& e : neighbors(u)) {   // 인접한 모든 역 검사
            int nd = d + e.weight;             // u 거쳐서 e.to로 가는 새 거리
            if (nd < dist[e.to]) {             // 더 짧으면 갱신(완화, relaxation)
                dist[e.to] = nd;
                prev[e.to] = u;                // 직전 역 기록
                pq.push({nd, e.to});
            }
        }
    }

    // prev[] 배열을 따라 end -> start 로 역추적한 뒤 뒤집어 경로 복원
    std::vector<int> path;
    if (dist[end] == INF) { totalTime = -1; return path; }  // 경로 없음
    for (int cur = end; cur != -1; cur = prev[cur]) path.push_back(cur);
    std::reverse(path.begin(), path.end());
    totalTime = dist[end];   // 총 소요시간
    return path;
}
