#include <QMainWindow>
#include <QtWidgets/QLineEdit>

class CallerMainWindow : public QMainWindow {
    Q_OBJECT

  public:
    QLineEdit* lineEdit = nullptr;
    CallerMainWindow(QWidget* parent = nullptr) : QMainWindow(parent) {}
    
  public slots:
    void slot0() { lineEdit->setText(lineEdit->text() + "0"); };
    void slot1() { lineEdit->setText(lineEdit->text() + "1"); };
    void slot2() { lineEdit->setText(lineEdit->text() + "2"); };
    void slot3() { lineEdit->setText(lineEdit->text() + "3"); };
    void slot4() { lineEdit->setText(lineEdit->text() + "4"); };
    void slot5() { lineEdit->setText(lineEdit->text() + "5"); };
    void slot6() { lineEdit->setText(lineEdit->text() + "6"); };
    void slot7() { lineEdit->setText(lineEdit->text() + "7"); };
    void slot8() { lineEdit->setText(lineEdit->text() + "8"); };
    void slot9() { lineEdit->setText(lineEdit->text() + "9"); };
    void slotCall() { lineEdit->setText("Call!"); };
};