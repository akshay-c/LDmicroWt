#ifndef __IOLIST_H
#define __IOLIST_H
#include <Wt/WTable.h>
#include <Wt/WLength.h>
#include <Wt/WLabel.h>
#include <Wt/WWebWidget.h>
#include <Wt/WString.h>
#include "miscutil.h"

class WtIolist : public Wt::WTable
{
    std::vector<std::string> ColumnNames{"Name",
            "Type",
            "State",
            "Pin on Processor",
            "MCU Port"};
public:
    WtIolist(/*int columns*/);
    // void RedrawItems(int min, int max);
    std::vector<std::unique_ptr<Wt::WStandardItem>> MakeRow(
        std::vector<std::string> data);

private:
    int rows_, columns_;
    void ClickEvent(Wt::WString label);
};

int  GenerateIoList(int prevSel);
void SaveIoListToFile(FILE *f);
BOOL LoadIoListFromFile(FILE *f);
void ShowIoDialog(int item);
// void IoListProc(NMHDR *h);
void ShowAnalogSliderPopup(char *name);

#endif