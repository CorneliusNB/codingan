from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time
import sys
import select

# --- HELPER FUNCTIONS ---

def is_enter_pressed():
    """
    Checks if the user pressed ENTER (or any key) on stdin without blocking.
    Works on Linux/Mac (perfect for NixOS).
    """
    try:
        # Check if there is data ready to be read on stdin
        if select.select([sys.stdin], [], [], 0)[0]:
            # Read the line to clear the buffer
            sys.stdin.readline()
            return True
    except:
        pass
    return False

def skip_media(driver):
    """Finds video or audio elements and fast-forwards them to the end."""
    try:
        driver.execute_script("""
            document.querySelectorAll('video, audio').forEach(media => {
                media.currentTime = 999999; 
                media.pause();
            });
        """)
        # print("   (Media skipped)")
    except Exception:
        pass

def click_next_button(driver):
    """Searches for and clicks Next/Submit buttons."""
    # Reduced sleep slightly to make it snappier inside the loop
    time.sleep(0.5) 

    # Strategy 1: Text-based Search
    # Added "Yes" to handle the Submit confirmation popup
    next_texts = ["Next", "Submit", "Continue", "Finish", "Yes"]
    
    for text in next_texts:
        try:
            xpath = f"//*[contains(translate(normalize-space(text()), 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz'), '{text.lower()}')]"
            btns = driver.find_elements(By.XPATH, xpath)
            for btn in btns:
                if btn.is_displayed():
                    print(f" -> Found navigation button: '{text}'")
                    try:
                        btn.click()
                    except:
                        driver.execute_script("arguments[0].click();", btn)
                    return True
        except:
            continue

    # Strategy 2: Class-based Search (Specific classes provided by user)
    # User identified class: "d-flex ... bl-button__inside secondary-color ..."
    # We target the stable part: bl-button__inside AND secondary-color
    try:
        xpath_class = "//div[contains(@class, 'bl-button__inside') and contains(@class, 'secondary-color')]"
        candidates = driver.find_elements(By.XPATH, xpath_class)
        
        for btn in candidates:
            if btn.is_displayed():
                # Avoid clicking 'Check' if it shares classes (though Check usually has text 'Check')
                btn_text = btn.text.lower()
                if "check" not in btn_text:
                    print(f" -> Found navigation button (by class: {btn.get_attribute('class')})")
                    try:
                        btn.click()
                    except:
                        driver.execute_script("arguments[0].click();", btn)
                    return True
    except:
        pass

    return False

# --- MODES ---

