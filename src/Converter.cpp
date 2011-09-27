#include <Converter.h>
#include <QtCore/QProcess>
#include <QtCore/QSize>
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
    //On définit les valeurs
    _max = max;
    _count = 0;
    _countFinished;
    _dest = dest;
    _list = list;
    //On boucle tant que on a pas dépassé le maximum
    for (int i = 0; i < list.size() && _count < _max ; i++)
    {
        QProcess *process = new QProcess(this);
        QStringList args;
        args << list[i] << "-resize" << QString::number(size.width()) + "x";
        args << dest + "/" + list[i];
        process->start("convert",args);
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
    if (_countFinished == _list.size())
    {
        emit taskCompleted();
    }
}
