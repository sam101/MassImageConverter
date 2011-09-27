#include <MainWindow.h>
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
    //On ajoute
}

MainWindow::~MainWindow()
{

}
