#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QPushButton *parent = nullptr);
    explicit MyPushButton(QString normalImg, QString pressImg = "");

    void zoom1();
    void zoom2();

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

protected:
    QString normalImgPath; // 默认显示图片路径
    QString pressedImgPath; // 按下后显示图片路径
};

#endif // MYPUSHBUTTON_H
