#ifndef STATSMATRIELS_H
#define STATSMATRIELS_H

#include <QMainWindow>

namespace Ui {
class StatsMatriels;
}

class StatsMatriels : public QMainWindow
{
    Q_OBJECT

public:
    explicit StatsMatriels(QWidget *parent = nullptr);
    ~StatsMatriels();

private:
    Ui::StatsMatriels *ui;
};

#endif // STATSMATRIELS_H
