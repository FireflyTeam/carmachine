#include "mainwindow.h"
#include <global_value.h>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <stdlib.h>
#include <QFileDialog>

mainWindow::mainWindow(QWidget *parent):baseWindow(parent)
  ,mediaHasUpdate(false)
{
    // 设置布局只需要设置m_mainwid即可
    //    m_mainwid->setStyleSheet("QLabel{color:white;}");
    initLayout();
    initAnimation();
    initConnection();
    mainwid = this;
    slot_updateMedia2();
}

void mainWindow::initLayout()
{
    m_mainwidup = new mainWidgetUp(m_mainwid);
    m_mainwidlow = new mainWidgetLow(m_mainwid);
    QVBoxLayout *vlyout=new QVBoxLayout;  // m_mainwid's layout(total)
    vlyout->addWidget(m_mainwidup,3);
    vlyout->addWidget(m_mainwidlow,1);
    vlyout->setContentsMargins(0,0,0,0);
    m_mainwid->setLayout(vlyout);

    m_stackedWid = new QStackedWidget(this);
    m_settingwid = new settingWidgets(m_stackedWid);
    m_musicWid  = new musicWidgets(m_stackedWid);
    m_cameraWid = new cameraWidgets(m_stackedWid);
    m_videoWid = new videoWidgets(m_stackedWid);
    m_galleryWid = new galleryWidgets(m_stackedWid,this);

    m_stackedWid->addWidget(m_settingwid);
    m_stackedWid->addWidget(m_musicWid);
    m_stackedWid->addWidget(m_videoWid);
    m_stackedWid->addWidget(m_galleryWid);
    m_stackedWid->addWidget(m_cameraWid);

    m_mainlyout=new QStackedLayout;
    m_mainlyout->addWidget(m_mainwid);
    m_mainlyout->addWidget(m_stackedWid);

    m_mainlyout->setContentsMargins(0,0,0,0);
    setLayout(m_mainlyout);

    m_mainlyout->setCurrentWidget(m_mainwid);
}

