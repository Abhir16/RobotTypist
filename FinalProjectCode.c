char row1[] = {'Q','W','E','R','T','Y','U','I','O','P'};
char row2[] = {'A','S','D','F','G','H','J','K','L'};
char row3[] = {'Z','X','C','V','B','N','M'};
const int KEYDIST = 50;
int resetArm=0;


int rowCheck(char letter, int & column)
{
	for(int i = 0; i < 10; i++)
	{q
		if (row1[i] == letter)
		{
			column=i;
			return 1;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if (row2[i] == letter)
		{
			column=i;
			return 2;
		}
	}
	for(int i = 0; i < 7; i++)
	{
		if (row3[i] == letter)
		{
			column=i;
			return 3;
		}
	}

	return 4; // spacebar


}




void positionReset(bool decision)
{

	nxtDisplayString(2,"moving back");
	motor[motorA] = 20;
	while(SensorValue[S2] !=1){}
	motor[motorA] = 0;
	nxtDisplayString(3,"resetting");
	if (decision)
	{
		nMotorEncoderTarget[motorB] = resetArm;
		motor[motorB] = 5;
		while(nMotorRunState[motorB] != runStateIdle){} // while Motor B is still running (hasn't reached target yet):
		motor[motorB] = 0;
		wait10Msec(300);
	}
}




void hitKey(bool decision, bool spacebar)
{
	if (spacebar)
	{
		motor[motorC] = 100;
		wait1Msec(170);
		motor[motorC] = 0;
		motor[motorC] = -100;
		wait1Msec(180);
		motor[motorC] = 0;
	}
	else
	{
		motor[motorC] = 100;
		wait1Msec(210);
		motor[motorC] = 0;
		motor[motorC] = -100;
		wait1Msec(222);
		motor[motorC] = 0;
	}

	positionReset(decision);

}





void typeRow1(int column)
{
	nMotorEncoder[motorA] = 0;
	int spot = KEYDIST * column;
	motor[motorA] = -20;
	while(nMotorEncoder[motorA] > -spot){}  // while Motor B is still running (hasn't reached target yet):
	motor[motorA] = 0;
	hitKey(0, 0);

}





void typeRow2(int column)
{
	nMotorEncoderTarget[motorA] = 4  * KEYDIST;
	motor[motorA] = -20;
	while(nMotorRunState[motorA] != runStateIdle){}
	motor[motorA] = 0;
	nMotorEncoder[motorA] = 0;
	int motorVal = 48;
	nMotorEncoderTarget[motorB] = motorVal;
	motor[motorB] = -5;
	while(nMotorRunState[motorB] != runStateIdle){}  // while Motor B is still running (hasn't reached target yet):
	motor[motorB] = 0;
	nMotorEncoder[motorB] = 0;

	nMotorEncoderTarget[motorA] = KEYDIST * column;
	motor[motorA] = -20;
	while(nMotorRunState[motorA] != runStateIdle){}
	resetArm= motorVal + 3;
	nMotorEncoder[motorA] = 0;

	hitKey(1, 0);
}





void typeRow3(int column)
{
	nMotorEncoderTarget[motorA] = 5 * KEYDIST;
	motor[motorA] = -20;
	while(nMotorRunState[motorA] != runStateIdle){}
	motor[motorA] = 0;
	nMotorEncoder[motorA] = 0;
	int motorVal = 68;
	nMotorEncoderTarget[motorB] = motorVal;
	motor[motorB] = -5;
	while(nMotorRunState[motorB] != runStateIdle){}  // while Motor B is still running (hasn't reached target yet):
	motor[motorB] = 0;
	nMotorEncoder[motorB] = 0;

	nMotorEncoderTarget[motorA] = KEYDIST * column;
	motor[motorA] = -20;
	while(nMotorRunState[motorA] != runStateIdle){}
	nMotorEncoder[motorA] = 0;
	resetArm = motorVal - 4;

	hitKey(1 , 0);
}


void typeSpacebar(void)
{
	nMotorEncoderTarget[motorA] = 6 * KEYDIST;
	motor[motorA] = -20;
	while(nMotorRunState[motorA] != runStateIdle){}
	motor[motorA] = 0;
	nMotorEncoder[motorA] = 0;
	int motorVal = 82;
	nMotorEncoderTarget[motorB] = motorVal;
	motor[motorB] = -5;
	while(nMotorRunState[motorB] != runStateIdle){}  // while Motor B is still running (hasn't reached target yet):
	motor[motorB] = 0;
	nMotorEncoder[motorB] = 0;

	nMotorEncoderTarget[motorA] = KEYDIST * 4;
	motor[motorA] = -20;
	while(nMotorRunState[motorA] != runStateIdle){}
	nMotorEncoder[motorA] = 0;
	resetArm= motorVal + 5;

	hitKey(1, 1);
}

void type(int row, int column)
{
	if (row == 1)
		typeRow1(column);
	else if (row == 2)
		typeRow2(column);
	else if (row == 3)
		typeRow3(column);
	else if (row == 4)
		typeSpacebar();

}





task main()
{
 //motor[motorA] = -20;
 // wait10Msec(500);


  int column = 0;

	SensorType[S1] = sensorCOLORFULL;
	SensorType[S2] = sensorTouch;

	nxtDisplayString(0,"Press any button to start");
	while(nNxtButtonPressed == -1){}
	while(nNxtButtonPressed != -1){}
	nxtDisplayClearTextLine(0);
	nxtDisplayString(0,"Insert a colour to scan");


	while(nNxtButtonPressed != 2)
	{

		//while(sensorValue[S1] == 6);

		if (SensorValue[S1] == 3)
		{
			char word[] = {'T','R','O','N',' '};

			for(int i=0; i<5; i++)
			{
				int rowhold = rowCheck(word[i], column);
				type(rowhold,column);
			}

		}

		else if (SensorValue[S1] == 2)
		{
			char word[] = {'I','S',' '};

			for(int i=0; i<3; i++)
			{
				type(rowCheck(word[i], column),column);
			}
		}

		else if (SensorValue[S1] == 5)
		{
			char word[] = {'L','O','V','E'};

			for (int i=0; i<4; i++)
			{
				type(rowCheck(word[i], column),column);
				nxtDisplayString(4, "%d", column);
			}

		}

	}

}
	/*
 WPM test for demo day!
	int column = 0;

	SensorType[S1] = sensorCOLORFULL;`
	SensorType[S2] = sensorTouch;

	nxtDisplayString(0,"Press any button to start");
	while(nNxtButtonPressed == -1);
	while(nNxtButtonPressed != -1);
	nxtDisplayClearTextLine(0);

	char word [] = {}

	for (int i=0; i<100; i++)
	{
		type(rowCheck(word[i], column),column);
	}
	*/

