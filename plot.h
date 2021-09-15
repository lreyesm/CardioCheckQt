#ifndef PLOT_H
#define PLOT_H

#include "plotpoint.h"
#include "qlabel_button.h"

class Plot: public QCustomPlot
{
    Q_OBJECT
public:
    explicit Plot(QWidget *parent  = 0, int radio_point = 5);

    ~Plot();

    void setup_Graph();

    void clear_Data();

    void add_Data(quint8 graph_i=0, quint32 x =0, quint32 y =0);
    void add_Data(quint8 graph_i, QVector<double> x_vector, QVector<double> y_vector);
    void add_Data(quint8 graph_i, QVector<double> y_vector);

    void set_Range_x_axis_initial(int min, int max){ x_axis_initial_range = QCPRange(min, max); this->xAxis->setRange(min, max);}
    void set_Range_x_axis(QCPRange range){ x_axis_range = range; this->xAxis->setRange(range);}
    void set_Range_x_axis(int min, int max){ x_axis_range = QCPRange(min, max); this->xAxis->setRange(min, max);}
    void set_Range_y_axis_initial(int min, int max){ y_axis_initial_range = QCPRange(min, max); this->yAxis->setRange(min, max);}
    void set_Range_y_axis(QCPRange range){ y_axis_range = range; this->yAxis->setRange(range);}
    void set_Range_y_axis(int min, int max){ y_axis_range = QCPRange(min, max); this->yAxis->setRange(min, max);}

    void set_Size(QSize size){ m_size = size; this->setFixedSize(m_size);}
    void set_maximize_Size(QSize size){ maximize_size = size; /*this->setFixedSize(maximize_size);*/}
    void set_is_Maximized(bool on){ isMaximized = on;}

    void set_position(QPoint position){ m_pos = position; move(m_pos);}
    void set_maximize_position(QPoint position){ maximized_pos = position;}
    void set_Maximized_position_whit_other_maximize(QPoint position){ maximized_pos_with_other_maximize = position;}

    void set_button_maximize(QLabel_Button* button){ button_maximized_with_other = (QLabel_Button*)button; button_maximized_with_other->hide();
                                                     QObject::connect(button_maximized_with_other,SIGNAL(leftClicked()),this,SLOT(maximizar_graph_with_other_button()));}
    void show_button_maximize(bool on);

    void set_background_blur_widget(QWidget* w){ background_blur = w;}
    void set_other_graph1(Plot* graph){ other_graph1 = (Plot*)graph;}
    void set_other_graph2(Plot* graph){ other_graph2 = (Plot*)graph;}


    QCPRange x_axis_Range(){ return x_axis_range;}
    QCPRange y_axis_Range(){ return y_axis_range;}
    QCPRange x_axis_initial_Range(){ return x_axis_initial_range;}
    QCPRange y_axis_initial_Range(){ return y_axis_initial_range;}

    bool is_graph_Maximized(){return isMaximized;}

    QPointF last_Point_After_Moving(){return last_point_after_moving;}
    bool isEKG_Graph(){ return mIsEKG_Graph;}
    void set_IsEKG_Graph(bool on){ mIsEKG_Graph = on;}

    void move_Bracket_right_to_this_pos(int index, QPointF pos);

    void set_Brackets_Visibles(bool on, int index);

    void move_button_maximize(bool up = false);

    void enable_maximize_button(bool on);
    void set_button_maximize_pos(bool up);

    void set_Background_blur(QWidget* blur){background_blur = blur;}

    void set_graph_number(int i=0){ graph_number = i;}
    int graph_Number(int i=0){ return graph_number;}

    QList<PlotPoint *> points;
    quint32 graph_count=0;
    QList<double> graph_points;

    void set_Point_Selected(bool on, int index);
public slots:

    //void testing();
    void minimizar_graph();
    void maximizar_graph();
    void maximizar_graph_with_other_button();
    void fix_Axis();

    void maximize(QPoint maximized_pos);
    void minimize();

signals:

    void shiftStateChanged(bool);
    void maximize_graph(bool);

protected:

    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:



    void stop_Moving_Point_Event(QPointF pos);

private:

    int graph_number;

    quint8 mRadio_points = 5;

    QLabel_Button *button_maximized;
    QLabel_Button *button_minimized;
    QLabel_Button *button_fix_Axis;
    QLabel_Button *button_maximized_with_other;

    bool isMaximized = false;

    QCPRange x_axis_initial_range;
    QCPRange y_axis_initial_range;

    QCPRange x_axis_range;
    QCPRange y_axis_range;

    bool isFirtsPos = false;

    QPoint m_pos;
    QPoint maximized_pos;
    QPoint maximized_pos_with_other_maximize;

    QSize m_size;
    QSize maximize_size;

    QWidget* background_blur;
    Plot *other_graph1;
    Plot *other_graph2;
    bool moving = false;
    qint32 last_moving_point_pos_in_list=-1;
    QPointF last_point_after_moving;
    bool mIsEKG_Graph = false;
};

#endif // PLOT_H
