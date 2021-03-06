#include "mainwindow.h"
#include "ui_mainwindow.h"

const uint32_t crc32_tab[] = {
    0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
    0xe963a535, 0x9e6495a3,	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
    0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
    0xf3b97148, 0x84be41de,	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
    0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,	0x14015c4f, 0x63066cd9,
    0xfa0f3d63, 0x8d080df5,	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
    0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,	0x35b5a8fa, 0x42b2986c,
    0xdbbbc9d6, 0xacbcf940,	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
    0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
    0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
    0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,	0x76dc4190, 0x01db7106,
    0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
    0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
    0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
    0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
    0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
    0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
    0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
    0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
    0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
    0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
    0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
    0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
    0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
    0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
    0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
    0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
    0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
    0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
    0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
    0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
    0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
    0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
    0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
    0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
    0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
    0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
    0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
    0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
    0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
    0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
    0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
    0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setGeometry(0,0,1280,800);
    setWindowFlags(Qt::CustomizeWindowHint);

    connect(this,SIGNAL(mouse_pressed()),this,SLOT(on_drag_screen()));
    connect(this,SIGNAL(mouse_Release()),this,SLOT(on_drag_screen_released()));
    connect(this,SIGNAL(mouse_DoubleClick()),this,SLOT(on_mouse_DoubleClick()));

    show_pantalla_paciente();

    for(int i=0; i < UART_SEND_TOTAL_SIZE; i++){
        receive_bytes[i] = 0;
    }

    for(int i=0; i < SPO2_FUNCTION_BUFFER_SIZE; i++){
        SPO2_Oxy1_function_values[i]=0;
        SPO2_Oxy2_function_values[i]=0;
        BPM_Oxy1_function_values[i]=0;
        BPM_Oxy2_function_values[i]=0;
        PI_Oxy1_function_values[i]=0;
        PI_Oxy2_function_values[i]=0;
    }

    x_axis_count =0;
    valid_receive_data = false;
    last_bad_receive_pos =0;
    errores = 0;
    function_value_pos=0;
    function_value_count=0;
    HR_value_pos=0;
    HR_value_count=0;

    update_fecha_y_hora();
    time.setInterval(1000);
    QObject::connect(&time,SIGNAL(timeout()),this,SLOT(update_fecha_y_hora()));
    time.start();

    for(int i=0;i<4;i++){

        keyData_graph_HR<<i+1;
        valueData_graph_HR<<i+1;

        keyData_graph_HR_recorded<<i+1;
        valueData_graph_HR_recorded<<i+1;
    }

    timer_graph.setInterval(16);
    QObject::connect(&timer_graph,SIGNAL(timeout()),this,SLOT(afterUpdateGraph()));

    // Busqueda de puertos serie, encuentra el PID y el VID del FTDI se procede a inicializar el puerto serie-----------------
    //------------------------------------------------------------------------------------------------------------------------
    ftdi_is_available=false;
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
            if(serialPortInfo.productIdentifier()==ftdiProductID && serialPortInfo.vendorIdentifier()==ftdiVendorID){
                ftdi_is_available=true;
                ftdi_port_name=serialPortInfo.portName();
            }
        }
    }
    //------------------------------------------------------------------------------------------------------------------------


    // Inicializacion de puerto serie y habilitacion de botones---------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------
    ftdi_serial_port=new QSerialPort(this);

    if(ftdi_is_available){
        ui->statusBar->showMessage("Dispositivo FTDI encontrado");
        ftdi_serial_port->setPortName(ftdi_port_name);
        ftdi_serial_port->open(QSerialPort::ReadWrite);
        ftdi_serial_port->setBaudRate(QSerialPort::Baud115200);
        ftdi_serial_port->setDataBits(QSerialPort::Data8);
        ftdi_serial_port->setFlowControl(QSerialPort::NoFlowControl);
        ftdi_serial_port->setParity(QSerialPort::NoParity);
        ftdi_serial_port->setStopBits(QSerialPort::OneStop);

        QByteArray write_data;
        for (int i=0; i<UART_READ_BUFFER_SIZE;++i){

            write_data.append(INIT_PROG_ID);
        }
        ftdi_serial_port->write(write_data);

        ui->statusBar->showMessage("Reiniciando discovery ---------------");
    }
    else {
        ui->statusBar->showMessage("Dispositivo FTDI no encontrado");
    }
    //------------------------------------------------------------------------------------------------------------------------

    //Creando objeto de Graficas e inicializandolas---------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------
    customPlot_graph_Oxy1 = new Plot(ui->widget_pantalla_test, 10);
    customPlot_graph_Oxy2 = new Plot(ui->widget_pantalla_test, 10);
    customPlot_graph_EKG = new Plot(ui->widget_pantalla_test, 10);

    setupGraph_Oxy1();
    setupGraph_Oxy2();
    setupGraph_EKG();
    //------------------------------------------------------------------------------------------------------------------------

    cargar_base_de_datos(data_base_name);

    conectar_senales_de_botones();

    thread_beat = new Beat_Thread(this);
    thread_beat->start();
    thread_beat->set_WAV_Dir("beat_sound.wav");
}

MainWindow::~MainWindow()
{
    //thread_beat->deleteLater();

    if(ftdi_serial_port->isOpen())
        ftdi_serial_port->close();
    delete ui;
}


void MainWindow::conectar_senales_de_botones(){

    ////Botones de pantalla paciente--------------------------------------------------------------------------------------------------------------------------
    QObject::connect(ui->pb_pant_paciente_descartar, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_descartar()));
    QObject::connect(ui->pb_pant_paciente_test, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_test()));
    QObject::connect(ui->pb_pant_paciente_nuevo, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_nuevo()));
    QObject::connect(ui->pb_pant_paciente_base_de_datos, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_base_de_datos()));
    QObject::connect(ui->pb_pant_paciente_menu, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_menu()));
    QObject::connect(ui->pb_pant_paciente_menu_2, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_menu()));
    QObject::connect(ui->pb_pant_paciente_fecha_nacimiento, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_fecha_de_nacimiento()));
    QObject::connect(ui->pb_pant_paciente_fecha_nacimiento_2, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_fecha_de_nacimiento()));
    QObject::connect(ui->pb_pant_paciente_label_femenino, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_radioB_femenino()));
    QObject::connect(ui->pb_pant_paciente_radioB_femenino, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_radioB_femenino()));
    QObject::connect(ui->pb_pant_paciente_label_masculino, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_radioB_masculino()));
    QObject::connect(ui->pb_pant_paciente_radioB_masculino, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_radioB_masculino()));
    ////-------------------------------------------------------------------------------------------------------------------------------------------------------

    ////Botones de pantalla base de datos----------------------------------------------------------------------------------------------------------------------
    QObject::connect(ui->pb_pant_base_de_datos_nuevo, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_base_de_datos_nuevo()));
    QObject::connect(ui->pb_pant_base_de_datos_menu, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_menu()));
    QObject::connect(ui->pb_pant_base_de_datos_menu_2, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_menu()));
    QObject::connect(ui->pb_pant_base_de_datos_respaldar, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_base_de_datos_respaldar()));
    ////-------------------------------------------------------------------------------------------------------------------------------------------------------


    ////Botones de pantalla menu-------------------------------------------------------------------------------------------------------------------------------
    QObject::connect(ui->pb_menu_salir, SIGNAL(leftClicked()), this, SLOT(on_pb_menu_salir()));
    QObject::connect(ui->pb_menu_salir_2, SIGNAL(leftClicked()), this, SLOT(on_pb_menu_salir()));
    QObject::connect(ui->pb_menu_acerca_de, SIGNAL(leftClicked()), this, SLOT(on_pb_menu_salir()));
    QObject::connect(ui->pb_menu_ayuda, SIGNAL(leftClicked()), this, SLOT(on_pb_menu_salir()));
    ////-------------------------------------------------------------------------------------------------------------------------------------------------------


    ////Botones de pantalla test-------------------------------------------------------------------------------------------------------------------------------
    QObject::connect(ui->pb_pant_test_atras, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_base_de_datos_nuevo()));
    QObject::connect(ui->pb_pant_test_menu, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_menu()));
    QObject::connect(ui->pb_pant_test_menu_2, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_menu()));
    QObject::connect(ui->pb_pant_test_Graficar_Iniciar, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_test_Graficar_Iniciar()));
    QObject::connect(ui->pb_pant_test_Ver_Registro_Guardar, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_test_Ver_Registro_Guardar()));
    QObject::connect(ui->pb_pant_test_ajustes, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_test_ajustes()));
    QObject::connect(ui->pb_pant_test_ajustes_2, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_test_ajustes()));
    QObject::connect(ui->pb_pant_test_pause_play, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_test_pause_play()));
    ////-------------------------------------------------------------------------------------------------------------------------------------------------------

    ////Botones de pantalla ajustes-------------------------------------------------------------------------------------------------------------------------------
    QObject::connect(ui->pb_pant_ajustes_atras, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_ajustes_atras()));
    QObject::connect(ui->pb_pant_ajustes_menu, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_menu()));
    QObject::connect(ui->pb_pant_ajustes_menu_2, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_paciente_menu()));
    QObject::connect(ui->pb_pant_ajustes_generales_Generales, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_ajustes_Generales()));
    QObject::connect(ui->pb_pant_ajustes_generales_Visualizacion, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_ajustes_Visualizacion()));
    QObject::connect(ui->pb_pant_ajustes_generales_ECG, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_ajustes_ECG()));
    QObject::connect(ui->pb_pant_ajustes_generales_Oxymetria, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_ajustes_Oxymetria()));
    QObject::connect(ui->pb_widget_ajustes_generales_color_EKG_curva, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_ajustes_generales_color_ECG_Curva()));
    QObject::connect(ui->pb_widget_ajustes_generales_color_EKG_fondo, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_ajustes_generales_color_ECG_fondo()));
    QObject::connect(ui->pb_widget_ajustes_generales_color_Oxy1_curva, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_ajustes_generales_color_Oxy1_Curva()));
    QObject::connect(ui->pb_widget_ajustes_generales_color_Oxy1_fondo, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_ajustes_generales_color_Oxy1_fondo()));
    QObject::connect(ui->pb_widget_ajustes_generales_color_Oxy2_curva, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_ajustes_generales_color_Oxy2_Curva()));
    QObject::connect(ui->pb_widget_ajustes_generales_color_Oxy2_fondo, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_ajustes_generales_color_Oxy2_fondo()));
    QObject::connect(ui->pb_widget_ajustes_generales_color_EKG_curva_2, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_ajustes_generales_color_ECG_Curva()));
    QObject::connect(ui->pb_widget_ajustes_generales_color_EKG_fondo_2, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_ajustes_generales_color_ECG_fondo()));
    QObject::connect(ui->pb_widget_ajustes_generales_color_Oxy1_curva_2, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_ajustes_generales_color_Oxy1_Curva()));
    QObject::connect(ui->pb_widget_ajustes_generales_color_Oxy1_fondo_2, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_ajustes_generales_color_Oxy1_fondo()));
    QObject::connect(ui->pb_widget_ajustes_generales_color_Oxy2_curva_2, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_ajustes_generales_color_Oxy2_Curva()));
    QObject::connect(ui->pb_widget_ajustes_generales_color_Oxy2_fondo_2, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_ajustes_generales_color_Oxy2_fondo()));
    ////-------------------------------------------------------------------------------------------------------------------------------------------------------

    ////Botones de widget paciente datos-----------------------------------------------------------------------------------------------------------------------
    QObject::connect(ui->pb_widget_paciente_datos_Borrar_paciente, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_paciente_datos_Borrar_paciente()));
    QObject::connect(ui->pb_widget_paciente_datos_Nuevo_Test, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_paciente_datos_Nuevo_Test()));
    QObject::connect(ui->pb_widget_paciente_datos_Nuevo_Test_2, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_paciente_datos_Nuevo_Test()));
    QObject::connect(ui->pb_widget_paciente_datos_Ver_Registro, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_paciente_datos_Ver_Registro()));
    QObject::connect(ui->pb_widget_paciente_datos_Ver_Registro_2, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_paciente_datos_Ver_Registro()));
    //-------------------------------------------------------------------------------------------------------------------------------------------------------

    ////Botones de widget colores-----------------------------------------------------------------------------------------------------------------------
    QObject::connect(ui->pb_widget_colores_aceptar_ECG_Curva, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_colores_aceptar_ECG_Curva()));
    QObject::connect(ui->pb_widget_colores_aceptar_ECG_fondo, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_colores_aceptar_ECG_fondo()));
    QObject::connect(ui->pb_widget_colores_aceptar_Oxy1_Curva, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_colores_aceptar_Oxy1_Curva()));
    QObject::connect(ui->pb_widget_colores_aceptar_Oxy1_fondo, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_colores_aceptar_Oxy1_fondo()));
    QObject::connect(ui->pb_widget_colores_aceptar_Oxy2_Curva, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_colores_aceptar_Oxy2_Curva()));
    QObject::connect(ui->pb_widget_colores_aceptar_Oxy2_fondo, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_colores_aceptar_Oxy2_fondo()));
    QObject::connect(ui->pb_widget_colores_cancelar, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_colores_cancelar()));
    QObject::connect(ui->pb_widget_colores_amarillo, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_colores_amarillo()));
    QObject::connect(ui->pb_widget_colores_azul, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_colores_azul()));
    QObject::connect(ui->pb_widget_colores_naranja, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_colores_naranja()));
    QObject::connect(ui->pb_widget_colores_verde, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_colores_verde()));
    QObject::connect(ui->pb_widget_colores_rojo, SIGNAL(leftClicked()), this, SLOT(on_pb_widget_colores_rojo()));
    //-------------------------------------------------------------------------------------------------------------------------------------------------------

    QObject::connect(ui->pb_pant_gris_blur_plus, SIGNAL(leftClicked()), this, SLOT(on_pb_pant_gris_blur_plus()));

}

void MainWindow::on_pb_pant_gris_blur_plus(){

    if(customPlot_graph_Oxy1->is_graph_Maximized()){
        customPlot_graph_Oxy1->minimize();
    }
    if(customPlot_graph_Oxy2->is_graph_Maximized()){
        customPlot_graph_Oxy2->minimize();
    }
    if(customPlot_graph_EKG->is_graph_Maximized()){
        customPlot_graph_EKG->minimize();
    }
    ui->pb_pant_gris_blur_plus->hide();
}

void MainWindow::afterUpdateGraph(){

    if((x_axis_count % ancho_de_ventana_OXY)==0){
        x_axis_count=0;

        clear_graphs(true, false);
    }

    for(int i=0; i < 4; i++){
        customPlot_graph_EKG->graph(0)->addData(x_axis_count*4+i, function_values_graph_HR_16bits[HR_value_count+i]);
    }
    HR_value_count+=4;
    if(HR_value_count >= DATA_ADC_BUFFER_SIZE){
        HR_value_count = 0;
    }

    //La correccion de sincronizacion se realiza en el recibo de la informacion (PROCESS BUFFER)
    customPlot_graph_Oxy1->graph(0)->addData(x_axis_count, function_values_graph_0[function_value_count]);
    customPlot_graph_Oxy2->graph(0)->addData(x_axis_count, function_values_graph_1[function_value_count]);

    function_value_count++;
    x_axis_count++;
    if(function_value_count >= DATA_FUNCTION_SIZE){
        function_value_count=0;
    }


    if(picar_frec >= 3){

        customPlot_graph_Oxy1->replot(QCustomPlot::rpHint);
        picar_frec=0;
    }
    else if(picar_frec == 2){
        customPlot_graph_Oxy2->replot(QCustomPlot::rpHint);
    }
    else if(picar_frec == 1){

        customPlot_graph_EKG->replot(QCustomPlot::rpHint);
    }
    picar_frec++;
}

