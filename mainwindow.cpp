#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_form.h"
#include <iostream>
#include <vector>
#include "UIManager.h"
using namespace std;

MainWindow::MainWindow(UIManager* uiM, QApplication * ap, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), a(ap), userID(""), userType(""), exit(true), year(""), term(""), courseName(""), uiMan(uiM)
{
    ui->setupUi(this);
    uiMan->sendYears();
    QStringList yearList;
    foreach (string str, QVector<string>::fromStdVector (uiMan->yLis)) {
        yearList <<  QString::fromStdString(str);
    }
    uiMan->yLis.clear();
    ui->YearBox_2->insertItems(0, yearList);

    ui->AvailableRadioButto_chS->setChecked(true);
    ui->AvailableRadioButton->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

string MainWindow::getUserID(){
    return userID;
}

string MainWindow::getUserType(){
    return userType;
}
string MainWindow::getYear(){
    return year;
}
string MainWindow::getTerm(){
    return term;
}

string MainWindow::getCourseName(){
    return courseName;
}

bool MainWindow::exited(){
    return exit;
}

void MainWindow::on_LoginButton_2_clicked()
{

    QString w= ui->lineEdit_2->text();
    QString y = ui->YearBox_2->currentText();
    QString t = ui->TermBox_2->currentText();
    userID= w.toUtf8().constData();
    userType= (ui->UsersBox_2->currentText()).toUtf8().constData();
    year = y.toUtf8().constData();
    term =t.toUtf8().constData();
    openCourseWindow();
}

void MainWindow::openCourseWindow(){
    vector<string> cL = uiMan->getCourseList();
    QStringList courseList;
    foreach (string str, QVector<string>::fromStdVector (cL)) {
        courseList <<  QString::fromStdString(str);
    }
    ui->CoursesList->addItems(courseList);
    ui->UserIDLabel->setText(QString::fromStdString(userID));
    ui->userTypeLabel->setText(QString::fromStdString(userType) + ": ");
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() + 1));
}

void MainWindow::on_CourseBackButton_clicked()
{
    ui->CoursesList->clear();
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() - 1));
}

void MainWindow::on_LogOutButton_clicked()
{
    ui->CoursesList->clear();
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() - 1));
}


void MainWindow::openContentsSWindow(){
    QString cName= ui->CoursesList->currentItem()->text();
    courseName = cName.toUtf8().constData();
    ui->UserIDLabel2->setText(QString::fromStdString(userID));
    ui->userTypeLabel2->setText(QString::fromStdString(userType) + ": ");
    ui->CourseNameLabel->setText("<b>" + ui->CoursesList->currentItem()->text() +"</b>");
    createContents();
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() + 1));
}
void MainWindow::openContentsCMWindow(){
    QString cName= ui->CoursesList->currentItem()->text();
    courseName = cName.toUtf8().constData();
    ui->UserIDLabelC2->setText(QString::fromStdString(userID));
    ui->userTypeLabelC2->setText(QString::fromStdString(userType) + ": ");
    ui->CourseNameLabelC->setText("<b>" + ui->CoursesList->currentItem()->text() +"</b>");
    createContentsC();
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() + 2));
}

void MainWindow::createContents(){
    int numBooks = *((int*) (uiMan->getInformation(0)));
    if(numBooks == 0){
        parseContents(new QTreeWidgetItem(ui->ContentTreeWidget, -1), -1, "There are no Books available!");
        ui->ContentTreeWidget->resizeColumnToContents(0);
        return;
    }
    uiMan->createContents();
    for(int i = 0; i < numBooks; i++){
        QTreeWidgetItem* newBook = new QTreeWidgetItem(ui->ContentTreeWidget, 0);
        parseContents(newBook,0, uiMan->bookLis[i]);
        newBook->setCheckState(0,Qt::Unchecked);
        int numChapters = *((int*) (uiMan->getInformation(0)));
        if(numChapters == 0){
            parseContents(new QTreeWidgetItem(newBook, -1), -1, "No Chapters available for sale!");
            break;
        }
        for(int j =0; j < numChapters; j++){
            QTreeWidgetItem* newChapter = new QTreeWidgetItem(newBook, 1);
            parseContents(newChapter,1, uiMan->chapterLis[j]);
            newChapter->setCheckState(0,Qt::Unchecked);
            int numSections = *((int*) (uiMan->getInformation(0)));
            if(numSections == 0){
                parseContents(new QTreeWidgetItem(newChapter, -1), -1, "No Sections available for sale!");
                break;
            }
            for(int k = 0; k < numSections; k++){
                QTreeWidgetItem* newSection = new QTreeWidgetItem(newChapter, 2);
                parseContents(newSection,2, uiMan->sectionLis[k]);
                newSection->setCheckState(0,Qt::Unchecked);
            }
        }
    }

    ui->ContentTreeWidget->resizeColumnToContents(0);
    ui->ContentTreeWidget->resizeColumnToContents(1);
    ui->ContentTreeWidget->resizeColumnToContents(2);
}

