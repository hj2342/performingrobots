#!/usr/bin/env python3
"""
Script to generate ALL Husband dialogues for the UPDATED play script.
CLEAN SEQUENTIAL NUMBERING: track001.mp3 through track023.mp3
NO GAPS - Complete fresh start!
"""

import requests
import json
import time
import os
import base64
from pathlib import Path
from datetime import datetime

# Hume AI credentials
API_KEY = "qPSc8vFt1nFp04h5ONRit3JXBM6g2AbEAyrgA1aUZ3CF8xSc"

# ALL dialogues for the UPDATED script - SEQUENTIAL NUMBERING
HUSBAND_DIALOGUES = [
    # Track 1 - Scene 1: Opening
    "You've been practicing. That spin almost looked graceful.",
    
    # Tracks 2-6 - Scene 2: Confrontation at home
    "It was just harmless dancing, relax. I was just feeling fly and wanted to have some fun.",
    "Honey, you're overreacting.",
    "Well, maybe if you were willing to dance with me more",
    "GO TO BED!",
    "Wow, I've never heard that one before! Divorce over a little spin? Is this your new punchline to guilt-trap me?!! You want to leave me? Fine. But you're not taking my child. That's my legacy. That's mine.",
    
    # Scene 3: Attorneys (NO HUSBAND LINES)
    
    # Tracks 7-9 - Scene 4: Text argument
    "I can't believe we're dividing our entire life over text.",
    "Visual superiority?",
    "Did I just lose custody of the Wi-Fi?",
    
    # Tracks 10-15 - Scene 4 Part 2: Private reckoning with child
    "It's just stuff, kid. Your mother's being dramatic. And the Judge—she just likes smoothies. Don't read into it.",
    "Go put that phone down.",
    "What? Give me that.",
    "Stop! That's private—hand it over!",
    "You don't understand adult relationships. This was a rough patch. She's not innocent either.",
    "Where did you even find that?",
    
    # Tracks 16-23 - Scene 5: Courtroom
    "Wait—I didn't actually—",
    "Why do YOU have HER phone?",
    "IT LOOKS LIKE YOU WERE SLEEPING WITH THE JUDGE!",
    "I cannot BELIEVE this— You accused ME— OVER A DANCE— While you were— with the JUDGE?!",
    "So what now?",
    "You're not helping.",
    "Hold on. Why is the Judge suddenly defending her?",
]

# Scene and emotion context for each dialogue
DIALOGUE_CONTEXT = [
    ("Scene 1 - Opening", "Playful/Flirtatious", "Speaking to Best Friend while dancing"),
    
    ("Scene 2 - Confrontation", "Defensive/Casual", "Defending his dancing behavior"),
    ("Scene 2 - Confrontation", "Dismissive/Patronizing", "Dismissing wife's concerns"),
    ("Scene 2 - Confrontation", "Accusatory/Deflecting", "Making excuses"),
    ("Scene 2 - Confrontation", "Angry/Frustrated", "Yelling at child with wife"),
    ("Scene 2 - Confrontation", "Sarcastic then Aggressive", "Responding to divorce threat"),
    
    ("Scene 4 - Text Fight", "Weary/Exasperated", "Sighing about texting situation"),
    ("Scene 4 - Text Fight", "Confused/Annoyed", "Confused by wife's message"),
    ("Scene 4 - Text Fight", "Baffled/Defeated", "Realizing he lost the argument"),
    
    ("Scene 4.2 - Private", "Dismissive/Irritated", "Dismissing child's observations"),
    ("Scene 4.2 - Private", "Authoritative/Frustrated", "Commanding child"),
    ("Scene 4.2 - Private", "Urgent/Panicked", "Demanding phone back"),
    ("Scene 4.2 - Private", "Panicked/Desperate", "Panicking as child reads texts"),
    ("Scene 4.2 - Private", "Defensive/Rationalizing", "Trying to justify himself"),
    ("Scene 4.2 - Private", "Quiet/Defeated/Guilty", "Defeated and caught"),
    
    ("Scene 5 - Courtroom", "Defensive/Protesting", "Denying accusation"),
    ("Scene 5 - Courtroom", "Angry/Confused", "Raging at revelation"),
    ("Scene 5 - Courtroom", "Yelling/Explosive", "Explosive realization"),
    ("Scene 5 - Courtroom", "Breaking/Furious/Betrayed", "Breaking down in anger"),
    ("Scene 5 - Courtroom", "Broken/Resigned", "After judgment"),
    ("Scene 5 - Courtroom", "Frustrated/Tired", "To Best Friend"),
    ("Scene 5 - Courtroom", "Suspicious/Confused", "Noticing suspicious behavior"),
]


