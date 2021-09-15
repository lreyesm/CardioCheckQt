#include "plot.h"
#include <QDebug>

Plot::Plot(QWidget *parent, int radio_point)
    :QCustomPlot(parent)
{

    this->setParent(parent);
    //mPointUnderCursor = new PlotPoint(this, radio_point);
    //this->addItem(mPointUnderCursor);

    mRadio_points = radio_point;

    //setSelectionTolerance(radio_point*2); //para android duplicar la seleccion de tolerancia


}

Plot::~Plot()
{
    this->deleteLater();
}

void Plot::setup_Graph(){

    button_maximized = new QLabel_Button((QOpenGLWidget*)this);
    button_maximized->setFixedSize(100,100);
    button_maximized->move(625,5);
    button_maximized->setStyleSheet(QStringLiteral("border-image: url(:/icons/fondo_transparente.png); background-image: url(:/icons/fondo_transparente.png);"));
    button_maximized->setPixmap(QPixmap(":/icons/maximize_graph.png"));
    button_maximized->setAlignment(Qt::AlignTop| Qt::AlignRight);
    button_maximized->hide();
    //button_maximized->show();

    button_minimized = new QLabel_Button((QOpenGLWidget*)this);
    button_minimized->setFixedSize(100,100);
    button_minimized->move(980,10);
    //button_minimized->move(525,10);
    button_minimized->setStyleSheet(QStringLiteral("border-image: url(:/icons/fondo_transparente.png); background-image: url(:/icons/fondo_transparente.png);"));
    button_minimized->setPixmap(QPixmap(":/icons/minimize_graph.png"));
    button_minimized->setAlignment(Qt::AlignTop | Qt::AlignRight);
    button_minimized->hide();

    button_fix_Axis = new QLabel_Button((QOpenGLWidget*)this);
    button_fix_Axis->setFixedSize(100,100);
    button_fix_Axis->move(980,190);
    //button_fix_Axis->move(625,40);
    button_fix_Axis->setStyleSheet(QStringLiteral("border-image: url(:/icons/fondo_transparente.png); background-image: url(:/icons/fondo_transparente.png);"));
    button_fix_Axis->setPixmap(QPixmap(":/icons/fix_graph_zoom.png"));
    button_fix_Axis->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    button_fix_Axis->hide();
    //button_maximized->show();

    //QObject::connect(button_maximized_help,SIGNAL(leftClicked()),this,SLOT(testing()));
    QObject::connect(button_maximized,SIGNAL(leftClicked()),this,SLOT(maximizar_graph()));
    QObject::connect(button_minimized,SIGNAL(leftClicked()),this,SLOT(minimize()));
    QObject::connect(button_fix_Axis,SIGNAL(leftClicked()),this,SLOT(fix_Axis()));

    QVector<double> time_x_axis(100),concentration_y_axis(100);

    for(int i=0; i< 100; i++){
        time_x_axis[i]=0;
        concentration_y_axis[i]=0;

    }
    this->addGraph();
    this->graph(0)->setData(time_x_axis,concentration_y_axis);

    //Para version android eliminar este codigo-------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------
    this->addGraph();
    this->graph(1)->setData(time_x_axis,concentration_y_axis);
    //------------------------------------------------------------------------------------------------------------------------

    this->xAxis->setVisible(false);
    this->yAxis->setVisible(false);

    this->xAxis->setTickLabelRotation(60);

    this->xAxis->setTickLength(0, 4);

    this->setBackground(QBrush(QColor(Qt::black)));
    //this->setBackground(QBrush(QColor(Qt::white)));

    this->setAutoFillBackground(true);

    this->setPlottingHints(QCP::phFastPolylines | QCP::phForceRepaint | QCP::phCacheLabels);
    this->setAntialiasedElements(QCP::aeNone);

    this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    //Con esto se puede modificar el zoom vertical u horizontal
    //this->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);

    //Solo para version android-------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------
    this->setAttribute(Qt::WA_AcceptTouchEvents,true);
    this->grabGesture(Qt::PanGesture);
    //------------------------------------------------------------------------------------------------------------------------

    PlotPoint *point = new PlotPoint(this,5,"");
    point->setColor(QColor(255,255,255));

    point->set_Item_index_in_list(0);

    point->setSelectable(false);

    points.append(point);
    this->addItem(point);
}

