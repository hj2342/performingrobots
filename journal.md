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

10/23/2025 - Leg Stabilization and Servo Calibration:

Today’s session focused on restoring the robot’s lower body stability. The previous leg joints had shown uneven weight distribution, causing slight wobble during movement. I took the lead in reinforcing the leg structures — re-drilling slightly offset holes to align with the robot’s center of gravity and tightening the mounting brackets to eliminate unwanted flex.

Once the mechanical foundation felt stable, we moved into servo calibration. Using the Arduino’s serial interface, I began developing a servo calibration routine to define each motor’s neutral position. This step proved essential for ensuring synchronized, fluid motion — especially in multi-servo sequences where even a few degrees of offset can create unnatural posture or joint stress.

I also designed preliminary movement sequences to test the robot’s full range of motion. These tests helped reveal torque inconsistencies between the left and right sides, likely due to minor servo variance. I noted these discrepancies for software compensation later. Toward the end of the session, we brainstormed the integration of simple sensors — possibly ultrasonic for distance detection or a microphone module for sound reactivity. The idea of making the robot responsive to its environment adds an exciting layer of interactivity we both want to pursue.

10/30/2025 - Visual Enhancements and Radio Communication:

Today marked a major leap in expressiveness for our robot. We began by installing LED lights for the eyes, carefully embedding them behind the face plate to achieve a natural glow effect without visible hardware. My main contribution was soldering the resistors and wiring the LEDs to the appropriate digital pins, ensuring consistent brightness and avoiding voltage overload.

On the coding side, I worked on the LED control functions — programming patterns to simulate blinking and emotional responses (idle pulse, alert flash, and synchronized eye movement cues). The subtle lighting effects brought surprising personality to the robot’s expression, especially in dim environments. Started with the setup of the nRF Servo Mega Shield setup for receiver transmitter communication.

10/31/2025:Radio Communication
We tackled the nRF Servo Mega Shield setup to establish wireless communication between the transmitter and receiver. I attached the radio to aurdino then started with debugging the radio initialization issues; tracing back the failure to a mismatched CE/CSN pin configuration. After correcting the wiring and recompiling the code, we successfully uploaded the transmitter and receiver sketches. The moment the remote control finally communicated with the main board felt like a breakthrough.


What did you accomplish for today November 6?
fixed the servo with weight issues in thr right shoulder
What features remain to be implemented?
radio connection issue and music board
What will you accomplish for next Thursday November 11?
Fixed the reciver transmitter issue and soldered the music board, connection is estabisled sucessfully




### Progress Photos:
![IMG_0062](https://github.com/user-attachments/assets/f2525f6e-866a-44b1-ae06-0c0e2922bd07)
![IMG_0058](https://github.com/user-attachments/assets/baa65f53-3f83-460b-9027-806c4bbea2d0)
![IMG_0060](https://github.com/user-attachments/assets/49b70c36-675a-4567-b33c-15bbf7b6ebfd)
