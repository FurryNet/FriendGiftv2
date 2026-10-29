#include "mainwindow.h"

#include <QApplication>
/*
 * All Possible Solution:
 * - Manual Bruteforce (slowest)
 * - Automated Bruteforce
 * - Reverse Engineering - Understand and decrypt the data manually
 * - Reverse Engineering - Modify the generation algorithm if/jmp condition to always return actual number (fastest)
 * - Use AI to automate reverse engineering (cheating and could be the fastest)
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
