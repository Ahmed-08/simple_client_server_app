#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(300, 300);
    this->udpSocket = new QUdpSocket(this);
    this->udpSocket->bind(QHostAddress::LocalHost, 1111);
    connect(this->udpSocket, SIGNAL(readyRead()), this, SLOT(ReadingData()));

    this->setWindowTitle("client 1");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReadingData()
{
    QHostAddress sender;
    quint16 senderPort;

    while(this->udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(this->udpSocket->pendingDatagramSize());
        this->udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        ui->textEdit->append("<font color=red>" + QString(datagram) + "</font>");
        ui->textEdit->setAlignment(Qt::AlignRight);
    }
}

void MainWindow::on_pushButton_clicked()
{
    this->udpSocket->writeDatagram(ui->lineEdit_2->text().toUtf8(), QHostAddress::LocalHost, 9999);
    ui->textEdit->append("You: <font color=cyan>" + ui->lineEdit_2->text() + "</font>");
    ui->textEdit->setAlignment(Qt::AlignLeft);
    ui->lineEdit_2->clear();
}

