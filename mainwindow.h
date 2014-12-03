#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QMainWindow>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
using namespace std;

namespace Ui {
class MainWindow;
class form;
}
class UIManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(UIManager * =0, QApplication* =0,  QWidget *parent = 0);
    bool exited();
    string getUserID();
    string getUserType();
    string getYear();
    string getTerm();
    string getCourseName();
    void   openCourseWindow();
    void   openContentsSWindow();
    void   openContentsCMWindow();
    void   createContents();
    void   createContentsC();
    void   parseContents(QTreeWidgetItem*, int, string);
    void   parseSummary(string);
    void   parseEdit(string);
    void   parseEdit_chs();
    ~MainWindow();

private slots:
    void on_LoginButton_2_clicked();

    void on_CourseBackButton_clicked();

    void on_LogOutButton_clicked();

    void on_viewContentsButton_clicked();

    void on_CoursesList_itemDoubleClicked(QListWidgetItem *item);

    void on_ContentsBackButton_clicked();

    void on_LogOutButton2_clicked();

    void on_LogOutButtonC2_clicked();

    void on_ContentsBackButtonC_clicked();

    void on_editContentButton_clicked();

    void on_SummaryButton_clicked();

    void on_CloseButton_clicked();

    void on_ContentTreeWidget_itemPressed(QTreeWidgetItem *item, int column);

    void on_ContentTreeWidgetC_itemPressed(QTreeWidgetItem *item, int column);

    void on_CancelButton_clicked();

    void on_CancelButton_chS_clicked();

    void on_SaveButton_clicked();

    void on_SaveButton_chS_clicked();

    void on_ViewCartButton_clicked();

    void on_CancelOrderButton_clicked();

    void on_HomeButton_clicked();

    void on_PlaceOrderButton_clicked();

    void on_ContentTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    QApplication *a;
    string userID;
    string userType;
    string courseName;
    bool exit;
    string year;
    string term;
    UIManager* uiMan;
};

#endif // MAINWINDOW_H
