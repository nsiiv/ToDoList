#include "TitleLineEdit.h"

#include <QPainter>
#include <QKeyEvent>
#include <QRegExp>

TitleLineEdit::TitleLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    setMaxLength(m_maxLength);
//    connect(this, &QLineEdit::textEdited, this, &TitleLineEdit::handleTextEdit);
}

void TitleLineEdit::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);

    QPainter painter(this);

    QPen customPen = painter.pen();
    QPen limitPen = QPen(Qt::red);

    painter.setRenderHint(QPainter::Antialiasing);

    QFontMetrics fontMetrics = painter.fontMetrics();

    QString lineText = QString::number(text().length()) + "/"
            + QString::number(m_maxLength);

    QRect textRect = fontMetrics.boundingRect(lineText);
    const int x = width() - textRect.width() - 5;
    const int y = height() - textRect.height()/2;

    if(text().length() >= m_maxLength)
        painter.setPen(limitPen);
    else
        painter.setPen(customPen);

    painter.drawText(x, y, lineText);
}

void TitleLineEdit::handleTextEdit(const QString &text)
{
    QLineEdit::setText(text);
}
