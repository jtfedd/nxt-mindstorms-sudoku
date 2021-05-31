import bluetooth

# Establishes a direct connection to the NXT
# to receive data

bt_addr = "00:16:53:09:0E:07"
port = 1

packet_size = 82

print("Connecting...")
sock=bluetooth.BluetoothSocket(bluetooth.RFCOMM)
sock.connect((bt_addr, port))
print("Connected!")

try:
	while True:
		data = bytearray()
		while len(data) < packet_size:
			data.extend(sock.recv(packet_size - len(data)))
		msg = data[6:].decode('ascii').strip('\0')
		print(msg, end='')
except Exception as e:
	print("Error:", e)
	sock.close()
