#include "HashMap.h"

HashMap::HashMap(int size)
{
	hashArray = new Node*[size];
	for (int i = 0; i < size; i++) {
		hashArray[i] = nullptr;
	}
	sizeOfArray = size;
}

HashMap::~HashMap()
{
	for (int i = 0; i < sizeOfArray; i++) {
		while (hashArray[i] != nullptr) {
			Node* temp = new Node();
			temp = hashArray[i];
			hashArray[i] = temp->next;
			delete temp;

		}
	}
	delete[] hashArray;
}
int HashMap::GenerateHash(string key) const
{
	int t = 123;
	for ( int i = 0; i <key.size(); i++)
	{
		int c = int(key[i]);
		t = (2 * t + c);
		
	}
	return t%sizeOfArray;
}
bool HashMap::IsKeyPresent(string const & key) const
{
	int hash = GenerateHash(key);
	Node* hashp = hashArray[hash];
	
	while (hashp != nullptr) {
		if (hashp->key == key) {
			
			return true;
		}
		hashp = hashp->next;
	}
	return false;
}

void HashMap::SetKeyValue(string const & key, int value)
{
	//key is present
	
	int hash = GenerateHash(key);
	
	if (IsKeyPresent(key)) {
		
		Node* hashp = hashArray[hash];
		while (hashp != nullptr) {
			if (hashp->key == key) {
				hashp->value = value;
				
				return;
			}
			hashp = hashp->next;
		}

	}

	Node* newNode = new Node(key, value);
	newNode->next = hashArray[hash];
	hashArray[hash] = newNode;
	return;
}

bool HashMap::GetKeyValue(string const & key, int & value)
{
	int hash = GenerateHash(key);
	
	if (IsKeyPresent(key)) {
		Node* hashp = hashArray[hash];
		while (hashp != nullptr) {
			if (hashp->key == key) {
				value = hashp->value;
				
				return true;
			}
			hashp = hashp->next;
		}

	}
	return false;
}

Iterator HashMap::begin()
{
	int index = 0;
	while (hashArray[index] == nullptr) {
		index++;
	}
	return Iterator(index, hashArray, sizeOfArray);
}

Iterator HashMap::end()
{
	return Iterator(sizeOfArray - 1, hashArray, sizeOfArray);
}

Iterator::Iterator(int index, Node ** hashArray, int sizeOfArray)
{
	this->index = index;
	current = hashArray[index];
	this->sizeOfArray = sizeOfArray;
	this->hashArray = hashArray;
}

Iterator::Iterator()
{
	index = 0;
	current = nullptr;
	sizeOfArray = 0;
}

string Iterator::operator*()
{
	return current->key;
}

void Iterator::operator++()
{
	if (current->next == nullptr) {
		index = index + 1;
		while(hashArray[index] == nullptr) {
			++index;
		}
		current = hashArray[index];
		return;
	}
	current = current->next;
	return;
}

bool Iterator::operator!=(Iterator & other)
{
	if (current->key != other.current->key) {
		return true;
	}
	return false;
}

bool Iterator::is_item()
{
	return current == nullptr;
}
