## Arduino Project: Motion-Activated Staircase Lighting Enhancement

  In an effort to enhance the lighting under the stairs at my residence, I embarked on a small Arduino project that seamlessly combines motion detection and sound sensing for an efficient and interactive lighting solution.

  Components Used:
  
    1. Arduino UNO: Serving as the brain of the project, the Arduino UNO is the central control unit that manages the entire system.
    
    2. PIR Sensor: This passive infrared sensor is employed for detecting motion. It ensures that the lights activate only when someone is in the vicinity.

    3. Sound Sensor KY-037: The sound sensor, KY-037, adds an interactive element to the project. By recognizing a single clap, it allows users to control the brightness of the LED strip.

    4. LED Strip 220V: The main source of illumination, the LED strip provides ambient lighting under the stairs.

    5. Module Dimmer AC: Utilizing the RBDDimmer library, this module facilitates the control of dimmer settings.
    
    6. Jumper Wires: Essential for connecting and establishing the required electrical connections.

# Project Operation:
  Upon a single clap in front of the sound sensor, the lighting system activates. The LED strip gradually brightens, providing ample illumination for activities under the stairs. The motion sensor ensures that the lights remain on as long as there is detected movement. Subsequently, the lights automatically turn off after a predefined period or upon another clap, signifying the conclusion of the task.

  Implementation:
The project leverages the RBDDimmer library, allowing for the control of the dimmer. The Arduino UNO orchestrates the operation, seamlessly integrating the input from both the PIR sensor and the sound sensor.

Check the Image folder for a visual representation of the setup, and find the project's code in the Code folder.

For a visual demonstration of the motion-activated staircase lighting enhancement, check out the demo video here. The video showcases the functionality and real-time operation of the Arduino project, providing insight into how the system responds to motion and sound cues.

This motion-activated lighting solution not only enhances the practicality of the staircase lighting but also adds a touch of interactivity, showcasing the versatility and creativity that Arduino projects can bring to everyday scenarios.
