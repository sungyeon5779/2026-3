#include "MainWindow.h"
#include "MapWidget.h"
#include "SubwayData.h"
#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

// ─────────────────────────────────────────────
//  MainWindow.cpp : GUI 배치 + 이벤트 처리 구현
// ─────────────────────────────────────────────

MainWindow::MainWindow() {
    setWindowTitle("지하철 최단경로 탐색");
    resize(1080, 720);
    buildSubway(graph_);   // 그래프에 노선 데이터 적재

    // 중앙 위젯과 좌우 분할 레이아웃
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout* root = new QHBoxLayout(central);
    root->setContentsMargins(16,16,16,16);
    root->setSpacing(16);

    // 왼쪽: 노선도 위젯 (클릭 콜백을 onStationClicked로 연결)
    map_ = new MapWidget(&graph_);
    map_->onClick = [this](int idx){ onStationClicked(idx); };
    root->addWidget(map_, 3);

    // 오른쪽: 카드 형태의 컨트롤 패널
    QFrame* card = new QFrame(); card->setObjectName("card");
    card->setMinimumWidth(300);
    QVBoxLayout* panel = new QVBoxLayout(card);
    panel->setContentsMargins(20,20,20,20);
    panel->setSpacing(10);

    QLabel* title = new QLabel("최단경로 찾기"); title->setObjectName("title");
    QLabel* sub = new QLabel("다익스트라 알고리즘 · 그래프 자료구조"); sub->setObjectName("sub");
    panel->addWidget(title); panel->addWidget(sub);

    // 출발/도착 콤보박스에 전체 역 채우기
    startBox_ = new QComboBox();
    endBox_ = new QComboBox();
    for (int i=0; i<graph_.size(); ++i) {
        QString nm = QString::fromStdString(graph_.station(i).name);
        startBox_->addItem("출발  " + nm); endBox_->addItem("도착  " + nm);
    }
    endBox_->setCurrentIndex(graph_.size()-1);   // 기본 도착역은 마지막 역

    QLabel* l1 = new QLabel("출발역"); l1->setObjectName("section");
    QLabel* l2 = new QLabel("도착역"); l2->setObjectName("section");
    panel->addWidget(l1); panel->addWidget(startBox_);
    panel->addWidget(l2); panel->addWidget(endBox_);

    // 검색 버튼 — clicked 시그널을 onSearch 슬롯에 연결
    QPushButton* searchBtn = new QPushButton("최단경로 검색");
    connect(searchBtn, &QPushButton::clicked, this, &MainWindow::onSearch);
    panel->addSpacing(4); panel->addWidget(searchBtn);

    result_ = new QLabel("출발/도착역을 선택하세요"); result_->setObjectName("result");
    result_->setWordWrap(true);
    panel->addSpacing(6); panel->addWidget(result_);

    QLabel* sInfo = new QLabel("역 정보"); sInfo->setObjectName("section");
    infoLabel_ = new QLabel("지도에서 역을 클릭하면 상세 정보가 표시됩니다.");
    infoLabel_->setObjectName("info"); infoLabel_->setWordWrap(true);
    panel->addWidget(sInfo); panel->addWidget(infoLabel_);

    QLabel* sPath = new QLabel("경유 역"); sPath->setObjectName("section");
    pathList_ = new QListWidget();
    panel->addWidget(sPath); panel->addWidget(pathList_, 1);

    root->addWidget(card, 0);
}

// "최단경로 검색" 버튼을 눌렀을 때
void MainWindow::onSearch() {
    int s = startBox_->currentIndex(), e = endBox_->currentIndex();
    int total = 0;
    std::vector<int> path = graph_.shortestPath(s, e, total);  // 다익스트라 실행
    pathList_->clear();
    if (path.empty()) { result_->setText("연결된 경로가 없습니다."); return; }
    // 경유역 목록을 리스트에 출력
    for (size_t k=0;k<path.size();++k) {
        const Station& st = graph_.station(path[k]);
        QString prefix = (k==0)?"[출발] ":(k==path.size()-1)?"[도착] ":"  - ";
        pathList_->addItem(prefix + QString::fromStdString(st.name+"  ("+st.line+")"));
    }
    map_->setPath(path);   // 노선도에 경로 강조
    result_->setText(QString("총 %1분  ·  %2개 역").arg(total).arg((int)path.size()));
}

// 노선도에서 역을 클릭했을 때 정보 표시
void MainWindow::onStationClicked(int idx) {
    const Station& s = graph_.station(idx);
    int deg = (int)graph_.neighbors(idx).size();  // 인접역 수 = 노드의 차수
    map_->setSelected(idx);
    infoLabel_->setText(QString("역명: %1\n노선: %2\n인접한 역: %3개")
        .arg(QString::fromStdString(s.name))
        .arg(QString::fromStdString(s.line)).arg(deg));
}