def generate_audio_hume(text, output_filename):
    """Generate audio using Hume AI's TTS API (FREE TIER COMPATIBLE)"""
    
    url = "https://api.hume.ai/v0/tts"
    
    headers = {
        "X-Hume-Api-Key": API_KEY,
        "Content-Type": "application/json"
    }
    
    payload = {
        "utterances": [
            {
                "text": text,
                "description": "A confident, mature male voice with emotional depth"
            }
        ],
        "format": {
            "type": "mp3"
        }
    }
    
    try:
        response = requests.post(url, headers=headers, json=payload, timeout=60)
        
        if response.status_code == 200:
            result = response.json()
            
            if 'generations' in result and len(result['generations']) > 0:
                generation = result['generations'][0]
                
                if 'audio' in generation:
                    audio_bytes = base64.b64decode(generation['audio'])
                    
                    with open(output_filename, 'wb') as f:
                        f.write(audio_bytes)
                    return True, "Success"
                else:
                    return False, "No audio data in generation"
            else:
                return False, f"Unexpected response format"
        elif response.status_code == 429:
            return False, "RATE_LIMIT"
        else:
            try:
                error_data = response.json()
                return False, f"Error {response.status_code}: {error_data}"
            except:
                return False, f"Error {response.status_code}: {response.text}"
            
    except Exception as e:
        return False, f"Exception: {str(e)}"


