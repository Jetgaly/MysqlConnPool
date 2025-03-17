#include"MysqlConnPool/ConnPool.h"
using namespace std;
int main(){
    ConnPool*p = ConnPool::getInstance();
    std::cout<<"1"<<std::endl;
    std::shared_ptr<MysqlConn> pcon = p->getConnection();
    std::cout<<'2'<<std::endl;
    int f=pcon->connect(p->host,p->user,p->passwd,p->dbName,p->port,p->unix_socket,p->clientflag);
    if(f)cout<<"connect success"<<endl;
    if(pcon->query("select * from t_student")){
        cout<<"query success"<<endl;
        int i=0;
        while (i<pcon->getRows())
        {   
            i++;
            pcon->nextRow();
            /* code */
            cout << pcon->value(0) << ", "
            << pcon->value(1) << ", "
            << pcon->value(2) << ", "<<endl;
        }
        
    }


    this_thread::sleep_for(chrono::seconds(3));
    return 0;
}