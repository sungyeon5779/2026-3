# 지하철 최단경로 탐색 (데이터구조 최종 프로젝트)

서울 지하철 1~4호선 일부를 **가중 그래프**로 모델링하고
**다익스트라 알고리즘**으로 최단경로를 찾아 노선도에 시각화하는 Qt GUI 프로그램.

## 클래스 구조
| 파일 | 역할 |
|------|------|
| Graph.h / Graph.cpp | Graph 클래스 (Station, Edge) — 그래프 자료구조 + 다익스트라 |
| SubwayData.h | buildSubway(), lineColor() — 노선 데이터/색상 |
| MapWidget.h / MapWidget.cpp | MapWidget(QWidget) — 노선도 렌더링/클릭 |
| MainWindow.h / MainWindow.cpp | MainWindow(QMainWindow) — 전체 GUI/이벤트 |
| main.cpp | 진입점 + 다크테마 스타일시트 |

## 클래스 관계
- MainWindow ──소유──> Graph (Station, Edge 포함)
- MainWindow ──소유──> MapWidget ──참조(포인터)──> Graph
- MapWidget.onClick ──연결──> MainWindow::onStationClicked()

## 빌드 방법
- Qt Creator: `CMakeLists.txt` 열기 → Configure → 실행
- qmake: `SubwayShortestPath.pro` 열기 → 빌드

## 핵심 자료구조 / 복잡도
- 인접 리스트 `vector<vector<Edge>>`
- 우선순위 큐 기반 다익스트라 — O((V+E) log V)
