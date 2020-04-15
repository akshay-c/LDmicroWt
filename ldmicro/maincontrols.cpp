#include "maincontrols.h"
#include "iolist.h"
#include "ldmicro.h"

// listview used to maintain the list of I/O pins with symbolic names, plus
// the internal relay too
// HLIST               IoList;
static int          IoListSelectionPoint;
static BOOL         IoListOutOfSync;
UINT                IoListHeight = 100;
int                 IoListTop;

// whether the simulation is running in real time
static BOOL         RealTimeSimulationRunning;

WtMenuBar::WtMenuBar()
{
    MakeMainWindowMenus();
    addMenu(std::move(MainMenu));
    MakeMainWindowControls();
    setMaximumSize(Wt::WLength(100, Wt::LengthUnit::Percentage),Wt::WLength(8, Wt::LengthUnit::Percentage));
}

void WtMenuBar::MakeMainWindowMenus()
{
    int i;

    MainMenu = Wt::cpp14::make_unique<Wt::WMenu>();
    FileMenu        = Wt::cpp14::make_unique<Wt::WMenuItem>("File");
    EditMenu        = Wt::cpp14::make_unique<Wt::WMenuItem>("Edit");
    Settings        = Wt::cpp14::make_unique<Wt::WMenuItem>("Settings");
    ProcessorMenu   = Wt::cpp14::make_unique<Wt::WMenuItem>("Microcontroller");
    InstructionMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Instructions");
    SimulateMenu    = Wt::cpp14::make_unique<Wt::WMenuItem>("Simulate");
    Compile         = Wt::cpp14::make_unique<Wt::WMenuItem>("Compile");
    Help            = Wt::cpp14::make_unique<Wt::WMenuItem>("Help");

    //Creating menu handlers
    FileMenuHandler         = Wt::cpp14::make_unique<Wt::WPopupMenu>();
    EditMenuHandler         = Wt::cpp14::make_unique<Wt::WPopupMenu>();
    SettingsHandler         = Wt::cpp14::make_unique<Wt::WPopupMenu>();
    ProcessorMenuHandler    = Wt::cpp14::make_unique<Wt::WPopupMenu>();
    InstructionMenuHandler   = Wt::cpp14::make_unique<Wt::WPopupMenu>();
    SimulateMenuHandler     = Wt::cpp14::make_unique<Wt::WPopupMenu>();
    CompileHandler          = Wt::cpp14::make_unique<Wt::WPopupMenu>();
    HelpHandler             = Wt::cpp14::make_unique<Wt::WPopupMenu>();

    // Creating labels for File Menu
    NewMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("New");
    OpenMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Open");
    SaveMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Save");
    SaveAsMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Save As");
    ExportMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Export As Text");
    ExitMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Exit");

    // Appending menu items (labels) to File menu and adding separators
    FileMenuHandler->addItem(std::move(NewMenu));
    FileMenuHandler->addItem(std::move(OpenMenu));
    FileMenuHandler->addItem(std::move(SaveMenu));
    FileMenuHandler->addItem(std::move(SaveAsMenu));
    FileMenuHandler->addSeparator();
    FileMenuHandler->addItem(std::move(ExportMenu));
    FileMenuHandler->addSeparator();
    FileMenuHandler->addItem(std::move(ExitMenu));
    FileMenu->setMenu(std::move(FileMenuHandler));

    // Creating labels for Edit Menu
    UndoMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Undo");
    RedoMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Redo");
    InsertRungBeforeMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert Rung Before");
    InsertRungAfterMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert Rung After");
    PushRungUpMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Move Selected Rung Up");
    PushRungDownMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Move Selected Rung Down");
    DeleteElementMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Delete Selected Element");
    DeleteRungMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Delete Rung");

    // Appending menu items to Edit menu and adding separators
    EditMenuHandler->addItem(std::move(UndoMenu));
    EditMenuHandler->addItem(std::move(RedoMenu));
    EditMenuHandler->addSeparator();
    EditMenuHandler->addItem(std::move(InsertRungBeforeMenu));
    EditMenuHandler->addItem(std::move(InsertRungAfterMenu));
    EditMenuHandler->addItem(std::move(PushRungUpMenu));
    EditMenuHandler->addItem(std::move(PushRungDownMenu));
    EditMenuHandler->addSeparator();
    EditMenuHandler->addItem(std::move(DeleteElementMenu));
    EditMenuHandler->addItem(std::move(DeleteRungMenu));
    EditMenu->setMenu(std::move(EditMenuHandler));

    // Creating labels for Settings Menu
    McuSettingsMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("MCU Parameters");
    MicroControllerMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Microcontroller");
    //MicroControllerHandler = Wt::cpp14::make_unique<Wt::WPopupMenu>();
    //ProcessorMenuGroup = Wt::cpp14::make_unique<Wt::WPopupMenu>();

    // Appending menu items to Settings menu
    SettingsHandler->addItem(std::move(McuSettingsMenu));
    // Appending the microcontroller names to "Microcontroller" item
    for (i = 0; i < NUM_SUPPORTED_MCUS; i++){
    ProcessorMenuItems[i] = Wt::cpp14::make_unique<Wt::WMenuItem>(SupportedMcus[i].mcuName);
    //ProcessorMenuItems[i]->setCheckable(true);
    //ProcessorMenuItems[i]->setActionGroup(ProcessorMenuGroup);
    ProcessorMenuHandler->addItem(std::move(ProcessorMenuItems[i]));
    }
    ProcessorMenuItems[i] = Wt::cpp14::make_unique<Wt::WMenuItem>("(no microcontroller)");
    //ProcessorMenuItems[i]->setCheckable(true);
    //ProcessorMenuItems[i]->setActionGroup(ProcessorMenuGroup);
    //MicroControllerMenu->addAction(ProcessorMenuItems[i]);
    ProcessorMenuHandler->addItem(std::move(ProcessorMenuItems[i]));
    MicroControllerMenu->setMenu(std::move(ProcessorMenuHandler));
    SettingsHandler->addItem(std::move(MicroControllerMenu));
    Settings->setMenu(std::move(SettingsHandler));
    // Creating labels for Instruction Menu and adding separators
    InsertCommentMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert Comment");
    InsertContactsMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert Contacts");
    InsertOsrMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert OSR (One Shot Rising)");
    InsertOsfMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert OSF (One Shot Falling)");
    InsertTonMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert TON (Delayed Turn On)");
    InsertTofMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert TOF (Delayed Turn Off)");
    InsertRtoMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert RTO (Retentive Delayed Turn On)");
    InsertCtuMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert CTU (Count Up)");
    InsertCtdMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert CTD (Count Down)");
    InsertCtcMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert CTC (Count Circular)");
    InsertEquMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert EQU (Compare for Equals)");
    InsertNeqMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert NEQ (Compare for Not Equals)");
    InsertGrtMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert GRT (Compare for Greater Than)");
    InsertGeqMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert GEQ (Compare for Greater Than or Equal)");
    InsertLesMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert LES (Compare for Less Than)");
    InsertLeqMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert LEQ (Compare for Less Than or Equal)");
    InsertOpenMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert Open Circuit");
    InsertShortMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert Short Circuit");
    InsertMasterRlyMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert Master Control Relay");
    InsertCoilMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert Coil");
    InsertResMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert RES (Counter/RTO Reset)");
    InsertMovMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert MOV (Move)");
    InsertAddMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert ADD (16-bit Integer Ad)");
    InsertSubMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert SUB (16-bit Integer Subtract)");
    InsertMulMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert MUL (16-bit Integer Multiply)");
    InsertDivMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert DIV (16-bit Integer Division)");
    InsertShiftRegMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert Shift Register");
    InsertLutMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert Look-Up Table");
    InsertPwlMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert Piecewise Linear");
    InsertFmtdStrMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert Formatted String Over UART");
    InsertUartSendMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert UART Send");
    InsertUartRecvMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert UART Receive");
    InsertSetPwmMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert Set PWM Output");
    InsertReadAdcMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert A/D Converter Read");
    InsertPersistMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Insert Make Persistent");
    MakeNormalMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Make Normal");
    NegateMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Make Negated");
    MakeSetOnlyMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Make Set-Only");
    MakeResetOnlyMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Make Reset-Only");

    // Appending menu items to Instruction menu and adding separators
    InstructionMenuHandler->addItem(std::move(InsertCommentMenu));
    InstructionMenuHandler->addSeparator();
    InstructionMenuHandler->addItem(std::move(InsertContactsMenu));
    InstructionMenuHandler->addSeparator();
    InstructionMenuHandler->addItem(std::move(InsertOsrMenu));
    InstructionMenuHandler->addSeparator();
    InstructionMenuHandler->addItem(std::move(InsertOsfMenu));
    InstructionMenuHandler->addItem(std::move(InsertTonMenu));
    InstructionMenuHandler->addItem(std::move(InsertTofMenu));
    InstructionMenuHandler->addItem(std::move(InsertRtoMenu));
    InstructionMenuHandler->addSeparator();
    InstructionMenuHandler->addItem(std::move(InsertCtuMenu));
    InstructionMenuHandler->addItem(std::move(InsertCtdMenu));
    InstructionMenuHandler->addItem(std::move(InsertCtcMenu));
    InstructionMenuHandler->addSeparator();
    InstructionMenuHandler->addItem(std::move(InsertEquMenu));
    InstructionMenuHandler->addItem(std::move(InsertNeqMenu));
    InstructionMenuHandler->addItem(std::move(InsertGrtMenu));
    InstructionMenuHandler->addItem(std::move(InsertGeqMenu));
    InstructionMenuHandler->addItem(std::move(InsertLesMenu));
    InstructionMenuHandler->addItem(std::move(InsertLeqMenu));
    InstructionMenuHandler->addSeparator();
    InstructionMenuHandler->addItem(std::move(InsertOpenMenu));
    InstructionMenuHandler->addItem(std::move(InsertShortMenu));
    InstructionMenuHandler->addItem(std::move(InsertMasterRlyMenu));
    InstructionMenuHandler->addSeparator();
    InstructionMenuHandler->addItem(std::move(InsertCoilMenu));
    InstructionMenuHandler->addItem(std::move(InsertResMenu));
    InstructionMenuHandler->addSeparator();
    InstructionMenuHandler->addItem(std::move(InsertMovMenu));
    InstructionMenuHandler->addItem(std::move(InsertAddMenu));
    InstructionMenuHandler->addItem(std::move(InsertSubMenu));
    InstructionMenuHandler->addItem(std::move(InsertMulMenu));
    InstructionMenuHandler->addItem(std::move(InsertDivMenu));
    InstructionMenuHandler->addSeparator();
    InstructionMenuHandler->addItem(std::move(InsertShiftRegMenu));
    InstructionMenuHandler->addItem(std::move(InsertLutMenu));
    InstructionMenuHandler->addItem(std::move(InsertPwlMenu));
    InstructionMenuHandler->addItem(std::move(InsertFmtdStrMenu));
    InstructionMenuHandler->addSeparator();
    InstructionMenuHandler->addItem(std::move(InsertUartSendMenu));
    InstructionMenuHandler->addItem(std::move(InsertUartRecvMenu));
    InstructionMenuHandler->addItem(std::move(InsertSetPwmMenu));
    InstructionMenuHandler->addItem(std::move(InsertReadAdcMenu));
    InstructionMenuHandler->addItem(std::move(InsertPersistMenu));
    InstructionMenuHandler->addSeparator();
    InstructionMenuHandler->addItem(std::move(MakeNormalMenu));
    InstructionMenuHandler->addItem(std::move(NegateMenu));
    InstructionMenuHandler->addItem(std::move(MakeSetOnlyMenu));
    InstructionMenuHandler->addItem(std::move(MakeResetOnlyMenu));

    InstructionMenu->setMenu(std::move(InstructionMenuHandler));

    // Creating labels for Compile Menu
    CompileMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Compile");
    CompileAsMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Compile As");

    // Appending menu items to Compile menu
    CompileHandler->addItem(std::move(CompileMenu));
    CompileHandler->addItem(std::move(CompileAsMenu));
    Compile->setMenu(std::move(CompileHandler));

    // Creating labels for Help Menu
    ManualMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Manual");
    AboutMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("About");

    // Appending menu items to Help menu
    HelpHandler->addItem(std::move(ManualMenu));
    HelpHandler->addItem(std::move(AboutMenu));
    Help->setMenu(std::move(HelpHandler));

    // Creating labels for Simulation Menu
    SimulationModeMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Simulation Mode");
    StartSimulationMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Start Real-Time Simulation");
    StopSimulationMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Halt Simulation");
    SingleCycleMenu = Wt::cpp14::make_unique<Wt::WMenuItem>("Single Cycle");
    
    // Appending menu items to Simulate menu and adding separators
    SimulateMenuHandler->addItem(std::move(SimulationModeMenu));
    SimulateMenuHandler->addItem(std::move(StartSimulationMenu));
    SimulateMenuHandler->addItem(std::move(StopSimulationMenu));
    SimulateMenuHandler->addItem(std::move(SingleCycleMenu));
    // SimulateMenuHandler->addSeparator();
    SimulateMenu->setMenu(std::move(SimulateMenuHandler));

    // Appending the menu item to the menu bar
    MainMenu->addItem(std::move(FileMenu));
    MainMenu->addItem(std::move(EditMenu));
    MainMenu->addItem(std::move(Settings));
    MainMenu->addItem(std::move(InstructionMenu));
    MainMenu->addItem(std::move(SimulateMenu));
    MainMenu->addItem(std::move(Compile));
    MainMenu->addItem(std::move(Help));
}