void MainWindow::on_time_out_Ver_registro(){

    quint64 HR_value_count_recorded = ver_registro_counter*4;

    porciento_de_adquirido = (unsigned int)(((float)ver_registro_counter/bebe_object->data_function_size)*100);
    ui->l_pant_test_porciento_value->setText(QString::number(porciento_de_adquirido)+"%");

    ui->l_pant_test_porciento_circle_progress->setPixmap(QPixmap(QString(":/icons/")+QString::number(5*(unsigned int)(porciento_de_adquirido/5))+QString(".png")));
    ui->l_pant_test_porciento_circle_progress->setFixedSize(QSize(990,230));

    if(keyData_graph_HR_recorded[0] >= 1600)
        customPlot_graph_EKG->set_Range_x_axis(keyData_graph_HR_recorded[0]- 1600,keyData_graph_HR_recorded[0] + 400);

    for(int i=0; i < 4; i++){
        valueData_graph_HR_recorded[i]= bebe_object->HR_data_bebe[HR_value_count_recorded+i];
    }
    //customPlot_graph_EKG->graph(0)->addData(keyData_graph_HR_recorded, valueData_graph_HR_recorded);
    customPlot_graph_EKG->add_Data(0, keyData_graph_HR_recorded, valueData_graph_HR_recorded);

    customPlot_graph_EKG->replot();

    for(int i=0; i<4; i++){
        keyData_graph_HR_recorded[i]+=4;
    }


    if(ver_registro_counter >= 400){
        customPlot_graph_Oxy1->set_Range_x_axis(ver_registro_counter- 400,ver_registro_counter + 100 );
        customPlot_graph_Oxy2->set_Range_x_axis(ver_registro_counter- 400,ver_registro_counter + 100 );
    }
    //customPlot_graph_Oxy1->xAxis->autoSubTicks();
    //customPlot_graph_Oxy1->graph(0)->addData(ver_registro_counter, bebe_object->function_0_data_bebe[ver_registro_counter]);
    customPlot_graph_Oxy1->add_Data(0, ver_registro_counter, bebe_object->function_0_data_bebe[ver_registro_counter]);
    //customPlot_graph_Oxy2->graph(0)->addData(ver_registro_counter, bebe_object->function_1_data_bebe[ver_registro_counter]);
    customPlot_graph_Oxy2->add_Data(0, ver_registro_counter, bebe_object->function_1_data_bebe[ver_registro_counter]);

    customPlot_graph_Oxy1->replot();
    customPlot_graph_Oxy2->replot();

    ver_registro_counter++;
    if(ver_registro_counter >= bebe_object->data_function_size){

        ver_registro_counter=0;
        timer_graph.stop();
        ver_registro_activated=false;
        QMessageBox::information(this,"Informacion","Se ha llegado al l??mite m??ximo de muestras ",QMessageBox::Ok);

        return;
    }
}

void MainWindow::on_drag_screen(){

    if(isFullScreen()){
        if(QApplication::mouseButtons()==Qt::RightButton){

            if(!ui->widget_menu->isHidden()){
                ui->widget_menu->hide();
                return;
            }
        }
        return;
    }

    if(QApplication::mouseButtons()==Qt::LeftButton){

        if(!ui->widget_menu->isHidden()){
            ui->widget_menu->hide();
        }
        if(!ui->widget_pantalla_ajustes_widget_colores->isHidden()){
            ui->widget_pantalla_ajustes_widget_colores->hide();
        }
        if(!ui->widget_paciente_datos->isHidden()){
            ui->widget_paciente_datos->hide();
        }

        start_moving_screen.start(10);
        init_pos_x = (QWidget::mapFromGlobal(QCursor::pos())).x();
        init_pos_y = (QWidget::mapFromGlobal(QCursor::pos())).y();
    }
    else if(QApplication::mouseButtons()==Qt::RightButton){

    }
}

void MainWindow::on_start_moving_screen_timeout(){

    int x_pos = (int)this->pos().x()+((QWidget::mapFromGlobal(QCursor::pos())).x() - init_pos_x);
    int y_pos = (int)this->pos().y()+((QWidget::mapFromGlobal(QCursor::pos())).y() - init_pos_y);
    x_pos = (x_pos < 0)?0:x_pos;
    y_pos = (y_pos < 0)?0:y_pos;

    x_pos = (x_pos > QApplication::desktop()->width()-100)?QApplication::desktop()->width()-100:x_pos;
    y_pos = (y_pos > QApplication::desktop()->height()-180)?QApplication::desktop()->height()-180:y_pos;

    this->move(x_pos,y_pos);

    init_pos_x = (QWidget::mapFromGlobal(QCursor::pos())).x();
    init_pos_y = (QWidget::mapFromGlobal(QCursor::pos())).y();
}

void MainWindow::on_start_scrolling_screen_ajustes_timeout(){

    int y_pos = (int)ui->widget_pantalla_ajustes->pos().y()+((QWidget::mapFromGlobal(QCursor::pos())).y() - init_pos_y);
    y_pos = (y_pos > 0)?0:y_pos;  ///limites para pantalla de ajustes
    y_pos = (y_pos < delta_y_constant_scrolling_ajustes)?delta_y_constant_scrolling_ajustes:y_pos;  ///si haces sroll en otras pantallas modificar esto

    ui->widget_pantalla_ajustes->move(ui->widget_pantalla_ajustes->pos().x(),y_pos);

    init_pos_y = (QWidget::mapFromGlobal(QCursor::pos())).y();
}

void MainWindow::on_drag_screen_released()
{
    if(isFullScreen()){

        return;
    }
    start_moving_screen.stop();
    init_pos_x = 0;
    init_pos_y = 0;
    //current_win_Pos = QPoint(this->pos().x()-200,this->pos().y()-200);
}

void MainWindow::on_mouse_DoubleClick()
{
    if(!ui->widget_menu->isHidden()){
        ui->widget_menu->hide();
        return;
    }
}

void MainWindow::check_message_crc32(){

    if(last_bad_receive_pos >= UART_SEND_TOTAL_SIZE){

        uint8_t buf_8b[4];
        uint32_t crcValue = crc32(receive_bytes, UART_SEND_BUFFER_SIZE);

        for (int i=0; i<4 ;++i){
            buf_8b[i] = ((uint8_t*)&crcValue)[3-i];
        }

        valid_receive_data = true;

        for (int i=0; i<4 ;++i){
            if(receive_bytes[i+UART_SEND_BUFFER_SIZE] != buf_8b[i]){
                valid_receive_data = false;//Error de datos solicitar reenvio

                last_bad_receive_pos=0;
                errores++;

                ui->statusBar->showMessage(QString::number(errores));
                return;//Error de check_sum solicitar reenvio
            }
        }
    }
}

void MainWindow::timeOut_wait_for_acknowledge(){

    wait_for_acknowledge.stop();

    //last_bad_receive_pos=0;

    //QObject::connect(ftdi_serial_port,SIGNAL(readyRead()),this,SLOT(readSerial_Acknowledge_end_of_recording()));
}

void MainWindow::readSerial_Acknowledge_end_of_recording()
{
    ui->statusBar->showMessage(QString("Funcion acknowledge"));

    QByteArray serialData = ftdi_serial_port->read(UART_SEND_TOTAL_SIZE);

    qint64 bytes_size = serialData.size();

    for(int i=0; i < bytes_size; i++){ //el elemento i = serialData.size() no existe y da error al correr

        receive_bytes[i + last_bad_receive_pos] = serialData.at(i);
    }
    last_bad_receive_pos += bytes_size;

    check_message_crc32();

    if(valid_receive_data){
        bool respuesta_a_chequeando_acknowledge = true;
        ui->statusBar->showMessage(QString("esperando acknowledge"));

        for(quint16 i = DATA_INIT_BUFFER_POS; i < DATA_GRAPH_HR_INIT_BUFFER_POS; i++){
            if(receive_bytes[i] != ACKNOWLEDGE_END_OF_RECORDING){
                respuesta_a_chequeando_acknowledge = false;
            }
        }
        if(respuesta_a_chequeando_acknowledge){

            ui->statusBar->showMessage(QString("acknowledge ok"));
            QObject::disconnect(ftdi_serial_port,SIGNAL(readyRead()),this,SLOT(readSerial_Acknowledge_end_of_recording()));
            ftdi_serial_port->flush();
            ftdi_serial_port->close();

            ftdi_serial_port->open(QSerialPort::ReadWrite);
            QObject::connect(ftdi_serial_port,SIGNAL(readyRead()),this,SLOT(readSerial()));

            ui->pb_pant_test_Graficar_Iniciar->setEnabled(true);

            clear_graphs();

            //            timer_check_connection.stop();
            //            QObject::disconnect(&timer_check_connection,SIGNAL(timeout()),this,SLOT(timeOut_Check_Connection()));
        }
    }
}

void MainWindow::clear_graphs(bool clear_data, bool replot)
{
    if(clear_data){
        customPlot_graph_Oxy1->graph(0)->data()->clear();
        customPlot_graph_Oxy2->graph(0)->data()->clear();
        customPlot_graph_EKG->graph(0)->data()->clear();

        customPlot_graph_Oxy1->graph_points.clear();
        customPlot_graph_Oxy2->graph_points.clear();
        customPlot_graph_EKG->graph_points.clear();
    }

    customPlot_graph_Oxy1->set_Range_x_axis(0,ancho_de_ventana_OXY);
    customPlot_graph_Oxy2->set_Range_x_axis(0,ancho_de_ventana_OXY);
    customPlot_graph_EKG->set_Range_x_axis(0,ancho_de_ventana_EKG);

    if(replot){
        customPlot_graph_Oxy1->replot();//);
        customPlot_graph_Oxy2->replot();//);
        customPlot_graph_EKG->replot();//);
    }
}

void MainWindow::readSerial()
{
    ////ui->statusBar->showMessage(QString("Funcion Read Serial"));

    QByteArray serialData = ftdi_serial_port->read(UART_SEND_TOTAL_SIZE);

    emit data_Received(serialData);
}

void MainWindow::on_data_received(QByteArray serialData)
{
    qint64 bytes_size = serialData.size();

    for(int i=0; i < bytes_size; i++){ //el elemento i = serialData.size() no existe y da error al correr

        receive_bytes[i + last_bad_receive_pos] = serialData.at(i);
        ////ui->statusBar->showMessage(QString("last_bad_receive_pos  -> ")+QString::number(last_bad_receive_pos));
    }
    last_bad_receive_pos += bytes_size;

    do{
        check_message(bytes_size);

        if(valid_receive_data){

            process_received_buffer(receive_bytes);

            if(first_receive){
                if(function_value_pos >= FUNCTION_BUFFER_SIZE*2){
                    first_receive = false;

                    timer_graph.start();
                    if(play_beat){
                        thread_beat->start_timer();
                    }
                }
            }
            valid_receive_data = false;
            last_bad_receive_pos -= UART_SEND_TOTAL_SIZE;
            if(last_bad_receive_pos > 0){
                memcpy( &receive_bytes[0], &receive_bytes[UART_SEND_TOTAL_SIZE], UART_SEND_TOTAL_SIZE);
            }
            else{
                for(int i=0; i < UART_SEND_TOTAL_SIZE; i++){
                    receive_bytes[i] = 0;
                }
            }
        }
    }while(last_bad_receive_pos >= UART_SEND_TOTAL_SIZE);
}

