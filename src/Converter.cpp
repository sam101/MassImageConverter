#include <Converter.h>
#include <QtCore/QProcess>
#include <QtCore/QSize>
#include <QDebug>
/**
  * Constructeur
  */
Converter::Converter() :
_count(0),
_max(0)
{

}
/**
  * Lance la conversion d'images
  */
void Converter::start(QStringList list, QSize size, int max, QString dest)
{
    //On inscrit les nouvelles valeurs dans les attributs.
    _size = size;
    _max = max;
    _count = 0;
    _countFinished = 0 ;
    _dest = dest;
    _list = list;
    //On boucle tant que on a pas dépassé le maximum
    for (int i = 0; i < list.size() && _count < _max ; i++)
    {
        launchProcess(_list[i],size);
        _count++;
    }
}
/**
  * Appelé à la fin de conversion d'une image
  */
void Converter::convertFinished()
{
    _countFinished++;
    emit imageHasFinished(_countFinished);
    if (_count < _list.size())
    {
        launchProcess(_list[_count],_size);
        _count++;
    }
    if (_countFinished == _list.size())
    {
        emit taskCompleted();
    }
}
/**
  * Lance un processus fils qui doit convertir une image
  */
void Converter::launchProcess(QString pathToImage, QSize size)
{
    QProcess *process = new QProcess(this);
    QStringList args;
    args << pathToImage << "-resize" << QString::number(size.width()) + "x";
    args << _dest + "/" + pathToImage;
    process->start("convert",args);
    connect(process,SIGNAL(finished(int)),this,SLOT(convertFinished()));

}