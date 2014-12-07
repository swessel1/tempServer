#include "UIManager.h"
#include <iostream>
#include <stdlib.h>

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sstream>
using namespace std;

#include "PracticalSocket.h"  // For Socket and SocketException
#include <cstdlib>            // For atoi()


const int RCVBUFSIZE = 32;    // Size of receive buffer

UIManager::UIManager(int ac, char* av[], QApplication *tempA): a(tempA), portno(6000), passValue(1)
  //  argc(ac)
{
  //  argv[0] = av[0];
}
/* testing */
/*vector<string> yLis;
vector <string> cLis;
vector <string> contLis;
*/
/***********/


void UIManager::control(){
    int i=0;
  //  while(1){cout<<"eder"<<endl;
      connectTo();
      openLoginView(false);
     /* if (m->exited())
          break;
      openCoursesView(&i);
      if(c->back ==true){
          c->back=false;
          continue;
      }
      if(c->exited())
          break;
      openContentsView();
      break;
    }*/
}


//error output
void UIManager::error(const char *msg)
{
    perror(msg);
    exit(0);
}

/*
 *This function connects to the server process using
 *TCP/IP Sockets on a preconfigured port number
 *
 *IN: N/A
 *RETURNS: void
 */
int UIManager::connectTo()
{
    /*if ((argc < 3) || (argc > 4)) {     // Test for correct number of arguments
       cerr << "Usage: " << argv[0]
            << " <Server> <Echo String> [<Server Port>]" << endl;
       exit(1);
     }*/

    string servAddress = "10.0.2.15"; // First arg: server address
     char *echoString = "bdsse";   // Second arg: string to echo
     int echoStringLen = strlen(echoString);   // Determine input length
     unsigned short echoServPort = 6000;//(argc == 4) ? atoi(argv[3]) : 7;

     try {
       // Establish connection with the echo server
       TCPSocket sock(servAddress, echoServPort);

       // Send the string to the echo server
       sock.send(echoString, echoStringLen);

       char echoBuffer[RCVBUFSIZE + 1];    // Buffer for echo string + \0
       int bytesReceived = 0;              // Bytes read on each recv()
       int totalBytesReceived = 0;         // Total bytes read
       // Receive the same string back from the server
       cout << "Received: ";               // Setup to print the echoed string
       while (totalBytesReceived < echoStringLen) {
         // Receive up to the buffer size bytes from the sender
         if ((bytesReceived = (sock.recv(echoBuffer, RCVBUFSIZE))) <= 0) {
           cerr << "Unable to read";
           exit(1);
         }
         totalBytesReceived += bytesReceived;     // Keep tally of total bytes
         echoBuffer[bytesReceived] = '\0';        // Terminate the string!
         cout << echoBuffer;                      // Print the echo buffer
       }
       cout << endl;

       // Destructor closes the socket

     } catch(SocketException &e) {
       cerr << e.what() << endl;
       exit(1);
     }

     return 0;
}

/*
 *This function returns the passValue (aka 0 or 1)
 *that is stored in client when a test case finishes running
 *
 *RETURNS: int 0 or 1 or negative value for error
 */
int UIManager::getPassValue()
{
    return passValue;
}

/*
 *This function runs the selected test case.
 *The specific case is determined through the UI
 *
 *IN: testIndex being the case number that is to be run
 *OUT: determines the pass value of the test case
 *RETURN: void
 */
void UIManager::runTest(char* testIndex)
{
    char buff[256];
    int error = write(sockfd,testIndex,strlen(testIndex));
    if(error<0)
        passValue = 1;

    bzero(buff,256);
    read(sockfd,buff,255);

    if(strcmp(buff,"0") == 0)
    {
        passValue = 0;
    }
    else
    {
        passValue = 1;
    }
}

//gracefully closes the created socket
void UIManager::closeConnection()
{
        close(sockfd);
}


int UIManager::openLoginView(bool running){
  //  a->quit();
    sendYears();
    vector<string> years = yLis;
    yLis.clear();
    m = new MainWindow(this, a);
   // *w)(a);
    m->show();
    a->exec();
   /* if(!running)
        a->exec();
   // a->quit();*/
    return 0;
}

vector<string> UIManager::getCourseList(){
    sendCourses();
    vector<string> c = cLis;
    cLis.clear();
    return c;
}

