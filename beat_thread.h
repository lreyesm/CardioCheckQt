#ifndef BEAT_THREAD_H
#define BEAT_THREAD_H

#include <QThread>
#include <QTimer>
#include <QSoundEffect>


class Beat_Thread: public QThread
{
    Q_OBJECT

public:

    explicit Beat_Thread(QObject *parent = 0);
    //Initialize(int interval = 1000);
    ~Beat_Thread();

    QTimer *timer_beat;
    bool timer_finished;
    void set_WAV_Dir(QString dir);

public slots:

    void on_time_out_sonud_beat();
    void start_timer(int interval = 1000);
    void set_Interval(int interval = 1000);
    bool stop_timer();
    //void run();

signals:
    void time_Out_beat(const bool result);

private:

    quint16 next_Interval = 0;
    QSoundEffect beat_sound;
};

#endif // BEAT_THREAD_H
