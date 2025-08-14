#  Сетевое приложение: TCP-сервер и клиент (C++)

Простое сетевое приложение на C++, реализующее TCP-сервер и клиент для обмена командами. Проект включает примеры кода для Linux (POSIX-сокеты) и Windows (WinSock2)

---
##  Структура проекта
network-app/
- server_linux.cpp        # Сервер на Linux (socket, bind, listen, accept)
- client_windows.cpp      # Клиент на Windows (WinSock2)
- server_windows.cpp      # Сервер на Windows (WinSock2, отправляет сообщение)
- README.md               # Этот файл
- Command.h               # (Опционально) — вынесенная структура Command

>  В текущей версии структура `Command` определена в `server_linux.cpp`, но рекомендуется вынести в отдельный заголовочный файл.
---

##  Функционал

###  Linux-сервер (`server_linux.cpp`)
- Создаёт TCP-сервер с использованием POSIX-сокетов.
- Принимает подключение клиента.
- Отправляет и принимает структуру `Command`.
- Логирует процесс подключения и обмена данными.

###  Windows-клиент (`client_windows.cpp`)
- Подключается к серверу по адресу `127.0.0.1:1111`.
- Принимает сообщение от сервера и выводит его в консоль.

### Windows-сервер (`server_windows.cpp`)
- Запускает TCP-сервер на порту `1111`.
- Принимает клиентское подключение.
- Отправляет тестовое сообщение: `"Hellows, its my first server"`.

---

##  Технологии и зависимости

- **Язык**: C++ (стандарт не ниже C++11)
- **Платформы**:
  - **Linux**: `g++`, `unistd.h`, `arpa/inet.h`, `netinet/in.h`
  - **Windows**: `WinSock2.h`, `Ws2_32.lib`, `wx`
- **Протокол**: TCP/IP
- **Сокеты**: Системные вызовы для сетевого взаимодействия

---

##  Как запустить

###  На Linux (сервер)

1. Сохраните код сервера в файл `server_linux.cpp`.
```
git clone https://github.com/ipvHEEL/cpp_winsock_messenger.git
```    
2. Скомпилируйте:
   ```bash
   g++ server_linux.cpp -o server_linux
   ```
3. Запустите
```
./server_linux
```
##  Флаги компиляции:

`wx-config --cxxflags --libs -lws2_32`
