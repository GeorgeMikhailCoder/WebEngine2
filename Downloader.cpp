#include "Downloader.h"

Downloader::Downloader(QObject* parent):QObject(parent)
{
connect(this,SIGNAL(createMessage(QString)), this->parent(), SLOT(showMessage(QString)));
}

Downloader::Downloader(QString Url, QString fPathName,QObject* parent):Downloader(parent)
{
    loadAndSave(Url, fPathName);
}
Downloader::Downloader(const Downloader& R)
{
    FilePathName=R.FilePathName;
    Page.setUrl(R.Page.url());
}

Downloader::~Downloader()
{

}

Downloader& Downloader::operator=(const Downloader& Right)
{
    FilePathName=Right.FilePathName;
    Page.setUrl(Right.Page.url());
    return *this;
}

void Downloader::loadAndSave(QString Url, QString fPathName)
{
    FilePathName=fPathName;
    Page.setUrl(Url);
    connect(&Page,SIGNAL(loadFinished(bool)),this,SLOT(save(bool)));
    Page.load(Url);
    emit createMessage("Signal sended");
}

void Downloader::save(bool ok)
{
QMessageBox::information(nullptr,"Signal","Accepted\n"+Page.url().toString());
if(ok)
{
    Page.save(FilePathName,QWebEngineDownloadItem::SavePageFormat::CompleteHtmlSaveFormat);
    //this->~MyPage();//возможны проблемы при асинхронном выполнении save от уничтоженного объекта
}
else
emit createMessage("Error loading file\n"+Page.url().toString());
}