void WtMenuBar::MakeMainWindowControls()
{
    
}

//-----------------------------------------------------------------------------
// Adjust the size and visibility of the scrollbars as necessary, either due
// to a change in the size of the program or a change in the size of the
// window.
//-----------------------------------------------------------------------------
/*void RefreshScrollbars(void)
{
}*/

//-----------------------------------------------------------------------------
// Set up the title bar text for the main window; indicate whether we are in
// simulation or editing mode, and indicate the filename.
//-----------------------------------------------------------------------------
void UpdateMainWindowTitleBar(void)
{
    char line[PATH_MAX+100];
    if(InSimulationMode) {
        if(RealTimeSimulationRunning) {
            strcpy(line, "LDmicro - Simulation (Running)");
        } else {
            strcpy(line, "LDmicro - Simulation (Stopped)");
        }
    } else {
        strcpy(line, "LDmicro - Program Editor");
    }
    if(strlen(CurrentSaveFile) > 0) {
        sprintf(line+strlen(line), " - %s", CurrentSaveFile);
    } else {
        strcat(line, " - (not yet saved)");
    }
    
  // gtk_window_set_title (GTK_WINDOW (MainWindow), line);
    // MainWindow->setWindowTitle(line);
}

//-----------------------------------------------------------------------------
// Set the enabled state of the logic menu items to reflect where we are on
// the schematic (e.g. can't insert two coils in series).
//-----------------------------------------------------------------------------
void SetMenusEnabled(BOOL canNegate, BOOL canNormal, BOOL canResetOnly,
    BOOL canSetOnly, BOOL canDelete, BOOL canInsertEnd, BOOL canInsertOther,
    BOOL canPushDown, BOOL canPushUp, BOOL canInsertComment)
{
    /*EnableMenuItem(EditMenu, PushRungUpMenu,
        canPushUp ? MF_ENABLED : MF_GRAYED);
    EnableMenuItem(EditMenu, PushRungDownMenu,
        canPushDown ? MF_ENABLED : MF_GRAYED);
    EnableMenuItem(EditMenu, DeleteRungMenu,
        (Prog.numRungs > 1) ? MF_ENABLED : MF_GRAYED);

    EnableMenuItem(InstructionMenu, NegateMenu,
        canNegate ? MF_ENABLED : MF_GRAYED);
    EnableMenuItem(InstructionMenu, MakeNormalMenu,
        canNormal ? MF_ENABLED : MF_GRAYED);
    EnableMenuItem(InstructionMenu, MakeResetOnlyMenu,
        canResetOnly ? MF_ENABLED : MF_GRAYED);
    EnableMenuItem(InstructionMenu, MakeSetOnlyMenu,
        canSetOnly ? MF_ENABLED : MF_GRAYED);

    EnableMenuItem(InstructionMenu, InsertCommentMenu,
        canInsertComment ? MF_ENABLED : MF_GRAYED);

    EnableMenuItem(EditMenu, DeleteElementMenu,
        canDelete ? MF_ENABLED : MF_GRAYED);

    int t;
    t = canInsertEnd ? MF_ENABLED : MF_GRAYED;
    EnableMenuItem(InstructionMenu, InsertCoilMenu, t);
    EnableMenuItem(InstructionMenu, InsertResMenu, t);
    EnableMenuItem(InstructionMenu, InsertMovMenu, t);
    EnableMenuItem(InstructionMenu, ArithmeticMenu, t);
    EnableMenuItem(InstructionMenu, InsertAddMenu, t);
    EnableMenuItem(InstructionMenu, InsertSubMenu, t);
    EnableMenuItem(InstructionMenu, InsertMulMenu, t);
    EnableMenuItem(InstructionMenu, InsertDivMenu, t);
    EnableMenuItem(InstructionMenu, InsertCtcMenu, t);
    EnableMenuItem(InstructionMenu, InsertPersistMenu, t);
    EnableMenuItem(InstructionMenu, AnalogMenu, t);
    EnableMenuItem(InstructionMenu, InsertReadAdcMenu, t);
    EnableMenuItem(InstructionMenu, InsertSetPwmMenu, t);
    EnableMenuItem(InstructionMenu, InsertMasterRlyMenu, t);
    EnableMenuItem(InstructionMenu, InsertShiftRegMenu, t);
    EnableMenuItem(InstructionMenu, InsertLutMenu, t);
    EnableMenuItem(InstructionMenu, InsertPwlMenu, t);

    // Disable tool buttons along with menus
    EnableMenuItem(NULL, CoilBtn, t);
    EnableMenuItem(NULL, NegCoilBtn, t);
    EnableMenuItem(NULL, SetCoilBtn, t);
    EnableMenuItem(NULL, ResetCoilBtn, t);
    EnableMenuItem(NULL, AddBtn, t);
    EnableMenuItem(NULL, SubBtn, t);
    EnableMenuItem(NULL, MulBtn, t);
    EnableMenuItem(NULL, DivBtn, t);

    t = canInsertOther ? MF_ENABLED : MF_GRAYED;
    EnableMenuItem(InstructionMenu, InsertTonMenu, t);
    EnableMenuItem(InstructionMenu, InsertTofMenu, t);
    EnableMenuItem(InstructionMenu, InsertOsrMenu, t);
    EnableMenuItem(InstructionMenu, InsertOsfMenu, t);
    EnableMenuItem(InstructionMenu, InsertRtoMenu, t);
    EnableMenuItem(InstructionMenu, InsertContactsMenu, t);
    EnableMenuItem(InstructionMenu, InsertCtuMenu, t);
    EnableMenuItem(InstructionMenu, InsertCtdMenu, t);
    EnableMenuItem(InstructionMenu, InsertEquMenu, t);
    EnableMenuItem(InstructionMenu, InsertNeqMenu, t);
    EnableMenuItem(InstructionMenu, InsertGrtMenu, t);
    EnableMenuItem(InstructionMenu, InsertGeqMenu, t);
    EnableMenuItem(InstructionMenu, InsertLesMenu, t);
    EnableMenuItem(InstructionMenu, InsertLeqMenu, t);
    EnableMenuItem(InstructionMenu, InsertShortMenu, t);
    EnableMenuItem(InstructionMenu, InsertOpenMenu, t);
    EnableMenuItem(InstructionMenu, InsertUartSendMenu, t);
    EnableMenuItem(InstructionMenu, InsertUartRecvMenu, t);
    EnableMenuItem(InstructionMenu, InsertFmtdStrMenu, t);

    //Disable respective tool items
    EnableMenuItem(NULL, ContactBtn, t);
    EnableMenuItem(NULL, NegContactBtn, t);
    EnableMenuItem(NULL, TonBtn, t);
    EnableMenuItem(NULL, TofBtn, t);
    EnableMenuItem(NULL, CtuBtn, t);
    EnableMenuItem(NULL, CtdBtn, t);*/
}

