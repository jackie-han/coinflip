#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include "mypushbutton.h"

PlayScene::PlayScene(int _index, QWidget *parent)
    : QMainWindow{parent}
    , levelIndex(_index)
{
    qDebug() << "current level:" << _index;
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

    // 显示当前关卡标题
    QLabel *label = new QLabel(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str = QString("Level:%1").arg(levelIndex);
    label->setText(str);
    label->setGeometry(QRect(30, height() - 50, 140, 50)); // 设置大小和位置

    // 创建金币的背景图片
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // 绘制北京图片
            QLabel *label = new QLabel(this);
            label->setGeometry(0, 0, 50, 50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->move(57 + i * 50, 200 + j * 50);
        }
    }
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
