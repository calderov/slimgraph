#include "typedefs.h"

using namespace std;

class PropertyManager {

public:

	PROPERTY_MAP _propertyMap;
	
	PropertyManager();
	~PropertyManager();

	// Add, delete, clear and exists operations
	bool property_exists(PROPERTY_NAME name);
	bool add(PROPERTY_NAME name, PROPERTY_TYPE type);
	bool del(PROPERTY_NAME name);
	bool del_all();
	bool clear(ELEMID elemId);
	
	// Properties printing functions
	void print_properties(ELEMID elemId);
	void print_properties();
	
	// Get property values
	const char* property_type_to_string(PROPERTY_TYPE type);
	PROPERTY_RESULT get(ELEMID elemId, PROPERTY_NAME name);
	size_t total_properties();

	// Set string property values
	bool set(ELEMID elemId, PROPERTY_NAME name, const char* value);
	bool set(ELEMID elemId, PROPERTY_NAME name, string value)
	{
		return set(elemId, name, value.c_str());
	}

	// Set numerical values
	template <typename T> bool set(ELEMID elemId, PROPERTY_NAME name, T value)
	{
		// If there is no property with matching name, abort
		if (!property_exists(name))
			return false;

		// If the expected property type is a string, abort
		if (_propertyMap[name].type == STRING) 
			return false;

		try
		{
			// If the node already has a value for this property, overwrite
			if (_propertyMap[name].element.count(elemId))
			{
				switch (_propertyMap[name].type)
				{
					case DOUBLE:
						_propertyMap[name].element[elemId].valueNum = (double)value;
						return true;

					default:
						return false;
				}
			}
			// The node has no value for this property yet
			else
			{
				// Create new PROPERTY_VALUE
				PROPERTY_VALUE propertyValue;
				switch(_propertyMap[name].type)
				{
					case DOUBLE:
						propertyValue.valueNum = (double)value;
						_propertyMap[name].element[elemId] = propertyValue;
						return true;

					default:
						return false;
				}
			}
		}
		catch (...)
		{
			return false;
		}

	}
};
