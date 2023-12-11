#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCoreApplication>
#include <QMainWindow>
#include <QProcess>
#include <QFileInfo>
#include <QDir>

// for adding settings of .ini files
#include <QFile>
#include <QSettings>
//#include <QCoreApplication>
#include <QStandardPaths>

// for Desktop ICON
#include <QFile>
#include <QTextStream>

// for proper way to call a html page.
#include <QDesktopServices>
#include <QUrl>

// Debugging
#include <QMessageBox>
#include <QDebug>

#include "dialog_about_qt.h"
#include "dialog_bhattacharjee.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAuto_Hide_triggered(bool checked);
    void on_actionClear_All_triggered();
    void on_actionReload_triggered();
    void on_actionReset_triggered();
    void on_actionSave_Position_triggered();
    void on_actionShow_Tasks_triggered(bool checked);
    void on_actionToggle_triggered();
    void on_actionView_All_triggered();
    void on_actionQuit_triggered();
    void on_actionSave_Quit_Visible_triggered(bool checked);
    void on_actionSave_triggered();
    void on_pushButton_save_clicked();
    void on_pushButton_save_quit_clicked();
    void on_actionShow_Events_triggered(bool checked);
    void on_checkBox_event_1_toggled(bool checked);
    void on_checkBox_event_2_toggled(bool checked);
    void on_plainTextEdit_event_1_modificationChanged(bool arg1);
    void on_plainTextEdit_event_2_modificationChanged(bool arg1);
    void on_actionNotes_On_triggered(bool checked);
    void on_checkBox_note_1_toggled(bool checked);
    void on_checkBox_note_2_toggled(bool checked);
    void on_checkBox_task_1_toggled(bool checked);
    void on_checkBox_task_2_toggled(bool checked);
    void on_checkBox_task_3_toggled(bool checked);
    void on_checkBox_task_4_toggled(bool checked);
    void on_textEdit_task_1_textChanged();
    void on_textEdit_task_2_textChanged();
    void on_textEdit_task_3_textChanged();
    void on_textEdit_task_4_textChanged();
    void on_textEdit_task_5_textChanged();
   void on_actionAbout_QT_triggered();
   void on_plainTextEdit_note_1_modificationChanged(bool arg1);
   void on_plainTextEdit_note_2_modificationChanged(bool arg1);
   void on_actionOrder_triggered();
   void on_actionShow_Tool_Bar_triggered(bool checked);
   void on_actionShow_Fortune_triggered(bool checked);
   void on_actionShow_Current_Weather_triggered(bool checked);
   void on_actionShow_Fortune_Before_After_triggered(bool checked);
   void on_actionShow_Weather_Before_After_triggered(bool checked);
   void on_actionShow_Light_Icons_triggered();
   void on_actionGettings_Started_triggered();
   void on_actionAbout_triggered();
   void on_actionCredits_triggered();
   void on_actionKeyboard_Shortcuts_triggered();
   void on_actionUsers_Guide_triggered();
   void on_actionCopyright_triggered();
   void on_actionDonate_triggered();
   void on_actionJoin_Our_Social_Groups_triggered();
   void on_actionSave_Postion_on_Exit_triggered(bool checked);

   void on_pushButton_save2_clicked();

   void on_pushButton_save3_clicked();

   void on_pushButton_save_quit2_clicked();

   void on_pushButton_save_quit3_clicked();


   void on_actionScreen_Shot_triggered();

   void on_actionRecord_Screen_triggered();

   void on_actionAbout_TODOs_triggered();

