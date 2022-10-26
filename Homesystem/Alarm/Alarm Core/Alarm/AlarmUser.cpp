#include "AlarmUser.h"
 
AlarmUser::AlarmUser(): 
  menu_pressed_(false), interaction(false) {

}

void AlarmUser::setInteraction() {
   AlarmTimer::SetLatestUserInteractionTime();
   interaction = true;
}
void AlarmUser::setMenuPressed() {
  menu_pressed_ = true;
} 
bool AlarmUser::getMenuPressed() {
  return menu_pressed_;
}
void AlarmUser::clear() {
   menu_pressed_ = false;
   interaction = false;      
}
