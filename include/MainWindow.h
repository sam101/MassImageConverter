#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Converter.h>

#include <QtGui/QListView>
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
    public:
        /**
          * Constructeur
          */
        MainWindow(QWidget *parent = 0);
        ~MainWindow();
};
#endif // MAINWINDOW_H