//-----------------------------------------------------------------------------
// Set the enabled state of the undo/redo menus.
//-----------------------------------------------------------------------------
void SetUndoEnabled(BOOL undoEnabled, BOOL redoEnabled)
{
    /*EnableMenuItem(EditMenu, UndoMenu, undoEnabled ? MF_ENABLED : MF_GRAYED);
    EnableMenuItem(EditMenu, RedoMenu, redoEnabled ? MF_ENABLED : MF_GRAYED);*/
}

//-----------------------------------------------------------------------------
// Toggle whether we are in simulation mode. A lot of options are only
// available in one mode or the other.
//-----------------------------------------------------------------------------
void ToggleSimulationMode(void)
{}

//-----------------------------------------------------------------------------
// Cause the status bar and the list view to be in sync with the actual data
// structures describing the settings and the I/O configuration. Listview
// does callbacks to get the strings it displays, so it just needs to know
// how many elements to populate.
//-----------------------------------------------------------------------------
void RefreshControlsToSettings(void)
{
    /*QTreeWidgetItem iter;
    QTreeWidgetItem* selection;
    if(!IoListOutOfSync) {
        selection = IoList->currentItem();
        IoListSelectionPoint =IoList->indexOfTopLevelItem(selection);
    }
    NMHDR h;
    h.code = LVN_GETDISPINFO;
    h.hlistFrom = IoList;
    IoList->clear();
    h.hlistIter.clear();
    for(int i = 0; i < Prog.io.count; i++) {
        h.item.iItem = i;
        IoListProc(&h);
    }
    IoList->insertTopLevelItems(0, h.hlistIter);
    if(IoListSelectionPoint >= 0)
    {
        IoList->setCurrentItem(IoList->topLevelItem(IoListSelectionPoint));
    }

    if(Prog.mcu) {
        StatusBar[0]->setText(Prog.mcu->mcuName);
    } 
    else {
        StatusBar[0]->setText("no MCU selected");
    }
    char buf[256];
    sprintf(buf, _("cycle time %.2f ms"), (double)Prog.cycleTime/1000.0);
    StatusBar[1]->setText(buf);

    if(Prog.mcu && (Prog.mcu->whichIsa == ISA_ANSIC ||
        Prog.mcu->whichIsa == ISA_INTERPRETED))
    {
        strcpy(buf, "");
    } else {
        sprintf(buf, _("processor clock %.4f MHz"),
            (double)Prog.mcuClock/1000000.0);
    }
    StatusBar[2]->setText(buf);


    for(int i = 0; i < NUM_SUPPORTED_MCUS; i++) {
        if(&SupportedMcus[i] == Prog.mcu) {
            CheckMenuItem(ProcessorMenu, ProcessorMenuItems[i], MF_CHECKED);
        }
        else {
            CheckMenuItem(ProcessorMenu, ProcessorMenuItems[i], MF_UNCHECKED);
        }
    }
    // `(no microcontroller)' setting
    if (!Prog.mcu){
        CheckMenuItem(ProcessorMenu,
            ProcessorMenuItems[NUM_SUPPORTED_MCUS], MF_CHECKED);
    }
    else {
        CheckMenuItem(ProcessorMenu,
            ProcessorMenuItems[NUM_SUPPORTED_MCUS], MF_UNCHECKED);
    }*/
}

