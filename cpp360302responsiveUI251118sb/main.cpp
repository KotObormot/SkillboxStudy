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
    QPushButton* button2 = new QPushButton("Two", window); // 2-я кнопка
    QPushButton* button3 = new QPushButton("Three", window); // 3-я кнопка

    auto* layout = new QVBoxLayout(window);
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);

    window->resize(300, 300);
    window->move(1000, 500);
    
    window->show();
    return app.exec();
}

#include <main.moc>
