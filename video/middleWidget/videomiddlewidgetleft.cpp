#include "videomiddlewidgetleft.h"
#include <QHBoxLayout>
#include <QTime>
#include "global_value.h"

videoMiddleWidgetLeft::videoMiddleWidgetLeft(QWidget *parent):baseWidget(parent)
{
    setStyleSheet("background:rgb(10,10,10)");
    initLayout();
    connect(m_slider,SIGNAL(sig_sliderPositionChanged(int)),this,SIGNAL(sig_sliderPositionChanged(int)));
}

void videoMiddleWidgetLeft::initLayout()
{
    vmainlyout = new QVBoxLayout;

    m_contentWid = new videoContentWidget(this);

    m_slider = new videoSlider(Qt::Horizontal,this);
    m_slider->setRange(0,0);

    m_currentTime = new QLabel("00:00",this);
    m_currentTime->setFont(QFont(Font_Family,Font_size_Small,QFont::Normal));
    m_currentTime->setStyleSheet("color:rgb(150,150,150);");

    m_totalTime = new QLabel("00:00",this);
    m_totalTime->setFont(QFont(Font_Family,Font_size_Small,QFont::Normal));
    m_totalTime->setStyleSheet("color:rgb(150,150,150);");

    QHBoxLayout *m_positionLayout = new QHBoxLayout;
    m_positionLayout->addWidget(m_currentTime);
    m_positionLayout->addWidget(m_slider);
    m_positionLayout->addWidget(m_totalTime);

    m_positionWid = new QWidget(this);
    m_positionWid->setFixedHeight(85);
    m_positionWid->setStyleSheet("background:rgb(31,31,31)");
    m_positionWid->setLayout(m_positionLayout);


    vmainlyout->addWidget(m_contentWid);
    vmainlyout->addWidget(m_positionWid);
    vmainlyout->setContentsMargins(0,0,0,0);
    vmainlyout->setSpacing(0);

    removePositionWidget();

    setLayout(vmainlyout);
}

void videoMiddleWidgetLeft::addPositionWidget()
{
    m_positionWid->show();
    vmainlyout->addWidget(m_positionWid);
    update();
}

void videoMiddleWidgetLeft::removePositionWidget()
{
    m_positionWid->hide();
    vmainlyout->removeWidget(m_positionWid);
    update();
}

void videoMiddleWidgetLeft::onDurationChanged(qint64 duration)
{
    m_slider->setRange(0, duration);
    QTime totalTime((duration % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60),
                    (duration % (1000 * 60 * 60)) / (1000 * 60),
                    (duration % (1000 * 60)) / 1000);
    m_totalTime->setText(totalTime.toString("hh:mm:ss"));
}

void videoMiddleWidgetLeft::onMediaPositionChanged(qint64 position)
{
    m_slider->setValue(position);
    QTime currentTime((position % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60),
                    (position % (1000 * 60 * 60)) / (1000 * 60),
                    (position % (1000 * 60)) / 1000);
    m_currentTime->setText(currentTime.toString("hh:mm:ss"));

}
