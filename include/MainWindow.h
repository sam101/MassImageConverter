#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Converter.h>

#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
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
        /**
          * Bouton "Convertir"
          */
        QPushButton *_convert;
        /**
          * SpinBox contenant la taille
          */
        QSpinBox *_size;
        /**
          * Spinbox contenant le nombre de processus
          */
        QSpinBox *_process;
        /**
          * LineEdit contenant le repertoire de déstination
          */
        QLineEdit *_dest;
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
          * Supprime toute les images de la liste
          */
        void clearImages();
        /**
          * Met à jour la ProgressBar sur le nombre d'images finies
          */
        void inProgress(int n);
        /**
          * Appelé à la fin du traitement,
          * Réactive le bouton "Convertir"
          */
        void endConvert();
};
#endif // MAINWINDOW_H
