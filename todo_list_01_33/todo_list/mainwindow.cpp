#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    checkFileStructure(); // setup for INI structure
    ui->setupUi(this);
    hideAll();
    // If the INI exists load it, if it does NOT create one.
    if(fileExists(PATHINIFILE)){
        loadINIfile();
    }else setupINIfile();

    if(!fileExists(TODO_FILE)) SAVE_FILE();
    // A TOTAL OVERRIDE FOR AUTOHIDE
    Reload();
    if(!AutoHideValue) showAll();
}
MainWindow::~MainWindow()
{
    if(CLOSE_AND_SAVING){
        SAVE_FILE();
        if(ui->actionSave_Postion_on_Exit->isChecked()){
            QSettings settings(PATHINIFILE, QSettings::IniFormat);
            settings.setValue(LastPosition, this->geometry());
        }
    }
    delete ui;
}
void MainWindow::setupINIfile()
{
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    //settings.beginGroup(GROUP_NAME);
    settings.setValue(ftsp, 0);
    settings.setValue(SavePosition, 1);
    settings.setValue(LastPosition, this->geometry());
    settings.setValue(ShowSaveQuit, ShowSaveQuitValue);
    settings.setValue(ShowTasks, ShowTaskValue);
    settings.setValue(ShowEvents, ShowEventsValue);
    settings.setValue(ShowNotes, ShowNotesValue);
    //settings.setValue(Task1, Task1);
    settings.setValue(AutoHide, AutoHideValue);
    settings.setValue(textFileOutputTask1, textFileOutputTaskValue1);
    settings.setValue(textFileOutputTask2, textFileOutputTaskValue2);
    settings.setValue(textFileOutputTask3, textFileOutputTaskValue3);
    settings.setValue(textFileOutputTask4, textFileOutputTaskValue4);
    settings.setValue(textFileOutputTask5, textFileOutputTaskValue5);
    settings.setValue(textFileOutputEvent1, textFileOutputEventValue1);
    settings.setValue(textFileOutputEvent2, textFileOutputEventValue2);
    settings.setValue(textFileOutputNote1, textFileOutputNoteValue1);
    settings.setValue(textFileOutputNote2, textFileOutputNoteValue2);
    settings.setValue(LocationToDoTXT,TODO_FILE);
    settings.setValue(LocationTask1, LocationTaskValue1);
    settings.setValue(LocationTask2, LocationTaskValue2);
    settings.setValue(LocationTask3, LocationTaskValue3);
    settings.setValue(LocationTask4, LocationTaskValue4);
    settings.setValue(LocationTask5, LocationTaskValue5);
    settings.setValue(LocationEvent1, LocationEventValue1);
    settings.setValue(LocationEvent2, LocationEventValue2);
    settings.setValue(LocationNote1, LocationNoteValue1);
    settings.setValue(LocationNote2, LocationNoteValue2);
    settings.setValue(OrderName, OrderNameValue);
    settings.setValue(ShowToolBar, true);
    settings.setValue(fortuneLocation, fortuneLocationValue);
    settings.setValue(showFortune, false);
    settings.setValue(showWeather, false);
    settings.setValue(showFortuneBefore, false);
    settings.setValue(showWeatherBefore, true);
    settings.setValue(showLightIcons, DisplayLightIcons);
    settings.setValue(SavePositionOnExit, false);
    settings.setValue(ScreenShot, ScreenShotValue);
    settings.setValue(ScreenRecorder, ScreenRecorderValue);
    settings.setValue(Setup_Complete, Setup_CompleteValue);

    // MENU SET UP and GUI

    setGeometry(DefaultGeoX1, DefaultGeoY1, DefaultGeoWidth, DefaultGeoHeight);
    ui->actionShow_Events->setChecked(ShowEventsValue);
    ui->actionSave_Quit_Visible->setChecked(ShowSaveQuitValue);
    ui->groupBox_save_quit->setVisible(ShowSaveQuitValue);
    ui->actionAuto_Hide->setChecked(AutoHideValue);
    //ui->textEdit_task_1->setText(Task1);
    //ui->groupBox_task_2->setVisible(true);
    //ui->actionDisplay_Debian_Hints->setChecked(false);
    ui->actionShow_Fortune->setChecked(false);
    ui->actionShow_Current_Weather->setChecked(false);
    ui->actionShow_Fortune_Before_After->setChecked(false);
    ui->actionShow_Weather_Before_After->setChecked(true);
    ui->actionShow_Fortune_Before_After->setVisible(false);
    ui->actionShow_Weather_Before_After->setVisible(false);
    if(ui->actionShow_Tasks->isChecked()){
        ui->groupBox_save_quit->setVisible(true); // tasks
        ui->groupBox_save_quit2->setVisible(false); // events
        ui->groupBox_save_quit3->setVisible(false); // notes
    }else if(!ui->actionShow_Tasks->isChecked() && ui->actionShow_Events->isChecked()){
        ui->groupBox_save_quit->setVisible(false); // tasks
        ui->groupBox_save_quit2->setVisible(true); // events
        ui->groupBox_save_quit3->setVisible(false); // notes
    }else if(ui->actionShow_Tasks->isChecked() && !ui->actionShow_Events->isChecked() && ui->actionNotes_On->isChecked()){
        ui->groupBox_save_quit->setVisible(false); // tasks
        ui->groupBox_save_quit2->setVisible(false); // events
        ui->groupBox_save_quit3->setVisible(true); // notes
    }
    if(fileExists(ScreenShotValue)){
        if(DEBUG) qDebug() << "exists ScreenShotValue:" << ScreenShotValue << " line: " << __LINE__;
        ui->actionScreen_Shot->setVisible(true);
    }else{
        if(DEBUG) qDebug() << "NOT exists ScreenShotValue:" << ScreenShotValue << " line: " << __LINE__;
        ui->actionScreen_Shot->setVisible(false);
    }
    if(fileExists(ScreenRecorderValue)){
        if(DEBUG) qDebug() << "exists ScreenRecorderValue:" << ScreenRecorderValue << " line: " << __LINE__;
        ui->actionRecord_Screen->setVisible(true);
    }else{
        if(DEBUG) qDebug() << "NOT exists ScreenRecorderValue:" << ScreenRecorderValue << " line: " << __LINE__;
        ui->actionRecord_Screen->setVisible(false);
    }

    if(fileExists(fortuneLocationValue)){
        fortuneExists = true;
        ui->actionShow_Fortune_Before_After->setVisible(true); // added 11-28-2023
    }else{
        fortuneExists = false;
        ui->actionShow_Fortune->setText(InstallFortune);
        ui->actionShow_Fortune->setChecked(false);
        ui->actionShow_Fortune_Before_After->setVisible(false);

    }
    // if(){}
    if(DEBUG) qDebug() << "StartWeb line: " << __LINE__;
    if(!Setup_CompleteValue){
        SetupConkyThemeDirectories();
    }
    StartWeb(_WEBSITE_HTML);
}
void MainWindow::loadINIfile()
{
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QFile file(PATHINIFILE);
    int value;
    bool bvalue;
    if(file.exists()){
        if(settings.contains(Debugging)){
            DEBUG = settings.value(Debugging).toBool();
        }
        if(settings.contains(ftsp)){
            value = settings.value(ftsp).toInt();
             if(value <= 3){
                 if(DEBUG) qDebug() << "StartWeb line: " << __LINE__;
                StartWeb(_WEBSITE_HTML);
                value++;
                settings.setValue(ftsp, value);
            }else{
                if(value < 25){
                    value++;
                    settings.setValue(ftsp, value);
                    if (value % 5 == 0){
                        if(DEBUG) qDebug() << "StartWeb line: " << __LINE__;
                        StartWeb( _WEBSITE_Donate);
                    }
                }else{
                    value++;
                    settings.setValue(ftsp, value);
                    if (value % 20 == 0) {
                        if(DEBUG) qDebug() << "StartWeb line: " << __LINE__;
                        StartWeb(_WEBSITE_Donate);
                    }
                }
            }
        }else{
            settings.setValue(ftsp, 1);
            if(DEBUG) qDebug() << "StartWeb line: " << __LINE__;
            StartWeb(_WEBSITE_HTML);
        }
        if(settings.contains(ShowSaveQuit)){
            ShowSaveQuitValue = settings.value(ShowSaveQuit).toBool();
        }else settings.setValue(ShowSaveQuit, ShowSaveQuitValue);
        if(settings.contains(ShowEvents)){
            ShowEventsValue = settings.value(ShowEvents).toBool();
        }else settings.setValue(ShowEvents, ShowEventsValue);
        if(settings.contains(ShowTasks)){
            ShowTaskValue = settings.value(ShowTasks).toBool();
        }else settings.setValue(ShowTasks, ShowTaskValue);
        if(settings.contains(ShowNotes)){
            ShowNotesValue = settings.value(ShowNotes).toBool();
        }else settings.setValue(ShowNotes, ShowNotesValue);
        if(settings.contains(AutoHide)){
            AutoHideValue = settings.value(AutoHide).toBool();
        }else settings.setValue(AutoHide, AutoHideValue);

        // TASKS and EVENTS
        if(settings.contains(textFileOutputTask1)){
            textFileOutputTaskValue1 = settings.value(textFileOutputTask1).toString();
        }else settings.setValue(textFileOutputTask1, textFileOutputTaskValue1);
        if(settings.contains(textFileOutputTask2)){
            textFileOutputTaskValue2 = settings.value(textFileOutputTask2).toString();
        }else settings.setValue(textFileOutputTask2, textFileOutputTaskValue2);
        if(settings.contains(textFileOutputTask3)){
            textFileOutputTaskValue3 = settings.value(textFileOutputTask3).toString();
        }else settings.setValue(textFileOutputTask3, textFileOutputTaskValue3);
        if(settings.contains(textFileOutputTask4)){
            textFileOutputTaskValue4 = settings.value(textFileOutputTask4).toString();
        }else settings.setValue(textFileOutputTask4, textFileOutputTaskValue4);
        if(settings.contains(textFileOutputTask5)){
            textFileOutputTaskValue5 = settings.value(textFileOutputTask5).toString();
        }else settings.setValue(textFileOutputTask5, textFileOutputTaskValue5);
        if(settings.contains(textFileOutputEvent1)){
            textFileOutputEventValue1 = settings.value(textFileOutputEvent1).toString();
        }else settings.setValue(textFileOutputEvent1, textFileOutputEventValue1);
        if(settings.contains(textFileOutputEvent2)){
            textFileOutputEventValue2 = settings.value(textFileOutputEvent2).toString();
        }else settings.setValue(textFileOutputEvent2, textFileOutputEventValue2);
        if(settings.contains(textFileOutputNote1)){
            textFileOutputNoteValue1 = settings.value(textFileOutputNote1).toString();
        }else settings.setValue(textFileOutputNote1, textFileOutputEventValue1);
        if(settings.contains(textFileOutputNote2)){
            textFileOutputNoteValue2 = settings.value(textFileOutputNote2).toString();
        }else settings.setValue(textFileOutputNote2, textFileOutputNoteValue2);

        // LOCATION OF TEXT FILES BEING SAVED
        if(settings.contains(LocationToDoTXT)){
            TODO_FILE = settings.value(LocationToDoTXT).toString();
        }else settings.setValue(LocationToDoTXT, TODO_FILE);
        if(settings.contains(LocationTask1)){
           LocationTaskValue1  = settings.value(LocationTask1).toString();
        }else settings.setValue(LocationTask1, LocationTaskValue1);
        if(settings.contains(LocationTask2)){
            LocationTaskValue2 = settings.value(LocationTask2).toString();
        }else settings.setValue(LocationTask2, LocationTaskValue2);
        if(settings.contains(LocationTask3)){
            LocationTaskValue3 = settings.value(LocationTask3).toString();
        }else settings.setValue(LocationTask3, LocationTaskValue3);
        if(settings.contains(LocationTask4)){
           LocationTaskValue4  = settings.value(LocationTask4).toString();
        }else settings.setValue(LocationTask4, LocationTaskValue4);
        if(settings.contains(LocationTask5)){
            LocationTaskValue5 = settings.value(LocationTask5).toString();
        }else settings.setValue(LocationTask5, LocationTaskValue5);
        if(settings.contains(LocationEvent1)){
           LocationEventValue1  = settings.value(LocationEvent1).toString();
        }else settings.setValue(LocationEvent1, LocationEventValue1);
        if(settings.contains(LocationEvent2)){
           LocationEventValue2 = settings.value(LocationEvent2).toString();
        }else settings.setValue(LocationEvent2, LocationEventValue2);
        if(settings.contains(LocationNote1)){
            LocationNoteValue1 = settings.value(LocationNote1).toString();
        }else settings.setValue(LocationNote1, LocationNoteValue1);
        if(settings.contains(LocationNote2)){
            LocationNoteValue2 = settings.value(LocationNote2).toString();
        }else settings.setValue(LocationNote2, LocationNoteValue2);
        //    const QString OrderName = "Order";
        //    QString OrderNameValue = "1"; // this can vary between 1 and 6
        if(settings.contains(OrderName)){
            OrderNameValue = settings.value(OrderName).toString();
            ORDER = settings.value(OrderName).toInt();
        }else settings.setValue(OrderName, OrderNameValue);
        if(settings.contains(ShowToolBar)){
            bvalue = settings.value(ShowToolBar).toBool();
            ui->toolBar->setVisible(bvalue);
            ui->actionShow_Tool_Bar->setChecked(bvalue);
        }else settings.setValue(ShowToolBar, true);
        if(settings.contains(fortuneLocation)){
            fortuneLocationValue = settings.value(fortuneLocation).toString();
        }else settings.setValue(fortuneLocation, fortuneLocationValue);

        if(fileExists(fortuneLocationValue)){
            if(settings.contains(showFortune)){
                bvalue = settings.value(showFortune).toBool();
                if(bvalue){
                    ui->actionShow_Fortune->setChecked(true);
                    ui->actionShow_Fortune_Before_After->setVisible(true);
                }else{
                    ui->actionShow_Fortune->setChecked(false);
                    ui->actionShow_Fortune_Before_After->setVisible(false);
                }
            }else{
                settings.setValue(showFortune, false);
                ui->actionShow_Fortune->setChecked(false);
                ui->actionShow_Fortune_Before_After->setVisible(false);
            }
            if(settings.contains(showFortuneBefore)){
                bvalue = settings.value(showFortuneBefore).toBool();
                if(bvalue){
                    ui->actionShow_Fortune_Before_After->setChecked(true);
                }else ui->actionShow_Fortune_Before_After->setChecked(false);
            }else settings.setValue(showFortuneBefore, false);
            fortuneExists = true;
        }else{
            // you need to install fortune for this feature to work
            fortuneExists = false;
            ui->actionShow_Fortune->setText(InstallFortune);
            ui->actionShow_Fortune->setChecked(false);
            ui->actionShow_Fortune_Before_After->setVisible(false);
        }
        if(settings.contains(showWeatherBefore)){
            bvalue = settings.value(showWeatherBefore).toBool();
            if(bvalue){
                ui->actionShow_Weather_Before_After->setChecked(true);
            }else ui->actionShow_Weather_Before_After->setChecked(false);
        }else{
            settings.setValue(showWeatherBefore, true);
            ui->actionShow_Weather_Before_After->setChecked(true);
        }

        if(settings.contains(showWeather)){
            bvalue = settings.value(showWeather).toBool();
            if(bvalue){
                ui->actionShow_Current_Weather->setChecked(true);
                ui->actionShow_Weather_Before_After->setVisible(true);
            }else{
                ui->actionShow_Current_Weather->setChecked(false);
                ui->actionShow_Weather_Before_After->setVisible(false);
            }
        }else{
            ui->actionShow_Current_Weather->setChecked(false);
            ui->actionShow_Weather_Before_After->setVisible(false);
        }

        if(settings.contains(showLightIcons)){
            DisplayLightIcons = settings.value(showLightIcons).toBool();
            ui->actionShow_Light_Icons->setChecked(DisplayLightIcons);
            change_icons(DisplayLightIcons);
        }else settings.setValue(showLightIcons, DisplayLightIcons);
        if(settings.contains(SavePositionOnExit)){
            bvalue = settings.value(SavePositionOnExit).toBool();
            ui->actionSave_Postion_on_Exit->setChecked(bvalue);
        }else settings.setValue(SavePositionOnExit, false);
        if(settings.contains(ScreenShot)){
            ScreenShotValue = settings.value(ScreenShot).toString();
        }else settings.setValue(ScreenShot, ScreenShotValue);

        if(settings.contains(ScreenRecorder)){
           ScreenRecorderValue  = settings.value(ScreenRecorder).toString();

        }else settings.setValue(ScreenRecorder, ScreenRecorderValue);

        if(fileExists(ScreenShotValue)){
            if(DEBUG) qDebug() << "exists ScreenShotValue:" << ScreenShotValue;
            ui->actionScreen_Shot->setVisible(true);
        }else{
            if(DEBUG) qDebug() << "NOT exists ScreenShotValue:" << ScreenShotValue;
            ui->actionScreen_Shot->setVisible(false);
        }
        if(fileExists(ScreenRecorderValue)){
            if(DEBUG) qDebug() << "exists ScreenRecorderValue:" << ScreenRecorderValue;
            ui->actionRecord_Screen->setVisible(true);
        }else{
            if(DEBUG) qDebug() << "NOT exists ScreenRecorderValue:" << ScreenRecorderValue;
            ui->actionRecord_Screen->setVisible(false);
        }

        if(DEBUG) qDebug() << "StartWeb line: " << __LINE__;
        //StartWeb(_WEBSITE_HTML);

        // MENU SET UP and GUI
        ui->groupBox_events->setVisible(ShowEventsValue);
        ui->actionShow_Events->setChecked(ShowEventsValue);
        ui->groupBox_notes->setVisible(ShowNotesValue);
        ui->actionNotes_On->setChecked(ShowNotesValue);
        ui->groupBox_task->setVisible(ShowTaskValue);
        ui->actionShow_Tasks->setChecked(ShowTaskValue);
        ui->actionSave_Quit_Visible->setChecked(ShowSaveQuitValue);
        ui->groupBox_save_quit->setVisible(ShowSaveQuitValue);
        ui->actionAuto_Hide->setChecked(AutoHideValue);

        if(ShowEventsValue){
            ui->actionShow_Events->setText(EventsTextShow); // changed 11-12-2023
        }else{
            ui->actionShow_Events->setText(EventsTextHide);
        }
        if(ShowNotesValue){
            ui->actionNotes_On->setText(NotesTextShow);
        }else{
            ui->actionNotes_On->setText(NotesTextHide);
        }
        if(ShowTaskValue){
            ui->actionShow_Tasks->setText(TaskMenuShow); // changed 11-12-2023
        }else ui->actionShow_Tasks->setText(TaskMenuHide);

        if(ShowSaveQuitValue){
            ui->actionSave_Quit_Visible->setText(SaveQuitTextHide);
        }else{
            ui->actionSave_Quit_Visible->setText(SaveQuitTextShow);
        }
        on_actionOrder_triggered();
        if(ui->actionSave_Quit_Visible->isChecked()){
            if(ui->actionShow_Tasks->isChecked()){
                ui->groupBox_save_quit->setVisible(true); // tasks
                ui->groupBox_save_quit2->setVisible(false); // events
                ui->groupBox_save_quit3->setVisible(false); // notes
            }else if(!ui->actionShow_Tasks->isChecked() && ui->actionShow_Events->isChecked()){
                ui->groupBox_save_quit->setVisible(false); // tasks
                ui->groupBox_save_quit2->setVisible(true); // events
                ui->groupBox_save_quit3->setVisible(false); // notes
            }else if(!ui->actionShow_Tasks->isChecked() && !ui->actionShow_Events->isChecked() && ui->actionNotes_On->isChecked()){
                ui->groupBox_save_quit->setVisible(false); // tasks
                ui->groupBox_save_quit2->setVisible(false); // events
                ui->groupBox_save_quit3->setVisible(true); // notes
            }
        }else{
            ui->groupBox_save_quit->setVisible(false); // tasks
            ui->groupBox_save_quit2->setVisible(false); // events
            ui->groupBox_save_quit3->setVisible(false); // notes
        }
        if(settings.contains(SavePosition) && settings.contains(LastPosition)){ // this section is to restore the last position
            if(settings.value(SavePosition).toBool()){
                QRect myrect = settings.value(LastPosition).toRect();
                setGeometry(myrect);
            }
        }
    }else MainWindow::setupINIfile();
}
void MainWindow::SAVE_FILE()
{
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QFile file(PATHINIFILE);
    settings.remove(Task1); // erase and start over when saving
    settings.remove(Task2);
    settings.remove(Task3);
    settings.remove(Task4);
    settings.remove(Task5);
    settings.remove(Event1);
    settings.remove(Event2);
    settings.remove(Note1);
    settings.remove(Note2);
    int CheckingCountTask = 1;
    int CheckingCountEvents = 1;
    int CheckingCountNote = 1;
    QString output;
    QString FINALOUTPUT = NULL;
    QString outputINIname;
    QString outputTXTname;
    QString TasksFileLocation;
    QString EventsFileLocation;
    if(ui->checkBox_task_1->isChecked()){
        output = ui->textEdit_task_1->toPlainText();
        outputINIname = outputINIVariableName(CheckingCountTask);
        outputTXTname = outputTXTVariableName(CheckingCountTask);
        settings.setValue(outputINIname, output); // this is to the INI file
        if(ui->actionShow_Tasks->isChecked()){ // added 11-26-2023
            if(ui->actionTasks_Save_to_Text_File->isChecked()){

                FINALOUTPUT = outputTXTname + output + "\n"; // this is to the text file
            }
            if(ui->actionTasks_Save_to_Many_Text_Files->isChecked()){
                saveConfigTextFile(LocationTaskValue1, output);
            }
        }else{
            deleteFile(LocationTaskValue1);
        }
        CheckingCountTask++;
    }else{
        settings.remove(Task1);
        deleteFile(LocationTaskValue1);
    }

    if(ui->checkBox_task_2->isChecked()){
        output = ui->textEdit_task_2->toPlainText();
        outputINIname = outputINIVariableName(CheckingCountTask);
        outputTXTname = outputTXTVariableName(CheckingCountTask);
        TasksFileLocation = outputTasksFileLocation(CheckingCountTask);
        settings.setValue(outputINIname, output); // INI file
        if(ui->actionShow_Tasks->isChecked()){ // added 11-26-2023
            if(ui->actionTasks_Save_to_Text_File->isChecked()){
                if(FINALOUTPUT == NULL){
                    FINALOUTPUT = outputTXTname + output + "\n";
                }else{
                    FINALOUTPUT +=outputTXTname + output + "\n";
                }
            }
            if(ui->actionTasks_Save_to_Many_Text_Files->isChecked()){
                saveConfigTextFile(TasksFileLocation, output);
            }
        }else{
            deleteFile(LocationTaskValue2);
        }
        CheckingCountTask++;
    }else{
        settings.remove(Task2);
        deleteFile(LocationTaskValue2);
    }
    if(ui->checkBox_task_3->isChecked()){
        output = ui->textEdit_task_3->toPlainText();
        outputINIname = outputINIVariableName(CheckingCountTask);
        outputTXTname = outputTXTVariableName(CheckingCountTask);
        TasksFileLocation = outputTasksFileLocation(CheckingCountTask);
        settings.setValue(outputINIname, output); // INI file
        if(ui->actionShow_Tasks->isChecked()){ // added 11-26-2023
            if(ui->actionTasks_Save_to_Text_File->isChecked()){
                if(FINALOUTPUT == NULL){
                    FINALOUTPUT = outputTXTname + output + "\n";
                }else{
                    FINALOUTPUT +=outputTXTname + output + "\n";
                }
            }
            if(ui->actionTasks_Save_to_Many_Text_Files->isChecked()){
               saveConfigTextFile(TasksFileLocation, output);
            }
        }else{
            deleteFile(LocationTaskValue3);
        }
        CheckingCountTask++;
    }else{
        settings.remove(Task3);
        deleteFile(LocationTaskValue3);
    }

    if(ui->checkBox_task_4->isChecked()){
        output = ui->textEdit_task_4->toPlainText();
        outputINIname = outputINIVariableName(CheckingCountTask);
        outputTXTname = outputTXTVariableName(CheckingCountTask);
        TasksFileLocation = outputTasksFileLocation(CheckingCountTask);
        settings.setValue(outputINIname, output); // INI file
        if(ui->actionShow_Tasks->isChecked()){ // added 11-26-2023
            if(ui->actionTasks_Save_to_Text_File->isChecked()){
                if(FINALOUTPUT == NULL){
                    FINALOUTPUT = outputTXTname + output + "\n";
                }else{
                    FINALOUTPUT +=outputTXTname + output + "\n";
                }
            }
            if(ui->actionTasks_Save_to_Many_Text_Files->isChecked()){
                saveConfigTextFile(TasksFileLocation, output);
            }
        }else{
            deleteFile(LocationTaskValue4);
        }
        CheckingCountTask++;
    }else{
        settings.remove(Task4);
        deleteFile(LocationTaskValue4);
    }
    
    if(ui->checkBox_task_5->isChecked()){
        output = ui->textEdit_task_5->toPlainText();
        outputINIname = outputINIVariableName(CheckingCountTask);
        outputTXTname = outputTXTVariableName(CheckingCountTask);
        TasksFileLocation = outputTasksFileLocation(CheckingCountTask);
        settings.setValue(outputINIname, output); // INI file
        if(ui->actionShow_Tasks->isChecked()){ // added 11-26-2023
            if(ui->actionTasks_Save_to_Text_File->isChecked()){
                if(FINALOUTPUT == NULL){
                    FINALOUTPUT = outputTXTname + output + "\n";
                }else{
                    FINALOUTPUT +=outputTXTname + output + "\n";
                }
            }
            if(ui->actionTasks_Save_to_Many_Text_Files->isChecked()){
             saveConfigTextFile(TasksFileLocation, output);
            }
        }else{
            deleteFile(LocationTaskValue5);
        }
        CheckingCountTask++;
    }else{
        settings.remove(Task5);
        deleteFile(LocationTaskValue5);
    }
    // events
    if(ui->checkBox_event_1->isChecked()){
        output = ui->plainTextEdit_event_1->toPlainText();
        settings.setValue(Event1, output);
        if(ui->actionShow_Events->isChecked()){ // added 11-26-2023
            if(ui->actionEvents_Save_to_Text_File->isChecked()){
                if(FINALOUTPUT == NULL){
                    FINALOUTPUT = textFileOutputEventValue1 + output + "\n";
                }else{
                    FINALOUTPUT +=textFileOutputEventValue1 + output + "\n";
                }
            }
            if(ui->actionEvents_Save_to_Many_Text_Files->isChecked()){
                saveConfigTextFile(LocationEventValue1, output);
            }
        }else{
            deleteFile(LocationEventValue1);
            //deleteFile(LocationEventValue2);
        }
        CheckingCountEvents++;
    }else{
        settings.remove(Event1);
        deleteFile(LocationEventValue1);
    }
    if(ui->checkBox_event_2->isChecked()){
        output = ui->plainTextEdit_event_2->toPlainText();
        if(ui->checkBox_event_1->isChecked()){
            settings.setValue(Event2, output);
            if(ui->actionShow_Events->isChecked()){ // added 11-26-2023
                if(ui->actionEvents_Save_to_Text_File->isChecked()){
                    FINALOUTPUT += textFileOutputEventValue2 + output + "\n";
                }
                if(ui->actionEvents_Save_to_Many_Text_Files->isChecked()){
                 saveConfigTextFile(LocationEventValue2, output);
                }
            }else{
                deleteFile(LocationEventValue2);
            }
        }else{
            //output = ui->plainTextEdit_event_2->toPlainText();
            settings.setValue(Event1, output);
            if(ui->actionShow_Events->isChecked()){ // added 11-26-2023
                if(ui->actionEvents_Save_to_Text_File->isChecked()){
                    if(FINALOUTPUT == NULL){
                        FINALOUTPUT = textFileOutputEventValue1 + output + "\n";
                    }else{
                        FINALOUTPUT +=textFileOutputEventValue1 + output + "\n";
                    }
                }
                if(ui->actionEvents_Save_to_Many_Text_Files->isChecked()){
                 saveConfigTextFile(LocationEventValue1, output);
                }
            }else{
                deleteFile(LocationEventValue1);
            }
        }
        CheckingCountEvents++;
    }else{
        settings.remove(Event2);
        deleteFile(LocationEventValue2);
    }
    // notes
    if(ui->checkBox_note_1->isChecked()){
        output = ui->plainTextEdit_note_1->toPlainText();
        settings.setValue(Note1, output);
        if(ui->actionNotes_On->isChecked()){ // added 11-26-2023
            if(ui->actionNotes_Save_to_Text_File->isChecked()){
                if(FINALOUTPUT == NULL){
                    FINALOUTPUT = textFileOutputNoteValue1 + output + "\n";
                }else{
                    FINALOUTPUT += textFileOutputNoteValue1 + output + "\n";
                }
            }
            if(ui->actionNotes_Save_to_Many_Text_Files->isChecked()){
                saveConfigTextFile(LocationNoteValue1, output);
            }
        }else{
            deleteFile(LocationNoteValue1);
        }
        CheckingCountNote++;
    }else{
        settings.remove(Note1);
        deleteFile(LocationNote1);
    }
    
    if(ui->checkBox_note_2->isChecked()){
        output = ui->plainTextEdit_note_2->toPlainText();
        if(ui->checkBox_note_1->isChecked()){
            settings.setValue(Note2, output);
            if(ui->actionNotes_On->isChecked()){ // added 11-26-2023
                if(ui->actionNotes_Save_to_Text_File->isChecked()){
                    FINALOUTPUT += textFileOutputEventValue2 + output + "\n";
                }
                if(ui->actionNotes_Save_to_Many_Text_Files->isChecked()){
                     saveConfigTextFile(LocationNoteValue2, output);
                }
            }else{
                deleteFile(LocationNoteValue2);
            }
        }else{
            settings.setValue(Note1, output);
            if(ui->actionNotes_On->isChecked()){ // added 11-26-2023
                if(ui->actionNotes_Save_to_Text_File->isChecked()){
                    if(FINALOUTPUT == NULL){
                        FINALOUTPUT = textFileOutputNoteValue1 + output + "\n";
                    }else{
                        FINALOUTPUT += textFileOutputNoteValue1 + output + "\n";
                    }
                }
                if(ui->actionNotes_Save_to_Many_Text_Files->isChecked()){
                    saveConfigTextFile(LocationNoteValue2, output);
                    CheckingCountNote++;
                }
            }else{
                deleteFile(LocationNoteValue2);
            }
        }
        CheckingCountNote++;
    }else{
        settings.remove(Note2);
        deleteFile(LocationNote2);
    }
    switch(CheckingCountTask){
        case 1:
            if(fileExists(LocationTaskValue1)) deleteFile(LocationTaskValue1);
        case 2:
            if(fileExists(LocationTaskValue2)) deleteFile(LocationTaskValue2);
        case 3:
            if(fileExists(LocationTaskValue3)) deleteFile(LocationTaskValue3);
        case 4:
            if(fileExists(LocationTaskValue4)) deleteFile(LocationTaskValue4);
        case 5:
            if(fileExists(LocationTaskValue5)) deleteFile(LocationTaskValue5);
        break;
    }
    switch (CheckingCountEvents) {
        case 1:
            //LocationEventValue1
            if(fileExists(LocationEventValue1)) deleteFile(LocationEventValue1);
        case 2:
            if(fileExists(LocationEventValue2)) deleteFile(LocationEventValue2);
        break;
    }
    switch (CheckingCountNote) {
        case 1:
            if(fileExists(LocationNoteValue1)) deleteFile(LocationNoteValue1);
        case 2:
            if(fileExists(LocationNoteValue2)) deleteFile(LocationNoteValue2);
        break;
    }
    qDebug() << "CheckingCountEvents: " << CheckingCountEvents << " line: " << __LINE__;
    qDebug() << "CheckingCountNote: " << CheckingCountNote << " line: " << __LINE__;    
    saveConfigTextFile(TODO_FILE, FINALOUTPUT);
    Reload();
}
void MainWindow::Reload()
{
    MainWindow::clearScreen();
    if(ui->actionShow_Tasks->isChecked() && ui->actionAuto_Hide->isChecked()){
        ui->groupBox_task_1->setVisible(true);
        ui->groupBox_task_2->setVisible(false);
        ui->groupBox_task_3->setVisible(false);
        ui->groupBox_task_4->setVisible(false);
        ui->groupBox_task_5->setVisible(false);
    }
    if(ui->actionShow_Events->isChecked() && ui->actionAuto_Hide->isChecked()){
        ui->groupBox_event_1->setVisible(true);
        ui->groupBox_event_2->setVisible(false);
    }
    if(ui->actionNotes_On->isChecked() && ui->actionAuto_Hide->isChecked()){
        ui->groupBox_note_1->setVisible(true);
        ui->groupBox_note_2->setVisible(false);
    }
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QFile file(PATHINIFILE);
    QString value;
    if(file.exists()){
        if(settings.contains(Task1)){
            value = settings.value(Task1).toString();
            ui->groupBox_task_1->setVisible(true);
            ui->groupBox_task_2->setVisible(true);
            ui->checkBox_task_1->setChecked(true);
            ui->textEdit_task_1->setText(value);
        }
        if(settings.contains(Task2)){
            value = settings.value(Task2).toString();
            ui->checkBox_task_2->setChecked(true);
            ui->textEdit_task_2->setText(value);
            ui->groupBox_task_3->setVisible(true);
        }
        if(settings.contains(Task3)){
            value = settings.value(Task3).toString();
            ui->checkBox_task_3->setChecked(true);
            ui->textEdit_task_3->setText(value);
            ui->groupBox_task_4->setVisible(true);
        }
        if(settings.contains(Task4)){
            value = settings.value(Task4).toString();
            ui->checkBox_task_4->setChecked(true);
            ui->textEdit_task_4->setText(value);
            ui->groupBox_task_5->setVisible(true);
        }
        if(settings.contains(Task5)){
            value = settings.value(Task5).toString();
            ui->checkBox_task_5->setChecked(true);
            ui->textEdit_task_5->setText(value);
        }
        if(settings.contains(Event1)){
            value = settings.value(Event1).toString();
            ui->checkBox_event_1->setChecked(true);
            ui->plainTextEdit_event_1->setPlainText(value);
            ui->groupBox_event_1->setVisible(true);
            ui->groupBox_event_2->setVisible(true);
        }
        if(settings.contains(Event2)){
            value = settings.value(Event2).toString();
            ui->checkBox_event_2->setChecked(true);
            ui->plainTextEdit_event_2->setPlainText(value);
        }
        if(settings.contains(Note1)){
            value = settings.value(Note1).toString();
            ui->checkBox_note_1->setChecked(true);
            ui->plainTextEdit_note_1->setPlainText(value);
        }
        if(settings.contains(Note2)){
            value = settings.value(Note2).toString();
            ui->checkBox_note_2->setChecked(true);
            ui->plainTextEdit_note_2->setPlainText(value);
        }
    }else MainWindow::setupINIfile();
}
void MainWindow::Reset()
{
    deleteFile(PATHINIFILE);
    deleteFile(TODO_FILE);
    deleteFile(LocationTaskValue1);
    deleteFile(LocationTaskValue2);
    deleteFile(LocationTaskValue3);
    deleteFile(LocationTaskValue4);
    deleteFile(LocationTaskValue5);
    deleteFile(LocationEventValue1);
    deleteFile(LocationEventValue2);
    deleteFile(LocationNoteValue1);
    deleteFile(LocationNoteValue2);
    deleteFile(LocationOrder);
    deleteFile(locationFortune);
    deleteFile(locationWeather);
    deleteFile(locationSFBefore);
    deleteFile(locationSWBefore);
    CLOSE_AND_SAVING = false;
    QApplication::quit();
}
void MainWindow::clearScreen()
{
    ui->textEdit_task_1->clear();
    ui->textEdit_task_2->clear();
    ui->textEdit_task_3->clear();
    ui->textEdit_task_4->clear();
    ui->textEdit_task_5->clear();
    ui->plainTextEdit_event_1->clear();
    ui->plainTextEdit_event_2->clear();
    ui->plainTextEdit_note_1->clear();
    ui->plainTextEdit_note_2->clear();

    ui->checkBox_task_5->setChecked(false); // do this in reverse otherwise results do not show properly
    ui->checkBox_task_4->setChecked(false);
    ui->checkBox_task_3->setChecked(false);
    ui->checkBox_task_2->setChecked(false);
    ui->checkBox_task_1->setChecked(false);

    ui->checkBox_event_2->setChecked(false);
    ui->checkBox_event_1->setChecked(false);
    ui->checkBox_note_1->setChecked(false);
    ui->checkBox_note_2->setChecked(false);
}
void MainWindow::showAll()
{
    ui->groupBox_task->setVisible(true);
    ui->groupBox_events->setVisible(true);
    ui->groupBox_notes->setVisible(true);
    ui->groupBox_task_1->setVisible(true);
    ui->groupBox_task_2->setVisible(true);
    ui->groupBox_task_3->setVisible(true);
    ui->groupBox_task_4->setVisible(true);
    ui->groupBox_task_5->setVisible(true);
    ui->groupBox_event_1->setVisible(true);
    ui->groupBox_event_2->setVisible(true);
    ui->groupBox_note_1->setVisible(true);
    ui->groupBox_note_2->setVisible(true);
    ui->groupBox_save_quit->setVisible(true); // tasks
    ui->groupBox_save_quit2->setVisible(false); // events
    ui->groupBox_save_quit3->setVisible(false); // notes
}
void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}
void MainWindow::on_actionSave_triggered()
{
    SAVE_FILE();
}
void MainWindow::on_actionSave_Position_triggered()
{
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QFile file(PATHINIFILE);
    settings.setValue(LastPosition, this->geometry());
}
void MainWindow::on_pushButton_save_quit_clicked()
{
    MainWindow::on_actionQuit_triggered();
}
void MainWindow::on_pushButton_save_clicked()
{
    SAVE_FILE();
}
QString MainWindow::outputINIVariableName(int Count)
{
    QString output;
    switch (Count) {
    case 1:
        output = Task1;
        break;
    case 2:
        output = Task2;
        break;
    case 3:
        output = Task3;
        break;
    case 4:
        output = Task4;
        break;
    case 5:
        output = Task5;
        break;
    }
    return output;
}
QString MainWindow::outputTXTVariableName(int Count)
{
    QString output;
    switch (Count) {
    case 1:
        output = textFileOutputTaskValue1;
        break;
    case 2:
        output = textFileOutputTaskValue2;
        break;
    case 3:
        output = textFileOutputTaskValue3;
        break;
    case 4:
        output = textFileOutputTaskValue4;
        break;
    case 5:
        output = textFileOutputTaskValue5;
        break;
    }
    return output;
}
QString MainWindow::outputTasksFileLocation(int Count)
{
    QString output;
    switch (Count) {
    case 1:
        output = LocationTaskValue1;
        break;
    case 2:
        output = LocationTaskValue2;
        break;
    case 3:
        output = LocationTaskValue3;
        break;
    case 4:
        output = LocationTaskValue4;
        break;
    case 5:
        output = LocationTaskValue5;
        break;
    }
    return output;
}
void MainWindow::change_icons(bool decide)
{
    if(decide){ // white theme

        ui->actionQuit->setIcon(QIcon(":/img/quit_icon_white.png"));
        ui->actionSave->setIcon(QIcon(":/img/save_icon_white.png"));
        ui->actionShow_Events->setIcon(QIcon(":/img/event_icon_white.png"));
        ui->actionReload->setIcon(QIcon(":/img/Reload_icon_white.png"));
        ui->actionClear_All->setIcon(QIcon(":/img/clear_icon_white.png"));
        ui->actionAuto_Hide->setIcon(QIcon(":/img/show_icon_white.png"));
        ui->actionShow_Tasks->setIcon(QIcon(":/img/task_icon_white.png"));
        ui->actionToggle->setIcon(QIcon(":/img/toggle_icon_white.png"));
        ui->actionNotes_On->setIcon(QIcon(":/img/notes_icon_white.png"));
        ui->actionView_All->setIcon(QIcon(":/img/viewall_icon_white.png"));
        ui->actionScreen_Shot->setIcon(QIcon(":/img/screenshot_icon_white.png"));
        ui->actionRecord_Screen->setIcon(QIcon(":/img/screenrecorder_icon_white.png"));
    }else{ // dark theme
        ui->actionQuit->setIcon(QIcon(":/img/quit_icon_dark.png"));
        ui->actionSave->setIcon(QIcon(":/img/save_icon_dark.png"));
        ui->actionShow_Events->setIcon(QIcon(":/img/event_icon_dark.png"));
        ui->actionReload->setIcon(QIcon(":/img/Reload_icon_dark.png"));
        ui->actionClear_All->setIcon(QIcon(":/img/clear_icon_dark.png"));
        ui->actionAuto_Hide->setIcon(QIcon(":/img/show_icon_dark.png"));
        ui->actionShow_Tasks->setIcon(QIcon(":/img/task_icon_dark.png"));
        ui->actionToggle->setIcon(QIcon(":/img/toggle_icon_dark.png"));
        ui->actionNotes_On->setIcon(QIcon(":/img/notes_icon_dark.png"));
        ui->actionView_All->setIcon(QIcon(":/img/viewall_icon_dark.png"));
        ui->actionScreen_Shot->setIcon(QIcon(":/img/screenshot_icon_dark.png"));
        ui->actionRecord_Screen->setIcon(QIcon(":/img/screenrecorder_icon_dark.png"));
    }
}

