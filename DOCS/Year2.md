[← Year 1](Year1.md) | [Main Repository](../README.md) | [Next → Year 3](Year3.md)



# INTERMEDIATE DEVELOPMENT PHASE

Summer Research & PID Control Transition

---

# YEAR 2 - Precision Control & Motion Intelligence

---

## 2.1.1 First PID Prototype

Introduce closed-loop feedback control using PID algorithms to achieve smoother, faster, and more stable line-following behavior.

#### System Configuration

- Microcontroller: Arduino NANO
- Power Source: Li-ion Battery Pack
- Drive System: Chassis + 2 N20 micro geared motors + castor wheel
- Sensors: Smartelex 8 Channel IR Sensor Array
- Motor Interface: TB6612FNG Motor Driver
- Development Platform: Zero board prototyping for rapid hardware experimentation

#### Initial Control Logic

- Sensor array readings were used to calculate positional error relative to the line
- PID control continuously adjusted motor speed based on real-time error values
- Proportional control reduced immediate deviation from the track
- Derivative control minimized oscillations during high-speed corrections
- Integral contribution was initially kept minimal to avoid instability during tuning

#### Observations

- Robot movement became significantly smoother compared to previous IF-ELSE based control systems
- Zigzag motion was drastically reduced due to continuous feedback correction
- Higher operating speeds became achievable while maintaining tracking stability
- Smartelex sensor array provided highly stable and accurate sensor readings
- TB6612FNG motor driver delivered smoother PWM response and more precise motor control
- PID tuning required repeated experimentation to balance responsiveness and stability
- High proportional gain introduced oscillations, while lower gain reduced correction responsiveness

#### Engineering Remark

This stage marked a major transition from reactive to controlled motion behavior. Instead of performing abrupt directional corrections, the robot continuously adjusted its trajectory using real-time feedback from the sensor array. The integration of the TB6612FNG motor driver further improved motor response precision, enabling stable high-speed PID-controlled operation.

#### Result

The implementation of PID-based control significantly improved motion smoothness, tracking accuracy, and high-speed stability. Combined with the precise motor response of the TB6612FNG driver and reliable sensor feedback from the Smartelex array, the robot established a strong foundation for future motion optimization and advanced autonomous navigation experiments.

---

## 2.1.2 First Custom PCB Prototype

Introduce custom PCB-based integration to improve circuit reliability, wiring organization, compactness, and embedded system scalability.

#### System Configuration

- Microcontroller: Arduino NANO
- Power Source: Li-ion Battery Pack
- Drive System: Chassis + 2 N20 micro geared motors + castor wheel
- Sensors: Smartelex 8 Channel IR Sensor Array
- Motor Interface: TB6612FNG Motor Driver
- Development Platform: Custom designed PCB developed using EasyEDA
- Initial circuit validation was performed using zero-board prototyping before PCB fabrication

#### Initial Control Logic

- PID-based line-following logic was retained from the previous iteration
- Sensor array readings continuously calculated positional error relative to the track
- Motor PWM values were dynamically adjusted using PID correction output
- Improved PCB routing reduced electrical noise and unstable signal connections during operation

#### Observations

- Circuit organization became significantly cleaner compared to zero-board prototyping
- Wiring complexity and loose interconnections were drastically reduced
- PCB integration improved overall system compactness and maintainability
- Stable electrical connections improved operational reliability during motion
- The robot achieved more consistent performance due to reduced connection instability
- Bulky Li-ion battery pack increased overall system weight and occupied significant chassis space
- Larger battery dimensions limited compact chassis integration and affected weight distribution

#### Engineering Remark

This stage marked the transition from prototype-level experimentation to structured embedded system design. Learning PCB design through EasyEDA enabled the development of a cleaner, more reliable, and scalable electronics architecture while significantly improving system integration quality.

#### Result

The first custom PCB implementation successfully improved circuit reliability, modularity, and system organization, establishing a strong foundation for future compact hardware optimization and advanced embedded robotics development.

---

## 2.1.3 Compact Power System & Embedded Miniaturization

Optimize the robot’s physical architecture by reducing power system size, improving weight distribution, and enhancing overall compactness for high-speed operation.

### System Configuration

- Microcontroller: Arduino Nano
- Power Source: Custom Li-Po Battery Pack
- Drive System: Chassis + 2 N20 micro geared motors + castor wheel
- Sensors: Smartelex 8 Channel IR Sensor Array
- Motor Interface: TB6612FNG Motor Driver
- Development Platform: Custom PCB designed using EasyEDA
- Battery capacity and discharge requirements were selected based on calculated robot power consumption


### Initial Control Logic

- PID-based line-following control was retained from the previous iteration
- Real-time positional error from the sensor array continuously adjusted motor PWM values
- Motor response was further optimized for lightweight high-speed operation
- Reduced system weight improved acceleration and directional responsiveness

### Observations

- Replacing bulky Li-ion batteries with compact Li-Po cells significantly reduced overall chassis weight
- Improved weight distribution enhanced robot stability during high-speed turns
- Reduced battery size enabled cleaner PCB and component placement within the chassis
- Lower system mass improved acceleration and correction responsiveness during PID operation
- Compact integration improved overall aesthetics and embedded system organization
- Power consumption calculations helped optimize battery selection for balanced runtime and performance

