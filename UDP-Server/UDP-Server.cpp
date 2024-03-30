
#include <winsock2.h>
#include <iostream>
#include <string>
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

char* GetIP(char domen[256])
{
    auto remoteHost = gethostbyname(domen);

    char* ip = remoteHost->h_addr_list[0];

    return inet_ntoa(**(in_addr**)remoteHost->h_addr_list);
}


int main()
{
    setlocale(LC_ALL, "Russian");

    WSAData wsaData;
    if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0)
        std::cout << "Ошибка инициализации WSA\n";

    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(49001);
    addr.sin_family = AF_INET;
    int addrlenght = sizeof(addr);

    SOCKET sListen = socket(AF_INET, SOCK_DGRAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    //listen(sListen, SOMAXCONN);

    while (true)
    {
        std::cout << "Жду запроса от клиента\n";

        SOCKADDR_IN cliaddr;
        int len = sizeof(cliaddr);

        char request[1024];
        recvfrom(sListen, request, sizeof(request), NULL,(struct sockaddr*)&cliaddr,&len);

        std::cout << "Поступил запрос: " << request << std::endl;

        char* response;
        response = GetIP(request);

        std::cout << "Отправляю ответ: " << response << std::endl;

        sendto(sListen, response, 255,
            NULL, (const struct sockaddr*)&cliaddr,
            len);

        std::cout << std::endl;
    }
}


