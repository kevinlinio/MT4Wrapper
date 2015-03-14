package com.opsunv.mt4.api;

import com.opsunv.mt4.api.bean.TradeRecord;

public class MT4ManagerAPI implements ManagerAPI{
	
	//manager的指针地址
	private int ptr;
	
	public MT4ManagerAPI() {
		ptr = init();
	}
	
	/**
	 * 初始化
	 * @return 返回CManagerInterface实例的地址
	 */
	private native int init();
	
	/**
	 * 释放manager实例
	 * @param ptr
	 * @return
	 */
	private native int Release(int ptr);
	
	/**
	 * 获取错误信息
	 * @param ptr
	 * @param code
	 * @return
	 */
	private native String ErrorDescription(int ptr,int code);
	
	/**
	 * 连接到服务端
	 * @param ptr
	 * @param server
	 * @return
	 */
	private native int Connect(int ptr,String server);
	
	/**
	 * 断开链接
	 * @param ptr
	 * @return
	 */
	private native int Disconnect(int ptr);
	
	/**
	 * 是否连接
	 * @param ptr
	 * @return
	 */
	private native int IsConnected(int ptr);
	
	/**
	 * 登陆
	 * @param ptr
	 * @param uid
	 * @param password
	 * @return
	 */
	private native int Login(int ptr,int uid,String password);
	
	//orders
	
	/**
	 * 交易信息
	 * @param ptr
	 * @return
	 */
	private native TradeRecord[] TradesRequest(int ptr);
	
	private native TradeRecord[] TradesUserHistory(int ptr);
	
	/**
	 * 加载socket
	 */
	private static native void WinsockStartup();
	
	static{
		System.loadLibrary("MT4Warpper");
		WinsockStartup();
	}

	
	@Override
	public int release() {
		return Release(ptr);
	}

	@Override
	public String getErrorDescription(int code) {
		return ErrorDescription(ptr,code);
	}

	@Override
	public int connect(String server) {
		return Connect(ptr, server);
	}

	@Override
	public int disconnect() {
		return Disconnect(ptr);
	}

	@Override
	public boolean isConnected() {
		return IsConnected(ptr)==1;
	}

	@Override
	public int login(int uid, String password) {
		return Login(ptr, uid, password);
	}

	@Override
	public TradeRecord[] getTradesRequest() {
		return TradesRequest(ptr);
	}

	@Override
	public TradeRecord[] getTradesUserHistory() {
		return null;
	}

}
