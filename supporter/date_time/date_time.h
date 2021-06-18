/* message */

#ifndef __SUPPORT_DATE_TIME__
#define __SUPPORT_DATE_TIME__

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DateTimeT {
  int year; int month; int day;
  int hour; int minute; int second;
} DateTimeT, * DateTime;

// New and Destroy
DateTime NewDateTime(int, int, int, int, int, int);
DateTime CurrentDateTime(bool);
DateTime NewDateTimeByTimeT(time_t, bool);
void DestroyDateTime(DateTime &);
void RevokeDateTime(DateTime &);

// Quickly set
void SetDate(DateTime, int, int, int);
void SetTime(DateTime, int, int, int);
void SetDateTime(DateTime, int, int, int, int, int, int);
void SetDateTimeByTimeT(DateTime, time_t, bool);

// Now
time_t TimeNow();
void TakeCurrentDateTime(DateTime, bool);

// Convert
time_t DateTimeToTimeT(DateTime);

#include "date_time.cpp"

#ifdef __cplusplus
}
#endif

#endif
