#ifndef __FRAMES_INVOICE_SHOW__
#define __FRAMES_INVOICE_SHOWL__

/* Private key - ISP */

// rapid - isp
#define isp_info_form_background\
        DrawRecShape(\
          frame->width, frame->height,\
          ' ',\
          frame->position_x, frame->position_y,\
          PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND\
        );

#define isp_info_form_shape(y) \
        DrawRecShape(\
          33, 3,\
          ' ',\
          frame->position_x + 12, frame->position_y + 1 + 4 * y,\
          PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND_LV1\
        );

#define isp_info_form_label(text, y) \
        WriteStr(text, frame->position_x + 2, frame->position_y + 2 + 4 * y, frame->foreground, frame->background);

#define isp_info_form_value(type, value, y) \
        isp_info_form_shape(y);\
        type(\
          value,\
          frame->position_x + 14,\
          frame->position_y + 2 + 4 * y,\
          PROGRAM_FOREGROUND_REVERSE,\
          PROGRAM_THEME_BACKGROUND_LV1\
        );

#define isp_info_form_element(text, type, value, y)\
        isp_info_form_label(text, y);\
        isp_info_form_value(type, value, y)

#ifdef __cplusplus
extern "C" {
#endif

// Custom console
bool ISPListViewScrollConsole(char keycode) {
  return (keycode == BACKSPACE);
}

bool ISPUpDownBackConsole(char keycode) {
  return (keycode == KEY_LEFT || keycode == KEY_RIGHT || keycode == BACKSPACE);
}

// Recovery screen
void ISPRecoveryScreen(Frame frame) {
  DrawRecShape(
    frame->width, frame->height,
    ' ',
    frame->position_x, frame->position_y,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND_LV1
  );
}

// Render Invoice info
void ISPRenderInvoiceInfoForm(Frame frame, Invoice invoice) {
  // Background
  isp_info_form_background;

  // Values
  isp_info_form_element("Số", WriteStr, invoice->number, 0);
  isp_info_form_element("Ngày lập", WriteDate, invoice->created_at, 1);
  if (invoice->type == IMPORT_INVOICE) {
    isp_info_form_element("Loại", WriteStr, "Nhập", 2);
  }
  else if (invoice->type == EXPORT_INVOICE) {
    isp_info_form_element("Loại", WriteStr, "Xuất", 2);
  }
  Staff staff = GetCreatedInvoiceStaff(invoice->number);
  isp_info_form_element("Người lập", WriteStr, staff->code, 3);
  double total_price = CalculateTotalPriceOfInvoice(invoice);
  isp_info_form_element("Trị giá", WriteDouble, total_price, 4);
}

void ActiveInvoiceShowFrame(Frame frame, Invoice invoice) {
  // Default
  frame->active_element = 1;

  // Init templates
  ListViewScroll list_view_scroll = NewListViewScroll(
    invoice->invoice_detail_list, // data
    NULL, // filter
    0, 4, // page, fields count
    CountInvoiceDetails, // count
    TakeInvoiceDetails, // take
    (frame->width - 4) / 2, (frame->height - 2), // heigh, width
    frame->position_x + frame->width / 2, frame->position_y + 1, // position_x, position_y
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    (frame->width - 4) / 2, 1,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    RENDER_LIST_VIEW_ITEM_WITH_DATA_AS_INVOICE_DETAIL_TYPE_A,
    ACTIVE_LIST_VIEW_ITEM_WITH_DATA_AS_INVOICE_DETAIL_TYPE_A,
    ISPListViewScrollConsole
  );

  AddFieldForListViewScroll(list_view_scroll, "Mã vật tư", 10);
  AddFieldForListViewScroll(list_view_scroll, "Số lượng", 10);
  AddFieldForListViewScroll(list_view_scroll, "Giá bán", 10);
  AddFieldForListViewScroll(list_view_scroll, "VAT", 8);

  Frame info_form = NewFrame(
    (frame->width - 4) / 2 - 1, 21,
    frame->position_x + 2,
    frame->position_y + (frame->height - 21) / 2
  );

  ISPRenderInvoiceInfoForm(info_form, invoice);
  RenderListViewScroll(list_view_scroll);

  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      keycode = ActiveListViewScroll(list_view_scroll);
      if (keycode == BACKSPACE)
        frame->active_element = 0;
    }
  }

  DestroyFrame(info_form);
  DestroyListViewScroll(list_view_scroll);
  ISPRecoveryScreen(frame);
}

#ifdef __cplusplus
}
#endif

#endif
