/* datetime */

/* New and Destroy */
DateTime NewDateTime(int year, int month, int day, int hour, int minute, int second) {
  DateTime date_time = (DateTime) malloc(sizeof(DateTimeT));
  date_time->year = year;
  date_time->month = month;
  date_time->day = day;
  date_time->hour = hour;
  date_time->minute = minute;
  date_time->second = second;

  return date_time;
}

DateTime CurrentDateTime(bool utc = false) {
  time_t t = time(NULL);
  tm _tm;
  if (utc == false) _tm = *localtime(&t);
  else _tm = *gmtime(&t);

  return NewDateTime(
    _tm.tm_year + 1900,
    _tm.tm_mon + 1,
    _tm.tm_mday,
    _tm.tm_hour,
    _tm.tm_min,
    _tm.tm_sec
  );
}

DateTime NewDateTimeByTimeT(time_t t, bool utc = false) {
  tm _tm;
  if (utc == false) _tm = *localtime(&t);
  else _tm = *gmtime(&t);

  return NewDateTime(
    _tm.tm_year + 1900,
    _tm.tm_mon + 1,
    _tm.tm_mday,
    _tm.tm_hour,
    _tm.tm_min,
    _tm.tm_sec
  );
}

void DestroyDateTime(DateTime &date_time) {
  free(date_time);
  date_time = NULL;
}

void RevokeDateTime(DateTime &date_time) {
  free(date_time);
  date_time = NULL;
}

// Quickly set
void SetDate(DateTime date_time, int year, int month, int day) {
  date_time->year = year;
  date_time->month = month;
  date_time->day = day;
}

void SetTime(DateTime date_time, int hour, int minute, int second) {
  date_time->hour = hour;
  date_time->minute = minute;
  date_time->second = second;
}

void SetDateTime(DateTime date_time, int year, int month, int day, int hour, int minute, int second) {
  date_time->year = year;
  date_time->month = month;
  date_time->day = day;
  date_time->hour = hour;
  date_time->minute = minute;
  date_time->second = second;
}

void SetDateTimeByTimeT(DateTime date_time, time_t t, bool utc = false) {
  tm _tm;
  if (utc == false) _tm = *localtime(&t);
  else _tm = *gmtime(&t);

  date_time->year = _tm.tm_year + 1900;
  date_time->month = _tm.tm_mon + 1;
  date_time->day = _tm.tm_mday;
  date_time->hour = _tm.tm_hour;
  date_time->minute = _tm.tm_min;
  date_time->second = _tm.tm_sec;
}

// Now
time_t TimeNow() {
  return time(NULL);
}

void TakeCurrentDateTime(DateTime date_time, bool utc = false) {
  time_t t = time(NULL);
  tm _tm;
  if (utc == false) _tm = *localtime(&t);
  else _tm = *gmtime(&t);

  date_time->year = _tm.tm_year + 1900;
  date_time->month = _tm.tm_mon + 1;
  date_time->day = _tm.tm_mday;
  date_time->hour = _tm.tm_hour;
  date_time->minute = _tm.tm_min;
  date_time->second = _tm.tm_sec;
}

// Convert
time_t DateTimeToTimeT(DateTime date_time) {
  tm _tm;
  _tm.tm_year = date_time->year - 1900;
  _tm.tm_mon = date_time->month - 1;
  _tm.tm_mday = date_time->day;
  _tm.tm_hour = date_time->hour;
  _tm.tm_min = date_time->minute;
  _tm.tm_sec = date_time->second;

  return mktime(&_tm);
}
