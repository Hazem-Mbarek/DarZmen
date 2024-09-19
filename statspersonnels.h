#ifndef STATSPERSONNELS_H
#define STATSPERSONNELS_H

#include <QMainWindow>

namespace Ui {
class StatsPersonnels;
}

class StatsPersonnels : public QMainWindow
{
    Q_OBJECT

public:
    explicit StatsPersonnels(QWidget *parent = nullptr);
    ~StatsPersonnels();

private:
    Ui::StatsPersonnels *ui;
};

#endif // STATSPERSONNELS_H