void MainWindow::SetupConkyThemeDirectories()
{
    // check to make sure that todo themes exists in the ~/.conky directory
    // if one or two folders are missing expect that all of them are missing
    QString TODO_LOCATION = "/usr/share/ashersprograms/todolist/conky_themes/";
    QString ACCU_WEATHER_TODO_LOCATION = TODO_LOCATION + "accu_weather/weather.sh";
    QString TODO_THEME_LOCATION = TODO_LOCATION + "Todo/todo";

    QString ACCU_PERSONAL_WEATHER_LOCATION = "~/.conky/accu_weather";
    QString TODO_PERSONAL_LOCATION = "~/.conky/Todo";
    bool pass_personal_1 = false;
    bool pass_personal_2 = false;
    bool pass_business_1 = false;
    bool pass_business_2 = false;
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QString output;
    if(fileExists(ACCU_WEATHER_TODO_LOCATION)) pass_business_1 = true;
    if(fileExists(TODO_THEME_LOCATION)) pass_business_2 = true;
    if(fileExists(ACCU_PERSONAL_WEATHER_LOCATION)) pass_personal_1 = true;
    if(fileExists(TODO_PERSONAL_LOCATION)) pass_personal_2 = true;
    if(settings.contains(Setup_Complete)){
        Setup_CompleteValue = settings.value(Setup_Complete).toBool();
    }
    if(!Setup_CompleteValue){
        if(pass_business_1 && pass_business_2){
            if(!pass_personal_1 && !pass_personal_2){
                // at this point the program belives that the To Do List Themes do NOT exists and need to be copied to the owns personal directory
                //if(!dirExists(path)) QDir().mkdir(path);
                output = "<p>You are about to set up the Conky themes that go with To Do List</p>";
                QMessageBox::information(this, "Set up Conky Themes", output);
                CopyAllConkyDirectories();
                Setup_CompleteValue = true;
                settings.setValue(Setup_Complete, Setup_CompleteValue);
            }else{
                // if seems that the conky themes already exists and there is no need to copy the directories again.
                output = "It seems that the Conky Themes are already installed there is no need to copy the directories at this time.";
                Setup_CompleteValue = true;
                settings.setValue(Setup_Complete, Setup_CompleteValue);
            }
        }else{
            // the main themes do NOT exists the program was not installed properly and this function can not be used.
            output = "<p>There seemed to be an issue finding the accompanying Conky Themes. Please notify the maintainer of this program and let them know that this error occured.</p><br><br> Error Number: 22";
            QMessageBox::warning(this, "Error in Setting up the Conky Themes", output);
            Setup_CompleteValue = false;
            settings.setValue(Setup_Complete, Setup_CompleteValue);
        }
    }
}

