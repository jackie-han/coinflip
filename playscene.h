#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(int _index, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

signals:
    void chooseSceneBack();

protected:
    int levelIndex; // 记录关卡索引
};

#endif // PLAYSCENE_H
