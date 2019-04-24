#include "resultdialog.h"
#include "sudoku.h"
#include "ui_sudoku.h"

#include <QAction>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QSignalMapper>

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



    QSignalMapper *mapper = new QSignalMapper(this);

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {

            m_push = new QPushButton(" ", this);
            m_push->setGeometry(QRect(STARTINGXPOINT + j * (LINESIZE + CUBESIZE),STARTINGYPOINT + i * (LINESIZE + CUBESIZE), CUBESIZE, CUBESIZE));

            setStyle(m_push);
            setFont(m_push);
            m_board.append(m_push);

            mapper->setMapping(m_push, m_board.count() - 1);


            connect(m_push, SIGNAL(clicked()), mapper, SLOT(map()));
        }
    }

    initNewGame();


    connect(mapper, SIGNAL(mapped(int)), this, SLOT(clickedButton(int)));
    connect(this, &Sudoku::gameOver, this, &Sudoku::handleGameOver);
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

void Sudoku::setFont(QPushButton *button)
{
    QFont font;
    font.setPixelSize(18);
    font.setFamily("Helvetica");
    font.setBold(true);
    button->setFont(font);
}

void Sudoku::setStyle(QPushButton *button)
{
    button->setStyleSheet("QPushButton:pressed {"
                          "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa);}");
}

bool Sudoku::checkWinCondition(QVector<QPushButton *> m_board, QVector<QString> m_goodBoard)
{
    bool statement = true;
    for(int i = 0; i < m_goodBoard.size(); i++)
    {
        if(m_board[i]->text() != m_goodBoard[i])
        {
            statement = false;
        }
    }
    if(statement == true) emit gameOver();
    return statement;
}



void Sudoku::clickedButton(int index)
{
    QPushButton *button = m_board[index];
    ResultDialog *dialog = new ResultDialog(this);

    if(dialog->exec() == QDialog::Rejected) return;
    button->setText(dialog->getResult());
    checkWinCondition(m_board, m_goodBoard);
}

void Sudoku::handleGameOver()
{
    QString message = "Jestes mistrzem sudoku! Gratulacje!";
    QMessageBox::information(this, tr("Wygrana!"), message);
}

