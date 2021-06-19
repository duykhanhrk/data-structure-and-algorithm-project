#ifndef __FRAMES_MAIN__
#define __FRAMES_MAIN__

/* private key - MFP */

#define MFP_NAVIGATE_LIST_WIDTH 20
#define MFP_CONTENT_WIDTH WINDOW_ROWS - MFP_NAVIGATE_LIST_WIDTH
#define MFP_NAVIGATE_LIST_HEIGHT WINDOW_ROWS
#define MFP_NAVIGATE_LIST_ITEM_WIDTH MFP_NAVIGATE_LIST_WIDTH
#define MFP_NAVIGATE_LIST_ITEM_HEIGHT 3


#ifdef __cplusplus
extern "C" {
#endif

void ActiveMainFrame(Frame);

#include "main.cpp"

#ifdef __cplusplus
}
#endif

#endif
