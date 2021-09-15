#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QDesktopWidget>
#include <QFileDialog>
#include "bebe_data_class.h"

#include "beat_thread.h"

#include "plot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setupGraph_Oxy1();
    void setupGraph_Oxy2();
    void setupGraph_EKG();

    void conectar_senales_de_botones();

    void hide_all();

    void show_pantalla_base_de_datos();
    void show_pantalla_test();
    void show_pantalla_paciente();
    void show_pantalla_ajustes();

    void show_widget_paciente_datos();

    void show_menu();

public slots:

    void afterUpdateGraph();

signals:

    void mouse_pressed();
    void mouse_Release();
    void mouse_DoubleClick();
    void data_Received(QByteArray);

//protected:

//    void touchEvent(QTouchEvent *ev);


private slots:

    void mousePressEvent(QMouseEvent *e) ///al reimplementar esta funcion deja de funcionar el evento pressed
    {
        Q_UNUSED(e);
        emit mouse_pressed();
    }

    void mouseDoubleClickEvent(QMouseEvent *e){

        Q_UNUSED(e);
        emit mouse_DoubleClick();
    }
    void mouseReleaseEvent(QMouseEvent *e) ///al reimplementar esta funcion deja de funcionar el evento pressed
    {
        Q_UNUSED(e);
        emit mouse_Release();
    }

    void on_Oxy1_mousePress(QMouseEvent *event=NULL);
    void on_Oxy2_mousePress(QMouseEvent *event=NULL);
    void on_EKG_mousePress(QMouseEvent *event=NULL);

    void on_Oxy1_mouseReleased(QMouseEvent *event=NULL);
    void on_Oxy2_mouseReleased(QMouseEvent *event=NULL);
    void on_EKG_mouseReleased(QMouseEvent *event=NULL);

    void on_Oxy1_mouseWheel(QWheelEvent *event=NULL);
    void on_Oxy2_mouseWheel(QWheelEvent *event=NULL);
    void on_EKG_mouseWheel(QWheelEvent *event=NULL);

    void on_drag_screen();
    void on_start_moving_screen_timeout();
    void on_start_scrolling_screen_ajustes_timeout();
    void on_start_scrolling_screen_test_timeout();
    void on_drag_screen_released();
    void on_mouse_DoubleClick();

    void readSerial();
    void on_data_received(QByteArray serialData);
    void readSerial_Acknowledge_end_of_recording();

    void on_pb_pant_paciente_descartar();
    void on_pb_pant_paciente_test();
    void on_pb_pant_paciente_nuevo();
    void on_pb_pant_paciente_base_de_datos();
    void on_pb_pant_paciente_menu();
    void on_pb_pant_paciente_fecha_de_nacimiento();
    void on_pb_pant_paciente_radioB_femenino();
    void on_pb_pant_paciente_radioB_masculino();

    void on_pb_pant_base_de_datos_nuevo();
    void on_pb_pant_base_de_datos_respaldar();

    void on_pb_menu_salir();
    void on_pb_menu_ayuda();
    void on_pb_menu_acerca_de();

    void on_pb_pant_test_Graficar_Iniciar();
    void on_pb_pant_test_Ver_Registro_Guardar();
    void on_pb_pant_test_atras();
    void on_pb_pant_test_pause_play();

    void on_lw_pant_base_de_datos_pacientes_itemPressed(QListWidgetItem *item);

    void on_pb_widget_paciente_datos_Nuevo_Test();
    void on_pb_widget_paciente_datos_Ver_Registro();
    void on_pb_pant_test_ajustes();

    void on_pb_pant_ajustes_Generales();
    void on_pb_pant_ajustes_Visualizacion();
    void on_pb_pant_ajustes_ECG();
    void on_pb_pant_ajustes_Oxymetria();

    void on_pb_widget_ajustes_generales_color_ECG_Curva();
    void on_pb_widget_ajustes_generales_color_ECG_fondo();
    void on_pb_widget_ajustes_generales_color_Oxy1_Curva();
    void on_pb_widget_ajustes_generales_color_Oxy1_fondo();
    void on_pb_widget_ajustes_generales_color_Oxy2_Curva();
    void on_pb_widget_ajustes_generales_color_Oxy2_fondo();

    void on_pb_widget_colores_aceptar_ECG_Curva();
    void on_pb_widget_colores_aceptar_ECG_fondo();
    void on_pb_widget_colores_aceptar_Oxy1_Curva();
    void on_pb_widget_colores_aceptar_Oxy1_fondo();
    void on_pb_widget_colores_aceptar_Oxy2_Curva();
    void on_pb_widget_colores_aceptar_Oxy2_fondo();

    void on_pb_widget_colores_cancelar();
    void on_pb_widget_colores_amarillo();
    void on_pb_widget_colores_azul();
    void on_pb_widget_colores_naranja();
    void on_pb_widget_colores_verde();
    void on_pb_widget_colores_rojo();


    void on_time_out_Ver_registro();
    void on_pb_pant_ajustes_atras();
    void update_fecha_y_hora();
    void on_le_pant_base_de_datos_buscar_textChanged(const QString &arg1);

    void on_le_pant_paciente_ID_textChanged(const QString &arg1);

    void on_pb_pant_gris_blur_plus();

    void on_timer_respaldar_timeOut();

    void timeOut_wait_for_acknowledge();



