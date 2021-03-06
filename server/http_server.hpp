#pragma once

#include "mongoose.h"
#include <bits/stdc++.h>
using namespace std;

static bool route_check(http_message* http_msg, char *route_prefix);
static int isWebsocket(const mg_connection * conn);

class HttpServer{
public:
    HttpServer(){}
    ~HttpServer(){}
public:
    void init(string  port, string root);
    bool start();
    bool close();
    static mg_serve_http_opts m_server_option;// web服务器选项
    static unordered_set<mg_connection*> m_websocket_session_set;// 缓存websocket连接

private:
    string m_port;
    mg_mgr m_mgr; // 连接管理器
    static void onHttpWebsocketEvent(mg_connection *connection, int envet_type, void*event_data);//连接回调
    static void handleHttpEvent(mg_connection* connection, http_message *http_req);// http回调
    static void handleWebsocketEvent(mg_connection* connection, int event_type, websocket_message* we_msg );//webskt回调
    static void sendHttpRsp(mg_connection *conn, string rsp);// 直接http返回信息
    static void sendWebsocketMsg(mg_connection *conn,string msg);//发送消息到指定连接
};


