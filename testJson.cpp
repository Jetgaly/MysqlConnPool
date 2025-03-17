#include <iostream>
#include <jsoncpp/json/json.h>
#include <fstream>

using namespace std;
using namespace Json;

int main() {
    std::ifstream ifs("MysqlConnPool/DBconfig.json");
    CharReaderBuilder readerBuilder;
    Json::Value root;
    std::string errs;

    // 使用 CharReaderBuilder 解析 JSON
    if (parseFromStream(readerBuilder, ifs, &root, &errs)) {
        if (root.isObject()) {
            cout << "start to parse config file..." << endl;
            cout << root["host"].asString() << endl;
            // 如果你想解析更多的字段，可以继续使用类似的方式
            // cout << root["port"].asInt() << endl;
            std::cout << "start to parse config file..." << std::endl;
            cout <<  root["host"].asString()<<std::endl;
            cout <<  root["port"].asInt()<<std::endl;
            cout << root["user"].asString()<<std::endl;
            cout << root["passwd"].asString()<<std::endl;
            cout <<  root["dbName"].asString()<<std::endl;
            cout << root["minSize"].asInt()<<std::endl;
            cout << root["maxSize"].asInt()<<std::endl;
            cout << root["timeout"].asInt()<<std::endl;
        
            cout << root["clientflag"].asInt()<<std::endl;
        }
        else {
            cout << "The root is not an object!" << endl;
        }
    }
    else {
        cout << "Failed to parse the JSON: " << errs << endl;
    }

    ifs.close();
    return 0;
}
