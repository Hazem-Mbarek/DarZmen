#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QThread>
namespace Ui {
class Startwindow;
}

class Startwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Startwindow(QWidget *parent = nullptr);
    ~Startwindow();
    void start_loading();
private:
    Ui::Startwindow *ui;
};

#endif // STARTWINDOW_H
