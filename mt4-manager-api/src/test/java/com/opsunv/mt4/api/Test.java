package com.opsunv.mt4.api;



public class Test {
	public static void main(String[] args) throws Exception{
		ManagerAPI mt4 = new MT4();
		mt4.connect("82.145.47.76:443");
		if(mt4.isConnected()){
			System.out.println("connected");
		}
		
		int rs = mt4.login(7598427, "a003Go43");
		
		System.out.println(mt4.getErrorDescription(rs));
		
		//TradeRecord[] records = mt4.getTradesRequest();
		
		//System.out.println(records.length);
	}
}
