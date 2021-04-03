#include "src/bluetooth/btio.h"

#ifndef BT_PRINT
#define BT_PRINT

#define CONNECTION 1
#define MAILBOX    0

void bt_print(string msg) {
  if (!BTCommCheck(CONNECTION)) {
    return;
  }
  BTSendMessage(CONNECTION, MAILBOX, msg);
}
  
#endif

