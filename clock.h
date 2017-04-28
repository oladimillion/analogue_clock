#ifndef Clock_H
#define Clock_H

#include <QWidget>
#include <QPainter>
#include <QPolygonF>
#include <QLineF>
#include <QTime>
#include <QPixmap>

class Clock : public QWidget
{
    Q_OBJECT

public:
    Clock(QWidget *parent = 0);
    ~Clock();

    void drawCenterPoint(QPainter *painter);
    void drawBorder(QPainter *painter);
    void drawClockhands(QPainter *painter);

protected:
    virtual void paintEvent(QPaintEvent *events);


private:
    QTime time;
    QTimer *timer;
    QPixmap pixmap;
};

#endif // Clock_H
