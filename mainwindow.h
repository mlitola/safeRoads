#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QUrl>


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
    void httpFinished();
    void doRequest();
    void refreshGUI();
    void refreshGUIValues();

private:
    Ui::MainWindow *ui;
    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QImage loadImage;
    QImage resizedImage;
};

#endif // MAINWINDOW_H
