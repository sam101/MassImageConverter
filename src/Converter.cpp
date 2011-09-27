/*
 * Copyright (C) 2011 Samuel L, MassImageConverter - http://github.com/sam101
 *
 * MassImageConverter is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MassImageConverter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <Converter.h>
#include <QtCore/QDir>
#include <QtCore/QProcess>
#include <QtCore/QSize>
#include <QDebug>
/**
  * Constructeur
  */
Converter::Converter(QObject *parent) :
QObject(parent),
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
    //On construit le process
    QProcess *process = new QProcess(this);
    //On commence à construire les arguments
    QStringList args;
    args << pathToImage << "-resize" << QString::number(size.width()) + "x";
    QString finalPath;
    //Chemin vers le dossier dans lequel se trouve l'image
    QString dir;
    QStringList imagePath = pathToImage.split('/');

    //TODO: Ceci est crade.
    for (int i = 0; i < imagePath.size(); i++)
    {
        if ( i == imagePath.size() - 1)
        {
            finalPath += _dest + "/" + imagePath[i];
        }
        else
        {
            dir += imagePath[i] + "/";
            finalPath += imagePath[i] + "/" ;
        }
    }
    //On finit de remplir le chemin vers le dossier
    dir += _dest;
    //On crée le dossier "TN"
    QDir dirMaker;
    dirMaker.mkdir(dir);
    //On finit de remplir les arguments
    args << finalPath;
    //On lance le processus
    process->start("convert",args);
    //On connecte au slot.
    connect(process,SIGNAL(finished(int)),this,SLOT(convertFinished()));

}
