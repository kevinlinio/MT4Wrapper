package com.opsunv.mt4.api.bean;

public class SymbolSummary
{
    // Symbol name
    private String symbol;

    // Symbol position
    private int count;

    // The accuracy of average prices
    private int digits;

    // The name of the group of symbols
    private int type;


    //---- Client information

    // Number of clients orders
    private int orders;

    // The volume of long positions
    private long buyLots;

    // The volume of short postions
    private long sellLots;

    // The average Buy price
    private double buyPrice;

    // The average Sell price
    private double sellPrice;

    // Client profit/loss
    private double profit;


    //---- Information about hedging positions

    // The number of hedging orders
    private int covOrders;

    // The volume of long positions
    private long covBuyLots;

    // The volume of short positions
    private long covSellLots;

    // The average buy price
    private double covBuyPrice;

    // The average sell price
    private double covSellPrice;

    // Profit/loss
    private double covProfit;


    public String getSymbol() {
        return symbol;
    }

    public void setSymbol(String symbol) {
        this.symbol = symbol;
    }

    public int getCount() {
        return count;
    }

    public void setCount(int count) {
        this.count = count;
    }

    public int getDigits() {
        return digits;
    }

    public void setDigits(int digits) {
        this.digits = digits;
    }

    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    public int getOrders() {
        return orders;
    }

    public void setOrders(int orders) {
        this.orders = orders;
    }

    public long getBuyLots() {
        return buyLots;
    }

    public void setBuyLots(long buyLots) {
        this.buyLots = buyLots;
    }

    public long getSellLots() {
        return sellLots;
    }

    public void setSellLots(long sellLots) {
        this.sellLots = sellLots;
    }

    public double getBuyPrice() {
        return buyPrice;
    }

    public void setBuyPrice(double buyPrice) {
        this.buyPrice = buyPrice;
    }

    public double getSellPrice() {
        return sellPrice;
    }

    public void setSellPrice(double sellPrice) {
        this.sellPrice = sellPrice;
    }

    public double getProfit() {
        return profit;
    }

    public void setProfit(double profit) {
        this.profit = profit;
    }

    public int getCovOrders() {
        return covOrders;
    }

    public void setCovOrders(int covOrders) {
        this.covOrders = covOrders;
    }

    public long getCovBuyLots() {
        return covBuyLots;
    }

    public void setCovBuyLots(long covBuyLots) {
        this.covBuyLots = covBuyLots;
    }

    public long getCovSellLots() {
        return covSellLots;
    }

    public void setCovSellLots(long covSellLots) {
        this.covSellLots = covSellLots;
    }

    public double getCovBuyPrice() {
        return covBuyPrice;
    }

    public void setCovBuyPrice(double covBuyPrice) {
        this.covBuyPrice = covBuyPrice;
    }

    public double getCovSellPrice() {
        return covSellPrice;
    }

    public void setCovSellPrice(double covSellPrice) {
        this.covSellPrice = covSellPrice;
    }

    public double getCovProfit() {
        return covProfit;
    }

    public void setCovProfit(double covProfit) {
        this.covProfit = covProfit;
    }

    @Override
    public String toString() {
        return "SymbolSummary{" +
                "symbol='" + symbol + '\'' +
                ", count=" + count +
                ", digits=" + digits +
                ", type=" + type +
                ", orders=" + orders +
                ", buyLots=" + buyLots +
                ", sellLots=" + sellLots +
                ", buyPrice=" + buyPrice +
                ", sellPrice=" + sellPrice +
                ", profit=" + profit +
                ", covOrders=" + covOrders +
                ", covBuyLots=" + covBuyLots +
                ", covSellLots=" + covSellLots +
                ", covBuyPrice=" + covBuyPrice +
                ", covSellPrice=" + covSellPrice +
                ", covProfit=" + covProfit +
                '}';
    }
}
