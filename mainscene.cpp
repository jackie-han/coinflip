#include "mainscene.h"
#include "./ui_mainscene.h"
#include <QPainter>
#include "mainscene.h"
#include <QTimer>
#include "mypushbutton.h"
#include "chooselevelscene.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    // 设置固定大小
    setFixedSize(320, 588);
    // 设置应用图片
    setWindowIcon(QPixmap(":/res/Coin0001.png"));
    // 设置窗口标题
    setWindowTitle(QString("Coin Flip"));

    // 退出按钮
    connect(ui->actionquit, &QAction::triggered, this, [=]() {
        close();
    });

    // 选择关卡场景
    ChooseLevelScene *chooseScene = new ChooseLevelScene;
    // 监听选择场景的返回按钮
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, this, [=]() {
        show();
    });

    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(width() * 0.5 - startBtn->width() * 0.5, height() * 0.7);

    // 监听点击事件，执行特效
    connect(startBtn, &MyPushButton::clicked, this, [=]() {
        startBtn->zoom1();
        startBtn->zoom2();

        // 延时0.5s后进入场景
        QTimer::singleShot(500, this, [=]() {
            hide();
            chooseScene->show();
        });
    });
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *event)
{
    // 创建画家，指定绘图设备
    QPainter painter(this);
    // 创建QPixmap对象
    QPixmap pix;
    // 加载图片
    pix.load(":/res/PlayLevelSceneBg.png");
    // 绘制背景图
    painter.drawPixmap(0, 0, width(), height(), pix);

    // 加载标题
    pix.load(":/res/Title.png");
    // 缩放图片
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}

