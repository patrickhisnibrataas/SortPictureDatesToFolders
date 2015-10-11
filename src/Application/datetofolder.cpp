#include "datetofolder.h"

DateToFolder::DateToFolder()
{

}

DateToFolder::DateToFolder(const QDate &date, const QDir &baseDir)
{
    setDate(date);
    setBaseDir(baseDir);
}

QDate DateToFolder::date() const
{
    return m_date;
}

void DateToFolder::setDate(const QDate &date)
{
    m_date = date;
}

QDir DateToFolder::baseDir() const
{
    return m_baseDir;
}

void DateToFolder::setBaseDir(const QDir &baseDir)
{
    m_baseDir = baseDir;
}

//Creates a folder hierarchy based on the set date.
bool DateToFolder::create()
{
    //Check if date object has valid year, month and day.
    if (!m_date.isValid())
    {
        emit error(DateToFolder::Error::InvalidDateFormat);
        return false;
    }

    //Check if base directory exists.
    if (!m_baseDir.exists())
    {
        emit error(DateToFolder::Error::DirectoryDoesNotExist);
        return false;
    }

    //Set current dir to base directory.
    QDir dir(baseDir());

    //Create year folder.
    auto year = QString::number(date().year());
    dir = createFolder(year, dir);
    if (dir == QDir(""))
    {
        return false;
    }

    //Create month folder.
    auto month = QString::number(date().month());
    dir = createFolder(month, dir);
    if (dir == QDir(""))
    {
        return false;
    }

    //Create day folder.
    auto day = QString::number(date().day());
    dir = createFolder(day, dir);
    if (dir == QDir(""))
    {
        return false;
    }

    return true;
}

//Navigates to the directory 'directory' and returns the directory navigated to.
//If QDir is empty the navigation failed.
QDir DateToFolder::navigateToDirectory(const QDir &directory)
{
    QDir dir;

    //Navigate to directory.
    auto dirString = directory.absolutePath();
    if (!dir.cd(dirString))
    {
        emit error(DateToFolder::Error::CouldNotNavigateToDirectory, dirString);
        dir = QDir("");
    }

    return dir;
}

//Navigates to and creates the folder 'folder' in directory 'directory' and returns the path to the newly created folder.
//If QDir is empty the navigation/creation failed.
QDir DateToFolder::createFolder(const QString &folderName, const QDir &directory)
{
    //Check if folder already exists.
    QDir dir;
    dir.setPath(directory.absolutePath() + "/" + folderName);
    if (dir.exists())
    {
        //Navigate to directory.
        dir = navigateToDirectory(dir);
        if (dir == QDir(""))
        {
            return QDir("");
        }

        return dir;
    }

    //Navigate to directory.
    dir = navigateToDirectory(directory);
    if (dir == QDir(""))
    {
        return QDir("");
    }

    //Create folder.
    if (!dir.mkdir(folderName))
    {
        emit error(DateToFolder::Error::CouldNotCreateDirectory, dir.absoluteFilePath(folderName));
        return QDir("");
    }

    //Set path to newly created folder.
    dir.setPath(dir.absolutePath() + "/" + folderName);

    //Navigate to newly created folder.
    dir = navigateToDirectory(dir);
    if (dir == QDir(""))
    {
        return QDir("");
    }

    return dir;
}
