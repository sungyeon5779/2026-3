#pragma once
#include <QWidget>
#include <vector>
#include <functional>
#include "Graph.h"

// ─────────────────────────────────────────────
//  MapWidget.h : 노선도를 그리고 클릭을 받는 커스텀 위젯
// ─────────────────────────────────────────────
class MapWidget : public QWidget {
    Q_OBJECT
public:
    explicit MapWidget(Graph* g, QWidget* parent=nullptr);  // 그래프 포인터를 받아 보관
    void setPath(const std::vector<int>& p);   // 강조할 최단경로 설정
    void setSelected(int idx);                 // 클릭 선택된 역 설정
    std::function<void(int)> onClick;          // 역 클릭 시 호출될 콜백

protected:
    void paintEvent(QPaintEvent*) override;          // 화면 그리기
    void mousePressEvent(QMouseEvent* ev) override;  // 마우스 클릭 처리

private:
    Graph* g_;                  // 데이터(그래프) 참조
    std::vector<int> path_;     // 현재 강조 중인 경로
    int selected_ = -1;         // 현재 선택된 역(없으면 -1)
};
