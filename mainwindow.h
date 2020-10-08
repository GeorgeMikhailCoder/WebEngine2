#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtWebEngine/QtWebEngine>
#include<QtWebEngineWidgets/QtWebEngineWidgets>
#include<QtWebEngineWidgets/qwebengineview.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ButLoad_clicked();
    void ConvertHtml(bool ok);
    void SaveHtml(bool);
    void on_ButSetPath_clicked();


private:
    Ui::MainWindow *ui;
    QStringList findLinks(QString strHtml);

    QWebEnginePage *Pages;
};
#endif // MAINWINDOW_H
