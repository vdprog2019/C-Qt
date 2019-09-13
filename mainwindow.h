#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
     void signalFromButton(int buttonID);    // Сигнал для передачи номер нажатой кнопки


private:
    Ui::MainWindow *ui;

protected:
    bool isLastX;
    short winsOfX = 0;
    short winsOfY = 0;
    QLabel *stat;
    QPushButton *but= new QPushButton[9];
    QPushButton *start = new QPushButton;
    void generateField();
    bool isWinColomn();
    bool isWinRow();
    bool isWinDiagonal();
    bool isWinReverseDiagonal();
    void checkWin();
private slots:
    void slotButtonPush();     // Слоты-обработчики нажатий кнопок
    void slotButStartGame();
};

#endif // MAINWINDOW_H
