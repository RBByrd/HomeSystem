#ifndef AlarmTimer_H_
#define AlarmTimer_H_

#include <Arduino.h>

class AlarmTimer {
    private: 
      static unsigned long alarm_current_time_;
      static unsigned long latest_user_interaction_time_;
      static unsigned long latest_zone_interaction_time_;
      unsigned long alarm_timer_;
      
    public:
      const unsigned long kMaxTime = 4294967295;
    public:
      AlarmTimer();
      static void SetCurrentTime();
      static void SetLatestUserInteractionTime();
      static void SetLatestZoneInteractionTime();
      unsigned long GetTimeDifference(unsigned long start_time, 
                                      unsigned long end_time);
      unsigned long UserInteractionInterval();
      unsigned long ZoneInteractionInterval();
      unsigned long LastInteraction();
};

#endif