void mainWindow::initConnection()
{
    connect(m_mainwidup->m_btnmini,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
    connect(m_mainwidup->m_btnexit,SIGNAL(clicked(bool)),this,SLOT(slot_appQuit()));

    connect(m_settingwid->m_topWid->m_btnmini,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
    connect(m_settingwid->m_topWid->m_btnexit,SIGNAL(clicked(bool)),this,SLOT(slot_appQuit()));
    connect(m_musicWid->m_topwid->m_btnmini,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
    connect(m_musicWid->m_topwid->m_btnexit,SIGNAL(clicked(bool)),this,SLOT(slot_appQuit()));
    connect(m_cameraWid->m_topWid->m_btnmini,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
    connect(m_cameraWid->m_topWid->m_btnexit,SIGNAL(clicked(bool)),this,SLOT(slot_appQuit()));
    connect(m_cameraWid->m_topWid->m_btnreturn,SIGNAL(clicked(bool)),this,SLOT(slot_closeCamera()));
    connect(m_videoWid->m_topWid->m_btnmini,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
    connect(m_videoWid->m_topWid->m_btnexit,SIGNAL(clicked(bool)),this,SLOT(slot_appQuit()));
    connect(m_galleryWid->m_topWid->m_btnmini,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
    connect(m_galleryWid->m_topWid->m_btnexit,SIGNAL(clicked(bool)),this,SLOT(slot_appQuit()));

    connect(m_mainwidlow->m_btnSetUp,SIGNAL(clicked()),this,SLOT(slot_showSetting()));
    connect(m_mainwidlow->m_btnMusic,SIGNAL(clicked()),this,SLOT(slot_showMusic()));
    connect(m_mainwidlow->m_btnVideo,SIGNAL(clicked()),this,SLOT(slot_showVideo()));
    connect(m_mainwidlow->m_btnGallery,SIGNAL(clicked()),this,SLOT(slot_showGallery()));
    connect(m_mainwidlow->m_btnCamera,SIGNAL(clicked()),this,SLOT(slot_showCamera()));

    connect(m_upwidclose,SIGNAL(finished()),this,SLOT(slot_closeanimationfinished()));
    connect(m_lowwidclose,SIGNAL(finished()),this,SLOT(slot_closeanimationfinished()));

    // 返回键——返回主界面
    connect(m_musicWid->m_topwid->m_btnreturn,SIGNAL(clicked(bool)),this,SLOT(slot_returnanimation()));
    connect(m_cameraWid->m_topWid->m_btnreturn,SIGNAL(clicked(bool)),this,SLOT(slot_returnanimation()));
    connect(m_videoWid->m_topWid->m_btnreturn,SIGNAL(clicked(bool)),this,SLOT(slot_returnanimation()));
    //    connect(m_galleryWid->m_topWid->m_btnreturn,SIGNAL(clicked(bool)),this,SLOT(slot_returnanimation()));
    connect(m_settingwid->m_topWid->m_btnreturn,SIGNAL(clicked(bool)),this,SLOT(slot_returnanimation()));

    connect(this,SIGNAL(beginUpdateMediaResource()),this,SLOT(slot_updateMedia1()));
    connect(this,SIGNAL(updateUiByRes(QFileInfoList,QFileInfoList,QMap<QString,QImage>)),this,SLOT(slot_updateUiByRes(QFileInfoList,QFileInfoList,QMap<QString,QImage>)));
}

void mainWindow::slot_appQuit()
{
    m_musicWid->savaSetting();
    m_videoWid->savaSetting();
    this->close();
}

void mainWindow::initAnimation()
{
    // initialize the animation,and position change realize in resize()
    m_upwidclose=new QPropertyAnimation(m_mainwidup,"pos");
    m_lowwidclose=new QPropertyAnimation(m_mainwidlow,"pos");
    m_upwidopen=new QPropertyAnimation(m_mainwidup,"pos");
    m_lowwidopen=new QPropertyAnimation(m_mainwidlow,"pos");
}

void mainWindow::slot_showSetting()
{
    m_stackedWid->setCurrentIndex(0);
    m_upwidclose->start();
    m_lowwidclose->start();
}

void mainWindow::slot_showMusic()
{
    m_stackedWid->setCurrentIndex(1);
    m_upwidclose->start();
    m_lowwidclose->start();

}

void mainWindow::slot_showVideo()
{
    m_stackedWid->setCurrentIndex(2);
    m_upwidclose->start();
    m_lowwidclose->start();
}

void mainWindow::slot_showGallery()
{
    m_stackedWid->setCurrentIndex(3);
    m_upwidclose->start();
    m_lowwidclose->start();
}

void mainWindow::slot_showCamera()
{
    qDebug() << "slot_showCamera";
    m_stackedWid->setCurrentIndex(4);
    m_upwidclose->start();
    m_lowwidclose->start();
    m_cameraWid->openCamera();
}

void mainWindow::slot_returnanimation()
{
    m_mainlyout->setCurrentWidget(m_mainwid);
    m_upwidopen->start();
    m_lowwidopen->start();
}

void mainWindow::slot_closeanimationfinished()
{
    m_mainlyout->setCurrentWidget(m_stackedWid);
}

void mainWindow::slot_updateMedia1()
{
    if(!mediaHasUpdate)
    {
        mediaHasUpdate = true;
        QTimer::singleShot(2000,this,SLOT(slot_updateMedia2()));
    }
}

void mainWindow::slot_updateMedia2()
{
    qDebug()<<"Carmachine: Update media resource.";
    mediaUpdateThread *thread = new mediaUpdateThread(this,this);
    thread->start();
    mediaHasUpdate =false;
}

void mainWindow::slot_updateUiByRes(QFileInfoList musicFileList,QFileInfoList videoFileList,QMap<QString,QImage> imageRes)
{
    m_musicWid->m_middlewid->m_leftWid->m_Swidget0->updateResUi(musicFileList);
    m_videoWid->m_middleWid->m_rightWid->updateResUi(videoFileList);
    m_galleryWid->m_middleWid->updateResUi(imageRes);
    if(m_videoWid->getPlayer()->currentMedia().canonicalUrl().toString()!="")
    {
        m_videoWid->slot_onCurrentMediaChanged(m_videoWid->getPlayer()->currentMedia());
    }
    if(m_musicWid->getPlayer()->currentMedia().canonicalUrl().toString()!="")
    {
        m_musicWid->slot_onCurrentMediaChanged(m_musicWid->getPlayer()->currentMedia());
    }
}

// 解决无边框窗口在最小化之后子控件不刷新的问题
void mainWindow::showEvent(QShowEvent *e)
{
    this->setAttribute(Qt::WA_Mapped);
    QWidget::showEvent(e);
}

void mainWindow::resizeEvent(QResizeEvent*)
{
    m_upwidclose->setStartValue(QPoint(0,0));
    m_upwidclose->setEndValue(QPoint(0,-m_mainwid->height()/4*3));
    m_upwidclose->setDuration(500);

    m_upwidopen->setStartValue(QPoint(0,-m_mainwid->height()/4*3));
    m_upwidopen->setEndValue(QPoint(0,0));
    m_upwidopen->setDuration(500);

    m_lowwidclose->setStartValue(QPoint(0,m_mainwid->height()/4*3));
    m_lowwidclose->setEndValue(QPoint(0,m_mainwid->height()));
    m_lowwidclose->setDuration(500);

    m_lowwidopen->setStartValue(QPoint(0,m_mainwid->height()));
    m_lowwidopen->setEndValue(QPoint(0,m_mainwid->height()/4*3));
    m_lowwidopen->setDuration(500);
}

void mainWindow::slot_standby()
{
    system("echo mem > /sys/power/state");
}


void mainWindow::closeCameraApp()
{
    qDebug() << "closeCameraApp";
    m_cameraWid->closeCamera();
}

void mainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"key value is:"<<event->key();
    switch(event->key())
    {
    // update musicPlayer and videoPlayer's volume by Key
    case Qt::Key_VolumeDown:
        if(m_stackedWid->currentWidget()==m_videoWid){
            m_videoWid->updateVolume(false);;
        }else if(m_stackedWid->currentWidget()==m_musicWid){
            m_musicWid->updateVolume(false);
        }
        QWidget::keyPressEvent(event);
        break;
    case Qt::Key_VolumeUp:
        if(m_stackedWid->currentWidget()==m_videoWid){
            m_videoWid->updateVolume(true);
        }else if(m_stackedWid->currentWidget()==m_musicWid){
            m_musicWid->updateVolume(true);
        }
        QWidget::keyPressEvent(event);
        break;
    case Qt::Key_PowerOff:   // when key_power enter
        if(m_stackedWid->currentWidget()==m_videoWid){
            m_videoWid->setPlayerPause();
        }
        QTimer::singleShot(100, this, SLOT(slot_standby()));
        break;
    default:
        break;
    }
}

mediaUpdateThread::mediaUpdateThread(QObject *parent,mainWindow *mainWindow):QThread(parent)
{
    m_mainWindow = mainWindow;
    qRegisterMetaType<QFileInfoList>("QFileInfoList");
    qRegisterMetaType<QMap<QString,QImage>>("QMap<QString,QImage>");
}

void mediaUpdateThread::run()
{
    QFileInfoList musicFileList = m_mainWindow->m_musicWid->m_middlewid->m_leftWid->m_Swidget0->findMusicFiles(MUSIC_SEARCH_PATH);
    QFileInfoList videoFileList = m_mainWindow->m_videoWid->m_middleWid->m_rightWid->findVideoFiles(VIDEO_SEARCH_PATH);
    QMap<QString,QImage> imageRes = m_mainWindow->m_galleryWid->m_middleWid->getImageResFromPath(MUSIC_SEARCH_PATH);
    emit m_mainWindow->updateUiByRes(musicFileList,videoFileList,imageRes);
}
