
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

    SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        std::cout << "Ошибка подключения к серверу\n";
        return 1;
    }

    char response[256];
    recv(Connection, response, sizeof(response), NULL);
    std::cout << response << std::endl;
    
    while (true)
    {
        std::cout << "\nВыберите команду: \n";
        std::cout << "1) Узнать IP для доменного имени \n";
        std::cout << "2) Выход \n";
        std::cout << "Ваш выбор: ";

        int clientInput;
        std::cin >> clientInput;

        switch (clientInput)
        {
            case 1:
            {
                char request[256];
                std::cout << "\nВведите доменное имя: ";
                std::cin >> request;

                send(Connection, request, sizeof(request), NULL);

                memset(response, 0, 255);
                recv(Connection, response, 255, NULL);
                std::cout << "Полученный IP от сервера: " << response << std::endl;

                system("pause");
                system("CLS");
                break;
            }
            case 2: 
            {
                shutdown(Connection, 0);
                closesocket(Connection);
                return 0;
            }   
            default: 
            {
                std::cout << "\nКоманда не распознана! ";
                break;
            }
        }
    }

}
