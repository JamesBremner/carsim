# carsim
A windows desktop application coded in C++ to simulate the fuel consumption of a car driving through an urban setting

# Inputs

## Car Configuration

The user can set the car configuration using these options:

The user can select from a list pre-configured cars

The user can create and edit a new configured car by editing the parameters - weight, etc

The user can edit the fuel table directly.

## Fuel Table

Each row of the fuel table specifies a speed in km/hour

The first column specified the speed

The second column specifies the fuel consumption in litres/100km at this constant speed

The following columns specify the fuel consumption in litres/sec at some acceleration/deceleration

## Driving Plan

A driving plan is a set of number pairs.  The first number in each pair is the time in seconds.  The second number is the speed in km/hour. The pairs are sorted in order of increasing time.
The simulation assumes that in the time between the time specified by two pairs the speed is constant, if the two speeds are equal, or constant acceleration/deceleration if the two speeds are different.
User can edit drive plans and save new ones.

## Space Time Points

We model the signals, using pairs of time and distance.

For example:

signal is at a distance of 100 meters. It is green right now but it will turn red in 7 seconds.
This can be input with a spacetime point of ( 100, 7 )

# Outputs

For each row in the driving plan, the time taken and the fuel consumption

For each space time point, the time taken to reach the distance and the speed at the distance.

2D plots: distance-time, speed-time

# Comparing Drive Plans

![image](https://user-images.githubusercontent.com/2046227/184908904-90d55638-311c-4874-a2c9-0196574a024d.png)

![image](https://user-images.githubusercontent.com/2046227/184909058-9342820a-1d80-43fa-a5d5-8916c2b4254d.png)
