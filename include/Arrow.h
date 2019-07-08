#pragma once
#include "Defs.h"
/////////////////////////
//Ported From MRPT CArrow.
/////////////////////////
namespace bogong {
	namespace model
	{
	
		class Arrow
		{
			point3 p1;
			point3 p2;
			vec3 v;
			float m_headRatio=0.0f;
			float m_smallRadius = 0.0f, m_largeRadius = 0.0f;
			float m_arrow_roll=0.0f;
			float m_arrow_pitch = 0.0f;
			float m_arrow_yaw = 0.0f;
			public:
				//Setters
				void setArrowYawPitchRoll(float yaw, float pitch, float roll)
				{
					m_arrow_yaw = yaw;
					m_arrow_pitch = pitch;
					m_arrow_roll = roll;
				}
				void setLargeRadius(float rat)
				{
					m_largeRadius = rat;
				}
				
				//Constructors
				Arrow(point3 p_Begin, point3 p_End, 
					  float p_SmallHeadSize = 0.2f, 
					  float p_LargeHeadSize = 0.5f,
					  float p_Arrow_Roll    = -1.0f,
					  float p_Arrow_Pitch   = -1.0f,
					  float p_Arrow_Yaw     = -1.0f)
					:
					p1(p_Begin),
					p2(p_End),
					m_smallRadius(p_SmallHeadSize),
					m_largeRadius(p_LargeHeadSize),
					m_arrow_roll(p_Arrow_Roll),
					m_arrow_pitch(p_Arrow_Pitch),
					m_arrow_yaw(p_Arrow_Yaw)
				{

				}
		};
	}
}
