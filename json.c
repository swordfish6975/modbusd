/**
 * @file json.c
 * @author Taka Wang
 * @brief cJSON helper functions
*/

#include <stdio.h>
#include <stdlib.h>
#include "json.h"

char *json_get_char (cJSON *inJson, const char *key)
{
    return cJSON_GetObjectItem (inJson, key)->valuestring;
}

int json_get_int (cJSON *inJson, const char *key)
{
    return cJSON_GetObjectItem (inJson, key)->valueint;
}

void json_set_int (cJSON *inJson, const char *key, int value)
{
    cJSON_GetObjectItem (inJson, key)->valueint = value;
}

double json_get_double (cJSON *inJson, const char *key)
{
    return cJSON_GetObjectItem (inJson, key)->valuedouble;
}

void json_set_double (cJSON *inJson, const char *key, double value)
{
    cJSON_GetObjectItem (inJson, key)->valuedouble = value;
}

long json_get_long (cJSON *inJson, const char *key)
{
    // convert double float to long integer
    return (long)cJSON_GetObjectItem(inJson, key)->valuedouble;
}

int file_to_json (const char *fname, cJSON **outJson)
{
    FILE *fPtr = fopen (fname,"rb");
    if (fPtr) 
    {
        fseek(fPtr, 0, SEEK_END);
        long len = ftell (fPtr);
        fseek(fPtr, 0, SEEK_SET);
        char *data = (char*) malloc (len+1);
        if (data != NULL) 
        {
            int _ = fread (data, 1, len, fPtr); _=_;
            fclose (fPtr);
            *outJson = cJSON_Parse (data);
            free (data);
            return outJson ? 0 : 1;
        }
        else
        {
            return -1;
        }
       
    }
    else
    {
        return -1;
    }
}

int json_to_file (const char *fname, cJSON *inJson)
{
    FILE *fPtr = fopen(fname, "w");
    if (fPtr)
    {
        fprintf (fPtr, "%s", cJSON_Print (inJson));
        fclose (fPtr);
        return 0;
    }
    else
    {
        return -1;
    }
}
