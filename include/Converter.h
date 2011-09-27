#ifndef CONVERTER_H
#define CONVERTER_H
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
    protected:
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
        Converter();
    public slots:
        /**
          * Lance la conversion d'images
          */
        void start(QStringList list, QSize size, int max = 4, QString dest = "TN");
        /**
          * Appelé à la fin de conversion d'une image
          */
        void convertFinished();
    signals:
        void imageHasFinished(qint32 n);
        void taskCompleted();
};

#endif // CONVERTER_H
