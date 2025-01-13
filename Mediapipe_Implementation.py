import cv2
import mediapipe as mp
from picamera2 import Picamera2, Preview
import serial
import time

# Initialize Serial Communication with Arduino
arduino = serial.Serial('/dev/ttyUSB0', 115200)  # Adjust port as needed
time.sleep(2)  # Allow serial connection to stabilize


mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils

# Initialize Picamera2
picam2 = Picamera2()
picam2.start_preview(Preview.NULL)
picam2.start()

# Set up MediaPipe Hands
with mp_hands.Hands(min_detection_confidence=0.7, min_tracking_confidence=0.7) as hands:
    while True:
        # Capture a frame from the camera
        frame = picam2.capture_array()

        # Ensure the frame has 3 channels (BGR)
        if frame.shape[2] == 4:  # If the frame has 4 channels (RGBA), convert it to BGR
            frame = cv2.cvtColor(frame, cv2.COLOR_RGBA2BGR)

        # Flip the frame horizontally for selfie-view display
        frame = cv2.flip(frame, 1)

        # Convert the frame to RGB for MediaPipe processing
        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        # Process the frame with MediaPipe Hands
        results = hands.process(rgb_frame)

        gesture = None  # Reset gesture

        if results.multi_hand_landmarks:
            for hand_landmarks in results.multi_hand_landmarks:
                mp_drawing.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)

                # Extract key landmark points
                thumb_tip = hand_landmarks.landmark[mp_hands.HandLandmark.THUMB_TIP]
                index_tip = hand_landmarks.landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP]
                middle_tip = hand_landmarks.landmark[mp_hands.HandLandmark.MIDDLE_FINGER_TIP]
                ring_tip = hand_landmarks.landmark[mp_hands.HandLandmark.RING_FINGER_TIP]
                pinky_tip = hand_landmarks.landmark[mp_hands.HandLandmark.PINKY_TIP]

                index_pip = hand_landmarks.landmark[mp_hands.HandLandmark.INDEX_FINGER_PIP]
                thumb_ip = hand_landmarks.landmark[mp_hands.HandLandmark.THUMB_IP]
                thumb_mcp = hand_landmarks.landmark[mp_hands.HandLandmark.THUMB_MCP]

                # Gesture Recognition Logic
                if thumb_tip.y < thumb_ip.y < thumb_mcp.y and index_tip.y > thumb_ip.y:
                    gesture = "Device_ON"  
                elif index_tip.y < middle_tip.y and ring_tip.y < middle_tip.y and pinky_tip.y < middle_tip.y and thumb_tip.y > thumb_ip.y:
                    gesture = "Device_OFF"  
                elif all(finger.y > index_tip.y for finger in [middle_tip, ring_tip, pinky_tip]) and index_tip.y < index_pip.y:
                    gesture = "Level_Up"  
                elif all(finger.y > index_tip.y for finger in [middle_tip, ring_tip, pinky_tip]) and index_tip.y > index_pip.y:
                    gesture = "Level_Down"  
                elif all(finger.y < index_pip.y for finger in [thumb_tip, index_tip, middle_tip, ring_tip, pinky_tip]) and pinky_tip.y < index_tip.y:
                    gesture = "Check_Temperature"  

                # Send gesture to Arduino if recognized
                if gesture:
                    arduino.write(f"{gesture}\n".encode())
                    cv2.putText(frame, gesture, (10, 70), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

        # Display the frame with gestures
        cv2.imshow('Hand Gesture Recognition', frame)

        # Exit the loop if 'q' is pressed
        if cv2.waitKey(10) & 0xFF == ord('q'):
            break

# Cleanup
picam2.close()
cv2.destroyAllWindows()
arduino.close()
