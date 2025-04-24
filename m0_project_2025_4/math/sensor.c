#include "sensor.h"
#include "filter.h"
#include "icm20608.h"
#include "wp_math.h"
/***************************************************
������: float kalman_filter(float angle,float gyro)
˵��:	�Ǿ��󿨶����˲�
���:	float angle-�۲�ŷ����
			float gyro-���ٶ�
����:	��
��ע:	��
����:	��������

****************************************************/
lpf_param accel_lpf_param,gyro_lpf_param;
lpf_buf gyro_filter_buf[3],accel_filter_buf[3];
sensor smartcar_imu;

/***************************************************
������: vector3f_sub(vector3f a,vector3f b,vector3f *c)
˵��:	��������
���:	vector3f a-������
			vector3f b-����
			vector3f *c-��
����:	��
��ע:	��
����:	��������
****************************************************/
void vector3f_sub(vector3f a,vector3f b,vector3f *c)
{
	c->x=a.x-b.x;
  c->y=a.y-b.y;
  c->z=a.z-b.z;
}


float kalman_filter(float angle,float gyro)
{
	static uint8_t init;
	static float x=0; 
	static float P=0.000001; 
	static float Q=0.000001; 
	static float R=0.35;//0.35 
	static float k=0; //*************
	if(init==0)
	{
		x=angle;
		init=1;
	}
	x=x+gyro*0.005f; 
	P=P+Q; 
	k=P/(P+R); 
	x=x+k*(angle-x);
	P=(1-k)*P;
	return x; 
} 



/***************************************************
������: void imu_data_sampling(void)
˵��:	IMU���ݲ���/У׼/�˲�
���:	��
����:	��
��ע:	��
����:	��������
****************************************************/
void imu_data_sampling(void)
{
	if(smartcar_imu.lpf_init==0)
	{
		set_cutoff_frequency(200, 50,&gyro_lpf_param); //��̬���ٶȷ����˲����� 
		set_cutoff_frequency(200, 30,&accel_lpf_param);//��̬����Ӽ������˲�ֵ
	  smartcar_imu.lpf_init=1;
	}
	smartcar_imu.last_temperature_raw=smartcar_imu.temperature_raw;
	//������/���������ݲɼ�
	ICM206xx_Read_Data(&smartcar_imu._gyro_dps_raw,&smartcar_imu._accel_g_raw,&smartcar_imu.temperature_raw);
	//���������ݵ�ͨ�˲�
	smartcar_imu.gyro_dps_raw.x=LPButterworth(smartcar_imu._gyro_dps_raw.x,&gyro_filter_buf[0],&gyro_lpf_param);
  smartcar_imu.gyro_dps_raw.y=LPButterworth(smartcar_imu._gyro_dps_raw.y,&gyro_filter_buf[1],&gyro_lpf_param);
  smartcar_imu.gyro_dps_raw.z=LPButterworth(smartcar_imu._gyro_dps_raw.z,&gyro_filter_buf[2],&gyro_lpf_param);		
	//���ٶ����ݵ�ͨ�˲�
	smartcar_imu.accel_g_raw.x=LPButterworth(smartcar_imu._accel_g_raw.x,&accel_filter_buf[0],&accel_lpf_param);
	smartcar_imu.accel_g_raw.y=LPButterworth(smartcar_imu._accel_g_raw.y,&accel_filter_buf[1],&accel_lpf_param);
	smartcar_imu.accel_g_raw.z=LPButterworth(smartcar_imu._accel_g_raw.z,&accel_filter_buf[2],&accel_lpf_param);	
	//�¶ȴ���������һ�׵�ͨ�˲�
	smartcar_imu.temperature_filter=0.75f*smartcar_imu.temperature_raw+0.25f*smartcar_imu.temperature_filter;
  //�õ�У׼��Ľ��ٶȡ����ٶȡ�����������
	vector3f_sub(smartcar_imu.gyro_dps_raw,smartcar_imu.gyro_offset,&smartcar_imu.gyro_dps);
  
	smartcar_imu.accel_g.x=smartcar_imu.accel_scale.x*smartcar_imu.accel_g_raw.x-smartcar_imu.accel_offset.x;
  smartcar_imu.accel_g.y=smartcar_imu.accel_scale.y*smartcar_imu.accel_g_raw.y-smartcar_imu.accel_offset.y;
  smartcar_imu.accel_g.z=smartcar_imu.accel_scale.z*smartcar_imu.accel_g_raw.z-smartcar_imu.accel_offset.z;  	
	//���ٶȼ�/������У׼���
	imu_calibration(&smartcar_imu.gyro_dps_raw,&smartcar_imu.accel_g_raw);
	
	//ͨ��������ٶȼ�,����ˮƽ�۲�Ƕ�
	float ax,ay,az;
	ax=smartcar_imu.accel_g.x;
	ay=smartcar_imu.accel_g.y;
	az=smartcar_imu.accel_g.z;
	
  smartcar_imu.rpy_obs_deg[0]=-57.3f*atan(ax*invSqrt(ay*ay+az*az)); //�����
  smartcar_imu.rpy_obs_deg[1]= 57.3f*atan(ay*invSqrt(ax*ax+az*az)); //������
	//��������̬�ǿ������˲�
	smartcar_imu.rpy_kalman_deg[1]=kalman_filter(smartcar_imu.rpy_obs_deg[1],smartcar_imu.gyro_dps.x);
}


