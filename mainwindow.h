#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void start_loading();
private slots:
    void on_matmainButton_clicked();

    void on_eventmainButton_clicked();

    void on_sallesmainButton_clicked();

    void on_contratsmainButton_clicked();

    void on_artistemainButton_clicked();

    void on_employesmainButton_clicked();

    void on_eventmainButton_2_clicked();

    void on_retourOptions_clicked();

    void on_sallesmainButton_2_clicked();

    void on_sallesmainButton_3_clicked();

    void on_loginButton_clicked();
    void on_forgotPasswordButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
