#include "main.h"

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants()
{
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants()
{
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants()
{
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults()
{
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition()
{
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

///
// Drive Example
///
void drive_example()
{
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
}

///
// Turn Example
///
void turn_example()
{
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}

///
// Combining Turn + Drive
///
void drive_and_turn()
{
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed()
{
  // wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}

///
// Swing Example
///
void swing_example()
{
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive

  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}

///
// Auto that tests everything
///
void combining_movements()
{
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}

///
// Interference example
///
void tug(int attempts)
{
  for (int i = 0; i < attempts - 1; i++)
  {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered)
    {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else
    {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees.
// If interfered, robot will drive forward and then attempt to drive backwards.
void interfered_example()
{
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  if (chassis.interfered)
  {
    tug(3);
    return;
  }

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
}

void soccerChallenge()
{
  pros::Motor claw(2);

  claw.move_velocity(-127);
  pros::delay(1000);
  claw.move_velocity(0);

  // move past first cone
  chassis.set_drive_pid(40, DRIVE_SPEED, true);
  chassis.wait_drive();

  // turn
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  // move past second cone
  chassis.set_drive_pid(53, DRIVE_SPEED, true);
  chassis.wait_drive();

  // turn
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // move past final cone and to end
  chassis.set_drive_pid(55, DRIVE_SPEED, true);
  chassis.wait_drive();

  // first adjustment
  chassis.set_turn_pid(-60, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(10, DRIVE_SPEED, true);
  chassis.wait_drive();

  // aligns furthur
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(10, DRIVE_SPEED, true);
  chassis.wait_drive();

  // straight around far cone
  chassis.set_turn_pid(-140, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(25, DRIVE_SPEED, true);
  chassis.wait_drive();

  // align for goal
  chassis.set_turn_pid(-220, TURN_SPEED);
  chassis.wait_drive();

  // drive to finish
  chassis.set_drive_pid(110, 127, true);
  chassis.wait_drive();
}

void semiSpeedSoccer()
{
  pros::Motor claw(2);

  claw.move_velocity(-127);
  pros::delay(1000);
  claw.move_velocity(0);

  // move past first cone
  chassis.set_drive_pid(40, 127, true);
  chassis.wait_drive();

  // turn
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  // move past second cone
  chassis.set_drive_pid(53, 127, true);
  chassis.wait_drive();

  // turn
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // move past final cone and to end
  chassis.set_drive_pid(55, 127, true);
  chassis.wait_drive();

  // first adjustment
  chassis.set_turn_pid(-60, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(10, 127, true);
  chassis.wait_drive();

  // aligns furthur
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(10, 127, true);
  chassis.wait_drive();

  // straight around far cone
  chassis.set_turn_pid(-140, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(25, 127, true);
  chassis.wait_drive();

  // align for goal
  chassis.set_turn_pid(-220, TURN_SPEED);
  chassis.wait_drive();

  // drive to finish
  chassis.set_drive_pid(110, 127, true);
  chassis.wait_drive();
}

void speedSoccerChallenge()
{
  pros::Motor claw(2);

  claw.move_velocity(-127);
  pros::delay(1000);
  claw.move_velocity(0);
  /*
  //move past first cone
    chassis.set_drive_pid(40, 127, true);
    chassis.wait_until(30);

    claw.move_velocity(-40);

  //turn
    chassis.set_turn_pid(-90, TURN_SPEED);
    chassis.wait_drive();

    claw.move_velocity(0);
  */

  // move past second cone
  chassis.set_drive_pid(75, 127, true);
  chassis.wait_until(70);

  claw.move_velocity(-20);

  // turn
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_until(89);

  claw.move_velocity(0);

  // move past final cone and to end
  chassis.set_drive_pid(55, 127, true);
  chassis.wait_until(46);

  claw.move_velocity(-8);

  // first adjustment
  chassis.set_turn_pid(30, TURN_SPEED);
  chassis.wait_until(31);

  claw.move_velocity(0);

  chassis.set_drive_pid(10, 127, true);
  chassis.wait_until(5);

  claw.move_velocity(-3);

  // aligns furthur
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_until(1);

  claw.move_velocity(0);

  chassis.set_drive_pid(10, 127, true);
  chassis.wait_until(5);

  claw.move_velocity(-3);

  // straight around far cone
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_until(-44);

  claw.move_velocity(0);

  chassis.set_drive_pid(25, 127, true);
  chassis.wait_until(20);

  claw.move_velocity(-3);

  // align for goal
  chassis.set_turn_pid(-130, TURN_SPEED);
  chassis.wait_until(-129);

  claw.move_velocity(0);

  // drive to finish
  chassis.set_drive_pid(110, 127, true);
  chassis.wait_drive();
}

/* Ideas for dance songs
- Escape (The Pina Colada Song)  <---
- Paradise City
- I'm Still Standing
- Johnny B. Goode
- Welcome To the Jungle
- Jump
- Live and Let Die
- Mr. Blue Sky
- We Didn't Start the Fire
- Walk This Way
- Life is a Highway
- Africa
- Seven Nation Army
- Hooked on a Feeling
- Shipping Up to Boston
- Sweet Caroline
- We Will Rock You
- Don't Stop me Now
*/
void singTask()
{
  pros::Motor claw(3);

  claw.move_velocity(60);
  pros::delay(100);

  claw.move_velocity(-90);
  pros::delay(100);

  claw.move_velocity(60);
  pros::delay(100);

  claw.move_velocity(-90);
  pros::delay(100);

  claw.move_velocity(60);
  pros::delay(100);

  claw.move_velocity(-90);
  pros::delay(100);

  claw.move_velocity(40);
  pros::delay(300);

  claw.move_velocity(-90);
  pros::delay(100);
}

void danceChallenge()
{

  // claw and claw mover
  pros::Motor claw(3);
  pros::Motor axel(2);

  pros::delay(2700);

  chassis.set_drive_pid(5, 110);
  chassis.wait_until(4);

  pros::delay(300);

  chassis.set_turn_pid(15, 90);
  chassis.wait_until(14);

  pros::delay(400);

  chassis.set_turn_pid(-18, 110);
  chassis.wait_until(-17);

  pros::delay(250);

  chassis.set_turn_pid(0, 110);
  chassis.wait_drive();

  pros::delay(300);

  axel.move_velocity(90);
  claw.move_velocity(60);

  chassis.set_drive_pid(-14, 60);
  chassis.wait_until(-13);

  axel.move_velocity(0);
  claw.move_velocity(0);

  chassis.set_swing_pid(ez::RIGHT_SWING, 90, SWING_SPEED);
  chassis.wait_until(89);

  pros::delay(100);

  chassis.set_drive_pid(8, 110);
  chassis.wait_until(6);

  // pros::delay(100);

  chassis.set_swing_pid(ez::LEFT_SWING, 0, SWING_SPEED);
  chassis.wait_until(1);

  pros::delay(100);

  chassis.set_drive_pid(8, 110);
  chassis.wait_until(6);

  chassis.set_turn_pid(-0, 110);
  chassis.wait_until(-1);

  pros::delay(200);

  axel.move_velocity(-50);
  claw.move_velocity(-60);

  chassis.set_drive_pid(14, 60);
  chassis.wait_until(13);

  axel.move_velocity(0);
  claw.move_velocity(0);

  chassis.set_drive_pid(5, 110);
  chassis.wait_until(4);

  pros::delay(300);

  chassis.set_turn_pid(15, 90);
  chassis.wait_until(14);

  pros::delay(400);

  chassis.set_turn_pid(-18, 110);
  chassis.wait_until(-17);

  pros::delay(250);

  chassis.set_turn_pid(0, 110);
  chassis.wait_drive();

  pros::delay(300);

  chassis.set_drive_pid(-14, 60);
  chassis.wait_until(-13);

  chassis.set_swing_pid(ez::RIGHT_SWING, 90, SWING_SPEED);
  chassis.wait_until(89);

  pros::delay(100);

  chassis.set_drive_pid(8, 110);
  chassis.wait_until(6);

  // pros::delay(100);

  chassis.set_swing_pid(ez::LEFT_SWING, 0, SWING_SPEED);
  chassis.wait_until(1);

  pros::delay(100);

  chassis.set_drive_pid(8, 110);
  chassis.wait_until(6);

  chassis.set_turn_pid(-0, 110);
  chassis.wait_until(-1);

  // SING PLEASE
  pros::Task sing(singTask);

  pros::delay(200);

  axel.move_velocity(50);

  chassis.set_drive_pid(14, 60);
  chassis.wait_until(13);

  axel.move_velocity(0);

  chassis.set_drive_pid(5, 110);
  chassis.wait_until(4);

  pros::delay(300);

  chassis.set_turn_pid(15, 90);
  chassis.wait_until(14);

  pros::delay(400);

  chassis.set_turn_pid(-18, 110);
  chassis.wait_until(-17);

  pros::delay(250);

  chassis.set_turn_pid(0, 110);
  chassis.wait_drive();

  pros::delay(300);

  chassis.set_drive_pid(-14, 60);
  chassis.wait_until(-13);

  chassis.set_drive_pid(-5, 110);
  chassis.wait_until(-4);

  pros::delay(300);

  chassis.set_turn_pid(-15, 90);
  chassis.wait_until(-14);

  pros::delay(400);

  chassis.set_turn_pid(18, 110);
  chassis.wait_until(17);

  pros::delay(250);

  chassis.set_turn_pid(0, 110);
  chassis.wait_drive();

  pros::delay(300);

  chassis.set_drive_pid(14, 60);
  chassis.wait_until(-13);

  chassis.set_drive_pid(5, 110);
  chassis.wait_until(4);

  pros::delay(300);

  chassis.set_turn_pid(15, 90);
  chassis.wait_until(14);

  pros::delay(400);

  chassis.set_turn_pid(-18, 110);
  chassis.wait_until(-17);

  pros::delay(250);

  chassis.set_turn_pid(0, 110);
  chassis.wait_drive();

  pros::delay(300);

  chassis.set_drive_pid(-14, 60);
  chassis.wait_until(-13);

  chassis.set_drive_pid(-5, 110);
  chassis.wait_until(-4);

  pros::delay(300);

  chassis.set_turn_pid(-15, 90);
  chassis.wait_until(-14);

  pros::delay(400);

  chassis.set_turn_pid(18, 110);
  chassis.wait_until(17);

  pros::delay(250);

  chassis.set_turn_pid(0, 110);
  chassis.wait_drive();

  pros::delay(300);

  chassis.set_drive_pid(14, 60);
  chassis.wait_until(-13);
}

void finalChallenge()
{

  unsigned long autonTimer;

  // ball tower
  pros::Motor intake(4);
  pros::Motor dropper(5);

  // claw
  pros::Motor claw(2);
  pros::Motor axel(3);
  /*

  while (1 == 1)
  {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
    {
      break;
    }

    pros::delay(20);
  }

  autonTimer = pros::millis();
  */

  while (true)
  {
    chassis.set_drive_pid(6, DRIVE_SPEED);
    chassis.wait_until(5);

    chassis.set_turn_pid(-130, TURN_SPEED);
    chassis.wait_drive();

    // intake.move_velocity(90);

    chassis.set_drive_pid(8, DRIVE_SPEED);
    chassis.wait_until(7);

    chassis.set_turn_pid(-90, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(24, DRIVE_SPEED);
    chassis.wait_until(23);

    claw.move_velocity(-30);

    pros::delay(150);

    claw.move_velocity(0);

    // pros::delay(500);

    // intake.move_velocity(0);

    // chassis.set_drive_pid(-4, DRIVE_SPEED);
    // chassis.wait_until(-3);

    chassis.set_turn_pid(50, TURN_SPEED);
    chassis.wait_drive();

    /*
            axel.move_velocity(-90);
        claw.move_velocity(-30);
        pros::delay(400);
        axel.move_velocity(0);
        claw.move_velocity(0);
        */

    chassis.set_drive_pid(7, DRIVE_SPEED);
    chassis.wait_until(6);

    chassis.set_turn_pid(0, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-9, DRIVE_SPEED);
    chassis.wait_until(-7);

    // open and close dropper
    dropper.move_velocity(-90);
    pros::delay(150);
    dropper.move_velocity(0);
    pros::delay(1000);
    dropper.move_velocity(90);
    pros::delay(200);
    dropper.move_velocity(0);

    int driveup1 = 30;
    int driveup2 = 20;

    chassis.set_drive_pid(driveup1, DRIVE_SPEED);
    chassis.wait_until(driveup1 - 1);

    chassis.set_turn_pid(-225, TURN_SPEED);
    chassis.wait_drive();

    axel.move_velocity(127);

    pros::delay(250);

    axel.move_velocity(0);

    chassis.set_drive_pid(-(driveup2), DRIVE_SPEED);
    chassis.wait_until(-(driveup2) + 1);

    axel.move_velocity(-90);

    pros::delay(400);

    axel.move_velocity(-5);

    chassis.set_drive_pid(driveup2, DRIVE_SPEED);
    chassis.wait_until(driveup2 - 1);

    chassis.set_turn_pid(0, TURN_SPEED);
    chassis.wait_drive();

    claw.move_velocity(105);

    dropper.move_velocity(30);

    chassis.set_drive_pid(-(driveup1)-3, 80);
    chassis.wait_until(-(driveup1)-2);

    dropper.move_velocity(0);

    claw.move_velocity(0);

    axel.move_velocity(100);

    pros::delay(200);

    axel.move_velocity(0);

    while (true)
    {
      pros::delay(100);
    }
  }

  while (true)
  {
    pros::delay(100);
  }
}

void finalChallengeAgain()
{

  // ball tower
  pros::Motor intake(4);
  pros::Motor dropper(5);

  // claw
  pros::Motor claw(2);
  pros::Motor axel(3);

  // open and close dropper
  dropper.move_velocity(-90);
  pros::delay(140);
  dropper.move_velocity(0);
  pros::delay(1000);
  dropper.move_velocity(90);
  pros::delay(200);
  dropper.move_velocity(0);

  chassis.set_drive_pid(13, DRIVE_SPEED);
  chassis.wait_until(12);

  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(28, TURN_SPEED);
  chassis.wait_until(27);

  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();

  intake.move_velocity(-90);

  chassis.set_drive_pid(18, TURN_SPEED);
  chassis.wait_until(17);

  pros::delay(300);

    intake.move_velocity(0);

  int driveup1 = 30;
    int driveup2 = 20;

    chassis.set_drive_pid(-driveup1, DRIVE_SPEED);
    chassis.wait_until(-driveup1 + 1);

    chassis.set_turn_pid(-225, TURN_SPEED);
    chassis.wait_drive();

    axel.move_velocity(127);

    pros::delay(250);

    axel.move_velocity(0);

    chassis.set_drive_pid(-(driveup2), DRIVE_SPEED);
    chassis.wait_until(-(driveup2) + 1);

    axel.move_velocity(-90);

    pros::delay(400);

    axel.move_velocity(-5);

    chassis.set_drive_pid(driveup2, DRIVE_SPEED);
    chassis.wait_until(driveup2 - 1);

    chassis.set_turn_pid(0, TURN_SPEED);
    chassis.wait_drive();

    claw.move_velocity(105);

    dropper.move_velocity(30);

    chassis.set_drive_pid(-(driveup1)-5, 80);
    chassis.wait_until(-(driveup1)-4);

    dropper.move_velocity(0);

    claw.move_velocity(0);

    axel.move_velocity(100);

    pros::delay(200);

    axel.move_velocity(0);

//end of second football
  chassis.set_drive_pid(4, DRIVE_SPEED);
  chassis.wait_until(3);

    chassis.set_turn_pid(64, TURN_SPEED);
  chassis.wait_drive();

claw.move_velocity(-10);
axel.move_velocity(10);

  chassis.set_drive_pid(102, DRIVE_SPEED);
  chassis.wait_until(101);

  claw.move_velocity(0);
  axel.move_velocity(0);

    axel.move_velocity(-90);

    pros::delay(400);

    axel.move_velocity(-5);

        chassis.set_drive_pid(driveup2, DRIVE_SPEED);
    chassis.wait_until(driveup2 - 1);

    chassis.set_turn_pid(0, TURN_SPEED);
    chassis.wait_drive();

    claw.move_velocity(105);

    dropper.move_velocity(30);

    chassis.set_drive_pid(-(driveup1)-5, 80);
    chassis.wait_until(-(driveup1)-4);

    dropper.move_velocity(0);

    claw.move_velocity(0);

    axel.move_velocity(100);

    pros::delay(200);

    axel.move_velocity(0);
}
