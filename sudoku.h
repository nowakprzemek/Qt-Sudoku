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
    void setFont(QPushButton *button);
    void setStyle(QPushButton *button);
    bool checkWinCondition(QVector<QPushButton *> m_board, QVector<QString> m_goodBoard);


private:
    Ui::Sudoku *ui;

    QVector<QPushButton *> m_board;
    QVector<QString> m_goodBoard;
    QPushButton *m_push;

private slots:
    void clickedButton(int index);
    void handleGameOver();

signals:
     void gameOver();
};

#endif // SUDOKU_H
