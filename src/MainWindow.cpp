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
#include <MainWindow.h>
#include <QtGui/QFileDialog>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
/**
  * Constructeur
  */
MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
    _converter = new Converter(this);
    connect(_converter,SIGNAL(imageHasFinished(int)),this,SLOT(inProgress(int)));
    connect(_converter,SIGNAL(taskCompleted()),this,SLOT(endConvert()));
    setWindowTitle(tr("MassImageConverter. By Sam101"));
    //On construit le layout de la fenêtre.
    QVBoxLayout *layout = new QVBoxLayout;
    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    widget->setLayout(layout);
    //On ajoute les boutons de l'interface
    QHBoxLayout *hbox = new QHBoxLayout;
    layout->addLayout(hbox);

    QPushButton *add = new QPushButton(tr("Add images"));
    connect(add,SIGNAL(clicked()),this,SLOT(addImages()));
    hbox->addWidget(add);

    QPushButton *del = new QPushButton(tr("Delete"));
    connect(del,SIGNAL(clicked()),this,SLOT(clearImages()));
    hbox->addWidget(del);

    _convert = new QPushButton(tr("Convert"));
    connect(_convert,SIGNAL(clicked()),this,SLOT(convert()));
    hbox->addWidget(_convert);

    //On ajoute un QHboxLayout pour les paramètres de taille et de nombre de processus
    QHBoxLayout *h2 = new QHBoxLayout;

    //Label de la taille
    QLabel *labelSize = new QLabel(tr("Size:"));
    h2->addWidget(labelSize);
    //Spinbox de la taille
    _size = new QSpinBox;
    _size->setMinimum(1);
    _size->setMaximum(10000);
    _size->setValue(Config::SIZE);
    h2->addWidget(_size);
    //Label des processus
    QLabel *labelProcess = new QLabel(tr("Process number:"));
    h2->addWidget(labelProcess);
    //Spinbox des processus
    _process = new QSpinBox;
    _process->setMinimum(1);
    _process->setMaximum(1024);
    _process->setValue(Config::PROCESS);
    h2->addWidget(_process);
    //LineEdit pour le repertoire de destination
    QLabel *destLabel = new QLabel(tr("Destination Directory:"));
    h2->addWidget(destLabel);
    _dest = new QLineEdit;
    _dest->setText(tr("TN"));
    h2->addWidget(_dest);
    //On ajoute le layout
    layout->addLayout(h2);

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
    _list += QFileDialog::getOpenFileNames(this,tr("Select pictures to convert"),QString(),"Images (*.png *.xpm *.jpg)");
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
    _converter->start(_list,QSize(_size->value(),0),_process->value(),_dest->text());
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
