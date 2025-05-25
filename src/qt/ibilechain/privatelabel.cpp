// Copyright (c) 2022 The Ibilechain Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "qt/ibilechain/privatelabel.h"
#include <iostream>

PrivateQLabel::PrivateQLabel(QWidget* parent) : QLabel(parent)
{
}

PrivateQLabel::PrivateQLabel(const QString& text, QWidget* parent, Qt::WindowFlags f) : QLabel(text, parent, f)
{
    setText(text);
}

PrivateQLabel::~PrivateQLabel()
{
}

QString PrivateQLabel::text() const
{
    return QLabel::text();
}

void PrivateQLabel::refresh()
{
    if (_isPrivate && !_isHovered)
        QLabel::setText(_masked);
    else
        QLabel::setText(_text);
}

void PrivateQLabel::setText(const QString& text)
{
    _text = text;
    refresh();
}

void PrivateQLabel::enterEvent(QEvent*)
{
    setIsHovered(true);
}

void PrivateQLabel::leaveEvent(QEvent*)
{
    setIsHovered(false);
}

void PrivateQLabel::setIsPrivate(bool value)
{
    _isPrivate = value;
    refresh();
}

void PrivateQLabel::setIsHovered(bool value)
{
    _isHovered = value;
    refresh();
}