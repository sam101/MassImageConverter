#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Converter.h>

#include <QtGui/QListView>
#include <QtGui/QProgressBar>
#include <QtGui/QStringListModel>
#include <QtGui/QMainWindow>
/**
  * Gère la fenêtre principale de l'application
  * @brief Gère la fenêtre principale de l'application
  * @author Samuel L
  */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    protected:
        /**
          * Pointeur vers le Converter
          */
        Converter *_converter;
        /**
          * Pointeur vers la ListView
          */
        QListView *_listView;
        /**
          * Modèle d'affichage du ListView
          */
        QStringListModel *_model;
        /**
          * Liste contenant les fichiers
          */
        QStringList _list;
        /**
          * Pointeur vers la ProgressBar
          */
        QProgressBar *_bar;
    public:
        /**
          * Constructeur
          */
        MainWindow(QWidget *parent = 0);
        /**
          * Destructeur
          */
        ~MainWindow();
    public slots:
        /**
          * Ajoute des images à la liste à convertir
          */
        void addImages();
        /**
          * Convertit les images à la liste
          */
        void convert();
        /**
          * Met à jour la ProgressBar sur le nombre d'images finies
          */
        void inProgress(int n);
};
#endif // MAINWINDOW_H
