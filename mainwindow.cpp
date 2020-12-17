#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , notation(10)
    , num_first(0)
    , num_second(0)
{
    ui->setupUi(this);
    QWidget::setFixedSize(360,480);
    connect(ui->button_1, SIGNAL(clicked()), this, SLOT(digit_number()));
    connect(ui->button_2, SIGNAL(clicked()), this, SLOT(digit_number()));
    connect(ui->button_3, SIGNAL(clicked()), this, SLOT(digit_number()));
    connect(ui->button_4, SIGNAL(clicked()), this, SLOT(digit_number()));
    connect(ui->button_5, SIGNAL(clicked()), this, SLOT(digit_number()));
    connect(ui->button_6, SIGNAL(clicked()), this, SLOT(digit_number()));
    connect(ui->button_7, SIGNAL(clicked()), this, SLOT(digit_number()));
    connect(ui->button_8, SIGNAL(clicked()), this, SLOT(digit_number()));
    connect(ui->button_9, SIGNAL(clicked()), this, SLOT(digit_number()));
    connect(ui->button_0, SIGNAL(clicked()), this, SLOT(digit_number()));

    connect(ui->button_plus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->button_minus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->button_multiplie, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->button_divide, SIGNAL(clicked()), this, SLOT(math_operations()));

    ui->button_plus->setCheckable(true);
    ui->button_minus->setCheckable(true);
    ui->button_divide->setCheckable(true);
    ui->button_multiplie->setCheckable(true);

    ui->radio_dec->toggle();
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
    ui->lineEdit->setText("0");
    ui->button_a->setEnabled(false);
    ui->button_b->setEnabled(false);
    ui->button_c->setEnabled(false);
    ui->button_d->setEnabled(false);
    ui->button_e->setEnabled(false);
    ui->button_f->setEnabled(false);


    connect(ui->radio_bin, SIGNAL(toggled(bool)), this, SLOT(convert_to_bin()));
    connect(ui->radio_oct, SIGNAL(toggled(bool)), this, SLOT(convert_to_oct()));
    connect(ui->radio_dec, SIGNAL(toggled(bool)), this, SLOT(convert_to_dec()));
    connect(ui->radio_hex, SIGNAL(toggled(bool)), this, SLOT(convert_to_hex()));

    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this,SLOT(change_labels(QString)));
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), this,SLOT(change_labels(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_number()
{
    QPushButton* button = (QPushButton *)sender();
    QString str = ui->lineEdit->text() + button->text();
    int a = str.toInt();

    ui->lineEdit->setText(QString::number(a));

}

void MainWindow::math_operations()
{
    QPushButton* button = (QPushButton *)sender();
    if (notation == 2)
    {
        temp_1 = ConvertCC(ui->lineEdit->text().toLocal8Bit().data(),notation,10);
        num_first = temp_1.toInt();
    } else if (notation == 8)
    {
        temp_1 = ConvertCC(ui->lineEdit->text().toLocal8Bit().data(),notation,10);
        num_first = temp_1.toInt();
    } else if (notation == 16)
    {
        temp_1 = ConvertCC(ui->lineEdit->text().toLocal8Bit().data(),notation,10);
        num_first = temp_1.toInt();
    } else
    {
        num_first = ui->lineEdit->text().toInt();
    }
    qDebug() << "first num =" << num_first;
    ui->lineEdit->setText("");
    button->setChecked(true);
}

char* MainWindow::ConvertCC(char* x,int fromCC,int toCC)
{
    char *abc = {"0123456789ABCDEFGHIJKLMNOPQESTUVWXYZ"};
    char buf[255]={0};
    char *result;

    int i //Это количество символов в начальном числе
       ,k //Это будет порядковым номером очередного символа в входном числе
       ,ten=0 //Это будет его аналог в 10-чной системе
       ,stp=1; //А это просто степень для перевода в 10-чную

    for(i=0;x[i];i++);
    for(;i;i--)
    {
        for(k=0;abc[k]!=x[i-1] && k<36;k++);
        ten+=k*stp;
        stp*=fromCC;
    }
    k=0;
    while(ten)
    {
        i=ten % toCC;
        buf[k++]=abc[i];
        ten/=toCC;
    }

    result=new char[k+1];
    for(i=0;k;i++) result[i]=buf[--k];
    result[i]=0;
    return result;
}

void MainWindow::convert_to_bin()
{
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-1]*")));
    ui->lineEdit->setText(ConvertCC(ui->lineEdit->text().toLocal8Bit().data(),notation,2));
    notation = 2;
    ui->button_2->setEnabled(false);
    ui->button_3->setEnabled(false);
    ui->button_4->setEnabled(false);
    ui->button_5->setEnabled(false);
    ui->button_6->setEnabled(false);
    ui->button_7->setEnabled(false);
    ui->button_8->setEnabled(false);
    ui->button_9->setEnabled(false);
    ui->button_a->setEnabled(false);
    ui->button_b->setEnabled(false);
    ui->button_c->setEnabled(false);
    ui->button_d->setEnabled(false);
    ui->button_e->setEnabled(false);
    ui->button_f->setEnabled(false);
}

void MainWindow::convert_to_oct()
{
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-7]*")));
    ui->lineEdit->setText(ConvertCC(ui->lineEdit->text().toLocal8Bit().data(),notation,8));
    notation = 8;
    ui->button_8->setEnabled(false);
    ui->button_9->setEnabled(false);
    ui->button_2->setEnabled(true);
    ui->button_3->setEnabled(true);
    ui->button_4->setEnabled(true);
    ui->button_5->setEnabled(true);
    ui->button_6->setEnabled(true);
    ui->button_7->setEnabled(true);
}

