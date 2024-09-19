#ifndef STATSARTISTES_H
#define STATSARTISTES_H

#include <QMainWindow>

namespace Ui {
class StatsArtistes;
}

class StatsArtistes : public QMainWindow
{
    Q_OBJECT

public:
    explicit StatsArtistes(QWidget *parent = nullptr);
    ~StatsArtistes();

private:
    Ui::StatsArtistes *ui;
};

#endif // STATSARTISTES_H
