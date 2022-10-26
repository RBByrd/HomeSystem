#ifndef AlarmMenuPages_H_
#define AlarmMenuPages_H_

#include <Arduino.h>

class AlarmMenuPages {
    private:
        const char* kTitle;
        AlarmMenuPages* child_menu_;
        bool has_child_;
        AlarmMenuPages* next_menu_;
        bool has_next_;
        
     public: 
      enum menuType {knull, kmenu, ksetting, kpassword};

      AlarmMenuPages();
      AlarmMenuPages(const char* _kTitle);
      AlarmMenuPages(const char* _kTitle,AlarmMenuPages& prev);
      AlarmMenuPages(const char* _kTitle,AlarmMenuPages& parent, byte generation);
      bool HasNext();
      AlarmMenuPages* GoToNextMenu(); 
      bool HasChild();
      AlarmMenuPages* GoToChildMenu();
};

#endif