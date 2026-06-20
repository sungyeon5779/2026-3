#include <QApplication>
#include "MainWindow.h"

// ─────────────────────────────────────────────
//  main.cpp : 프로그램 진입점 + 다크 테마(QSS) 적용
// ─────────────────────────────────────────────
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    // 전체 위젯에 적용되는 스타일시트(다크 테마, 둥근 모서리, hover 효과 등)
    app.setStyleSheet(R"(
        QMainWindow, QWidget { background:#141C28; color:#E6ECF3; font-family:'Malgun Gothic'; }
        QLabel#title { font-size:20px; font-weight:bold; color:#FFFFFF; }
        QLabel#sub { color:#8A97A8; font-size:12px; }
        QLabel#section { color:#5FB0FF; font-size:12px; font-weight:bold; padding-top:6px; }
        QComboBox { background:#1F2A38; border:1px solid #2E3C4E; border-radius:8px;
                    padding:8px 12px; font-size:14px; color:#E6ECF3; }
        QComboBox:hover { border:1px solid #5FB0FF; }
        QComboBox QAbstractItemView { background:#1F2A38; selection-background-color:#2D7DD2; color:#E6ECF3; }
        QPushButton { background:#2D7DD2; border:none; border-radius:10px;
                      padding:12px; font-size:15px; font-weight:bold; color:white; }
        QPushButton:hover { background:#3A8DE8; }
        QPushButton:pressed { background:#2468B0; }
        QListWidget { background:#1A2330; border:1px solid #2E3C4E; border-radius:8px;
                      padding:4px; font-size:13px; }
        QListWidget::item { padding:6px 8px; border-radius:6px; }
        QListWidget::item:selected { background:#2D7DD2; }
        QFrame#card { background:#1A2330; border:1px solid #2A3645; border-radius:12px; }
        QLabel#info { background:#10171F; border:1px solid #2A3645; border-radius:8px;
                      padding:12px; font-size:13px; color:#C8D4E0; }
        QLabel#result { font-size:16px; font-weight:bold; color:#FFD24B; }
    )");
    MainWindow w;   // 메인 윈도우 생성
    w.show();       // 화면에 표시
    return app.exec();  // 이벤트 루프 시작
}
