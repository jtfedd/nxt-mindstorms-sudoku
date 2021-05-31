import bluetooth

# Searches local bluetooth devices to find
# the address used by the NXT

target_name = "NXT"
target_address = None

print("Searching for devices...")
nearby_devices = bluetooth.discover_devices()
print("Found", len(nearby_devices), "Device(s)")

for btaddr in nearby_devices:
	btname = bluetooth.lookup_name(btaddr)
	#print(btaddr, btname)
	if target_name == btname:
		target_address = btaddr

if target_address is None:
	print("NXT not found.")
else:
	print("Found NXT:", target_address)
