#include <QApplication>
#include <QSlider>
#include <QSpinBox>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto* slider = new QSlider(Qt::Horizontal);
    auto* spinbox = new QSpinBox();
    slider->setMaximum(100);
    slider->setMinimum(0);
    spinbox->setMinimum(0);
    spinbox->setMaximum(100);

    QObject::connect(slider, &QSlider::valueChanged, spinbox, &QSpinBox::setValue);
    QObject::connect(spinbox, QOverload<int>::of(&QSpinBox::valueChanged), slider, &QSlider::setValue);

    slider->resize(500, 50);
    spinbox->resize(200, 50);
    spinbox->move(2800, 500);
    slider->move(2600, 500);

    slider->show();
    spinbox->show();

    app.exec();
}

//#include <main.moc>
/********************************************
что означает includes the moc file "main.moc", but does not contain a q_object, q_gadget, q_namespace or q_namespace_export macro.
Если ваш файл main.cpp не содержит класса, унаследованного от QObject (или использующего другие макросы мета-объектной системы) 
и не требует генерации мета-информации, то включение MOC-файла не нужно, и его можно просто удалить.
*********************************************/