void MainWindow::process_received_buffer(quint8 *receive_bytes){


    if(((receive_bytes[STATUS_CHECK_ADC]) == 3)){
        //amarillo desconectado
        ui->l_pant_test_electrodo_amarillo->show();
        porciento_de_adquirido = 0;
    }
    else if((receive_bytes[STATUS_CHECK_ADC]) == 2){
        //rojo desconectado
        ui->l_pant_test_electrodo_rojo->show();
        porciento_de_adquirido = 0;
    }
    else if((receive_bytes[STATUS_CHECK_ADC]) == 1){
        //verde desconectado
        ui->l_pant_test_electrodo_verde->show();
        porciento_de_adquirido = 0;
    }
    else{
        ui->l_pant_test_electrodo_amarillo->hide();
        ui->l_pant_test_electrodo_rojo->hide();
        ui->l_pant_test_electrodo_verde->hide();
    }



    //Desfase de 4 muestras (4 * 16ms) en total un desfase de 64ms (la atraso para sincronizarla con el EKG desfasado por el filtro)-------
    //-------------------------------------------------------------------------------------------------------------------------------------
    if(function_value_pos + FUNCTION_BUFFER_SIZE  >= DATA_FUNCTION_SIZE){
        memcpy( &function_values_graph_0[function_value_pos + 4], &receive_bytes[DATA_GRAPH_FT_INIT_BUFFER_POS], FUNCTION_BUFFER_SIZE - 4);
        memcpy( &function_values_graph_1[function_value_pos + 4], &receive_bytes[DATA_GRAPH_FT_2_INIT_BUFFER_POS], FUNCTION_BUFFER_SIZE - 4);
        memcpy( &function_values_graph_0[0], &receive_bytes[DATA_GRAPH_FT_INIT_BUFFER_POS + FUNCTION_BUFFER_SIZE - 4], 4);
        memcpy( &function_values_graph_1[0], &receive_bytes[DATA_GRAPH_FT_2_INIT_BUFFER_POS + FUNCTION_BUFFER_SIZE - 4], 4);
    }
    else{
        memcpy( &function_values_graph_0[function_value_pos + 4], &receive_bytes[DATA_GRAPH_FT_INIT_BUFFER_POS], FUNCTION_BUFFER_SIZE);
        memcpy( &function_values_graph_1[function_value_pos + 4], &receive_bytes[DATA_GRAPH_FT_2_INIT_BUFFER_POS], FUNCTION_BUFFER_SIZE);
    }
    //-------------------------------------------------------------------------------------------------------------------------------------

    //Convierto los 2bytes en 16bits (recibo 12bits del ADC)-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------------------------------------------
    uint32_t c;
    for(uint32_t i=0; i<ADC_BUFFER_SIZE ;++i){
        c = i*2;
        function_values_graph_HR_16bits[i + HR_value_pos] = ((((receive_bytes[c + DATA_GRAPH_HR_INIT_BUFFER_POS]<<8)& 0x0FF00)|((receive_bytes[c+1+DATA_GRAPH_HR_INIT_BUFFER_POS])& 0x0FF)));
    }
    //-------------------------------------------------------------------------------------------------------------------------------------
    //memcpy( &function_values_graph_0[function_value_pos], &receive_bytes[DATA_GRAPH_FT_INIT_BUFFER_POS], FUNCTION_BUFFER_SIZE);
    //memcpy( &function_values_graph_1[function_value_pos], &receive_bytes[DATA_GRAPH_FT_2_INIT_BUFFER_POS], FUNCTION_BUFFER_SIZE);

    function_value_pos+=FUNCTION_BUFFER_SIZE;
    HR_value_pos+=ADC_BUFFER_SIZE;

    if(function_value_pos >=DATA_FUNCTION_SIZE){
        function_value_pos=0;
        HR_value_pos=0;
        primera_vuelta=false;
    }

    //Incremento el porciento al avanzar la prueba (circulo) - se reinicia si se ddesconecta electrodo-------------------------------------
    //-------------------------------------------------------------------------------------------------------------------------------------
    if(porciento_de_adquirido < 100){
        ////ui->statusBar->showMessage(QString::number(SUMA_DE_PORCIENTO_RECIBIDO));
        porciento_de_adquirido += SUMA_DE_PORCIENTO_RECIBIDO;
    }
    else{
        ui->pb_pant_test_Ver_Registro_Guardar->setEnabled(true);
    }
    //-------------------------------------------------------------------------------------------------------------------------------------


    quint16 beats_per_minute_OXY1;
    quint16 beats_per_minute_OXY2;
    quint16 PI_value_OXY1;
    quint16 PI_value_OXY2;
    //SPO2_Oxy1_function_values[function_value_count_SPO2_BPM_PI] = receive_bytes[SPO2_BUFFER_OXY1_POS];

    if(receive_bytes[SPO2_BUFFER_OXY1_POS] <= 100 && receive_bytes[SPO2_BUFFER_OXY1_POS] > 0){
        SPO2_Oxy1_function_values[function_value_count_SPO2_BPM_PI] = receive_bytes[SPO2_BUFFER_OXY1_POS];
    }
    else{
        if(function_value_count_SPO2_BPM_PI != 0){
            SPO2_Oxy1_function_values[function_value_count_SPO2_BPM_PI] =SPO2_Oxy1_function_values[function_value_count_SPO2_BPM_PI-1];
        }
        else{
            SPO2_Oxy1_function_values[function_value_count_SPO2_BPM_PI] =SPO2_Oxy1_function_values[SPO2_FUNCTION_BUFFER_SIZE-1];
        }
    }

    //SPO2_Oxy2_function_values[function_value_count_SPO2_BPM_PI] = receive_bytes[SPO2_BUFFER_OXY2_POS];

    if(receive_bytes[SPO2_BUFFER_OXY2_POS] <= 100 && receive_bytes[SPO2_BUFFER_OXY2_POS] > 0){
        SPO2_Oxy2_function_values[function_value_count_SPO2_BPM_PI] = receive_bytes[SPO2_BUFFER_OXY2_POS];
    }
    else{
        if(function_value_count_SPO2_BPM_PI != 0){
            SPO2_Oxy2_function_values[function_value_count_SPO2_BPM_PI] =SPO2_Oxy2_function_values[function_value_count_SPO2_BPM_PI-1];
        }
        else{
            SPO2_Oxy2_function_values[function_value_count_SPO2_BPM_PI] =SPO2_Oxy2_function_values[SPO2_FUNCTION_BUFFER_SIZE-1];
        }
    }

    beats_per_minute_OXY1 = receive_bytes[BPM_BUFFER_OXY1_POS+1];  //HIGH
    beats_per_minute_OXY1 = beats_per_minute_OXY1<<8;              //LOW
    beats_per_minute_OXY1 = beats_per_minute_OXY1|(receive_bytes[BPM_BUFFER_OXY1_POS] & 0x0FF);

    if(beats_per_minute_OXY1 <= 300 && beats_per_minute_OXY1 > 0){
        BPM_Oxy1_function_values[function_value_count_SPO2_BPM_PI] = beats_per_minute_OXY1;
    }
    else{
        if(function_value_count_SPO2_BPM_PI != 0){
            BPM_Oxy1_function_values[function_value_count_SPO2_BPM_PI] =BPM_Oxy1_function_values[function_value_count_SPO2_BPM_PI-1];
        }
        else{
            BPM_Oxy1_function_values[function_value_count_SPO2_BPM_PI] =BPM_Oxy1_function_values[SPO2_FUNCTION_BUFFER_SIZE-1];
        }
    }

    beats_per_minute_OXY2 = receive_bytes[BPM_BUFFER_OXY2_POS+1];
    beats_per_minute_OXY2 = beats_per_minute_OXY2<<8;              //LOW
    beats_per_minute_OXY2 = beats_per_minute_OXY2|(receive_bytes[BPM_BUFFER_OXY2_POS] & 0x0FF);

    //----beat pulse--------------------------------------------------------------------------------
    if(beats_per_minute_OXY1 < 300){
        thread_beat->set_Interval((int)(((float)60/beats_per_minute_OXY1)*1000));
    }
    else{
        thread_beat->set_Interval((int)(((float)60/beats_per_minute_OXY2)*1000));
    }
    //-----------------------------------------------------------------------------------------------

    if(beats_per_minute_OXY2 <= 300 && beats_per_minute_OXY2 > 0){
        BPM_Oxy2_function_values[function_value_count_SPO2_BPM_PI] = beats_per_minute_OXY2;
    }
    else{
        if(function_value_count_SPO2_BPM_PI != 0){
            BPM_Oxy2_function_values[function_value_count_SPO2_BPM_PI] =BPM_Oxy2_function_values[function_value_count_SPO2_BPM_PI-1];
        }
        else{
            BPM_Oxy2_function_values[function_value_count_SPO2_BPM_PI] =BPM_Oxy2_function_values[SPO2_FUNCTION_BUFFER_SIZE-1];
        }
    }

    PI_value_OXY1 = receive_bytes[PI_BUFFER_OXY1_POS+1];
    PI_value_OXY1 = PI_value_OXY1<<8;              //LOW
    PI_value_OXY1 = PI_value_OXY1|(receive_bytes[PI_BUFFER_OXY1_POS] & 0x0FF);

    //PI_Oxy1_function_values[function_value_count_SPO2_BPM_PI] = PI_value_OXY1;

    if(PI_value_OXY1 <= 30000){
        PI_Oxy1_function_values[function_value_count_SPO2_BPM_PI] = PI_value_OXY1;
    }
    else{
        if(function_value_count_SPO2_BPM_PI != 0){
            PI_Oxy1_function_values[function_value_count_SPO2_BPM_PI] =PI_Oxy1_function_values[function_value_count_SPO2_BPM_PI-1];
        }
        else{
            PI_Oxy1_function_values[function_value_count_SPO2_BPM_PI] =PI_Oxy1_function_values[SPO2_FUNCTION_BUFFER_SIZE-1];
        }
    }

    PI_value_OXY2 = receive_bytes[PI_BUFFER_OXY2_POS+1];
    PI_value_OXY2 = PI_value_OXY2<<8;              //LOW
    PI_value_OXY2 = PI_value_OXY2|(receive_bytes[PI_BUFFER_OXY2_POS] & 0x0FF);

    //PI_Oxy2_function_values[function_value_count_SPO2_BPM_PI] = PI_value_OXY2;

    if(PI_value_OXY2 <= 30000){
        PI_Oxy2_function_values[function_value_count_SPO2_BPM_PI] = PI_value_OXY2;
    }
    else{
        if(function_value_count_SPO2_BPM_PI != 0){
            PI_Oxy2_function_values[function_value_count_SPO2_BPM_PI] =PI_Oxy2_function_values[function_value_count_SPO2_BPM_PI-1];
        }
        else{
            PI_Oxy2_function_values[function_value_count_SPO2_BPM_PI] =PI_Oxy2_function_values[SPO2_FUNCTION_BUFFER_SIZE-1];
        }
    }

    ui->l_HR_ECG->setText("-");
    if(beats_per_minute_OXY1 <= 300){
        ui->l_HR_Oxy1->setText(QString::number(beats_per_minute_OXY1));
    }
    else{
        ui->l_HR_Oxy1->setText("-");
    }
    if(beats_per_minute_OXY2 <= 300){
        ui->l_HR_Oxy2->setText(QString::number(beats_per_minute_OXY2));
    }
    else{
        ui->l_HR_Oxy2->setText("-");
    }

    if(SPO2_Oxy1_function_values[function_value_count_SPO2_BPM_PI] <= 100){
        ui->l_SpO2_Oxy1->setText(QString::number(SPO2_Oxy1_function_values[function_value_count_SPO2_BPM_PI])+"%");
    }
    else{
        ui->l_SpO2_Oxy1->setText("-");
    }

    if(SPO2_Oxy2_function_values[function_value_count_SPO2_BPM_PI] <= 100){
        ui->l_SpO2_Oxy2->setText(QString::number(SPO2_Oxy2_function_values[function_value_count_SPO2_BPM_PI])+"%");
    }
    else{
        ui->l_SpO2_Oxy2->setText("-");
    }

    ui->l_PI_Oxy1->setText(QString::number((float)PI_value_OXY1/1000)+"%");
    ui->l_PI_Oxy2->setText(QString::number((float)PI_value_OXY2/1000)+"%");


    function_value_count_SPO2_BPM_PI++;

    if(function_value_count_SPO2_BPM_PI >= SPO2_FUNCTION_BUFFER_SIZE){
        function_value_count_SPO2_BPM_PI=0;
    }
}


void MainWindow::on_pb_pant_paciente_descartar(){

    //ui->statusBar->showMessage("pb_descartar");
    ui->le_pant_paciente_Nombre->clear();
    ui->le_pant_paciente_ID->clear();
    ui->pb_pant_paciente_radioB_femenino->setStyleSheet(QStringLiteral("border-image: url(:/icons/pantalla_principal_sin_seleccion.png);"));
    ui->pb_pant_paciente_radioB_masculino->setStyleSheet(QStringLiteral("border-image: url(:/icons/pantalla_principal_sin_seleccion.png);"));
}

void MainWindow::on_pb_pant_paciente_test()
{
    update_data_pacient_in_labels(true);
    show_pantalla_test();
}

void MainWindow::on_pb_pant_paciente_nuevo()
{

}

void MainWindow::on_pb_pant_paciente_base_de_datos()
{
    //ui->statusBar->showMessage("on_pb_pant_paciente_base_de_datos");
    cargar_base_de_datos(data_base_name); // ficheros .dat se puede utilizar formato txt tambien

    show_pantalla_base_de_datos();
}

void MainWindow::on_pb_pant_paciente_menu()
{
    show_menu();
}

void MainWindow::show_menu()
{
    ui->widget_menu->show();
    ui->widget_menu->move(985,60);
    ui->widget_menu->raise();
}

void MainWindow::on_pb_pant_paciente_fecha_de_nacimiento()
{

}

void MainWindow::on_pb_pant_paciente_radioB_femenino()
{
    //ui->statusBar->showMessage("pb_radioB_femenino");
    ui->pb_pant_paciente_radioB_masculino->setStyleSheet(QStringLiteral("border-image: url(:/icons/pantalla_principal_sin_seleccion.png);"));
    ui->pb_pant_paciente_radioB_femenino->setStyleSheet(QStringLiteral("border-image: url(:/icons/pantalla_principal_seleccion.png);"));

    sexo_de_paciente = "femenino";
}

void MainWindow::on_pb_pant_paciente_radioB_masculino()
{
    //ui->statusBar->showMessage("pb_radioB_masculino");
    ui->pb_pant_paciente_radioB_femenino->setStyleSheet(QStringLiteral("border-image: url(:/icons/pantalla_principal_sin_seleccion.png);"));
    ui->pb_pant_paciente_radioB_masculino->setStyleSheet(QStringLiteral("border-image: url(:/icons/pantalla_principal_seleccion.png);"));

    sexo_de_paciente = "masculino";
}

void MainWindow::on_pb_pant_base_de_datos_nuevo()
{
    show_pantalla_paciente();

}

void MainWindow::on_pb_pant_base_de_datos_respaldar()
{
    QByteArray write_data;
    for (int i=0; i<UART_READ_BUFFER_SIZE;++i){

        write_data.append(INIT_SAVE_TO_SD);
    }
    ftdi_serial_port->write(write_data);

    ui->statusBar->showMessage("Respaldando datos ---------------");

    read_BD.clear();

    QFile *data_base = new QFile(data_base_name); // ficheros .dat se puede utilizar formato txt tambien


    if(data_base->open(QIODevice::ReadOnly))
    {
        while(!data_base->atEnd()){

            read_BD.append(data_base->read(UART_READ_BUFFER_SIZE));
        }
        data_base->close();
    }
    else{
        QMessageBox::information(this,"Informacion","No se ha podido cargar la base de datos   ",QMessageBox::Ok);
    }

    QObject::connect(&timer_respaldar_datos, SIGNAL(timeout()),this,SLOT(on_timer_respaldar_timeOut()));
    timer_respaldar_datos.setInterval(200);
    timer_respaldar_datos.start();
}

void MainWindow::on_timer_respaldar_timeOut(){

    ftdi_serial_port->write(read_BD.at(BD_transfer_count));

    BD_transfer_count++;

    if(BD_transfer_count >= read_BD.length()){

        timer_respaldar_datos.stop();
        QObject::disconnect(&timer_respaldar_datos, SIGNAL(timeout()),this,SLOT(on_timer_respaldar_timeOut()));
    }

    ui->statusBar->showMessage("Timer Respaldando datos ---------------",100);
}

void MainWindow::on_pb_menu_salir()
{
    this->close();
}

void MainWindow::on_pb_menu_ayuda()
{
    this->close();
}

void MainWindow::on_pb_menu_acerca_de()
{
    this->close();
}

void MainWindow::on_pb_pant_test_Graficar_Iniciar()
{
    ui->pb_pant_test_Graficar_Iniciar->setEnabled(false);

    if(ui->pb_pant_test_Ver_Registro_Guardar->text()!="VER REGISTRO"){
        QObject::connect(this,SIGNAL(data_Received(QByteArray)),this,SLOT(on_data_received(QByteArray)));
        QObject::connect(ftdi_serial_port,SIGNAL(readyRead()),this,SLOT(readSerial()));

    }

    Bebe_Data_Class bebe_temp;

    QString ID_string = ui->le_pant_paciente_ID->text();
    quint64 ID_copia = ID_string.toLongLong();
    bebe_temp.ID = (quint64)(ID_copia);

    bebe_temp.sexo = sexo_de_paciente;
    for(int i=0; bebe_temp.sexo.length() < SEX_STRING_LENGTH;i++){
        bebe_temp.sexo.append('&');
    }

    bebe_temp.cantidad_de_pruebas = 1;

    bebe_temp.state = "Seguimiento";
    for(quint16 i=0; bebe_temp.state.length() < STATE_STRING_LENGTH; i++){
        bebe_temp.state.append('&');
    }

    bebe_temp.birth_date = birth_date_paciente;
    QString birth_date_string = bebe_temp.birth_date.toString();
    for(quint16 i=0; birth_date_string.length() < DATE_STRING_LENGTH; i++){
        birth_date_string.append('&');
    }

    bebe_temp.baby_name = "unknow";
    for(quint16 i=0; bebe_temp.baby_name.length() < NAMES_STRING_LENGTH; i++){
        bebe_temp.baby_name.append('&');
    }
    bebe_temp.mother_name = ui->le_pant_paciente_Nombre->text();
    for(quint16 i=0; bebe_temp.mother_name.length() < NAMES_STRING_LENGTH; i++){
        bebe_temp.mother_name.append('&');
    }

    bebe_temp.date = QDate::currentDate();
    QString date_string = bebe_temp.date.toString();
    for(quint16 i=0; date_string.length() < DATE_STRING_LENGTH; i++){
        date_string.append('&');
    }

    bebe_temp.time = QTime::currentTime();
    QString time_string = bebe_temp.time.toString();
    for(quint16 i=0; time_string.length() < TIME_STRING_LENGTH; i++){
        time_string.append('&');
    }


    QByteArray envio_en_bytes;

    ///ID en byteArray-------------------------------------------------------------------
    envio_en_bytes.append(quint64_to_QByte_Array(bebe_temp.ID));
    ////------------------------------------------------------------------------------

    /// sexo en byteArray-------------------------------------------------------------------
    envio_en_bytes.append(QString_to_QByte_Array(bebe_temp.sexo));
    ////------------------------------------------------------------------------------

    ///cantidad_de_pruebas en byteArray-------------------------------------------------------------------
    envio_en_bytes.append(quint32_to_QByte_Array(bebe_temp.cantidad_de_pruebas));
    ////------------------------------------------------------------------------------

    /// estado en byteArray-------------------------------------------------------------------
    envio_en_bytes.append(QString_to_QByte_Array(bebe_temp.state));
    ////------------------------------------------------------------------------------

    /// birth_date en byteArray-------------------------------------------------------------------
    envio_en_bytes.append(QString_to_QByte_Array(birth_date_string));
    ////------------------------------------------------------------------------------

    /// baby_name en byteArray-------------------------------------------------------------------
    envio_en_bytes.append(QString_to_QByte_Array(bebe_temp.baby_name));
    ////------------------------------------------------------------------------------

    /// mother name en byteArray-------------------------------------------------------------------
    envio_en_bytes.append(QString_to_QByte_Array(bebe_temp.mother_name));
    ////------------------------------------------------------------------------------

    /// date en byteArray-------------------------------------------------------------------
    envio_en_bytes.append(QString_to_QByte_Array(date_string));
    ////------------------------------------------------------------------------------

    /// time en byteArray-------------------------------------------------------------------
    envio_en_bytes.append(QString_to_QByte_Array(time_string));
    ////------------------------------------------------------------------------------

    quint16 size_send_info = envio_en_bytes.length();

    envio_en_bytes.prepend(quint16_to_QByte_Array(size_send_info));

    for(quint8 i=0; i<4; i++){

        envio_en_bytes.prepend(INIT_SEND_ID);
    }

    quint32 c = envio_en_bytes.length();

    for(quint32 i = c; i < UART_READ_BUFFER_SIZE; i++){

        envio_en_bytes.append(0x0ff);
    }

    ftdi_serial_port->write(envio_en_bytes);

    tiempo_de_Prueba = QTime(0,0,0);

    ui->statusBar->showMessage("Enviando datos ---------------");
}

QByteArray MainWindow::quint32_to_QByte_Array(quint32 integer){

    QByteArray envio_en_bytes, envio_en_bytes_reverse;

    envio_en_bytes_reverse.append((char*)&(integer));

    for(int i=envio_en_bytes_reverse.length(); i < 4; i++){

        envio_en_bytes_reverse.append(0x0f);
        envio_en_bytes_reverse[i]=0;
    }

    for(int i=envio_en_bytes_reverse.length()-1; i >= 0; i--){

        envio_en_bytes.append(envio_en_bytes_reverse.at(i));
    }
    return envio_en_bytes;
}

