/**
 * Copyright (c) Paper 2022
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#ifndef __guac_utils_h__
#define __guac_utils_h__

#include <string.h>
#include <stdlib.h>

/**
 * valid syntax:
 *
 * int reta;
 * char* str = "5.penis,6.balls1;"; // this can be any proper guac string
 * char** ret = NULL;
 * ret = guac_decode(str, ret, &reta);
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