### Engineering Remark

This stage focused on embedded system miniaturization and power optimization. Instead of selecting batteries solely based on availability, power requirements were analyzed to design a lighter and more efficient energy system better suited for high-speed PID-controlled robotics applications.

### Result

The transition to a compact Li-Po-based power system significantly improved robot agility, structural compactness, and motion responsiveness, further refining the robot into a more optimized and competition-ready embedded robotic platform.

---

## 2.1.4 Custom Sensor Experimentation — TCRT & QRE1113

Explore the behavior, precision, and performance characteristics of discrete IR sensing components to achieve deeper understanding of high-speed line detection systems.

### System Configuration

- Microcontroller: Arduino Nano
- Power Source: Custom Li-Po Battery Pack
- Drive System: Chassis + 2 N20 micro geared motors + castor wheel
- Sensors: Experimental TCRT and QRE1113 IR sensors
- Motor Interface: TB6612FNG Motor Driver
- Development Platform: Custom PCB and zero-board prototyping for sensor experimentation
- Control System: PID-based closed-loop motion control

### Initial Control Logic

- Individual sensor outputs were analyzed for positional error calculation and line detection sensitivity
- PID correction logic continuously adjusted motor speed using real-time sensor feedback
- Sensor placement and spacing were experimentally modified to optimize tracking precision
- Hybrid sensor configurations were tested to balance precision stabilization and robust junction detection
- Analog sensor behavior was evaluated for smoother trajectory correction during high-speed navigation

### Observations

- QRE1113 sensors required minimal external circuitry, consisting primarily of current limiting resistors for the IR emitter and pull-up/pull-down resistors for the receiver output
- Despite their compact size, QRE1113 sensors exhibited relatively high current consumption, leading to noticeably faster battery discharge during operation
- The narrow IR emission cone of QRE1113 sensors enabled extremely precise line detection characteristics
- QRE1113 sensors generated smooth transitional analog readings between black and white surfaces, allowing the PID controller to detect and correct even very small positional deviations
- Instead of abrupt binary transitions, the sensors produced gradual analog variation proportional to surface reflectivity, significantly improving fine trajectory correction capability
- Due to their focused sensing region, QRE1113 sensors were highly sensitive to environmental variations such as surface texture, ambient lighting, and sensor height
- Stable operation of QRE1113 sensors required extremely close placement to the track surface, typically around 3 mm above the line
- TCRT sensors operated with comparatively optimized current consumption and demonstrated stable sensing performance over a wider operating range
- The broader IR emission cone of TCRT sensors enabled reliable operation at greater sensor heights
- TCRT sensor modules required more complex onboard circuitry and occupied significantly larger PCB area compared to QRE1113 sensors
- The physical footprint of a single TCRT sensor module was large enough to accommodate approximately two QRE1113 sensor units within the same area
- TCRT sensors provided accurate and stable readings suitable for high-speed line-following applications
- Compared to QRE1113 sensors, TCRT sensors were less sensitive to minute positional variations but performed more reliably for detecting junctions, sharp turns, and complex track structures

### Hybrid Sensor Strategy

A hybrid sensing architecture was implemented by combining QRE1113 and TCRT sensors for different operational purposes within the robot.

- QRE1113 sensors were utilized primarily for PID stabilization due to their high positional sensitivity and smooth analog response characteristics
- Their ability to detect very small changes in line position enabled rapid PID correction and smoother trajectory stabilization during high-speed operation
- TCRT sensors were integrated mainly for structural track interpretation, including junction detection and sharp turn recognition
- This hybrid configuration balanced precision motion stabilization with robust environmental sensing capability

### Engineering Remark

This stage shifted the focus from using ready-made sensing modules to understanding the underlying behavior of discrete IR sensing components. The experimentation process highlighted important tradeoffs between sensing precision, environmental robustness, power efficiency, hardware compactness, and circuit complexity. By implementing a hybrid sensing strategy, the robot achieved both high-speed PID stabilization and reliable complex track interpretation.

### Result

The sensor experimentation phase significantly expanded the understanding of precision line detection system design and demonstrated the effectiveness of hybrid sensing architectures in autonomous robotics. The integration of QRE1113 sensors for fine PID stabilization and TCRT sensors for robust junction detection established a strong foundation for future custom sensor array development and advanced high-speed navigation systems.

---

The intermediate development phase marked a major transformation in the overall engineering maturity of the robotic system. The transition from reactive IF-ELSE logic to PID-based closed-loop control significantly improved motion smoothness, trajectory stability, and high-speed navigation capability.

During this phase, the project expanded beyond basic robotics experimentation into broader embedded system engineering domains including PCB design, power optimization, competition-oriented system validation, and precision sensor research.

The introduction of custom PCB integration, compact Li-Po power systems, and hybrid sensing architectures enabled the robot to evolve into a more reliable, scalable, and competition-ready autonomous platform. In parallel, experimentation with discrete sensing components provided deeper understanding of sensor physics, environmental sensitivity, and precision feedback control.

Participation in Technoxian — World Robotics Championship further validated the practical effectiveness of the developed system under real-world competitive conditions.

By the end of this phase, the robot had progressed from a simple line-following prototype into a high-speed PID-controlled embedded robotic platform capable of stable autonomous navigation and advanced sensing experimentation.

---
