#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("SafeRoads");

    currentIndex = 0;

    url = QUrl("https://www.kelikamerat.info/kelikamerat/Päijät-Häme/Heinola/tie-4/vt4_Heinola");
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

void MainWindow::doImageRequest()
{
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &MainWindow::imageDownloadFinished);
}

void MainWindow::httpFinished()
{
    rawHTML = QString::fromUtf8(reply->readAll());
    parseRawHTML();
}

void MainWindow::parseRawHTML()
{
    /* h4X0red kludge... */
    if (rawHTML.length() > 99000)
    {
        QString parseMore = rawHTML.right(7700).left(1800);
        // QTextStream(stdout) << parseMore << endl;
        currentAirTemp = parseMore.split("<span id=\"air-temp-image\">")[1].left(25).trimmed();
        currentRoadTemp = parseMore.split("<span id=\"road-temp-image\">")[1].left(25).trimmed();
        QString parseImageUrl = "https://www.kelikamerat.info" + parseMore.split("src=\"")[1].split("\"")[0];
        url = QUrl(parseImageUrl);
        doImageRequest();
    }
}

void MainWindow::imageDownloadFinished()
{
    loadImage = QImage::fromData(reply->readAll(), "JPG");
    refreshGUI();
}

void MainWindow::refreshGUI()
{
    if (!loadImage.isNull())
    {
        resizedImage = loadImage.scaled(640, 360, Qt::KeepAspectRatio);
        QPixmap qpm = QPixmap::fromImage(resizedImage);
        QGraphicsScene *scene = new QGraphicsScene();
        scene->addPixmap(qpm);

        if (currentIndex == 0)
        {
            ui->topLeftGraphicsView->setScene(scene);
            ui->topLeftAirTemp->setText("Air temp:" + currentAirTemp + " C");
            ui->topLeftRoadTemp->setText("Road temp:" + currentRoadTemp + " C");
            url = QUrl("https://www.kelikamerat.info/kelikamerat/Pirkanmaa/Kangasala/tie-9/vt9_Suinula");
        }
        if (currentIndex == 1)
        {
            ui->lowLeftGraphicsView->setScene(scene);
            ui->lowLeftAirTemp->setText("Air temp:" + currentAirTemp + " C");
            ui->lowLeftRoadTemp->setText("Road temp:" + currentRoadTemp + " C");
            url = QUrl("https://www.kelikamerat.info/kelikamerat/Keski-Suomi/Viitasaari/tie-4/vt4_Viitasaari_Taimoniemi");
        }
        if (currentIndex == 2)
        {
            ui->topRightGraphicsView->setScene(scene);
            ui->topRightAirTemp->setText("Air temp:" + currentAirTemp + " C");
            ui->topRightRoadTemp->setText("Road temp:" + currentRoadTemp + " C");
            url = QUrl("https://www.kelikamerat.info/kelikamerat/Pohjois-Pohjanmaa/Kärsämäki/tie-4/vt4_Kärsämäki");
        }
        if (currentIndex == 3)
        {
            ui->lowRightGraphicsView->setScene(scene);
            ui->lowRightAirTemp->setText("Air temp:" + currentAirTemp + " C");
            ui->lowRightRoadTemp->setText("Road temp:" + currentRoadTemp + " C");
        }
    }

    currentIndex++;
    doRequest();
}
