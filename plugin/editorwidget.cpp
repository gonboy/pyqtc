/* This file is part of Clementine.
   Copyright 2011, David Sansome <me@davidsansome.com>
   
   Clementine is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   Clementine is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with Clementine.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "constants.h"
#include "editorwidget.h"

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/icore.h>
#include <texteditor/texteditorconstants.h>

namespace pyqtc {

Editor::Editor(EditorWidget* editor)
  : TextEditor::PlainTextEditor(editor)
{
  setContext(Core::Context(constants::kEditorId,
                           constants::kPythonLanguage,
                           TextEditor::Constants::C_TEXTEDITOR));
}

Core::Id Editor::id() const {
  return constants::kEditorId;
}


EditorWidget::EditorWidget(QWidget* parent)
  : TextEditor::PlainTextEditorWidget(parent)
{
  setMimeType(QLatin1String(constants::kPythonMimetype));
  setDisplayName(tr(constants::kEditorDisplayName));

  comment_definition_.setAfterWhiteSpaces(false);
  comment_definition_.setSingleLine("#");
  comment_definition_.setMultiLineStart("'''");
  comment_definition_.setMultiLineEnd("'''");
}

void EditorWidget::unCommentSelection() {
  Utils::unCommentSelection(this, comment_definition_);
}

void EditorWidget::contextMenuEvent(QContextMenuEvent* e) {
  QScopedPointer<QMenu> menu(new QMenu);

  Core::ActionManager* am = Core::ICore::instance()->actionManager();
  Core::ActionContainer* mcontext = am->actionContainer(constants::kMenuContext);

  menu->addActions(mcontext->menu()->actions());
  appendStandardContextMenuActions(menu.data());

  menu->exec(e->globalPos());
}


} // namespace pyqtc
