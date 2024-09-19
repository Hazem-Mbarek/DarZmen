#ifndef STATSSALLES_H
#define STATSSALLES_H

#include <QMainWindow>

namespace Ui {
class StatsSalles;
}

class StatsSalles : public QMainWindow
{
    Q_OBJECT

public:
    explicit StatsSalles(QWidget *parent = nullptr);
    ~StatsSalles();

private:
    Ui::StatsSalles *ui;
};

#endif // STATSSALLES_H
