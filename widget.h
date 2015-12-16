#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QQueue>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void paintEvent(QPaintEvent*);//画图函数
private slots:
    void on_valueRange_sliderMoved(int position);//滑动条数值改变为position时调用的函数

    void on_valueRange_valueChanged(int value);

private:
    Ui::Widget *ui;
    QColor color;//填充颜色
    QQueue<QPolygonF>* triangles;//储存已有的分形三角形
    int length;//大三角形的边长
    int n;//分形的次数

    void updateTriangles(int n);//根据n的值，更新分形三角形
};

#endif // WIDGET_H
