# Robot Build Journal

# Performing Robots Journal - Your Entry

## 10/02/2025 - Initial Assembly and Motor Troubleshooting:
Today marked the beginning of our robot construction journey. Working alongside my teammate, I focused primarily on understanding the base mechanics and electrical systems. While my partner tackled the Arduino board diagnostics, I concentrated on preparing the wooden components and testing the motor connections systematically. 

The troubleshooting process was enlightening watching the methodical elimination of potential failure points taught me the importance of patience in robotics. When we discovered the Arduino fault, I realized how easy it is to assume external wiring issues when the problem lies within core components.

My main contribution involved measuring and preparing the Alpine wood plank for the spine structure. I learned proper techniques for ensuring structural stability particularly how weight distribution affects a tall, vertical robot. The drilling process required precision to avoid splitting the wood, especially near edges.

## 10/03/2025 - Character Design and Artistic Integration:
Today shifted from pure mechanics to the artistic side of robotics something I found surprisingly challenging. While my teammate worked on the shoulder assembly, I focused on understanding how our character's proportions would translate to functional movement.

The Walter White face cutout process was meticulous. I assisted by holding materials steady and helping with measurements. What struck me most was the balance between aesthetic accuracy and functional practicality we needed the face light enough not to strain the servo, yet rigid enough to maintain its shape during movement.

I spent considerable time thinking about how to attach the shredded body costume in a way that wouldn't interfere with servo operation or obscure any components we'd need to access later. This forward-thinking approach proved valuable in later sessions.

## 10/07/2025 - Arm Mechanics and Movement Planning:
Today I took a more active role in conceptualizing the arm movement system. While my partner cut the planks, I sketched out different servo placement options and their respective range-of-motion possibilities. The decision to incorporate two-dimensional movement excited me - it would make our robot far more expressive.

I researched servo torque requirements for lifting wooden arms and calculated approximate weight loads. This mathematical planning phase, though less visually impressive than construction, felt crucial to ensuring our servos wouldn't burn out under strain.

The video of progress shows how much more "alive" the robot appears with proper arm proportions. I'm beginning to understand that robot performance isn't just about technical function - it's about creating believable character presence.

## 10/08/2025 - Servo Integration Challenges:
This evening presented fascinating problem-solving opportunities. While my teammate wrestled with the face servo mounting, I worked on organizing our wiring strategy. The copper wire mesh solution my partner developed was brilliant - it taught me that sometimes unconventional approaches work better than standard adhesives.

I prepared the pan-tilt assembly components, organizing all M3 bolts and nuts before installation. My contribution was ensuring we had proper spacing measurements to avoid the servo interference issues. I learned that in robotics, a few millimeters can mean the difference between smooth operation and mechanical binding.

The three-servo setup (face, shoulder, forearm) creates exciting performance possibilities. I'm already imagining choreographed movements that could make Walter White's characteristic gestures recognizable.

## 10/09/2025 - Electronics Architecture and System Integration:
Today I focused intensively on understanding our electronics hierarchy. While the Arduino Mega 2560 and custom PCB were being installed, I documented the pin connections meticulously - D20, D21, D19, D17, D16, D18. Creating a clear wiring diagram became my priority, knowing we'd need this reference during programming and troubleshooting.

I also worked on cable management strategy, using zip ties and planning wire routes that wouldn't interfere with movement. The challenge of keeping multiple servo cables organized while allowing for full range of motion required creative thinking.

The 5mm M3 bolt swap was a relief - I had been concerned about the mechanical interference. This experience reinforced how crucial proper hardware selection is to final functionality.

## 10/16/2025 - Programming Logic and Mechanical Refinement:
Fall break lab session - I arrived with specific goals around code architecture. While my teammate experimented with servo control, I worked on developing a modular code structure that would allow independent servo testing before integration.

