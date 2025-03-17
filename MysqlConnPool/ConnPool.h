#ifndef CONNPOOL_H
#define CONNPOOL_H
#include <thread>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <queue>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <iostream>

#include "MysqlConn.h"

class ConnPool
{
public:
    ConnPool(const ConnPool& obj) = delete;
    ConnPool& operator=(const ConnPool& obj) = delete;
    ~ConnPool();
    static::ConnPool* getInstance();
    std::shared_ptr<MysqlConn> getConnection();

    std::string host;
    std::string user;
    std::string passwd;
    std::string dbName;
    unsigned int port;
    const char *unix_socket;
    unsigned long clientflag;
private:
    bool parseConfig();
    
    void produceConn();

    void reduceConn();

    void addConnection();
    ConnPool(/* args */);
    /* data */
    
    int maxSize;
    int minSize;
    std::mutex myMutex;
    std::condition_variable condi;
    std::queue<MysqlConn*> connQueue;
    int timeout;
    bool stop;
};

#endif