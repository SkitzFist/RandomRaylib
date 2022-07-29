#pragma once

class Focusable{
public:
    Focusable();
    const bool isFocused() const;
    void setFocus(const bool focus);
private:
    bool m_isFocused;
};