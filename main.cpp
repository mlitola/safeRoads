#include <QApplication>
#include <QHBoxLayout>
#include <QDir>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.resize(1280, 720);
    w.setStyleSheet("background-color: black;");
    w.show();

    return app.exec();
}

void quitApp(QGuiApplication app) {
    app.exit();
}
