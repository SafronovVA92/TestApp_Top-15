#ifndef TEXTFILEPARSER_H
#define TEXTFILEPARSER_H

#include <QtCore>

#define FILE_CHUNK_SIZE     (2 * 1024 * 1024)
#define RESULT_SIZE         (15)
#define REFRESH_TIME        (1000)

#define ENABLE_REFRESH_RATE


class TextFileParser : public QObject
{
    Q_OBJECT

public:
    TextFileParser(QString fileName);
    ~TextFileParser();

public slots:
    void doWork();

signals:
    void sendResults(int index, QString wordName, int wordsCount, double value);
    void updateProgress(double);
    void parsingFinished(double);

private:
    void ReadTextFile();
    void CollectWords(QString& readedString);
    void PrepareChart(bool isLastRefresh);

    QString m_fileName;
    QHash<QString, int> m_wordsCount;

    qint64 m_initialTime;
    qint64 m_timePrevValue = 0;
};

#endif // TEXTFILEPARSER_H
