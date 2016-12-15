#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "treenode.h"
// to insert from file
    #include <QFileDialog>
    #include <QFile>
    #include <QTextStream>
    #include <QMessageBox>

#include <QString>
#include <QMap>
#include <QQueue>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // hide
    ui->tableWidget->hide();
    ui->label_2->hide();
    ui->pushButton_2->hide();
    ui->textBrowser->hide();
    ui->tableWidget->hide();
   // ui->pushButton_6->hide();
    //void ifStmt(QString currentToken);
}

MainWindow::~MainWindow()
{
    delete ui;
}
QVector<QString> ::iterator it;

void MainWindow::on_pushButton_clicked()
{


    using namespace std;
    // as it is a glbal variable: to ensure every time i click, i restart it
    parserInput.clear();

    QString text = ui->textEdit->toPlainText(); // read the input

    QMap<QString,QString> token;
    token["if"]     ="if";
    token["then"]   ="then";
    token["end"]    ="end";
    token["until"]  ="until";
    token["write"]  ="write";
    token["else"]   ="else";
    token["repeat"] ="repeat";
    token["read"]   ="read";

    enum state{start,inComment,inID,inNum,inAssign,done};
    state s=start;

    QString myCharContainer="";

    QVector <pair <QString,QString> > answer;
    QString type;
    //////////////////////////////////////////
    // scanner part
    for (int i = 0 ;i < (text.size()+1);i++){
     //   QChar ch = text[i];
        label:  switch (s) {   // the label to not waste the current char
                               // or u can use (i--) instead of (goto)
          case start:
                 myCharContainer="";
                 // comment
                 if (text[i]=='{')
                 {
                    //myCharContainer=myCharContainer+text[i];
                    s=inComment;
                 }
                 // assign
                 else if (text[i]==':') {
                    myCharContainer=myCharContainer+text[i];
                    s=inAssign;
                 }
                 // alphapitic
                 else if (text[i].isLetter())
                 {
                     myCharContainer=myCharContainer+text[i];
                     s=inID;
                 }
                 //  numbers
                 else if (text[i].isDigit())
                 {
                    myCharContainer=myCharContainer+text[i];
                    s=inNum;
                 }
                 else if (text[i]=='+') {
                     answer.push_back({"+","Plus"});
                     parserInput.push_back("PLUS");
                     //outputToken["+"]="PLUS";
                 }
                 else if (text[i]=='-') {
                     answer.push_back({"-","Minus"});
                     parserInput.push_back("MINUS");
                     //outputToken["-"]="MINUS";
                 }
                 else if (text[i]=='/') {
                    answer.push_back({"/","Divide"});
                    parserInput.push_back("DIVIDE");
                    // outputToken["/"]="DIVIDE";
                 }
                 else if (text[i]=='*') {
                    answer.push_back({"*","Multiple Operator"});
                    parserInput.push_back("MULTIPLE");
                    //outputToken["*"]="MULTIPLE";
                 }
                 else if (text[i]==';') {
                    answer.push_back({";","SemiColon"});
                    parserInput.push_back("SEMIColon");
                    //outputToken[";"]="SEMI";
                 }
                 else if ( text[i]== '.'){
                    answer.push_back({".","DOT"});
                    parserInput.push_back("DOT");
                 }
                 else if ( text[i]== '<'){
                    answer.push_back({"<","SmallerThan"});
                    parserInput.push_back("SmallerThan");
                 }
                 else if ( text[i]=='>')
                 {
                     answer.push_back({">","GreaterThan"});
                     parserInput.push_back("GreaterThan");
                 }
                 else if ( text[i]=='=')
                 {
                     answer.push_back({"=","equal"});
                     parserInput.push_back("Equal");
                 }
                break;


           case inAssign:
                   if (text[i]=='=')
                   {
                       myCharContainer= myCharContainer+(text[i]);
                        type="assignment operator";

                   }
                   else{
                        i--;
                        type="Colon";
                   }
                   s=done;
                   goto label;
                          // or u can use (i--) instead of (goto)
                   break;
           case inComment:
                    while (text[i] !='}')
                        { i++;}
                    s=start;
                    break;
           case inNum:
                    while (text[i].isDigit())
                    {
                        myCharContainer=myCharContainer+text[i];
                        i++;
                    }
                    i--;
                    //outputToken[myCharContainer]="Number";
                    type="Number";
                    s=done;
                    //s=start;
                    goto label;
                     break;
           case inID:
                     while (text[i].isLetter()||text[i].isDigit())
                     {
                         myCharContainer=myCharContainer+text[i];
                         i++;
                     }
                     i--;
                     if (token.find(myCharContainer)!=token.end())
                     {
                         type=token[myCharContainer];
                     }
                     else type="identefier";
                     s=done;
                    goto label;
            break;

          case done:
                 //container.push_back(myCharContainer);
                 answer.push_back({myCharContainer,type});
                 parserInput.push_back(type);
                 s=start;
           break;
          }
      }

     /*   // to get the Reserved word and the Identefier
      for(QVector<QString>::iterator vec = container.begin(); vec != container.end(); vec++) {
          for (QMap<QString,QString>::iterator mp=token.begin();mp!=token.end(); mp++) {
              if (vec ==mp.key() )
              {
                  outputToken[mp.key()]=mp.value();
                  break;
              }
              else outputToken[*vec]="IDENTEFIER";
           }
      }*/
    /* //to print in textBrowser not so good
    ui->textBrowser->setText("Symbol       ||    TokenType");// added so when you repeat the use of the button just restart w mtkmlsh 3la el2dyym

    for (QVector< pair <QString,QString> >::iterator it=answer.begin(); it != answer.end(); it++) {
        ui->textBrowser->append(it->first + "       ||    " + it->second);
    }*/
    // to print in a table
    ui->tableWidget->show();
    // ------------
    // to not repeat the data
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    //--------------------------
    ui->label_2->show();

    for (QVector< pair <QString,QString> >::iterator it=answer.begin(); it != answer.end(); it++){
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        QTableWidgetItem *newItem1 = new QTableWidgetItem(it->first);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, newItem1);
        QTableWidgetItem *newItem2 = new QTableWidgetItem(it->second);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, newItem2);
    }

    /////////////////////////////////////////////////////////////////////
    // parser part
    it = parserInput.begin();
    program();

}

