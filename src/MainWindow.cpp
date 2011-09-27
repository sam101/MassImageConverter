#include <MainWindow.h>
#include <QtGui/QFileDialog>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
/**
  * Constructeur
  */
MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
    setWindowTitle(tr("MassImageConverter 1.0"));
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
    hbox->addWidget(del);
    QPushButton *convert = new QPushButton(tr("Convertir"));
    connect(convert,SIGNAL(clicked()),this,SLOT(convert()));
    hbox->addWidget(convert);

    _listView = new QListView;
    _model = new QStringListModel;
    _listView->setModel(_model);
    _model->setStringList(_list);

    layout->addWidget(_listView);

    _converter = new Converter(this);

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
}
/**
  * Convertit les images à la liste
  */
void MainWindow::convert()
{
    _converter->start(_list,QSize(1000,1000));
}