QByteArray MainWindow::quint64_to_QByte_Array(quint64 integer){

    QByteArray envio_en_bytes, envio_en_bytes_reverse;

    envio_en_bytes_reverse.append((char*)&(integer));

    for(int i=envio_en_bytes_reverse.length(); i < 8; i++){

        envio_en_bytes_reverse.append(0x0f);
        envio_en_bytes_reverse[i]=0;
    }

    for(int i=envio_en_bytes_reverse.length()-1; i >= 0; i--){

        envio_en_bytes.append(envio_en_bytes_reverse.at(i));
    }
    return envio_en_bytes;
}

QByteArray MainWindow::quint16_to_QByte_Array(quint16 integer){

    QByteArray envio_en_bytes;

    envio_en_bytes.append(integer>>8);
    envio_en_bytes.append(integer & 0x0FF);

    return envio_en_bytes;
}

QByteArray MainWindow::QString_to_QByte_Array(QString string){

    quint32 temp_32_t = string.toLatin1().length() * 2;
    QByteArray envio_en_bytes;
    QByteArray envio_en_bytes_reverse;

    envio_en_bytes_reverse.append((char*)&(temp_32_t));

    for(quint8 i = envio_en_bytes_reverse.length(); i < 4; i++){  ////rellenar hasta 32bits
        envio_en_bytes_reverse.append(0x0f);
        envio_en_bytes_reverse[i]=0;
    }
    for(int i=envio_en_bytes_reverse.length()-1; i >= 0; i--){

        envio_en_bytes.append(envio_en_bytes_reverse.at(i));
    }

    for(quint32 i = 0; i < temp_32_t/2; i++){

        envio_en_bytes.append(0x0F);
        envio_en_bytes[envio_en_bytes.length()-1]=0;
        envio_en_bytes.append(string.toLatin1().at(i));
    }

    return envio_en_bytes;
}

void MainWindow::on_pb_pant_test_Ver_Registro_Guardar()
{
    ui->statusBar->showMessage("GUARDAR");

    if(ui->pb_pant_test_Ver_Registro_Guardar->text() == "GUARDAR"){
        if(QMessageBox::Ok==QMessageBox::question(this,"CONFIRMACI??N","Desea guardar datos recibidos",QMessageBox::Ok,QMessageBox::No)){

            QFile *data_base= new QFile(data_base_name);

            if(data_base->open(QIODevice::Append))
            {
                timer_graph.stop();
                QObject::disconnect(ftdi_serial_port,SIGNAL(readyRead()),this,SLOT(readSerial()));
                ftdi_serial_port->flush();
                ftdi_serial_port->close();

                QDataStream out(data_base);

                quint32 fin_i=0;
                if(primera_vuelta){
                    fin_i = function_value_count_SPO2_BPM_PI;
                }
                else{
                    fin_i = SPO2_FUNCTION_BUFFER_SIZE;
                }
                quint32 fin_i_resta_SPO2_OXY1=0;
                quint32 fin_i_resta_SPO2_OXY2=0;
                quint32 fin_i_resta_BPM_OXY1=0;
                quint32 fin_i_resta_BPM_OXY2=0;
                quint32 fin_i_resta_PI_OXY1=0;
                quint32 fin_i_resta_PI_OXY2=0;

                float PI_Oxy1=0, PI_Oxy2=0;

                for(quint32 i=0; i < fin_i; i++){

                    if(SPO2_Oxy1_function_values[i]>0 && SPO2_Oxy1_function_values[i]<=100)
                        SPO2_bebe_value_average_OXY1+= SPO2_Oxy1_function_values[i];
                    else
                        fin_i_resta_SPO2_OXY1++;

                    if(SPO2_Oxy2_function_values[i]>0 && SPO2_Oxy2_function_values[i]<=100)
                        SPO2_bebe_value_average_OXY2+= SPO2_Oxy2_function_values[i];
                    else
                        fin_i_resta_SPO2_OXY2++;

                    if(BPM_Oxy1_function_values[i]>0 && BPM_Oxy1_function_values[i]<=300)
                        beats_per_minute_value_average_OXY1+= BPM_Oxy1_function_values[i];
                    else
                        fin_i_resta_BPM_OXY1++;

                    if(BPM_Oxy2_function_values[i]>0 && BPM_Oxy2_function_values[i]<=300)
                        beats_per_minute_value_average_OXY2+= BPM_Oxy2_function_values[i];
                    else
                        fin_i_resta_BPM_OXY2++;

                    if(PI_Oxy1_function_values[i]>0 && PI_Oxy1_function_values[i]<=30000)
                        PI_Oxy1+= (float)PI_Oxy1_function_values[i]/1000;
                    else
                        fin_i_resta_PI_OXY1++;
                    if(PI_Oxy2_function_values[i]>0 && PI_Oxy2_function_values[i]<=30000)
                        PI_Oxy2+= (float)PI_Oxy2_function_values[i]/1000;
                    else
                        fin_i_resta_PI_OXY2++;
                }
                SPO2_bebe_value_average_OXY1 = (quint8)((float)SPO2_bebe_value_average_OXY1/(fin_i-fin_i_resta_SPO2_OXY1));
                SPO2_bebe_value_average_OXY2 = (quint8)((float)SPO2_bebe_value_average_OXY2/(fin_i-fin_i_resta_SPO2_OXY2));
                beats_per_minute_value_average_OXY1 = (qint16)((float)beats_per_minute_value_average_OXY1/(fin_i-fin_i_resta_BPM_OXY1));
                beats_per_minute_value_average_OXY2 = (qint16)((float)beats_per_minute_value_average_OXY2/(fin_i-fin_i_resta_BPM_OXY2));
                PI_value_average_OXY1 = (quint16)(((float)PI_Oxy1/(fin_i-fin_i_resta_PI_OXY1))*1000);
                PI_value_average_OXY2 = (quint16)(((float)PI_Oxy2/(fin_i-fin_i_resta_PI_OXY2))*1000);


                bebe_object->baby_name = "unknow";
                QString ID_string = ui->le_pant_paciente_ID->text();
                quint64 ID_copia = ID_string.toLongLong();
                bebe_object->ID = (quint64)(ID_copia);
                bebe_object->mother_name = ui->le_pant_paciente_Nombre->text();
                bebe_object->sexo = sexo_de_paciente;
                bebe_object->date = QDate::currentDate();
                bebe_object->time = QTime::currentTime();
                bebe_object->beats_per_minute_value_average_OXY1 = beats_per_minute_value_average_OXY1;
                bebe_object->beats_per_minute_value_average_OXY2 = beats_per_minute_value_average_OXY2;
                bebe_object->PI_value_average_OXY1 = PI_value_average_OXY1;
                bebe_object->PI_value_average_OXY2 = PI_value_average_OXY2;
                bebe_object->birth_date = birth_date_paciente;
                bebe_object->SPO2_bebe_value_average_OXY1 = SPO2_bebe_value_average_OXY1;
                bebe_object->SPO2_bebe_value_average_OXY2 = SPO2_bebe_value_average_OXY2;
                bebe_object->state = "Seguimiento";
                bebe_object->cantidad_de_pruebas = 1;

                if(primera_vuelta ){

                    memcpy(&(bebe_object->function_0_data_bebe[0]), &function_values_graph_0[0], function_value_pos);
                    memcpy(&(bebe_object->function_1_data_bebe[0]), &function_values_graph_1[0], function_value_pos);
                    memcpy(&(bebe_object->HR_data_bebe[0]), &function_values_graph_HR_16bits[0], HR_value_pos*2); //por 2 porque son 16bits

                    memcpy(&(bebe_object->SPO2_function_OXY1_data_bebe[0]), &SPO2_Oxy1_function_values[0], function_value_count_SPO2_BPM_PI);
                    memcpy(&(bebe_object->SPO2_function_OXY2_data_bebe[0]), &SPO2_Oxy2_function_values[0], function_value_count_SPO2_BPM_PI);
                    memcpy(&(bebe_object->BPM_function_OXY1_data_bebe[0]), &BPM_Oxy1_function_values[0], function_value_count_SPO2_BPM_PI);
                    memcpy(&(bebe_object->BPM_function_OXY2_data_bebe[0]), &BPM_Oxy2_function_values[0], function_value_count_SPO2_BPM_PI);
                    memcpy(&(bebe_object->PI_function_OXY1_data_bebe[0]), &PI_Oxy1_function_values[0], function_value_count_SPO2_BPM_PI);
                    memcpy(&(bebe_object->PI_function_OXY2_data_bebe[0]), &PI_Oxy2_function_values[0], function_value_count_SPO2_BPM_PI);

                    bebe_object->data_function_size = function_value_pos;
                    bebe_object->data_adc_buffer_size = HR_value_pos;

                    bebe_object->SPO2_data_function_OXY1_size = function_value_count_SPO2_BPM_PI;
                    bebe_object->SPO2_data_function_OXY2_size = function_value_count_SPO2_BPM_PI;
                    bebe_object->BPM_data_function_OXY1_size = function_value_count_SPO2_BPM_PI;
                    bebe_object->BPM_data_function_OXY2_size = function_value_count_SPO2_BPM_PI;
                    bebe_object->PI_data_function_OXY1_size = function_value_count_SPO2_BPM_PI;
                    bebe_object->PI_data_function_OXY2_size = function_value_count_SPO2_BPM_PI;

                }else{
                    if(function_value_pos != DATA_FUNCTION_SIZE)
                        memcpy(&(bebe_object->function_0_data_bebe[0]), &function_values_graph_0[function_value_pos], DATA_FUNCTION_SIZE - function_value_pos);
                    if(function_value_pos != 0)
                        memcpy(&(bebe_object->function_0_data_bebe[DATA_FUNCTION_SIZE - function_value_pos]), &function_values_graph_0[0], function_value_pos);

                    if(function_value_pos != DATA_FUNCTION_SIZE)
                        memcpy(&(bebe_object->function_1_data_bebe[0]), &function_values_graph_1[function_value_pos], DATA_FUNCTION_SIZE - function_value_pos);
                    if(function_value_pos != 0)
                        memcpy(&(bebe_object->function_1_data_bebe[DATA_FUNCTION_SIZE - function_value_pos]), &function_values_graph_1[0], function_value_pos);

                    if(HR_value_pos != DATA_ADC_BUFFER_SIZE)
                        memcpy(bebe_object->HR_data_bebe, &function_values_graph_HR_16bits[HR_value_pos], (DATA_ADC_BUFFER_SIZE - HR_value_pos)*2); //por porque son transferencias de 16bits
                    if(HR_value_pos != 0)
                        memcpy(&(bebe_object->HR_data_bebe[DATA_ADC_BUFFER_SIZE - HR_value_pos]), &function_values_graph_HR_16bits[0], HR_value_pos*2); //por porque son transferencias de 16bits

                    if(function_value_count_SPO2_BPM_PI != SPO2_FUNCTION_BUFFER_SIZE){

                        memcpy(bebe_object->SPO2_function_OXY1_data_bebe, &SPO2_Oxy1_function_values[function_value_count_SPO2_BPM_PI], SPO2_FUNCTION_BUFFER_SIZE - function_value_count_SPO2_BPM_PI);
                        memcpy(bebe_object->SPO2_function_OXY2_data_bebe, &SPO2_Oxy2_function_values[function_value_count_SPO2_BPM_PI], SPO2_FUNCTION_BUFFER_SIZE - function_value_count_SPO2_BPM_PI);
                        memcpy(bebe_object->BPM_function_OXY1_data_bebe, &BPM_Oxy1_function_values[function_value_count_SPO2_BPM_PI], SPO2_FUNCTION_BUFFER_SIZE - function_value_count_SPO2_BPM_PI);
                        memcpy(bebe_object->BPM_function_OXY2_data_bebe, &BPM_Oxy2_function_values[function_value_count_SPO2_BPM_PI], SPO2_FUNCTION_BUFFER_SIZE - function_value_count_SPO2_BPM_PI);
                        memcpy(bebe_object->PI_function_OXY1_data_bebe, &PI_Oxy1_function_values[function_value_count_SPO2_BPM_PI], SPO2_FUNCTION_BUFFER_SIZE - function_value_count_SPO2_BPM_PI);
                        memcpy(bebe_object->PI_function_OXY2_data_bebe, &PI_Oxy2_function_values[function_value_count_SPO2_BPM_PI], SPO2_FUNCTION_BUFFER_SIZE - function_value_count_SPO2_BPM_PI);
                    }
                    if(function_value_count_SPO2_BPM_PI != 0){

                        memcpy(&(bebe_object->SPO2_function_OXY1_data_bebe[SPO2_FUNCTION_BUFFER_SIZE - function_value_count_SPO2_BPM_PI]), &SPO2_Oxy1_function_values[0], function_value_count_SPO2_BPM_PI);
                        memcpy(&(bebe_object->SPO2_function_OXY2_data_bebe[SPO2_FUNCTION_BUFFER_SIZE - function_value_count_SPO2_BPM_PI]), &SPO2_Oxy2_function_values[0], function_value_count_SPO2_BPM_PI);
                        memcpy(&(bebe_object->BPM_function_OXY1_data_bebe[SPO2_FUNCTION_BUFFER_SIZE - function_value_count_SPO2_BPM_PI]), &BPM_Oxy1_function_values[0], function_value_count_SPO2_BPM_PI);
                        memcpy(&(bebe_object->BPM_function_OXY2_data_bebe[SPO2_FUNCTION_BUFFER_SIZE - function_value_count_SPO2_BPM_PI]), &BPM_Oxy2_function_values[0], function_value_count_SPO2_BPM_PI);
                        memcpy(&(bebe_object->PI_function_OXY1_data_bebe[SPO2_FUNCTION_BUFFER_SIZE - function_value_count_SPO2_BPM_PI]), &PI_Oxy1_function_values[0], function_value_count_SPO2_BPM_PI);
                        memcpy(&(bebe_object->PI_function_OXY2_data_bebe[SPO2_FUNCTION_BUFFER_SIZE - function_value_count_SPO2_BPM_PI]), &PI_Oxy2_function_values[0], function_value_count_SPO2_BPM_PI);

                    }

                    bebe_object->data_function_size = DATA_FUNCTION_SIZE;
                    bebe_object->data_adc_buffer_size = DATA_ADC_BUFFER_SIZE;

                    bebe_object->SPO2_data_function_OXY1_size = SPO2_FUNCTION_BUFFER_SIZE;
                    bebe_object->SPO2_data_function_OXY2_size = SPO2_FUNCTION_BUFFER_SIZE;
                    bebe_object->BPM_data_function_OXY1_size = SPO2_FUNCTION_BUFFER_SIZE;
                    bebe_object->BPM_data_function_OXY2_size = SPO2_FUNCTION_BUFFER_SIZE;
                    bebe_object->PI_data_function_OXY1_size = SPO2_FUNCTION_BUFFER_SIZE;
                    bebe_object->PI_data_function_OXY2_size = SPO2_FUNCTION_BUFFER_SIZE;
                }


                //Posicion de Paciente en Archivo y tama??os de datos------------------------------------------------------------------
                bebe_object->posicion_en_archivo = data_base->pos();

                bebe_object->cantidad_de_pacientes = lista_de_pacientes.length()+1;

                bebe_object->numero_de_paciente = lista_de_pacientes.length()+1;

                bebe_object->size_of_pacient_data = 0;

                bebe_object->size_of_pacient_data += sizeof(bebe_object->ID);
                bebe_object->size_of_pacient_data += SIZEOF_SEX_STRING/*sizeof(uint32_t)*/;
                bebe_object->size_of_pacient_data += sizeof(bebe_object->cantidad_de_pruebas);
                bebe_object->size_of_pacient_data += SIZEOF_STATE_STRING;  ///30
                bebe_object->size_of_pacient_data += SIZEOF_DATE_STRING;///40 >36
                bebe_object->size_of_pacient_data += SIZEOF_NAMES_STRING;
                bebe_object->size_of_pacient_data += SIZEOF_NAMES_STRING;///80
                bebe_object->size_of_pacient_data += SIZEOF_DATE_STRING;///40 >36
                bebe_object->size_of_pacient_data += SIZEOF_TIME_STRING; /// 24 >20
                bebe_object->size_of_pacient_data += sizeof(bebe_object->SPO2_bebe_value_average_OXY1); ///1
                bebe_object->size_of_pacient_data += sizeof(bebe_object->SPO2_bebe_value_average_OXY2); ///1
                bebe_object->size_of_pacient_data += sizeof(bebe_object->beats_per_minute_value_average_OXY1); ///2
                bebe_object->size_of_pacient_data += sizeof(bebe_object->beats_per_minute_value_average_OXY2); ///2
                bebe_object->size_of_pacient_data += sizeof(bebe_object->PI_value_average_OXY1); ///2
                bebe_object->size_of_pacient_data += sizeof(bebe_object->PI_value_average_OXY2); ///2

                bebe_object->size_of_pacient_info = bebe_object->size_of_pacient_data;

                bebe_object->size_of_pacient_data += sizeof(bebe_object->data_function_size); ///4
                bebe_object->size_of_pacient_data += bebe_object->data_function_size*2; ///37500 ->18750*2
                bebe_object->size_of_pacient_data += sizeof(bebe_object->data_adc_buffer_size);///4
                bebe_object->size_of_pacient_data += bebe_object->data_adc_buffer_size*2; ////150000 -> 75000*2 ->5min
                bebe_object->size_of_pacient_data += sizeof(bebe_object->SPO2_data_function_OXY1_size);///4
                bebe_object->size_of_pacient_data += bebe_object->SPO2_data_function_OXY1_size; ///750
                bebe_object->size_of_pacient_data += sizeof(bebe_object->SPO2_data_function_OXY2_size); ///4
                bebe_object->size_of_pacient_data += bebe_object->SPO2_data_function_OXY2_size; ///750
                bebe_object->size_of_pacient_data += sizeof(bebe_object->BPM_data_function_OXY1_size); ///4
                bebe_object->size_of_pacient_data += bebe_object->BPM_data_function_OXY1_size*2; ///1500
                bebe_object->size_of_pacient_data += sizeof(bebe_object->BPM_data_function_OXY2_size);///4
                bebe_object->size_of_pacient_data += bebe_object->BPM_data_function_OXY2_size*2;///1500
                bebe_object->size_of_pacient_data += sizeof(bebe_object->PI_data_function_OXY1_size);///4
                bebe_object->size_of_pacient_data += bebe_object->PI_data_function_OXY1_size*2;///1500
                bebe_object->size_of_pacient_data += sizeof(bebe_object->PI_data_function_OXY2_size);///4
                bebe_object->size_of_pacient_data += bebe_object->PI_data_function_OXY2_size*2;///1500

                bebe_object->size_of_pacient_signals = bebe_object->size_of_pacient_data - bebe_object->size_of_pacient_info;///195032

                bebe_object->size_of_pacient_data += sizeof(bebe_object->size_of_pacient_info);
                bebe_object->size_of_pacient_data += sizeof(bebe_object->size_of_pacient_signals);

                bebe_object->size_of_pacient_data += sizeof(bebe_object->posicion_en_archivo);
                bebe_object->size_of_pacient_data += sizeof(bebe_object->cantidad_de_pacientes);
                bebe_object->size_of_pacient_data += sizeof(bebe_object->numero_de_paciente);
                bebe_object->size_of_pacient_data += sizeof(quint32); //el tama??o de ??l mismo (sizeof(size_of_pacient_data))
                //---------------------------------------------------------------------------------------------------------------------

                //Enviar promedio de mediciones al la SD--------------------------------------------------------------------------------

                ftdi_serial_port->open(QSerialPort::ReadWrite);

                QByteArray write_data;

                for (int i = 0; i<DESPLAZAMIENTO_EN_ENVIO_DE_PROMEDIOS-1;++i){

                    write_data.append(STOP_SAVE_TO_SD);
                }

                if(primera_vuelta){

                    write_data.append(0x0BB);
                }
                else{
                    write_data.append(0xFF);
                }

                write_data.append(SPO2_bebe_value_average_OXY1);

                write_data.append(SPO2_bebe_value_average_OXY2);


                write_data.append((beats_per_minute_value_average_OXY1>>8) & 0x0FF);  //BPM_BUFFER_OXY1_POS

                write_data.append((beats_per_minute_value_average_OXY1) & 0x0FF); //BPM_BUFFER_OXY1_POS


                write_data.append((beats_per_minute_value_average_OXY2>>8) & 0x0FF);//BPM_BUFFER_OXY2_POS

                write_data.append((beats_per_minute_value_average_OXY2) & 0x0FF);//BPM_BUFFER_OXY2_POS


                write_data.append((PI_value_average_OXY1>>8) & 0x0FF);//PI_BUFFER_OXY1_POS

                write_data.append((PI_value_average_OXY1) & 0x0FF);//PI_BUFFER_OXY1_POS


                write_data.append((PI_value_average_OXY2>>8) & 0x0FF);//PI_BUFFER_OXY2_POS

                write_data.append((PI_value_average_OXY2) & 0x0FF);//PI_BUFFER_OXY2_POS

                if(primera_vuelta){


                    write_data.append(quint32_to_QByte_Array(function_value_pos));

                    write_data.append(quint32_to_QByte_Array(HR_value_pos));

                    for(quint8 i=0; i<6;i++){
                        write_data.append(quint32_to_QByte_Array(function_value_count_SPO2_BPM_PI));
                    }

                }
                else{
                    quint32 size = DATA_FUNCTION_SIZE;
                    write_data.append(quint32_to_QByte_Array(size));

                    size = DATA_ADC_BUFFER_SIZE;
                    write_data.append(quint32_to_QByte_Array(size));

                    size = SPO2_FUNCTION_BUFFER_SIZE;
                    for(quint8 i=0; i<6;i++){
                        write_data.append(quint32_to_QByte_Array(size));
                    }
                }

                write_data.append(quint64_to_QByte_Array(bebe_object->posicion_en_archivo));
                write_data.append(quint32_to_QByte_Array(bebe_object->cantidad_de_pacientes));
                write_data.append(quint32_to_QByte_Array(bebe_object->numero_de_paciente));
                write_data.append(quint32_to_QByte_Array(bebe_object->size_of_pacient_data));
                write_data.append(quint32_to_QByte_Array(bebe_object->size_of_pacient_info));
                write_data.append(quint32_to_QByte_Array(bebe_object->size_of_pacient_signals));

                for (int i = write_data.length(); i<UART_READ_BUFFER_SIZE;++i){

                    write_data.append(STOP_SAVE_TO_SD);
                }

                ftdi_serial_port->write(write_data);



                QObject::connect(&wait_for_acknowledge,SIGNAL(timeout()),this,SLOT(timeOut_wait_for_acknowledge()));
                wait_for_acknowledge.setInterval(150);
                wait_for_acknowledge.start();
                //----------------------------------------------------------------------------------------------------------------------


                bebe_object->write_file_with_size_data_fix_strings(out);

                data_base->close();

                data_base->deleteLater();

                generar_reporte();

                QMessageBox::information(this,"Informacion","Se ha guardado correctamente datos",QMessageBox::Ok);
            }
            else {

                QMessageBox::information(this,"Informacion","No se pudo guardar",QMessageBox::Ok);
            }
        }
    }
    else if(ui->pb_pant_test_Ver_Registro_Guardar->text() == "VER REGISTRO"){

        timer_graph.stop();

        QObject::disconnect(&timer_graph,SIGNAL(timeout()),this,SLOT(afterUpdateGraph()));

        QObject::connect(&timer_graph,SIGNAL(timeout()),this,SLOT(on_time_out_Ver_registro()));

        ui->l_SpO2_Oxy1->setText((QString::number((bebe_object->SPO2_bebe_value_average_OXY1)))+"%");
        ui->l_SpO2_Oxy2->setText((QString::number((bebe_object->SPO2_bebe_value_average_OXY2)))+"%");
        ui->l_HR_Oxy1->setText((QString::number((bebe_object->beats_per_minute_value_average_OXY1))));
        ui->l_HR_Oxy2->setText((QString::number((bebe_object->beats_per_minute_value_average_OXY2))));
        ui->l_PI_Oxy1->setText((QString::number(((float)bebe_object->PI_value_average_OXY1/1000)))+"%");
        ui->l_PI_Oxy2->setText((QString::number(((float)bebe_object->PI_value_average_OXY2/1000)))+"%");

        keyData_graph_HR_recorded.clear();
        valueData_graph_HR_recorded.clear();

        porciento_de_adquirido =0;

        for(int i=0;i<4;i++){

            keyData_graph_HR_recorded<<i+1;
            valueData_graph_HR_recorded<<i+1;
        }

        ver_registro_counter=0;

        customPlot_graph_Oxy1->clear_Data();
        customPlot_graph_Oxy2->clear_Data();
        customPlot_graph_EKG->clear_Data();

        ver_registro_activated = true;

        timer_graph.start();
    }
}

