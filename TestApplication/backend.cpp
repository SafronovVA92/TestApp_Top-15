#include "backend.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{

}

BackEnd::~BackEnd()
{

}

void BackEnd::setFileName(const QString& fileName)
{
    QUrl url(fileName);

    if (url.isLocalFile())
        m_fileParser = new TextFileParser(url.toLocalFile());
    else
        m_fileParser = new TextFileParser(fileName);

    StartWorkingThread();
}

void BackEnd::valueReceived(int index, QString wordName, int wordsCount, double value)
{
    emit resultsAreReady(index, wordName, wordsCount, value);
}

void BackEnd::progressUpdated(double progressValue)
{
    emit progressChanged(progressValue);
}

void BackEnd::threadFinished(double parsingTime)
{
    qDebug() << "ThreadFinished";

    delete m_fileParser;

    emit parsingCompleted(parsingTime);
}

void BackEnd::StartWorkingThread()
{
    m_thread = new QThread();

    m_fileParser->moveToThread(m_thread);

    connect(m_fileParser, SIGNAL(sendResults(int,QString,int,double)), this, SLOT(valueReceived(int,QString,int,double)));
    connect(m_fileParser, SIGNAL(updateProgress(double)), this, SLOT(progressUpdated(double)));
    connect(m_fileParser, SIGNAL(parsingFinished(double)), this, SLOT(threadFinished(double)));
    connect(m_thread, SIGNAL(started()), m_fileParser, SLOT(doWork()));
    connect(m_thread, SIGNAL(finished()), m_thread, SLOT(deleteLater()));

    m_thread->start();
}

