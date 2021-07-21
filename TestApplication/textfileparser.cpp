#include "textfileparser.h"

TextFileParser::TextFileParser(QString fileName)
{
    m_fileName = fileName;
}

TextFileParser::~TextFileParser()
{

}

void TextFileParser::doWork()
{
    qDebug() << "doWork()";

    ReadTextFile();
    emit parsingFinished((QDateTime::currentMSecsSinceEpoch() - m_initialTime) / 1000.0);
}

void TextFileParser::ReadTextFile()
{
    QFile file(m_fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open failed";
        return;
    }

    m_initialTime = QDateTime::currentMSecsSinceEpoch();

    QTextStream in(&file);
    in.setCodec("UTF-8");

    QString residue;

    while (!in.atEnd())
    {
        QString line;
        QString chunk = in.read(FILE_CHUNK_SIZE);

        qint32 spaceIdx = chunk.lastIndexOf(' ');

        if (spaceIdx != -1)
        {
            line.append(residue);
            line.append(chunk.leftRef(spaceIdx));
            residue = chunk.right(chunk.length() - spaceIdx);
        }
        else
        {
            residue.append(chunk);
        }

        emit updateProgress(file.pos() / (double)file.size());

        CollectWords(line);
    }

    if (residue.length() > 0)
    {
        CollectWords(residue);
    }

    file.close();

    PrepareChart(true);
}

void TextFileParser::CollectWords(QString& readedString)
{
    auto words = readedString.split(QRegExp("\\W+"), QString::SkipEmptyParts);

    for (auto &word : words)
    {
        m_wordsCount[word]++;
    }

    PrepareChart(false);
}

void TextFileParser::PrepareChart(bool isLastRefresh)
{
    qDebug() << (QDateTime::currentMSecsSinceEpoch() - m_initialTime);

#ifdef ENABLE_REFRESH_RATE
    if (isLastRefresh == false)
    {
        if ((QDateTime::currentMSecsSinceEpoch() - m_timePrevValue) < REFRESH_TIME)
            return;
        m_timePrevValue = QDateTime::currentMSecsSinceEpoch();
    }
#endif

    QVector<QPair<QString, int>> sortedWords;
    sortedWords.reserve(m_wordsCount.count());

    auto i = m_wordsCount.constBegin();
    while (i != m_wordsCount.constEnd())
    {
        sortedWords.push_back(QPair<QString, int>(i.key(), i.value()));
        i++;
    }

    std::sort(std::begin(sortedWords), std::end(sortedWords),
              [](const QPair<QString, int> &a, const QPair<QString, int>& b)
    {
        return a.second >  b.second;
    });

    int resultLength = ( sortedWords.size() >= RESULT_SIZE ) ? RESULT_SIZE : sortedWords.size();

    if (resultLength > 0)
    {
        int firstColumnValue = sortedWords[0].second;

        for (int w = 0; w < resultLength; w++)
        {
            emit sendResults(w, sortedWords[w].first, sortedWords[w].second, sortedWords[w].second / (double)firstColumnValue);
        }
    }
}