private:
    Ui::MainWindow *ui;
    bool DEBUG = true;
    //bool DEBUG = false;
    bool CLOSE_AND_SAVING = true;
    const QString COMPANY_NAME = "ashersprograms";
    const QString PROGRAMS_NAME = "todolist";
    const QString CONFIGURATION_DIR = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    const QString CONFIGURATION_BASE = CONFIGURATION_DIR+"/" + COMPANY_NAME +"/";
    const QString CACHE_DIR = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/";
    const QString PATHINIFILE = CONFIGURATION_BASE+PROGRAMS_NAME+".ini";
    const QString LocationToDoTXT = "LocToDoTXT";
    QString TODO_FILE = CACHE_DIR+"todo.txt"; // location of the main text file.
    const QString LocationTask1 = "LocTask1";
    QString LocationTaskValue1 = CACHE_DIR+"Task1.txt";
    const QString LocationTask2 = "LocTask2";
    QString LocationTaskValue2 = CACHE_DIR+"Task2.txt";
    const QString LocationTask3 = "LocTask3";
    QString LocationTaskValue3 = CACHE_DIR+"Task3.txt";
    const QString LocationTask4 = "LocTask4";
    QString LocationTaskValue4 = CACHE_DIR+"Task4.txt";
    const QString LocationTask5 = "LocTask5";
    QString LocationTaskValue5 = CACHE_DIR+"Task5.txt";
    const QString LocationEvent1 = "LocEvent1";
    QString LocationEventValue1 = CACHE_DIR+"Event1.txt";
    const QString LocationEvent2 = "LocEvent2";
    QString LocationEventValue2 = CACHE_DIR+"Event2.txt";
    const QString LocationNote1 = "LocNote1";
    QString LocationNoteValue1 = CACHE_DIR+"Note1.txt";
    const QString LocationNote2 = "LocNote2";
    QString LocationNoteValue2 = CACHE_DIR+"Note2.txt";
    const QString ftsp = "ftsp";
    const QString SavePosition = "pos"; // name of the variable to see if you want to save last position
    int savePositionValue = 1; // 1 equals true 0 equals false DEFAULT value
    const QString LastPosition = "lastpos";
    const QString ShowEvents = "ShowEvents";
    bool ShowEventsValue = true;
    const QString SavePositionOnExit = "SavePosExit";
    const QString EventsTextShow = "Events ON";
    const QString EventsTextHide = "Events OFF";
    const QString OrderName = "Order";
    QString OrderNameValue = "1"; // this can vary between 1 and 6
    const QString ShowTasks = "ShowTasks";
    const QString ShowToolBar = "ShowToolBar";
    bool ShowTaskValue = true;
    const QString TaskMenuShow = "Tasks ON";
    const QString TaskMenuHide = "Tasks OFF";
    const QString ShowNotes = "ShowNotes";
    bool ShowNotesValue = true;
    const QString NotesTextShow = "Notes ON";
    const QString NotesTextHide = "Notes OFF";
    const QString ShowSaveQuit = "ShowSaveQuit";
    const QString SaveQuitTextShow = "Show Save and Quit";
    const QString SaveQuitTextHide = "Hide Save and Quit";
    const QString AutoHide = "AutoHide";
    const QString Debugging = "Debugging";
    bool AutoHideValue = true;
    bool ShowSaveQuitValue = true;
    void setupINIfile();
    void loadINIfile();
    QString filepath;
    void SAVE_FILE();
    void saveConfigTextFile(QString FileName, QString Output);
    void loadConfigFile();
    void processTxtInputToGUI(QString wholeFile);
    void checkFileStructure();
    bool fileExists(QString path);
    void deleteFile(QString path);
    bool dirExists(QString path);
    void dirCreate(QString path);
    const QString _WEBSITE = "http://www.ashersprograms.com/";
    const QString _WEBSITE_HTML = _WEBSITE + "index.php?program=" + PROGRAMS_NAME;
    const QString _WEBSITE_About = _WEBSITE_HTML + "#About";
    const QString _WEBSITE_Credits = _WEBSITE_HTML + "#Credits";
    const QString _WEBSITE_Donate = _WEBSITE_HTML + "#Donate";
    const QString _WEBSITE_KeyboardShortcuts = _WEBSITE_HTML + "#KeyboardShortcuts";
    const QString _WEBSITE_UsersGuideHTML = _WEBSITE_HTML + "#GettingStarted";
    const QString _WEBSITE_Social = _WEBSITE_HTML + "#Social";
    const QString _WEBSITE_Copyright = _WEBSITE_HTML + "&section=Copyright";
    void StartWeb(QString path);
    void Reload();
    void Reset();
    int DefaultGeoX1 = 0;
    int DefaultGeoY1 = 54;
    int DefaultGeoWidth = 1250;
    int DefaultGeoHeight = 391;
    void clearScreen();
    const QString Task1 = "Task1";
    const QString Task2 = "Task2";
    const QString Task3 = "Task3";
    const QString Task4 = "Task4";
    const QString Task5 = "Task5";
    const QString Event1 = "Event1";
    const QString Event2 = "Event2";
    const QString Note1 = "Note1";
    const QString Note2 = "Note2";
    const QString textFileOutputTask1 = "TD1"; // this is the name of the variable that in the ini file
    QString textFileOutputTaskValue1 = "Task1: \n"; // this is what is written to the TXT file.
    const QString textFileOutputTask2 = "TD2"; // this is the name of the variable that in the ini file
    QString textFileOutputTaskValue2 = "Task2: \n"; // this is what is written to the TXT file.
    const QString textFileOutputTask3 = "TD3"; // this is the name of the variable that in the ini file
    QString textFileOutputTaskValue3 = "Task3: \n"; // this is what is written to the TXT file.
    const QString textFileOutputTask4 = "TD4"; // this is the name of the variable that in the ini file
    QString textFileOutputTaskValue4 = "Task4: \n"; // this is what is written to the TXT file.
    const QString textFileOutputTask5 = "TD5"; // this is the name of the variable that in the ini file
    QString textFileOutputTaskValue5 = "Task5: \n"; // this is what is written to the TXT file.
    const QString textFileOutputEvent1 = "Ev1"; // this is the name of the variable that in the ini file
    QString textFileOutputEventValue1 = "Event 1: \n"; // this is what is written to the TXT file.
    const QString textFileOutputEvent2 = "Ev2"; // this is the name of the variable that in the ini file
    QString textFileOutputEventValue2 = "Event 2: \n"; // this is what is written to the TXT file.
    const QString textFileOutputNote1 = "Nt1"; // this is the name of the variable that in the ini file
    QString textFileOutputNoteValue1 = "Note 1: \n"; // this is what is written to the TXT file.
    const QString textFileOutputNote2 = "Nt2"; // this is the name of the variable that in the ini file
    QString textFileOutputNoteValue2 = "Note 2: \n"; // this is what is written to the TXT file.

    QString fortuneLocation = "fortuneLocation";
    QString fortuneLocationValue = "/usr/games/fortune";
    const QString showFortune = "ShowFortune";
    bool fortuneExists = false;
    const QString InstallFortune = "Install Fortune";
    const QString MissingFortuneTitle = "How to Install Fortune";
    const QString MissingFortune = "It seems that you are missing 'fortune' a fun and enternaining terminal program. That display a variety of enertaining sayings.\nBut with Ashers To Do List it can be added to your Conky for a new and intovative way to interact with fortune.\n\n\nInstructions on how to install are as follows:\n    Open a Terminal and type the following:\n    sudo apt install fortunes-mod\n    sudo apt install fortunes-debian-hints\n    sudo apt install fortunes-mario\n\n\n    If you are from another country you can look up what languages are available.\n    \n    For example.\n    If you speak German you would want to install fortunes-de by typing:\n    sudo apt install fortunes-mod fortunes-de\n\n    Or if you speak German you can would want to type:\n    sudo apt install fortunes-mod fortunes-es\n\n    To see a Full listing of available fortunes type:\n    apt-cache search fortune | grep fortune\n\nIf you have any problems, questions, or comments check out our social media groups\n\nThis program is not essential, just a fun program.";

    const QString showWeather = "ShowWeather";
    const QString showFortuneBefore = "SFBefore";
    const QString showWeatherBefore = "SWBefore";


    const QString ScreenShot = "ScreenShot";
    QString ScreenShotValue = "/usr/bin/xfce4-screenshooter";
    const QString ScreenRecorder = "ScreenRecorder";
    QString ScreenRecorderValue = "/usr/bin/simplescreenrecorder";

    void showAll();
    void hideAll();
    QString returnStartOfLine(int count);
    QString eraseName(int count);
    QString outputINIVariableName(int Count);
    QString outputTXTVariableName(int Count);
    QString outputTasksFileLocation(int Count);
    int TOGGLE_NUMBER = 1;
    int ORDER = 1;
    const QString LocationOrder = CONFIGURATION_BASE+"todo_Order.ini";
    const QString locationFortune = CONFIGURATION_BASE+"todo_ShowFortune.ini";
    const QString locationWeather = CONFIGURATION_BASE+"todo_ShowWeather.ini";
    const QString locationSFBefore = CONFIGURATION_BASE+"todo_SFBefore.ini";
    const QString locationSWBefore = CONFIGURATION_BASE+"todo_SWBefore.ini";
    const QString showLightIcons = "ShowLightIcons";
    bool DisplayLightIcons = true;
    void change_icons(bool decide); // changes the icon theme light/dark

    const QString Setup_Complete = "Setup_Complete";
    bool Setup_CompleteValue = false;
    void SetupConkyThemeDirectories();
    void CopyAllConkyDirectories();

};
#endif // MAINWINDOW_H
