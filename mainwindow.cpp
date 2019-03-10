#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("SafeRoads");

    //target url
    url = QUrl("https://www.kelikamerat.info/sites/default/files/infotripla/2019_03_10/09_40/C0450401_3789688052.jpg");

    doRequest();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::doRequest()
{
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &MainWindow::httpFinished);

}

void MainWindow::refreshGUI()
{
    if (!loadImage.isNull())
    {
        resizedImage = loadImage.scaled(640, 360, Qt::KeepAspectRatio);
        QPixmap qpm = QPixmap::fromImage(resizedImage);
        QGraphicsScene *scene = new QGraphicsScene();
        scene->addPixmap(qpm);
        ui->topLeftGraphicsView->setScene(scene);
        ui->lowLeftGraphicsView->setScene(scene);
        ui->topRightGraphicsView->setScene(scene);
        ui->lowRightGraphicsView->setScene(scene);
    }
}

void MainWindow::refreshGUIValues()
{
    refreshGUI();
}

void MainWindow::httpFinished()
{
    loadImage = QImage::fromData(reply->readAll(), "JPG");
    refreshGUIValues();
    reply = nullptr;
}
