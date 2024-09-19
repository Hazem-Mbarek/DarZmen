#ifndef AJOUTERMATRIELS_H
#define AJOUTERMATRIELS_H

#include <QMainWindow>

namespace Ui {
class AjouterMatriels;
}

class AjouterMatriels : public QMainWindow
{
    Q_OBJECT

public:
    explicit AjouterMatriels(QWidget *parent = nullptr);
    ~AjouterMatriels();
    void FacialRecognition();

private slots:
    void on_facialrec_clicked();

private:
    Ui::AjouterMatriels *ui;
};

#endif // AJOUTERMATRIELS_H
