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
    scene=new QGraphicsScene(this);
    // hide
    ui->tableWidget->hide();
    ui->label_2->hide();
    ui->pushButton_2->hide();

    ui->tableWidget->hide();
    ui->graphicsView->setScene(scene);
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

    if ( ui->textEdit->toPlainText()==NULL)
        {
            QMessageBox msgBox;
            msgBox.setText("stop playing xD\n insert ur code");
            msgBox.exec();
        }

    else{
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
                         //  Numbers
                         else if (text[i].isDigit())
                         {
                            myCharContainer=myCharContainer+text[i];
                            s=inNum;
                         }
                         else if (text[i]=='+') {
                             answer.push_back({"+","Plus"});
                             parserInput.push_back("Plus");
                             //outputToken["+"]="PLUS";
                         }
                         else if (text[i]=='-') {
                             answer.push_back({"-","Minus"});
                             parserInput.push_back("Minus");
                             //outputToken["-"]="MINUS";
                         }
                         else if (text[i]=='/') {
                            answer.push_back({"/","Divide"});
                            parserInput.push_back("Divide");
                            // outputToken["/"]="DIVIDE";
                         }
                         else if (text[i]=='*') {
                            answer.push_back({"*","Multiple"});
                            parserInput.push_back("Multiple");
                            //outputToken["*"]="MULTIPLE";
                         }
                         else if (text[i]==';') {
                            answer.push_back({";","SemiColon"});
                            parserInput.push_back("SemiColon");
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
            itFlag=true;
            if(parserInput.size()==1)
            {
                QMessageBox msgBox;
                msgBox.setText("please study tiny lang. then back\n as there is syntax error");
                msgBox.exec();
            }
            else rootOfTree=stmtSequnce();

    }
}

// fn No.1
/*void MainWindow::program()
{
      TreeNode * n= stmtSequnce();
}*/

// fn No.2
TreeNode *MainWindow::stmtSequnce()
{
    TreeNode *stmtSeq = new TreeNode();
    stmtSeq=stmt();
    if (*it=="SemiColon")
    {
        match("SemiColon");
        stmtSeq->setBehind(stmt());
    }
    return stmtSeq;
}

//fn No.3
TreeNode *MainWindow::stmt()
{
    TreeNode *stmt= new TreeNode();//TreeNode("stmt")
    if(*it == "if")
    {
        stmt=ifStmt(); //stmt->setRight(ifStmt();
    }
    else if(*it == "repeat")
    {
       stmt=repeatStmt(); // //stmt->setRight(repeatStmt();
    }
    else if (*it =="identefier")
    {
        stmt=assignStmt();//stmt->setRight(assignStmt();
    }
    else if(*it == "read")
    {
       stmt=readStmt();//stmt->setRight(readStmt();
    }
    else if (*it == "write")
    {
        stmt=writeStmt();//stmt->setRight(writeStmt();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.exec();
        exit(0);
    }
    return stmt;
}

// function No 4
TreeNode *MainWindow::ifStmt()
{
    TreeNode *temp = new TreeNode("if");
    match("if");
    temp->addChildren(exp());
    match("then");
    temp->addChildren(stmtSequnce());
    if(*it=="else")
    { match("else");
      temp->addChildren(stmtSequnce());}
    match("end");
    return temp;
}

//fn No.5
TreeNode *MainWindow::repeatStmt()
{
    TreeNode *repeat = new TreeNode("repeat");
    match("repeat");
    repeat->addChildren(stmtSequnce());
    match("until");
    repeat->addChildren(exp());
    return repeat;
}

// fn No 6
TreeNode *MainWindow::assignStmt(){
    TreeNode *temp = new TreeNode("assign");
    match("identefier");
    match("assignment operator");
    temp->addChildren(exp());
    return temp;
}
//fn No.7
TreeNode *MainWindow::readStmt()
{
    TreeNode *read = new TreeNode("read");
    match("read");
    match("identefier");read->setDataValue("identefier");
    return read;
}

// fn No 8
TreeNode *MainWindow::writeStmt(){
    TreeNode *temp=new TreeNode("write");
    match("write");
    temp->addChildren(exp());
    return temp;
}
// fn No.9
TreeNode *MainWindow::exp()
{
    TreeNode *exp = new TreeNode();
    exp=simpleExp();
    while(*it == "SmallerThan" || *it == "Equal" )
    {
        TreeNode *temp= new TreeNode;
        temp->setDataKey(*it);
        temp->addChildren(exp);
        match(*it);
        exp=temp;
        exp->addChildren(simpleExp());
    }
    return exp;
}

//fn No.10
TreeNode *MainWindow::simpleExp()
{
    TreeNode *simpleExp= new TreeNode;
    simpleExp=term();
    while(*it=="Plus" || *it=="Minus")
    {
        TreeNode *temp= new TreeNode;
        temp->setDataKey(*it);
        temp->addChildren(simpleExp);
        match(*it);
        simpleExp=temp;
        simpleExp->addChildren(term());
    }
    return simpleExp;
}

