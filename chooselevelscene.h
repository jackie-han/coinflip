#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>

class PlayScene;

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

signals:
    void chooseSceneBack();

protected:
    PlayScene *pScene;
};

#endif // CHOOSELEVELSCENE_H
