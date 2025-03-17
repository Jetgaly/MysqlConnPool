#include<chrono>
#include<iostream>
#include<ctime>
#include<thread>
int main(){
    auto now = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto newnow = std::chrono::steady_clock::now();
    auto dura = std::chrono::duration_cast<std::chrono::milliseconds>(newnow - now);

    std::cout<<dura.count()<<std::endl;
    return 0;
}