void MainWindow::createContentsC(){
    int numBooks = *((int*) (uiMan->getInformation(0)));
    if(numBooks == 0){
        parseContents(new QTreeWidgetItem(ui->ContentTreeWidgetC, -1), -1, "There are no Books available!");
        ui->ContentTreeWidgetC->resizeColumnToContents(0);
        return;
    }
    uiMan->createContents();
    for(int i = 0; i < numBooks; i++){
        QTreeWidgetItem* newBook = new QTreeWidgetItem(ui->ContentTreeWidgetC, 0);
        parseContents(newBook,0, uiMan->bookLis[i]);
        int numChapters = *((int*) (uiMan->getInformation(0)));
        if(numChapters == 0){
            parseContents(new QTreeWidgetItem(newBook, -1), -1, "No Chapters available for sale!");
            break;
        }
        for(int j =0; j < numChapters; j++){
            QTreeWidgetItem* newChapter = new QTreeWidgetItem(newBook, 1);
            parseContents(newChapter,1, uiMan->chapterLis[j]);
            int numSections = *((int*) (uiMan->getInformation(0)));
            if(numSections == 0){
                parseContents(new QTreeWidgetItem(newChapter, -1), -1, "No Sections available for sale!");
                break;
            }
            for(int k = 0; k < numSections; k++){
                QTreeWidgetItem* newSection = new QTreeWidgetItem(newChapter, 1);
                parseContents(newSection,2, uiMan->sectionLis[k]);
            }
        }
    }

    ui->ContentTreeWidgetC->resizeColumnToContents(0);
}

void MainWindow::parseContents(QTreeWidgetItem* item, int type, string info){
    size_t prev = 0, index, j=0;
    while ((index = info.find_first_of("*", prev)) != string::npos){
        if (index > prev){
            if((type != -1))
              item->setData(j++, 0, QString::fromStdString(info.substr(prev, index-prev)));
        }
        prev = index + 1;
    }
    if (prev < info.length()){
        if(type != -1)
            item->setData(j, 0, QString::fromStdString(info.substr(prev, string::npos)));
        else{
            item->setData(j, 0, QString::fromStdString(info.substr(prev, string::npos)));
            return;
        }
    }

}

void MainWindow::on_viewContentsButton_clicked()
{
    if(ui->CoursesList->currentItem() != NULL){
        if(userType == "Student")
            openContentsSWindow();
        else if (userType =="Content Manager")
            openContentsCMWindow();
    }
}


void MainWindow::on_CoursesList_itemDoubleClicked(QListWidgetItem *item)
{
    if(userType == "Student")
        openContentsSWindow();
    else if (userType =="Content Manager")
        openContentsCMWindow();
}

void MainWindow::on_ContentsBackButton_clicked()
{
    ui->ContentTreeWidget->clear();
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() - 1));
}

void MainWindow::on_LogOutButton2_clicked()
{
    ui->CoursesList->clear();
    ui->ContentTreeWidget->clear();
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() - 2));
}

void MainWindow::on_LogOutButtonC2_clicked()
{
    ui->CoursesList->clear();
    ui->ContentTreeWidgetC->clear();
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() - 3));
}

void MainWindow::on_ContentsBackButtonC_clicked()
{
    ui->ContentTreeWidgetC->clear();
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() - 2));
}

void MainWindow::on_editContentButton_clicked()
{
    if (ui->ContentTreeWidgetC->currentItem() == 0)
        return;
    if ( ui->ContentTreeWidgetC->currentItem()->type()!=0){
        ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() + 2));
        parseEdit_chs();
    }
    else{
        ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() + 1));
        parseEdit(*((string*)(uiMan->getInformation(1))));
    }
}

