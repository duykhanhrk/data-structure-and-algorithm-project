#include "invoice.h"

// Rapid - ivp
#define ivp_render_invoice_frame IVPRenderInvoiceFrame(\
                                   add_button,\
                                   edit_query,\
                                   edit_from,\
                                   edit_to,\
                                   filter_button,\
                                   list_view_scroll\
                                 )

bool IVPAddButtonConsole(keycode_tp c) {
  return (c == KEY_LEFT || c == KEY_RIGHT || c == KEY_DOWN || c == ENTER || c == BACKSPACE);
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

void IVPRenderInvoiceFrame(
  Button add_button,
  EditStr edit_query,
  EditDateTime edit_from,
  EditDateTime edit_to,
  Button filter_button,
  ListViewScroll list_view_scroll
) {
  RenderButton(add_button);
  RenderEditStr(edit_query);
  RenderEditDateTime(edit_from);
  RenderEditDateTime(edit_to);
  RenderButton(filter_button);
  RenderListViewScroll(list_view_scroll);
}

void ActiveInvoiceFrame(Frame frame) {
  // Variable
  LinearList linear_list;
  Invoice invoice;
  char query[33];
  strcpy(query, "\0");
  time_t from_date = 1388534400;
  time_t to_date = TimeNow();

  // Init templates
  Button add_button = NewButton(
    " Thêm", ALIGN_CENTER,
    IVP_BUTTON_WIDTH, IVP_BUTTON_HEIGHT, 0,
    frame->position_x + 2, frame->position_y + 1,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    IVPAddButtonConsole
  );

  EditStr edit_query = NewEditStr(
    query,
    32, 0,
    IVP_BUTTON_WIDTH, IVP_BUTTON_HEIGHT,
    frame->position_x + 51, frame->position_y + 1,
    EDIT_STR_FOREGROUND, PROGRAM_THEME_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND,
    CODE_FORMAT_CHAR_SET
  );

  EditDateTime edit_from = NewEditDateTime(
    &(from_date),
    to_date, from_date,
    36, 3,
    frame->position_x + 2, frame->position_y + 5,
    EDIT_STR_FOREGROUND, PROGRAM_THEME_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND
  );

  EditDateTime edit_to = NewEditDateTime(
    &(to_date),
    to_date, from_date,
    36, 3,
    frame->position_x + 39, frame->position_y + 5,
    EDIT_STR_FOREGROUND, PROGRAM_THEME_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND
  );

  Button filter_button = NewButton(
    " Lọc", ALIGN_CENTER,
    22, 3, 0,
    frame->position_x + 76, frame->position_y + 5,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    IVPAddButtonConsole
  );

  // TODO: add filter by created_at
  ListViewScroll list_view_scroll = NewListViewScroll(
    STAFF_LIST_IN_ARCHIVE, // data,
    NULL,
    0, 4, // page, fields count
    CountInvoicesInArchive, // items count
    TakeInvoicesInArchive, // take items
    IVP_INVOICE_LIST_WIDTH, IVP_INVOICE_LIST_HEIGHT,
    frame->position_x + 2, frame->position_y + 9,
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
    frame->position_x + (frame->width - IVP_UPDATED_FORM_WIDTH) / 2,
    frame->position_y + (frame->height - IVP_CREATION_FORM_HEIGHT) / 2
  );

  // updated
  Frame updated_frame = NewFrame(
    IVP_UPDATED_FORM_WIDTH, IVP_UPDATED_FORM_HEIGHT,
    frame->position_x + (frame->width - IVP_UPDATED_FORM_WIDTH) / 2,
    frame->position_y + (frame->height - IVP_UPDATED_FORM_HEIGHT) / 2
  );

  // show frame
  Frame show_frame = NewFrame(
    frame->width, frame->height,
    frame->position_x, frame->position_y
  );

  // Render - using rapid
  ivp_render_invoice_frame;

  // Active
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      // Add button
      keycode = ActiveButton(add_button);
      if (keycode == KEY_LEFT) {
        frame->active_element = 0;
      } else if (keycode == KEY_RIGHT) {
        frame->active_element = 3;
      } else if (keycode == KEY_DOWN) {
        frame->active_element = 4;
      } else if (keycode == ENTER) {
        IVPRecovery(frame);
        creation_frame->active_element = 1;
        ActiveInvoiceCreationFrame(creation_frame);
        ivp_render_invoice_frame;
        frame->active_element = 1;
      } else if (keycode == BACKSPACE) {
         frame->active_element = 0;
      }
    } else if (frame->active_element == 2) {
      // List
      keycode = ActiveListViewScroll(list_view_scroll);
      if (keycode == ENTER) {
        IVPRecovery(frame);
        linear_list = (LinearList) GetSelectedItemInListViewScroll(list_view_scroll);
        invoice = (Invoice) GetFirstItemInLinearList(linear_list);
        ActiveInvoiceShowFrame(show_frame, invoice);
        ivp_render_invoice_frame;
      } else if (keycode == BACKSPACE) {
        frame->active_element = 1;
      } else if (keycode == KEY_UP) {
        frame->active_element = 1;
      } else if (keycode == NULL_KEY) {
        frame->active_element = 1;
      }
    } else if (frame->active_element == 3) {
      keycode = ActiveEditStr(edit_query);
      if (keycode == KEY_LEFT) {
        frame->active_element = 1;
      } else if (keycode == KEY_DOWN)
        frame->active_element = 5;
      else if (keycode == ENTER) {
        frame->active_element = 2;
      }
    } else if (frame->active_element == 4) {
      keycode = ActiveEditDateTime(edit_from);
      if (keycode == KEY_UP) {
        frame->active_element = 1;
      } else if (keycode == KEY_DOWN)
        frame->active_element = 2;
      else if (keycode == KEY_RIGHT)
        frame->active_element = 5;
      else if (keycode == ENTER) {
        frame->active_element = 2;
      }
    } else if (frame->active_element == 5) {
      keycode = ActiveEditDateTime(edit_to);
      if (keycode == KEY_UP) {
        frame->active_element = 3;
      } else if (keycode == KEY_DOWN)
        frame->active_element = 2;
      else if (keycode == KEY_LEFT)
        frame->active_element = 4;
      else if (keycode == ENTER) {
        frame->active_element = 2;
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
