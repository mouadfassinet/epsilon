#ifndef APPS_VARIABLE_BOX_CONTROLLER_H
#define APPS_VARIABLE_BOX_CONTROLLER_H

#include <escher.h>
#include <poincare.h>
#include "variable_box_leaf_cell.h"

class VariableBoxController : public StackViewController {
public:
  VariableBoxController(Context * context);
  void didBecomeFirstResponder() override;
  void setTextFieldCaller(TextField * textField);
private:
  class ContentViewController : public ViewController, public ListViewDataSource {
  public:
    ContentViewController(Responder * parentResponder, Context * context);
    View * view() override;
    const char * title() const override;
    void didBecomeFirstResponder() override;
    bool handleEvent(Ion::Events::Event event) override;
    int numberOfRows() override;
    TableViewCell * reusableCell(int index, int type) override;
    int reusableCellCount(int type) override;
    void willDisplayCellForIndex(TableViewCell * cell, int index) override;
    KDCoordinate rowHeight(int j) override;
    KDCoordinate cumulatedHeightFromIndex(int j) override;
    int indexFromCumulatedHeight(KDCoordinate offsetY) override;
    int typeAtLocation(int i, int j) override;
    void setTextFieldCaller(TextField * textField);
  private:
    enum class Page {
      RootMenu,
      Scalar,
      List,
      Matrix
    };
    constexpr static int k_maxNumberOfDisplayedRows = 6; //240/40
    constexpr static int k_numberOfMenuRows = 3; //240/40
    constexpr static KDCoordinate k_leafRowHeight = 40;
    constexpr static KDCoordinate k_nodeRowHeight = 40;
    Page pageAtIndex(int index);
    void putLabelAtIndexInBuffer(int index, char * buffer);
    const char * nodeLabelAtIndex(int index);
    const Expression * expressionForIndex(int index);

    Context * m_context;
    TextField * m_textFieldCaller;
    int m_firstSelectedRow;
    int m_previousSelectedRow;
    Page m_currentPage;
    VariableBoxLeafCell m_leafCells[k_maxNumberOfDisplayedRows];
    ChevronMenuListCell m_nodeCells[k_numberOfMenuRows];
    SelectableTableView m_selectableTableView;
  };
  ContentViewController m_contentViewController;
};

#endif