The involuntary servo movement issue fascinated me from a debugging perspective. I researched power supply requirements and discovered the same concerns my partner noted - our 35kg servos drawing significant amperage might exceed the power bank's regulated output capacity. I suggested we might need a dedicated 5V/6V power supply with higher current rating, possibly 10A or more, to prevent voltage drops causing erratic behavior.

I spent time refining the physical structure - the detail work of covering sharp edges, tightening connections, and improving overall build quality. These finishing touches transform a functional prototype into a reliable performance robot.

The mouth servo installation was particularly satisfying to observe. The mechanical linkage between servo horn and jaw movement required careful positioning - too much resistance and the servo would strain, too loose and movement would be sloppy.

**Technical Reflection:**
The power supply issue highlights a crucial lesson - computational control is meaningless without proper electrical infrastructure. Moving forward, I'm researching regulated DC power supplies and considering whether we need separate power domains (one for Arduino logic, one for servo motors) to prevent current draw from motors affecting microcontroller stability.

**Artistic Reflection:**
Our robot is becoming a character, not just a machine. The mouth movement, combined with potential shoulder and arm choreography, creates opportunities for genuine performance. I'm thinking about how we might program reaction behaviors or characteristic gestures that reference the source material.

##10/23/2025 - Leg Stabilization and Servo Calibration:

Today’s session focused on restoring the robot’s lower body stability. The previous leg joints had shown uneven weight distribution, causing slight wobble during movement. I took the lead in reinforcing the leg structures — re-drilling slightly offset holes to align with the robot’s center of gravity and tightening the mounting brackets to eliminate unwanted flex.

Once the mechanical foundation felt stable, we moved into servo calibration. Using the Arduino’s serial interface, I began developing a servo calibration routine to define each motor’s neutral position. This step proved essential for ensuring synchronized, fluid motion — especially in multi-servo sequences where even a few degrees of offset can create unnatural posture or joint stress.

I also designed preliminary movement sequences to test the robot’s full range of motion. These tests helped reveal torque inconsistencies between the left and right sides, likely due to minor servo variance. I noted these discrepancies for software compensation later. Toward the end of the session, we brainstormed the integration of simple sensors — possibly ultrasonic for distance detection or a microphone module for sound reactivity. The idea of making the robot responsive to its environment adds an exciting layer of interactivity we both want to pursue.

##10/30/2025 - Visual Enhancements and Radio Communication:

Today marked a major leap in expressiveness for our robot. We began by installing LED lights for the eyes, carefully embedding them behind the face plate to achieve a natural glow effect without visible hardware. My main contribution was soldering the resistors and wiring the LEDs to the appropriate digital pins, ensuring consistent brightness and avoiding voltage overload.

On the coding side, I worked on the LED control functions — programming patterns to simulate blinking and emotional responses (idle pulse, alert flash, and synchronized eye movement cues). The subtle lighting effects brought surprising personality to the robot’s expression, especially in dim environments. Started with the setup of the nRF Servo Mega Shield setup for receiver transmitter communication.

##10/31/2025:Radio Communication
We tackled the nRF Servo Mega Shield setup to establish wireless communication between the transmitter and receiver. I attached the radio to aurdino then started with debugging the radio initialization issues; tracing back the failure to a mismatched CE/CSN pin configuration. After correcting the wiring and recompiling the code, we successfully uploaded the transmitter and receiver sketches. The moment the remote control finally communicated with the main board felt like a breakthrough.



##11/02/2025 - Radio Debugging Breakthrough:
Came in early today determined to fix the radio communication. Started by swapping the nRF modules between transmitter and receiver to isolate whether it was a hardware or configuration issue. Both modules worked individually when tested with simple ping-pong sketches.
The breakthrough came when I discovered the CE/CSN pin configuration in our code didn't match the actual shield wiring. The shield used different pins than the standard setup I'd been referencing. After correcting the pin definitions and recompiling, we successfully uploaded the transmitter and receiver sketches. The moment the remote control finally communicated with the main board felt like a breakthrough - seeing "Data received" in the serial monitor was incredibly satisfying.
Tested basic servo commands wirelessly. Movement was responsive but occasionally dropped packets. Made a note to implement acknowledgment protocols later.

