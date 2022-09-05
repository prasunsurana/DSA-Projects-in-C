// =================== Support Code =================
// Hashmap 
//
// - Implement each of the functions to create a working hashmap.
// - Do not change any of the function declarations
//   - (i.e. hashmap_t* hashmap_create() should not have additional arguments)
// - You should not have any 'printf' statements in your functions other 
//   than functions that explicitly ask for printf output. 
//   - (You may consider using these printf statements to debug,
//     but they should be removed from your final version)
// - You may add any helper functions that you think you need
//   (if any, or otherwise for debugging)
// ==================================================
#ifndef MY_HASHMAP_T
#define MY_HASHMAP_T

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// An entry consisting of a key-value pair.
// This is specifically for a (char*, char*) key-value pair
typedef struct pair {
    char* key;
    char* value;
} pair_t;

// Each node holds a key and a value
typedef struct node {
    pair_t* kv; // key/value pair
    struct node* next;
} node_t;


// Simple hash function that will put a key into a bucket
// You should not modify this
int stringHash(char* myKey, int numberOfBuckets){
    return strlen(myKey) % numberOfBuckets;
}

// Create a function prototype to a function that takes
// in a char* and an int.
typedef int(*hashFunctionPointer)(char*, int); 

// Chained implementation of a hashmap
typedef struct hashmap {
    unsigned int buckets;   // i.e. size of the hashmap
    node_t** arrayOfLists;  // An array of linked lists for our buckets
                            // Read another way -- an array of node_t*

    // A function pointer to a hash function
    // The hash_function must take in a 'char*' as a key, and have a
    // second parameter specifying the number of buckets.
    hashFunctionPointer hashFunction;
} hashmap_t;

// Creates a new hashmap
// Allocates memory for a new hashmap.
// Initializes the capacity(i.e. number of buckets)
// The algorithm is:
//  - allocate memory for our hashmap
//  - set the number of buckets
//  - initialize our array of lists for each bucket
//  - setup our hash function to point to our stringHash function
//  - return new map that we have created
hashmap_t* hashmap_create(unsigned int _buckets) {
	// TODO: Implement me!!

	if(_buckets == 0){
		return NULL;
	}

	//Allocate memory for the hashmap
	hashmap_t* myMap = (hashmap_t*)malloc(sizeof(hashmap_t));

	//Check if malloc was unable to allocate memory
	if (myMap == NULL){
		return NULL;
	}

	//Initialize the number of buckets in myMap
	myMap->buckets = _buckets;

	//Allocate memory for the arrayOfLists 
	myMap->arrayOfLists = (node_t**)malloc(sizeof(node_t*)*_buckets);

	//Check if malloc was unable to allocate memory
	if (myMap->arrayOfLists == NULL){
		return NULL;
	}

	for (int i = 0; i < _buckets; i++){
		myMap->arrayOfLists[i] = NULL;
	}

	myMap->hashFunction = stringHash;
		

    return myMap;
}

// Frees a hashmap
// Responsibility to free a hashmap that has been previously allocated.
// Must also free all of the chains in the hashmap
// This function should run in O(n) time
void hashmap_delete(hashmap_t* _hashmap) {
    // TODO: Implement me!!
	
	//Check if hashmap is null
	if (_hashmap == NULL){
		return;
	}

	for (int i = 0; i < _hashmap->buckets; i++){
		node_t* temp = _hashmap->arrayOfLists[i];
		while (temp != NULL){
			node_t* tempnext = temp->next;
			free(temp->kv->key);
			free(temp->kv->value);
			free(temp->kv);
			free(temp);
			temp = tempnext;
		}
	}

	free(_hashmap->arrayOfLists);
	free(_hashmap);

}

// Returns a boolean value if a key has been put into
// the hashmap
//  - Returns a '1' if a key exists already
//  - Returns a '0' if the key does not exist
//  - Returns a '-9999' if the hashmap is NULL
// The algorithm is:
//  - Call the _hashmap's hash function on the key
//  - Search that bucket to see if the key exists.
// This function should run in average-case constant time
int hashmap_hasKey(hashmap_t* _hashmap, char* key) {
	// TODO: Implement me!!

	//Check if hashmap is null or key is null
	if (_hashmap == NULL || key == NULL){
		return -9999;
	}

	//Call the hash function on the key
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);

	//Create an interator called temp
	node_t* temp = _hashmap->arrayOfLists[bucket];

	while (temp != NULL){
		if (strcmp(temp->kv->key, key) == 0){
			return 1;
		}

		temp = temp->next;
	}

	return 0;

}

