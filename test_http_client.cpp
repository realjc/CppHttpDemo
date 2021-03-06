#include <bits/stdc++.h>
#include "http_client.hpp"

using namespace std;
void handle_func(std::string rsp)
{
	// do sth according to rsp
	std::cout << "http rsp1: " << rsp << std::endl;
}

int main(){
    string url = "http://127.0.0.1:7999/api/hello";
    HttpClient::sendReq(url, handle_func);
    return 0;
}