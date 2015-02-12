/* 
 * File:   main.cpp
 * Author: jester
 * 
 * Created on February 10, 2015, 10:21 AM
 */

#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netdb.h>


using namespace std;




int main(int argc, char** argv) 
{
    int status;
    struct addrinfo HostInfo;
    struct addrinfo *HostInfoList;
    
    memset(&HostInfo, 0, sizeof HostInfo);
    
    
    std::cout << "Setting up the structs..." << std::endl;
    
    HostInfo.ai_family = AF_UNSPEC; // IP version not specified. Can be both.
    HostInfo.ai_socktype = SOCK_STREAM; // Use Sock_Stream for TCP or SOCK_DGRAM for UDP
    
    // fill up the linked list of hostinfo stucts 
    status = getaddrinfo("www.google.com", "80", &HostInfo, &HostInfoList);
    if(status != 0)
    {
        std::cout << "getaddrinfo error" << gai_strerror(status);
    }

    //--------------------------------------------------------------------------
    // creat socket
    std::cout << "Creating a socket..." << std::endl;
    int socketfd;
    
    // int socket(int domain, int type, int protocol);  
    socketfd = socket(HostInfoList->ai_family, HostInfoList->ai_socktype, HostInfoList->ai_protocol);
    if(socketfd == -1)
    {
        std::cout << "socket error ";
    }

    //--------------------------------------------------------------------------
    // connect 
    std::cout << "Connect()int..." << std::endl;
    
    // int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen); 
    status = connect(socketfd, HostInfoList->ai_addr, HostInfoList->ai_addrlen);
    if(status == -1)
    {
        std::cout << "connect error";
    }
    
    //--------------------------------------------------------------------------
    // sending and receiving data
    std::cout << "send()ing messag..." << std::endl;
    char *msg = "GET / HTTP/1.1\nhost: www.google.com\n\n";
    int len;
    ssize_t bytes_sent;
    len = strlen(msg);
    bytes_sent = send(socketfd, msg, len, 0);
    
    
    
    std::cout << "Waiting to recieve dat..." << std::endl;
    ssize_t bytes_recieved;
    char incoming_data_buffer[1000];
    
    //ssize_t recv(int sockfd, void *buf, size_t len, int flags); 
    bytes_recieved = recv(socketfd, incoming_data_buffer, 1000, 0);
    
    // if no data arives, the program will jst wait here until some data arrives.
    if(bytes_recieved == 0)
    {
        std::cout << "host shut down." << std::endl;
    }
    
    if(bytes_recieved == -1)
    {
        std::cout << "receive error!" << std::endl;
    }
    
    std::cout << bytes_recieved << " bytes recieved :" << std::endl;
    std::cout << incoming_data_buffer << std::endl;
    return 0;
    
}



