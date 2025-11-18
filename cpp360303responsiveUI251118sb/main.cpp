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
    QPushButton* button4 (new QPushButton("Four", window));
    QPushButton* button5{new QPushButton("Five", window)};

    auto* layout = new QGridLayout(window);
    layout->addWidget(button1, 0, 0);
    layout->addWidget(button2, 0, 1);
    layout->addWidget(button3, 1, 0, 1, 2);
    layout->addWidget(button4, 2, 0);
    layout->addWidget(button5, 2, 1);

    window->resize(300, 300);
    window->move(1000, 500);
    
    window->show();
    return app.exec();
}

#include <main.moc>
