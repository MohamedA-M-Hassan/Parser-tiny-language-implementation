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
//#include <QQueue>



using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene=new QGraphicsScene(this);
    // hide
    ui->tableWidget->hide();
   // ui->label_2->hide();
    ui->pushButton_2->hide();
    ui->pushButton_6->hide();
    ui->tableWidget->hide();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}
QVector<QString> ::iterator it;

void MainWindow::on_pushButton_clicked()
{

    it = NULL;

    using namespace std;
    // as it is a glbal variable: to ensure every time i click, i restart it
    parserInput.clear();
    input.clear();

    if ( ui->textEdit->toPlainText()==NULL)
        {
            QMessageBox msgBox;
            msgBox.setText("stop playing xD\n insert ur code");
            msgBox.exec();
        }

    else{
            QString text = ui->textEdit->toPlainText(); // read the input
            //QVector <pair <QString,QString> > input;
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
                             input.push_back({"+","Plus"});
                             parserInput.push_back("Plus");
                             //outputToken["+"]="PLUS";
                         }
                         else if (text[i]=='-') {
                             input.push_back({"-","Minus"});
                             parserInput.push_back("Minus");
                             //outputToken["-"]="MINUS";
                         }
                         else if (text[i]=='/') {
                            input.push_back({"/","Divide"});
                            parserInput.push_back("Divide");
                            // outputToken["/"]="DIVIDE";
                         }
                         else if (text[i]=='*') {
                            input.push_back({"*","Multiple"});
                            parserInput.push_back("Multiple");
                            //outputToken["*"]="MULTIPLE";
                         }
                         else if (text[i]==';') {
                            input.push_back({";","SemiColon"});
                            parserInput.push_back("SemiColon");
                            //outputToken[";"]="SEMI";
                         }
                         else if ( text[i]== '.'){
                            input.push_back({".","DOT"});
                            parserInput.push_back("DOT");
                         }
                         else if ( text[i]== '<'){
                            input.push_back({"<","SmallerThan"});
                            parserInput.push_back("SmallerThan");
                         }
                         else if ( text[i]=='>')
                         {
                             input.push_back({">","GreaterThan"});
                             parserInput.push_back("GreaterThan");
                         }
                         else if ( text[i]=='=')
                         {
                             input.push_back({"=","Equal"});
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
                         input.push_back({myCharContainer,type});
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
            //ui->label_2->show();

            for (QVector< QPair <QString,QString> >::iterator i=input.begin(); i != input.end(); i++){
                ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
                QTableWidgetItem *newItem1 = new QTableWidgetItem(i->first);
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, newItem1);
                QTableWidgetItem *newItem2 = new QTableWidgetItem(i->second);
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, newItem2);
            }

            /////////////////////////////////////////////////////////////////////
            // parser part
            ui->pushButton_6->show();
            ui->graphicsView->show();
            it =input.begin();
            itFlag=true;
            if(input.size()==1)
            {
                QMessageBox msgBox;
                msgBox.setText("please study tiny lang. then back\n as there is syntax error");
                msgBox.exec();

                ui->tableWidget->hide();
         //       ui->label_2->hide();
                ui->pushButton_2->hide();
                ui->tableWidget->hide();
                ui->textEdit->clear();
                // ui->tableWidget->clear();
                ui->tableWidget->setRowCount(0);
                ui->tableWidget->hide();
   //             ui->label_2->hide();
                parserInput.clear();

            }
            else rootOfTree=stmtSequnce();
            int x =3;
               x =3;
               x =3;
               x =3;
               x =3;
               x =3;
               x =3;
               x =3;
               x =3;


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
    if (it->second=="SemiColon")
    {
        match("SemiColon");
        stmtSeq->setBehind(stmtSequnce());
    }
    return stmtSeq;
}