void MainWindow::generar_reporte()
{
    if(!ui->le_pant_paciente_Nombre->text().isEmpty()){

        int paso=40;

        QString dir_path = QFileDialog::getExistingDirectory(this,tr("Seleccione Carpeta para Guardar"));
        dir_path+=QString("/Reportes");
        QDir dir(dir_path);

        if (!dir.exists()) { // don't overwrite existing folders
            if (!dir.mkdir(dir_path)) {
                qDebug() << "Error creating directory: " <<  dir;
            }
        }



        QString file_name= QString("Reportes/Reporte de ") + ui->le_pant_paciente_Nombre->text()+QString(".txt");
        int n = 1;
        while(QFile::exists(file_name)){
            n++;
            file_name = QString("Reportes/Reporte de ") + ui->le_pant_paciente_Nombre->text() + QString(" numero ")+QString::number(n)+QString(".txt");
        }

        QFile *file = new QFile(file_name,this);

        if(file->open(QIODevice::WriteOnly)){
            QDataStream out(file);
            //stream_out << "Oximetro 1: \n";
            out<<("Oximetro 1:");
            out<<endl;
            out<<endl;

            if(primera_vuelta){

                for(unsigned int i=0; i< function_value_pos;i++){

                    out<<(QString::number(function_values_graph_0[i]).toLatin1());
                    out<<(",");
                    if((i+1) % paso == 0){
                        out<<endl;
                    }
                }

            }
            else{
                for(unsigned int i=function_value_pos; i< DATA_FUNCTION_SIZE;i++){

                    out<<(QString::number(function_values_graph_0[i]).toLatin1());
                    out<<(",");
                    if((i+1) % paso == 0){
                        out<<endl;
                    }
                }
                for(unsigned int i=0; i< function_value_pos;i++){

                    out<<(QString::number(function_values_graph_0[i]).toLatin1());
                    out<<(",");
                    if((i+1) % paso == 0){
                        out<<endl;
                    }
                }
            }
            out<<endl;
            out<<endl;
            out<<endl;
            out<<("Oximetro 2:");
            out<<endl;
            out<<endl;
            if(primera_vuelta){

                for(unsigned int i=0; i< function_value_pos;i++){

                    out<<(QString::number(function_values_graph_1[i]).toLatin1());
                    out<<(",");
                    if((i+1) % paso == 0){
                        out<<endl;
                    }
                }

            }
            else{
                for(unsigned int i=function_value_pos; i< DATA_FUNCTION_SIZE;i++){

                    out<<(QString::number(function_values_graph_1[i]).toLatin1());
                    out<<(",");
                    if((i+1) % paso == 0){
                        out<<endl;
                    }
                }
                for(unsigned int i=0; i< function_value_pos;i++){

                    out<<(QString::number(function_values_graph_1[i]).toLatin1());
                    out<<(",");
                    if((i+1) % paso == 0){
                        out<<endl;
                    }
                }
            }

            out<<endl;
            out<<endl;
            out<<endl;
            out<<endl;
            out<<("Electrocardiografia:");
            out<<endl;
            out<<endl;

            if(primera_vuelta){

                for(unsigned int i=0; i< HR_value_pos;i++){

                    out<<(QString::number(function_values_graph_HR_16bits[i]).toLatin1());
                    out<<(",");
                    if((i+1) % paso == 0){
                        out<<endl;
                    }
                }
            }
            else{
                for(unsigned int i=HR_value_pos; i< DATA_ADC_BUFFER_SIZE;i++){

                    out<<(QString::number(function_values_graph_HR_16bits[i]).toLatin1());
                    out<<(",");
                    if((i+1) % paso == 0){
                        out<<endl;
                    }
                }
                for(unsigned int i=0; i< HR_value_pos;i++){

                    out<<(QString::number(function_values_graph_HR_16bits[i]).toLatin1());
                    out<<(",");
                    if((i+1) % paso == 0){
                        out<<endl;
                    }
                }
            }

            out<<endl;
            out<<endl;
            out<<endl;
            out<<endl;
            out<<("SPO2 OXYMETER 1:");
            out<<endl;
            out<<endl;

            if(primera_vuelta){

                for(unsigned int i=0; i< function_value_count_SPO2_BPM_PI;i++){

                    out<<(QString::number(SPO2_Oxy1_function_values[i]).toLatin1());
                    out<<(",");
                    if((i+1) % paso == 0){
                        out<<endl;
                    }
                }

            }
            else{
                for(unsigned int i=function_value_count_SPO2_BPM_PI; i< SPO2_FUNCTION_BUFFER_SIZE;i++){

                    out<<(QString::number(SPO2_Oxy1_function_values[i]).toLatin1());
                    out<<(",");
                    if((i+1) % paso == 0){
                        out<<endl;
                    }
                }
                for(unsigned int i=0; i< function_value_count_SPO2_BPM_PI;i++){

                    out<<(QString::number(SPO2_Oxy1_function_values[i]).toLatin1());
                    out<<(",");
                    if((i+1) % paso == 0){
                        out<<endl;
                    }
                }
            }

            out<<endl;
            out<<endl;
            out<<endl;
            out<<endl;
            out<<("SPO2 OXYMETER 2:");
            out<<endl;
            out<<endl;

            if(primera_vuelta){

                for(unsigned int i=0; i< function_value_count_SPO2_BPM_PI;i++){

                    out<<(QString::number(SPO2_Oxy2_function_values[i]).toLatin1());
                    out<<(",");
                    if((i+1) % paso == 0){
                        out<<endl;
                    }
                }

            }
            else{
                for(unsigned int i=function_value_count_SPO2_BPM_PI; i< SPO2_FUNCTION_BUFFER_SIZE;i++){

                    out<<(QString::number(SPO2_Oxy2_function_values[i]).toLatin1());
                    out<<(",");
                    if((i+1) % paso == 0){
                        out<<endl;
                    }
                }
                for(unsigned int i=0; i< function_value_count_SPO2_BPM_PI;i++){

                    out<<(QString::number(SPO2_Oxy2_function_values[i]).toLatin1());
                    out<<(",");
                    if((i+1) % paso == 0){
                        out<<endl;
                    }
                }
            }

            file->close();

            QMessageBox::information(this, "Reporte", file_name + QString(" generado correctamente"), QMessageBox::Ok);
        }
    }
}

void MainWindow::on_pb_pant_test_ajustes(){

    show_pantalla_ajustes();
}

void MainWindow::on_pb_pant_test_pause_play(){


    if(!pausado){

        ui->pb_pant_test_pause_play->setPixmap(QPixmap(":/icons/button_play.png"));
        timer_graph.stop();
        pausado = true;

        customPlot_graph_Oxy1->enable_maximize_button(true);
        customPlot_graph_Oxy2->enable_maximize_button(true);
        customPlot_graph_EKG->enable_maximize_button(true);
    }
    else{

        ui->pb_pant_test_pause_play->setPixmap(QPixmap(":/icons/button_pausar.png"));
        timer_graph.start();
        pausado = false;

        customPlot_graph_Oxy1->enable_maximize_button(false);
        customPlot_graph_Oxy2->enable_maximize_button(false);
        customPlot_graph_EKG->enable_maximize_button(false);
    }
}

void MainWindow::on_pb_pant_test_atras()
{
    on_pb_pant_paciente_nuevo();
}


