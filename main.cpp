/*
 ****************************************************
 *
 * Author:WuHanghang                                *
 * CST,Tsinghua University.                         *
 * email:wuxx14@mails.tsinghua.edu.cn               *
 * from git@china.                                  *
 *                                                  *
 ****************************************************
*/

#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
