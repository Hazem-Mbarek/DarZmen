#ifndef AJOUTERCONTRATS_H
#define AJOUTERCONTRATS_H

#include <QMainWindow>

namespace Ui {
class AjouterContrats;
}

class AjouterContrats : public QMainWindow
{
    Q_OBJECT

public:
    explicit AjouterContrats(QWidget *parent = nullptr);
    ~AjouterContrats();

private:
    Ui::AjouterContrats *ui;
};

#endif // AJOUTERCONTRATS_H