##11/04/2025 - Music Board Research and Power Issues:
Today I focused on integrating the DFPlayer Mini music board. Spent time understanding the serial communication protocol and wiring requirements. Connected the module to the Mega using SoftwareSerial on pins 10 and 11, with the speaker output connected through a small amplifier circuit.
Initial power-up seemed fine, but when I tried to trigger audio playback while servos were moving, the board would reset. Classic power supply problem - the sudden current draw from servo movements was causing voltage dips that crashed the music board.
Researched solutions and decided we need to implement separate power regulation for the audio system. Ordered some capacitors to add to the power rails for smoothing. Also realized we need to properly format the SD card with the correct file structure for the DFPlayer.

##11/06/2025 - Shoulder Servo Weight Issues:
Today we fixed the servo with weight issues in the right shoulder. The servo was struggling to maintain position under load, causing the arm to droop during operation. After testing different positions and checking the mounting points, we confirmed it was a mechanical stress issue rather than electrical.
The servo would move to position but couldn't hold it - the arm would slowly sag down despite full power. Checked our calculations and realized the 20kg servo was right at its limit with the arm weight and leverage. Ordered a 35kg servo as replacement but it won't arrive until next week.
What features remain to be implemented? Radio connection stability improvements, music board integration with proper power management, and the emotional lighting system I've been planning.

Nov 6
What did you accomplish for today November 6?
fixed the servo with weight issues in thr right shoulder
What features remain to be implemented?
radio connection issue and music board
What will you accomplish for next Thursday November 11?
Fixed the reciver transmitter issue and soldered the music board, connection is estabisled sucessfully and using neo strips to great a aura around the robot during emotions and also getting inspiration from cartoons to bring emotions like jealousy



##11/08/2025 - Emotional Expression Research:
Spent today in pure research mode since we're waiting on parts. Diving deep into how cartoons and animations convey emotions through color and light. Watched clips from Inside Out, Steven Universe, Adventure Time, and classic Disney films frame by frame.
Created a detailed mood board documenting color associations:

Anger: Sharp reds, aggressive pulses, quick transitions
Happiness: Warm yellows and oranges, bouncy rhythms, sparkles
Sadness: Deep blues, slow waves, dimming effects
Fear: Purple and dark blue, erratic flashing, building intensity
Jealousy: Sickly greens, uneven pulses, shadowy effects

What struck me most was how timing and movement pattern matter as much as color choice. Smooth transitions read as calm, while sharp changes create tension. I sketched out timing diagrams for each emotion - essentially choreographing light the way you'd choreograph dance.

##11/09/2025 - NeoPixel Prototype Testing:
Started building my emotional lighting system today. Connected a small 8-LED NeoPixel strip to an Arduino Uno as a test bed - didn't want to risk damaging our main robot during experimentation.
Wrote basic test patterns for each emotion I'd researched. The coding was straightforward but the visual results were fascinating. Even with just 8 LEDs, the different patterns created distinct moods:
Anger test: Pulsing red (255,0,0) with sharp 100ms transitions - visually aggressive
Happiness test: Alternating yellow-orange with 300ms fade - felt cheerful and energetic
Sadness test: Deep blue wave (0,0,150) with 2-second cycles - genuinely melancholic
Jealousy test: Green pulse (100,200,50) with irregular timing - unsettling effect
Documented all the RGB values and timing parameters in a spreadsheet. The dimming curves matter enormously - exponential fade looks much more natural than linear.

