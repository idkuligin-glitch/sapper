#include "mainwindow.h"
#include <QWidget>
#include <QApplication>
#include <QList>
#include <QPushButton>
#include "zone.h"
#include <QRandomGenerator>
#include <QGridLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *b = new QWidget;
    QList<zone*> list;
    int count = 0;
    static QList<int>bombs;
    while (bombs.size()<5){
        int tmp = QRandomGenerator::global()->bounded(25);
        if(!bombs.contains(tmp)){
            bombs.append(tmp);
        }
    }
    auto *layer=new QGridLayout;
    for (int i = 0; i<5; i++){
        for (int j = 0; j<5; j++){
            zone *tmp = new zone(new QPushButton("",b), i*5+j, bombs);
            tmp->but->setFixedSize(32,32);
            QObject::connect(tmp, &zone::pressed,tmp, &zone::a);
            QObject::connect(tmp->but, &QPushButton::clicked, [tmp,&count](){
                emit tmp->pressed();
                QObject::disconnect(tmp, &zone::pressed,tmp, &zone::a);
                if (++count==20){
                    QMessageBox::critical(nullptr, "Вы победили", "Вы победили");
                    QApplication::quit();
                }
            });
            layer->addWidget(tmp->but,i,j);
        }
    }
    b->setLayout(layer);
    b->show();
    return QApplication::exec();
}
