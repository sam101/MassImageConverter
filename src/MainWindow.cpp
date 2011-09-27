#include <MainWindow.h>
#include <QtGui/QFileDialog>
#include <QtGui/QVBoxLayout>
/**
  * Constructeur
  */
MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
    _converter = new Converter(this);
    connect(_converter,SIGNAL(imageHasFinished(int)),this,SLOT(inProgress(int)));

    setWindowTitle(tr("MassImageConverter. Par Sam101"));
    //On construit le layout de la fenêtre.
    QVBoxLayout *layout = new QVBoxLayout;
    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    widget->setLayout(layout);
    //On ajoute les boutons de l'interface
    QHBoxLayout *hbox = new QHBoxLayout;
    layout->addLayout(hbox);

    QPushButton *add = new QPushButton(tr("Ajouter images"));
    connect(add,SIGNAL(clicked()),this,SLOT(addImages()));
    hbox->addWidget(add);

    QPushButton *del = new QPushButton(tr("Supprimer"));
    connect(del,SIGNAL(clicked()),this,SLOT(clearImages()));
    hbox->addWidget(del);

    _convert = new QPushButton(tr("Convertir"));
    connect(_convert,SIGNAL(clicked()),this,SLOT(convert()));
    hbox->addWidget(_convert);

    //On ajoute la listView et on paramètre son modèle
    _listView = new QListView;
    _model = new QStringListModel;
    _listView->setModel(_model);
    _model->setStringList(_list);

    layout->addWidget(_listView);

    //On ajoute la progressBar
    _bar = new QProgressBar;
    layout->addWidget(_bar);

    //On fixe la taille de la barre
    resize(640,480);
}
/**
  * Destructeur
  */
MainWindow::~MainWindow()
{

}
/**
  * Ajoute des images à la liste à convertir
  */
void MainWindow::addImages()
{
    _list += QFileDialog::getOpenFileNames(this,tr("Selectionnez les images à convertir"),QString(),"Images (*.png *.xpm *.jpg)");
    _model->setStringList(_list);
    _bar->setMaximum(_list.size());
    _bar->setValue(0);
}
/**
  * Supprime toutes les images de la liste
  */
void MainWindow::clearImages()
{
    _list.clear();
    _model->setStringList(_list);
}
/**
  * Convertit les images à la liste
  */
void MainWindow::convert()
{
    _bar->setValue(0);
    _converter->start(_list,QSize(1000,1000));
    _convert->setEnabled(false);
}
/**
  * Met à jour la ProgressBar sur le nombre d'images finies
  */
void MainWindow::inProgress(int n)
{
    _bar->setValue(n);
}
/**
  * Appelé à la fin du traitement,
  * Réactive le bouton "Convertir"
  */
void MainWindow::endConvert()
{
    _convert->setEnabled(true);
}