// fn No.1
void MainWindow::program()
{

    stmtSequnce();
}

// fn No.2
void MainWindow::stmtSequnce()
{
    stmt();
}

//fn No.3
void MainWindow::stmt()
{
    if(*it == "if")
    {
        ifStmt();
    }
    else if(*it == "repeat")
    {
       repeatStmt();
    }
    else if (*it =="assign")
    {
        assignStmt();
    }
    else if(*it == "read")
    {
       readStmt();
    }
    else if (*it == "write")
    {
        writeStmt();
    }

}

// function No 4
void MainWindow::ifStmt()
{
    match("if");
    exp();
    match("then");
    stmtSequnce();
    if(*it=="else")
    { match("else"); stmtSequnce();}
    match("end");

}

//fn No.5
void MainWindow::repeatStmt()
{
}

// fn No 6
void MainWindow::assignStmt(){
    match("identefier");
    match("assignment operator");
    exp();
}
//fn No.7
void MainWindow::readStmt()
{
}

// fn No 8
void MainWindow::writeStmt(){
    match("write");
    exp();
}
// still empty
void MainWindow::exp (){

}


// fn No 16
void  MainWindow::match (QString expectedToken)
{
    if (*it == expectedToken)
    {
        it++;
    }
      
    else
    {  
        QMessageBox msgBox;
        msgBox.setText("Error ya s7by");
        msgBox.exec();       
    }
}

void MainWindow::on_textEdit_destroyed()
{
 //   trial = "hi";
}

void MainWindow::on_pushButton_3_clicked()
{
   close();
}


// trial Button
void MainWindow::on_pushButton_2_clicked()
{
    //ui->tableWidget->setRowCount(0);
    //ui->tableWidget->setColumnCount(0);
    //token type
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    QTableWidgetItem *newItem1 = new QTableWidgetItem("hello");
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, newItem1);
    QTableWidgetItem *newItem2 = new QTableWidgetItem("Boogy");
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, newItem2);
}
// clear button
void MainWindow::on_pushButton_4_clicked()
{
    ui->textEdit->clear();
    ui->textBrowser->clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->hide();
    ui->label_2->hide();
    //-------------------
    // parser part
    // as it is a glbal variable: to ensure every time i click, i restart it
    parserInput.clear();

}

// insert button
void MainWindow::on_pushButton_5_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "/home", tr("code file (*.txt)"));// string has the file link



    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());
    QTextStream in(&file);

    ui->textEdit->setText(in.readAll());

}

