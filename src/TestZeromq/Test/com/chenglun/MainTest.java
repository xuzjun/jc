package com.chenglun;

import org.junit.Test;

public class MainTest {
    /* TODO:
      1. client send req (dest, topic)
      2. get rep: pull_info
    */

    public void Client(){
        StockQuotationService.Client c = new StockQuotationService.Client("tcp://localhost:6666");
        String info = c.getTopicPushInfo("topic_stock_day_quotation", "Stock_Code", "20120101", "20150101");
        if(info == null){
            //PrintError("get Pull info failed!");
            return ;
        }
        System.out.println("client recv: " + info);

        StockQuotationService.PullerThread puller= new StockQuotationService.PullerThread(info);
        puller.start();

        try {
            puller.join();
            System.out.println("puller join...");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        c.close();
        System.out.println("client quit");
    }
    public void Server(){
        StockQuotationService.Server s = new StockQuotationService.Server("tcp://localhost:6666");
        s.start();
    }
    public void Sleep(int ms){
        try {
            Thread.sleep(ms);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    @Test
    public void testClient(){

        Server();
        Client();

        Sleep(10000);

    }

    @Test
    public void testServer(){

        //StockQuotationService.Server s = new StockQuotationService.Server("tcp://localhost:6666");
        //s.start();
    }
}