#include <QApplication>
#include <iostream>
#include <string>
#include "UIManager.h"
//#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UIManager ui(&a);
    ui.control();
    cout <<"Done!"<<endl;

    return 0;
}
