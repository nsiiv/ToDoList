#ifndef TITLELINEEDIT_H
#define TITLELINEEDIT_H

#include <QtWidgets/QLineEdit>

class TitleLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    TitleLineEdit(QWidget* parent = nullptr);

protected:
//    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void handleTextEdit(const QString &text);

private:
    int m_maxLength = 50;
};

#endif // TITLELINEEDIT_H