void MainWindow::on_pb_pant_ajustes_Generales()
{
    if(ui->widget_ajustes_generales_Generales->isHidden()){

        ui->widget_pantalla_ajustes->setFixedHeight(ui->widget_pantalla_ajustes->size().height()+ui->widget_ajustes_generales_Generales->size().height());

        delta_y_constant_scrolling_ajustes -= ui->widget_ajustes_generales_Generales->size().height();

        ui->statusBar->showMessage(QString::number(delta_y_constant_scrolling_ajustes));

        ui->widget_ajustes_generales_Generales->show();
        ui->widget_ajustes_generales_Generales->move(ui->pb_pant_ajustes_generales_Generales->pos().x()+60,ui->pb_pant_ajustes_generales_Generales->pos().y()+50);

        ui->pb_pant_ajustes_generales_Visualizacion->move(ui->pb_pant_ajustes_generales_Visualizacion->pos().x(),
                                                          ui->pb_pant_ajustes_generales_Visualizacion->pos().y()+ui->widget_ajustes_generales_Generales->size().height());
        ui->pb_pant_ajustes_generales_ECG->move(ui->pb_pant_ajustes_generales_ECG->pos().x(),
                                                ui->pb_pant_ajustes_generales_ECG->pos().y()+ui->widget_ajustes_generales_Generales->size().height());
        ui->pb_pant_ajustes_generales_Oxymetria->move(ui->pb_pant_ajustes_generales_Oxymetria->pos().x(),
                                                      ui->pb_pant_ajustes_generales_Oxymetria->pos().y()+ui->widget_ajustes_generales_Generales->size().height());

        ui->widget_ajustes_generales_visualizacion->move(ui->widget_ajustes_generales_visualizacion->pos().x(),
                                                         ui->widget_ajustes_generales_visualizacion->pos().y()+ui->widget_ajustes_generales_Generales->size().height());
        ui->widget_ajustes_generales_ECG->move(ui->widget_ajustes_generales_ECG->pos().x(),
                                               ui->widget_ajustes_generales_ECG->pos().y()+ui->widget_ajustes_generales_Generales->size().height());
        ui->widget_ajustes_generales_Oximetria->move(ui->widget_ajustes_generales_Oximetria->pos().x(),
                                                     ui->widget_ajustes_generales_Oximetria->pos().y()+ui->widget_ajustes_generales_Generales->size().height());

        ui->l_pant_ajuste_barra_expansion_Generales->setFixedHeight(ui->l_pant_ajuste_barra_expansion_Generales->size().height()
                                                                    +ui->widget_ajustes_generales_Generales->size().height());
        ui->l_pant_ajuste_barra_expansion_Generales->move(ui->l_pant_ajuste_barra_expansion_Generales->pos().x(),
                                                          ui->pb_pant_ajustes_generales_Generales->pos().y()+30);

        ui->l_pant_ajuste_barra_expansion_Visualizacion->move(ui->l_pant_ajuste_barra_expansion_Visualizacion->pos().x(),
                                                              ui->l_pant_ajuste_barra_expansion_Visualizacion->pos().y()+ui->widget_ajustes_generales_Generales->size().height());

        ui->l_pant_ajuste_barra_expansion_ECG->move(ui->l_pant_ajuste_barra_expansion_ECG->pos().x(),
                                                    ui->l_pant_ajuste_barra_expansion_ECG->pos().y()+ui->widget_ajustes_generales_Generales->size().height());
    }
    else{

        ui->widget_pantalla_ajustes->setFixedHeight(ui->widget_pantalla_ajustes->size().height()-ui->widget_ajustes_generales_Generales->size().height());

        ui->widget_pantalla_ajustes->move(0,0);

        delta_y_constant_scrolling_ajustes += ui->widget_ajustes_generales_Generales->size().height();

        ui->statusBar->showMessage(QString::number(delta_y_constant_scrolling_ajustes));

        ui->widget_ajustes_generales_Generales->hide();

        ui->pb_pant_ajustes_generales_Visualizacion->move(ui->pb_pant_ajustes_generales_Visualizacion->pos().x(),
                                                          ui->pb_pant_ajustes_generales_Visualizacion->pos().y()-ui->widget_ajustes_generales_Generales->size().height());
        ui->pb_pant_ajustes_generales_ECG->move(ui->pb_pant_ajustes_generales_ECG->pos().x(),
                                                ui->pb_pant_ajustes_generales_ECG->pos().y()-ui->widget_ajustes_generales_Generales->size().height());
        ui->pb_pant_ajustes_generales_Oxymetria->move(ui->pb_pant_ajustes_generales_Oxymetria->pos().x(),
                                                      ui->pb_pant_ajustes_generales_Oxymetria->pos().y()-ui->widget_ajustes_generales_Generales->size().height());

        ui->widget_ajustes_generales_visualizacion->move(ui->widget_ajustes_generales_visualizacion->pos().x(),
                                                         ui->widget_ajustes_generales_visualizacion->pos().y()-ui->widget_ajustes_generales_Generales->size().height());
        ui->widget_ajustes_generales_ECG->move(ui->widget_ajustes_generales_ECG->pos().x(),
                                               ui->widget_ajustes_generales_ECG->pos().y()-ui->widget_ajustes_generales_Generales->size().height());
        ui->widget_ajustes_generales_Oximetria->move(ui->widget_ajustes_generales_Oximetria->pos().x(),
                                                     ui->widget_ajustes_generales_Oximetria->pos().y()-ui->widget_ajustes_generales_Generales->size().height());

        ui->l_pant_ajuste_barra_expansion_Generales->setFixedHeight(57);
        ui->l_pant_ajuste_barra_expansion_Generales->move(ui->l_pant_ajuste_barra_expansion_Generales->pos().x(),
                                                          ui->pb_pant_ajustes_generales_Generales->pos().y()+30);

        ui->l_pant_ajuste_barra_expansion_Visualizacion->move(ui->l_pant_ajuste_barra_expansion_Visualizacion->pos().x(),
                                                              ui->l_pant_ajuste_barra_expansion_Visualizacion->pos().y()-ui->widget_ajustes_generales_Generales->size().height());

        ui->l_pant_ajuste_barra_expansion_ECG->move(ui->l_pant_ajuste_barra_expansion_ECG->pos().x(),
                                                    ui->l_pant_ajuste_barra_expansion_ECG->pos().y()-ui->widget_ajustes_generales_Generales->size().height());


    }
}

void MainWindow::on_pb_pant_ajustes_Visualizacion()
{
    if(ui->widget_ajustes_generales_visualizacion->isHidden()){

        ui->widget_pantalla_ajustes->setFixedHeight(ui->widget_pantalla_ajustes->size().height()+ui->widget_ajustes_generales_visualizacion->size().height());

        delta_y_constant_scrolling_ajustes -= ui->widget_ajustes_generales_visualizacion->size().height();

        ui->statusBar->showMessage(QString::number(delta_y_constant_scrolling_ajustes));

        ui->widget_ajustes_generales_visualizacion->show();
        ui->widget_ajustes_generales_visualizacion->move(ui->pb_pant_ajustes_generales_Visualizacion->pos().x()+70,ui->pb_pant_ajustes_generales_Visualizacion->pos().y()+70);

        ui->pb_pant_ajustes_generales_ECG->move(ui->pb_pant_ajustes_generales_ECG->pos().x(),
                                                ui->pb_pant_ajustes_generales_ECG->pos().y()+ui->widget_ajustes_generales_visualizacion->size().height());
        ui->pb_pant_ajustes_generales_Oxymetria->move(ui->pb_pant_ajustes_generales_Oxymetria->pos().x(),
                                                      ui->pb_pant_ajustes_generales_Oxymetria->pos().y()+ui->widget_ajustes_generales_visualizacion->size().height());

        ui->widget_ajustes_generales_ECG->move(ui->widget_ajustes_generales_ECG->pos().x(),
                                               ui->widget_ajustes_generales_ECG->pos().y()+ui->widget_ajustes_generales_visualizacion->size().height());
        ui->widget_ajustes_generales_Oximetria->move(ui->widget_ajustes_generales_Oximetria->pos().x(),
                                                     ui->widget_ajustes_generales_Oximetria->pos().y()+ui->widget_ajustes_generales_visualizacion->size().height());

        ui->widget_pantalla_ajustes->move(ui->widget_pantalla_ajustes->pos().x(),-150);

        ui->l_pant_ajuste_barra_expansion_Visualizacion->setFixedHeight(ui->l_pant_ajuste_barra_expansion_Visualizacion->size().height()
                                                                        +ui->widget_ajustes_generales_visualizacion->size().height());
        ui->l_pant_ajuste_barra_expansion_Visualizacion->move(ui->l_pant_ajuste_barra_expansion_Visualizacion->pos().x(),
                                                              ui->pb_pant_ajustes_generales_Visualizacion->pos().y()+45);
        ui->l_pant_ajuste_barra_expansion_ECG->move(ui->l_pant_ajuste_barra_expansion_ECG->pos().x(),
                                                    ui->l_pant_ajuste_barra_expansion_ECG->pos().y()+ui->widget_ajustes_generales_visualizacion->size().height());
    }
    else{

        ui->widget_pantalla_ajustes->setFixedHeight(ui->widget_pantalla_ajustes->size().height()-ui->widget_ajustes_generales_visualizacion->size().height());

        ui->widget_pantalla_ajustes->move(0,0);

        delta_y_constant_scrolling_ajustes += ui->widget_ajustes_generales_visualizacion->size().height();

        ui->statusBar->showMessage(QString::number(delta_y_constant_scrolling_ajustes));

        ui->widget_ajustes_generales_visualizacion->hide();

        ui->pb_pant_ajustes_generales_ECG->move(ui->pb_pant_ajustes_generales_ECG->pos().x(),
                                                ui->pb_pant_ajustes_generales_ECG->pos().y()-ui->widget_ajustes_generales_visualizacion->size().height());
        ui->pb_pant_ajustes_generales_Oxymetria->move(ui->pb_pant_ajustes_generales_Oxymetria->pos().x(),
                                                      ui->pb_pant_ajustes_generales_Oxymetria->pos().y()-ui->widget_ajustes_generales_visualizacion->size().height());

        ui->widget_ajustes_generales_ECG->move(ui->widget_ajustes_generales_ECG->pos().x(),
                                               ui->widget_ajustes_generales_ECG->pos().y()-ui->widget_ajustes_generales_visualizacion->size().height());
        ui->widget_ajustes_generales_Oximetria->move(ui->widget_ajustes_generales_Oximetria->pos().x(),
                                                     ui->widget_ajustes_generales_Oximetria->pos().y()-ui->widget_ajustes_generales_visualizacion->size().height());

        ui->l_pant_ajuste_barra_expansion_Visualizacion->setFixedHeight(64);
        ui->l_pant_ajuste_barra_expansion_Visualizacion->move(ui->l_pant_ajuste_barra_expansion_Visualizacion->pos().x(),
                                                              ui->pb_pant_ajustes_generales_Visualizacion->pos().y()+45);

        ui->l_pant_ajuste_barra_expansion_ECG->move(ui->l_pant_ajuste_barra_expansion_ECG->pos().x(),
                                                    ui->l_pant_ajuste_barra_expansion_ECG->pos().y()-ui->widget_ajustes_generales_visualizacion->size().height());

    }
}

void MainWindow::on_pb_pant_ajustes_ECG()
{
    if(ui->widget_ajustes_generales_ECG->isHidden()){

        ui->widget_pantalla_ajustes->setFixedHeight(ui->widget_pantalla_ajustes->size().height()+ui->widget_ajustes_generales_ECG->size().height());

        delta_y_constant_scrolling_ajustes -= ui->widget_ajustes_generales_ECG->size().height();

        ui->statusBar->showMessage(QString::number(delta_y_constant_scrolling_ajustes));

        ui->widget_ajustes_generales_ECG->show();
        ui->widget_ajustes_generales_ECG->move(ui->pb_pant_ajustes_generales_ECG->pos().x()+70,ui->pb_pant_ajustes_generales_ECG->pos().y()+60);

        ui->pb_pant_ajustes_generales_Oxymetria->move(ui->pb_pant_ajustes_generales_Oxymetria->pos().x(),
                                                      ui->pb_pant_ajustes_generales_Oxymetria->pos().y()+ui->widget_ajustes_generales_ECG->size().height());

        ui->widget_ajustes_generales_Oximetria->move(ui->widget_ajustes_generales_Oximetria->pos().x(),
                                                     ui->widget_ajustes_generales_Oximetria->pos().y()+ui->widget_ajustes_generales_ECG->size().height());

        ui->widget_pantalla_ajustes->move(ui->widget_pantalla_ajustes->pos().x(),-250);

        ui->l_pant_ajuste_barra_expansion_ECG->setFixedHeight(ui->l_pant_ajuste_barra_expansion_ECG->size().height()
                                                              +ui->widget_ajustes_generales_ECG->size().height());
        ui->l_pant_ajuste_barra_expansion_ECG->move(ui->l_pant_ajuste_barra_expansion_ECG->pos().x(),
                                                    ui->pb_pant_ajustes_generales_ECG->pos().y()+46);

    }
    else{

        ui->widget_pantalla_ajustes->setFixedHeight(ui->widget_pantalla_ajustes->size().height()-ui->widget_ajustes_generales_ECG->size().height());

        ui->widget_pantalla_ajustes->move(0,0);

        delta_y_constant_scrolling_ajustes += ui->widget_ajustes_generales_ECG->size().height();

        ui->statusBar->showMessage(QString::number(delta_y_constant_scrolling_ajustes));

        ui->widget_ajustes_generales_ECG->hide();

        ui->pb_pant_ajustes_generales_Oxymetria->move(ui->pb_pant_ajustes_generales_Oxymetria->pos().x(),
                                                      ui->pb_pant_ajustes_generales_Oxymetria->pos().y()-ui->widget_ajustes_generales_ECG->size().height());

        ui->widget_ajustes_generales_Oximetria->move(ui->widget_ajustes_generales_Oximetria->pos().x(),
                                                     ui->widget_ajustes_generales_Oximetria->pos().y()-ui->widget_ajustes_generales_ECG->size().height());

        ui->l_pant_ajuste_barra_expansion_ECG->setFixedHeight(59);
        ui->l_pant_ajuste_barra_expansion_ECG->move(ui->l_pant_ajuste_barra_expansion_ECG->pos().x(),
                                                    ui->pb_pant_ajustes_generales_ECG->pos().y()+46);

    }
}

void MainWindow::on_pb_pant_ajustes_Oxymetria()
{
    if(ui->widget_ajustes_generales_Oximetria->isHidden()){

        ui->widget_pantalla_ajustes->setFixedHeight(ui->widget_pantalla_ajustes->size().height()+ui->widget_ajustes_generales_Oximetria->size().height());

        delta_y_constant_scrolling_ajustes -= ui->widget_ajustes_generales_Oximetria->size().height();

        ui->statusBar->showMessage(QString::number(delta_y_constant_scrolling_ajustes));

        ui->widget_ajustes_generales_Oximetria->show();
        ui->widget_ajustes_generales_Oximetria->move(ui->pb_pant_ajustes_generales_Oxymetria->pos().x()+70,ui->pb_pant_ajustes_generales_Oxymetria->pos().y()+60);

        ui->widget_pantalla_ajustes->move(ui->widget_pantalla_ajustes->pos().x(),-210);
    }
    else{

        ui->widget_pantalla_ajustes->setFixedHeight(ui->widget_pantalla_ajustes->size().height()-ui->widget_ajustes_generales_Oximetria->size().height());

        ui->widget_pantalla_ajustes->move(0,0);

        delta_y_constant_scrolling_ajustes += ui->widget_ajustes_generales_Oximetria->size().height();

        ui->statusBar->showMessage(QString::number(delta_y_constant_scrolling_ajustes));

        ui->widget_ajustes_generales_Oximetria->hide();
    }
}

void MainWindow::on_pb_widget_colores_aceptar_ECG_Curva()
{
    ui->statusBar->showMessage("aceptar");
    //customPlot_graph_EKG->graph(0)->setPen(QPen(ui->pb_widget_ajustes_generales_color_EKG_curva->palette().color(QPalette::Background)));  //azul claro

    ui->widget_pantalla_ajustes_widget_colores->hide();
    customPlot_graph_EKG->graph(0)->setPen(QPen(ui->l_widget_colores_color_seleccionado->palette().color(QPalette::Background)));
    ui->pb_widget_ajustes_generales_color_EKG_curva->setStyleSheet(ui->l_widget_colores_color_seleccionado->styleSheet());
}

void MainWindow::on_pb_widget_colores_aceptar_ECG_fondo()
{
    ui->statusBar->showMessage("aceptar");
    //customPlot_graph_EKG->graph(0)->setPen(QPen(ui->pb_widget_ajustes_generales_color_EKG_curva->palette().color(QPalette::Background)));  //azul claro

    ui->widget_pantalla_ajustes_widget_colores->hide();
    customPlot_graph_EKG->setBackground(QBrush(ui->l_widget_colores_color_seleccionado->palette().color(QPalette::Background)));
    ui->pb_widget_ajustes_generales_color_EKG_fondo->setStyleSheet(ui->l_widget_colores_color_seleccionado->styleSheet());
}