private:

    Ui::MainWindow *ui;

    QSerialPort *ftdi_serial_port;
    int errores;

    static const quint16 ftdiVendorID=0x403;
    static const quint16 ftdiProductID=0x6014;

    bool ftdi_is_available;
    QString ftdi_port_name;

    bool valid_receive_data = false;
    quint32 last_bad_receive_pos;
    bool first_receive = true;

    quint8 receive_bytes[UART_SEND_TOTAL_SIZE*2];
    quint8 function_values_graph_0[DATA_FUNCTION_SIZE];
    quint8 function_values_graph_1[DATA_FUNCTION_SIZE];
    quint8 function_values_graph_0_desfasado[DATA_FUNCTION_SIZE];
    quint8 function_values_graph_1_desfasado[DATA_FUNCTION_SIZE];
    //quint8 function_values_graph_HR[DATA_ADC_BUFFER_SIZE*2];
    quint16 function_values_graph_HR_16bits[DATA_ADC_BUFFER_SIZE];
    //quint16 DESFASAJE = DESFASAJE_EN_MUESTRAS_EKG_FIR_orden_X;
    quint16 function_values_graph_HR_16bits_unfiltered[DATA_ADC_BUFFER_SIZE];
    quint32 function_value_count=-4;
    quint32 function_value_count_desfasado=-4;
    quint32 function_value_pos=0;
    quint32 HR_value_pos=0;
    quint32 x_axis_count=0;
    quint32 HR_value_count=0;
    qint32 HR_value_count_desfasado=-16;

    quint8 SPO2_Oxy1_function_values[SPO2_FUNCTION_BUFFER_SIZE];
    quint8 SPO2_Oxy2_function_values[SPO2_FUNCTION_BUFFER_SIZE];
    quint16 BPM_Oxy1_function_values[BPM_FUNCTION_BUFFER_SIZE];
    quint16 BPM_Oxy2_function_values[BPM_FUNCTION_BUFFER_SIZE];
    quint16 PI_Oxy1_function_values[PI_FUNCTION_BUFFER_SIZE];
    quint16 PI_Oxy2_function_values[PI_FUNCTION_BUFFER_SIZE];
    quint32 function_value_count_SPO2_BPM_PI=0;



    Plot *customPlot_graph_Oxy1;
    Plot *customPlot_graph_Oxy2;
    Plot *customPlot_graph_EKG;
    bool oxy1_maximized=false;
    bool oxy2_maximized=false;
    bool EKG_maximized=false;

    qint8 picar_frec=0;

    QVector<double> keyData_graph_HR;
    QVector<double> valueData_graph_HR;

    QVector<double> keyData_graph_HR_recorded;
    QVector<double> valueData_graph_HR_recorded;

    QTimer timer_graph;
    QTime tiempo_de_Prueba = QTime(0,0,0);
    bool pausado = false;
    QTimer start_moving_screen;
    QTimer timer_respaldar_datos;
    QTimer wait_for_acknowledge;

    int init_pos_x;
    int init_pos_y;
    int delta_y_constant_scrolling_ajustes = 0;
    int delta_y_constant_scrolling_test = 0;

    quint16 BPM_bebe_value_OXY1 = 0;
    quint16 BPM_bebe_value_OXY2 = 0;
    quint64 SPO2_bebe_value_average_OXY1 = 0;
    quint64 SPO2_bebe_value_average_OXY2 = 0;
    quint64 beats_per_minute_value_average_OXY1 = 0;
    quint64 beats_per_minute_value_average_OXY2 = 0;
    quint16 PI_value_average_OXY1 = 0;
    quint16 PI_value_average_OXY2 = 0;

    uint32_t crc32(const void *buf, size_t size);
    void check_message(qint64 bytes_size);
    void check_message_crc32();

    Bebe_Data_Class *bebe_object = new Bebe_Data_Class("mama", "bebe");//funciona con un puntero a la clase pero con un objeto de la clase no
    bool primera_vuelta=true;

    float porciento_de_adquirido=0;

    bool cargar_base_de_datos(QString);
    QString ordenar_para_lista_de_paciente(Bebe_Data_Class &bebe_object_copia);
    bool  ver_registro_activated = false;
    quint32 ver_registro_counter=0;

    void update_data_pacient_in_labels(bool desde_pantalla_principal);
    QTimer time;
    QString sexo_de_paciente="masculino";
    QDate birth_date_paciente = QDate(1991,7,16);
    QStringList lista_de_pacientes;


    QList<QByteArray> read_BD;
    quint64 BD_transfer_count=0;

    QString data_base_name = "base_datos_oximetria.dat";

    void generar_reporte();

    QByteArray QString_to_QByte_Array(QString string);
    QByteArray quint16_to_QByte_Array(quint16 integer);
    QByteArray quint32_to_QByte_Array(quint32 integer);
    QByteArray quint64_to_QByte_Array(quint64 integer);

    void process_received_buffer(quint8 *);

    quint32 ancho_de_ventana_EKG = EKG_GRAPH_RANGE;
    quint32 ancho_de_ventana_OXY = OXY_GRAPH_RANGE;
    void clear_graphs(bool clear_data = true, bool replot = true);

    bool play_beat = false;
    Beat_Thread *thread_beat;

};

#endif // MAINWINDOW_H
