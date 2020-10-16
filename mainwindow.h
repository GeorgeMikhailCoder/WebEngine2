#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtWebEngine/QtWebEngine>
#include<QtWebEngineWidgets/QtWebEngineWidgets>
#include<QtWebEngineWidgets/qwebengineview.h>
#include"Downloader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void createMessage(QString);
private slots:
    void on_ButLoad_clicked();
    void convertHtml(bool ok);
    void on_ButSetPath_clicked();
    void showMessage(QString msg);
    void on_loadProgress(int progress);
    void countLoadFinished(bool);

private:
    Ui::MainWindow *ui;
    QList<Downloader*> MassHtml;
    QStringList findLinks(QString strHtml);
    QString defPath();

    int CountDownloaded;
    int CountHtml;
};
#endif // MAINWINDOW_H