// Insert a new key/value pair into a hashmap
// The algorithm is:
//  - If a key already exists, do not add it--return
//  - Call the _hashmap's hash function on the key
//  - Store the key/value pair at the end of the buckets chain
//      - You should malloc the key/value in this function
// This function should run in average-case constant time
void hashmap_insert(hashmap_t* _hashmap,char* key,char* value) {
    // TODO: IMplement me!!

	//Exit the function if any of the parameters is null
	if (_hashmap == NULL || key == NULL || value == NULL){
		return;
	}

	//Exit the function if the key already exists 
	if (hashmap_hasKey(_hashmap, key) == 1){
		return;
	}

	//Allocate memory for a new key-value pair
	pair_t* newpair = (pair_t*)malloc(sizeof(pair_t));

	//Check whether malloc was unable to allocate memory
	if (newpair == NULL){
		return;
	}

	//Allocate memory for the new key and new value
	newpair->key = (char*)malloc(strlen(key)*sizeof(char)+1);
	newpair->value = (char*)malloc(strlen(value)*sizeof(char)+1);
	
	//Check whether malloc was unable to allocate memory for the key and value
	if (newpair->key == NULL || newpair->value == NULL){
		return;
	}

	//Copy the parameter values entered into the new pair's fields
	strcpy(newpair->key,key);
	strcpy(newpair->value,value);

	//Allocate memory to the new node
	node_t* newnode = (node_t*)malloc(sizeof(node_t));

	//Check whether malloc was unable to allocate memory
	if (newnode == NULL){
		return;
	}

	//Initialize the new node's fields
	newnode->next = NULL;
	newnode->kv = newpair;

	//Call the hash function on the key
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
	
	//Create an interator called iter
	node_t* iter = _hashmap->arrayOfLists[bucket];
	
	if (iter == NULL){
		_hashmap->arrayOfLists[bucket] = newnode;
	}else{
		while (iter->next != NULL){
			iter = iter->next;
		}
		
		iter->next = newnode;
	}	
}

// Return a value from a key 
// Returns NULL if the _hashmap is NULL
// Returns NULL if the key is not found
// The algorithm is:
//  - If the key does not exist, then--return NULL if not found.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and return the value
// This function should run in average-case constant time
char* hashmap_getValue(hashmap_t* _hashmap, char* key) {
	// TODO Implement me!!

	//Return null if hashmap is null or the key parameter is null
	if (_hashmap == NULL || key == NULL){
		return NULL;
	}

	//Return null if the key does not exist
	if (hashmap_hasKey(_hashmap, key) == 0){
		return NULL;
	}

	//Call the hash function on the key 
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
	
	//Create an interator called iter
	node_t* iter = _hashmap->arrayOfLists[bucket];
	
	while (iter != NULL){
		if (strcmp(iter->kv->key,key) == 0){
			return iter->kv->value;
		}
		
		iter = iter->next;
	}
	return NULL;
}

// Remove a key from a hashmap
// The algorithm is:
//  - Determine if the key exists--return if it does not.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and then remove it
// This function should run in average-case constant time
void hashmap_removeKey(hashmap_t* _hashmap, char* key) {
	// TODO: Implement me!!

	//Check if the function parameters are null
	if (_hashmap == NULL || key == NULL){
		return;
	}

	//Check if the key exists
	if (hashmap_hasKey(_hashmap,key) == 0){
		return;
	}	

	//Call the hash function on the key
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);

	//Create an interator called iter
	node_t* iter = _hashmap->arrayOfLists[bucket];

	if (iter != NULL){ //Removes the head node of the linked list if the keys match
		if (strcmp(iter->kv->key,key) == 0){
			_hashmap->arrayOfLists[bucket] = iter->next;
			free(iter->kv->key);
			free(iter->kv->value);
			free(iter->kv);
			free(iter);
			return;
		}
		
		//Create another iterator called temp
		node_t* temp = iter->next;

		while (temp!= NULL){ //Removes the node where the keys match if it is not the head node
			if (strcmp(temp->kv->key,key) == 0){
				iter->next = temp->next;
				free(temp->kv->key);
				free(temp->kv->value);
				free(temp->kv);
				free(temp);
				return;
			}
		
			iter = temp;
			temp = temp->next;
		}
	}	

}

// Update a key with a new Value
// The algorithm is:
//  - Returns immediately if the key does not exist
//  - Call the _hashmap's hash function on the key
//  - Updates the value of the key to the new value
// This function should run in average-case constant time
void hashmap_update(hashmap_t* _hashmap, char* key, char* newValue) {
	// TODO: Implement me!!


	//Check that the parameters entered are not null
	if (_hashmap == NULL || key == NULL || newValue == NULL){
		return;
	}

	//Exit the function if the key does not exist
	if (hashmap_hasKey(_hashmap,key) == 0){
		return;
	}

	//Call the hash function on the key
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);

	//Create an iterator called temp	
	node_t* temp = _hashmap->arrayOfLists[bucket];

	while (temp != NULL){
		if (strcmp(temp->kv->key,key) == 0){
			free(temp->kv->value);
			char* newval = (char*)malloc(strlen(newValue)*sizeof(char)+1);
	
			//Check if malloc was unable to allocate memory
			if (newval == NULL){
				return;
			}
	
			strcpy(newval, newValue);
			temp->kv->value = newval;
		}

		temp = temp->next;
	}
}

// Prints all of the keys in a hashmap
// The algorithm is:
//  - Iterate through every bucket and print out the keys
// This function should run in O(n) time
void hashmap_printKeys(hashmap_t* _hashmap){
	// TODO: Implement me!!

	//Check if hashmap parameter is null
	if (_hashmap == NULL){
		return;
	}

	for (int i = 0; i < _hashmap->buckets; i++){
		node_t* temp = _hashmap->arrayOfLists[i];
		while (temp != NULL){
			printf("%s\t", temp->kv->key);
			temp = temp->next;
		}
	}
}


#endif
