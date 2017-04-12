package com.opsunv.mt4.api;

import com.opsunv.mt4.api.bean.SymbolSummary;

public class Test {
	public static void main(String... args) throws Exception{

		System.out.println(System.getProperty("user.dir"));

		ManagerAPI mt4 = new MT4();
		mt4.connect("12.34.45.56:443");
		if(mt4.isConnected()){
			System.out.println("connected");
		}

		int rs = mt4.login(1234, "xxxx");

		System.out.println("Logged in: " + rs);
		System.out.println(mt4.getErrorDescription(rs));

		boolean pumpingSuccess = mt4.switchToPumpingMode();
		

		while(true) {
			System.out.println("Woke up");
			Thread.sleep(2000);

			SymbolSummary[] records = mt4.getSummaryPositionsAll();

			for (SymbolSummary record : records) {
				System.out.println(record);
			}
		}
	}
}
