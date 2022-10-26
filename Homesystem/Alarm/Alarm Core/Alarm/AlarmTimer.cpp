
#include "AlarmTimer.h"


AlarmTimer::AlarmTimer() {
  static unsigned long alarm_current_time_  = 0;
  static unsigned long latest_user_interaction_time_ = 0;
  static unsigned long latest_zone_interaction_time_ = 0;
  unsigned long alarm_timer_ = 0;
  
}

void AlarmTimer::SetCurrentTime() {
  alarm_current_time_ = millis();
  return;
}

void AlarmTimer::SetLatestUserInteractionTime() {
   latest_user_interaction_time_ = alarm_current_time_;
}

void AlarmTimer::SetLatestZoneInteractionTime() {
   latest_zone_interaction_time_ = alarm_current_time_;
}

unsigned long AlarmTimer::GetTimeDifference(unsigned long start_time, 
                                unsigned long end_time) {
    //Account for rollover. 
    //Maximuim amount of time is 4294967295 milliseconds, ~50 days
    
    if (start_time <= end_time) {
        return end_time - start_time;
    }
    return (kMaxTime - start_time) + end_time;
}  
    
unsigned long AlarmTimer::UserInteractionInterval() {
    return GetTimeDifference(latest_user_interaction_time_,
                             alarm_current_time_);
}

unsigned long AlarmTimer::ZoneInteractionInterval() {
    return GetTimeDifference(latest_zone_interaction_time_, 
                             alarm_current_time_);
}

unsigned long AlarmTimer::LastInteraction() {
    if(ZoneInteractionInterval() > UserInteractionInterval()) {
      return UserInteractionInterval();
    }
    return ZoneInteractionInterval();
}