void MainWindow::on_pb_widget_colores_aceptar_Oxy1_Curva()
{
    ui->statusBar->showMessage("aceptar");
    //customPlot_graph_EKG->graph(0)->setPen(QPen(ui->pb_widget_ajustes_generales_color_EKG_curva->palette().color(QPalette::Background)));  //azul claro

    ui->widget_pantalla_ajustes_widget_colores->hide();
    customPlot_graph_Oxy1->graph(0)->setPen(QPen(ui->l_widget_colores_color_seleccionado->palette().color(QPalette::Background)));
    ui->pb_widget_ajustes_generales_color_Oxy1_curva->setStyleSheet(ui->l_widget_colores_color_seleccionado->styleSheet());
}

void MainWindow::on_pb_widget_colores_aceptar_Oxy1_fondo()
{
    ui->statusBar->showMessage("aceptar");
    //customPlot_graph_EKG->graph(0)->setPen(QPen(ui->pb_widget_ajustes_generales_color_EKG_curva->palette().color(QPalette::Background)));  //azul claro

    ui->widget_pantalla_ajustes_widget_colores->hide();
    customPlot_graph_Oxy1->setBackground(QBrush(ui->l_widget_colores_color_seleccionado->palette().color(QPalette::Background)));
    ui->pb_widget_ajustes_generales_color_Oxy1_fondo->setStyleSheet(ui->l_widget_colores_color_seleccionado->styleSheet());
}

void MainWindow::on_pb_widget_colores_aceptar_Oxy2_Curva()
{
    ui->statusBar->showMessage("aceptar");
    //customPlot_graph_EKG->graph(0)->setPen(QPen(ui->pb_widget_ajustes_generales_color_EKG_curva->palette().color(QPalette::Background)));  //azul claro

    ui->widget_pantalla_ajustes_widget_colores->hide();
    customPlot_graph_Oxy2->graph(0)->setPen(QPen(ui->l_widget_colores_color_seleccionado->palette().color(QPalette::Background)));
    ui->pb_widget_ajustes_generales_color_Oxy2_curva->setStyleSheet(ui->l_widget_colores_color_seleccionado->styleSheet());
}

void MainWindow::on_pb_widget_colores_aceptar_Oxy2_fondo()
{
    ui->statusBar->showMessage("aceptar");
    //customPlot_graph_EKG->graph(0)->setPen(QPen(ui->pb_widget_ajustes_generales_color_EKG_curva->palette().color(QPalette::Background)));  //azul claro

    ui->widget_pantalla_ajustes_widget_colores->hide();
    customPlot_graph_Oxy2->setBackground(QBrush(ui->l_widget_colores_color_seleccionado->palette().color(QPalette::Background)));
    ui->pb_widget_ajustes_generales_color_Oxy2_fondo->setStyleSheet(ui->l_widget_colores_color_seleccionado->styleSheet());
}

void MainWindow::on_pb_widget_colores_cancelar()
{
    ui->statusBar->showMessage("cancelar");

    ui->widget_pantalla_ajustes_widget_colores->hide();
}

void MainWindow::on_pb_widget_colores_amarillo()
{
    ui->statusBar->showMessage("amarillo");

    ui->l_widget_colores_color_seleccionado->setStyleSheet(ui->pb_widget_colores_amarillo->styleSheet());
}

void MainWindow::on_pb_widget_colores_azul()
{
    ui->statusBar->showMessage("azul");

    ui->l_widget_colores_color_seleccionado->setStyleSheet(ui->pb_widget_colores_azul->styleSheet());
}

void MainWindow::on_pb_widget_colores_naranja()
{
    ui->statusBar->showMessage("naranja");

    ui->l_widget_colores_color_seleccionado->setStyleSheet(ui->pb_widget_colores_naranja->styleSheet());
}

void MainWindow::on_pb_widget_colores_verde()
{
    ui->statusBar->showMessage("verde");

    ui->l_widget_colores_color_seleccionado->setStyleSheet(ui->pb_widget_colores_verde->styleSheet());
}

void MainWindow::on_pb_widget_colores_rojo()
{
    ui->statusBar->showMessage("rojo");

    ui->l_widget_colores_color_seleccionado->setStyleSheet(ui->pb_widget_colores_rojo->styleSheet());
}

void MainWindow::on_pb_widget_ajustes_generales_color_ECG_Curva()
{
    ui->statusBar->showMessage("Color");

    ui->widget_pantalla_ajustes_widget_colores->show();
    ui->widget_pantalla_ajustes_widget_colores->move(600,360);
    ui->pb_widget_colores_aceptar_ECG_Curva->raise();
}

void MainWindow::on_pb_widget_ajustes_generales_color_ECG_fondo()
{
    ui->statusBar->showMessage("Color");

    ui->widget_pantalla_ajustes_widget_colores->show();
    ui->widget_pantalla_ajustes_widget_colores->move(600,360);
    ui->pb_widget_colores_aceptar_ECG_fondo->raise();
}

void MainWindow::on_pb_widget_ajustes_generales_color_Oxy1_Curva()
{
    ui->statusBar->showMessage("Color");

    ui->widget_pantalla_ajustes_widget_colores->show();
    ui->widget_pantalla_ajustes_widget_colores->move(600,360);
    ui->pb_widget_colores_aceptar_Oxy1_Curva->raise();
}
void MainWindow::on_pb_widget_ajustes_generales_color_Oxy1_fondo()
{
    ui->statusBar->showMessage("Color");

    ui->widget_pantalla_ajustes_widget_colores->show();
    ui->widget_pantalla_ajustes_widget_colores->move(600,360);
    ui->pb_widget_colores_aceptar_Oxy1_fondo->raise();
}
void MainWindow::on_pb_widget_ajustes_generales_color_Oxy2_Curva()
{
    ui->statusBar->showMessage("Color");

    ui->widget_pantalla_ajustes_widget_colores->show();
    ui->widget_pantalla_ajustes_widget_colores->move(600,360);
    ui-> pb_widget_colores_aceptar_Oxy2_Curva->raise();
}
void MainWindow::on_pb_widget_ajustes_generales_color_Oxy2_fondo()
{
    ui->statusBar->showMessage("Color");

    ui->widget_pantalla_ajustes_widget_colores->show();
    ui->widget_pantalla_ajustes_widget_colores->move(600,360);
    ui-> pb_widget_colores_aceptar_Oxy2_fondo->raise();
}

uint32_t MainWindow::crc32(const void *buf, size_t size)
{
    const uint8_t *p = (uint8_t *)buf;
    uint32_t crc;

    crc = ~0U;
    while (size--)
        crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);
    return crc ^ ~0U;
}

void MainWindow::check_message(qint64 bytes_size)
{
    if(last_bad_receive_pos >= UART_SEND_TOTAL_SIZE){

        uint8_t buf_8b[4];
        uint32_t crcValue = crc32(receive_bytes, UART_SEND_BUFFER_SIZE);

        for (int i=0; i<4 ;++i){
            buf_8b[i] = ((uint8_t*)&crcValue)[3-i];
        }

        valid_receive_data = true;

        for (int i=0; i<4 ;++i){
            if(receive_bytes[i+UART_SEND_BUFFER_SIZE] != buf_8b[i]){
                valid_receive_data = false;//Error de datos solicitar reenvio

                QObject::disconnect(ftdi_serial_port,SIGNAL(readyRead()),this,SLOT(readSerial()));
                ftdi_serial_port->close();

                QByteArray write_data;

                for (int i = 0; i<UART_READ_BUFFER_SIZE;++i){

                    write_data.append(ERROR_ID);
                }

                ftdi_serial_port->open(QSerialPort::ReadWrite);
                last_bad_receive_pos=0;
                errores++;
                QObject::connect(ftdi_serial_port,SIGNAL(readyRead()),this,SLOT(readSerial()));

                ftdi_serial_port->write(write_data);

                ui->statusBar->showMessage(QString::number(errores));
                return;//Error de check_sum solicitar reenvio
            }
        }

        for(int i=HEADER_START_POS; i < HEADER_SIZE; i++){
            if(receive_bytes[i] != HEADER_ID){
                valid_receive_data = false;//Error de datos solicitar reenvio

                QObject::disconnect(ftdi_serial_port,SIGNAL(readyRead()),this,SLOT(readSerial()));
                ftdi_serial_port->close();

                QByteArray write_data;

                for (int i = 0; i<UART_READ_BUFFER_SIZE;++i){

                    write_data.append(ERROR_ID);
                }

                ftdi_serial_port->open(QSerialPort::ReadWrite);
                last_bad_receive_pos=0;
                errores++;
                QObject::connect(ftdi_serial_port,SIGNAL(readyRead()),this,SLOT(readSerial()));


                ui->statusBar->showMessage(QString::number(errores));
                ftdi_serial_port->write(write_data);
                return;//Error de cabecera solicitar reenvio
            }
        }
    }
}


void MainWindow::setupGraph_Oxy1(){   //OXYmetro 1

    customPlot_graph_Oxy1->setup_Graph();

    customPlot_graph_Oxy1->graph(0)->setName("Oxy1");
    customPlot_graph_Oxy1->graph(0)->setPen(QPen(QColor(0, 200, 255)));  //azul

    customPlot_graph_Oxy1->graph(1)->setName("Oxy1 defasado");
    customPlot_graph_Oxy1->graph(1)->setPen(QPen(QColor(255, 200, 255)));  //violeta

    customPlot_graph_Oxy1->set_Range_x_axis_initial(0,500);
    customPlot_graph_Oxy1->set_Range_y_axis_initial(0,100);

    customPlot_graph_Oxy1->set_Size(QSize(728, 124));
    customPlot_graph_Oxy1->set_position(QPoint(205,618));

    customPlot_graph_Oxy1->set_maximize_Size(QSize(1090, 300));
    customPlot_graph_Oxy1->set_maximize_position(QPoint(100,100));
    customPlot_graph_Oxy1->set_Maximized_position_whit_other_maximize(QPoint(100,450));

    customPlot_graph_Oxy1->set_IsEKG_Graph(false);

    customPlot_graph_Oxy1->set_Background_blur((QWidget*)ui->pb_pant_gris_blur_plus);

    customPlot_graph_Oxy1->set_button_maximize(ui->pb_pant_test_maximize_oxy1);

    customPlot_graph_Oxy1->set_graph_number(0);

    customPlot_graph_Oxy1->set_other_graph1(customPlot_graph_Oxy2);
    customPlot_graph_Oxy1->set_other_graph2(customPlot_graph_EKG);

    //customPlot_graph_Oxy1->set_Interactions_in_graph(false);

    customPlot_graph_Oxy1->replot();

}



void MainWindow::setupGraph_Oxy2()
{

    customPlot_graph_Oxy2->setup_Graph();

    customPlot_graph_Oxy2->graph(0)->setName("Oxy1");
    customPlot_graph_Oxy2->graph(0)->setPen(QPen(QColor(0, 200, 255)));  //azul

    customPlot_graph_Oxy2->graph(1)->setName("Oxy1 defasado");
    customPlot_graph_Oxy2->graph(1)->setPen(QPen(QColor(255, 200, 255)));  //violeta

    customPlot_graph_Oxy2->set_Range_x_axis_initial(0,500);
    customPlot_graph_Oxy2->set_Range_y_axis_initial(0,100);

    customPlot_graph_Oxy2->set_Size(QSize(728, 124));
    customPlot_graph_Oxy2->set_position(QPoint(205,758));

    customPlot_graph_Oxy2->set_maximize_Size(QSize(1090, 300));
    customPlot_graph_Oxy2->set_maximize_position(QPoint(100,100));
    customPlot_graph_Oxy2->set_Maximized_position_whit_other_maximize(QPoint(100,450));

    customPlot_graph_Oxy2->set_IsEKG_Graph(false);

    customPlot_graph_Oxy2->set_Background_blur((QWidget*)ui->pb_pant_gris_blur_plus);

    customPlot_graph_Oxy2->set_button_maximize(ui->pb_pant_test_maximize_oxy2);

    customPlot_graph_Oxy2->set_graph_number(1);

    //customPlot_graph_Oxy2->set_Interactions_in_graph(false);

    customPlot_graph_Oxy2->set_other_graph1(customPlot_graph_Oxy1);
    customPlot_graph_Oxy2->set_other_graph2(customPlot_graph_EKG);

    customPlot_graph_Oxy2->replot();


}

void MainWindow::setupGraph_EKG()
{

    customPlot_graph_EKG->setup_Graph();

    customPlot_graph_EKG->graph(0)->setName("Ekg filtered");
    customPlot_graph_EKG->graph(0)->setPen(QPen(QColor(0, 255, 0)));  //azul

    customPlot_graph_EKG->graph(1)->setName("Ekg unfiltered");
    customPlot_graph_EKG->graph(1)->setPen(QPen(QColor(0, 255, 255)));  //violeta

    customPlot_graph_EKG->set_Range_x_axis_initial(0,2000);
    customPlot_graph_EKG->set_Range_y_axis_initial(0,4096);

    customPlot_graph_EKG->set_Size(QSize(728, 124));
    customPlot_graph_EKG->set_position(QPoint(205,479));

    customPlot_graph_EKG->set_maximize_Size(QSize(1090, 300));
    customPlot_graph_EKG->set_maximize_position(QPoint(100,100));
    customPlot_graph_EKG->set_Maximized_position_whit_other_maximize(QPoint(100,450));

    //customPlot_graph_EKG->setBackground(QBrush(QColor(100,100,100)));

    customPlot_graph_EKG->set_Background_blur((QWidget*)ui->pb_pant_gris_blur_plus);

    customPlot_graph_EKG->set_button_maximize(ui->pb_pant_test_maximize_ecg);

    customPlot_graph_EKG->set_IsEKG_Graph(true);

    customPlot_graph_EKG->set_graph_number(2);

    //customPlot_graph_EKG->set_Interactions_in_graph(false);

    customPlot_graph_EKG->set_other_graph1(customPlot_graph_Oxy1);
    customPlot_graph_EKG->set_other_graph2(customPlot_graph_Oxy2);

    customPlot_graph_EKG->replot();

}


void MainWindow::on_Oxy1_mousePress(QMouseEvent *event)
{

    int x = customPlot_graph_Oxy1->xAxis->pixelToCoord(event->pos().x());
    int y = customPlot_graph_Oxy1->yAxis->pixelToCoord(event->pos().y());

    customPlot_graph_Oxy1->setToolTip(QString("%1 , %2").arg(x).arg(y));

}

void MainWindow::on_Oxy2_mousePress(QMouseEvent *event)
{

    int x = customPlot_graph_Oxy2->xAxis->pixelToCoord(event->pos().x());
    int y = customPlot_graph_Oxy2->yAxis->pixelToCoord(event->pos().y());

    customPlot_graph_Oxy2->setToolTip(QString("%1 , %2").arg(x).arg(y));

}

void MainWindow::on_EKG_mousePress(QMouseEvent *event)
{

    int x = customPlot_graph_EKG->xAxis->pixelToCoord(event->pos().x());
    int y = customPlot_graph_EKG->yAxis->pixelToCoord(event->pos().y());

    customPlot_graph_EKG->setToolTip(QString("%1 , %2").arg(x).arg(y));

    emit customPlot_graph_Oxy1->mousePress(event);
    emit customPlot_graph_Oxy2->mousePress(event);
}

void MainWindow::on_Oxy1_mouseReleased(QMouseEvent *event)
{

    int x = customPlot_graph_Oxy1->xAxis->pixelToCoord(event->pos().x());
    int y = customPlot_graph_Oxy1->yAxis->pixelToCoord(event->pos().y());

    customPlot_graph_Oxy1->setToolTip(QString("%1 , %2").arg(x).arg(y));

}

void MainWindow::on_Oxy2_mouseReleased(QMouseEvent *event)
{

    int x = customPlot_graph_Oxy2->xAxis->pixelToCoord(event->pos().x());
    int y = customPlot_graph_Oxy2->yAxis->pixelToCoord(event->pos().y());

    customPlot_graph_Oxy2->setToolTip(QString("%1 , %2").arg(x).arg(y));

}

