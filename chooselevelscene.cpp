#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include "mypushbutton.h"
#include "playscene.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
    , pScene(nullptr)
{
    // 设置窗口固定大小
    setFixedSize(320, 588);
    // 设置图标
    setWindowIcon(QPixmap(":/res/Coin0001.png"));
    // 设置标题
    setWindowTitle("select level");

    // 创建菜单栏
    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    // 创建开始菜单
    QMenu *startMenu = bar->addMenu("start");
    // 创建按钮菜单项
    QAction *quickAction = startMenu->addAction("quit");
    // 点击退出，退出游戏
    connect(quickAction, &QAction::triggered, this, [=]() {
        close();
    });

    // 创建返回按钮
    MyPushButton *closeBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(width() - closeBtn->width(), height() - closeBtn->height());

    // 返回按钮共嗯
    connect(closeBtn, &MyPushButton::clicked, this, [=]() {
        this->hide();
        // 触发自定义信号，关闭自身，该信号写到signals下做声明
        emit chooseSceneBack();
    });

    // 创建关卡按钮
    for (int i = 0; i < 20; i++) {
        MyPushButton *menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + (i % 4) * 70, 130 + (i / 4) * 70);

        // 按钮上显示的文字
        QLabel *label = new QLabel(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i + 1));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter); // 设置居中
        label->move(25 + (i % 4) * 70, 130 + (i / 4) * 70);
        label->setAttribute(Qt::WA_TransparentForMouseEvents); // 鼠标事件穿透

        // 监听选择关卡按钮的信号槽
        connect(menuBtn, &MyPushButton::clicked, this, [=]() {
            qDebug() << "select: " << i;
            if (pScene == nullptr) { // 游戏场景最好不用复用，直接移除掉创建新的游戏场景
                hide();
                pScene = new PlayScene(i + 1);
                connect(pScene, &PlayScene::chooseSceneBack, this, [=]() {
                    show();
                    delete pScene;
                    pScene = nullptr;
                });
                pScene->show();
            }
        });
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, width(), height(), pix);

    // 加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);
}
