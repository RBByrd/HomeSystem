#include "AlarmMenuPages.h"


AlarmMenuPages::AlarmMenuPages(){

}
 
AlarmMenuPages::AlarmMenuPages(const char* _kTitle)
  :kTitle(_kTitle){

}
  
AlarmMenuPages::AlarmMenuPages(const char* _kTitle,AlarmMenuPages& prev)
  :kTitle(_kTitle){        
    AlarmMenuPages* next = this;
    prev.next_menu_ = next;
    prev.has_next_ = true;
}

AlarmMenuPages::AlarmMenuPages(const char* _kTitle,AlarmMenuPages& parent, byte generation)
  :kTitle(_kTitle){        
    AlarmMenuPages* child = this;
    parent.child_menu_ = child;
    parent.has_child_ = true;
}

bool AlarmMenuPages::HasNext(){
  return has_next_;
}

AlarmMenuPages* AlarmMenuPages::GoToNextMenu(){
  return next_menu_;
}

bool AlarmMenuPages::HasChild(){
  return has_child_;
}

AlarmMenuPages* AlarmMenuPages::GoToChildMenu(){
  return child_menu_;
}
