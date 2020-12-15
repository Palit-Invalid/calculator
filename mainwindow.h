#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    char* ConvertCC(char* x,int fromCC,int toCC);

private slots:
    void digit_number();
    void math_operations();

    void on_button_equal_clicked();
    void on_button_ac_clicked();

    void convert_to_bin();
    void convert_to_oct();
    void convert_to_dec();
    void convert_to_hex();

    void change_labels(QString text);

private:
    Ui::MainWindow *ui;
    bool error;
    int notation;
    int num_first;
    int num_second;
    int answer;
    QString temp_1, temp_2;

};
#endif // MAINWINDOW_H
