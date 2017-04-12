package com.opsunv.mt4.api;

import com.opsunv.mt4.api.bean.SymbolSummary;
import com.opsunv.mt4.api.bean.TradeRecord;

public interface ManagerAPI {
	
	public int release();
	
	public String getErrorDescription(int code);
	
	//
	
	public int connect(String server);
	
	public int disconnect();
	
	public boolean isConnected();
	
	public int login(int uid,String password);

	public boolean switchToPumpingMode();
	
	public TradeRecord[] getTradesRequest();
	
	public TradeRecord[] getTradesUserHistory();

	public SymbolSummary[] getSummaryPositionsAll();
}
