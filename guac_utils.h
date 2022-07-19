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
 * stuff can and WILL break
 *
 * char* encoded_str | C-style encoded string to decode
 * char** ret        | malloc'd (empty) char pointer array
 * int* reta         | pointer to an int, stores the amount of items in the array
**/
char** guac_decode(char* encoded_str, char** ret, int* reta) {
	int i, j;
	for (j = i = 0; i < strlen(encoded_str); j++) {
		char* tmp = calloc(1, sizeof(char));
		/* length */
		int len_end = (strchr(encoded_str, '.') - encoded_str);
		if (encoded_str[len_end] == '\0') {
			break;
		}
		tmp = realloc(tmp, len_end * sizeof(char));
		memcpy(tmp, &encoded_str[i], len_end);
		tmp[len_end] = '\0';
		int len = atoi(tmp);
		tmp[0] = '\0'; // nobody will notice i'm wearing the same shirt
		/* data */
		i += (len_end + 1);
		tmp = realloc(tmp, len * sizeof(char));
		memcpy(tmp, &encoded_str[i], len);
		i += len;
		tmp[len] = '\0';
		ret = realloc(ret, (j + 1) * sizeof(char*));
		ret[j] = calloc(len, sizeof(char));
		strncpy(ret[j], tmp, len);
		if (encoded_str[i] == ',') {
			i++;
		} else if (encoded_str[i] == ';') {
			break;
		}
		free(tmp);
	}
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
	char* str = calloc(1, sizeof(char));
	for (int i = 0; i <= reta; i++) {
		str = realloc(str, (3 + (strlen(ret[i]))) * sizeof(char));
		sprintf(str + strlen(str), "%d.%s,", strlen(ret[i]), ret[i]);
	}
	str[strlen(str)-1] = ';';
	return str;
}

#endif // __guac_utils_h__
