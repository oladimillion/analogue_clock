#include "clock.h"
#include <QTimer>
#include <QDate>

Clock::Clock(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(500, 550);
    setWindowTitle("Analogue Clock");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout() ), this, SLOT(update() ) );
    timer->setInterval(1000);
    timer->start();
}

Clock::~Clock()
{
    delete timer;
}

void Clock::drawCenterPoint(QPainter *painter)
{
    QPen originalPen = painter->pen();
    QPen pen(Qt::white);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawEllipse(-1, -1, 2, 2);
    painter->setPen(originalPen);
}

void Clock::drawBorder(QPainter *painter)
{

    QPen originalPen = painter->pen();
    QBrush originalBrush = painter->brush();
    QRect rect = QRect(-48, -48, 96, 96);
    painter->setBrush(Qt::Dense3Pattern);
    painter->drawRect(rect);


    pixmap = QPixmap(":/bg/ClockBackground2.jpg");
    rect = QRect(-45, -45, 90, 90);
    QPen pen(Qt::black);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawRect(rect);

    rect = QRect(-45, -45, 90, 90);
    painter->drawPixmap(rect, pixmap);

    painter->setPen(originalPen);
    painter->setBrush(originalBrush);
}

void Clock::drawClockhands(QPainter *painter)
{
    QPointF secondHand[] = {
        QPointF(0, -38),
        QPointF(-1.5, 0),
        QPointF(0, 8),
        QPointF(1.5, 0) };

    QPointF minuteHand[] = {
        QPointF(0, -32),
        QPointF(-2, 0),
        QPointF(0, 5),
        QPointF(2, 0) };

    QPointF minuteHandBorder[] = {
        QPointF(0, -30),
        QPointF(-2, 0),
        QPointF(0, 5),
        QPointF(2, 0) };

    QPointF hourHand[] = {
        QPointF(0, -24),
        QPointF(-2, 0),
        QPointF(0, 2),
        QPointF(2, 0) };

    QPointF hourHandBorder[] = {
        QPointF(0, -22),
        QPointF(-2, 0),
        QPointF(0, 1.5),
        QPointF(2, 0) };

    time = QTime::currentTime();

    //draw hour hand
    painter->save();
    qreal minuteHand_angle = (time.minute() * 6);
    qreal hourHand_angle = (time.hour() * 30) + (minuteHand_angle/12);
    QPen pen = QPen(Qt::darkGray);
    painter->setPen(pen);
    painter->setBrush(Qt::darkGray);
    painter->rotate(hourHand_angle);
    painter->drawPolygon(hourHand, 4);
    painter->restore();

    //draw hour hand border
    painter->save();
    qreal hourHand_angle_border = (time.hour() * 30) + (minuteHand_angle/12);
    pen = QPen(Qt::white);
    pen.setWidth(0.7);
    painter->setPen(pen);
    painter->rotate(hourHand_angle_border);
    painter->drawPolygon(hourHandBorder, 4);
    painter->restore();

    //draw minute hand
    painter->save();
    minuteHand_angle = (time.minute() * 6);
    pen = QPen(Qt::darkGray);
    painter->setPen(pen);
    painter->setBrush(Qt::darkGray);
    painter->rotate(minuteHand_angle);
    painter->drawPolygon(minuteHand, 4);
    painter->restore();

    //draw minute hand border
    painter->save();
    qreal minuteHand_angle_border = (time.minute() * 6);
    pen = QPen(Qt::white);
    pen.setWidth(0.7);
    painter->setPen(pen);
    painter->rotate(minuteHand_angle_border);
    painter->drawPolygon(minuteHandBorder, 4);
    painter->restore();

    //draw second hand
    painter->save();
    qreal secondHand_angle = (time.second() * 6);
    pen = QPen(Qt::red);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->setBrush(Qt::red);
    painter->rotate(secondHand_angle);
    painter->drawPolygon(secondHand, 4);
    painter->restore();
}

void Clock::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    int side = qMin(width(), height());

    painter.setViewport((width() - side) / 2,
                        (height() - side) / 2,
                        side, side);

    painter.setWindow(-50, -50, 100, 100);

    drawBorder(&painter);
    drawClockhands(&painter);
    drawCenterPoint(&painter);
}
