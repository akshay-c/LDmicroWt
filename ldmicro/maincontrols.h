#ifndef __MAINCONTROLS_H
#define __MAINCONTROLS_H

#include <Wt/WApplication.h>
#include <Wt/WNavigationBar.h>

#define NUM_SUPPORTED_MCUS  16

class WtMenuBar : public Wt::WNavigationBar
{
    public:

        WtMenuBar();

    protected:
        std::unique_ptr<Wt::WMenuItem>      FileMenu;
        std::unique_ptr<Wt::WMenuItem>      EditMenu;
        std::unique_ptr<Wt::WMenuItem>      InstructionMenu;
        std::unique_ptr<Wt::WMenuItem>      ProcessorMenu;
        std::unique_ptr<Wt::WMenuItem>      SimulateMenu;
        std::unique_ptr<Wt::WMenuItem>      Settings;
        std::unique_ptr<Wt::WMenuItem>      Compile;
        std::unique_ptr<Wt::WMenuItem>      Help;

        std::unique_ptr<Wt::WMenuItem> NewMenu;
        std::unique_ptr<Wt::WMenuItem> OpenMenu;
        std::unique_ptr<Wt::WMenuItem> SaveMenu;
        std::unique_ptr<Wt::WMenuItem> SaveAsMenu;
        std::unique_ptr<Wt::WMenuItem> ExportMenu;
        std::unique_ptr<Wt::WMenuItem> ExitMenu;
        std::unique_ptr<Wt::WMenuItem> UndoMenu;
        std::unique_ptr<Wt::WMenuItem> RedoMenu;
        std::unique_ptr<Wt::WMenuItem> PushRungUpMenu;
        std::unique_ptr<Wt::WMenuItem> PushRungDownMenu;
        std::unique_ptr<Wt::WMenuItem> InsertRungBeforeMenu;
        std::unique_ptr<Wt::WMenuItem> InsertRungAfterMenu;
        std::unique_ptr<Wt::WMenuItem> DeleteElementMenu;
        std::unique_ptr<Wt::WMenuItem> DeleteRungMenu;
        std::unique_ptr<Wt::WMenuItem> InsertCommentMenu;
        std::unique_ptr<Wt::WMenuItem> InsertContactsMenu;
        std::unique_ptr<Wt::WMenuItem> InsertCoilMenu;
        std::unique_ptr<Wt::WMenuItem> InsertTonMenu;
        std::unique_ptr<Wt::WMenuItem> InsertTofMenu;
        std::unique_ptr<Wt::WMenuItem> InsertRtoMenu;
        std::unique_ptr<Wt::WMenuItem> InsertResMenu;
        std::unique_ptr<Wt::WMenuItem> InsertOsrMenu;
        std::unique_ptr<Wt::WMenuItem> InsertOsfMenu;
        std::unique_ptr<Wt::WMenuItem> InsertCtuMenu;
        std::unique_ptr<Wt::WMenuItem> InsertCtdMenu;
        std::unique_ptr<Wt::WMenuItem> InsertCtcMenu;
        std::unique_ptr<Wt::WMenuItem> InsertAddMenu;
        std::unique_ptr<Wt::WMenuItem> InsertSubMenu;
        std::unique_ptr<Wt::WMenuItem> InsertMulMenu;
        std::unique_ptr<Wt::WMenuItem> InsertDivMenu;
        std::unique_ptr<Wt::WMenuItem> InsertMovMenu;
        std::unique_ptr<Wt::WMenuItem> InsertReadAdcMenu;
        std::unique_ptr<Wt::WMenuItem> InsertSetPwmMenu;
        std::unique_ptr<Wt::WMenuItem> InsertUartSendMenu;
        std::unique_ptr<Wt::WMenuItem> InsertUartRecvMenu;
        std::unique_ptr<Wt::WMenuItem> InsertEquMenu;
        std::unique_ptr<Wt::WMenuItem> InsertNeqMenu;
        std::unique_ptr<Wt::WMenuItem> InsertGrtMenu;
        std::unique_ptr<Wt::WMenuItem> InsertGeqMenu;
        std::unique_ptr<Wt::WMenuItem> InsertLesMenu;
        std::unique_ptr<Wt::WMenuItem> InsertLeqMenu;
        std::unique_ptr<Wt::WMenuItem> InsertOpenMenu;
        std::unique_ptr<Wt::WMenuItem> InsertShortMenu;
        std::unique_ptr<Wt::WMenuItem> InsertMasterRlyMenu;
        std::unique_ptr<Wt::WMenuItem> InsertShiftRegMenu;
        std::unique_ptr<Wt::WMenuItem> InsertLutMenu;
        std::unique_ptr<Wt::WMenuItem> InsertFmtdStrMenu;
        std::unique_ptr<Wt::WMenuItem> InsertPersistMenu;
        std::unique_ptr<Wt::WMenuItem> MakeNormalMenu;
        std::unique_ptr<Wt::WMenuItem> NegateMenu;
        std::unique_ptr<Wt::WMenuItem> MakeSetOnlyMenu;
        std::unique_ptr<Wt::WMenuItem> MakeResetOnlyMenu;
        std::unique_ptr<Wt::WMenuItem> InsertPwlMenu;
        std::unique_ptr<Wt::WMenuItem> McuSettingsMenu;
        std::unique_ptr<Wt::WMenuItem> ProcessorMenuItems[NUM_SUPPORTED_MCUS+1];
        std::unique_ptr<Wt::WMenuItem> MicroControllerMenu;                                         // Item for Microcontroller
        
        std::unique_ptr<Wt::WMenuItem> SimulationModeMenu;
        std::unique_ptr<Wt::WMenuItem> StartSimulationMenu;
        std::unique_ptr<Wt::WMenuItem> StopSimulationMenu;
        std::unique_ptr<Wt::WMenuItem> SingleCycleMenu;
        std::unique_ptr<Wt::WMenuItem> CompileMenu;
        std::unique_ptr<Wt::WMenuItem> CompileAsMenu;
        std::unique_ptr<Wt::WMenuItem> ManualMenu;
        std::unique_ptr<Wt::WMenuItem> AboutMenu;
        
        //QActionGroup* ProcessorMenuGroup;
        
        
        std::unique_ptr<Wt::WPopupMenu> FileMenuHandler;
        std::unique_ptr<Wt::WPopupMenu> EditMenuHandler;
        std::unique_ptr<Wt::WPopupMenu> SettingsHandler;
        std::unique_ptr<Wt::WPopupMenu> ProcessorMenuHandler;
        std::unique_ptr<Wt::WPopupMenu> InstructionMenuHandler;
        std::unique_ptr<Wt::WPopupMenu> SimulateMenuHandler;
        std::unique_ptr<Wt::WPopupMenu> CompileHandler;
        std::unique_ptr<Wt::WPopupMenu> HelpHandler;
        
        std::unique_ptr<Wt::WMenu> MainMenu;

        void MakeMainWindowMenus();
        void MakeMainWindowControls();
    };
    void ToggleSimulationMode(void);
    void VscrollProc(int wParam);
    void HscrollProc(int wParam);
    void GenerateIoListDontLoseSelection(void);
    void RefreshControlsToSettings(void);
    void MainWindowResized(void);
    void StopSimulation(void);
    void StartSimulation(void);
    void UpdateMainWindowTitleBar(void);

    #endif