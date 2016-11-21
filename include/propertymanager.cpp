#include <typeinfo>
#include <iostream>
#include "propertymanager.h"

PropertyManager::PropertyManager()
{}


PropertyManager::~PropertyManager()
{}


bool PropertyManager::property_exists(PROPERTY_NAME name)
{
	if(_propertyMap.count(name))
		return true;
	return false;
}


bool PropertyManager::add(PROPERTY_NAME name, PROPERTY_TYPE type)
{
	// If the property already exists, abort
	if (property_exists(name))
		return false;

	VALUE_MAP valueMap;
	valueMap.type = type;

	_propertyMap[name] = valueMap;

	return true;
}


bool PropertyManager::clear(ELEMID elemId)
{
	// Iterate over all properties removing the values maped to elemId
	for (PROPERTY_MAP::iterator it = _propertyMap.begin(); it != _propertyMap.end(); ++it)
	{
		_propertyMap[it->first].element.erase(elemId);
	}

	return true;
}


bool PropertyManager::del(PROPERTY_NAME name)
{
	return _propertyMap.erase(name);
}


bool PropertyManager::del_all()
{
	_propertyMap.clear();
	return true;
}


const char* PropertyManager::property_type_to_string(PROPERTY_TYPE type)
{
	switch (type)
	{
		case STRING:
			return "STRING";
		case DOUBLE:
			return "DOUBLE";
		default:
			return "ERROR";
	}
}



void PropertyManager::print_properties(ELEMID elemId)
{
	for (PROPERTY_MAP::iterator it = _propertyMap.begin(); it != _propertyMap.end(); ++it)
	{
		cout << "   " << it->first << " : " << property_type_to_string(_propertyMap[it->first].type) << " : " << get(elemId, it->first).to_string() << endl;
	}
}


void PropertyManager::print_properties()
{
	for (PROPERTY_MAP::iterator it = _propertyMap.begin(); it != _propertyMap.end(); ++it)
	{
		cout << "   " << it->first << " : " << property_type_to_string(_propertyMap[it->first].type) << endl;
	}
}


PROPERTY_RESULT PropertyManager::get(ELEMID elemId, PROPERTY_NAME name)
{
	PROPERTY_RESULT propertyResult;
	propertyResult.type = ERROR;

	if (property_exists(name))
	{
		if (_propertyMap[name].element.count(elemId))
		{
			propertyResult.type = _propertyMap[name].type;
			propertyResult.value = _propertyMap[name].element[elemId];
		}
	}

	return propertyResult;
}


size_t PropertyManager::total_properties()
{
	return _propertyMap.size();
}


bool PropertyManager::set(ELEMID elemId, PROPERTY_NAME name, const char* value)
{
	// If there is no property with matching name, abort
	if (!property_exists(name))
		return false;

	// If the expected property type is a number, abort
	if (_propertyMap[name].type == DOUBLE)
	{
		cout << "Error: Property "<< name <<" not set. Incompatible type." << endl;
		return false;
	}

	try
	{
		// If the node already has a value for this property, overwrite
		if (_propertyMap[name].element.count(elemId))
		{
			switch (_propertyMap[name].type)
			{
				case STRING:
					_propertyMap[name].element[elemId].valueStr = value;
					return true;

				default:
					cout << "Error: Property "<< name <<" not set. Incompatible type." << endl;
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
				case STRING:
					propertyValue.valueStr = value;
					_propertyMap[name].element[elemId] = propertyValue;
					return true;

				default:
					cout << "Error: Property "<< name <<" not set. Incompatible type." << endl;
					return false;
			}
		}
	}
	catch (...)
	{
		cout << "Error: Property not set." << endl;
	}

	return false;
}