//-----------------------------------------------------------------------------
// Regenerate the I/O list, keeping the selection in the same place if
// possible.
//-----------------------------------------------------------------------------
void GenerateIoListDontLoseSelection(void)
{
/*    QTreeWidgetItem* selection;
    selection = IoList->currentItem();
    IoListSelectionPoint =IoList->indexOfTopLevelItem(selection);
    IoListSelectionPoint = GenerateIoList(IoListSelectionPoint);
    
    // can't just update the listview index; if I/O has been added then the
    // new selection point might be out of range till we refill it
    IoListOutOfSync = TRUE;
*/    RefreshControlsToSettings();
}

//-----------------------------------------------------------------------------
// Called when the main window has been resized. Adjust the size of the
// status bar and the listview to reflect the new window size.
//-----------------------------------------------------------------------------
void MainWindowResized(void)
{
    // IoListTop = DrawWindow->height();

}

//-----------------------------------------------------------------------------
// Start real-time simulation. Have to update the controls grayed status
// to reflect this.
//-----------------------------------------------------------------------------
void StartSimulation(void)
{
    RealTimeSimulationRunning = TRUE;
    // EnableMenuItem(SimulateMenu, StartSimulationMenu, MF_GRAYED);
    // EnableMenuItem(SimulateMenu, StopSimulationMenu, MF_ENABLED);
    // StartSimulationTimer();
    UpdateMainWindowTitleBar();
}

//-----------------------------------------------------------------------------
// Stop real-time simulation. Have to update the controls grayed status
// to reflect this.
//-----------------------------------------------------------------------------
void StopSimulation(void)
{
    RealTimeSimulationRunning = FALSE;

    // EnableMenuItem(SimulateMenu, StartSimulationMenu, MF_ENABLED);
    // EnableMenuItem(SimulateMenu, StopSimulationMenu, MF_GRAYED);
    // KillTimer(DrawWindow, TIMER_SIMULATE);
    
    UpdateMainWindowTitleBar();
}



