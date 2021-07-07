#include "invoice_detail.h"

message_tp InvoiceDetailValidation(InvoiceDetail invoice_detail, bool strict = true, char invoice_type = IMPORT_INVOICE) {
  if (IsNull(invoice_detail)) return M_NULL;

  if (!IsCodeInMaterialList(archive->material_list, invoice_detail->material_code))
    return M_INVOICE_DETAIL_MATERIAL_CODE_INVALID;

  if (!IsPositive(invoice_detail->amount))
    return M_INVOICE_DETAIL_AMOUNT_INVALID;

  if (strict == true) {
    if (invoice_type == EXPORT_INVOICE)
      if (!IsMaterialAvailable(invoice_detail->material_code, invoice_detail->amount))
        return M_INVOICE_DETAIL_AMOUNT_INVALID;
  }

  if (IsNegative(invoice_detail->price))
    return M_INVOICE_DETAIL_PRICE_INVALID;

//   if (IsNegative(invoice_detail->vat))
//     return M_INVOICE_DETAIL_VAT_INVALID;

  return OK;
}
