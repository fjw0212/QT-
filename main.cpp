#include "studentdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    studentDialog w;
    w.show();
    return a.exec();
}
