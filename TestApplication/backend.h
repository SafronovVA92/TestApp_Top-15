#ifndef BACKEND_H
#define BACKEND_H

#include <QtCore>
#include <textfileparser.h>

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName WRITE setFileName NOTIFY resultsAreReady)

public:
    explicit BackEnd(QObject *parent = nullptr);
    ~BackEnd();

    void setFileName(const QString& fileName);

signals:
    void resultsAreReady(int index, QString wordName, int wordsCount, double value);
    void progressChanged(double progress);
    void parsingCompleted(double parsingTime);

private slots:
    void valueReceived(int index, QString wordName, int wordsCount, double value);
    void progressUpdated(double progressValue);
    void threadFinished(double parsingTime);

private:
    void StartWorkingThread();

    QThread *m_thread;
    TextFileParser *m_fileParser;
};

#endif // BACKEND_H
