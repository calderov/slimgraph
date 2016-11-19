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


bool PropertyManager::del(PROPERTY_NAME name)
{
	// Not implemented
	return true;
}


bool PropertyManager::clear(ELEMID elemId)
{
	// Not implemented
	return true;
}


bool PropertyManager::clear_all()
{
	// Not implemented
	return true;
}


void PropertyManager::print_properties(ELEMID elemId)
{
	// Not implemented
	cout << "print properties" << endl;
}


void PropertyManager::print_properties()
{
	// Not implemented
	cout << "print properties" << endl;
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
