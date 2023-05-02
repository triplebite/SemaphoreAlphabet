#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QDebug>
#include "time.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //Связь сигнала и слота переключения текущей вкладки
    connect(ui->tabWidget,&QTabWidget::currentChanged, this, &Widget::changeCurrentIndex);

    //Переключаемся на первую вкладку
    ui->tabWidget->setCurrentIndex(0);
    changeCurrentIndex(0);

    //Заполняем массив letters
    this->setLetters();

    //Клик по кнопке Начать
    connect(ui->startButton, &QPushButton::clicked, this, &Widget::startButtonClicked);

    //Меняем картинку
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::nextLetter);

    treningTimer = new QTimer(this);
    connect(treningTimer, &QTimer::timeout, this, &Widget::nextSignal);

    //Клик по кнопке Начать на вкладке Тренировка
    connect(ui->startButton_2, &QPushButton::clicked, this, &Widget::startButton_2_Clicked);

    //Устанавливаем текст для QLabel на вкладке Инфомрация
    this->setHtmlText();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeCurrentIndex(int index)
{
    switch (index) {
    case 0:
        ui->tabWidget->setFixedSize(640, 320);
        this->setFixedSize(660, 340);
        //qDebug() << this->width();
        break;
    case 1:
        ui->tabWidget->setFixedSize(640, 280);
        this->setFixedSize(660, 300);
        //qDebug() << this->width();
        break;
    case 2:
        ui->tabWidget->setFixedSize(640, 740);
        ui->infoLabel->setFixedSize(640, 740);
        //qDebug() << this->width();
        this->setFixedSize(660, 760);
    }
}

void Widget::startButtonClicked()
{

    words = ui->wordsEdit->text().trimmed().toLower();
    if(words.length() > 0){
        currentPosition = 0;
        timer->start(1000);
        ui->startButton->setEnabled(false);
    }
}


void Widget::nextLetter()
{
    if(currentPosition == words.length())
    {
        ui->semaforLabel->setPixmap(QPixmap(":/images/letter_SPACE.png"));
        ui->letterLabel->setText("");
        timer->stop();
        ui->startButton->setEnabled(true);
        return;
    }

    for (int j=0; j<34 ;j++ ) {
          if(letters[j].letter==words[currentPosition]){
                QPixmap pix(letters[j].path);
                ui->semaforLabel->setPixmap(pix);
                if(letters[j].letter==' '){
                    ui->letterLabel->setText("_");
                }else{
                    ui->letterLabel->setText(letters[j].letter.toUpper());
                }
                currentPosition ++;
                break;
           }

    }

}

void Widget::startButton_2_Clicked()
{
    if(question){
        QString messageText;
        if(words==ui->inputEdit->text().trimmed().toLower()){
            messageText = "Отлично!";
        }else{
            messageText = "Неверно! Попробуй ещё.";
        }
        QMessageBox::information(this,"Результат", messageText);
        question = false;
        ui->startButton_2->setText("Начать");
        return;
    }
    QString lite[5] = {"Мама",
                       "Кот",
                       "Дом",
                       "Река",
                       "Сон"
                      };
    QString normal[5] = {"Космос",
                         "Волнение",
                         "Крейсер",
                         "Ремонтник",
                         "Девяносто"
                        };
    QString super[5] = {"Кораблекрушение",
                        "Неизведанное",
                        "Эрудированный",
                        "топливозаливная",
                        "Турбодвигатель"
                       };
    srand(time(0));
    int index = rand() % 5;
    switch (ui->levelComboBox->currentIndex()) {
        case 0:
        words = lite[index].toLower();
        break;
        case 1:
        words = normal[index].toLower();
        break;
        case 2:
        words = super[index].toLower();
    }
    currentPosition = 0;
    int interval = ui->timeSpinBox->value()*1000;
    treningTimer->start(interval);
    if(ui->repeatCheckBox->isChecked()){
        ui->startButton_2->setText("Первое повторение");
    }
    ui->startButton_2->setEnabled(false);

}

void Widget::nextSignal()
{

    if(currentPosition == words.length())
    {
        ui->semaforLabel_2->setPixmap(QPixmap(":/images/letter_SPACE.png"));
        if(ui->repeatCheckBox->isChecked()  and (ui->startButton_2->text()=="Первое повторение")){
            ui->startButton_2->setText("Второе повторение");
            currentPosition = 0;
        }else{
            treningTimer->stop();
            ui->startButton_2->setText("Ответ");
            ui->startButton_2->setEnabled(true);
            question = true;
        }
        return;
    }
    for (int j=0; j<34 ;j++ ) {
          if(letters[j].letter==words[currentPosition]){
                QPixmap pix(letters[j].path);
                ui->semaforLabel_2->setPixmap(pix);
                currentPosition ++;
                break;
           }
    }
}

