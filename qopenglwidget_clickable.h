#ifndef QOPENGLWIDGET_CLICKABLE_H
#define QOPENGLWIDGET_CLICKABLE_H

#include <QOpenGLWidget>

class QOpenGLWidget_Clickable : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit QOpenGLWidget_Clickable(QWidget *parent = nullptr);
    ~QOpenGLWidget_Clickable();
};

#endif // QOPENGLWIDGET_CLICKABLE_H