void Plot::enable_maximize_button(bool on){ //muestra boton para maximizar

    if(on){

        button_maximized->show();
        button_fix_Axis->hide();
        button_minimized->hide();
    }
    else{

        button_maximized->hide();
        button_fix_Axis->show();
        button_minimized->show();
    }
}

void Plot::clear_Data(){

    for(qint16 i=0; i<this->graphCount(); i++){
        this->graph(i)->data()->clear();
    }
    this->xAxis->setRange(x_axis_initial_range);
    this->replot(QCustomPlot::rpHint);
}

void Plot::add_Data(quint8 graph_i, quint32 x, quint32 y)
{
    if(graph_i==0){
        graph_count = x;
        graph_points.append(y);
    }
    this->graph(graph_i)->addData(x,y);
}

void Plot::add_Data(quint8 graph_i, QVector<double> x_vector, QVector<double> y_vector)
{
    if(graph_i==0){
        graph_count = x_vector.first();

        for(quint8 i=0; i< y_vector.length();i++){
            graph_points.append(y_vector[i]);
        }
    }
    this->graph(graph_i)->addData(x_vector,y_vector);
}

void Plot::add_Data(quint8 graph_i, QVector<double> y_vector)
{
    clear_Data();

    if(graph_i==0){

        QVector<double> x_vector;
        x_vector.clear();
        for(quint16 i=0; i< y_vector.length();i++){
            x_vector.append(i+1);
        }
        graph_points.append(y_vector.toList());
        graph_count = x_vector.last();

        this->graph(graph_i)->addData(x_vector,y_vector);
    }
}

void Plot::show_button_maximize(bool on){

    if(on){
        button_maximized_with_other->show();
        button_maximized_with_other->raise();
    }
    else{
        button_maximized_with_other->hide();
    }
}

void Plot::set_button_maximize_pos(bool up)
{
    if(up){
        button_maximized_with_other->move(button_maximized_with_other->pos().x(), 200);
    }
    else{
        button_maximized_with_other->move(button_maximized_with_other->pos().x(), 500);
    }
}

void Plot::fix_Axis(){

    if(x_axis_range.upper <= x_axis_initial_range.upper){

        this->set_Range_x_axis(x_axis_initial_Range());
    }
    else{
        this->set_Range_x_axis(x_axis_Range());
    }
    this->set_Range_y_axis(y_axis_initial_Range());
    this->replot(QCustomPlot::rpHint);
}

void Plot::move_button_maximize(bool up){

    if(up){

        button_maximized_with_other->move(button_maximized_with_other->pos().x(), 200);
    }
    else{

        button_maximized_with_other->move(button_maximized_with_other->pos().x(), 500);
    }
}

void Plot::minimizar_graph(){

    isMaximized = false;
    isFirtsPos=false;

    enable_maximize_button(true);

    show_button_maximize(false);

    setFixedSize(m_size);
    move(m_pos);
    show();

    replot();
}


void Plot::maximizar_graph_with_other_button(){

    maximizar_graph();
}

void Plot::maximizar_graph(){

    if(other_graph1->is_graph_Maximized() && other_graph2->is_graph_Maximized()){
        return;
    }

    isMaximized = true;

    if(other_graph1->is_graph_Maximized() || other_graph2->is_graph_Maximized()){

        if(other_graph1->pos() != maximized_pos && other_graph2->pos() != maximized_pos){
            maximize(maximized_pos);
            isFirtsPos=true;
            //this->button_fix_Axis->show();
        }
        else{
            maximize(maximized_pos_with_other_maximize);
            isFirtsPos=false;
        }
        this->show();
    }
    else{

        maximize(maximized_pos);
        other_graph1->show_button_maximize(true); //si es el primero maximizado enseño los 2 botones para maximizar otras graficas
        other_graph2->show_button_maximize(true);
    }

    if(!other_graph1->is_graph_Maximized()){

        other_graph1->setFixedSize(maximize_size);
        other_graph1->hide();

    }
    if(!other_graph2->is_graph_Maximized()){

        other_graph2->setFixedSize(maximize_size);
        other_graph2->hide();
    }

    this->parentWidget()->move(0,0);

    background_blur->setParent(this->parentWidget());

    background_blur->move(0,0);
    background_blur->stackUnder(this);

    if(other_graph1->is_graph_Maximized())
        background_blur->stackUnder(other_graph1);

    if(other_graph2->is_graph_Maximized())
        background_blur->stackUnder(other_graph2);

    background_blur->show();

    this->replot(/*QCustomPlot::rpHint*/);
}