def main():
    """Main function to process all dialogues"""
    
    output_dir = Path("husband_audio")
    output_dir.mkdir(parents=True, exist_ok=True)
    
    print(f"╔══════════════════════════════════════════════════════════════════╗")
    print(f"║           FRESH START - CLEAN SEQUENTIAL NUMBERING              ║")
    print(f"║                 Tracks 001-023 (No Gaps!)                       ║")
    print(f"╚══════════════════════════════════════════════════════════════════╝")
    print(f"\nOutput directory: {output_dir.absolute()}")
    print(f"Total tracks: {len(HUSBAND_DIALOGUES)}\n")
    
    # Calculate total characters
    total_chars = sum(len(d) for d in HUSBAND_DIALOGUES)
    print(f"Total characters: {total_chars}")
    print(f"Free tier limit: 10,000 characters/month (~10 minutes)")
    print(f"Estimated audio: ~{total_chars/100} minutes\n")
    
    if total_chars > 10000:
        print(f"⚠️  WARNING: This exceeds free tier limit!")
        print(f"   You may hit rate limits during generation.")
        print(f"   The script will pause and you can resume later.\n")
    
    print("═" * 70)
    print("TRACK BREAKDOWN:")
    print("═" * 70)
    print("Track 001       - Scene 1 (Opening)")
    print("Tracks 002-006  - Scene 2 (Confrontation)")
    print("                  [Scene 3 has no husband lines]")
    print("Tracks 007-009  - Scene 4 (Text Fight)")
    print("Tracks 010-015  - Scene 4.2 (Private Reckoning)")
    print("Tracks 016-023  - Scene 5 (Courtroom)")
    print("═" * 70)
    print()
    
    input("Press Enter to start generation...")
    print()
    
    successful = 0
    failed = 0
    rate_limited = False
    
    for idx, dialogue in enumerate(HUSBAND_DIALOGUES, start=1):
        filename = output_dir / f"track{idx:03d}.mp3"
        scene, emotion, context = DIALOGUE_CONTEXT[idx - 1]
        
        display_text = dialogue[:60] + "..." if len(dialogue) > 60 else dialogue
        
        print(f"[{idx:03d}/{len(HUSBAND_DIALOGUES)}] {display_text}")
        print(f"      Scene: {scene}")
        print(f"      Emotion: {emotion}")
        print(f"      Requesting audio generation...")
        
        success, message = generate_audio_hume(dialogue, filename)
        
        if success:
            print(f"      ✓ Generated: {filename.name}")
            successful += 1
            time.sleep(2)  # Slower rate to avoid hitting limit
        elif message == "RATE_LIMIT":
            print(f"      ⏸️  RATE LIMIT HIT!")
            print(f"\n{'='*70}")
            print(f"Rate limit reached after generating {successful} file(s).")
            print(f"\n📊 Progress:")
            print(f"  Completed: {successful}/{len(HUSBAND_DIALOGUES)}")
            print(f"  Remaining: {len(HUSBAND_DIALOGUES) - successful}")
            print(f"\n⏰ Wait 1 hour and run this script again.")
            print(f"   Already generated files will be skipped automatically.")
            rate_limited = True
            break
        else:
            print(f"      ✗ Failed: {message}")
            failed += 1
            time.sleep(2)
        
        print()
    
    if not rate_limited:
        print("="*70)
        print(f"\n🎉 ALL TRACKS GENERATED!")
        print(f"  Successful: {successful}")
        print(f"  Failed: {failed}")
        print(f"  Output directory: {output_dir.absolute()}")
        print()
        print("="*70)
        print("FILES GENERATED (Sequential 1-23):")
        print("="*70)
        for i in range(1, len(HUSBAND_DIALOGUES) + 1):
            print(f"  track{i:03d}.mp3")
        print("="*70)
        print()
        print("NEXT STEPS:")
        print("1. Format SD card as FAT32")
        print("2. Copy ALL 23 files to SD card root")
        print("3. Insert SD card into Music Maker Shield")
        print("4. Update Arduino code for tracks 1-23")
        print("5. Test!")
        print("="*70)
    
    # Create reference file
    reference_file = output_dir / "dialogue_reference.txt"
    with open(reference_file, 'w') as f:
        f.write("HUSBAND'S DIALOGUES - UPDATED SCRIPT\n")
        f.write("CLEAN SEQUENTIAL NUMBERING: Tracks 001-023\n")
        f.write("="*70 + "\n\n")
        f.write(f"Generated: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
        f.write(f"Total tracks: {len(HUSBAND_DIALOGUES)}\n")
        f.write(f"Total characters: {total_chars}\n\n")
        
        current_scene = ""
        for idx, dialogue in enumerate(HUSBAND_DIALOGUES, start=1):
            scene, emotion, context = DIALOGUE_CONTEXT[idx - 1]
            
            # Add scene headers
            if scene.split(" - ")[0] != current_scene:
                scene_name = scene.split(" - ")[0]
                f.write("\n" + "="*70 + "\n")
                f.write(f"{scene_name.upper()}\n")
                f.write("="*70 + "\n\n")
                current_scene = scene_name
            
            f.write(f"track{idx:03d}.mp3\n")
            f.write(f"Scene: {scene}\n")
            f.write(f"Emotion: {emotion}\n")
            f.write(f"Context: {context}\n")
            f.write(f'Dialogue: "{dialogue}"\n')
            f.write(f"Characters: {len(dialogue)}\n\n")
            f.write("-"*70 + "\n\n")
        
        f.write(f"\nSUMMARY\n")
        f.write("="*70 + "\n")
        f.write(f"Total tracks: {len(HUSBAND_DIALOGUES)}\n")
        f.write(f"Total characters: {total_chars}\n")
        f.write(f"Estimated duration: ~{total_chars/100} minutes\n")
    
    print(f"\nReference file created: {reference_file}")


if __name__ == "__main__":
    main()