//fn No.11
TreeNode *MainWindow::term()
{
    TreeNode *term = new TreeNode();
    term=factor();
    while(*it=="Multiple" || *it=="Divide")
    {
        TreeNode *temp = new TreeNode();
        temp->setDataKey(*it);
        temp->addChildren(term);
        match(*it);
        term=temp;
        term->addChildren(factor());
    }
    return term;
}



//fn No.12
TreeNode *MainWindow::factor()
{
    TreeNode *temp=new TreeNode();
    if(*it=="(")
    {
        match("(");
        temp = exp();
        match(")");
        return temp;
    }
    else if(*it=="identefier")
    {
        temp->setDataKey(*it);
        //temp->setDataValue(NULL);
        //temp->setRoot(NULL);
        match("identefier");
        return temp;
    }
    else if(*it=="Number")
    {
        temp->setDataKey(*it);
        //temp->setDataValue(NULL);
        //temp->setRoot(NULL);
        match("Number");
        return temp;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.exec();
        exit(0);
    }

}

// fn No 16
void  MainWindow::match (QString expectedToken)
{
     if (*it == expectedToken)
        {
            it++;
            if (it== parserInput.end())
            {it--;
                int c=3;
                c=4+4;}

                //itFlag=false;
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Oh, there is an error\n ");
            msgBox.exec();
            exit(0);
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

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->hide();
    ui->label_2->hide();
    //-------------------
    // parser part
    // as it is a glbal variable: to ensure every time i click, i restart it
    parserInput.clear();

}
void MainWindow :: drawLeftNode(TreeNode * l, int x, int y)
{
    scene->addLine(x,y,x-40,y+30);
    scene->addRect(x-40,y+30,80,30);
    scene->addSimpleText(l->getDataKey())->setPos(x-5,y+30);

}
void MainWindow :: drawRightNode (TreeNode * r, int x, int y)
{
    scene->addLine(x+80,y,x+120,y+30);
    scene->addRect(x+80,y+30,80,30);
    scene->addSimpleText(r->getDataKey())->setPos(x+100,y+40);
}

void MainWindow ::drawCenterNode(TreeNode * c, int x, int y)
{
    scene->addLine(x+40,y,x+40,y+40);
    y+=40;
    scene->addRect(x,y,80,30);
    scene->addSimpleText(c->getDataKey())->setPos(x+20,y+10);

}

void MainWindow :: drawnode(TreeNode * v)
{
    int x= -170,y=-110,width=80,length=30;
    bool left =true,right=false;
    scene->addRect(x,y,width,length);
    scene->addSimpleText(v->getDataKey())->setPos(x+15,y+10);
    y+=length;
    QVector<TreeNode*> childs = v->getChildren();

        for(int i =0 ; i<v->getCountChildren();i++)
        {
            if(v->getCountChildren()==1)
            {
                drawRightNode(childs[i],x,y);
            }
            else
            {
                if(left)
                {
                    int tempX=x,tempY=y;
                    drawLeftNode(childs[i],x,y);
                    x-=40;
                    y+=60;
                    for(int j = 0 ;j < childs[i]->getCountChildren();j++)
                    {
                        if(childs[i]->getCountChildren()==1)
                        {
                            drawRightNode(childs[i]->getChildrenByIndex(childs[i]->getChildren(),j),x,y);
                        }
                        else{
                            if(left)
                            {

                                drawLeftNode(childs[i]->getChildrenByIndex(childs[i]->getChildren(),j),x,y);

                            }
                            if(right)
                            {
                                drawRightNode(childs[i]->getChildrenByIndex(childs[i]->getChildren(),j),x,y);
                            }
                        }
                        left = !left;
                        right =!right;


                    }
                    x=tempX;
                    y=tempY;
                }

                if(right)
                {
                    int tempX=x,tempY=y;
                    drawRightNode(childs[i],x,y);
                    x+=60;
                    y+=60;
                    for(int j = 0 ;j < childs[i]->getCountChildren();j++)
                    {
                        if(childs[i]->getCountChildren()==1)
                        {
                            drawRightNode(childs[i]->getChildrenByIndex(childs[i]->getChildren(),j),x,y);

                        }
                        else
                        {
                            if(left)
                            {

                                drawLeftNode(childs[i]->getChildrenByIndex(childs[i]->getChildren(),j),x,y);

                            }
                            if(right)
                            {
                                drawRightNode(childs[i]->getChildrenByIndex(childs[i]->getChildren(),j),x,y);
                            }
                        }
                        left = !left;
                        right =!right;


                    }
                    x=tempX;
                    y=tempY;
                }

             }

            left = !left;
            right =!right;


    }
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


void MainWindow::on_pushButton_6_clicked()
{

  drawnode(rootOfTree);

}
