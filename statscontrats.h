#ifndef STATSCONTRATS_H
#define STATSCONTRATS_H

#include <QMainWindow>

namespace Ui {
class StatsContrats;
}

class StatsContrats : public QMainWindow
{
    Q_OBJECT

public:
    explicit StatsContrats(QWidget *parent = nullptr);
    ~StatsContrats();

private:
    Ui::StatsContrats *ui;
};

#endif // STATSCONTRATS_H