void MainWindow::on_SummaryButton_clicked()
{
    if (ui->ContentTreeWidget->currentItem() == 0)
        return;
    cout<< ui->ContentTreeWidget->currentItem()->text(1).toUtf8().constData()<<endl;
    parseSummary(*((string*)(uiMan->getInformation(1))));
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() + 4));
}

void MainWindow::parseSummary(string summary){
    size_t prev = 0, index, j=0;
    while ((index = summary.find_first_of("*", prev)) != string::npos){
        if (index > prev){
            if(j ==0){
                ui->ContentsTitleEdit->setText(ui->ContentTreeWidget->currentItem()->text(0).toUtf8().constData());
                j++;
            }
            else if(j ==1){
                ui->AuthorEdit->setText(QString::fromStdString(summary.substr(prev, index-prev)));
                j++;
            }
            else if(j ==2){
                ui->ReleaseYearEdit->setText(QString::fromStdString(summary.substr(prev, index-prev)));
                j++;
            }
            else if(j ==3){
                ui->PageCountEdit->setText(QString::fromStdString(summary.substr(prev, index-prev)));
                j++;
            }
            else if(j ==4){
                ui->DecscriptionEdit->setText(QString::fromStdString(summary.substr(prev, index-prev)));
                j++;
            }
            else if(j ==5){
                ui->PublisherEdit->setText(QString::fromStdString(summary.substr(prev, index-prev)));
                j++;
            }
        }
        prev = index + 1;
    }
    if (prev < summary.length()){
        ui->PriceEdit->setText(ui->ContentTreeWidget->currentItem()->text(2).toUtf8().constData());
    }

}
void MainWindow::parseEdit(string edit){
    size_t prev = 0, index, j=0;
    while ((index = edit.find_first_of("*", prev)) != string::npos){
        if (index > prev){
            if(j ==0){
                ui->BookTitleEditC->setText(ui->ContentTreeWidgetC->currentItem()->text(0).toUtf8().constData());
                j++;
            }
            else if(j ==1){
                ui->AuthorEditC->setText(QString::fromStdString(edit.substr(prev, index-prev)));
                j++;
            }
            else if(j ==2){
                ui->ReleaseYearEditC->setText(QString::fromStdString(edit.substr(prev, index-prev)));
                j++;
            }
            else if(j ==3){
                ui->PageCountEditC->setText(QString::fromStdString(edit.substr(prev, index-prev)));
                j++;
            }
            else if(j ==4){
                ui->DecscriptionEditC->setText(QString::fromStdString(edit.substr(prev, index-prev)));
                j++;
            }
            else if(j ==5){
                ui->PublisherEditC->setText(QString::fromStdString(edit.substr(prev, index-prev)));
                j++;
            }
        }
        prev = index + 1;
    }
    if (prev < edit.length()){
        ui->PriceEditC->setText(ui->ContentTreeWidgetC->currentItem()->text(2).toUtf8().constData());
    }

}

void MainWindow::parseEdit_chs(){
    ui->chSTitleEditC->setText(ui->ContentTreeWidgetC->currentItem()->text(0).toUtf8().constData());
    ui->chSPriceEditC->setText(ui->ContentTreeWidgetC->currentItem()->text(2).toUtf8().constData());
}

void MainWindow::on_CloseButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() - 4));
}

void MainWindow::on_ContentTreeWidget_itemPressed(QTreeWidgetItem *item, int column)
{
    if (item->type()!=0){
        ui->SummaryButton->setEnabled(false);
    }
    else
       ui->SummaryButton->setEnabled(true);
}

void MainWindow::on_ContentTreeWidgetC_itemPressed(QTreeWidgetItem *item, int column)
{

}

void MainWindow::on_CancelButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() - 1));
}

void MainWindow::on_CancelButton_chS_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() - 2));
}

