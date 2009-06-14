#include <jni.h>
#include <stdio.h>
#include "dbookjava.h"
 
JNIEXPORT void JNICALL 
Java_dbookjava_check_isbn(JNIEnv *env, jobject obj)
{
    printf("Hello World!\n");
    return;
}
