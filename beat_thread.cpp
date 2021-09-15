#include "beat_thread.h"
#include <QtCore>

Beat_Thread::Beat_Thread(QObject *parent)
{
    //this->setParent(parent);

    timer_beat = new QTimer(this);
    connect(timer_beat,SIGNAL(timeout()),this,SLOT(on_time_out_sonud_beat()));
    timer_beat->setInterval(1000);
    timer_finished = false;

    beat_sound.setParent(this);
}

Beat_Thread::~Beat_Thread()
{
    timer_beat->deleteLater();
}


void Beat_Thread::set_WAV_Dir(QString dir)
{
    beat_sound.setSource(QUrl::fromLocalFile(dir));
    //effect.setLoopCount(QSoundEffect::Infinite);
    beat_sound.setVolume(0.5f);
    //effect.play();
    connect(timer_beat,SIGNAL(timeout()),&beat_sound,SLOT(play()));
}

void Beat_Thread::on_time_out_sonud_beat()
{
    timer_finished = true;
    timer_beat->setInterval(next_Interval);
}

void Beat_Thread::start_timer(int interval)
{
    timer_beat->setInterval(interval);
    timer_beat->start();
}

void Beat_Thread::set_Interval(int interval)
{
    next_Interval = interval;
}

bool Beat_Thread::stop_timer()
{
    timer_beat->stop();
}