void MainWindow::on_SaveButton_clicked()
{
    /* This should reload contentsPage */
    QString temp  =  ui->ContentTreeWidgetC->currentItem()->text(1) + "*";
    temp += ui->BookTitleEditC->text() + "*" + ui->AuthorEditC->text() + "*" + ui->ReleaseYearEditC->text()
                   + "*" + ui->PageCountEditC->text() + "*" + ui->DecscriptionEditC->toPlainText() + "*"
            + ui->PublisherEditC->text() + "*" +  ui->PriceEditC->text() + "*";
    if(ui->NotAvailableRadioButton->isChecked())
        temp += "false";
    else if(ui->AvailableRadioButton->isChecked())
        temp += "true";
    string contents = temp.toUtf8().constData();
    cout<< contents <<endl;
    ui->AvailableRadioButton->setChecked(true);
    ui->ContentTreeWidgetC->currentItem()->setData(0,0, ui->BookTitleEditC->text());
    ui->ContentTreeWidgetC->currentItem()->setData(2,0, ui->PriceEditC->text());
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() - 1));

}

void MainWindow::on_SaveButton_chS_clicked()
{
    /* This should reload contentsPage */
    QString temp  =  ui->ContentTreeWidgetC->currentItem()->text(1) + "*";
    temp += ui->chSTitleEditC->text() + "*" + ui->chSPriceEditC->text() + "*";
    if(ui->NotAvailableRadioButton_chS->isChecked())
        temp += "false";
    else if(ui->AvailableRadioButto_chS->isChecked())
        temp += "true";
    string contents = temp.toUtf8().constData();
    cout<< contents <<endl;
    ui->AvailableRadioButto_chS->setChecked(true);
    ui->ContentTreeWidgetC->currentItem()->setData(0,0, ui->chSTitleEditC->text());
    ui->ContentTreeWidgetC->currentItem()->setData(2,0, ui->chSPriceEditC->text());
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() - 2));
}

void MainWindow::on_ViewCartButton_clicked()
{
    int totalPrice = 0;
    cout<<ui->ContentTreeWidget->topLevelItemCount()<<endl;
    for(int i = 0; i < ui->ContentTreeWidget->topLevelItemCount(); i ++){
        QTreeWidgetItem* currentItem = ui->ContentTreeWidget->topLevelItem(i);
        if(currentItem->checkState(0)==2){
             QTreeWidgetItem* newBook = new QTreeWidgetItem(ui->ShoppCTreeWidget, 0);
             newBook->setData(0, 0, currentItem->data(0,0));
             newBook->setData(1, 0, currentItem->data(1,0));
             newBook->setData(2, 0, currentItem->data(2,0));
             totalPrice += currentItem->data(2,0).toInt();
             continue;
        }
        for(int j = 0; j < currentItem->childCount(); j++){
            QTreeWidgetItem* chapterChild = currentItem->child(j);
            if(chapterChild->checkState(0)==2){
                 QTreeWidgetItem* newChapter = new QTreeWidgetItem(ui->ShoppCTreeWidget, 0);
                 newChapter->setData(0, 0, chapterChild->data(0,0));
                 newChapter->setData(1, 0, chapterChild->data(1,0));
                 newChapter->setData(2, 0, chapterChild->data(2,0));
                 totalPrice += chapterChild->data(2,0).toInt();
                 continue;
            }
            for(int k = 0; k < chapterChild->childCount(); k++){
                QTreeWidgetItem* sectionChild = chapterChild->child(k);
                if(sectionChild->checkState(0)==2){
                     QTreeWidgetItem* newSection = new QTreeWidgetItem(ui->ShoppCTreeWidget, 0);
                     newSection->setData(0, 0, sectionChild->data(0,0));
                     newSection->setData(1, 0, sectionChild->data(1,0));
                    newSection->setData(2, 0, sectionChild->data(2,0));
                     totalPrice += sectionChild->data(2,0).toInt();
                }
            }

        }

    }
    ui->ShoppCTPEdit->setText( "Total price is " + QString::number(totalPrice));
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() + 5));
}

void MainWindow::on_PlaceOrderButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() + 1));
}

void MainWindow::on_CancelOrderButton_clicked()
{
    ui->ShoppCTreeWidget->clear();
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() - 5));
}

void MainWindow::on_HomeButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() - 8));
}



void MainWindow::on_ContentTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if(item->checkState(0) == 2)
        item->setChildIndicatorPolicy(QTreeWidgetItem::DontShowIndicator);
    else
        item->setChildIndicatorPolicy(QTreeWidgetItem::DontShowIndicatorWhenChildless);
}
