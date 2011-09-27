#include <MainWindow.h>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
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
    hbox->addWidget(add);
    QPushButton *del = new QPushButton(tr("Supprimer"));
    hbox->addWidget(del);
    QPushButton *convert = new QPushButton(tr("Convertir"));
    hbox->addWidget(convert);

    _listView = new QListView;
    _model = new QStringListModel;
    _listView->setModel(_model);
    _model->setStringList(_list);

    layout->addWidget(_listView);
}

MainWindow::~MainWindow()
{

}
