#ifndef __FIELD_INFO_H__
#define __FIELD_INFO_H__

class FieldInfo
{
	public:
		FieldInfo() {
				_field_width = 6050;
				_field_height = 4050;
				//_team_color = WorldState::BLUE;
				_number_of_enemies = 5;
				_number_of_allies = 5;
		 };
		~FieldInfo () { };

		char _team_color;
		double _field_width, _field_height;
		int _number_of_enemies, _number_of_allies;
		
};

#endif /* __FIELD_INFO_H__ */

