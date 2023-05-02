#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
struct Letter{
    QString path;
    QChar letter;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void changeCurrentIndex(int index);
    void startButtonClicked();
    void startButton_2_Clicked();
    void nextLetter();
    void nextSignal();

private:
    Ui::Widget *ui;
    Letter letters[34];
    void setLetters();
    void setHtmlText();
    QString words;
    int currentPosition;
    QTimer *timer;
    QTimer *treningTimer;
    bool question = false;
};
#endif // WIDGET_H