##11/11/2025 - First Performance Demonstration and Crown Planning:
Major milestone today! We were able to play any sound clip (including the iconic "laugh?" line) and successfully drive our robot. Volta White - our creation belonging to Hariharan and Ali - performed flawlessly during the demonstration. The combination of audio playback and wireless control finally working together felt incredibly rewarding.
The class response was encouraging, though I'm already thinking about refinements. The timing between audio and movement needs tighter synchronization for truly believable performance.
After the demo, I started planning the NeoPixel crown implementation. Measured the robot's head circumference and calculated I'd need approximately 16 LEDs for good coverage. Sketched mounting designs that would create a halo effect without interfering with the face servo or blocking the wig we plan to add later.
Nov 11
who able to play any sound clip (who was that?) and who was able to drive their robot? It was our robot Volta White which is the hisband belongs to Hariharan and Ali

##11/13/2025 - Crown Soldering Begins:
Today was all about careful soldering work. Cut the NeoPixel strip to the right length and began forming it into a crown shape. The trick was maintaining the strip's flexibility while ensuring each solder joint was solid.
Worked on one section at a time: solder the connection points, test continuity with multimeter, verify LEDs light up, move to next section. Tedious but necessary - one bad joint would break the entire chain.
Made it through about half the crown before calling it a day. My eyes were getting tired and precision was suffering. Better to continue tomorrow fresh than risk a mistake now. The completed sections tested perfectly though - all LEDs responding to test signals.

##11/15/2025 - Crown Completion and Initial Arduino Testing:
Finished the remaining crown soldering this morning. The circular shape came out well - uniform spacing between pixels and solid connections throughout. Added heat shrink tubing over exposed solder joints for protection and durability.
Connected the crown to an Arduino Mega for testing. Wrote test code to cycle through all the emotional states we'd defined. Ran into an immediate problem - some LEDs were significantly dimmer than others. Grabbed my magnifying glass and found two cold solder joints where the connection was weak.
Reflowed those joints with fresh solder and suddenly everything looked perfect. The crown lit up beautifully, casting ambient colored light that genuinely affected the perceived mood. Testing each emotion:

Anger: Aggressive red waves looked fantastic
Happiness: Yellow sparkle pattern was delightful
Jealousy: The green pulse was appropriately creepy

Very pleased with how this turned out. The crown adds so much character presence.

##11/17/2025 - Eye and Crown Integration Nightmare:
Today I learned an important lesson about timing conflicts in Arduino code. Decided to integrate the eye LEDs with the crown NeoPixels so both systems reflect the same emotional state simultaneously.
Started by writing a unified emotion control function that takes an emotion parameter and triggers appropriate patterns in both subsystems. Seemed straightforward in theory.
The reality was frustrating. The NeoPixel library uses timing-sensitive protocols that don't play well with other code. When I tried to update both eyes and crown, the NeoPixels would glitch - random colors, flickering, or complete freezeouts.
Spent hours debugging. Discovered the issue was blocking delays in my LED blink code interfering with the NeoPixel update timing. The library needs precise timing to communicate with the strip, and any interruption causes data corruption.
Research led me to non-blocking timing approaches using millis(). Started refactoring all the timing code to track elapsed time rather than using delay() commands. Not finished yet but I can see this is the right path.

##11/18/2025 - Servo Replacement and Non-Blocking Code Refactor:
 I  replaced the servo horn crown with a higher quality  one that came with the new servo. The star plastic horn we'd been using showed stress cracks - another sign we'd been overloading the old servo.T he new 35kg servo! Immediately began installation. Had to slightly enlarge the mounting holes since the new servo had a different horn size, but the process was straightforward.
After installation and recalibration, the improvement was dramatic. The arm moved smoothly with no strain, held position solidly even when pushed, and responded quickly to commands. Tested the full range of motion multiple times - absolutely solid performance.
Running movement sequences that had caused the old servo to struggle, the new one handled them effortlessly. The difference between marginal and adequate torque rating is night and day.


