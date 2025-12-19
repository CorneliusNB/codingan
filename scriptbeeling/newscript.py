import cv2
import pytesseract
import pyautogui
import numpy as np
import time
import sys
import select
import shutil
import os
import subprocess
from PIL import Image

# --- CONFIGURATION ---

# NIXOS FIX: Find tesseract in the current PATH.
tesseract_path = shutil.which("tesseract")

if tesseract_path:
    print(f"[*] Tesseract binary found at: {tesseract_path}")
    pytesseract.pytesseract.tesseract_cmd = tesseract_path
else:
    print("[!] ERROR: Tesseract not found in PATH.")
    print("    Did you run 'nix-shell -p tesseract ...'?")
    sys.exit(1)

pyautogui.FAILSAFE = True
pyautogui.PAUSE = 0.5

# --- HELPER FUNCTIONS ---

def is_enter_pressed():
    """Checks for ENTER key press on Linux/NixOS non-blocking."""
    try:
        if select.select([sys.stdin], [], [], 0)[0]:
            sys.stdin.readline()
            return True
    except:
        pass
    return False

def get_screen_image():
    """
    Captures screen and returns CV2 image (BGR).
    Includes specific logic for Wayland (using 'grim').
    """
    # Check for Wayland environment
    is_wayland = os.environ.get('WAYLAND_DISPLAY') or os.environ.get('XDG_SESSION_TYPE') == 'wayland'
    
    if is_wayland:
        # On Wayland, pyautogui.screenshot() usually fails or returns black.
        # We use 'grim' (standard for Sway/Hyprland) if available.
        if shutil.which("grim"):
            try:
                # Capture to a temp file
                subprocess.run(["grim", "/tmp/ocr_bot_shot.png"], check=True, stderr=subprocess.DEVNULL)
                img = Image.open("/tmp/ocr_bot_shot.png")
                img = np.array(img)
                # Convert RGB (PIL default) to BGR (OpenCV default)
                return cv2.cvtColor(img, cv2.COLOR_RGB2BGR)
            except Exception as e:
                print(f"[!] Wayland screenshot (grim) failed: {e}")
        else:
             print("[!] Wayland detected but 'grim' not found. OCR will likely fail.")
             print("    Please add 'grim' to your nix-shell packages.")

    # Fallback / X11 Standard Method
    try:
        screenshot = pyautogui.screenshot()
        img = np.array(screenshot)
        return cv2.cvtColor(img, cv2.COLOR_RGB2BGR)
    except Exception as e:
        print(f"[!] Screenshot failed: {e}")
        return None

def get_ocr_data(img):
    """
    Runs OCR on the provided image.
    """
    if img is None: return None
    try:
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        # OTSU Thresholding for high contrast
        _, thresh = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
        
        custom_config = r'--psm 11 -c tessedit_char_whitelist=ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!.:'
        data = pytesseract.image_to_data(thresh, output_type=pytesseract.Output.DICT, config=custom_config)
        return data
    except Exception as e:
        print(f"[!] OCR failed: {e}")
        return None

def click_orange_next_button(img):
    """
    Fallback: Looks for the specific ORANGE color of the Next button.
    Useful when OCR fails to read white text on orange background.
    Orange Range (Approx BGR): Blue: 0-80, Green: 140-200, Red: 220-255
    """
    if img is None: return False
    # Define range for that specific orange button
    lower_orange = np.array([0, 130, 200])
    upper_orange = np.array([100, 210, 255])
    
    mask = cv2.inRange(img, lower_orange, upper_orange)
    
    # Find contours
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    for c in contours:
        x, y, w, h = cv2.boundingRect(c)
        
        # Filter for button-sized blobs (width > 50px, height > 20px)
        if w > 50 and h > 20:
            center_x = x + w // 2
            center_y = y + h // 2
            print(f" -> Found Orange Button (Next) at ({center_x}, {center_y}). Clicking...")
            pyautogui.moveTo(center_x, center_y, duration=0.2)
            pyautogui.click()
            return True
    return False

def click_text(target_text, data, strict=False):
    """
    Scans OCR data for target_text and clicks it.
    """
    if not data: return False
    
    n_boxes = len(data['text'])
    for i in range(n_boxes):
        text = data['text'][i].strip()
        if not text: continue
        
        match = False
        if strict:
            if text.lower() == target_text.lower():
                match = True
        else:
            if target_text.lower() in text.lower():
                match = True
        
        if match:
            (x, y, w, h) = (data['left'][i], data['top'][i], data['width'][i], data['height'][i])
            center_x = x + w // 2
            center_y = y + h // 2
            
            print(f" -> Found text '{text}' at ({center_x}, {center_y}). Clicking...")
            pyautogui.moveTo(center_x, center_y, duration=0.2)
            pyautogui.click()
            return True
            
    return False

