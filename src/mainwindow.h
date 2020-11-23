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

signals:
    void createMessage(QString);

private slots:
    void on_ButSetPath_clicked();
    void on_ButLoad_clicked();
    void on_loadProgress(int progress);

    void showMessage(QString msg);
    void convertHtml(bool ok);
    void countLoadFinished(bool);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QStringList findLinks(QString strHtml);
    void parsePath();
    bool createPageDirectory();
    bool checkPath();
    QString addLinkedPath();

    Ui::MainWindow *ui;
    QList<Downloader*> MassHtml;
    QDir SavePath;
    QString SaveFileName;
    int CountDownloaded;
    int CountHtml;
};
#endif // MAINWINDOW_H
