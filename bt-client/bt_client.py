import bluetooth

server_sock=bluetooth.BluetoothSocket(bluetooth.RFCOMM)

port = 1
server_sock.bind(("",port))
server_sock.listen(1)

print("Awaiting connection...")
client_sock,address = server_sock.accept()
print("Accepted connection from", address)

while True:
	data = client_sock.recv(128)
	msg = data[6:].decode('utf-8').strip('\0')
	print(msg,end='')

client_sock.close()
server_sock.close()

