#ifndef DATETOFOLDER_H
#define DATETOFOLDER_H

#include <QObject>
#include <QDate>
#include <QDir>
#include <QString>

class DateToFolder : public QObject
{
    Q_OBJECT
public:
    enum class Error
    {
        DirectoryDoesNotExist,
        InvalidDateFormat,
        CouldNotNavigateToDirectory,
        CouldNotCreateDirectory
    };
    Q_ENUM(Error)

    DateToFolder();
    DateToFolder(const QDate& date, const QDir& baseDir);
    QDate date() const;
    void setDate(const QDate &date);
    QDir baseDir() const;
    void setBaseDir(const QDir &baseDir);
    QDir create();

private:
    QDate m_date;
    QDir m_baseDir;
    QDir m_dir;

    QDir navigateToDirectory(const QDir &directory);
    QDir createFolder(const QString& folderName, const QDir &directory);

signals:
    void error (DateToFolder::Error error, QString errorText = QString(""));
};

#endif // DATETOFOLDER_H
