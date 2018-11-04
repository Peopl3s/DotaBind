#ifndef UTILITYFUNCTIONS
#define UTILITYFUNCTIONS
#include <QtWidgets>
#include <thread>
QVector<QPair<QString,QString>> readCommandsFromFile(const QString &, const QString &);

void findlWork( QTableWidget *tb,const QRegExp &reg,int start, int finish);

bool allRowsShow(QTableWidget *tb);

QStringList picLoad(const QString &);

template <typename T>
inline void setQss(T *obj, const QString &qssFile)
{
    QFile file(qssFile);
    if(file.open(QIODevice::ReadOnly))
    {
        QString strCSS = QLatin1String(file.readAll());
        obj->setStyleSheet(strCSS);
        file.close();
    } else qDebug()<<"Opening file error";
}
bool lstrC(LPTSTR str, const char *com);

bool isDota();

template<class Func, class ...Args>
void runEndless(int msec, Func func, Args &&...args)
{
    auto endless = [=](Args &&...args){
        while(true){
            func(std::forward<Args>(args)...);
            std::this_thread::sleep_for(std::chrono::milliseconds(msec));
        }
    };

    std::thread thread(endless, args...);
    thread.detach();
}

#endif // UTILITYFUNCTIONS

