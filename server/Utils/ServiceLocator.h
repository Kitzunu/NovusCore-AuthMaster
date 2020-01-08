/*
    MIT License

    Copyright (c) 2020 NovusCore

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
#pragma once
#include <entt.hpp>
#include "../Networking/MessageHandler.h"

class ServiceLocator
{
public:
    static entt::registry* GetMainRegistry() { return _mainRegistry; }
    static void SetMainRegistry(entt::registry* registry)
    {
        assert(_mainRegistry == nullptr);
        _mainRegistry = registry;
    }

    static MessageHandler* GetMessageHandler() { return _messageHandler; }
    static void SetMessageHandler(MessageHandler* messageHandler)
    {
        assert(_messageHandler == nullptr);
        _messageHandler = messageHandler;
    }

private:
    static entt::registry* _mainRegistry;
    static MessageHandler* _messageHandler;
};