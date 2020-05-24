#include <QtWidgets>
#include <QtConcurrent>
#include "utilityfunctions.h"
#include <string>

QVector<QPair<QString,QString>> readCommandsFromFile(const QString &path, const QString &pattern)
{
    QFile file(path);
    QVector<QPair<QString,QString>> vec;

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString txt{stream.readAll()};
        file.close();

        QRegExp rx(pattern);
        int pos = 0;
        while ((pos = rx.indexIn(txt, pos)) != -1) {
          //   qDebug()<<rx.cap(1)<<" "<<rx.cap(3);
            vec.push_back(QPair<QString,QString>{rx.cap(1),rx.cap(3)});
            pos += rx.matchedLength();
        }
        //qDebug()<<vec.size();

    } else qDebug()<<"Opening error";
    return vec;
}

void findlWork( QTableWidget *tb, const QRegExp &reg, int start, int finish)
{
            for(int i = start; i != finish; ++i)
            {
                QPushButton * item = (QPushButton*) tb -> cellWidget(i, 0);
           //     qDebug()<<item->text();
                if(reg.indexIn(item -> text()) == -1)
                {
                    try
                    {
                       tb->hideRow(i);

                    } catch(...)
                    {
                        qDebug()<<"exception";
                    }
                }

            }
}

bool allRowsShow(QTableWidget *tb)
{

    for(int i = 0;i != tb -> rowCount(); ++i)
    {
        if(tb -> isRowHidden(i))
        {
            return false;
        }

    }
    return true;
}

QStringList picLoad(const QString &path)
{
    QDir dir(path);
    QStringList pics = dir.entryList(QDir::Files | QDir::NoSymLinks);
    qSort(pics.begin(), pics.end(),[](const QString &a, const QString &b){
        return a.mid(0, a.indexOf('.')).toInt() < b.mid(0, b.indexOf('.')).toInt();
    });
    return pics;
}

bool lstrC(LPTSTR str, const char *com)
{
    if(strlen(com) != wcslen(str)) return false;
    bool f = true;
      for(int i = 0;i != wcslen (str); ++i)
      {
        if( char(str[i]) != com[i]) return false;
      }
      return f;
}

bool isDota()
{
    HWND handle = GetForegroundWindow();
    int len = GetWindowTextLength(handle) + 1;
    LPTSTR title = new TCHAR[len];
    GetWindowText(handle, title, len);
    //qDebug()<<wcslen (title);
    return lstrC(title,"Dota 2") || lstrC(title,"untitled6");
}


