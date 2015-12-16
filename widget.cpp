#include "widget.h"
#include "ui_widget.h"
#include<QtCore/qmath.h>
#include<QPainter>
#include<QtDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //设置界面
    ui->setupUi(this);
    this->setWindowTitle("Sierpinski");
    //初始值设置
    length=600;
    n=0;
    color=Qt::yellow;
    //计算初始面积
    double area=5000*qCos(M_PI/6)*pow(0.75,n);
    //更新面积显示区的数值
    ui->areaEdit->setText(QString::number(area));
    //初始化triangles
    triangles=new QQueue<QPolygonF>();
    triangles->clear();
    updateTriangles(0);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //设置画笔
    QPen pen;
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    painter.setPen(pen);
    //设置画刷
    QBrush brush(Qt::SolidPattern); // 画刷
    brush.setColor(color);
    painter.setBrush(brush); // 设置画刷
    //将triangles里面的所有分形三角形画出来
    for(int i=0;i<triangles->size();++i)
        painter.drawPolygon(triangles->at(i));
}

void Widget::updateTriangles(int n) {
    //初始化只含有最大的三角形
    triangles->clear();
    QPolygonF singleTriangle;
    singleTriangle  << QPointF(160+length*qSin(M_PI/6),30)
                    << QPointF(160,30+length*qCos(M_PI/6))
                    << QPointF(160+length,30+length*qCos(M_PI/6));
    triangles->append(singleTriangle);
    //1-n级分形三角形的位置坐标，并且更新到triangles里面
    for(int i=0;i<n;++i)   {
        long long needOut=pow(3,i);
        for(long long j=1;j<=needOut;++j)   {
            QPolygonF singleTriangle=triangles->dequeue();
            QPointF A,B,C;
            //singleTriangle>>A>>B>>C;
            A=singleTriangle.at(0);
            B=singleTriangle.at(1);
            C=singleTriangle.at(2);
            QPointF AB=QPointF((A.x()+B.x())/2,(A.y()+B.y())/2);
            QPointF BC=QPointF((B.x()+C.x())/2,(B.y()+C.y())/2);
            QPointF CA=QPointF((C.x()+A.x())/2,(C.y()+A.y())/2);
            QPolygonF A_AB_CA,B_AB_BC,C_BC_CA;
            A_AB_CA <<A<<AB<<CA;
            B_AB_BC <<B<<AB<<BC;
            C_BC_CA <<C<<BC<<CA;
            triangles->append(A_AB_CA);
            triangles->append(B_AB_BC);
            triangles->append(C_BC_CA);
        }
    }
    //triangles被更新，所以应该调用update()函数，重新绘制
    update();
}

void Widget::on_valueRange_sliderMoved(int position)
{
    //n值显示区的数值更新
    ui->nLabel->setText(QString::number(position));
    //n大于maxVisiableValue时，更多的分形在已有屏幕上体现不出来，没有深入绘制的必要
    int maxVisiableValue=8;
    if(position>maxVisiableValue) {
        if(n<maxVisiableValue)     updateTriangles(maxVisiableValue);
    }
    //否则，绘制n级分形三角形
    else {
        updateTriangles(position);
    }
    //更新n以及面积
    n=position;
    double area=5000*qCos(M_PI/6)*pow(0.75,n);
    ui->areaEdit->setText(QString::number(area));
}

void Widget::on_valueRange_valueChanged(int value)
{
    //直接调用以上函数即可
    on_valueRange_sliderMoved(value);
}