void MainWindow::on_EKG_mouseReleased(QMouseEvent *event)
{

    int x = customPlot_graph_EKG->xAxis->pixelToCoord(event->pos().x());
    int y = customPlot_graph_EKG->yAxis->pixelToCoord(event->pos().y());

    customPlot_graph_EKG->setToolTip(QString("%1 , %2").arg(x).arg(y));

    emit customPlot_graph_Oxy1->mouseRelease(event);
    emit customPlot_graph_Oxy2->mouseRelease(event);

}

void MainWindow::on_Oxy1_mouseWheel(QWheelEvent *event)
{

    int x = customPlot_graph_Oxy1->xAxis->pixelToCoord(event->pos().x());
    int y = customPlot_graph_Oxy1->yAxis->pixelToCoord(event->pos().y());

    customPlot_graph_Oxy1->setToolTip(QString("%1 , %2").arg(x).arg(y));

}

void MainWindow::on_Oxy2_mouseWheel(QWheelEvent *event)
{

    int x = customPlot_graph_Oxy2->xAxis->pixelToCoord(event->pos().x());
    int y = customPlot_graph_Oxy2->yAxis->pixelToCoord(event->pos().y());

    customPlot_graph_Oxy2->setToolTip(QString("%1 , %2").arg(x).arg(y));

}

void MainWindow::on_EKG_mouseWheel(QWheelEvent *event)
{

    int x = customPlot_graph_EKG->xAxis->pixelToCoord(event->pos().x());
    int y = customPlot_graph_EKG->yAxis->pixelToCoord(event->pos().y());

    customPlot_graph_EKG->setToolTip(QString("%1 , %2").arg(x).arg(y));

    emit customPlot_graph_Oxy1->mouseWheel(event);
    emit customPlot_graph_Oxy2->mouseWheel(event);
}

void MainWindow::show_widget_paciente_datos(){

    ui->widget_paciente_datos->show();
    ui->widget_paciente_datos->move(this->pos().x()+300,this->pos().y()+40);
}

void MainWindow::show_pantalla_paciente(){

    hide_all();

    QObject::connect(&start_moving_screen,SIGNAL(timeout()),this,SLOT(on_start_moving_screen_timeout()));
    QObject::disconnect(&start_moving_screen,SIGNAL(timeout()),this,SLOT(on_start_scrolling_screen_test_timeout()));

    this->setFixedSize(1280,800);
    ui->widget_pantalla_paciente->show();
    ui->widget_pantalla_paciente->move(0,0);
}
void MainWindow::show_pantalla_test(){

    hide_all();
    this->setFixedSize(1280,800);

    delta_y_constant_scrolling_test = -242;

    QObject::disconnect(&start_moving_screen,SIGNAL(timeout()),this,SLOT(on_start_scrolling_screen_ajustes_timeout()));
    QObject::disconnect(&start_moving_screen,SIGNAL(timeout()),this,SLOT(on_start_moving_screen_timeout()));
    QObject::connect(&start_moving_screen,SIGNAL(timeout()),this,SLOT(on_start_scrolling_screen_test_timeout()));

    ui->widget_pantalla_test->show();
    ui->widget_pantalla_test->move(0,0);
}

void MainWindow::on_start_scrolling_screen_test_timeout(){

    int y_pos = (int)ui->widget_pantalla_test->pos().y()+((QWidget::mapFromGlobal(QCursor::pos())).y() - init_pos_y);
    y_pos = (y_pos > 0)?0:y_pos;  ///limites para pantalla de ajustes
    y_pos = (y_pos < delta_y_constant_scrolling_test)?delta_y_constant_scrolling_test:y_pos;  ///si haces sroll en otras pantallas modificar esto

    ui->widget_pantalla_test->move(ui->widget_pantalla_test->pos().x(),y_pos);

    init_pos_y = (QWidget::mapFromGlobal(QCursor::pos())).y();
}

void MainWindow::show_pantalla_base_de_datos(){

    hide_all();
    this->setFixedSize(1280,800);
    ui->widget_pant_base_de_Datos->show();
    ui->widget_pant_base_de_Datos->move(0,0);
}

void MainWindow::show_pantalla_ajustes(){

    hide_all();
    this->setFixedSize(1280,800);

    QObject::disconnect(&start_moving_screen,SIGNAL(timeout()),this,SLOT(on_start_moving_screen_timeout()));
    QObject::disconnect(&start_moving_screen,SIGNAL(timeout()),this,SLOT(on_start_scrolling_screen_test_timeout()));
    QObject::connect(&start_moving_screen,SIGNAL(timeout()),this,SLOT(on_start_scrolling_screen_ajustes_timeout()));

    ui->widget_pantalla_ajustes->show();
    ui->widget_pantalla_ajustes->move(0,0);
    ui->widget_pantalla_ajustes->setFixedSize(1280,800);
    delta_y_constant_scrolling_ajustes =0;

    ui->pb_pant_ajustes_generales_Generales->move(210,460);
    ui->pb_pant_ajustes_generales_Visualizacion->move(211,515);
    ui->pb_pant_ajustes_generales_ECG->move(210,594);
    ui->pb_pant_ajustes_generales_Oxymetria->move(210,669);

    ui->widget_ajustes_generales_Generales->hide();
    ui->widget_ajustes_generales_visualizacion->hide();
    ui->widget_ajustes_generales_ECG->hide();
    ui->widget_ajustes_generales_Oximetria->hide();

    ui->l_pant_ajuste_barra_expansion_Generales->setFixedHeight(57);
    ui->l_pant_ajuste_barra_expansion_Generales->move(ui->l_pant_ajuste_barra_expansion_Generales->pos().x(),
                                                      ui->pb_pant_ajustes_generales_Generales->pos().y()+30);

    ui->l_pant_ajuste_barra_expansion_Visualizacion->setFixedHeight(64);
    ui->l_pant_ajuste_barra_expansion_Visualizacion->move(ui->l_pant_ajuste_barra_expansion_Visualizacion->pos().x(),
                                                          ui->pb_pant_ajustes_generales_Visualizacion->pos().y()+45);

    ui->l_pant_ajuste_barra_expansion_ECG->setFixedHeight(59);
    ui->l_pant_ajuste_barra_expansion_ECG->move(ui->l_pant_ajuste_barra_expansion_ECG->pos().x(),
                                                ui->pb_pant_ajustes_generales_ECG->pos().y()+46);

    ui->pb_widget_ajustes_generales_caneles_0->hide();
    ui->pb_widget_ajustes_generales_caneles_1->hide();
    ui->pb_widget_ajustes_generales_caneles_2->hide();
}


void MainWindow::hide_all(){

    connect(&start_moving_screen,SIGNAL(timeout()),this,SLOT(on_start_moving_screen_timeout()));
    ui->widget_pantalla_paciente->hide();
    //ui->widget_scrollArea_test->hide();
    ui->widget_pantalla_test->hide();
    ui->widget_pant_base_de_Datos->hide();
    ui->widget_borrar_paciente->hide();
    ui->widget_paciente_datos->hide();
    ui->widget_proseguir_test_paciente->hide();
    ui->widget_menu->hide();
    ui->widget_pantalla_ajustes->hide();
    ui->widget_pantalla_ajustes_widget_colores->hide();
}

void MainWindow::on_pb_widget_paciente_datos_Nuevo_Test()
{
    ui->pb_pant_test_Graficar_Iniciar->setText("GRAFICAR");
    ui->pb_pant_test_Ver_Registro_Guardar->setText("GUARDAR");

    update_data_pacient_in_labels(false);

    show_pantalla_test();
}

void MainWindow::on_pb_pant_ajustes_atras()
{
    show_pantalla_test();
}


void MainWindow::on_pb_widget_paciente_datos_Ver_Registro()
{
    ui->pb_pant_test_Graficar_Iniciar->setText("RESULTADOS");
    ui->pb_pant_test_Ver_Registro_Guardar->setText("VER REGISTRO");

    update_data_pacient_in_labels(false);

    QObject::disconnect(ftdi_serial_port,SIGNAL(readyRead()),this,SLOT(readSerial()));

    timer_graph.stop();
    show_pantalla_test();
}

void MainWindow::on_lw_pant_base_de_datos_pacientes_itemPressed(QListWidgetItem *item)
{
    QFile *data_base = new QFile(data_base_name); // ficheros .dat se puede utilizar formato txt tambien

    if(data_base->open(QIODevice::ReadOnly))
    {
        QDataStream in(data_base);

        while(!data_base->atEnd()){

            bebe_object->read_file_with_size_data_only_pacient_info_fix_strings(in);

            data_base->seek(bebe_object->posicion_en_archivo + bebe_object->size_of_pacient_data);

            if(item->text().left(15).contains(QString::number(bebe_object->ID)) && item->text().contains(bebe_object->mother_name)){

                data_base->seek(bebe_object->posicion_en_archivo);
                bebe_object->read_file_with_size_data_fix_strings(in);

                ui->l_paciente_datos_nombre->setText(bebe_object->mother_name);
                ui->l_paciente_datos_ID->setText(QString::number(bebe_object->ID));
                ui->l_paciente_datos_sexo->setText(bebe_object->sexo);
                ui->l_paciente_datos_fecha_nacimiento->setText(bebe_object->birth_date.toString("dd/MM/yyyy"));
                ui->l_paciente_datos_pruebas->setText(QString::number(bebe_object->cantidad_de_pruebas));
                ui->l_paciente_datos_estado->setText(bebe_object->state);

                break;
            }
        }

        data_base->close();
    }
    else{
        QMessageBox::information(this,"Informacion","No se ha podido cargar la base de datos   ",QMessageBox::Ok);
    }

    show_widget_paciente_datos();
}

bool MainWindow::cargar_base_de_datos(QString database_name)
{
    ui->lw_pant_base_de_datos_pacientes->clear();
    QFile *data_base = new QFile(database_name); // ficheros .dat se puede utilizar formato txt tambien
    lista_de_pacientes.clear();
    QString paciente;
    qDebug()<<"Cargando: "<<database_name;
    if(data_base->open(QIODevice::ReadOnly))
    {
        QDataStream in(data_base);

        while(!data_base->atEnd()){

            bebe_object->read_file_with_size_data_only_pacient_info_fix_strings(in);

            data_base->seek(bebe_object->posicion_en_archivo + bebe_object->size_of_pacient_data);

            paciente = ordenar_para_lista_de_paciente(*bebe_object);
            lista_de_pacientes.append(paciente);
        }

        ui->lw_pant_base_de_datos_pacientes->addItems(lista_de_pacientes);

        data_base->close();
        return true;
    }
    else{
        QMessageBox::information(this,"Informacion","No se ha podido cargar la base de datos   ",QMessageBox::Ok);
        return false;
    }
}

QString MainWindow::ordenar_para_lista_de_paciente(Bebe_Data_Class &bebe_object_copia)
{

    QString order_string="";

    for(int i=0; i<250;i++){
        order_string.append(" ");
    }
    quint8 pos_ID=0, pos_nombre = 30, pos_sexo = 90, pos_fecha_nac = 115, pos_pruebas=170, pos_estado=190;

    order_string.replace(pos_ID, QString::number(bebe_object_copia.ID).length() ,QString::number(bebe_object_copia.ID));
    order_string.replace(pos_nombre, bebe_object_copia.mother_name.length(), bebe_object_copia.mother_name);
    order_string.replace(pos_sexo, 1,bebe_object_copia.sexo.at(0));
    order_string.replace(pos_fecha_nac, bebe_object_copia.birth_date.toString("dd/MM/yyyy").length(), bebe_object_copia.birth_date.toString("dd/MM/yyyy"));
    order_string.replace(pos_pruebas,QString::number(bebe_object_copia.cantidad_de_pruebas).length(), QString::number(bebe_object_copia.cantidad_de_pruebas));
    order_string.replace(pos_estado, bebe_object_copia.state.length(),bebe_object_copia.state);

    return order_string;
}

void MainWindow::update_data_pacient_in_labels(bool desde_pantalla_principal)
{
    if(desde_pantalla_principal){

        ui->l_test_nombre->setText(ui->le_pant_paciente_Nombre->text());
        ui->l_test_ID->setText(ui->le_pant_paciente_ID->text());
        ui->l_test_sexo->setText(sexo_de_paciente);
        ui->l_test_fecha_nacimiento->setText(ui->pb_pant_paciente_fecha_nacimiento->text());

        ui->l_pantalla_ajustes_nombre->setText(ui->le_pant_paciente_Nombre->text());
        ui->l_pantalla_ajustes_ID->setText(ui->le_pant_paciente_ID->text());
        ui->l_pantalla_ajustes_sexo->setText(sexo_de_paciente);
        ui->l_pantalla_ajustes_fecha_nacimiento->setText(ui->pb_pant_paciente_fecha_nacimiento->text());

    }
    else{  ////desde base de datos

        ui->l_test_nombre->setText(ui->l_paciente_datos_nombre->text());
        ui->l_test_ID->setText(ui->l_paciente_datos_ID->text());
        ui->l_test_sexo->setText(ui->l_paciente_datos_sexo->text());
        ui->l_test_fecha_nacimiento->setText(ui->l_paciente_datos_fecha_nacimiento->text());

        ui->l_pantalla_ajustes_nombre->setText(ui->l_paciente_datos_nombre->text());
        ui->l_pantalla_ajustes_ID->setText(ui->l_paciente_datos_ID->text());
        ui->l_pantalla_ajustes_sexo->setText(ui->l_paciente_datos_sexo->text());
        ui->l_pantalla_ajustes_fecha_nacimiento->setText(ui->l_paciente_datos_fecha_nacimiento->text());
    }
}


void MainWindow::update_fecha_y_hora()
{
    if(timer_graph.isActive()){

        tiempo_de_Prueba = tiempo_de_Prueba.addSecs(1);
        ui->l_pant_test_tiempo_de_prueba->setText(tiempo_de_Prueba.toString("h:mm:ss"));
    }

    ui->pb_pant_test_fecha->setText(QDate::currentDate().toString("dd/MM/yyyy"));
    ui->pb_pant_paciente_fecha_actual->setText(ui->pb_pant_test_fecha->text());
    ui->pb_pant_base_de_datos_fecha->setText(ui->pb_pant_test_fecha->text());

    ui->pb_pant_test_hora->setText(QTime::currentTime().toString("hh:mm ap"));
    ui->pb_pant_paciente_hora_actual->setText(ui->pb_pant_test_hora->text());
    ui->pb_pant_base_de_datos_hora->setText(ui->pb_pant_test_hora->text());
}

void MainWindow::on_le_pant_base_de_datos_buscar_textChanged(const QString &arg1)
{

    ui->lw_pant_base_de_datos_pacientes->clear();

    if(arg1.isEmpty()){
        ui->lw_pant_base_de_datos_pacientes->addItems(lista_de_pacientes);
        ui->le_pant_base_de_datos_buscar->setStyleSheet(QStringLiteral("border-image: url(:/icons/fondo_transparente.png); color: rgb(255, 255, 255); border-image: url(:/icons/pantalla_secundaria_buscar.png);font: 57 italic 14pt \"Alegreya Sans Medium\";"));
        return;
    }

    QStringList lista_auxiliar;
    QString paciente;

    for(quint32 i=0; i< lista_de_pacientes.length(); i++){

        paciente = (lista_de_pacientes.at(i));
        if(paciente.left(50).contains(arg1,Qt::CaseInsensitive)){
            lista_auxiliar.append(paciente);
        }
    }

    ui->le_pant_base_de_datos_buscar->setStyleSheet(QStringLiteral("border-image: url(:/icons/fondo_transparente.png); color: rgb(255, 255, 255); border-image: url(:/icons/pantalla_secundaria_buscar_.png);font: 57 italic 14pt \"Alegreya Sans Medium\";"));

    ui->lw_pant_base_de_datos_pacientes->addItems(lista_auxiliar);
}

void MainWindow::on_le_pant_paciente_ID_textChanged(const QString &arg1)
{
    if(arg1.length() >= 6){

        uint16_t year,month, day;

        year = arg1.left(2).toInt();
        if(year > 20){
            year += 1900;
        }
        else{
            year+=2000;
        }

        month = arg1.left(4).right(2).toInt();
        day = arg1.left(6).right(2).toInt();

        birth_date_paciente.setDate(year, month, day);

        ui->pb_pant_paciente_fecha_nacimiento->setText(birth_date_paciente.toString("dd/MM/yyyy"));
    }
}
