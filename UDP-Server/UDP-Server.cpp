
#include <winsock2.h>
#include <iostream>
#include <string>

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

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    while (true)
    {
        std::cout << "Жду присоединения клиента\n";

        SOCKET clientConnection = accept(sListen, (SOCKADDR*)&addr, &addrlenght);

        if (clientConnection != 0)
        {
            std::cout << "Клиент подключен!\n";

            char message[256] = "Вы успешно подключились!";
            send(clientConnection, message, sizeof(message), NULL);

            //Ждем и обрабатываем запрос от клиента
            while (true)
            {
                char request[256];
                recv(clientConnection, request, sizeof(request), NULL);

                if (strlen(request) == 0) //Вот это не получилось
                {
                    std::cout << "Клиент отключился!" << request << std::endl;
                    closesocket(clientConnection);
                    break;
                }

                std::cout << "Поступил запрос: " << request << std::endl;

                char* response;
                response = GetIP(request);

                std::cout << "Отправляю ответ: " << response << std::endl;
                send(clientConnection, response, 255, NULL);

                std::cout << std::endl;
            }
        }
    }
}


