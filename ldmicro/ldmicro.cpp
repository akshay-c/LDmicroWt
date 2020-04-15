#include "ldmicro.h"
#include "iolist.h"
#include "mcutable.h"

std::unique_ptr<WtMenuBar>  MenuBar;
std::unique_ptr<WtIolist>   Iolist;
std::unique_ptr<Wt::WVBoxLayout> PackBoxMenu;

// ProgramSlots MenuHandle;

// For the open/save dialog boxes
#define LDMICRO_PATTERN "LDmicro Ladder Logic Programs (*.ld)\0*.ld\0" \
                     "All files\0*\0\0"
char CurrentSaveFile[MAX_PATH];
static BOOL ProgramChangedNotSaved = FALSE;

#define HEX_PATTERN  "Intel Hex Files (*.hex)\0*.hex\0All files\0*\0\0"
#define C_PATTERN "C Source Files (*.c)\0*.c\0All Files\0*\0\0"
#define INTERPRETED_PATTERN \
    "Interpretable Byte Code Files (*.int)\0*.int\0All Files\0*\0\0"
char CurrentCompileFile[MAX_PATH];

#define TXT_PATTERN  "Text Files (*.txt)\0*.txt\0All files\0*\0\0"

// Everything relating to the PLC's program, I/O configuration, processor
// choice, and so on--basically everything that would be saved in the
// project file.
PlcProgram Prog;

PaintWidget*             DrawWindow;

WtMain::WtMain(const Wt::WEnvironment& env) : 
    Wt::WApplication(env)
{
	setTitle("LDmicro");
	useStyleSheet("resources/themes/bootstrap/3/bootstrap-theme.min.css");
    auto bootstrapTheme = std::make_shared<Wt::WBootstrapTheme>();
    bootstrapTheme->setVersion(Wt::BootstrapVersion::v3);
    bootstrapTheme->setResponsive(true);
    setTheme(bootstrapTheme);
    useStyleSheet("style/everywidget.css");
    useStyleSheet("style/dragdrop.css");
    useStyleSheet("style/combostyle.css");
    useStyleSheet("style/pygments.css");
    useStyleSheet("style/layout.css");
    useStyleSheet("style/filedrop.css");
    useStyleSheet("resources/themes/default/wt.css");
    //MenuBar = root()->addNew<Wt::WNavigationBar>();
    //->addWidget(std::move(MenuBar));Wt::cpp14::make_unique<Wt::WNavigationBar>();
    MenuBar = std::move(Wt::cpp14::make_unique<WtMenuBar>());
    MenuBar->addStyleClass("main-nav");
    MenuBar->setResponsive(true);
    PackBoxMenu = Wt::cpp14::make_unique<Wt::WVBoxLayout>();
    PackBoxMenu->addWidget(std::move(MenuBar));

    auto DrawWndContainer = Wt::cpp14::make_unique<Wt::WContainerWidget>();
    DrawWndContainer->setMinimumSize(Wt::WLength(100, Wt::LengthUnit::Percentage),
        Wt::WLength(70, Wt::LengthUnit::Percentage));
    DrawWndContainer->addNew<PaintWidget>();
    PackBoxMenu->addWidget(std::move(DrawWndContainer));

    // Iolist->addStyleClass("tcontainer");
    // Iolist->setStyleClass("Wt-itemview Wt-tableview");
    // Iolist->setAttributeValue("style", "table-layout: fixed;");
    auto IolistContainer = Wt::cpp14::make_unique<Wt::WContainerWidget>();
    IolistContainer->setMinimumSize(Wt::WLength(100, Wt::LengthUnit::Percentage),
        Wt::WLength(2, Wt::LengthUnit::Percentage));
    IolistContainer->addNew<WtIolist>();
    PackBoxMenu->addWidget(std::move(IolistContainer));
    
    root()->setLayout(std::move(PackBoxMenu));
}

int main(int argc, char** argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
      return std::make_unique<WtMain>(env);
    });
}