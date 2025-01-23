#include "ConsoleFramebuffer.h"
#include <Windows.h>
enum Scroll
{
    No_Scrol
    ,UP_Scroll
    ,Down_Scroll
};
class ConsoleFramebufferPrivateImpl
{
public:
    ConsoleFramebufferPrivateImpl();
    void show();
    void setString(std::string text, Color color = White, Color backColor = Black);
    void updateSze();
    void writeConsol();
    std::string getLastCommand();
    void clear();
    bool IsRunning();
    void CloseWindow();
private:
    void setCharacter(int row, int col, char car, Color foreground, Color background);
    void copyStringToEnd(std::string string);
    void changeIdxToEnd(std::string& string);
    void resize(int numRows, int numCols);
    void setString(int row, int i);
    void eraseEmtpyHistorique();
    void printText();
private:
    //windows needed member
    HANDLE m_handleoutput;
    HANDLE m_handleinput;
    std::vector<CHAR_INFO> m_buffer;
    SHORT windowWidth;
    SHORT windowHeight;
    int m_numRows;
    int m_numCols;
    int m_idx;
    bool m_IsRunning;
    std::string m_lastCommand;
    std::vector<std::string> m_historique;
    std::vector <std::string> m_toWrite;
    std::vector <Color> m_colorToWrite;
    std::vector <Color> m_backColorToWrite;
};

void ConsoleFramebufferPrivateImpl::updateSze()
{
    CONSOLE_SCREEN_BUFFER_INFO sbi;
    BOOL result = GetConsoleScreenBufferInfo(m_handleoutput, &sbi);
    windowWidth = sbi.srWindow.Right - sbi.srWindow.Left + 1;
    windowHeight = sbi.srWindow.Bottom - sbi.srWindow.Top + 1;
    resize(windowHeight, windowWidth);
    //remove empty commands
    eraseEmtpyHistorique();
}

void ConsoleFramebufferPrivateImpl::writeConsol()
{
    INPUT_RECORD inputRecord;
    DWORD events;
    ReadConsoleInput(m_handleinput, &inputRecord, 1, &events);
    if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown)
    {
        wchar_t key = inputRecord.Event.KeyEvent.uChar.UnicodeChar;
        WORD virtualKey = inputRecord.Event.KeyEvent.wVirtualKeyCode;
        if (key == '\r') //if ENTER is pressed
        {
            //Save the last command
            m_lastCommand = m_historique[m_idx];
            // Duplicate the last string
            if (m_idx != m_historique.size() - 1)
                copyStringToEnd(m_historique[m_idx]);
           // Create a new string
            std::string newstring;
            changeIdxToEnd(newstring);
        }
        else if (virtualKey == VK_UP) //if Up is pressed
        {
            if (m_idx == 0)
                return;
            --m_idx;
        }
        else if (virtualKey == VK_DOWN) //if Down is pressed
        {
            if (m_idx == m_historique.size() - 1)
                return;
            ++m_idx;
        }
        else if (key >= 32)
        {
            // Duplicate the last string
            if (m_idx != m_historique.size() - 1)
                copyStringToEnd(m_historique[m_idx]);
            m_historique[m_idx] += key;
        }
        else if (key == '\b' && !m_historique.back().empty())
        {
            // Duplicate the last string
            if (m_idx != m_historique.size() - 1)
                copyStringToEnd(m_historique[m_idx]);
            m_historique[m_idx].pop_back();
        }
       
    }
}
std::string ConsoleFramebufferPrivateImpl::getLastCommand()
{
    return m_lastCommand;
}
void ConsoleFramebufferPrivateImpl::clear()
{
   m_toWrite.clear();
 m_colorToWrite.clear();
   m_backColorToWrite.clear();
}
bool ConsoleFramebufferPrivateImpl::IsRunning()
{
    return m_IsRunning;
}
void ConsoleFramebufferPrivateImpl::CloseWindow()
{
    m_IsRunning = false;
}
void ConsoleFramebufferPrivateImpl::copyStringToEnd(std::string string)
{
    std::string newstring = string;
    changeIdxToEnd(newstring);
}

void ConsoleFramebufferPrivateImpl::changeIdxToEnd(std::string& string)
{
    m_historique.push_back(string);
    m_idx = m_historique.size() - 1;
}




ConsoleFramebufferPrivateImpl::ConsoleFramebufferPrivateImpl() :m_handleoutput(GetStdHandle(STD_OUTPUT_HANDLE)), m_handleinput(::GetStdHandle(STD_INPUT_HANDLE)),m_idx(0), m_IsRunning(true)
{
    //prepare the first command
    m_historique.reserve(1);
    m_historique.resize(1);
    updateSze();
   setString("-------New Consol-------", Color::Blue, Color::Black);
}


