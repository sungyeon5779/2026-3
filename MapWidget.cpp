#pragma once
#include <QMainWindow>
#include "Graph.h"

// 전방 선언(헤더 의존 줄이기)
class MapWidget;
class QComboBox;
class QLabel;
class QListWidget;

// ─────────────────────────────────────────────
//  MainWindow.h : 전체 GUI를 총괄하는 메인 윈도우
// ─────────────────────────────────────────────
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
private slots:
    void onSearch();                 // "최단경로 검색" 버튼 처리
    void onStationClicked(int idx);  // 역 클릭 시 정보 표시
private:
    Graph graph_;            // 데이터: 그래프를 직접 소유
    MapWidget* map_;         // 노선도 위젯
    QComboBox* startBox_;    // 출발역 선택
    QComboBox* endBox_;      // 도착역 선택
    QLabel* infoLabel_;      // 역 정보 표시
    QLabel* result_;         // 검색 결과(시간/역수) 표시
    QListWidget* pathList_;  // 경유역 목록
};