//CoursesView c
/*void UIManager::openCoursesView(int *i){
    //sendCourses();
    vector<string> courses = cLis;
    cLis.clear();
    c = new CoursesView(m->getUserType(), m->getUserID(), courses, a);
  //  MainWindow m;
   // a->quit();
   // m->hide();
    c->show();
    a->exec();
   // a->quit();
   // QApplication* b=a;
  //  b->exec();
}

void UIManager::openContentsView(){
    sendContents();
    cont = new ContentsView(a);
    cont->show();
    a->exec();
}
*/

/* testing functions */
/*vector<string> UIManager::sendRequest(){
    return courses;
}*/
vector<string> UIManager::queryYears(){

}

void UIManager::receiveYears(string* buffer){
    yLis.push_back(*buffer);

}

void UIManager::sendYears(){
    vector<string> years;
    years.push_back("2000");
    years.push_back("2001");
    years.push_back("2002");
    years.push_back("2003");
    //getNumber(&years);
    //return years;
    for(int i =0; i < years.size(); i++){
        receiveYears(&(years.at(i)));
    }

}
int UIManager::getSize(vector<string>* list){
    return list->size();
}

void UIManager::receiveCourses(string *buffer){
    cLis.push_back(*buffer);
}

void UIManager::sendCourses(){
    //cout << m->getUserID()<< " " << m->getUserType()<<endl;
    //cout << "Year:  "<< m->getYear() <<" Term: "<<m->getTerm()<<endl;
    vector<string> courses;
    courses.push_back("PSYCH 1993");
    courses.push_back("MATH 1005");
    courses.push_back("PHIL 3232");
    for(int i =0; i < courses.size(); i++){
        receiveCourses(&(courses.at(i)));
    }


}

void UIManager::receiveContents(string *buffer){

    //conLis[title] = temp ;
}

void UIManager::createContents(){

    bookLis.push_back("The legend of Naruto*124W3*1000*");
    bookLis.push_back("Warrior*2343A*324");
    bookLis.push_back("Born sinner*4Q43W*10000");
    bookLis.push_back("TeaCan*233WE*5000");
    bookLis.push_back("Bored*34DS2*900");
    bookLis.push_back("Laughable*23WF2*3000");
    bookLis.push_back("Dishonored*34ER2*10000");
    bookLis.push_back("Blah!*ER23Q*400");
    bookLis.push_back("What do I know?*34W34*100");
    bookLis.push_back("We don't*23EW2*3000");

    chapterLis.push_back("Chapter1*23EW*230");
    chapterLis.push_back("Chapter2*23EW*200");
    chapterLis.push_back("Chapter3*23EW*453");
    chapterLis.push_back("Chapter4*23EW*500");
    chapterLis.push_back("Chapter5*23EW*342");
    chapterLis.push_back("Chapter6*23EW*700");
    chapterLis.push_back("Chapter7*23EW*433");
    chapterLis.push_back("Chapter8*23EW*200");
    chapterLis.push_back("Chapter9*23EW*100");
    chapterLis.push_back("Chapter10*23EW*2300");

    sectionLis.push_back("Section1*23EW*430");
    sectionLis.push_back("Section2*23EW*40");
    sectionLis.push_back("Section3*23EW*30");
    sectionLis.push_back("Section4*23EW*90");
    sectionLis.push_back("Section5*23EW*110");
    sectionLis.push_back("Section6*23EW*230");
    sectionLis.push_back("Section7*23EW*430");
    sectionLis.push_back("Section8*23EW*230");
    sectionLis.push_back("Section9*23EW*400");
    sectionLis.push_back("Section10*23EW*1430");

}

void* UIManager::getInformation(int what){
    switch(what){
    case 0:
        return new int(rand() % 10 + 0); /* get from server */;
    case 1:
        /* get serialized string from server */
        return new string("testing Title*testing author*testing release year*testing page count*testing description*testing publisher*testing price");

    }
}

/*void UIManager::receiveChapter(string *buffer){
    string temp;
    for(int i= 0;i<buffer.length;i++){
        if(buffer[i] != "*")
            temp+=buffer
    }
}*/

void UIManager::sendContents(){
    vector<string> books;
    for(int i =0; i < books.size(); i++){
        receiveCourses(&(books.at(i)));
        //"Chapter1*240*"
    }
}

//vector

