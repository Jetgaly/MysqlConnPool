#include<iostream>
#include<mysql/mysql.h>
#include<string>

const std::string host = "127.0.0.1";
const std::string user = "jet";
const std::string passwd = "Qwe123@asd456";
const std::string DBname = "test";
const unsigned int port = 3306;

int main(){
    //init mysql
    MYSQL* my = mysql_init(nullptr);
    if(!my){
        std::cout<<"init err"<<std::endl;
        return 0;
    }
    std::cout<<mysql_get_client_info()<<std::endl;
    
    if(!mysql_real_connect(my,host.c_str(),user.c_str(),passwd.c_str(),DBname.c_str(),port,nullptr,0)){
        std::cout<<"conn err"<<std::endl;
        std::cerr << "连接错误: " << mysql_error(my) << std::endl;//不经历缓冲直接输出错误
        return 0;
    }
    std::string insertcommand = "insert into t_student values(3,'jam','m')";
    std::string updatecommand = "update t_student set s_name ='zhangsan' where s_id = 3";
    std::string deletecommand = "delete from t_student where s_id = 5";
    std::string findcommand = "select * from t_student";
    int n = mysql_query(my,findcommand.c_str());
    if(n==0){
        std::cout<<"success"<<std::endl;
    }else{
        std::cout<<"failed"<<std::endl;
        std::cerr << "错误: " << mysql_error(my) << std::endl;
    }
    MYSQL_RES* res = mysql_store_result(my);
    my_ulonglong row =mysql_num_rows(res);
    my_ulonglong field = mysql_num_fields(res);
    //get attribute
    MYSQL_FIELD* fieldsArray = mysql_fetch_field(res);
    for(int i=0;i<field;++i){
        std::cout<<fieldsArray[i].name<<'\t';//print per attribute
    }
    std::cout<<'\n';
    for(int i=0;i<row;++i){
        MYSQL_ROW temp=mysql_fetch_row(res);//fetch row
        for(int j=0;j<field;++j){
            std::cout<<temp[j]<<'\t';//print per data
        }
        std::cout<<'\n';
    }
    mysql_free_result(res);//free res
    mysql_close(my);//close connection
    //mysql_set_character_set()
    return 0;
}