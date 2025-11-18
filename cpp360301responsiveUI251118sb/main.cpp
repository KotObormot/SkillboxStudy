#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget* window = new QWidget(); // главное окно

    QPushButton* button1 = new QPushButton("One", window); // 1-я кнопка
    button1->move(40, 50);                                 // переместим внутрь окна
    
    QPushButton* button2 = new QPushButton("Two", window); // 2-я кнопка
    button2->move(140, 150);                                 // переместим внутрь окна
    
    QPushButton* button3 = new QPushButton("Three", window); // 3-я кнопка
    button3->move(200, 200);                                 // переместим внутрь окна

    window->resize(300, 300);
    window->move(1000, 500);
    
    window->show();
    return app.exec();
}

#include <main.moc>
