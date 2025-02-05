/**
 * @file Motor.h - Library for controlling a DC motor using an H-bridge driver.
 *
 * @author Alexandre Figueiredo and Daniela Gonçalves
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "Expander.h"
#include <Math.h>
#include <FunctionalInterrupt.h>

/**
 * @brief Struct representing an interrupt configuration.
 */
struct Interrupt
{
    byte PIN_DO;    // Digital input pin for the interrupt
    byte INT_COUNT; // Interrupt counter value
};

/**
 * @brief Struct representing a motor controller configuration.
 */
struct MotorController
{
    byte PIN_EN;         // Enable pin for the motor controller
    byte PIN_IN1;        // Input 1 pin for the motor controller
    byte PIN_IN2;        // Input 2 pin for the motor controller
    Interrupt interrupt; // Interrupt configuration for the motor controller
    float wheelRadius;   // Wheel radius in centimeters
};

/**
 * @brief Class representing a DC motor.
 */
class Motor
{
public:
    // Public constants

    // Public variables

    // Public methods

    /**
     * @brief Constructor for the Motor class.
     *
     * @param expander - An optional Expander object for expanding the available GPIO pins.
     * @param controller - An optional MotorController object for configuring the motor controller.
     */
    Motor(Expander expander, MotorController controller);

    /**
     * @brief Initializes the motor and motor controller pins.
     * This method should be called once at the beginning of the program.
     */
    void begin();

    /**
     * @brief Sets the direction of the motor.
     *
     * @param clockwise - A boolean indicating the direction of the motor.
     *                    true for clockwise, false for counterclockwise.
     */
    void setDirection(bool clockwise);

    /**
     * @brief Starts the motor in the forward direction.
     *
     * @param speed - An integer indicating the speed of the motor.
     *                Must be between 0 and 100.
     * @param cm - An optional float indicating the distance to travel in centimeters.
     *             Defaults to 0.
     */
    void front(float speed, float length = 0);

    /**
     * @brief Starts the motor in the backward direction.
     *
     * @param speed - An integer indicating the speed of the motor.
     *                Must be between 0 and 100.
     * @param cm - An optional float indicating the distance to travel in centimeters.
     *             Defaults to 0.
     */
    void back(float speed, float cm = 0);

    /**
     * @brief Stops the motor.
     *
     * @param now - A boolean indicating whether to stop the motor immediately (true) or coast to a stop (false).
     *              Defaults to false.
     */
    void stop();

    /**
     * @brief Slows the motor down.
     */
    void slow();

    /**
     * @brief Blocks the motor.
     */
    void block();

    /**
     * @brief Gets the current interrupt count.
     *
     * @return An integer representing the interrupt count.
     */
    int getCounter();

    /**
     * @brief Resets the interrupt count to zero.
     */
    void resetCounter();

    /**
     * @brief Sets the speed of the motor.
     *
     * @param speed - An integer indicating the speed of the motor.
     *                Must be between 0 and 100.
     */
    void setSpeed(float speed);

    /**
     * @brief Gets the speed of the motor.
     *
     * @return A float representing the speed of the motor.
     */
    float getSpeed();

    /**
     * @brief Sets the PWM of the motor.
     *
     * @param pwm - An integer indicating the PWM of the motor.
     *              Must be between 0 and 100.
     */
    void setPWM(int pwm);

    /**
     * @brief Gets the PWM of the motor.
     *
     * @return An integer representing the PWM of the motor.
     */
    int getPWM();

    /**
     * @brief Get the target interrupt.
     */
    int getTargetInterrupt();

    /**
     * @brief Check if the motor has a interrupt.
     */
    bool hasInterrupt();

    /**
     * @brief Get the radius of the wheel.
     */
    float getRadius();

    /**
     * @brief Get the perimeter of the wheel.
     */
    float getPerimeter();

private:
    // Private constants
    static constexpr const float _FULL_SPEED = 100.0; // The maximum speed value
    static constexpr const float _STOP_SPEED = 0.0;   // The minimum speed value
    static const int _INTERRUPT_FIX = 2;              // Multiplicative constant for interrupt attach on change

    // Private variables
    Expander _expander;          // The Expander object for expanding the available GPIO pins
    Interrupt _interrupt;        // The Interrupt object for configuring the interrupt
    MotorController _controller; // The MotorController object for configuring the motor controller

    volatile int _counter; // The interrupt counter for the motor
    int _turnInterruptCount;
    int _interruptTarget; // Interrupt target for the motor
    int _hasInterrupt;    // Flag for interrupt mode

    float _perimeter; // Wheel perimeter (cm)
    float _radius;
    float _speed;
    int _pwm;

    // Private methods
    /**
     * @brief Interrupt service routine for counting interrupts.
     * This method should not be called directly.
     */
    IRAM_ATTR void _incrementCounter();

    /**
     * @brief Convert the lenght (cm) to number of interrupts and updates the interrupt target.
     */
    void _updateInterruptTarget(float length);
};

#endif
