#include "musiclrcfloatplaywidget.h"
#include "musicuiobject.h"
#include "musicfunctionuiobject.h"
#include "musicapplication.h"

#include <QBoxLayout>
#include <QToolButton>

MusicLrcFloatPlayWidget::MusicLrcFloatPlayWidget(QWidget *parent)
    : MusicFloatAbstractWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(2, 2, 2, 2);
    layout->setSpacing(0);

    m_musicPrevious = new QToolButton(this);
    m_musicNext = new QToolButton(this);
    m_musicKey = new QToolButton(this);
    layout->addWidget(m_musicPrevious);
    layout->addWidget(m_musicKey);
    layout->addWidget(m_musicNext);
    setLayout(layout);

    m_musicPrevious->setStyleSheet(MusicUIObject::MKGBtnPrevious);
    m_musicNext->setStyleSheet(MusicUIObject::MKGBtnNext);

    m_musicPrevious->setCursor(QCursor(Qt::PointingHandCursor));
    m_musicKey->setCursor(QCursor(Qt::PointingHandCursor));
    m_musicNext->setCursor(QCursor(Qt::PointingHandCursor));

    m_musicPrevious->setFixedSize(44, 44);
    m_musicNext->setFixedSize(44, 44);
    m_musicKey->setFixedSize(44, 44);

    connect(m_musicKey, SIGNAL(clicked()), SLOT(musicStatePlay()));
    connect(m_musicPrevious, SIGNAL(clicked()), MusicApplication::instance(), SLOT(musicPlayPrevious()));
    connect(m_musicNext, SIGNAL(clicked()), MusicApplication::instance(), SLOT(musicPlayNext()));

    m_musicKey->setToolTip(tr("Play"));
    m_musicPrevious->setToolTip(tr("Previous"));
    m_musicNext->setToolTip(tr("Next"));

    resizeWindow(0, 0);
    setCurrentPlayState();

    m_firstInit = true;
    show();
}

MusicLrcFloatPlayWidget::~MusicLrcFloatPlayWidget()
{
    delete m_musicPrevious;
    delete m_musicNext;
    delete m_musicKey;
}

QString MusicLrcFloatPlayWidget::getClassName()
{
    return staticMetaObject.className();
}

void MusicLrcFloatPlayWidget::resizeWindow(int width, int height)
{
    m_rectIn = QRect(260 + width/2, 600 + height, 145, 60);
    m_rectOut = QRect(260 + width/2, 655 + height, 145, 60);

    setGeometry(m_rectOut);

    if((width != 0 && height != 0) && m_firstInit && !m_blockAnimation)
    {
        m_firstInit = false;
        animationIn();
    }
}

void MusicLrcFloatPlayWidget::musicStatePlay()
{
    MusicApplication *w = MusicApplication::instance();
    w->musicStatePlay();
    setCurrentPlayState();
}

void MusicLrcFloatPlayWidget::enterEvent(QEvent *event)
{
    MusicFloatAbstractWidget::enterEvent(event);
    setCurrentPlayState();
}

void MusicLrcFloatPlayWidget::setCurrentPlayState()
{
    MusicApplication *w = MusicApplication::instance();
    m_musicKey->setStyleSheet(w->isPlaying() ? MusicUIObject::MKGBtnPause : MusicUIObject::MKGBtnPlay);
}
