#include "invoice_detail.h"

bool IDPAddButtonConsole(keycode_tp c) {
  return (c == KEY_LEFT || c == KEY_DOWN || c == ENTER || c == BACKSPACE);
}

void IDPRecovery(Frame frame) {
  DrawRecShape(
    IDP_INVOICE_DETAIL_LIST_ITEM_WIDTH, 3, ' ',
    frame->position_x + 2, frame->position_y + 1,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );

  DrawRecShape(
    IDP_INVOICE_DETAIL_LIST_ITEM_WIDTH, WINDOW_ROWS - 6, ' ',
    frame->position_x + 2, frame->position_y + 5,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
}

void ActiveInvoiceDetailFrame(Frame frame, InvoiceDetailList invoice_detail_list, char invoice_type) {
  // Varialbe
  InvoiceDetail invoice_detail;

  // Button
  Button add_button = NewButton(
    "Thêm", ALIGN_CENTER,
    IDP_ADD_BUTTON_WIDTH, IDP_ADD_BUTTON_HEIGHT, 0,
    frame->position_x + 2, frame->position_y + 1,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    IDPAddButtonConsole
  );

  // Material list view
  ListViewScroll list_view_scroll = NewListViewScroll(
    invoice_detail_list, // data
    NULL, // filter
    0, 4, // page, fields count
    CountInvoiceDetails, // items count
    TakeInvoiceDetails, // take items
    IDP_INVOICE_DETAIL_LIST_WIDTH, IDP_INVOICE_DETAIL_LIST_HEIGHT,
    frame->position_x + 2, frame->position_y + 5,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    IDP_INVOICE_DETAIL_LIST_ITEM_WIDTH, IDP_INVOICE_DETAIL_LIST_ITEM_HEIGHT,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    RENDER_LIST_VIEW_ITEM_WITH_DATA_AS_INVOICE_DETAIL,
    ACTIVE_LIST_VIEW_ITEM_WITH_DATA_AS_INVOICE_DETAIL,
    LIST_VIEW_SCROLL_EB_CONSOLE,
    0
  );

  AddFieldForListViewScroll(list_view_scroll, "Mã vật tư", 10);
  AddFieldForListViewScroll(list_view_scroll, "Số lượng", 32);
  AddFieldForListViewScroll(list_view_scroll, "Giá bán", 32);
  AddFieldForListViewScroll(list_view_scroll, "VAT", 12);

  // creation
  Frame creation_form = NewFrame(
    IDP_CREATION_FORM_WIDTH, IDP_CREATION_FORM_HEIGHT,
    frame->position_x + (frame->width - IDP_CREATION_FORM_WIDTH) / 2,
    frame->position_y + (frame->height - IDP_CREATION_FORM_HEIGHT) / 2
  );

  // updated
  Frame updated_form = NewFrame(
    IDP_UPDATED_FORM_WIDTH, IDP_UPDATED_FORM_HEIGHT,
    frame->position_x + (frame->width - IDP_UPDATED_FORM_WIDTH) / 2,
    frame->position_y + (frame->height - IDP_UPDATED_FORM_HEIGHT) / 2
  );

  // Render

  RenderButton(add_button);
  RenderListViewScroll(list_view_scroll);

  // Active
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
        creation_form->active_element = 1;
        IDPRecovery(frame);
        ActiveInvoiceDetailCreationFrame(creation_form, invoice_detail_list, invoice_type);
        RenderButton(add_button);
        RenderListViewScroll(list_view_scroll);
        frame->active_element = 1;
      } else if (keycode == BACKSPACE) {
         frame->active_element = 0;
      }
    } else if (frame->active_element == 2) {
      // List
      keycode = ActiveListViewScroll(list_view_scroll);
      if (keycode == ENTER) {
        IDPRecovery(frame);
        invoice_detail = (InvoiceDetail) GetSelectedItemInListViewScroll(list_view_scroll);
        if (invoice_detail == NULL) continue;
        ActiveInvoiceDetailUpdatedFrame(
          updated_form,
          invoice_detail_list,
          invoice_type,
          invoice_detail
        );
        RenderButton(add_button);
        RenderListViewScroll(list_view_scroll);
        frame->active_element = 2;
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
  DestroyFrame(creation_form);
  DestroyFrame(updated_form);

  // Recovery
  IDPRecovery(frame);
}
