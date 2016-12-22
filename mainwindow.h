#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QString>
#include <QPair>
#include <QMainWindow>
#include <QVector>
#include "treenode.h"
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QtCore>
#include <QtGui>
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
    void drawnode(TreeNode *v);
    void drawLeftNode(TreeNode * l, int x, int y);
    void drawRightNode(TreeNode * r, int x, int y);
    void drawNode(TreeNode * c);
    void drawTree(TreeNode * no);
    void match (QString expectedToken);
  private slots:
    void on_pushButton_clicked();

    void on_textEdit_destroyed();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;

    //QVector<QString> ::iterator it;
    QVector <QString>parserInput;
    QVector<QPair <QString,QString> > ::iterator it;
    QVector <QPair <QString,QString> > input;
    bool itFlag;
    TreeNode *rootOfTree=new TreeNode();
    QGraphicsScene *scene;
    int x,y;
};

#endif // MAINWINDOW_H
