#include "define.h"
#include "BodyCalib.h"
#include "BodyDataLoader.h"
#include "DataRecord.h"
#include "MatlabLoader.h"

#define SAMPLECOUNT 5

#define MATLAB

#ifndef MATLAB
#define BIN
#endif

int main(){

	////////////////////////////////////////////////mocap/////////////////////////////////////////////////////////////
	BodyCalib Calib;
	int iCount = 0, jCount = 0;
	int tDataCount = 0;

#ifdef BIN
	DataRecord data;
	data.OpenDataFile("record.bin", 'r');
	data.ReadAllData();
	tDataCount = data.GetDataCount();
#else
	MatlabLoader matlab;
	matlab.ReadFile("C:\\Users\\Vision Demo\\Desktop\\Kinect3DCalib-master\\Kinect3DCalib-master\\Knect3dCalib\\Kinect3DCalib\\MatlabDataFile.mat", "data");
	tDataCount = matlab.GetDataCount();
#endif

	for(int i = 0; i < tDataCount; i++){
		cv::Point3f robot, mocap;
#ifdef BIN
		data.GetBodyData(&robot, &mocap);
#else
		matlab.GetBodyData(&robot, &mocap);
#endif

		Calib.DataStore(mocap, robot);
		printf("[%.2f %.2f %.2f] - [%.2f %.2f %.2f]\n", robot.x, robot.y, robot.z, mocap.x, mocap.y, mocap.z);
		jCount++;
	}
	printf("Inserted Data Count : %d\n", jCount);
#ifdef BIN
	data.CloseDataFile();
#else
#endif
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	int LoopCount = Calib.CalcLoopNUM(0.9999, 0.8, SAMPLECOUNT);
	printf("Loop Count : %d\n", LoopCount);
	Calib.InitParam(LoopCount, 5, SAMPLECOUNT);
	Calib.CalcMatrix();

	return 0;
}