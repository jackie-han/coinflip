#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include <QTimer>
#include "mypushbutton.h"

PlayScene::PlayScene(int _index, QWidget *parent)
    : QMainWindow{parent}
    , levelIndex(_index)
{
    qDebug() << "当前关卡为" << _index;
    // 设置窗口固定大小
    setFixedSize(320, 588);
    // 设置图标
    setWindowIcon(QPixmap(":/res/Coin0001.png"));
    // 设置标题
    setWindowTitle("Coin Flip");

    // 创建菜单栏
    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    // 创建开始菜单
    QMenu *startMenu = bar->addMenu(QStringLiteral("开始"));
    // 创建按钮菜单项
    QAction *quitAction = startMenu->addAction(QStringLiteral("退出"));
    // 点击退出，退出游戏
    connect(quitAction, &QAction::triggered, this, [=]() {
        close();
    });

    // 返回按钮
    MyPushButton *closeBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(width() - closeBtn->width(), height() - closeBtn->height());

    // 返回按钮功能实现
    connect(closeBtn, &MyPushButton::clicked, this, [=]() {
        QTimer::singleShot(500, this, [=]() {
            hide();
            // 触发自定义信号，关闭自身，该信号写到signals下做声明
            emit chooseSceneBack();
        });
    });
}

void PlayScene::paintEvent(QPaintEvent *event)
{
    // 加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, width(), height(), pix);

    // 加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}
