#include "sudoku.h"
#include "ui_sudoku.h"

#include <QDebug>
#include <QFile>
#include <QMessageBox>

const int SIZE = 470;
const int STARTINGXPOINT = 2;
const int STARTINGYPOINT = 2;
const int CUBESIZE = 50;
const int LINESIZE = 2;


Sudoku::Sudoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sudoku)
{
    ui->setupUi(this);
    resize(SIZE,SIZE);
    setMinimumSize(QSize(SIZE,SIZE));
    setMaximumSize(QSize(SIZE,SIZE));
    setWindowIcon(QIcon(":/images/sudoku-icon"));


    QPixmap background(":/images/sudoku");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            //QPushButton *m_push = new QPushButton(QString::number(j + 1 + (i * 9)), this);
            QPushButton *m_push = new QPushButton(" ", this);
            m_push->setGeometry(QRect(STARTINGXPOINT + j * (LINESIZE + CUBESIZE),STARTINGYPOINT + i * (LINESIZE + CUBESIZE), CUBESIZE, CUBESIZE));
            //m_push->setStyleSheet("border:none");

            m_push->setStyleSheet("QPushButton:pressed {"
                                  "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa);}");
            m_board.append(m_push);

            m_push->show();
        }
    }

    initNewGame();

    //qDebug() << m_board.size();
    //qDebug() << m_goodBoard;

}

Sudoku::~Sudoku()
{
    delete ui;
}


void Sudoku::initNewGame()
{
    QFile file("D:\\QtProjects\\Sudoku\\GameBoards.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(nullptr,"Information", file.errorString());
    }

    QTextStream in(&file);

    for(int i = 0; i < m_board.size(); i++)
    {
        if(in.readLine().contains('t'))
        {
            QString str = in.readLine();
            m_board[i]->setText(str);
            m_board[i]->setStyleSheet("border:none");
            m_goodBoard.append(str);
        }
        else {
            QString str = in.readLine();
            //m_board[i]->setText(str);
            m_goodBoard.append(str);
        }
    }
}

