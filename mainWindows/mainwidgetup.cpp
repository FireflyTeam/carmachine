#include "mainwidgetup.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDateTime>
#include "global_value.h"

mainWidgetUp::mainWidgetUp(QWidget *parent):baseWidget(parent)
{
    // 设置mainwid上半部分背景
    setObjectName("mainWidgetUp");
    setStyleSheet("QWidget#mainWidgetUp{border-image: url(:/image/main/mainwidUp_bg.jpg)}");

    initLayout();

    // 连接定时器的信号
    m_timer = new QTimer;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slot_updatetime()));
    m_timer->start(1000);
}

void mainWidgetUp::initLayout()
{
    QVBoxLayout *vmainyout = new QVBoxLayout;
    // first layout
//    QHBoxLayout *hyout1=new QHBoxLayout;

//    m_btnexit=new flatButton(this);
//    m_btnmini=new flatButton(this);
//    m_btnmobile=new flatButton(this);
//    m_btnsetting=new flatButton(this);

//    m_btnexit->setFixedSize(25,25);
//    m_btnmini->setFixedSize(25,25);
//    m_btnmobile->setFixedSize(25,25);
//    m_btnsetting->setFixedSize(25,25);

//    m_btnexit->setStyleSheet("QPushButton{border-image:url(:/image/main/btn_close (1).png);}"
//                             "QPushButton::hover{border-image:url(:/image/main/btn_close (2).png);}"
//                             "QPushButton::pressed{border-image:url(:/image/main/btn_close (3).png);}");
//    m_btnmini->setStyleSheet("QPushButton{border-image:url(:/image/main/btn_mini (1).png);}"
//                             "QPushButton::hover{border-image:url(:/image/main/btn_mini (2).png);}"
//                             "QPushButton::pressed{border-image:url(:/image/main/btn_mini (3).png);}");
//    m_btnmobile->setStyleSheet("QPushButton{border-image:url(:/image/main/btn_mobile (1).png);}"
//                               "QPushButton::hover{border-image:url(:/image/main/btn_mobile (2).png);}"
//                               "QPushButton::pressed{border-image:url(:/image/main/btn_mobile (3).png);}");
//    m_btnsetting->setStyleSheet("QPushButton{border-image:url(:/image/main/btn_setting (1).png);}"
//                                "QPushButton::hover{border-image:url(:/image/main/btn_setting (2).png);}"
//                                "QPushButton::pressed{border-image:url(:/image/main/btn_setting (3).png);}");

//    QLabel*label1=new QLabel("丨",this);
//    label1->setFixedSize(6,16);
//    label1->setStyleSheet("color:rgb(255,255,255,255);");
//    label1->adjustSize();

//    hyout1->addStretch(0);
//    hyout1->addWidget(label1);
//    hyout1->addWidget(m_btnmobile);
//    hyout1->addWidget(m_btnsetting);
//    hyout1->addWidget(m_btnmini);
//    hyout1->addWidget(m_btnexit);
//    hyout1->setSpacing(12);
    // first layout end

    // second layout
    QLabel *m_titleText = new QLabel("Qt Demo Application",this);
    m_titleText->setAlignment(Qt::AlignCenter);
    m_titleText->setFont(QFont(Font_Family,Font_Size_Big,QFont::Bold));
    m_titleText->setStyleSheet("color:rgb(255,255,255,255);");
    m_titleText->adjustSize();

    m_lbltime=new QLabel("",this);
    m_lbltime->setAlignment(Qt::AlignCenter);
    m_lbltime->setFont(QFont(Font_Family,Font_Size_Big,QFont::Bold));
    m_lbltime->setStyleSheet("color:rgb(255,255,255,255);");
    m_lbltime->adjustSize();
    // second layout end

//    vmainyout->addLayout(hyout1);
    vmainyout->addStretch(0);
    vmainyout->addWidget(m_titleText);
    vmainyout->addSpacing(40);
    vmainyout->addWidget(m_lbltime,0);
    vmainyout->addStretch(0);
    vmainyout->setSpacing(0);
    vmainyout->setContentsMargins(10,10,10,10);
    setLayout(vmainyout);
}

void mainWidgetUp::slot_updatetime()
{
    QString timeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    m_lbltime->setText("Time:"+timeStr);
}
