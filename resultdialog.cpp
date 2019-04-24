#include "resultdialog.h"
#include "sudoku.h"

#include <QLabel>
#include <QDebug>
#include <QRegularExpression>
#include <QDialogButtonBox>

const int XSIZE = 410;
const int YSIZE = 110;

ResultDialog::ResultDialog(QWidget *parent) :
    QDialog (parent)
{
    initialiseWindow();
    connect(textEdit, &QLineEdit::textChanged, this, &ResultDialog::updateOKButtonState);
    connect(okButton, &QPushButton::clicked, this, &ResultDialog::sendValue);
    //updateOKButtonState();
}

ResultDialog::~ResultDialog()
{

}

void ResultDialog::setResult(const QString &str)
{
    textEdit->setText(str);
}

QString ResultDialog::getResult() const
{
    //qDebug() << "fff" << textEdit->text();
    return textEdit->text();
}

void ResultDialog::initialiseWindow()
{
    resize(XSIZE,YSIZE);
    setWindowTitle("Podaj liczbe:");
    QLabel *label = new QLabel("Podaj liczbe, ktora chcesz wpisac do wyznaczonego pola : ", this);
    label->setGeometry(QRect(15,15,350,45));

    QFont font;
    font.setPixelSize(12);
    font.setFamily("Helvetica");

    label->setFont(font);
    label->show();
    textEdit = new QLineEdit(this);
    textEdit->setGeometry(QRect(340, 25,50,25));
    textEdit->setAlignment(Qt::AlignCenter);
    textEdit->show();
    okButton = new QPushButton("OK", this);
    okButton->setGeometry(QRect(XSIZE / 2 - 90 / 2, 55,90,35));
    okButton->setDisabled(true);
    okButton->show();

}

void ResultDialog::updateOKButtonState()
{
    if(textEdit->text().toInt() > 0 && textEdit->text().toInt() < 10 && !textEdit->text().contains("0"))
    {
        okButton->setEnabled(true);
    }
    else {
        okButton->setDisabled(true);
    }
}

void ResultDialog::sendValue()
{
    setResult(textEdit->text());
    emit accept();
}