void MainWindow::convert_to_dec()
{
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
    ui->lineEdit->setText(ConvertCC(ui->lineEdit->text().toLocal8Bit().data(),notation,10));
    notation = 10;
    ui->button_2->setEnabled(true);
    ui->button_3->setEnabled(true);
    ui->button_4->setEnabled(true);
    ui->button_5->setEnabled(true);
    ui->button_6->setEnabled(true);
    ui->button_7->setEnabled(true);
    ui->button_8->setEnabled(true);
    ui->button_9->setEnabled(true);
}

void MainWindow::convert_to_hex()
{
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9, A-F]*")));
    ui->lineEdit->setText(ConvertCC(ui->lineEdit->text().toLocal8Bit().data(),notation,16));
    notation = 16;
    ui->button_2->setEnabled(true);
    ui->button_3->setEnabled(true);
    ui->button_4->setEnabled(true);
    ui->button_5->setEnabled(true);
    ui->button_6->setEnabled(true);
    ui->button_7->setEnabled(true);
    ui->button_8->setEnabled(true);
    ui->button_9->setEnabled(true);
    ui->button_a->setEnabled(true);
    ui->button_b->setEnabled(true);
    ui->button_c->setEnabled(true);
    ui->button_d->setEnabled(true);
    ui->button_e->setEnabled(true);
    ui->button_f->setEnabled(true);
}

void MainWindow::on_button_equal_clicked()
{

    if (notation == 2)
    {
        temp_1 = ConvertCC(ui->lineEdit->text().toLocal8Bit().data(),notation,10);
        num_second = temp_1.toInt();
    } else if (notation == 8)
    {
        temp_1 = ConvertCC(ui->lineEdit->text().toLocal8Bit().data(),notation,10);
        num_second = temp_1.toInt();
    } else if (notation == 16)
    {
        temp_1 = ConvertCC(ui->lineEdit->text().toLocal8Bit().data(),notation,10);
        num_second = temp_1.toInt();
    } else
    {
        num_second = ui->lineEdit->text().toInt();
    }

    qDebug() << "second num =" << num_second;

    if (ui->button_plus->isChecked())
    {
        answer = num_first + num_second;
        ui->button_plus->setChecked(false);
    } else if (ui->button_minus->isChecked())
    {
        answer = num_first - num_second;
        ui->button_minus->setChecked(false);
    } else if (ui->button_divide->isChecked())
    {
        answer = num_first / num_second;
        ui->button_divide->setChecked(false);
    } else if (ui->button_multiplie->isChecked())
    {
        answer = num_first * num_second;
        ui->button_multiplie->setChecked(false);
    }
    qDebug() << "answer before convert" << answer;


    if (notation == 2)
    {
        temp_2 = ConvertCC(QString::number(answer).toLocal8Bit().data(),10,notation);
        answer = temp_2.toInt();
    } else if (notation == 8)
    {
        temp_2 = ConvertCC(QString::number(answer).toLocal8Bit().data(),10,notation);
        answer = temp_2.toInt();
    } else if (notation == 16)
    {
        temp_2 = ConvertCC(QString::number(answer).toLocal8Bit().data(),10,notation);
        answer = temp_2.toInt();
    }
    qDebug() << "Answer =" << answer;
    ui->lineEdit->setText(QString::number(answer, 'g', 50));
}

void MainWindow::on_button_ac_clicked()
{
    ui->lineEdit->setText("");
    num_first = num_second = 0;
    ui->lineEdit->setText("0");
    ui->button_plus->setChecked(false);
    ui->button_minus->setChecked(false);
    ui->button_divide->setChecked(false);
    ui->button_multiplie->setChecked(false);
}

void MainWindow::change_labels(QString text)
{
    QString tmp = ConvertCC(text.toLocal8Bit().data(),notation,2);
    ui->label_bin->setText(tmp);

    tmp = ConvertCC(text.toLocal8Bit().data(),notation,8);
    ui->label_oct->setText(tmp);

    tmp = ConvertCC(text.toLocal8Bit().data(),notation,10);
    ui->label_dec->setText(tmp);

    tmp = ConvertCC(text.toLocal8Bit().data(),notation,16);
    ui->label_hex->setText(tmp);

}