def find_option_coordinates(img):
    """
    Looks for the circular Teal/Cyan option buttons (A, B, C...) using COLOR DETECTION.
    This replaces OCR for finding options, which is unreliable on styled buttons.
    """
    if img is None: return []

    # Convert to HSV color space
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    
    # Define color range for Teal/Cyan (The button border or fill)
    # OpenCV HSV Hue is 0-180. Cyan is ~90.
    # We use a broad range to catch light cyan borders and dark teal fills.
    lower_teal = np.array([75, 50, 50])
    upper_teal = np.array([105, 255, 255])
    
    mask = cv2.inRange(hsv, lower_teal, upper_teal)
    
    # Find contours
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    found_items = []
    
    for c in contours:
        x, y, w, h = cv2.boundingRect(c)
        
        # Filter based on size: Buttons are typically 20x20 to 100x100
        if 20 < w < 100 and 20 < h < 100:
            aspect_ratio = float(w)/h
            # Ensure it's roughly square/circular (0.7 - 1.3)
            if 0.7 < aspect_ratio < 1.3:
                center_x = x + w // 2
                center_y = y + h // 2
                
                # Store as (y, x) for sorting top-to-bottom
                found_items.append((center_y, center_x))
                
    # Sort top to bottom
    found_items.sort(key=lambda k: k[0])
    
    # Filter duplicates (concentric circles often detected as two contours)
    unique_items = []
    for item in found_items:
        if not unique_items:
            unique_items.append(item)
        else:
            last_y, last_x = unique_items[-1]
            curr_y, curr_x = item
            # Calculate distance
            dist = ((curr_x - last_x)**2 + (curr_y - last_y)**2)**0.5
            # If distance > 20px, treat as a new distinct button
            if dist > 20:
                unique_items.append(item)
    
    # Return as [(x,y), (x,y)...]
    return [(x, y) for (y, x) in unique_items]

# --- MAIN LOGIC ---

def run_ocr_bot():
    print("--- OCR BOT STARTED (Smart Mode for NixOS/Wayland) ---")
    print("1. Open your browser to the quiz.")
    print("2. Press ENTER to start.")
    print("(!) SAFETY: Slam mouse to top-left to STOP.")
    
    input()
    print(">>> Starting in 3 seconds...")
    time.sleep(3)
    
    try:
        while True:
            if is_enter_pressed():
                print("Stopped by user.")
                break

            print("\n[Scanning Screen...]")
            img = get_screen_image()
            data = get_ocr_data(img)
            
            if not data:
                print("[!] No image data obtained (Wayland issue?). Retrying...")
                time.sleep(1)
                continue

            # 1. CHECK STATUS: Are we already Correct?
            is_correct = False
            for text in data['text']:
                if "Correct!" in text or "Excellent" in text:
                    is_correct = True
                    break
            
            if is_correct:
                print(" -> 'Correct!' detected. Skipping options.")
            
            # 2. NAVIGATION (Next/Continue)
            # If is_correct is True, we try even harder to find Next
            nav_clicked = False
            
            # Try Text Search (Loose match)
            if click_text("Next", data, strict=False) or \
               click_text("Continue", data, strict=False) or \
               click_text("Submit", data, strict=False):
                nav_clicked = True
            
            # Try Color Search (Fallback for Orange Button)
            if not nav_clicked and is_correct:
                print("   (Text 'Next' not found, looking for Orange Button...)")
                if click_orange_next_button(img):
                    nav_clicked = True

            if nav_clicked:
                print(" -> Navigation clicked. Waiting for page load...")
                time.sleep(3.0)
                continue
                
            # If we are correct but couldn't find the button, loop/wait
            if is_correct:
                print(" -> Correct, but cannot find 'Next' button yet. Waiting...")
                time.sleep(1)
                continue

            # 3. QUIZ ANSWERING (Only if NOT correct)
            check_found = False
            for text in data['text']:
                if "Check" in text:
                    check_found = True
                    break
            
            if check_found:
                print(" -> 'Check' detected. Finding choices (Color Detection)...")
                
                # UPDATED: Pass image to find_option_coordinates (CV based)
                option_coords = find_option_coordinates(img)
                
                if not option_coords:
                    print("   [!] No options found (Teal circles not detected). Retrying...")
                    time.sleep(1)
                    continue
                
                print(f"   -> Found {len(option_coords)} potential options.")
                
                # Bruteforce Loop
                for i, (opt_x, opt_y) in enumerate(option_coords):
                    print(f"   [Attempt {i+1}] Clicking Option at ({opt_x}, {opt_y})")
                    pyautogui.moveTo(opt_x, opt_y)
                    pyautogui.click()
                    time.sleep(0.3)
                    
                    # Click Check
                    # Refresh image/data to find Check button exactly
                    img_check = get_screen_image()
                    data_check = get_ocr_data(img_check)
                    if not click_text("Check", data_check):
                        print("   [!] Could not click Check. Retrying...")
                        continue
                    
                    time.sleep(1.5) # Wait for grading
                    
                    # RESCAN: Did we become Correct?
                    img_after = get_screen_image()
                    data_after = get_ocr_data(img_after)
                    if not data_after: continue

                    # Look for Navigation or Correct text
                    success = False
                    for t in data_after['text']:
                        if t in ["Next", "Continue", "Finish"] or "Correct!" in t or "Excellent" in t:
                            success = True
                            break
                    
                    # Also try color search for the orange button as a success indicator
                    if not success:
                         if click_orange_next_button(img_after):
                             success = True
                             print("   -> Orange Next button found & clicked!")

                    if success:
                        print("   -> Success! Breaking loop.")
                        break # Break inner loop -> Main loop will handle clicking text Next if needed
                    
                    print("   -> Wrong answer. Trying next option...")

            else:
                print(" -> No 'Check' or Navigation found. Waiting...")
                time.sleep(1)

    except KeyboardInterrupt:
        print("\n[!] Ctrl+C detected. Exiting.")

if __name__ == "__main__":
    run_ocr_bot()
