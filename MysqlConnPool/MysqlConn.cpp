#include"MysqlConn.h"
#include <iostream>
MysqlConn::MysqlConn(){
   
    MyConn = mysql_init(nullptr);
    mysql_set_character_set(MyConn,"utf8");
}
MysqlConn::~MysqlConn(){
    if(MyConn){
        mysql_close(MyConn);
    }
}

bool MysqlConn::connect(std::string host,std::string user,std::string passwd,std::string dbName,unsigned int port,const char *unix_socket, unsigned long clientflag){
    if(!mysql_real_connect(MyConn,host.c_str(),user.c_str(),passwd.c_str(),dbName.c_str(),port,unix_socket,clientflag)){
        return false;
    }
    return true;
}

bool MysqlConn::update(std::string sql){
    if(mysql_query(MyConn,sql.c_str())==0)return true;
    return false;
}
// 查询数据库
bool MysqlConn::query(std::string sql){
    if(mysql_query(MyConn,sql.c_str()))return false;
    freeRes();
    MyRes=mysql_store_result(MyConn);
    return true;
}
// 遍历查询得到的结果集
bool MysqlConn::nextRow(){
    if(MyRes){
        row = mysql_fetch_row(MyRes);
        return true;
    }
    return false;
}
// 得到结果集中的字段值
std::string MysqlConn::value(int index){
    int fieldsCount = mysql_num_fields(MyRes);
    if(index<0||index>=fieldsCount){
        return std::string();
    }
    char* val=row[index];
    unsigned long len = mysql_fetch_lengths(MyRes)[index];
    return std::string(val,len);
}
// 事务操作
bool MysqlConn::transaction(){
    return !mysql_autocommit(MyConn, false);//mysql_autocommit() success will return 0
}
// 提交事务
bool MysqlConn::commit(){
    return !mysql_commit(MyConn);
}
// 事务回滚
bool MysqlConn::rollback(){
    return !mysql_rollback(MyConn);
}
// 刷新起始的空闲时间点
void MysqlConn::refreshAliveTime(){
    startTime = std::chrono::steady_clock::now();
}
// 计算连接存活的总时长
long long MysqlConn::getAliverTime(){
    auto now =std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);
    return duration.count();
}
//
void MysqlConn::freeRes(){
    if(!MyRes){
        mysql_free_result(MyRes);
        MyRes==nullptr;
    }
}
long long MysqlConn::getFields(){
    if(MyRes){
        return mysql_num_fields(MyRes);
    }
    return 0;
}

long long MysqlConn::getRows(){
    if(MyRes){
        return mysql_num_rows(MyRes);
    }
    return 0;
}