void Widget::setLetters()
{
    letters[0] =  {":/images/letter_A.png",    L'а'};
    letters[1] =  {":/images/letter_B.png",    L'б'};
    letters[2] =  {":/images/letter_V.png",    L'в'};
    letters[3] =  {":/images/letter_G.png",    L'г'};
    letters[4] =  {":/images/letter_D.png",    L'д'};
    letters[5] =  {":/images/letter_E.png",    L'е'};
    letters[6] =  {":/images/letter_E.png",    L'ё'};
    letters[7] =  {":/images/letter_JE.png",   L'ж'};
    letters[8] =  {":/images/letter_Z.png",    L'з'};
    letters[9] =  {":/images/letter_I.png",    L'и'};
    letters[10] = {":/images/letter_I.png",    L'й'};
    letters[11] = {":/images/letter_K.png",    L'к'};
    letters[12] = {":/images/letter_L.png",    L'л'};
    letters[13] = {":/images/letter_M.png",    L'м'};
    letters[14] = {":/images/letter_N.png",    L'н'};
    letters[15] = {":/images/letter_O.png",    L'о'};
    letters[16] = {":/images/letter_P.png",    L'п'};
    letters[17] = {":/images/letter_R.png",    L'р'};
    letters[18] = {":/images/letter_S.png",    L'с'};
    letters[19] = {":/images/letter_T.png",    L'т'};
    letters[20] = {":/images/letter_U.png",    L'у'};
    letters[21] = {":/images/letter_F.png",    L'ф'};
    letters[22] = {":/images/letter_H.png",    L'х'};
    letters[23] = {":/images/letter_C.png",    L'ц'};
    letters[24] = {":/images/letter_CH.png",   L'ч'};
    letters[25] = {":/images/letter_SH.png",   L'ш'};
    letters[26] = {":/images/letter_SHI.png",  L'щ'};
    letters[27] = {":/images/letter_ZNAK.png", L'ъ'};
    letters[28] = {":/images/letter_ZNAK.png", L'ь'};
    letters[29] = {":/images/letter_II.png",   L'ы'};
    letters[30] = {":/images/letter_YU.png",   L'ю'};
    letters[31] = {":/images/letter_YA.png",   L'я'};
    letters[32] = {":/images/letter_E.png",    L'э'};
    letters[33] = {":/images/letter_SPACE.png", ' '};
}

void Widget::setHtmlText()
{
    QString html =
        "<html>"
        "  <head>"
        "    <style>"
        "      h2 {"
        "         color:#7e85b6;"
        "      }"
        "      p {"
        "         color:#333333;"
        "      }"
        "    </style>"
        "  </head>"
        "  <body>"
        "    <h2>История</h2>"

        "    <p>Существующую сегодня на флоте русскую семафорную азбуку "
        "    разработал в 1895 году вице-адмирал Степан Осипович Макаров. "
        "    Русская семафорная азбука составлена в соответствии с русским "
        "    алфавитом, включает 29 буквенных и 3 служебных знака. Она не содержит "
        "    цифр и знаков препинания. Их передача производится по буквам, словами.</p>"

        "    <p>Передача информации семафором производится сигнальщиками с помощью "
        "    флажков, размер ткани которых составляет 30x35 см. Цвет ткани флажков "
        "    зависит от времени суток: в тёмное время суток используются флажки с "
        "    тканью светлого тона (желтый, белый), а в светлое время суток - с тканью "
        "    тёмного тона (красный, чёрный). При отсутствии флажков семафорят бескозырками.</p>"

        "    <p>С 1 декабря 2011 года <i>флажное сигналопроизводство</i> исключено из учебной программы младших "
        "    специалистов связи ВМФ. Вместо семафора связисты будут больше времени "
        "    уделять изучению световой сигнализации азбукой Морзе. "
        "    Курс семафорной азбуки оставлен только в рамках курсов подготовки молодого "
        "    бойца, как наиболее незаметный для противника способ передачи информации.</p>"
        "    <h2>Сигналы</h2>"
        "    <p><img src=':/images/all.jpg' width='400'></p>"
        "  </body>"
        "</html>";
    ui->infoLabel->setWordWrap(true);
    ui->infoLabel->setText(html);
}

