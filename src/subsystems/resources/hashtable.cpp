#include "hashtable.h"

namespace MagusEngine
{
	HashTable::HashTable()
	{
		_data = 0;
		_maxsize = 0;
		_dataCount = 0;
	}

	bool HashTable::Initialise(int size)
	{
		/* Allocate memory for the hash table */
		_data = (HashDataItem**)malloc(sizeof(HashDataItem*) * size);
		_maxsize = size;

		if (_data != NULL)
		{
			LOGDINFO("Hashtable Created with %d Bytes", sizeof(HashDataItem*) * size);
			return true;
		}

		LOGERROR("Unable to Initialise Hashtable with %d Bytes", sizeof(HashDataItem*) * size);
		return false;
	}

	bool HashTable::Insert(HashDataItem* item)
	{
		if (_dataCount == _maxsize)
			return false;
		
		_data[_dataCount] = item;
		_dataCount++;

		return true;
	}

	HashDataItem* HashTable::Get(int index)
	{
		return _data[index];
	}

	HashDataItem* HashTable::Search(const char* name)
	{
		for (int i = 0; i < _dataCount; i++)
		{
			if (strcmp(_data[i]->id, name) == 0)
			{
				return _data[i];
			}
		}
		return NULL;
	}

	/* Getters */
	int HashTable::GetCount() { return _dataCount; }
	int HashTable::GetMaxCount() { return _maxsize; }
}