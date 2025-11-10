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

#include <main.moc>
