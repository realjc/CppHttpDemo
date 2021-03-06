#include <bits/stdc++.h>
#include "http_server.hpp"

using namespace std;


int main(){
    string port = "7999";
    string root = "root/";
    auto http_server = std::shared_ptr<HttpServer>(new HttpServer);
    http_server->init(port,root);
    http_server->start();
    http_server->close();
    return 0;
}