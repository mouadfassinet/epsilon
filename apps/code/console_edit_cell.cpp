#include "console_edit_cell.h"
#include "console_controller.h"
#include <escher/app.h>
#include <apps/i18n.h>
#include <assert.h>

namespace Code {

ConsoleEditCell::ConsoleEditCell(Responder * parentResponder, TextFieldDelegate * delegate) :
  HighlightCell(),
  Responder(parentResponder),
  m_textBuffer{0},
  m_promptView(ConsoleController::k_fontSize, I18n::Message::ConsolePrompt, 0, 0.5),
  m_textField(this, m_textBuffer, m_textBuffer, TextField::maxBufferSize(), delegate, false, ConsoleController::k_fontSize)
{
}

int ConsoleEditCell::numberOfSubviews() const {
  return 2;
}

View * ConsoleEditCell::subviewAtIndex(int index) {
  assert(index == 0 || index ==1);
  if (index == 0) {
   return &m_promptView;
  } else {
   return &m_textField;
  }
}

void ConsoleEditCell::layoutSubviews() {
  KDSize chevronsSize = KDText::stringSize(I18n::translate(I18n::Message::ConsolePrompt), ConsoleController::k_fontSize);
  m_promptView.setFrame(KDRect(KDPointZero, chevronsSize.width(), bounds().height()));
  m_textField.setFrame(KDRect(KDPoint(chevronsSize.width(), KDCoordinate(0)), bounds().width() - chevronsSize.width(), bounds().height()));
}

void ConsoleEditCell::didBecomeFirstResponder() {
  app()->setFirstResponder(&m_textField);
}

void ConsoleEditCell::setEditing(bool isEditing,  bool reinitDraftBuffer) {
  m_textField.setEditing(isEditing, reinitDraftBuffer);
}

void ConsoleEditCell::setText(const char * text) {
  m_textField.setText(text);
}

bool ConsoleEditCell::insertText(const char * text) {
  bool didCopy = m_textField.insertTextAtLocation(text, m_textField.cursorLocation());
  if (didCopy) {
    m_textField.setCursorLocation(m_textField.cursorLocation() + strlen(text));
  }
  return didCopy;
}
}