void Plot::mouseDoubleClickEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton) {

        moving = false;

        PlotPoint *plotPoint = qobject_cast<PlotPoint*>(itemAt(event->localPos(), true));

        if(plotPoint == 0){

            PlotPoint *point = new PlotPoint(this, mRadio_points, QString::number(points.isEmpty()? 0:points.last()->point_text().toInt() + 1) );
            PlotPoint *point_other_graph1 = new PlotPoint(other_graph1, mRadio_points, QString::number(points.isEmpty()? 0:points.last()->point_text().toInt() + 1) );
            PlotPoint *point_other_graph2 = new PlotPoint(other_graph2, mRadio_points, QString::number(points.isEmpty()? 0:points.last()->point_text().toInt() + 1) );

            point_other_graph1->setColor(point->color());
            point_other_graph2->setColor(point->color());


            if(isEKG_Graph()){

                point->set_Is_EKG_graph_point(true);
            }
            else if(other_graph2->isEKG_Graph()){

                point_other_graph2->set_Is_EKG_graph_point(true);
            }

            point->set_Item_index_in_list(points.length());
            point_other_graph1->set_Item_index_in_list(other_graph1->points.length());
            point_other_graph2->set_Item_index_in_list(other_graph2->points.length());

            last_moving_point_pos_in_list = points.length();

            points.append(point);
            this->addItem(point);

            other_graph1->points.append(point_other_graph1);
            other_graph1->addItem(point_other_graph1);
            other_graph2->points.append(point_other_graph2);
            other_graph2->addItem(point_other_graph2);

            double coord_x_this = this->xAxis->pixelToCoord(event->localPos().x());
            double coord_x_other_graph1 = other_graph1->xAxis->pixelToCoord(event->localPos().x());
            double coord_x_other_graph2 = other_graph2->xAxis->pixelToCoord(event->localPos().x());

            if(graph_points.length() > (int)coord_x_this){

                points.last()->set_Position(coord_x_this, graph_points[(int)coord_x_this]);
                other_graph1->points.last()->set_Position(coord_x_other_graph1, other_graph1->graph_points[(int)coord_x_other_graph1]);
                other_graph2->points.last()->set_Position(coord_x_other_graph2, other_graph2->graph_points[(int)coord_x_other_graph2]);
            }
            else{
                (qobject_cast<PlotPoint*>(this->item()))->movePx(event->x(), event->y()); //mueve el ultimo item de la lista a la posicion requerida
                (qobject_cast<PlotPoint*>(other_graph1->item()))->movePx(event->x(), event->y()); //mueve el ultimo item de la lista a la posicion requerida
                (qobject_cast<PlotPoint*>(other_graph2->item()))->movePx(event->x(), event->y()); //mueve el ultimo item de la lista a la posicion requerida
            }

            if(points.length()>1){ //si hay mas de un punto mostrar bracket

                point->add_Bracket(points.at(points.length()-2)->pos());
                points.at(points.length()-2)->set_Bracket_visible(false);

                if(isEKG_Graph()){

                    point_other_graph1->add_Bracket(QPointF(points.at(points.length()-2)->pos().x()/4,
                                                            points.at(points.length()-2)->pos().y()/40.96));
                    point_other_graph2->add_Bracket(QPointF(points.at(points.length()-2)->pos().x()/4,
                                                            points.at(points.length()-2)->pos().y()/40.96));
                    other_graph1->points.at(other_graph1->points.length()-2)->set_Bracket_visible(false);
                    other_graph2->points.at(other_graph2->points.length()-2)->set_Bracket_visible(false);
                }
                else{
                    point_other_graph1->add_Bracket(other_graph1->points.at(other_graph1->points.length()-2)->pos());
                    other_graph1->points.at(other_graph1->points.length()-2)->set_Bracket_visible(false);

                    if(other_graph2->isEKG_Graph()){
                        point_other_graph2->add_Bracket(QPointF(points.at(points.length()-2)->pos().x()*4,
                                                                points.at(points.length()-2)->pos().y()*40.96));
                    }
                    else{
                        point_other_graph2->add_Bracket(other_graph2->points.at(other_graph2->points.length()-2)->pos());
                    }
                    other_graph2->points.at(other_graph2->points.length()-2)->set_Bracket_visible(false);
                }
            }

            //point->set_Point_Text(QString::number(coord_x)); //el mouse devuelve pixeles de posicion y la grafica recibe coordenadas para posicionar

            //point->set_Point_Text(QString::number(graph_points[(int)coord_x])); //el mouse devuelve pixeles de posicion y la grafica recibe coordenadas para posicionar

            replot(QCustomPlot::rpHint);
            other_graph1->replot(QCustomPlot::rpHint);
            other_graph2->replot(QCustomPlot::rpHint);
        }
        ///remover si dobleclick sobre punto
        else if (points.contains(plotPoint)){  //eliminar punto

            int index = points.indexOf(plotPoint);

            if(index +1  < points.length()){ //esconde brackets de punto siguiente

                set_Brackets_Visibles(false,index +1 );
            }

            if(points.last() != points.at(index) && points.length()>1){ //Al eliminar un punto modificar la llave del siguiente con el anterior punto

                if(points.first() != points.at(index)){

                    points.at(index+1)->move_Bracket_right(points.at(index-1)->pos());

                    if(isEKG_Graph()){
                        other_graph1->points.at(index+1)->move_Bracket_right(QPointF(points.at(index-1)->pos().x()/4,
                                                                                     points.at(index-1)->pos().y()/40.96));
                        other_graph2->points.at(index+1)->move_Bracket_right(QPointF(points.at(index-1)->pos().x()/4,
                                                                                     points.at(index-1)->pos().y()/40.96));
                    }
                    else{
                        other_graph1->points.at(index+1)->move_Bracket_right(other_graph1->points.at(index-1)->pos());
                        if(other_graph2->isEKG_Graph()){
                            other_graph2->points.at(index+1)->move_Bracket_right(QPointF(points.at(index-1)->pos().x()*4,
                                                                                         points.at(index-1)->pos().y()*40.96));
                        }
                        else{
                            other_graph2->points.at(index+1)->move_Bracket_right(other_graph2->points.at(index-1)->pos());
                        }
                    }
                }
            }
            last_moving_point_pos_in_list--;

            points.at(index)->set_Point_visible(false);
            other_graph1->points.at(index)->set_Point_visible(false);
            other_graph2->points.at(index)->set_Point_visible(false);


            points.removeAt(index);
            this->removeItem(index);

            other_graph1->points.removeAt(index);
            other_graph1->removeItem(index);
            other_graph2->points.removeAt(index);
            other_graph2->removeItem(index);

            for(quint32 i =index; i< points.length(); i++){

                points[i]->set_Item_index_in_list(i);
                other_graph1->points[i]->set_Item_index_in_list(i);
                other_graph2->points[i]->set_Item_index_in_list(i);
            }

            if(points.length()==1){  //Si hay un solo punto esconder brackets
                set_Brackets_Visibles(false,0);
            }
            replot(QCustomPlot::rpHint);
            other_graph1->replot(QCustomPlot::rpHint);
            other_graph2->replot(QCustomPlot::rpHint);
        }
    }
}

