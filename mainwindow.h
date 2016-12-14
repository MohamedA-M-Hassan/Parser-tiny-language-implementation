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
    void ifStmt(QString currentToken);
    void exp ();
    void stmtSequnce();
    void mulop(QString currentToken,QString expectedToken);
    void  match (QString currentToken,QString expectedToken);
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