##11/19/2025 - The Great Robot Catastrophe:
Came into the lab this afternoon to find our robot on the floor. Someone had knocked it over - not sure if it was accidental or carelessness, but the damage was extensive.
The chest plate had broken completely free, screws ripped out of the wood. The back panel was hanging by a single mounting point. Worst of all, the face assembly - the piece we'd spent hours perfecting - was completely dismantled. The jaw mechanism was bent, the face plate cracked, and the eye LED wiring pulled loose.
Stood there for a moment just processing the damage. Then got to work.
Started with structural assessment. The main spine was intact - good news. The servo mounts hadn't shifted. Most damage was to cosmetic and mounting elements rather than core functionality.
Spent the next four hours in careful repair mode. Reattached the chest plate with additional mounting screws and added small L-brackets for reinforcement. Fixed the back panel with stronger hardware. The face required the most work - straightening the jaw mechanism, regluing the face plate crack with epoxy, resoldering the eye LED connections that had torn free.
By evening the robot was structurally sound again, actually stronger than before with the reinforcements. Silver lining - the accident revealed weak points we could address before they failed during an actual performance. Added extra zip ties to secure wiring that could pull loose in another impact.
Still frustrated about the setback, but feeling accomplished about the repair work. Tomorrow I'll test all systems to make sure nothing else was damaged in the fall.

##11/20/2025 - Post-Catastrophe System Testing, Shield Design and costume design:
Started today by systematically testing every system after yesterday's disaster. Ran through servo movements - all responding correctly. Tested eye LEDs - working perfectly after the resoldering. Crown NeoPixels - flawless. Even the radio communication seemed unaffected.
One problem emerged: the fall had loosened several breadboard connections for the NeoPixel system. Wires would occasionally lose contact during movement, causing the crown to flicker or go dark completely. This confirmed what I'd been thinking - we need a more permanent solution than breadboard connections.
Decided to design a custom shield to mount on the main Mega board for clean, reliable NeoPixel integration. Measured the Mega's header spacing carefully and marked out perfboard for cutting. Cut the board to size with a rotary tool - dusty work but satisfying.
Began the tedious process of soldering header pins to match the Mega's layout. This time I used a printed template taped to the board for precise pin placement. Learning from past mistakes - measure twice, solder once.

Feeling energized by finally having working systems, I decided to tackle the costume aspect. Needed a mental break from electronics anyway. Visited a local costume shop to find appropriate attire for our Walter White robot.
Found a navy captain's suit that had potential - the pants fit our robot's proportions perfectly, but the coat was too restrictive around the shoulder servos. I could see immediately that the fabric would bind against the servo housing during movement.
After discussing options with my teammate, we agreed a sleeveless vest would be the better choice. This would maintain a dressed, professional appearance while keeping the shoulder motors completely unobstructed. The freedom of movement is too important to sacrifice for aesthetics.

##11/21/2025 - Shield Wiring Crisis and Servo Failure:
Continued shield work this morning. Soldered bus lines for 5V and ground across the board, with connection points for the NeoPixel power. Double-checked polarity multiple times. Connected the NeoPixel data wire to digital pin 6.
Time to test. Plugged in power and immediately smelled something wrong - that distinctive electronics burning smell. Quickly disconnected everything. Panic set in as I traced connections with a multimeter.
Found the problem - in my hurry I'd connected positive 5V to what I thought was the power rail, but I'd actually bridged it to a data line heading to another component. Created a short circuit that could have damaged the Mega.
Carefully cut away the wrongly attached wires with flush cutters. Cleaned up the solder points and started over with the power connections, this time triple-checking every single wire before applying power. Connected positive 5V and ground properly, then soldered the NeoPixel data and power wires to the shield.
Final test - powered up slowly while watching for problems. Everything worked! NeoPixels lit up properly, no shorts, no burning smells.
But then disaster struck during movement testing. The right shoulder servo stopped responding during a basic test sequence. At first I thought it was a code issue - maybe I'd accidentally changed something while working on the shield.
Spent an hour debugging code. Verified pin assignments, checked servo initialization, uploaded minimal test sketches. The servo would occasionally twitch but wouldn't move to commanded positions. Sometimes it would move but couldn't hold position against even light pressure.
Consulted with the professor who suggested testing the servo in isolation. Disconnected it from the robot and connected to a separate Arduino with fresh code. Same behavior - erratic movement and inability to hold torque.
The professor noted we'd been pushing that 20kg servo pretty hard with the arm weight, especially after the fall might have stressed internal components. Likely combination of internal gear wear and the torque demands simply exceeding the motor's specifications. He recommended upgrading to a 35kg servo, which would give us significant safety margin.
Ordered a 35kg servo with priority shipping. Should arrive tomorrow or the day after. Frustrating to have another setback, but at least the shield is working now.

