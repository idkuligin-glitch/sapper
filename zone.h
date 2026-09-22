#ifndef ZONE_H
#define ZONE_H

#include <QObject>
#include <QPushButton>
#include <QList>
#include <QMessageBox>
#include <QApplication>
static int x = 5, y=5;
class zone : public QObject
{
    Q_OBJECT
public:
    explicit zone(QObject *parent = nullptr);
    QPushButton *but;
    int *ind;
    QList<int>bombs;
    zone(QPushButton *b, int ind, QList<int> bom){
        this->but = b;
        this->ind=new int(ind);
        this->bombs=bom;
    }
    ~zone(){
        delete ind;
    }

signals:
    void pressed();
public slots:
    void a(){
        if (!bombs.contains(*ind)){
            int b = 0;
            int i = *ind / y, j = *ind % y;
            for (int i2=-1; i2<=1; i2++){
                for (int j2=-1;j2<=1; j2++){
                    if (i2==0 && j2==0){
                        continue;
                    }
                    int tmp1 = i+i2,tmp2 = j+j2;
                    if (!(tmp1<0 || tmp1>=x || tmp2<0 || tmp2>=y)&&bombs.contains(tmp1*y+tmp2)){
                        b+=1;
                    }
                }
            }

            but->setText(QString::number(b));
        }
        else{
            but->setText("ой");
            QMessageBox::critical(nullptr, "Вы проиграли", "Вы проиграли");
            QApplication::quit();
        }
    }
};

#endif // ZONE_H
