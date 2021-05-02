import bluetooth

server_sock=bluetooth.BluetoothSocket(bluetooth.RFCOMM)

port = 1
server_sock.bind(("",port))
server_sock.listen(1)

packet_size = 82

print("Awaiting connection...")
client_sock,address = server_sock.accept()
print("Accepted connection from", address)

while True:
	# Receive a packet
	data = bytearray()
	while len(data) < packet_size:
		data.extend(client_sock.recv(packet_size - len(data)))
	# Parse the packet
	msg = data[6:].decode('ascii').strip('\0')
	print(msg,end='')

client_sock.close()
server_sock.close()