void Plot::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {

        PlotPoint *plotPoint = qobject_cast<PlotPoint*>(itemAt(event->localPos(), true));
        if(plotPoint ==0){

            QCustomPlot::mousePressEvent(event);
        }
        else{  //mover punto seleccionado si el boton izquierdo esta apretado

            if(points.contains(plotPoint)){

                //si no es el primer punto y no mayor que el tamño de la lista
                if(last_moving_point_pos_in_list != -1 && last_moving_point_pos_in_list <= points.length()){

                    //Esconde los braquets del ultimo anterior punto presionado
                    set_Brackets_Visibles(false, last_moving_point_pos_in_list);
                }
                else{
                    //si no lo igualo el punto anterior al ultimo de la lista
                    //last_moving_point_pos_in_list = points.length()-1;
                }
                plotPoint->startMoving(event->localPos(),
                                       event->modifiers().testFlag(Qt::ShiftModifier));
                moving = true;

                int index = points.indexOf(plotPoint);
                last_moving_point_pos_in_list = index;
                last_point_after_moving = plotPoint->pos();

                //Muestro los braquets del punto presionado
                set_Brackets_Visibles(true, index);

                //Si es el primer punto y hay mas de dos puntos muestro el bracket del primero
                if(index==0 && points.length()>1){
                    set_Brackets_Visibles(true, index+1);
                }
                else if(points.length()>1 && index !=1){
                    set_Brackets_Visibles(false, 1);
                }

                QObject::connect(plotPoint, SIGNAL(stoppedMoving(QPointF)),this,SLOT(stop_Moving_Point_Event(QPointF)));
            }
        }
    }
}

