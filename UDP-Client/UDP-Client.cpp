
#include <winsock2.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

int main()
{
    setlocale(LC_ALL, "Russian");

    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0)
        std::cout << "Ошибка инициализации WSA\n";

    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(49001);
    addr.sin_family = AF_INET;

    SOCKET Connection = socket(AF_INET, SOCK_DGRAM, NULL);

    int clientInput;
    while (true)
    {
        char request[256];
        std::cout << "\nВведите доменное имя: ";
        std::cin >> request;

        int len = sizeof(addr);

        sendto(Connection, request, sizeof(request), NULL,
            (struct sockaddr*)&addr, len);

        char response[256];
        memset(response, 0, 255);
        recv(Connection, response, 255, NULL);

        std::cout << "Полученный IP от сервера: " << response << std::endl;

        system("pause");
        system("CLS");
    }
}