//fn No.3
TreeNode *MainWindow::stmt()
{
    TreeNode *stmt= new TreeNode();//TreeNode("stmt")
    if(it->second == "if")
    {
        stmt=ifStmt(); //stmt->setRight(ifStmt();
    }
    else if(it->second == "repeat")
    {
       stmt=repeatStmt(); // //stmt->setRight(repeatStmt();
    }
    else if (it->second =="identefier")
    {
        stmt=assignStmt();//stmt->setRight(assignStmt();
    }
    else if(it->second == "read")
    {
       stmt=readStmt();//stmt->setRight(readStmt();
    }
    else if (it->second == "write")
    {
        stmt=writeStmt();//stmt->setRight(writeStmt();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.exec();

        ui->tableWidget->hide();
 //       ui->label_2->hide();
        ui->pushButton_2->hide();
        ui->tableWidget->hide();
        ui->textEdit->clear();
        // ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->hide();
//        ui->label_2->hide();
        parserInput.clear();

        //exit(0);
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
    if(it->second=="else")
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
    temp->setDataValue("("+it->first+")");
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
    match("identefier");
    //read->setDataValue("("+it->second+")");
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
    while(it->second == "SmallerThan" || it->second == "Equal" )
    {
        TreeNode *temp= new TreeNode;
        temp->setDataKey("OP");
        temp->setDataValue("("+it->first+")");
        temp->addChildren(exp);
        match(it->second);
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
    while(it->second=="Plus" || it->second=="Minus")
    {
        TreeNode *temp= new TreeNode;
        temp->setDataKey("OP");
        temp->setDataValue("("+it->first+")");
        temp->addChildren(simpleExp);
        match(it->second);
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
    while(it->second=="Multiple" || it->second=="Divide")
    {
        TreeNode *temp = new TreeNode();
        temp->setDataKey("OP");
        temp->setDataValue("("+it->first+")");
        temp->addChildren(term);
        match(it->second);
        term=temp;
        term->addChildren(factor());
    }
    return term;
}

//fn No.12
TreeNode *MainWindow::factor()
{
    TreeNode *temp=new TreeNode();
    if(it->second=="(")
    {
        match("(");
        temp = exp();
        match(")");
        return temp;
    }
    else if(it->second=="identefier")
    {
        temp->setDataKey("Id");
        temp->setDataValue("("+it->first+")");
        //temp->setRoot(NULL);
        match("identefier");
        return temp;
    }
    else if(it->second=="Number")
    {
        temp->setDataKey("const");
        temp->setDataValue(it->first);
        match("Number");
        return temp;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.exec();


        ui->tableWidget->hide();
     //   ui->label_2->hide();
        ui->pushButton_2->hide();
        ui->tableWidget->hide();
        ui->textEdit->clear();
        // ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->hide();
 //       ui->label_2->hide();
        input.clear();

        //exit(0);
    }

}

// fn No 16
void  MainWindow::match (QString expectedToken)
{
     if (it->second == expectedToken)
        {
            it++;
            if (it== input.end())
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


            ui->tableWidget->hide();
 //           ui->label_2->hide();
            ui->pushButton_2->hide();
            ui->tableWidget->hide();
            ui->textEdit->clear();
            // ui->tableWidget->clear();
            ui->tableWidget->setRowCount(0);
            ui->tableWidget->hide();
 //           ui->label_2->hide();
            input.clear();


            //exit(0);
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
    scene->clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->hide();
    //s  ui->label_2->hide();
    //-------------------
    // parser part
    // as it is a glbal variable: to ensure every time i click, i restart it
    parserInput.clear();
    input.clear();
    it=NULL;
    ui->graphicsView->hide();
    ui->pushButton_6->hide();
}

/*
void MainWindow :: drawLeftNode(TreeNode * l, int x, int y)
{
    scene->addLine(x,y,x-40,y+30);
    scene->addRect(x-40,y+30,80,30);
    scene->addSimpleText(l->getDataValue())->setPos(x-5,y+30);

}
void MainWindow :: drawRightNode (TreeNode * r, int x, int y)
{
    scene->addLine(x+80,y,x+120,y+30);
    scene->addRect(x+80,y+30,80,30);
    scene->addSimpleText(r->getDataValue())->setPos(x+100,y+40);
}

void MainWindow ::drawCenterNode(TreeNode * c, int x, int y)
{
    scene->addLine(x+40,y,x+40,y+40);
    y+=40;
    scene->addRect(x,y,80,30);
    scene->addSimpleText(c->getDataValue())->setPos(x+20,y+10);

}

void MainWindow :: drawnode(TreeNode * v)
{
    int x= 0,y=0,width=80,length=30;
    bool left =true,right=false;
    scene->addRect(x,y,width,length);
    scene->addSimpleText(v->getDataKey())->setPos(x+15,y+10);
    y+=length;
    QVector<TreeNode*> childs = v->getChildren();
    TreeNode *node=v;
    QVector<TreeNode*> temp = v->getChildren();
    temp=childs;
    int index =0 ;
    bool first =true;
    while(node->getCountChildren()>0)
      {

        for(int i =0 ; i<node->getCountChildren();i++)
        {
            if(node->getCountChildren()==1)
            {
                drawRightNode(childs[i],x,y);
            }
            else
            {
                if(left){drawLeftNode(childs[i],x,y);}
                if(right){drawRightNode(childs[i],x,y);}//x+=60;y+=60;}

            }
            left = !left;
            right =!right;
        }
        first=false;
        x-=40;y+=60;
        childs =temp;
        node=childs[index];
        childs=childs[index]->getChildren();
        index++;
        if(index==2){index=0;temp=childs;x+=140;y-=60;}
<<<<<<< HEAD
    }
}*/

/////////////////
void MainWindow::drawTree(TreeNode * no)
{
    drawNode(no);
    int noOfChildren= no->getCountChildren();
    QVector <TreeNode*> trial= no->getChildren();
    TreeNode *child=new TreeNode();
    if(noOfChildren >= 1)
    {
        child=trial[0];
        child->setPosition(0);
        drawTree(child);
        //delete trial;
    }
    if(noOfChildren >= 2)
    {
        child=trial[1];
        child->setPosition(1);
        drawTree(child);
        //delete trial;
    }
     if(noOfChildren==3)
    {
         child=trial[2];
         child->setPosition(2);
         drawTree(child);
    }

    if(no->getBehind()!=NULL)
    {
       drawTree(no->getBehind());
    }
}
void MainWindow::drawNode(TreeNode * no)
{
    if(no == NULL)
    {

        scene->clear();
    }
    else
    {
        QPen pen;
        QFont font;
        font.bold();
        font.setPixelSize(12);
        pen.setWidth(1);
        if(no->getDataKey() == "if" || no->getDataKey() == "write"
                                    || no->getDataKey() == "repeat"
                                    || no->getDataKey() == "read"
                                    || no->getDataKey() == "assign")
        {
            scene->addRect(x,y,70,50);
            scene->addSimpleText(no->getDataKey(),font)->setPos(x+20,y+10);
            x +=40;
            y +=40;
        }
        else
        {
            if (no->getPosition()==0)
            {
                scene->addEllipse(x-40,y+40,70,50);
                scene->addSimpleText(no->getDataKey(),font)->setPos(x+20,y+10);
                scene->addSimpleText(no->getDataValue(),font)->setPos(x+20,y+25);
                x +=30;
                //y +=30;
            }
            else if (no->getPosition()==1)
            {
                scene->addEllipse(x+35,y+40,70,50);
                scene->addSimpleText(no->getDataKey(),font)->setPos(x+20,y+10);
                scene->addSimpleText(no->getDataKey(),font)->setPos(x+20,y+25);
                x +=30;
                y +=30;
            }
       }
    }
}
/*void MainWindow ::drawNode(TreeNode * c)
{
    scene->addLine(x+40,y,x+40,y+40);
    y+=40;
    scene->addRect(x,y,80,30);
    scene->addSimpleText(c->getDataKey())->setPos(x+20,y+10);

}*/
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
  x =-200; y=-200;
  drawTree(rootOfTree);


}
