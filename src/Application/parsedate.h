#ifndef PARSEDATE_H
#define PARSEDATE_H

#include <QObject>
#include <QDate>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
#include <QStringList>
#include <QTime>

class ParseDate : public QObject
{
    Q_OBJECT
public:
    enum class Error
    {
        FileNameEmpty
    };
    Q_ENUM(Error)


    ParseDate();
    ParseDate(const QFile& file);
    void setFile(const QFile& file);
    bool parse();
    QDateTime dateTime() const;

private:
    QString m_fileName;
    QDateTime m_dateTime;
    bool m_status;

signals:
    void error(ParseDate::Error error, QString errorText = QString(""));
};

#endif // PARSEDATE_H
