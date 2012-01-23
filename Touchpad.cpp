
#include "Touchpad.h"

TouchpadHandler::TouchpadHandler()
{
  handler = NULL;
  wipes = 0;
}

void TouchpadHandler::initialize()
{
  mpr.initialize();
}

void TouchpadHandler::update()
{
  if (handler) {
    for (int i=0; i<5; i++)  {
      bool state = mpr.getTouchStatus(i);
      if (state != lastTouchState[i]) {
        switch(i) {
          case TP_EAST:
            checkWipes(state, TP_NORTH, TP_SOUTH);
            if (wipes==0) {
              handler->rightChanged(state);
            }
            break;
          case TP_NORTH:
            checkWipes(state, TP_WEST, TP_EAST);
            if (wipes==0) {
              handler->upChanged(state);
            }
            break;
          case TP_WEST:
            handler->leftChanged(state);
            if (wipes==0) {
              checkWipes(state, TP_SOUTH, TP_NORTH);
            }
            break;
          case TP_SOUTH:
            checkWipes(state, TP_EAST, TP_WEST);
            if (wipes==0) {
              handler->downChanged(state);
            }
            break;
            
          case TP_CENTER:
            handler->centerChanged(state);
            break;
        }
      }
      lastTouchState[i] = state;
    }
  }
}

void TouchpadHandler::setHandler(TouchpadEventHandler* handler)
{
  this->handler = handler;
}

void TouchpadHandler::checkWipes(bool centerState, byte padLeft, byte padRight)
{
  // Check if the handler wants to detect wipes.
  if (handler->wipeEnabled()) {
    if (centerState == 1){
      if (lastTouchState[padLeft]) {
        wipes++;
        handler->rightWipe(wipes*-1);
      } else if (lastTouchState[padRight]) {
        wipes--;
        handler->leftWipe(wipes);
      }
    } else {
      // If the current pad was released, and neither the pad right nor the pad left of it
      // is pressed, then the user has aborted wiping.
      if ((!lastTouchState[padLeft] && wipes < 0) || (!lastTouchState[padRight] && wipes > 0)) {
        wipes = 0;
      }
    }
  }
}

TouchpadHandler Touchpad;
