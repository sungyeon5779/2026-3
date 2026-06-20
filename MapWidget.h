#include "MapWidget.h"
#include "SubwayData.h"
#include <QPainter>
#include <QMouseEvent>
#include <QLinearGradient>
#include <QSet>
#include <QFont>

// ─────────────────────────────────────────────
//  MapWidget.cpp : 노선도 렌더링 + 클릭 처리 구현
// ─────────────────────────────────────────────

MapWidget::MapWidget(Graph* g, QWidget* parent) : QWidget(parent), g_(g) {
    setMinimumSize(680,640);   // 최소 크기 지정
}
void MapWidget::setPath(const std::vector<int>& p) { path_ = p; update(); }  // 경로 갱신 후 다시 그림
void MapWidget::setSelected(int idx) { selected_ = idx; update(); }          // 선택 갱신 후 다시 그림

// 위젯이 다시 그려질 때마다 호출되는 함수
void MapWidget::paintEvent(QPaintEvent*) {
    QPainter qp(this); qp.setRenderHint(QPainter::Antialiasing);  // 부드럽게(안티앨리어싱)

    // 1) 배경 그라데이션
    QLinearGradient bg(0,0,0,height());
    bg.setColorAt(0, QColor(0x1B,0x26,0x35));
    bg.setColorAt(1, QColor(0x0F,0x16,0x20));
    qp.fillRect(rect(), bg);

    QSet<int> inPath(path_.begin(), path_.end());  // 경로에 포함된 역 빠른 확인용

    // 2) 일반 간선(구간) 그리기 — 호선 색을 반투명하게
    QSet<QPair<int,int>> drawn;   // 무방향이라 같은 간선 두 번 안 그리도록 기록
    for (int u=0; u<g_->size(); ++u) {
        const Station& su = g_->station(u);
        for (const Edge& e : g_->neighbors(u)) {
            int v = e.to;
            if (drawn.contains({v,u})) continue;  // 이미 반대방향으로 그렸으면 skip
            drawn.insert({u,v});
            const Station& sv = g_->station(v);
            QColor c = lineColor(su.line); c.setAlpha(110);
            qp.setPen(QPen(c, 5, Qt::SolidLine, Qt::RoundCap));
            qp.drawLine(su.x,su.y,sv.x,sv.y);
        }
    }

    // 3) 최단경로 강조 — 노란색 글로우(굵은 반투명 + 선명한 선)
    for (size_t i=1; i<path_.size(); ++i) {
        const Station& a = g_->station(path_[i-1]);
        const Station& b = g_->station(path_[i]);
        qp.setPen(QPen(QColor(255,210,60,90), 14, Qt::SolidLine, Qt::RoundCap));
        qp.drawLine(a.x,a.y,b.x,b.y);
        qp.setPen(QPen(QColor(255,205,40), 6, Qt::SolidLine, Qt::RoundCap));
        qp.drawLine(a.x,a.y,b.x,b.y);
    }

    // 4) 노드(역) 그리기 — 역 원 + 이름
    for (int i=0; i<g_->size(); ++i) {
        const Station& s = g_->station(i);
        bool on = inPath.contains(i);     // 경로에 포함된 역인지
        int r = on ? 11 : 8;              // 경로 역은 더 크게
        if (i==selected_) {               // 선택된 역은 흰색 링 표시
            qp.setBrush(Qt::NoBrush);
            qp.setPen(QPen(QColor(255,255,255,160), 2));
            qp.drawEllipse(QPoint(s.x,s.y), r+6, r+6);
        }
        qp.setPen(QPen(Qt::white, on?3:2));
        qp.setBrush(on ? QColor(255,205,40) : lineColor(s.line));  // 경로 역은 노랑
        qp.drawEllipse(QPoint(s.x,s.y), r, r);
        QFont f = qp.font(); f.setPointSize(9); f.setBold(on);
        qp.setFont(f);
        qp.setPen(on ? QColor(255,230,150) : QColor(220,228,238));
        qp.drawText(s.x+14, s.y+5, QString::fromStdString(s.name));  // 역 이름 표시
    }

    // 5) 좌측 상단 범례(호선 색상 안내)
    QFont lf = qp.font(); lf.setPointSize(9); lf.setBold(false); qp.setFont(lf);
    const char* lines[4] = {"1호선","2호선","3호선","4호선"};
    for (int i=0;i<4;++i){
        int ly = 24 + i*22;
        qp.setBrush(lineColor(lines[i])); qp.setPen(Qt::NoPen);
        qp.drawEllipse(QPoint(24, ly), 6,6);
        qp.setPen(QColor(200,210,220));
        qp.drawText(38, ly+5, lines[i]);
    }
}

// 마우스를 클릭하면 어떤 역을 눌렀는지 검사
void MapWidget::mousePressEvent(QMouseEvent* ev) {
    for (int i=0; i<g_->size(); ++i) {
        const Station& s = g_->station(i);
        int dx=ev->pos().x()-s.x, dy=ev->pos().y()-s.y;
        if (dx*dx+dy*dy <= 196) {        // 역 중심에서 반경 14px 안이면 클릭으로 인정
            if(onClick) onClick(i);      // 콜백 호출(=MainWindow로 알림)
            return;
        }
    }
}
