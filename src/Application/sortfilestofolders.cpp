#include "sortfilestofolders.h"

SortFilesToFolders::SortFilesToFolders()
{
    m_fileHelper = QSharedPointer<FileHelper>(new FileHelper);
    m_dateToFolder = QSharedPointer<DateToFolder>(new DateToFolder);
    m_parseDate = QSharedPointer<ParseDate>(new ParseDate);

    connect(m_fileHelper.data(), &FileHelper::error, this, onFileHelperError);
    connect(m_dateToFolder.data(), &DateToFolder::error, this, onDateToFolderError);
    connect(m_parseDate.data(), &ParseDate::error, this, onParseDateError);
}

quint32 SortFilesToFolders::sort(QDir from, QDir to)
{
    quint32 copy = 0;
    //Get a string list of all file names in a specific folder.
    auto files = m_fileHelper->filesInDir(from);

    //Parse all file names and create folders.
    m_dateToFolder->setBaseDir(to);

    for (auto file : files)
    {
        //Set file to parse.
        m_parseDate->setFile(QFile(file));

        //Parse file name.
        if (!m_parseDate->parse())
        {
            qDebug() << "Could not parse";
            continue;
        }

        //Get parsed date object.
        auto date = m_parseDate->dateTime().date();

        //Set date and create corresponding folder.
        m_dateToFolder->setDate(date);
        auto dir = m_dateToFolder->create();
        if (dir == QDir(""))
        {
            qDebug() << "Could not create";
            continue;
        }

        QString fromString = from.absoluteFilePath(file);
        QString toString = dir.absoluteFilePath(file);
        QFile from(fromString);
        QFile to(toString);
        m_fileHelper->copy(from, to);

        copy++;
    }

    return copy;
}

void SortFilesToFolders::onFileHelperError(FileHelper::Error error, QString errorText)
{
    qDebug() << EnumHelper<FileHelper::Error>::toString(error) + ": " + errorText;
}

void SortFilesToFolders::onDateToFolderError(DateToFolder::Error error, QString errorText)
{
    qDebug() << EnumHelper<DateToFolder::Error>::toString(error) + ": " + errorText;
}

void SortFilesToFolders::onParseDateError(ParseDate::Error error, QString errorText)
{
    qDebug() << EnumHelper<ParseDate::Error>::toString(error) + ": " + errorText;
}
