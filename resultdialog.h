#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(QWidget *parent = nullptr);
    ~ResultDialog();

    void setResult(const QString &str);

    QString getResult() const;

private:
    void initialiseWindow();

public:
    QLineEdit *textEdit;
    QPushButton *okButton;

public slots:
    void updateOKButtonState();
    void sendValue();

};

#endif // RESULTDIALOG_H
