/* NXT Bluetooth communication library
 * Author: Daniele Benedettelli
 * Indirect contributors: David Wallace, Sivan Toledo, John Hansen
 * Modified by Alexander Demin
 */

#ifndef BTIO
#define BTIO

byte __buffer[];
byte __array[];

byte BTCommCheck (int connection){ //checks if BT connection on line exists
   return (BluetoothStatus(connection)==NO_ERR);
}

sub BTWait (int connection){  //wait until BT is idle
   until(BluetoothStatus(connection)==NO_ERR);
}

sub BTSendMessage(byte connection, byte mailbox, string msg){ //send a BT message
   byte len,Smb;
   int i;
   BTWait(connection);
   ArrayInit(__buffer,0,80);
   ArrayInit(__array,0,59);
   StrToByteArray(msg,__array);
   len = ArrayLen(__array);
   __buffer[0] = 0x80; //no reply telegram
   __buffer[1] = 0x09; //MessageWrite Direct Command
   __buffer[2] = mailbox; //inbox number
   __buffer[3] = len+1; //message size
   for (i=4;i<(len+4);i++){
      __buffer[i] = __array[i-4];
   }
   BluetoothWrite(connection,__buffer);
   BTWait(connection);
}

string BTReceiveMessage(byte connection, byte mailbox, byte flush){ //receive a BT message
   string msg;
   BTWait(connection);
   ReceiveMessage(mailbox,flush,msg);
   BTWait(connection);
   return msg;
}

#endif

