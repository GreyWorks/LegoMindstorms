/* sample.cpp for TOPPERS/ATK(OSEK) */ 

// ECRobot++ API
#include "LightSensor.h"
#include "SonarSensor.h"
#include "SoundSensor.h"
#include "TouchSensor.h"
#include "IrSeeker.h"
#include "Clock.h"
#include "Lcd.h"
#include "Motor.h"
using namespace ecrobot;

extern "C"
{
	#include "kernel.h"
	#include "kernel_id.h"
	#include "ecrobot_interface.h"
	
	//wichtig, damit Tasks gestartet werden können, da sie nicht automatisch gestartet werden
    DeclareCounter(SysTimerCnt);
    DeclareTask(TaskDisplay);
	
	Clock clock;
	Lcd lcd;

	LightSensor           light(PORT_3, true);
	SonarSensor			  sonar(PORT_1);


	/* nxtOSEK hook to be invoked from an ISR in category 2 */
	void user_1ms_isr_type2(void)
	{
		StatusType ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
	    if(ercd != E_OK)
	    {
		    lcd.clear();
			lcd.putf("sn",   "Shutdown OS!");
			lcd.disp();
			clock.wait(2000);
		    ShutdownOS(ercd);
	    }
		SleeperMonitor(); // needed for I2C device and Clock classes
	}

	
	
	TASK(TaskDisplay)
	{

		S16 bright;
		S16 dist;

		while(1)
		{
			bright = light.getBrightness();
			dist = sonar.getDistance();
			lcd.clear();
			lcd.putf("sdn", "Bright:", bright);
			lcd.putf("sdn", "Dist:", dist);
			lcd.disp();

			clock.wait(100);
		}
		TerminateTask();
	}
}
