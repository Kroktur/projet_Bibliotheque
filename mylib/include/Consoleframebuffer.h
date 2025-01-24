#pragma once
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
    void clear();
    std::string getLastCommand();
    bool IsRunning();
    void CloseWindow();
private:
    ConsoleFramebufferPrivateImpl* m_impl;
};
