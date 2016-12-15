#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void ifStmt(QVector<QString> ::iterator pointerToCurrentToken);
    void assignStmt(QVector<QString> ::iterator pointerToCurrentToken);
    void writeStmt(QVector<QString> ::iterator pointerToCurrentToken);
    void exp ();
    void stmtSequnce();
    void addOp(QVector<QString> ::iterator pointerToCurrentToken);
    void mulOp(QVector<QString> ::iterator pointerToCurrentToken);
    void  match (QVector<QString> ::iterator pointerToCurrentToken,QString expectedToken);
private slots:
    void on_pushButton_clicked();

    void on_textEdit_destroyed();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();


private:
    Ui::MainWindow *ui;

    QVector<QString> ::iterator it;
    int index;
    QVector <QString>parserInput;
};

#endif // MAINWINDOW_H
