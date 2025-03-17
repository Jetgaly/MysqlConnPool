#ifndef MYSQLCONN_H
#define MYSQLCONN_H
#include<mysql/mysql.h>
#include<string>
#include<chrono>

class MysqlConn{
    public:
        MysqlConn();
        ~MysqlConn();
        bool connect(std::string host,std::string user,std::string passwd,std::string dbName,unsigned int port,const char *unix_socket, unsigned long clientflag);
        bool update(std::string sql);
        // 查询数据库
        bool query(std::string sql);
        // 遍历查询得到的结果集
        bool nextRow();
        // 得到结果集中的字段值
        std::string value(int index);
        // 事务操作
        bool transaction();
        // 提交事务
        bool commit();
        // 事务回滚
        bool rollback();
        // 刷新起始的空闲时间点
        void refreshAliveTime();
        // 计算连接存活的总时长
        long long getAliverTime();
        //free res
        void freeRes();

        //
        long long getFields();
        long long getRows();
    private:
        MYSQL* MyConn;
        MYSQL_RES* MyRes;
        MYSQL_ROW row;
        std::chrono::steady_clock::time_point startTime;
};

#endif