void MainWindow::CopyAllConkyDirectories()
{

}
void MainWindow::on_actionSave_Quit_Visible_triggered(bool checked)
{
    if(checked){
        if(ui->actionShow_Tasks->isChecked()){
            ui->groupBox_save_quit->setVisible(true); // tasks
            ui->groupBox_save_quit2->setVisible(false); // events
            ui->groupBox_save_quit3->setVisible(false); // notes
        }else if(!ui->actionShow_Tasks->isChecked() && ui->actionShow_Events->isChecked()){
            ui->groupBox_save_quit->setVisible(false); // tasks
            ui->groupBox_save_quit2->setVisible(true); // events
            ui->groupBox_save_quit3->setVisible(false); // notes
        }else if(!ui->actionShow_Tasks->isChecked() && !ui->actionShow_Events->isChecked()){
            ui->groupBox_save_quit->setVisible(false); // tasks
            ui->groupBox_save_quit2->setVisible(false); // events
            ui->groupBox_save_quit3->setVisible(true); // notes
        }
        ui->actionSave_Quit_Visible->setText(SaveQuitTextHide);
    }else{
        ui->groupBox_save_quit->setVisible(false); // tasks
        ui->groupBox_save_quit2->setVisible(false); // events
        ui->groupBox_save_quit3->setVisible(false); // notes
        ui->actionSave_Quit_Visible->setText(SaveQuitTextShow);
    }
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QFile file(PATHINIFILE);
    ShowSaveQuitValue = checked;
    settings.setValue(ShowSaveQuit, ShowSaveQuitValue);
}
void MainWindow::on_plainTextEdit_event_1_modificationChanged(bool arg1)
{
    if(DEBUG) qDebug() << "Change happened: on_plainTextEdit_event_1_modificationChanged: " << arg1 << " line: " << __LINE__;
    ui->checkBox_event_1->setChecked(true);
}
void MainWindow::on_plainTextEdit_event_2_modificationChanged(bool arg1)
{
    if(DEBUG) qDebug() << "Change happened: on_plainTextEdit_event_2_modificationChanged: " << arg1 << " line: " << __LINE__ ;
    ui->checkBox_event_2->setChecked(true);
}
void MainWindow::on_plainTextEdit_note_1_modificationChanged(bool arg1)
{
    if(DEBUG) qDebug() << "Change happened: on_plainTextEdit_note_1_modificationChanged: " << arg1 << " line: " << __LINE__ ;
    ui->checkBox_note_1->setChecked(true);
}
void MainWindow::on_plainTextEdit_note_2_modificationChanged(bool arg1)
{
    if(DEBUG) qDebug() << "Change happened: on_plainTextEdit_note_2_modificationChanged: " << arg1 << " line: " << __LINE__ ;
    ui->checkBox_note_2->setChecked(true);
}
void MainWindow::on_checkBox_event_1_toggled(bool checked)
{
    if(checked){
        if(ui->actionAuto_Hide->isChecked()){
            if(checked) ui->groupBox_event_2->setVisible(true);
        }
    }else{
        if(ui->actionAuto_Hide->isChecked()){
            if(!ui->checkBox_event_2->isChecked()){
                ui->groupBox_event_2->setVisible(false);
            }
        }
    }
}
void MainWindow::on_checkBox_task_1_toggled(bool checked)
{
    if(ui->actionAuto_Hide->isChecked()){
        if(checked){
            ui->groupBox_task_2->setVisible(true);
        }else{
            // SAVE_FILE();

//            ui->groupBox_task_2->setVisible(false);
//            ui->groupBox_task_3->setVisible(false);
//            ui->groupBox_task_4->setVisible(false);
//            ui->groupBox_task_5->setVisible(false);
//            ui->checkBox_task_2->setChecked(false);
//            ui->checkBox_task_3->setChecked(false);
//            ui->checkBox_task_4->setChecked(false);
//            ui->checkBox_task_5->setChecked(false);
        }
    }
}
void MainWindow::on_checkBox_task_2_toggled(bool checked)
{
    if(ui->actionAuto_Hide->isChecked()){
        if(checked){
            ui->groupBox_task_3->setVisible(true);
        }else{
//           ui->groupBox_task_3->setVisible(false);
//            if(!ui->checkBox_task_4->isChecked()){
//                ui->groupBox_task_4->setVisible(false);
//            }
//            if(!ui->checkBox_task_5->isChecked()){
//                ui->groupBox_task_5->setVisible(false);
//            }

//            ui->checkBox_task_3->setChecked(false);
//            ui->checkBox_task_4->setChecked(false);
//            ui->checkBox_task_5->setChecked(false);
        }
    }
}
void MainWindow::on_checkBox_task_3_toggled(bool checked)
{
    if(ui->actionAuto_Hide->isChecked()){
        if(checked){
            ui->groupBox_task_4->setVisible(true);
        }else{
            //ui->groupBox_task_4->setVisible(false);
           // ui->groupBox_task_5->setVisible(false);

            //ui->checkBox_task_4->setChecked(false);
            //ui->checkBox_task_5->setChecked(false);
        }
    }
}
void MainWindow::on_checkBox_task_4_toggled(bool checked)
{
    if(ui->actionAuto_Hide->isChecked()){
        if(checked){
            ui->groupBox_task_5->setVisible(true);
        }else{
//            ui->groupBox_task_5->setVisible(false);
//            ui->checkBox_task_5->setChecked(false);
        }
    }
}
void MainWindow::on_textEdit_task_1_textChanged()
{
    if(DEBUG) qDebug() << "Change happened:  on_textEdit_task_1_cursorPositionChanged line: " << __LINE__;
    ui->checkBox_task_1->setChecked(true);
}
void MainWindow::on_textEdit_task_2_textChanged()
{
    if(DEBUG) qDebug() << "Change happened:  on_textEdit_task_2_cursorPositionChanged line: " << __LINE__;
    ui->checkBox_task_2->setChecked(true);
}
void MainWindow::on_textEdit_task_3_textChanged()
{
    if(DEBUG) qDebug() << "Change happened:  on_textEdit_task_3_cursorPositionChanged line: " << __LINE__;
    ui->checkBox_task_3->setChecked(true);
}
void MainWindow::on_textEdit_task_4_textChanged()
{
    if(DEBUG) qDebug() << "Change happened:  on_textEdit_task_4_cursorPositionChanged line: " << __LINE__;
    ui->checkBox_task_4->setChecked(true);
}
void MainWindow::on_textEdit_task_5_textChanged()
{
    if(DEBUG) qDebug() << "Change happened:  on_textEdit_task_5_cursorPositionChanged line: " << __LINE__;
    ui->checkBox_task_5->setChecked(true);
}
void MainWindow::saveConfigTextFile(QString FileName, QString Output)
{
    if(Output != NULL){
        QFile file(FileName);
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this, "File did NOT Open", "The File: "+TODO_FILE+" did NOT open.");
            return;
        }
        QTextStream out(&file);
        out << Output;
        file.flush();
        file.close();
    }
}
void MainWindow::loadConfigFile()
{
    //QString filename = QFileDialog::getOpenFileName(this, "Open the File");
    QFile file(TODO_FILE);
    //filepath = filename;
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "File NOT Open", "The File: "+TODO_FILE+" did NOT open.");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    //ui->textEdit->setText(text);
    file.close();
    MainWindow::processTxtInputToGUI(text);
}
void MainWindow::processTxtInputToGUI(QString wholeFile)
{
    QMessageBox::information(this, "info", wholeFile);
}
void MainWindow::on_actionShow_Tasks_triggered(bool checked) // tasks
{
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QFile file(PATHINIFILE);
    if(checked){
        ui->groupBox_task->setVisible(true);
        ui->actionShow_Tasks->setText(TaskMenuShow);
        if(ui->actionSave_Quit_Visible->isChecked()){
            ui->groupBox_save_quit->setVisible(true); // tasks
            ui->groupBox_save_quit2->setVisible(false); // events
            ui->groupBox_save_quit3->setVisible(false); // notes
        }
    }else{
        if(!ui->actionShow_Events->isChecked() && !ui->actionNotes_On->isChecked()){ // if all three are blank open Events
            ui->actionShow_Events->setChecked(true);
            on_actionShow_Events_triggered(true);
            ShowEventsValue = true;
            settings.setValue(ShowEvents, ShowEventsValue);
        }
        ui->groupBox_task->setVisible(false);
        ui->actionShow_Tasks->setText(TaskMenuHide);
        //if(ui->actionSave_Quit_Visible->isChecked()){
        if(ui->actionSave_Quit_Visible->isChecked() && ui->actionShow_Events->isChecked()){
            ui->groupBox_save_quit->setVisible(false); // tasks
            ui->groupBox_save_quit2->setVisible(true); // events
            ui->groupBox_save_quit3->setVisible(false); // notes
        }else{
            ui->groupBox_save_quit->setVisible(false); // tasks
            ui->groupBox_save_quit2->setVisible(false); // events
            ui->groupBox_save_quit3->setVisible(true); // notes
        }
        //}
    }
    ShowTaskValue = checked;
    settings.setValue(ShowTasks, ShowTaskValue);
}
void MainWindow::on_actionShow_Events_triggered(bool checked)
{
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QFile file(PATHINIFILE);
    if(checked){
        ui->groupBox_events->setVisible(true);
        ui->actionShow_Events->setText(EventsTextShow);
        //if(ui->actionSave_Quit_Visible->isChecked()){
        if(ui->actionSave_Quit_Visible->isChecked() && !ui->actionShow_Tasks->isChecked()){
            ui->groupBox_save_quit->setVisible(false); // tasks
            ui->groupBox_save_quit2->setVisible(true); // events
            ui->groupBox_save_quit3->setVisible(false); // notes
        }
        //}
    }else{
        if(!ui->actionShow_Tasks->isChecked() && !ui->actionNotes_On->isChecked()){
            ui->actionShow_Tasks->setChecked(true);
            on_actionShow_Tasks_triggered(true);
            ShowTaskValue = true;
            settings.setValue(ShowTasks, ShowTaskValue);
        }
        //if(ui->actionSave_Quit_Visible->isChecked()){
        if(ui->actionSave_Quit_Visible->isChecked() && ui->actionShow_Tasks->isChecked()){
            ui->groupBox_save_quit->setVisible(true); // tasks
            ui->groupBox_save_quit2->setVisible(false); // events
            ui->groupBox_save_quit3->setVisible(false); // notes
        }else if(ui->actionSave_Quit_Visible->isChecked()){
            ui->groupBox_save_quit->setVisible(false); // tasks
            ui->groupBox_save_quit2->setVisible(false); // events
            ui->groupBox_save_quit3->setVisible(true); // notes
        }
        //}
        ui->actionShow_Events->setText(EventsTextHide);
        ui->groupBox_events->setVisible(false);
        ui->groupBox_save_quit2->setVisible(false); // events
    }
    ShowEventsValue = checked;
    settings.setValue(ShowEvents, ShowEventsValue);
}
void MainWindow::on_actionNotes_On_triggered(bool checked)
{
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QFile file(PATHINIFILE);
    if(checked){
        ui->groupBox_notes->setVisible(true);
        //if(ui->actionSave_Quit_Visible->isChecked()){
        if(ui->actionSave_Quit_Visible->isChecked() && !ui->actionShow_Tasks->isChecked() && !ui->actionShow_Events->isChecked()){
            ui->groupBox_save_quit->setVisible(false);
            ui->groupBox_save_quit2->setVisible(false);
            ui->groupBox_save_quit3->setVisible(true);
        }
        //}
    }else{
        ui->groupBox_notes->setVisible(false);
        ui->actionNotes_On->setText(NotesTextHide);
        if(!ui->actionShow_Tasks->isChecked() && !ui->actionShow_Events->isChecked()) {
            ui->actionShow_Tasks->setText(TaskMenuShow);
            ui->actionNotes_On->setText(NotesTextHide);
            ui->groupBox_task->setVisible(true);
            ui->actionShow_Tasks->setChecked(true);
            if(ui->actionSave_Quit_Visible->isChecked()){
                ui->groupBox_save_quit->setVisible(true); // tasks
                ui->groupBox_save_quit2->setVisible(false); // events
                ui->groupBox_save_quit3->setVisible(false); // notes
            }
            ShowTaskValue = true;
            settings.setValue(ShowTasks, ShowTaskValue);
        }
    }

    ShowNotesValue = checked;
    settings.setValue(ShowNotes, ShowNotesValue);
}
void MainWindow::checkFileStructure()
{
    // If the skeleton for the TEXT and INI file to be stored here
    if(!dirExists(CONFIGURATION_BASE)) dirCreate(CONFIGURATION_BASE);
    if(!dirExists(CACHE_DIR)) dirCreate(CACHE_DIR);
}
bool MainWindow::dirExists(QString path)
{
    if(QDir(path).exists()){
        return true;
    } else return false;
}
void MainWindow::dirCreate(QString path)
{
    if(!dirExists(path)) QDir().mkdir(path);
}
bool MainWindow::fileExists(QString path)
{
    QFileInfo check_file(path);
    if (check_file.exists() && check_file.isFile()) { return true; } else { return false; } // check if file exists and if yes: Is it really a file and no directory?
}
void MainWindow::deleteFile(QString path)
{
    QFileInfo check_file(path);
    if(fileExists(path)){
        QDir().remove(path);
    }
}
void MainWindow::StartWeb(QString path)
{
    QDesktopServices::openUrl(QUrl(path));
}
void MainWindow::on_actionReload_triggered()
{
    Reload();
}
void MainWindow::on_actionClear_All_triggered()
{
    clearScreen();
}
void MainWindow::on_actionReset_triggered()
{
    Reset();
}
void MainWindow::on_actionAuto_Hide_triggered(bool checked)
{
    AutoHideValue = checked;
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QFile file(PATHINIFILE);
    settings.setValue(AutoHide, AutoHideValue);
    if(checked){
        hideAll();
        //loadTODOfile();
        Reload();
    }else{
        showAll();
    }
}
void MainWindow::hideAll()
{
    //ui->groupBox_task_1->setVisible(false);
    ui->groupBox_task_2->setVisible(false);
    ui->groupBox_task_3->setVisible(false);
    ui->groupBox_task_4->setVisible(false);
    ui->groupBox_task_5->setVisible(false);
    //ui->groupBox_event_1->setVisible(false);
    ui->groupBox_event_2->setVisible(false);
    ui->groupBox_note_2->setVisible(false);
}
void MainWindow::on_actionAbout_QT_triggered()
{
    Dialog_About_QT qt;
    qt.setModal(true);
    qt.exec();
}
QString MainWindow::returnStartOfLine(int count)
{
        QString StartLine;
        if(count == 1){
            StartLine = textFileOutputTaskValue1;
        }else if(count == 2){
            StartLine = textFileOutputTaskValue2;
        }else if(count == 3){
            StartLine = textFileOutputTaskValue3;
        }else if(count == 4){
            StartLine = textFileOutputTaskValue4;
        }else if(count == 5){
            StartLine = textFileOutputTaskValue5;
        }
        return StartLine;
}
QString MainWindow::eraseName(int count)
{
    QString output;
    if(count == 1){
        output = Task1;
    }else if(count == 2){
        output = Task2;
    }else if(count == 3){
        output = Task3;
    }else if(count == 4){
        output = Task4;
    }else if(count == 5){
        output = Task5;
    }
    return output;
}
void MainWindow::on_actionToggle_triggered()
{
    if(!ui->actionShow_Tasks->isChecked() && !ui->actionShow_Events->isChecked() && ui->actionNotes_On->isChecked()) TOGGLE_NUMBER = 1;
    if(!ui->actionShow_Tasks->isChecked() && ui->actionShow_Events->isChecked() && !ui->actionNotes_On->isChecked()) TOGGLE_NUMBER = 3;
    if(ui->actionShow_Tasks->isChecked() && !ui->actionShow_Events->isChecked() && !ui->actionNotes_On->isChecked() && TOGGLE_NUMBER == 1) TOGGLE_NUMBER++;
    if(TOGGLE_NUMBER > 3) TOGGLE_NUMBER = 3;
    if(TOGGLE_NUMBER < 1) TOGGLE_NUMBER = 1;
    if(TOGGLE_NUMBER == 1){ // Task
        ShowTaskValue = true;
        ShowEventsValue = false;
        ShowNotesValue = false;
       ui->actionShow_Tasks->setText(TaskMenuShow);
       ui->actionShow_Events->setText(EventsTextHide);
       ui->actionNotes_On->setText(NotesTextHide);
       if(ui->actionSave_Quit_Visible->isChecked()){
       ui->groupBox_save_quit->setVisible(true);
       ui->groupBox_save_quit2->setVisible(false);
       ui->groupBox_save_quit3->setVisible(false);
       }else{
           ui->groupBox_save_quit->setVisible(false);
           ui->groupBox_save_quit2->setVisible(false);
           ui->groupBox_save_quit3->setVisible(false);
       }
        TOGGLE_NUMBER++;
    }else if(TOGGLE_NUMBER == 2){ // Event
       ShowTaskValue = false;
       ShowEventsValue = true;
       ShowNotesValue = false;
       ui->actionShow_Tasks->setText(TaskMenuHide);
       ui->actionShow_Events->setText(EventsTextShow);
       ui->actionNotes_On->setText(NotesTextHide);
       if(ui->actionSave_Quit_Visible->isChecked()){
       ui->groupBox_save_quit->setVisible(false);
       ui->groupBox_save_quit2->setVisible(true);
       ui->groupBox_save_quit3->setVisible(false);
       }else{
           ui->groupBox_save_quit->setVisible(false);
           ui->groupBox_save_quit2->setVisible(false);
           ui->groupBox_save_quit3->setVisible(false);
       }
        TOGGLE_NUMBER++;
    }else{
       ShowTaskValue = false;
       ShowEventsValue = false;
       ShowNotesValue = true;
       ui->actionShow_Tasks->setText(TaskMenuHide);
       ui->actionShow_Events->setText(EventsTextHide);
       ui->actionNotes_On->setText(NotesTextShow);
       if(ui->actionSave_Quit_Visible->isChecked()){
       ui->groupBox_save_quit->setVisible(false);
       ui->groupBox_save_quit2->setVisible(false);
       ui->groupBox_save_quit3->setVisible(true);
       }else{
           ui->groupBox_save_quit->setVisible(false);
           ui->groupBox_save_quit2->setVisible(false);
           ui->groupBox_save_quit3->setVisible(false);
       }
        TOGGLE_NUMBER = 1;
    }
    ui->actionShow_Tasks->setChecked(ShowTaskValue);
    ui->groupBox_task->setVisible(ShowTaskValue);
    ui->actionShow_Events->setChecked(ShowEventsValue);
    ui->groupBox_events->setVisible(ShowEventsValue);
    ui->actionNotes_On->setChecked(ShowNotesValue);
    ui->groupBox_notes->setVisible(ShowNotesValue);
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QFile file(PATHINIFILE);
    settings.setValue(ShowTasks, ShowTaskValue);
    settings.setValue(ShowEvents, ShowEventsValue);
    settings.setValue(ShowNotes, ShowNotesValue);
}
void MainWindow::on_actionView_All_triggered()
{
    ui->actionShow_Tasks->setText(TaskMenuShow);
    ui->actionShow_Events->setText(EventsTextShow);
    ui->actionNotes_On->setText(NotesTextShow);
    ui->actionShow_Tasks->setChecked(true);
    ui->actionShow_Events->setChecked(true);
    ui->actionNotes_On->setChecked(true);
    ui->groupBox_task->setVisible(true);
    ui->groupBox_events->setVisible(true);
    ui->groupBox_notes->setVisible(true);
    if(ui->actionSave_Quit_Visible->isChecked()){
        ui->groupBox_save_quit->setVisible(true);
        ui->groupBox_save_quit2->setVisible(false);
        ui->groupBox_save_quit3->setVisible(false);
    }
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QFile file(PATHINIFILE);
    ShowTaskValue = true;
    ShowEventsValue = true;
    ShowNotesValue = true;
    settings.setValue(ShowTasks, ShowTaskValue);
    settings.setValue(ShowEvents, ShowNotesValue);
    settings.setValue(ShowNotes, ShowNotesValue);
}
void MainWindow::on_checkBox_note_1_toggled(bool checked)
{
    if(checked){
        if(ui->actionAuto_Hide->isChecked()){
            if(checked) ui->groupBox_note_2->setVisible(true);
        }
    }else{
        if(ui->actionAuto_Hide->isChecked()){
            if(!ui->checkBox_note_2->isChecked()){
                ui->groupBox_note_2->setVisible(false);
            }
        }
    }
}
void MainWindow::on_checkBox_event_2_toggled(bool checked)
{
    if(!checked){
      if(ui->actionAuto_Hide->isChecked()){
          if(!ui->checkBox_event_1->isChecked()){
              ui->groupBox_event_2->setVisible(false);
          }
      }
    }
}
void MainWindow::on_checkBox_note_2_toggled(bool checked)
{
    if(!checked){
        if(ui->actionAuto_Hide->isChecked()){
            if(!ui->checkBox_note_1->isChecked()){
                ui->groupBox_note_2->setVisible(false);
            }
        }
    }
}
void MainWindow::on_actionOrder_triggered()
{
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QString output;
    if(ORDER == 1){
        ui->actionOrder->setText("Events, Notes, Tasks");
        output = "echo '1' > " + LocationOrder;
        system(output.toLocal8Bit());
        OrderNameValue = "1";
        settings.setValue(OrderName, OrderNameValue);
        if(DEBUG) qDebug() << "output: " << output;
        ORDER ++;
    }else if(ORDER == 2){
        ui->actionOrder->setText("Events, Tasks, Notes");
        output = "echo '2' > " + LocationOrder;
        system(output.toLocal8Bit());
        OrderNameValue = "2";
        settings.setValue(OrderName, OrderNameValue);
        if(DEBUG) qDebug() << "output: " << output;
        ORDER ++;
    }else if(ORDER == 3){
        ui->actionOrder->setText("Tasks, Events, Notes");
        output = "echo '3' > " + LocationOrder;
        system(output.toLocal8Bit());
        OrderNameValue = "3";
        settings.setValue(OrderName, OrderNameValue);
        if(DEBUG) qDebug() << "output: " << output;
        ORDER ++;
    }else if(ORDER == 4){
        ui->actionOrder->setText("Tasks, Notes, Events");
        output = "echo '4' > " + LocationOrder;
        system(output.toLocal8Bit());
        OrderNameValue = "4";
        settings.setValue(OrderName, OrderNameValue);
        if(DEBUG) qDebug() << "output: " << output;
        ORDER ++;
    }else if(ORDER == 5){
        ui->actionOrder->setText("Notes, Events, Tasks");
        output = "echo '5' > " + LocationOrder;
        system(output.toLocal8Bit());
        OrderNameValue = "5";
        settings.setValue(OrderName, OrderNameValue);
        if(DEBUG) qDebug() << "output: " << output;
        ORDER ++;
    }else{ // ORDER == 6
        ui->actionOrder->setText("Notes, Tasks, Events");
        output = "echo '6' > " + LocationOrder;
        OrderNameValue = "6";
        settings.setValue(OrderName, OrderNameValue);
        system(output.toLocal8Bit());
        if(DEBUG) qDebug() << "output: " << output;
        ORDER = 1;
    }
}
void MainWindow::on_actionShow_Tool_Bar_triggered(bool checked)
{
    ui->toolBar->setVisible(checked);
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QFile file(PATHINIFILE);
    settings.setValue(ShowToolBar, checked);
}
void MainWindow::on_actionShow_Fortune_triggered(bool checked)
{
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QString output;
    if(checked && fortuneExists == true){
        output = "echo '1' > " + locationFortune;
        system(output.toLocal8Bit());
        settings.setValue(showFortune, true);
        ui->actionShow_Fortune_Before_After->setVisible(true);
    }else{
        output = "echo '0' > " + locationFortune;
        system(output.toLocal8Bit());
        settings.setValue(OrderName, OrderNameValue);
        settings.setValue(showFortune, false);
        ui->actionShow_Fortune_Before_After->setVisible(false);
    }
    if(fortuneExists == false){
        ui->actionShow_Fortune->setChecked(false);
        QMessageBox::information(this, MissingFortuneTitle, MissingFortune);
    }
}
void MainWindow::on_actionShow_Current_Weather_triggered(bool checked)
{
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QString output;
    if(checked){
        settings.setValue(showWeather, true);
        output = "echo '1' > " + locationWeather;
        system(output.toLocal8Bit());
        ui->actionShow_Weather_Before_After->setVisible(true);
    }else{
        settings.setValue(showWeather, false);
        output = "echo '0' > " + locationWeather;
        system(output.toLocal8Bit());
        ui->actionShow_Weather_Before_After->setVisible(false);
    }
}
void MainWindow::on_actionShow_Fortune_Before_After_triggered(bool checked)
{
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QString output;
    if(checked){
        settings.setValue(showFortuneBefore, true);
        output = "echo '1' > " + locationSFBefore;
        system(output.toLocal8Bit());
    }else{
        settings.setValue(showFortuneBefore, false);
        output = "echo '0' > " + locationSFBefore;
        system(output.toLocal8Bit());
    }
}
void MainWindow::on_actionShow_Weather_Before_After_triggered(bool checked)
{
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    QString output;
    if(checked){
        settings.setValue(showWeatherBefore, true);
        output = "echo '1' > " + locationSWBefore;
        system(output.toLocal8Bit());
    }else{
        settings.setValue(showWeatherBefore, false);
        output = "echo '0' > " + locationSWBefore;
        system(output.toLocal8Bit());
    }
}
void MainWindow::on_actionShow_Light_Icons_triggered()
{
    if(DisplayLightIcons){
        ui->actionShow_Light_Icons->setText("Show Light Icons");
        DisplayLightIcons = false;
    }else{
        ui->actionShow_Light_Icons->setText("Show Dark Icons");
        DisplayLightIcons = true;
    }
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    settings.setValue(showLightIcons, DisplayLightIcons);
    change_icons(DisplayLightIcons);
}
void MainWindow::on_actionGettings_Started_triggered()
{
    StartWeb(_WEBSITE_UsersGuideHTML);
}
void MainWindow::on_actionAbout_triggered()
{
    StartWeb(_WEBSITE_About);
}
void MainWindow::on_actionCredits_triggered()
{
    StartWeb(_WEBSITE_Credits);
}
void MainWindow::on_actionKeyboard_Shortcuts_triggered()
{
    StartWeb(_WEBSITE_KeyboardShortcuts);
}
void MainWindow::on_actionUsers_Guide_triggered()
{
   StartWeb(_WEBSITE_UsersGuideHTML);
}
void MainWindow::on_actionCopyright_triggered()
{
    StartWeb(_WEBSITE_Copyright);
}
void MainWindow::on_actionDonate_triggered()
{
    StartWeb(_WEBSITE_Donate);
}
void MainWindow::on_actionJoin_Our_Social_Groups_triggered()
{
    StartWeb(_WEBSITE_Social);
}
void MainWindow::on_actionSave_Postion_on_Exit_triggered(bool checked)
{
    QSettings settings(PATHINIFILE, QSettings::IniFormat);
    settings.setValue(SavePositionOnExit, checked);
}
void MainWindow::on_pushButton_save2_clicked()
{
    SAVE_FILE();
}
void MainWindow::on_pushButton_save3_clicked()
{
    SAVE_FILE();
}
void MainWindow::on_pushButton_save_quit2_clicked()
{
    MainWindow::on_actionQuit_triggered();
}
void MainWindow::on_pushButton_save_quit3_clicked()
{
    MainWindow::on_actionQuit_triggered();
}
void MainWindow::on_actionScreen_Shot_triggered()
{
    if(fileExists(ScreenShotValue)){
        system(ScreenShotValue.toLocal8Bit());
    }
}
void MainWindow::on_actionRecord_Screen_triggered()
{
    if(fileExists(ScreenRecorderValue)){
        system(ScreenRecorderValue.toLocal8Bit());
    }
}
void MainWindow::on_actionAbout_TODOs_triggered()
{
    Dialog_Bhattacharjee qt;
    qt.setModal(true);
    qt.exec();
}
