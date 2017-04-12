#include "stdafx.h"
#pragma once
#pragma comment(lib, "ws2_32.lib")

#include "MT4ManagerAPI.h"

/*
 * use javap -s class to find method signature
 */
void setStringValue(JNIEnv * env, jobject obj, jclass clazz, const char *methodName,  const char* val) {
	jmethodID method = env->GetMethodID(clazz, methodName, "(Ljava/lang/String;)V");
	env->CallVoidMethod(obj, method, env->NewStringUTF(val));
}

void setIntValue(JNIEnv * env, jobject obj, jclass clazz, const char *methodName, jint val) {
	jmethodID method = env->GetMethodID(clazz, methodName, "(I)V");
	env->CallVoidMethod(obj, method, val);
}

void setLongValue(JNIEnv * env, jobject obj, jclass clazz, const char *methodName, jlong val) {
	jmethodID method = env->GetMethodID(clazz, methodName, "(J)V");
	env->CallVoidMethod(obj, method, val);
}

void setDoubleValue(JNIEnv * env, jobject obj, jclass clazz, const char *methodName, jdouble val) {
	jmethodID method = env->GetMethodID(clazz, methodName, "(D)V");
	env->CallVoidMethod(obj, method, val);
}



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

void __stdcall pumpingModelCallback(int code)
{
}

/*
 * Class:     com_opsunv_mt4_api_MT4
 * Method:    PumpingSwitch
 * Signature: ()I
 */
JNIEXPORT jboolean JNICALL Java_com_opsunv_mt4_api_MT4_PumpingSwitch
  (JNIEnv *env, jobject obj, jint ptr){

	CManagerInterface *manager = (CManagerInterface*)ptr;

	int pumpingResult = manager->PumpingSwitch(pumpingModelCallback, 0, 0, CLIENT_FLAGS_HIDETICKS | CLIENT_FLAGS_HIDEMAIL | CLIENT_FLAGS_HIDENEWS | CLIENT_FLAGS_HIDEONLINE | CLIENT_FLAGS_HIDEUSERS);

    return pumpingResult == TRUE ? JNI_TRUE : JNI_FALSE;
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
		TradeRecord tr = records[i];

		jmethodID cid = env->GetMethodID(clazz,"<init>","()V");
		jobject record = env->NewObject(clazz,cid);
		
		setIntValue(env, record, clazz, "setOrder", tr.order);
		setIntValue(env, record, clazz, "setLogin", tr.login);
		setStringValue(env, record, clazz, "setSymbol",tr.symbol);
		//etc...

		env->SetObjectArrayElement(arr,i,record);
	}

	return arr;
}


/*
* Class:     com_opsunv_mt4_api_MT4
* Method:    TradesRequest
* Signature: ()[Lcom/opsunv/mt4/api/bean/TradeRecord;
*/
JNIEXPORT jobjectArray JNICALL Java_com_opsunv_mt4_api_MT4_SummaryGetAll
(JNIEnv * env, jobject obj, jint ptr) {

	CManagerInterface *manager = (CManagerInterface*)ptr;

	int total = 0;
	SymbolSummary * records = manager->SummaryGetAll(&total);

	if (total == 0) {
		return NULL;
	}

	jclass clazz = env->FindClass("com/opsunv/mt4/api/bean/SymbolSummary");
	if (clazz == NULL) {
		printf("error");
		fflush(stdout);
	}

	jobjectArray arr = env->NewObjectArray(total, clazz, NULL);
	jmethodID cid = env->GetMethodID(clazz, "<init>", "()V");

	for (int i = 0; i<total; i++) {
		SymbolSummary ss = records[i];
		jobject record = env->NewObject(clazz, cid);
		setStringValue(env, record, clazz, "setSymbol", ss.symbol);
		setIntValue(env, record, clazz, "setCount", ss.count);
		setIntValue(env, record, clazz, "setDigits", ss.digits);
		setIntValue(env, record, clazz, "setType", ss.type);
		setIntValue(env, record, clazz, "setOrders", ss.orders);
		setLongValue(env, record, clazz, "setBuyLots", ss.buylots);
		setLongValue(env, record, clazz, "setSellLots", ss.selllots);
		setDoubleValue(env, record, clazz, "setBuyPrice", ss.buyprice);
		setDoubleValue(env, record, clazz, "setSellPrice", ss.sellprice);
		setDoubleValue(env, record, clazz, "setProfit", ss.profit);
		setIntValue(env, record, clazz, "setCovOrders", ss.covorders);
		setLongValue(env, record, clazz, "setCovBuyLots", ss.covbuylots);
		setLongValue(env, record, clazz, "setCovSellLots", ss.covselllots);
		setDoubleValue(env, record, clazz, "setCovBuyPrice", ss.covbuyprice);
		setDoubleValue(env, record, clazz, "setCovSellPrice", ss.covsellprice);
		setDoubleValue(env, record, clazz, "setCovProfit", ss.covprofit);

		env->SetObjectArrayElement(arr, i, record);
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