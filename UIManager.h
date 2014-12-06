#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QApplication>
#include <mainwindow.h>
//#include "coursesview.h"
//#include "contentsview.h"

class MainWindow;
class UIManager
{
private:
    QApplication *a;
    MainWindow *m;
    int portno;
    int sockfd;
    int passValue;
    int argv;
    char *argc;
    //CoursesView *c;
    //ContentsView *cont;

public:
    UIManager(QApplication* = 0);
    void connectTo();
    int getPassValue();
    void runTest(char*);
    void closeConnection();
    void error(const char *);
    int openLoginView(bool);
    void openCoursesView(int*);
    void openContentsView();

    /* testing vectors*/
    vector<string> yLis;
    vector<string> cLis;
    vector<string> bookLis;
    vector<string>  chapterLis;
    vector<string>  sectionLis;

    /* testing functions */
    vector<string> sendRequest();
    vector<string> queryYears();
    void receiveYears(string*);
    void sendYears();
    void receiveCourses(string*);
    void sendCourses();
    void receiveContents(string*);
    void sendContents();
    void createContents();
    int getSize(vector<string>*);
    void* getInformation(int);
    void control();
    vector<string> getCourseList();
};

#endif // UIMANAGER_H