void Plot::mouseMoveEvent(QMouseEvent *event)
{
    QCustomPlot::mouseMoveEvent(event);
    //si no hay botones presionados
    if (event->buttons() == Qt::NoButton) {
        PlotPoint *plotPoint = qobject_cast<PlotPoint*>(itemAt(event->localPos(), true));
        if (plotPoint == 0) {

            unsetCursor();
            replot(QCustomPlot::rpHint);
        }
        else if(points.contains(plotPoint)){

            setCursor(Qt::OpenHandCursor);
            replot(QCustomPlot::rpHint);
        }
    }
    //si es con el boton left presionado el movimiento
    else if(event->buttons() == Qt::LeftButton){

        PlotPoint *plotPoint = qobject_cast<PlotPoint*>(itemAt(event->localPos(), true));
        if (plotPoint == 0) {
            return;
        }
        //si esta sobre un punto
        else if(points.contains(plotPoint)){

            //guardo la posicion del ultimo punto en movimiento
            int index = points.indexOf(plotPoint);

            last_moving_point_pos_in_list = index;
            last_point_after_moving = plotPoint->pos();

            //muevo el bracket del siguente punto a la posicion de este
            if(points.length()>1){
                move_Bracket_right_to_this_pos(index, plotPoint->pos());
            }
        }
    }
}


void Plot::stop_Moving_Point_Event(QPointF pos)
{
    //if(is_moving_point){

        //is_moving_point = false;


        if(points.length() > last_moving_point_pos_in_list && last_moving_point_pos_in_list > 0){

            set_Point_Selected(true, last_moving_point_pos_in_list);
            set_Brackets_Visibles(true, last_moving_point_pos_in_list);

            int coord_x = (int)pos.x();

            if(coord_x < graph_points.length()){
                points.at(last_moving_point_pos_in_list)->set_Position(pos.x(), graph_points[coord_x]);
            }
            else{
                points.at(last_moving_point_pos_in_list)->set_Position(pos);
            }

            if(isEKG_Graph()){

                if(other_graph1->graph_points.length() > pos.x()/4){

                    other_graph1->points[last_moving_point_pos_in_list]->set_Position(pos.x()/4, other_graph1->graph_points[(int)(pos.x()/4)]);
                    other_graph2->points[last_moving_point_pos_in_list]->set_Position(pos.x()/4, other_graph2->graph_points[(int)(pos.x()/4)]);
                }
                else{
                    other_graph1->points[last_moving_point_pos_in_list]->set_Position(pos.x()/4, pos.y()/40.96);
                    other_graph2->points[last_moving_point_pos_in_list]->set_Position(pos.x()/4, pos.y()/40.96);
                }
            }
            else{
                if(other_graph1->graph_points.length() > pos.x()){
                    other_graph1->points[last_moving_point_pos_in_list]->set_Position(pos.x(), other_graph1->graph_points[coord_x]);
                }
                else{
                    other_graph1->points[last_moving_point_pos_in_list]->set_Position(pos);
                }

                if(other_graph2->isEKG_Graph()){

                    if(other_graph2->graph_points.length() > pos.x()*4){
                        other_graph2->points[last_moving_point_pos_in_list]->set_Position(pos.x()*4, other_graph2->graph_points[(int)(pos.x()*4)]);
                    }
                    else{
                        other_graph2->points[last_moving_point_pos_in_list]->set_Position(pos.x()*4, pos.y()*40.96);
                    }
                }
                else{
                    if(other_graph2->graph_points.length() > pos.x()){
                        other_graph2->points[last_moving_point_pos_in_list]->set_Position(pos.x(), other_graph2->graph_points[coord_x]);
                    }
                    else{
                        other_graph2->points[last_moving_point_pos_in_list]->set_Position(pos);
                    }
                }
            }

            move_Bracket_right_to_this_pos(last_moving_point_pos_in_list, pos);

            replot();///*QCustomPlot::rpHint*/);
            other_graph1->replot();///*QCustomPlot::rpHint*/);
            other_graph2->replot();///*QCustomPlot::rpHint*/);
        }
    //}

}

