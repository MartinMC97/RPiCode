 /* A simple controlling program that turns raspberry pi into a car. 
 *  An Xbox 360 controller and a motor coltrolling module L298N are required.
 *  most of the code is ripped from http://archives.seul.org/linuxgames/Aug-1999/msg00107.html
 *  GPIO controlling is handled by WiringPi.
 *  The comment may not be accurate. Sorry about that.
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <wiringPi.h>
#include <softPwm.h>

#define JOY_DEV "/dev/input/js0"

int main()
{
	wiringPiSetup () ;
	pinMode (0, OUTPUT) ;
	pinMode (1, OUTPUT) ;
	pinMode (2, OUTPUT) ;
	pinMode (3, OUTPUT) ;
	softPwmCreate (4, 50, 100) ;
	softPwmCreate (5, 50, 100) ;
	
	int joy_fd, *axis=NULL, num_of_axis=0, num_of_buttons=0, x;
	char *button=NULL, name_of_joystick[80];
	struct js_event js;

	if( ( joy_fd = open( JOY_DEV , O_RDONLY)) == -1 )
	{
		printf( "Couldn't open joystick\n" );
		return -1;
	}

	ioctl( joy_fd, JSIOCGAXES, &num_of_axis );
	ioctl( joy_fd, JSIOCGBUTTONS, &num_of_buttons );
	ioctl( joy_fd, JSIOCGNAME(80), &name_of_joystick );

	axis = (int *) calloc( num_of_axis, sizeof( int ) );
	button = (char *) calloc( num_of_buttons, sizeof( char ) );

	printf("Joystick detected: %s\n\t%d axis\n\t%d buttons\n\n"
		, name_of_joystick
		, num_of_axis
		, num_of_buttons );

	fcntl( joy_fd, F_SETFL, O_NONBLOCK );	/* use non-blocking mode */

	while( 1 ) 	/* infinite loop */
	{

			/* read the joystick state */
		read(joy_fd, &js, sizeof(struct js_event));
		
			/* see what to do with the event */
		switch (js.type & ~JS_EVENT_INIT)
		{
			case JS_EVENT_AXIS:
				axis   [ js.number ] = js.value;
				break;
			case JS_EVENT_BUTTON:
				button [ js.number ] = js.value;
				break;
		}
		
		if(button[5] == 1)				//holding RT for speeding up
		{
			softPwmWrite (4, 100) ;
			softPwmWrite (5, 100) ;
		}
		
		if(button[5] == 0)				//release RT for normal speed
		{
			softPwmWrite (4, 50) ;
			softPwmWrite (5, 50) ;
		}
		
		if(axis[0]<0) 					// turn left.?
		{	
			digitalWrite (0, HIGH) ;
			digitalWrite (1, LOW) ;
			digitalWrite (2, LOW) ;
			digitalWrite (3, LOW) ;
		}
		if(axis[0]>0) 					// turn right.?
		{	
			digitalWrite (0, LOW) ;
			digitalWrite (1, LOW) ;
			digitalWrite (2, HIGH) ;
			digitalWrite (3, LOW) ;
		}
		if(axis[1]<0) 					// go back.?
		{	
			digitalWrite (0, HIGH) ;
			digitalWrite (1, LOW) ;
			digitalWrite (2, HIGH) ;
			digitalWrite (3, LOW) ;
		}
		if(axis[1]>0) 					// forward.?
		{	
			digitalWrite (0, LOW) ;
			digitalWrite (1, HIGH) ;
			digitalWrite (2, LOW) ;
			digitalWrite (3, HIGH) ;
		}
		if(axis[0] == 0 && axis[1] == 0)
		{
			digitalWrite (0, LOW) ;
            digitalWrite (1, LOW) ;
            digitalWrite (2, LOW) ;
            digitalWrite (3, LOW) ;
		}
		/*if(button[0] == 1)       digitalWrite (0, HIGH) ;
		else if (button[0] == 0) digitalWrite (0,  LOW) ;*/
		/*	
		printf( "X: %6d  Y: %6d  ", axis[0], axis[1] );
		
		if( num_of_axis > 2 )
			printf("Z: %6d  ", axis[2] );
			
		if( num_of_axis > 3 )
			printf("R: %6d  ", axis[3] );
			
		for( x=0 ; x<num_of_buttons ; ++x )
			printf("B%d: %d  ", x, button[x] );

		printf("  \r");
		fflush(stdout);*/
	}

	close( joy_fd );	/* too bad we never get here */
	return 0;
}
