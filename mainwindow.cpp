#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->isLastX = true;

    this->stat = new QLabel();
    this->stat->setParent(this);
    this->stat->setGeometry(140, 10, 150, 50);
    this->stat->setText("пока никто не выиграл");

    this->start = new QPushButton;
    this->start->setParent(this);
    this->start->setGeometry(10, 10,100,50);
    this->start->setText("New Game");
    connect(start, SIGNAL(clicked()), this, SLOT(slotButStartGame()));

    generateField();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotButtonPush()
{
    this->isLastX = !this->isLastX;
    QString *str = new QString ("background-color: ");
    str->append(this->isLastX == true? "red" : "green");

    QPushButton *tmp = qobject_cast<QPushButton*>(this->sender());
    tmp->setText( emit this->isLastX == false ? "X" : "O");
    tmp->setStyleSheet(*str);
    tmp->disconnect();

    checkWin();

}

bool MainWindow::isWinColomn(){

    for(int i=  0 ; i < 4; i ++){
        if(this->but[i].text() == this->but[i + 1].text() )
            if(this->but[i + 1].text() == this->but[i + 2].text())
                return true;
    }
    return false;

        //QMessageBox msgBox;
        //QString *str = new QString ("Win for ");
        //str->append(this->isLastX == true? "O" : "X");
        //msgBox.setText(*str);
        //msgBox.exec();
        //msgBox.disconnect();

        //close();
}

void MainWindow::generateField(){
    const int SIZE_H = 40;
    const int SIZE_W = 40;
    int h = 140;
    int w = 110;

    for(int i = 0 ; i < 9 ; i ++){
        but[i].setParent(this);
        but[i].setText(QString::number(i));
        but[i].setGeometry(h,w,SIZE_H , SIZE_W);
        but[i].setStyleSheet("background-color: gray");
        w += 38; // каждый шаг пробел вправо на 50
        if(i%3 == 2){   // каждый трейтий шаг
            h += 38;
            w = 110;
        }
        connect(&but[i], SIGNAL(clicked()), this, SLOT(slotButtonPush()));
    }
}
bool MainWindow::isWinRow(){
    for(int i = 0; i<4; i++){
        if(this->but[i].text() == this->but[i + 3].text() )
            if(this->but[i + 3].text() == this->but[i + 6].text())
                return true;
    }
    return  false;
}

bool MainWindow::isWinDiagonal(){
    if(this->but[0].text() == this->but[4].text())
        if(this->but[4].text() == this->but[8].text())
            return true;
    return  false;
}


bool MainWindow::isWinReverseDiagonal(){
    if(this->but[2].text() == this->but[4].text())
        if(this->but[4].text() == this->but[6].text())
            return true;
    return  false;
}

void MainWindow::checkWin(){
    if(!isWinRow())
        if(!isWinColomn())
            if(!isWinDiagonal())
                if(!isWinReverseDiagonal())
                    return;
    QMessageBox msgBox;
    QString *str = new QString ("Win for ");
    str->append(this->isLastX == true? "O" : "X");
    msgBox.setText(*str);
    msgBox.exec();
    //победы
    if(!this->isLastX)
        winsOfX ++;
    else
        winsOfY ++;
    QString s("Победы X : O --> ");
    s.append(QString::number(winsOfX));
    s.append(" : ");
    s.append(QString::number(winsOfY));
    this->stat->setText(s);

    generateField();
}
void MainWindow::slotButStartGame(){
    this->isLastX = true;
    generateField();
}
