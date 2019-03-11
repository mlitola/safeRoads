#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QUrl>

#include <QTextStream>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void doRequest();
    void doImageRequest();
    void httpFinished();
    void parseRawHTML();
    void imageDownloadFinished();
    void refreshGUI();

private:
    Ui::MainWindow *ui;
    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QString rawHTML;
    QImage loadImage;
    QImage resizedImage;
    QString currentAirTemp;
    QString currentRoadTemp;
    int currentIndex;
};

#endif // MAINWINDOW_H
