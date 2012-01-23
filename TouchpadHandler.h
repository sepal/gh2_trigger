#ifndef _TOUCHPAD_EVENT_HANDLER_H_
#define _TOUCHPAD_EVENT_HANDLER_H_

class TouchpadEventHandler
{
public:
  /**
   * Called if the state of the button facing up from the user was changed.
   * @param pressed True if the button was pressed, False if it was released.
   */
  virtual void upChanged(bool pressed) = 0;
  
  /**
   * Called if state of the the button facing down from the user was changed.
   * @param pressed True if the button was pressed, False if it was released.
   */
  virtual void downChanged(bool pressed) = 0;
  
  /**
   * Called if state of the the button facing left from the user was changed.
   * @param pressed True if the button was pressed, False if it was released.
   */
  virtual void leftChanged(bool pressed) = 0;
  
  /**
   * Called if state of the the button facing right from the user was changed.
   * @param pressed True if the button was pressed, False if it was released.
   */
  virtual void rightChanged(bool pressed) = 0;
  
  /**
   * Called if state of the the centric button was changed.
   * @param pressed True if the button was pressed, False if it was released.
   */
  virtual void centerChanged(bool pressed) = 0;
  
  
  /**
   * Called when user has wiped from one pad to the left one of itself.
   * @param wipes How often has the user swiped from one pad to the previous (is alsways > 1).
   */
  virtual void leftWipe(int wipes) {}
  
  /**
   * Called when user has wiped from one pad to the right one of itself.
   * @param wipes How often has the user swiped from one pad to the next (is alsways > 1).
   */
  virtual void rightWipe(int wipes) {}
  
  /**
   * Returns true if handler wants to (half-)circle drawing detection.
   */ 
  bool wipeEnabled() {
    return wipeDetection;
  }
protected:
  // Should only be set by a derived class.
  bool wipeDetection;
};

#endif//_TOUCHPAD_EVENT_HANDLER_H_