void ConsoleFramebufferPrivateImpl::resize(int numRows, int numCols)
{
    m_numRows = numRows;
    m_numCols = numCols;
    m_buffer.resize(m_numRows * m_numCols);
    ::ZeroMemory(&m_buffer[0], m_numRows * m_numCols * sizeof(CHAR_INFO));
}



WORD convertForegroundColorToWindows(Color foreground)
{
    switch (foreground)
    {
    case Red:
        return FOREGROUND_RED;

    case Green:
        return FOREGROUND_GREEN;

    case Blue:
        return FOREGROUND_BLUE;

    case White:
        return FOREGROUND_RED + FOREGROUND_GREEN + FOREGROUND_BLUE;

    case Black:
        return 0;

    default:
        throw;
    }
}

WORD convertBackgroundColorToWindows(Color background)
{
    return convertForegroundColorToWindows(background) * 16;
}

WORD convertColorToWindows(Color foreground, Color background)
{
    return convertForegroundColorToWindows(foreground) + convertBackgroundColorToWindows(background);
}

void ConsoleFramebufferPrivateImpl::setCharacter(int row, int col, char car, Color foreground, Color background)
{
    CHAR_INFO& cell = m_buffer[row * m_numCols + col];
    cell.Char.AsciiChar = car;
    cell.Attributes = convertColorToWindows(foreground, background);
}

void ConsoleFramebufferPrivateImpl::show()
{
    printText();
    COORD dwBufferSize;
    dwBufferSize.X = m_numCols;
    dwBufferSize.Y = m_numRows;
    COORD dwBufferCoord;
    dwBufferCoord.X = 0;
    dwBufferCoord.Y = 0;

    SMALL_RECT writeRegion;
    writeRegion.Top = 0;
    writeRegion.Left = 0;
    writeRegion.Right = m_numCols - 1;
    writeRegion.Bottom = m_numRows - 1;

    BOOL result = WriteConsoleOutput(
        m_handleoutput,
        &m_buffer[0],
        dwBufferSize,
        dwBufferCoord,
        &writeRegion
    );
}
int myMin(int a, int b)
{
    //returns the minimum between a and b
    return (a > b) ? b : a;
}
void ConsoleFramebufferPrivateImpl::setString(std::string text, Color color, Color backColor)
{
    m_toWrite.push_back(text);
    m_colorToWrite.push_back(color);
    m_backColorToWrite.push_back(backColor);
}
void ConsoleFramebufferPrivateImpl::setString(int row, int i)
{
    for (int idx = 0; idx < m_toWrite[i].size(); ++idx)
    {
        setCharacter(row, idx, m_toWrite[i][idx], m_colorToWrite[i], m_backColorToWrite[i]);
    }
}
void ConsoleFramebufferPrivateImpl::eraseEmtpyHistorique()
{
    for (auto i = 0; i < m_historique.size() - 1; ++i)
    {
        if (m_historique[i] != "")
            continue;
        auto it = std::find(m_historique.begin(), m_historique.end(), m_historique[i]);
        if (it != m_historique.end())
        {
            --m_idx;
            m_historique.erase(it);
            --i;
        }
    }
}
void ConsoleFramebufferPrivateImpl::printText()
{
    int row = 0;
    auto startVec = m_toWrite.size() - myMin((m_numRows - 1), m_toWrite.size());
    auto stop = m_toWrite.size();
    for (auto i = startVec; i < stop; ++i)
    {
        setString(row, i);
        ++row;
    }
    //write what you write
    for (int idx = 0; idx < m_historique[m_idx].size(); ++idx)
    {
        setCharacter(row, idx, m_historique[m_idx][idx], White, Black);
    }
}

ConsoleFramebuffer::ConsoleFramebuffer():m_impl(new ConsoleFramebufferPrivateImpl)
{}

ConsoleFramebuffer::~ConsoleFramebuffer()
{
    delete m_impl;
    m_impl = nullptr;
}

void ConsoleFramebuffer::setString(std::string text, Color color, Color backColor)
{
    m_impl->setString(text, color, backColor);
}

void ConsoleFramebuffer::show()
{
    m_impl->show();
}

void ConsoleFramebuffer::updateSize()
{
    m_impl->updateSze();
}

void ConsoleFramebuffer::writeConsol()
{
    m_impl->writeConsol();
}

void ConsoleFramebuffer::clear()
{
    m_impl->clear();
}

std::string ConsoleFramebuffer::getLastCommand()
{
    return m_impl->getLastCommand();
}

bool ConsoleFramebuffer::IsRunning()
{
    return m_impl->IsRunning();
}

void ConsoleFramebuffer::CloseWindow()
{
    m_impl->CloseWindow();
}

