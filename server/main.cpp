#include <NovusTypes.h>
#include "defines.h"
#include <Utils/Message.h>
#include <Utils/StringUtils.h>
#include <asio/io_service.hpp>
#include <Networking/BaseServer.h>

#include <future>

#include "EngineLoop.h"
#include "ConsoleCommands.h"

#ifdef _WIN32
#include <Windows.h>
#endif

i32 main()
{
#ifdef _WIN32 //Windows
    SetConsoleTitle(WINDOWNAME);
#endif
    EngineLoop engineLoop(30);
    engineLoop.Start();

    std::thread* runIoServiceThread;
    asio::io_service ioService(2);
    BaseServer baseServerInternal(ioService, 3725, true);
    BaseServer baseServerPublic(ioService, 3724);

    ConsoleCommandHandler consoleCommandHandler;
    std::future<std::string> future = std::async(std::launch::async, StringUtils::GetLineFromCin);
    while (true)
    {
        Message message;
        bool shouldExit = false;

        while (engineLoop.TryGetMessage(message))
        {
            if (message.code == MSG_OUT_EXIT_CONFIRM)
            {
                shouldExit = true;
                break;
            }
            else if (message.code == MSG_OUT_PRINT)
            {
                NC_LOG_MESSAGE(*message.message);
                delete message.message;
            }
            else if (message.code == MSG_OUT_SETUP_COMPLETE)
            {
                baseServerInternal.Start();
                baseServerPublic.Start();

                runIoServiceThread = new std::thread([&] 
                {
                    ioService.run();
                });
            }
        }

        if (shouldExit)
            break;

        if (future.wait_for(std::chrono::milliseconds(50)) == std::future_status::ready)
        {
            std::string command = future.get();
            std::transform(command.begin(), command.end(), command.begin(), ::tolower); // Convert command to lowercase

            consoleCommandHandler.HandleCommand(engineLoop, command);
            future = std::async(std::launch::async, StringUtils::GetLineFromCin);
        }
    }

    engineLoop.Stop();
    return 0;
}