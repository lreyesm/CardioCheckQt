#include "qopenglwidget_clickable.h"

QOpenGLWidget_Clickable::QOpenGLWidget_Clickable(QWidget *parent):
    QOpenGLWidget(parent)
{
    this->setParent(parent);
}

QOpenGLWidget_Clickable::~QOpenGLWidget_Clickable()
{
    this->deleteLater();
}
