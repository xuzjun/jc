package com.chenglun;

import org.junit.Test;

public class MainTest {
    /* TODO:
      1. client send req (dest, topic)
      2. get rep: pull_info
    */
    public void PrintError(String msg){
        System.out.println( "Error:" + msg);
    }
    public void PrintDebug(String msg){
        System.out.println("Debug:" + msg);
    }
    public void Sleep(int ms){
        try {
            Thread.sleep(ms);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static class Service implements  StockQuotationService.IService{
        private int pusherPortNo = 6667;
        private String topicUrl = "tcp://localhost:%d";
        private StockQuotationService.PusherThread pusher = null;

        public Service(){
        }
        @Override
        public String server(String topic, String stockCode, String startDate, String endDate) {
            String url = String.format(topicUrl, pusherPortNo++);
            pusher = new StockQuotationService.PusherThread(url);
            pusher.start();
            return url;
        }
        @Override
        public void close(){
            if(pusher != null) {
                try {
                    this.pusher.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                pusher = null;
            }
        }
    }

    public void BlockClient(){
        String url = "tcp://localhost:6666";

        StockQuotationService.Client c = new StockQuotationService.Client(url);
        String info = c.call("topic_stock_day_quotation", "Stock_Code", "20120101", "20150101");
        if(info == null){
            PrintError(String.format("get Pull info from server failed:%s!", url));
            c.close();
            return ;
        }
        System.out.println("client recv topic url is : " + info);
        c.makePuller(info, new StockQuotationService.DayQuotationPuller.Handler() {
            @Override
            public void handle(String msg) {
                System.out.println("this from outside -- pull msg:" + msg);
            }
        }).pulling();
        c.close();
    }

    public void Server(){
        Thread sh = new Thread(new Runnable() {
            @Override
            public void run() {
                String url = "tcp://localhost:6666";
                StockQuotationService.Server s = new StockQuotationService.Server(url);
                s.addService("topic_stock_day_quotation",new Service());
                s.run();
                s.close();
            }
        });
        sh.start();
    }

    @Test
    public void testClient(){

        Server();
        BlockClient();
        //Sleep(10000);
    }
}