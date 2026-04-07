# EmergencyStop.srv
# Emergency stop command

# Request
uint8 drone_id                   # Target drone (255 = ALL)
uint8 ALL_DRONES = 255

uint8 STOP_HOVER = 0             # Stop and hover in place
uint8 STOP_LAND = 1              # Land immediately
uint8 STOP_RTL = 2               # Return to launch
uint8 stop_type

string reason                    # For logging
