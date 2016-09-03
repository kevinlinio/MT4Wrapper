#include "stdafx.h"
#pragma once
#pragma comment(lib, "ws2_32.lib")

#include "MT4ManagerAPI.h"

CManagerFactory Factory;

/*
 * Class:     com_opsunv_mt4_api_MT4
 * Method:    WinsockStartup
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_opsunv_mt4_api_MT4_WinsockStartup
  (JNIEnv *, jclass){
	Factory.WinsockStartup();
}


/*
 * Class:     com_opsunv_mt4_api_MT4
 * Method:    init
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_opsunv_mt4_api_MT4_init
	(JNIEnv * env, jobject obj){
	
	CManagerInterface *manager;
	
	if (Factory.IsValid() == FALSE || (manager = Factory.Create(ManAPIVersion)) == NULL){
		return -1;
	}

	return (unsigned int)manager;

}

/*
 * Class:     com_opsunv_mt4_api_MT4
 * Method:    Release
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_opsunv_mt4_api_MT4_Release
	(JNIEnv * env,jobject obj,jint ptr){
	CManagerInterface *manager = (CManagerInterface*)ptr;

	return manager->Release();
}

/*
 * Class:     com_opsunv_mt4_api_MT4
 * Method:    ErrorDescription
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_opsunv_mt4_api_MT4_ErrorDescription
	(JNIEnv * env, jobject obj, jint ptr, jint code){

	CManagerInterface *manager = (CManagerInterface*)ptr;
	LPCSTR str = manager->ErrorDescription(code);

	return (env)->NewStringUTF(str);

}

/*
 * Class:     com_opsunv_mt4_api_MT4
 * Method:    Connect
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_opsunv_mt4_api_MT4_Connect
	(JNIEnv * env, jobject obj,jint ptr, jstring server){

	CManagerInterface *manager = (CManagerInterface*)ptr;

	const char* srv = (env)->GetStringUTFChars(server,JNI_FALSE);
	int rs = manager->Connect(srv);
	(env)->ReleaseStringUTFChars(server,srv);

	return rs;
}

/*
 * Class:     com_opsunv_mt4_api_MT4
 * Method:    Disconnect
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_opsunv_mt4_api_MT4_Disconnect
	(JNIEnv *, jobject,jint ptr){

	CManagerInterface *manager = (CManagerInterface*)ptr;

	return manager->Disconnect();
}

/*
 * Class:     com_opsunv_mt4_api_MT4
 * Method:    IsConnected
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_opsunv_mt4_api_MT4_IsConnected
  (JNIEnv *, jobject,jint ptr){
	CManagerInterface *manager = (CManagerInterface*)ptr;
	return manager->IsConnected();
}

/*
 * Class:     com_opsunv_mt4_api_MT4
 * Method:    Login
 * Signature: (ILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_opsunv_mt4_api_MT4_Login
	(JNIEnv * env, jobject obj,jint ptr, jint uid, jstring password){

	CManagerInterface *manager = (CManagerInterface*)ptr;

	const char* _password = env->GetStringUTFChars(password,JNI_FALSE);
	int rs = manager->Login(uid,_password);
	env->ReleaseStringUTFChars(password,_password);

	return rs;
}

/*
 * Class:     com_opsunv_mt4_api_MT4
 * Method:    TradesRequest
 * Signature: ()[Lcom/opsunv/mt4/api/bean/TradeRecord;
 */
JNIEXPORT jobjectArray JNICALL Java_com_opsunv_mt4_api_MT4_TradesRequest
	(JNIEnv * env, jobject obj,jint ptr){

	CManagerInterface *manager = (CManagerInterface*)ptr;

	int total = 0;
	TradeRecord * records = manager->TradesRequest(&total);
	
	if(total==0){
		return NULL;
	}

	jclass clazz = env->FindClass("com/opsunv/mt4/api/bean/TradeRecord");
	if(clazz==NULL){
		printf("error");
	}
	
	jobjectArray arr = env->NewObjectArray(total,clazz,NULL);
	
	
	for(int i=0;i<total;i++){
		jmethodID cid = env->GetMethodID(clazz,"<init>","()V");
		jobject record = env->NewObject(clazz,cid);
		
		jmethodID setOrder = env->GetMethodID(clazz,"setOrder","(I)V");

		env->CallVoidMethod(record,setOrder,123);

		env->SetObjectArrayElement(arr,i,record);
	}

	return arr;
}

/*
 * Class:     com_opsunv_mt4_api_MT4
 * Method:    TradesUserHistory
 * Signature: ()[Lcom/opsunv/mt4/api/bean/TradeRecord;
 */
JNIEXPORT jobjectArray JNICALL Java_com_opsunv_mt4_api_MT4_TradesUserHistory
	(JNIEnv * env, jobject obj,jint ptr){
	return NULL;
}