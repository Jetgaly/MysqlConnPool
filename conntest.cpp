#include "MysqlConnPool/MysqlConn.h"
#include <iostream>
using namespace std;
#include "thread"
int main(){
    MysqlConn* q = new MysqlConn();
    cout<<"success"<<endl;
    this_thread::sleep_for(chrono::seconds(3));
    delete q;
    return 0;
}