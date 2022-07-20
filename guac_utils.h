#ifndef __guac_utils_h__
#define __guac_utils_h__

// by Paper in C
// for C++ use guac_utils.hpp by totallyNotAUser

#include <string.h>
#include <stdlib.h>

/**
 * Decodes a guac-encoded string.
 * this function is not safe!!! make sure your strings are terminated ;)
 * my first time dealing with dynamic memory management...
 *
 * char* encoded_str | C-style encoded string to decode
 * char** ret        | malloc'd (empty) char pointer array
 * int* reta         | pointer to an int, stores the amount of items in the array
**/
char** guac_decode(char* encoded_str, char** ret, int* reta) {
	char* _msg = calloc(strlen(encoded_str) + 1, sizeof(char));
	if (_msg == NULL)
		return NULL;
	strncpy(_msg, encoded_str, strlen(encoded_str));
	int i, j;
	for (j = i = 0; i < strlen(_msg); j++) {
		/* length */
		int len_end = (strchr(_msg, '.') - _msg);
		if (_msg[len_end] == '\0') {
			break;
		}
		int len = atoi(strtok(_msg, "."));
		/* data */
		i += (len_end + 1);
		if (_msg[i] == ',') {
			i++;
		} else if (_msg[i] == ';') {
			break;
		}
		ret = realloc(ret, (j + 1) * sizeof(char*));
		ret[j] = calloc(len, sizeof(char));
		strncpy(ret[j], &_msg[i], len);
		strncpy(_msg, &_msg[i+len+1], strlen(encoded_str));
		i = 0;
	}
	free(_msg);
	*reta = j;
	return ret;
}

/**
 * Encodes into guac format...
 * also uses strlen(), but the data in ret should be safe anyways
 *
 * char** ret | list of items to encode
 * int reta   | amount of items in list, returned by guac_decode
**/
char* guac_encode(char** ret, int reta) {
	int i;
	char* str = calloc(1, sizeof(char));
	for (i = 0; i < reta; i++) {
		str = realloc(str, sizeof(str) + ((strlen(ret[i])) * sizeof(char)));
		sprintf(str + strlen(str), "%lld.%s,", strlen(ret[i]), ret[i]);
	}
	str[strlen(str)-1] = ';';
	return str;
}

#endif // __guac_utils_h__
