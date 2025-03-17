#include"ConnPool.h"

ConnPool::ConnPool()
{   
    stop=false;
    if(parseConfig()==false){
        std::cout<<"parse failed"<<std::endl;
        stop = true;
        return;
    }

    for(int i=0;i<minSize;++i){
        ConnPool::addConnection();
    }
            
    std::thread tProduce(&ConnPool::produceConn,this);
    std::thread tReduce(&ConnPool::reduceConn,this);
    tProduce.detach();
    tReduce.detach();
    std::cout<<"the pool init successfully"<<std::endl;
}

ConnPool::~ConnPool()
{
    {
        std::unique_lock<std::mutex> lock(myMutex);
        stop = true;
    }
    condi.notify_all(); // 唤醒所有线程

    std::unique_lock<std::mutex> lock(myMutex);
    while (!connQueue.empty()) {
        delete connQueue.front();
        connQueue.pop();
    }
}

ConnPool* ConnPool::getInstance(){
    static ConnPool pool;
    return &pool;
}

void ConnPool::produceConn(){
    while (!stop)
    {
        std::unique_lock<std::mutex> lock(myMutex);
        while (connQueue.size()>=minSize)
        {
            condi.wait(lock);
        }    
        ConnPool::addConnection();
        condi.notify_all();
    }
    
}

void ConnPool::reduceConn(){
    
    while (!stop)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2500));
        std::unique_lock<std::mutex> lock(myMutex);
        while (connQueue.size()>=minSize)
        {   MysqlConn* temp = connQueue.front();
            if(temp->getAliverTime()>timeout){
                
                connQueue.pop();
                delete temp;
            }
            else break;
        }
        
    }
}

void ConnPool::addConnection(){
    MysqlConn* q = new MysqlConn();
    q->refreshAliveTime();
    connQueue.push(q);
}

std::shared_ptr<MysqlConn> ConnPool::getConnection(){
    
    std::unique_lock<std::mutex> lock(myMutex);
    while (connQueue.empty()||stop)
    {   
        condi.notify_all();
        condi.wait(lock);
    }
    std::shared_ptr<MysqlConn> connPtr(connQueue.front(),[this](MysqlConn* Connection){
        std::unique_lock<std::mutex> lock(myMutex);
        if(connQueue.size()<maxSize&&!this->stop){
            Connection->refreshAliveTime();
            connQueue.push(Connection);
            return;
        }
        delete Connection;
        return;
    });
    connQueue.pop();
    
    return connPtr;
}

bool ConnPool::parseConfig(){
    std::ifstream ifs("MysqlConnPool/DBconfig.json");
    Json:: Reader rd;
    Json::Value root;
    rd.parse(ifs, root);

    if (root.isObject()) {
        
        std::cout << "start to parse config file..." << std::endl;
        host = root["host"].asString();
        port = root["port"].asInt();
        user = root["user"].asString();
        passwd = root["passwd"].asString();
        dbName = root["dbName"].asString();
        minSize = root["minSize"].asInt();
        maxSize = root["maxSize"].asInt();
        timeout = root["timeout"].asInt();
        unix_socket = NULL;
        clientflag = root["clientflag"].asInt();
        ifs.close();
        return true;
    }
    return false;

}