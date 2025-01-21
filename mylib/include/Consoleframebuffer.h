#pragma once

#include <vector>
#include <string>

enum Color
{
      Red
    , Green
    , Blue
    , White
    , Black
};

class ConsoleFramebufferPrivateImpl;

class ConsoleFramebuffer
{
public:
    ConsoleFramebuffer();
    ~ConsoleFramebuffer();
    void setString(std::string text, Color color = White, Color backColor = Black);
    void show();
    void updateSize();
    void writeConsol();
    std::string getLastCommand();
private:
    ConsoleFramebufferPrivateImpl* m_impl;
};
