#include "invoice.h"

// Rapid - ivp
#define ivp_templates_args\
        Button add_button,\
        Button filter_button,\
        EditStr edit_query,\
        ListViewScroll list_view_scroll,\
        Notify notify

#define ivp_templates_params\
        add_button,\
        filter_button,\
        edit_query,\
        list_view_scroll,\
        notify

#define ivp_render_templates RenderInvoiceFrameTemplates(ivp_templates_params)

// Custon console
bool IVPAddButtonConsole(keycode_tp c) {
  return (c == KEY_LEFT || c == KEY_RIGHT || c == KEY_DOWN || c == ENTER || c == BACKSPACE);
}

void ConcealInvoiceFrame(Frame frame, ivp_templates_args) {
  ConcealButton(add_button);
  ConcealButton(filter_button);
  ConcealEditStr(edit_query);
  ConcealNotify(notify);
  ConcealListViewScroll(list_view_scroll);
}

void RenderInvoiceFrameTemplates(ivp_templates_args) {
  RenderButton(add_button);
  RenderButton(filter_button);
  RenderEditStr(edit_query);
  RenderNotify(notify, NORMAL_NOTIFY, "In hóa đơn nhanh với thanh nhập phía trên");
  RenderListViewScroll(list_view_scroll);
}

void DestroyInvoiceFrameTemplates(ivp_templates_args) {
  DestroyButton(add_button);
  DestroyButton(filter_button);
  DestroyEditStr(edit_query);
  DestroyNotify(notify);
  DestroyListViewScroll(list_view_scroll);
}

void ActiveInvoiceFrame(Frame frame) {
  // Variable
  LinearList linear_list;
  Invoice invoice;
  char query[INVOICE_NUMBER_MAX_LEN + 1];
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

  Button filter_button = NewButton(
    "     Lọc hóa đơn theo khoảng thời gian", ALIGN_CENTER,
    IVP_BUTTON_WIDTH, IVP_BUTTON_HEIGHT, 0,
    frame->position_x + 2, frame->position_y + 5,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    STANDARD_CONSOLE
  );

  EditStr edit_query = NewEditStr(
    query,
    INVOICE_NUMBER_MAX_LEN, 0,
    IVP_BUTTON_WIDTH, IVP_BUTTON_HEIGHT,
    frame->position_x + 51, frame->position_y + 1,
    EDIT_STR_FOREGROUND, PROGRAM_THEME_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND,
    NUMERIC_CHAR_SET
  );

  Notify notify = NewNotify(
    IVP_BUTTON_WIDTH, IVP_BUTTON_HEIGHT, 0,
    frame->position_x + 51, frame->position_y + 5,
    PROGRAM_FOREGROUND, BACKGROUND_LIGHT_AQUA
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

  AddFieldForListViewScroll(list_view_scroll, "Số", 20);
  AddFieldForListViewScroll(list_view_scroll, "Ngày lập", 10);
  AddFieldForListViewScroll(list_view_scroll, "Người lập", 46);
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

  // filter form
  Frame filter_form = NewFrame(
    IVP_FILTER_FORM_WIDTH, IVP_FILTER_FORM_HEIGHT,
    frame->position_x + (frame->width - IVP_FILTER_FORM_WIDTH) / 2,
    frame->position_y + (frame->height - IVP_FILTER_FORM_HEIGHT) / 2
  );

  // Render - using rapid
  ivp_render_templates;

  // Active
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      // Add button
      keycode = ActiveButton(add_button);
      if (keycode == KEY_RIGHT) {
        frame->active_element = 3;
      } else if (keycode == KEY_DOWN) {
        frame->active_element = 4;
      } else if (keycode == ENTER) {
        ConcealInvoiceFrame(frame, ivp_templates_params);
        creation_frame->active_element = 1;
        ActiveInvoiceCreationFrame(creation_frame);
        ivp_render_templates;
        frame->active_element = 1;
      } else if (keycode == BACKSPACE) {
         frame->active_element = 0;
      }
    } else if (frame->active_element == 2) {
      // List
      keycode = ActiveListViewScroll(list_view_scroll);
      if (keycode == ENTER) {
        ConcealInvoiceFrame(frame, ivp_templates_params);
        linear_list = (LinearList) GetSelectedItemInListViewScroll(list_view_scroll);
        invoice = (Invoice) GetFirstItemInLinearList(linear_list);
        ActiveInvoiceShowFrame(show_frame, invoice);
        ivp_render_templates;
      } else if (keycode == BACKSPACE) {
        frame->active_element = 1;
      } else if (keycode == KEY_UP) {
        frame->active_element = 4;
      } else if (keycode == NULL_KEY) {
        frame->active_element = 4;
      } else if (keycode == KEY_RIGHT) {
        frame->active_element = 3;
      } else if (keycode == KEY_LEFT) {
        frame->active_element = 1;
      }
    } else if (frame->active_element == 3) {
      // Query
      keycode = ActiveEditStr(edit_query);
      if (keycode == KEY_LEFT) {
        frame->active_element = 1;
      } else if (keycode == KEY_DOWN)
        frame->active_element = 2;
      else if (keycode == ENTER) {
        if (IsBlankString(edit_query->str)) {
          RenderNotify(notify, WARNING_NOTIFY, "Không được để trắng");
          continue;
        }

        invoice = GetInvoiceInArchiveByNumber(edit_query->str);
        if (IsNull(invoice)) {
          RenderNotify(notify, ERROR_NOTIFY, "Không tìm thấy hóa đơn");
          continue;
        }

        ConcealInvoiceFrame(frame, ivp_templates_params);
        ActiveInvoiceShowFrame(show_frame, invoice);
        ivp_render_templates;
      }
    } else if (frame->active_element == 4) {
      keycode = ActiveButton(filter_button);
      if (keycode == KEY_UP) {
        frame->active_element = 1;
      } else if (keycode == ENTER) {
        ConcealInvoiceFrame(frame, ivp_templates_params);
        ActiveInvoiceFilterForm(filter_form);
        ivp_render_templates;
      } else if (keycode == KEY_LEFT) {
        frame->active_element = 1;
      } else if (keycode == KEY_RIGHT) {
        frame->active_element = 3;
      } else if (keycode == KEY_DOWN) {
        frame->active_element = 2;
      } else if (keycode == BACKSPACE) {
        frame->active_element = 0;
      }
    }
  }

  // Recovery
  ConcealInvoiceFrame(frame, ivp_templates_params);

  // Release
  DestroyInvoiceFrameTemplates(ivp_templates_params);
  DestroyFrame(creation_frame);
  DestroyFrame(updated_frame);
}
