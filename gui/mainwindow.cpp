#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startScanButton_clicked()
{
    // 清空日志
    ui->log->clear();

    // 获取IP地址
    char ip_address[16];
    char buffer[200], temp[200];
    int ipNum[4];
    ipNum[0] = ui->ipNum1->value();
    ipNum[1] = ui->ipNum2->value();
    ipNum[2] = ui->ipNum3->value();
    ipNum[3] = ui->ipNum4->value();
    sprintf(ip_address, "%d.%d.%d.%d", ipNum[0], ipNum[1], ipNum[2], ipNum[3]);

    strcpy(buffer, "IP address set: ");
    strcat(buffer, ip_address);
    ui->log->appendPlainText(buffer);

    // 获取线程数
    int threadNum = ui->threadNum->value();
    strcpy(buffer, "Thread num set: ");
    sprintf(temp, "%d", threadNum);
    strcat(buffer, temp);
    ui->log->appendPlainText(buffer);

    // 获取端口范围
    int portStart, portEnd;
    portStart = ui->startPortNum->value();
    portEnd = ui->endPortNum->value();
    strcpy(buffer, "Port set: ");
    sprintf(temp, "%d - %d", portStart, portEnd);
    strcat(buffer, temp);
    ui->log->appendPlainText(buffer);

    // 开始线程操作
    // TODO
}
