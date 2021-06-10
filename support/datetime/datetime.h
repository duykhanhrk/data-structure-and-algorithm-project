/* message */

#ifndef __SUPPORT_DATETIME__
#define __SUPPORT_DATETIME__

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DateTimeT {
  int year, int month, int day,
  int hour, int minute, int second
} DateTimeT, * DateTimeT;

// New and Destroy
DateTime NewDateTime(int, int, int, int, int, int);
DateTime NewDateTimeByTimeT(time_t)
DateTime DestroyDateTime(DateTime &)
DateTime RevokeDateTime(DateTime &)

// Quickly set
SetDate(DateTime, int, int, int);
SetTime(DateTime, int, int, int);
SetDateTime(DateTime, int, int, int, int, int, int);
SetDateTimeByTimeT(DateTime, time_t);

// Now
time_t TimeNow();
DateTime CurrentDateTime();
void TakeCurrentDateTime(DateTime);

// Convert
time_t DateTimeToTimeT(DateTime);

#ifdef __cplusplus
}
#endif

#endif
