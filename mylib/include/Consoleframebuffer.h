#pragma once

#pragma once
#include <Windows.h>
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


class ConsoleFramebufferPrivateImpl
{
public:
    ConsoleFramebufferPrivateImpl();
    void setCharacter(int row, int col, char car, Color foreground, Color background);
    /*  void printString(int row, int col, const std::string& str, Color foreground, Color background);*/
    void show();
    void setString(std::string text, Color color = White, Color backColor = Black);
    void printtxt();
    void updatesize();
    void writeconsol();
private:
    void copystringtoend(std::string string);
    void changeidxtoend(std::string& string);
    void resize(int numRows, int numCols);
    void setstring(int row, int i);
    void eraseemtpyhystorique();
private:
    HANDLE m_handleoutput;
    HANDLE m_handleinput;
    std::vector<CHAR_INFO> m_buffer;
    SHORT windowWidth;
    SHORT windowHeight;
    int m_numRows;
    int m_numCols;
    //to set txt
    int m_idx;
    std::vector<std::string> m_hystorique;
    std::vector <std::string> m_write;
    std::vector <Color> m_colortowrite;
    std::vector <Color> m_backcolortowrite;
};
