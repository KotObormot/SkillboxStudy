#include <QApplication>
#include <QPushButton>
#include "./ui_caller.h"
#include "callermainwindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    //QPushButton button("Hello World!", nullptr);
    CallerMainWindow window(nullptr);
    Ui::MainWindow caller;
    caller.setupUi(&window);
    window.lineEdit = caller.lineEdit;
    window.resize(480, 640);
    window.show();
    return QApplication::exec();
}