##11/22/2025 - Radio Communication Complete Failure:
The servo issue had a cascading effect. Today discovered the radio communication had completely failed - neither the transmitter nor receiver would initialize properly. Error messages suggested the nRF module wasn't being detected at all.
Started to wonder if yesterday's electrical short had damaged something beyond just the immediate circuit. Ran systematic diagnostics: re-uploaded code to both Arduino boards, checked every wire connection with a multimeter, verified power supply voltages, tested with different nRF modules we had as spares.
Nothing worked for the first three hours. The frustration was mounting - we're getting close to performance date and now basic functionality was broken. Genuinely started to panic about whether we'd meet our deadline.
Took a break, cleared my head, came back with fresh perspective. Decided to completely disassemble the radio connections and rebuild them from scratch with fresh Dupont wires. Stripped back to bare boards and methodically reconnected everything, documenting each connection as I went.
On the new upload, suddenly both boards showed proper initialization messages! The issue had been intermittent wire connections - likely damaged during the robot's fall days ago, then worsened by vibrations from testing.
When the connection re-established successfully, the relief was overwhelming. Tested extensively with multiple movement commands to ensure stability. Everything held solid. Added strain relief to all radio module connections using hot glue and zip ties to prevent future failures.
By evening, both the shield integration and radio communication were working reliably. Exhausting day but we're back on track.

##11/23/2025 - Code refactoring:
Continued the code refactoring .Created state machines for each animation pattern - tracking what step we're on, when we started that step, and when to transition to the next.
The code is significantly more complex now but the results are worth it. Both eye LEDs and crown NeoPixels update smoothly without interfering with each other. Added servo test movements and everything runs simultaneously without glitches.
The real test will be running this on the main robot with all servos active, audio playback, and radio control happening simultaneously. But I'm confident the architecture is sound now. Creating a proper timing framework was time-consuming but essential for reliable performance.
Then came the challenge of recording these dialogues. Started researching AI voice platforms. Found ElevenLabs which had exactly the quality I needed - their voice samples sounded incredibly natural and expressive.
Created an account, excited to get started. Selected a voice that matched our character. Began testing with our first dialogue line and... blocked. My IP address was rejected from their free tier.
Tried again thinking it was a temporary error. Same result. Checked their documentation and discovered geographic restrictions or usage limits must have flagged my IP. Incredibly frustrating - their quality was perfect for what we needed.
Spent the next two hours researching alternatives. Tried several platforms but quality was poor or pricing was too expensive. Getting desperate - we need these recordings done soon for integration. Finally discovered HumeAI right before midnight. They offer a free tier with 10,000 characters. Created an account and verified it works with my IP - success! Will start the actual voice generation tomorrow.


glue back and front to robot: half done (face) rest will be done on wednesday 26 nov 
3D arms: 25 nov
cases: done 
hands: 26 nov
clothing: done on nov 20
wire management: done on Monday Nov 24

### Progress Photos:
![IMG_0062](https://github.com/user-attachments/assets/f2525f6e-866a-44b1-ae06-0c0e2922bd07)
![IMG_0058](https://github.com/user-attachments/assets/baa65f53-3f83-460b-9027-806c4bbea2d0)
![IMG_0060](https://github.com/user-attachments/assets/49b70c36-675a-4567-b33c-15bbf7b6ebfd)
