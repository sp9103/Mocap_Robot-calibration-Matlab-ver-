# Mocap_Robot-calibration-Matlab-ver-
=============

Mocap & robot calibration source. (matlab version)

using 3d rigid body marker.

*opencv library (recommend 2.4.10)
*matlab external lib

-3D calibration

방법 : 
 - X1 : 모션캡쳐의 좌표 ( 4*1 Vector) (m 단위)
 - X2 : 로봇 마커의 좌표 ( [x,y,z,1]^T ) (mm 단위)
 - M : transformation matrix ( 4*4 Matrix )
    1. M * X1 = X2
       X1 = inv(M) * X2     (X1 - 4*4Mat )

    2. M * X1 = X2
       M = inv(tran(X1)*X1)*tran(X1)*X2
		- least square ( overfitting 문제 ) 

parameter :
 - N : RANSAC 수행횟수
 - Threshold : Inlier & outlier 구분. (유클리디안 디스턴스)
 - m : 한 루프에 least square를 수행할 샘플 갯수 
 
 define :
 - SAMPLECOUNT : Least square로 한번 계산에 사용할 샘플의 수.
 - MATLAB : 매틀랩에서 바로 데이터 파일을 읽어와서 사용할 경우 정의
 
