#ifndef CONVERTER_H
#define CONVERTER_H
#include <Config.h>
#include <QtCore/QObject>
#include <QtCore/QSize>
#include <QtCore/QStringList>
/**
  * Gère la conversion des images
  * @brief Gère la conversion des images
  * @author Samuel L
  */
class Converter : public QObject
{
    Q_OBJECT
    protected:
        /**
          * Taille de l'image
          */
        QSize _size;
        /**
          * Liste des images à convertir
          */
        QStringList _list;
        /**
          * Compteur de l'image lancés en conversion
          */
        qint32 _count;
        /**
          * Compteur du nombre d'images finies
          */
        qint32 _countFinished;
        /**
          * Maximum d'images converties en même temps
          */
        qint32 _max;
        /**
          * Repertoire de destination
          */
        QString _dest;
    public:
        /**
          * Constructeur
          */
        Converter(QObject *parent = 0);
    public slots:
        /**
          * Lance la conversion d'images
          */
        void start(QStringList list, QSize size, int max = Config::PROCESS, QString dest = "TN");
        /**
          * Appelé à la fin de conversion d'une image
          */
        void convertFinished();
    signals:
        void imageHasFinished(int n);
        void taskCompleted();
    protected:
        /**
          * Lance un processus fils qui doit convertir une image
          */
        void launchProcess(QString pathToImage, QSize size);
};

#endif // CONVERTER_H
