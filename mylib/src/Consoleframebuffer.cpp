#include "ConsoleFramebuffer.h"

void ConsoleFramebufferPrivateImpl::updatesize()
{

    CONSOLE_SCREEN_BUFFER_INFO sbi;
    BOOL result = GetConsoleScreenBufferInfo(m_handleoutput, &sbi);

    windowWidth = sbi.srWindow.Right - sbi.srWindow.Left + 1;
    windowHeight = sbi.srWindow.Bottom - sbi.srWindow.Top + 1;
    resize(windowHeight, windowWidth);
    eraseemtpyhystorique();
}

void ConsoleFramebufferPrivateImpl::writeconsol()
{
    INPUT_RECORD inputRecord;
    DWORD events;


    ReadConsoleInput(m_handleinput, &inputRecord, 1, &events);


    if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown)
    {

        wchar_t key = inputRecord.Event.KeyEvent.uChar.UnicodeChar;
        WORD virtualKey = inputRecord.Event.KeyEvent.wVirtualKeyCode;
        if (key == '\r') // Si la touche "Entrée" est détectée
        {
            //envoyer le string modifier a faire
            std::string newstring;
            changeidxtoend(newstring);


        }
        else if (virtualKey == VK_UP) // Flèche haut
        {
            if (m_idx == 0)
                return;
            --m_idx;
        }
        else if (virtualKey == VK_DOWN) // Flèche bas
        {
            if (m_idx == m_hystorique.size() - 1)
                return;
            ++m_idx;
        }
        else if (key >= 32)
        {
            if (m_idx != m_hystorique.size() - 1)
                copystringtoend(m_hystorique[m_idx]);
            m_hystorique[m_idx] += key;
        }
        else if (key == '\b' && !m_hystorique.back().empty())
        {
            if (m_idx != m_hystorique.size() - 1)
                copystringtoend(m_hystorique[m_idx]);
            m_hystorique[m_idx].pop_back();
        }



    }
}
void ConsoleFramebufferPrivateImpl::copystringtoend(std::string string)
{
    std::string newstring = string;
    changeidxtoend(newstring);
}

void ConsoleFramebufferPrivateImpl::changeidxtoend(std::string& string)
{
    m_hystorique.push_back(string);
    m_idx = m_hystorique.size() - 1;
}




ConsoleFramebufferPrivateImpl::ConsoleFramebufferPrivateImpl() :m_handleoutput(GetStdHandle(STD_OUTPUT_HANDLE)), m_handleinput(::GetStdHandle(STD_INPUT_HANDLE)),m_idx(0)
{
    m_hystorique.reserve(1);
    m_hystorique.resize(1);
    updatesize();
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
    printtxt();
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
//
int myMin(int a, int b)
{
    return (a > b) ? b : a;
}
void ConsoleFramebufferPrivateImpl::setString(std::string text, Color color, Color backColor)
{
    m_write.push_back(text);
    m_colortowrite.push_back(color);
    m_backcolortowrite.push_back(backColor);
}
void ConsoleFramebufferPrivateImpl::setstring(int row, int i)
{
    for (int idx = 0; idx < m_write[i].size(); ++idx)
    {
        setCharacter(row, idx, m_write[i][idx], m_colortowrite[i], m_backcolortowrite[i]);
    }
}
void ConsoleFramebufferPrivateImpl::eraseemtpyhystorique()
{
    for (auto i = 0; i < m_hystorique.size() - 1; ++i)
    {
        if (m_hystorique[i] != "")
            continue;
        auto it = std::find(m_hystorique.begin(), m_hystorique.end(), m_hystorique[i]);
        if (it != m_hystorique.end())
        {
            --m_idx;
            m_hystorique.erase(it);
            --i;
        }
    }
}
void ConsoleFramebufferPrivateImpl::printtxt()
{

    int row = 0;
    for (auto i = m_write.size() - myMin((m_numRows - 1), m_write.size()); i < m_write.size(); ++i)
    {
        setstring(row, i);
        ++row;
    }
    for (int idx = 0; idx < m_hystorique[m_idx].size(); ++idx)
    {
        setCharacter(row, idx, m_hystorique[m_idx][idx], White, Black);
    }
}

//
//void ConsoleFramebufferPrivateImpl::printString(int row, int col, const std::string& str, Color foreground, Color background)
//{
//    int numCarToWrite = myMin(m_numRows - row, static_cast<int>(str.size()));
//    for (int idx = 0; idx < numCarToWrite; ++idx)
//    {
//        setCharacter(row, col + idx, str[idx], foreground, background);
//        m_row++;
//    }
//    m_col++;
//}