void Plot::set_Point_Selected(bool on, int index){

    for(int i=1; i< points.length(); i++){
        points.at(i)->set_Selected(false);
        other_graph1->points.at(i)->set_Selected(false);
        other_graph2->points.at(i)->set_Selected(false);
    }
    if(points.length() > index && index > 0){

        points.at(index)->set_Selected(on);
        other_graph1->points.at(index)->set_Selected(on);
        other_graph2->points.at(index)->set_Selected(on);
    }
}


void Plot::set_Brackets_Visibles(bool on, int index){

    for(int i=1; i < points.length() ;i++){

        points.at(i)->set_Bracket_visible(false);
        other_graph1->points.at(i)->set_Bracket_visible(false);
        other_graph2->points.at(i)->set_Bracket_visible(false);
    }
    if(points.length() > index && index > 0){
        points.at(index)->set_Bracket_visible(on);
        other_graph1->points.at(index)->set_Bracket_visible(on);
        other_graph2->points.at(index)->set_Bracket_visible(on);
    }
}

//mover el estremo derecho del bracket del punto siguiente a la posicion de este
void Plot::move_Bracket_right_to_this_pos(int index, QPointF pos){

    if(points.last() != points.at(index)){  //si no el ultimo punto mover la derecha de llave del siguiente a posicion de este punto

        //set_Brackets_Visibles(true, index);

        points.at(index + 1)->move_Bracket_right(pos);

        if(isEKG_Graph()){

            other_graph1->points.at(index + 1)->move_Bracket_right(QPointF(pos.x()/4,
                                                                           pos.y()/40.96));
            other_graph2->points.at(index + 1)->move_Bracket_right(QPointF(pos.x()/4,
                                                                           pos.y()/40.96));
        }
        else{

            other_graph1->points.at(index + 1)->move_Bracket_right(pos);

            if(other_graph2->isEKG_Graph()){
                other_graph2->points.at(index + 1)->move_Bracket_right(QPointF(pos.x()*4,
                                                                               pos.y()*40.96));
            }
            else{
                other_graph2->points.at(index + 1)->move_Bracket_right(pos);
            }
        }
    }
}

void Plot::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift) {
        emit shiftStateChanged(true);
    }
    QCustomPlot::keyPressEvent(event);
}

void Plot::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift) {
        emit shiftStateChanged(false);
    }
    QCustomPlot::keyReleaseEvent(event);
}


void Plot::maximize(QPoint maximized_pos){

    //set_Interactions_in_graph(true);

    enable_maximize_button(false);

    this->setFixedSize(maximize_size);
    this->move(maximized_pos);
    this->raise();

    show_button_maximize(false);

    for(int i=0; i< this->itemCount();i++){

        points[i]->setVisible(true);
        points[i]->set_Bracket_visible(false);
    }
    if(last_moving_point_pos_in_list!=-1 && last_moving_point_pos_in_list < points.length()){
        points[last_moving_point_pos_in_list]->set_Bracket_visible(true);
    }
}


void Plot::minimize(){

    isMaximized = false;

    //set_Interactions_in_graph(false);

    enable_maximize_button(true);

    this->setFixedSize(m_size);
    this->move(m_pos);

    if(other_graph1->is_graph_Maximized() || other_graph2->is_graph_Maximized()){ //si hay alguno maximizado

        show_button_maximize(true);

        if(isFirtsPos){
            set_button_maximize_pos(true);
        }
        else{
            set_button_maximize_pos(false);
        }

        if(other_graph1->is_graph_Maximized()){//si esta maximizado muestro boton del otro
            other_graph2->show_button_maximize(true);
        }
        else if(other_graph2->is_graph_Maximized()){
            other_graph1->show_button_maximize(true);
        }
    }
    else{ //si no hay ninguno maximizado

        background_blur->hide();
        other_graph1->minimizar_graph();
        other_graph2->minimizar_graph();
        set_button_maximize_pos(false);
    }

    for(int i=0; i< this->itemCount();i++){

        points[i]->setVisible(false);
    }
    this->lower();
    this->stackUnder(background_blur);
}
