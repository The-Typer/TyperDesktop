#include "EnterMenu.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QKeyEvent>
#include <QAbstractItemView>

typer::gui::EnterMenu::EnterMenu(const QStringList & wordTypes,
                                 QWidget *parent)
    : QWidget( parent )
    , m_wordTypeComboBox(new QComboBox(this))
    , m_timeComboBox( new QComboBox(this) )
{
    buildForm(wordTypes);
    setFocusPolicy(Qt::StrongFocus);
}

void typer::gui::EnterMenu::setCurentSettings(const QString &wordType, int time)
{
    m_wordTypeComboBox->setCurrentText(wordType);
    m_timeComboBox->setCurrentText(timeToStr(time));
}

void typer::gui::EnterMenu::keyReleaseEvent(QKeyEvent *event)
{
    QWidget::keyReleaseEvent(event);
    bool spacePressed = (event->key() == Qt::Key_Space);
    if ( spacePressed ) {
        emitStart();
    }
}

void typer::gui::EnterMenu::resizeEvent(QResizeEvent *event)
{
    updateComboBoxesPos();
    QWidget::resizeEvent(event);
}

void typer::gui::EnterMenu::showEvent(QShowEvent *event)
{
    setFocus();
    updateComboBoxesPos();
    QWidget::showEvent(event);
}

void typer::gui::EnterMenu::emitStart()
{
    emit start(m_wordTypeComboBox->currentText(),
               strToTime(m_timeComboBox->currentText()));
}

void typer::gui::EnterMenu::buildForm(const QStringList &wordTypes)
{
    QVBoxLayout * buttonLayout = new QVBoxLayout();
    const int BUTTON_WIDTH = 300;
    const int BUTTON_HEIGHT = 50;

    QPushButton * startButton = new QPushButton("press space to start", this);
    startButton->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0); color: gray;}");

    startButton->setFixedWidth( BUTTON_WIDTH );
    startButton->setFixedHeight( BUTTON_HEIGHT );
    connect( startButton, &QPushButton::clicked, this, &EnterMenu::emitStart);

    QPalette startButtonPallete = startButton->palette();
    startButtonPallete.setColor(QPalette::WindowText, Qt::gray);
    startButton->setPalette(startButtonPallete);

    QFont font = startButton->font();
    font.setPointSize(18);
    startButton->setFont(font);

    buttonLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding) );
    buttonLayout->addWidget( startButton );
    buttonLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding) );

    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding) );
    mainLayout->addLayout( buttonLayout );
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding) );

    setLayout( mainLayout );

    font.setPointSize(14);
    m_wordTypeComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    m_wordTypeComboBox->setFont(font);
    m_wordTypeComboBox->setPalette(startButtonPallete);
    m_wordTypeComboBox->move(0, 0);
    m_wordTypeComboBox->addItems(wordTypes);

    m_timeComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    m_timeComboBox->setFont(font);
    m_timeComboBox->setPalette(startButtonPallete);
    //m_timeComboBox->move(0, 0);
    const QStringList times = QStringList()
                              << timeToStr(15)
                              << timeToStr(30)
                              << timeToStr(60)
                              << timeToStr(120);
    m_timeComboBox->addItems(times);

    m_timeComboBox->setStyleSheet("QComboBox { background-color: transparent; color: gray;}");

    m_timeComboBox->view()->setStyleSheet("QComboBox QAbstractItemView { background-color: transparent;  color: white; } "
                                          " QComboBox QAbstractItemView::item:selected { background-color: rgb(40, 40, 40); }"
                                          " QComboBox QAbstractItemView::item {background-color: gray; } ");

    m_wordTypeComboBox->setStyleSheet("QComboBox { background-color: transparent; color: gray;}");
    m_wordTypeComboBox->view()->setStyleSheet("QComboBox QAbstractItemView { background-color: transparent;  color: white; } "
                                          " QComboBox QAbstractItemView::item:selected { background-color: rgb(40, 40, 40); }"
                                          " QComboBox QAbstractItemView::item {background-color: gray; }");


    connect(m_timeComboBox, &QComboBox::currentTextChanged, m_timeComboBox, [startButton]() {
        startButton->setFocus();
    });

    connect(m_wordTypeComboBox, &QComboBox::currentTextChanged, m_timeComboBox, [startButton]() {
        startButton->setFocus();
    });
    m_wordTypeComboBox->adjustSize();

    updateComboBoxesPos();
}

void typer::gui::EnterMenu::updateComboBoxesPos()
{
    int widgetWidth = size().width();
    int cbWidth     = m_timeComboBox->sizeHint().width();
    m_timeComboBox->move(widgetWidth - cbWidth - 10, 10);
    m_wordTypeComboBox->move(QPoint(10, 10));
}

QString typer::gui::EnterMenu::timeToStr(int time)
{
    return QString::number(time) + " s";
}

int typer::gui::EnterMenu::strToTime(const QString &timeStr)
{
    QStringList splitedTime = timeStr.split(' ');
    Q_ASSERT(splitedTime.size());
    return splitedTime[0].toInt();
}
