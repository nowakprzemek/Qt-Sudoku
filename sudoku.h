#ifndef SUDOKU_H
#define SUDOKU_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>

namespace Ui {
class Sudoku;
}

class Sudoku : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sudoku(QWidget *parent = nullptr);
    ~Sudoku();

    void initNewGame();

private:
    Ui::Sudoku *ui;

    //QPushButton *m_push;
    QVector<QPushButton *> m_board;
    QVector<QString> m_goodBoard;

private:

};

#endif // SUDOKU_H
