#pragma once
#include "Graph.h"
#include <QColor>

// ─────────────────────────────────────────────
//  SubwayData.h : 노선 데이터 + 호선별 색상 정의
// ─────────────────────────────────────────────

// 호선 이름에 따라 노선도에 쓸 색상을 반환
inline QColor lineColor(const std::string& line) {
    if (line=="1호선") return QColor(0x00,0x52,0x9F);  // 남색
    if (line=="2호선") return QColor(0x00,0xA8,0x4E);  // 초록
    if (line=="3호선") return QColor(0xEF,0x7C,0x1C);  // 주황
    if (line=="4호선") return QColor(0x00,0xA5,0xDE);  // 하늘
    return QColor(120,120,120);                        // 기본 회색
}

// 그래프에 역(노드)과 구간(간선)을 적재한다.
inline void buildSubway(Graph& g) {
    // addStation(역이름, 호선, x좌표, y좌표)
    g.addStation("시청","1호선",120,140); g.addStation("종각","1호선",220,140);
    g.addStation("종로3가","1호선",320,140); g.addStation("동대문","1호선",430,140);
    g.addStation("신설동","1호선",540,140);
    g.addStation("을지로입구","2호선",220,240); g.addStation("을지로3가","2호선",320,240);
    g.addStation("동대문역사문화공원","2호선",430,250); g.addStation("왕십리","2호선",560,270);
    g.addStation("강남","2호선",430,430); g.addStation("교대","2호선",320,430);
    g.addStation("사당","2호선",210,430);
    g.addStation("충무로","3호선",320,330); g.addStation("고속터미널","3호선",210,350);
    g.addStation("이수","4호선",210,510); g.addStation("동작","4호선",320,510);

    // addEdge(역A, 역B, 소요시간[분]) — 양방향 간선으로 등록됨
    g.addEdge("시청","종각",2); g.addEdge("종각","종로3가",2);          // 1호선
    g.addEdge("종로3가","동대문",3); g.addEdge("동대문","신설동",3);
    g.addEdge("시청","을지로입구",2); g.addEdge("을지로입구","을지로3가",2);  // 2호선
    g.addEdge("을지로3가","동대문역사문화공원",3); g.addEdge("동대문역사문화공원","왕십리",4);
    g.addEdge("왕십리","강남",12); g.addEdge("강남","교대",3); g.addEdge("교대","사당",5);
    g.addEdge("사당","을지로입구",14);
    g.addEdge("종로3가","을지로3가",2); g.addEdge("을지로3가","충무로",2);   // 3호선/환승
    g.addEdge("충무로","동대문역사문화공원",2); g.addEdge("교대","고속터미널",4);
    g.addEdge("고속터미널","충무로",9);
    g.addEdge("사당","이수",2); g.addEdge("이수","동작",2); g.addEdge("동작","고속터미널",4); // 4호선
}
