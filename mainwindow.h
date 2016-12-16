#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QString>
#include <QMainWindow>
#include "treenode.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    TreeNode *exp ();
    void program();
    TreeNode *simpleExp();
    TreeNode *term();
    TreeNode *factor();
    TreeNode *stmtSequnce();
    TreeNode *ifStmt();
    TreeNode *stmt();
    TreeNode *readStmt();
    TreeNode *repeatStmt();
    TreeNode *assignStmt();
    TreeNode *writeStmt();
    void match (QString expectedToken);
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
    QVector <QString>parserInput;
    bool itFlag;
};

#endif // MAINWINDOW_H
