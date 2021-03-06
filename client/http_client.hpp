#pragma once
#include <bits/stdc++.h>
#include "mongoose.h"

using namespace std;

using reqCallback = std::function<void (std::string)>;

class HttpClient{
public:
    HttpClient(){}
    ~HttpClient(){}

    static void sendReq( const string &url, reqCallback req_callback);
    static void onHttpEvent(mg_connection *conn, int event_type, void* event_data);
    static reqCallback m_req_callback;
    static int m_exit_flag;
};