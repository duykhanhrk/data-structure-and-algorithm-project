
#include "invoice.h"
bool IVPAddButtonConsole(keycode_tp c) {
  return (c == KEY_LEFT || c == KEY_DOWN || c == ENTER || c == BACKSPACE);
}

void IVPRecovery(Frame frame) {
  DrawRecShape(
    IVP_INVOICE_LIST_ITEM_WIDTH, 3, ' ',
    frame->position_x + 2, frame->position_y + 1,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );

  DrawRecShape(
    IVP_INVOICE_LIST_ITEM_WIDTH, WINDOW_ROWS - 6, ' ',
    frame->position_x + 2, frame->position_y + 5,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
}

void ActiveInvoiceFrame(Frame frame) {
  // Button
  Button add_button = NewButton(
    " Thêm", ALIGN_CENTER,
    IVP_ADD_BUTTON_WIDTH, IVP_ADD_BUTTON_HEIGHT, 0,
    frame->position_x + 2, frame->position_y + 1,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    IVPAddButtonConsole
  );

  // Invoice list view
  ListViewScroll list_view_scroll = NewListViewScroll(
    STAFF_LIST_IN_ARCHIVE, // data
    0, 4, // page, fields count
    CountInvoicesInArchive, // items count
    TakeInvoicesInArchive, // take items
    IVP_INVOICE_LIST_WIDTH, IVP_INVOICE_LIST_HEIGHT,
    frame->position_x + 2, frame->position_y + 5,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    IVP_INVOICE_LIST_ITEM_WIDTH, IVP_INVOICE_LIST_ITEM_HEIGHT,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    RENDER_LIST_VIEW_ITEM_WITH_DATA_AS_INVOICE,
    ACTIVE_LIST_VIEW_ITEM_WITH_DATA_AS_INVOICE,
    LIST_VIEW_SCROLL_EB_CONSOLE,
    0
  );

  AddFieldForListViewScroll(list_view_scroll, "Số", 10);
  AddFieldForListViewScroll(list_view_scroll, "Ngày lập", 12);
  AddFieldForListViewScroll(list_view_scroll, "Người lập", 54);
  AddFieldForListViewScroll(list_view_scroll, "Trị giá", 10);

  // creation
  Frame creation_frame = NewFrame(
    IVP_CREATION_FORM_WIDTH, IVP_CREATION_FORM_HEIGHT,
    frame->position_x + (frame->width - IVP_CREATION_FORM_WIDTH) / 2,
    frame->position_y + (frame->height - IVP_CREATION_FORM_HEIGHT) / 2
  );

  // updated
  Frame updated_frame = NewFrame(
    IVP_UPDATED_FORM_WIDTH, IVP_UPDATED_FORM_HEIGHT,
    frame->position_x + (frame->width - IVP_UPDATED_FORM_WIDTH) / 2,
    frame->position_y + (frame->height - IVP_UPDATED_FORM_HEIGHT) / 2
  );

  RenderButton(add_button);
  RenderListViewScroll(list_view_scroll);

  // Active
  Invoice invoice;
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      // Add button
      keycode = ActiveButton(add_button);
      if (keycode == KEY_LEFT) {
        frame->active_element = 0;
      } else if (keycode == KEY_DOWN)
        frame->active_element = 2;
      else if (keycode == ENTER) {
//         creation_frame->active_element = 1;
//         IVPRecovery(frame);
//         ActiveInvoiceCreationFrame(creation_frame);
//         RenderButton(add_button);
//         RenderListViewScroll(list_view_scroll);
//         frame->active_element = 1;
      } else if (keycode == BACKSPACE) {
         frame->active_element = 0;
      }
    } else if (frame->active_element == 2) {
      // List
      keycode = ActiveListViewScroll(list_view_scroll);
      if (keycode == ENTER) {
//         updated_frame->active_element = 2;
//         IVPRecovery(frame);
//         invoice = (Invoice) GetItemInLinearListByIndex(
//           list_view_scroll->list_view->linear_list,
//           list_view_scroll->list_view->selected_item
//         );
//         if (invoice == NULL) continue;
//         ActiveInvoiceUpdatedFrame(updated_frame, invoice);
//         RenderButton(add_button);
//         RenderListViewScroll(list_view_scroll);
//         frame->active_element = 2;
      } else if (keycode == BACKSPACE) {
        frame->active_element = 1;
      } else if (keycode == KEY_UP) {
        frame->active_element = 1;
      } else if (keycode == NULL_KEY) {
        frame->active_element = 1;
      }
    }
  }

  // Release
  DestroyButton(add_button);
  DestroyListViewScroll(list_view_scroll);
  DestroyFrame(creation_frame);
  DestroyFrame(updated_frame);

  // Recovery
  IVPRecovery(frame);
}
