#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QPushButton *parent)
    : QPushButton{parent}
    , normalImgPath("")
    , pressedImgPath("")
{

}

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
    : normalImgPath(normalImg)
    , pressedImgPath(pressImg)
{
    // 创建QPixmap对象
    QPixmap pixmap;
    // 判断是否能够加载正常显示的图片，若不能提示加载失败
    if (!pixmap.load(normalImgPath)) {
        qDebug() << normalImgPath << "加载图片失败!";
    }
    // 设置图片的固定尺寸
    setFixedSize(pixmap.width(), pixmap.height());
    // 设置不规则图片的样式表
    setStyleSheet("QPushButton{border:0px;}");
    // 设置图标
    setIcon(pixmap);
    // 设置图标大小
    setIconSize(QSize(pixmap.width(), pixmap.height()));
}

void MyPushButton::zoom1()
{
    // 创建动画对象
    QPropertyAnimation *animation1 = new QPropertyAnimation(this, "geometry");
    // 设置时间间隔，单位毫秒
    animation1->setDuration(200);
    // 创建起始位置
    animation1->setStartValue(QRect(x(), y(), width(), height()));
    // 创建结束位置
    animation1->setEndValue(QRect(x(), y() + 10, width(), height()));
    // 设置缓和曲线， QEasingCurve::OutBounce为弹跳效果
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    // 开始执行动画
    animation1->start();
}

void MyPushButton::zoom2()
{
    QPropertyAnimation *animation1 = new QPropertyAnimation(this, "geometry");
    animation1->setDuration(200);

    animation1->setStartValue(QRect(x(), y() + 10, width(), height()));
    animation1->setEndValue(QRect(x(), y(), width(), height()));
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if (pressedImgPath != "") {
        QPixmap pixmap;
        if (!pixmap.load(pressedImgPath)) {
            qDebug() << "pressedImgPath" << "加载图片失败";
        }

        setFixedSize(pixmap.width(), pixmap.height());
        setStyleSheet("QPushButton{border:0px;}");
        setIcon(pixmap);
        setIconSize(QSize(pixmap.width(), pixmap.height()));
    }

    // 交给父类执行按下事件
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (normalImgPath != "") {
        QPixmap pixmap;
        if (!pixmap.load(normalImgPath)) {
            qDebug() << "normalImgPath" << "加载图片失败";
        }

        setFixedSize(pixmap.width(), pixmap.height());
        setStyleSheet("QPushButton{border:0px;}");
        setIcon(pixmap);
        setIconSize(QSize(pixmap.width(), pixmap.height()));
    }

    // 交给父类执行按下事件
    return QPushButton::mouseReleaseEvent(e);
}