def run_quiz_mode(driver):
    """
    Mode 1: Quiz Loop
    - Checks for 100% stop condition.
    - Bruteforces options.
    - Clicks Check.
    - Checks if Correct (Next button appears) -> If yes, Skips rest.
    """
    print("\n[!] QUIZ MODE STARTED. Press ENTER to return to menu.")
    options_selector = (By.CSS_SELECTOR, "button.MuiButtonBase-root.bl-w-full")
    check_btn_selector = (By.XPATH, "//*[normalize-space(text())='Check']")
    
    try:
        while True:
            # 0. Check for Stop Key (Enter)
            if is_enter_pressed():
                print("\n[!] Stop key detected. Returning to menu...")
                break

            # 1. Stop Condition (Optional)
            try:
                if "100" in driver.find_element(By.TAG_NAME, "body").text:
                    print(">>> Found '100'. Quiz might be done.")
            except:
                pass

            print("\n>>> Quiz Cycle... (Press ENTER to stop)")
            
            # 2. Find Options
            try:
                current_options = driver.find_elements(*options_selector)
            except:
                current_options = []

            if not current_options:
                print("   (No answer options found. Checking for Next/Submit/Yes button...)")
                # Try clicking Next/Submit/Yes directly if no options are present (e.g. info slide or popup)
                if click_next_button(driver):
                    print(" -> Moving to next page...")
                    time.sleep(1.5)
            else:
                next_clicked_successfully = False
                
                for i in range(len(current_options)):
                    # Check stop key inside inner loop too for responsiveness
                    if is_enter_pressed():
                        print("\n[!] Stop key detected. Returning to menu...")
                        return

                    # Re-locate elements to avoid stale reference
                    current_options = driver.find_elements(*options_selector)
                    if i >= len(current_options): break

                    print(f" -> Clicking Option {i + 1}")
                    try:
                        current_options[i].click()
                    except:
                        driver.execute_script("arguments[0].click();", current_options[i])
                    
                    time.sleep(0.1)

                    # Click Check
                    try:
                        check_btn = driver.find_element(*check_btn_selector)
                        try:
                            check_btn.click()
                        except:
                            driver.execute_script("arguments[0].click();", check_btn)
                    except:
                        pass 
                    
                    # --- NEW LOGIC: Verify Correctness First ---
                    time.sleep(0.5) # Wait for feedback to appear
                    
                    # We check visible text for "Correct!" or "Excellent"
                    # User warned: Next button might exist even if incorrect, so we MUST confirm text first.
                    try:
                        body_text = driver.find_element(By.TAG_NAME, "body").text
                        if "Correct!" in body_text or "Excellent" in body_text or "Well done" in body_text:
                            print("   -> Feedback says 'Correct!'. Clicking Next...")
                            if click_next_button(driver):
                                next_clicked_successfully = True
                                time.sleep(1.5) 
                                break # Correct answer found, move to next question
                        else:
                            print("   -> No 'Correct!' message found. Trying next option...")
                    except:
                        pass
                
                # If we went through all options and didn't click Next (or last one was wrong),
                # try one last time (though usually captured inside the loop).
                if not next_clicked_successfully:
                    print(" -> Options exhausted. Checking for Next button...")
                    if click_next_button(driver):
                         print(" -> Moving to next page...")
                         time.sleep(1.5)
                    else:
                         print(" -> No 'Next' button found yet. Retrying...")
                         time.sleep(1)

    except KeyboardInterrupt:
        print("\n[!] Ctrl+C detected. Stopping Quiz Mode...")

def run_video_mode(driver):
    """
    Mode 2: Video Loop
    - Skips media.
    - Clicks Next.
    """
    print("\n[!] VIDEO MODE STARTED. Press ENTER to return to menu.")
    try:
        while True:
            if is_enter_pressed():
                print("\n[!] Stop key detected. Returning to menu...")
                break

            print("\n>>> Video Cycle... (Press ENTER to stop)")
            skip_media(driver)
            
            if click_next_button(driver):
                print(" -> Moving to next page...")
                time.sleep(2)
            else:
                print(" -> Waiting for Next button...")
                time.sleep(1)
    except KeyboardInterrupt:
        print("\n[!] Ctrl+C detected. Stopping Video Mode...")

# --- MAIN MENU ---

def main():
    options = webdriver.ChromeOptions()
    
    # Cookie preferences for login support
    prefs = {
        "profile.default_content_setting_values.cookies": 1,
        "profile.block_third_party_cookies": False,
        "network.cookie.cookieBehavior": 0
    }
    options.add_experimental_option("prefs", prefs)

    driver = webdriver.Chrome(options=options)

    try:
        # Automatically navigate to target URL
        driver.get("https://lms.binus.ac.id/beelingua/")

        print("--- Browser Launched ---")
        print("1. Log in manually if needed.")
        print("2. Navigate to the specific section you want to automate.")
        input("3. Press ENTER here to see the menu...")

        while True:
            print("\n" + "="*40)
            print(" SELECT AUTOMATION MODE")
            print("="*40)
            print(" 1. QUIZ MODE  (Bruteforce answers -> Next)")
            print(" 2. VIDEO MODE (Skip video -> Next)")
            print(" Q. QUIT")
            print("="*40)
            
            try:
                choice = input("Enter choice: ").lower().strip()

                if choice == '1':
                    run_quiz_mode(driver)
                elif choice == '2':
                    run_video_mode(driver)
                elif choice == 'q':
                    print("Exiting...")
                    break
                else:
                    print("Invalid choice.")
            except KeyboardInterrupt:
                print("\n[!] Ctrl+C detected in menu. Press 'q' to quit nicely.")
                continue

    except Exception as e:
        print(f"An error occurred: {e}")

    finally:
        print("Closing browser...")
        driver.quit()

if __name__ == "__main__":
    main()
