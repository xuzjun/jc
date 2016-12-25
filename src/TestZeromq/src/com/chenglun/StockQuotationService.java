package com.chenglun;

/**
 * Created by chenglun on 25/12/2016.
 */
public class StockQuotationService {


    public static class PullerThread extends  Thread{
        private Puller puller;
        public PullerThread(String url){
            this.puller = new Puller(url);
        }
        @Override
        public void run() {
            this.puller.connect();
            while(!this.isInterrupted()){
                String msg = this.puller.pull();
                System.out.println("pull msg:" + msg);
                if(msg.equals("")){
                    break;
                }
            }
            puller.close();
            System.out.println("Puller thread is quit!");
        }
    }

    public static class PusherThread extends  Thread{
        private Pusher pusher;
        public PusherThread(String url){
            this.pusher = new Pusher(url);
        }

        @Override
        public void run() {
            this.pusher.bind();

            int cnt = 0;
            while(!this.isInterrupted()){
                this.pusher.push(String.format("Push %d msg from--> %s", cnt++, this.pusher.getUrl()));
                if(cnt >= 20){
                    this.pusher.push(""); // push an empty-string for puller quit
                    break;
                }
            }
            this.pusher.close();
            System.out.println("Pusher thread is quit!");
        }
    }

    public static class Client{

        private Requester req;
        public Client(String serverUrl){

            this.req = new Requester(serverUrl);
            this.req.connect(); // block and wait for server(reply) bind
        }
        public String getTopicPushInfo(String topic, String stockCode, String startDate, String endDate){
            //TODO: req.send(String.format("%s %s %s %s", topic, stockCode, startDate, endDate), 0);
            req.send(topic);
            return this.req.recv();
        }

        public void close() {
            this.req.close();
        }
    }

    public static interface IServer{
        public String getTopicUrl(String topic, String stockCode, String startDate, String endDate);
        public void close();
    }

    public static class Service implements  IServer{
        private int pusherPortNo = 6667;
        private String topicUrl = "tcp://localhost:%d";
        private PusherThread pusher = null;
        public Service(){
        }
        @Override
        public String getTopicUrl(String topic, String stockCode, String startDate, String endDate) {
            String url = String.format(topicUrl, pusherPortNo++);
            pusher = new PusherThread(url);
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
    public static class Server extends Thread{

        private Replier rep;
        private IServer iServer;

        public Server(String localUrl){
            this.iServer = new Service();
            this.rep = new Replier(localUrl);
        }



        @Override
        public void run(){
            rep.bind();

            while(!isInterrupted())
            {
                System.out.println("server runing...");
                String topic = this.rep.recv();
                System.out.println("server recv :" + topic);

                if(topic.equals("topic_stock_day_quotation")) {
                    if(this.iServer != null) {
                        String topicUrl = this.iServer.getTopicUrl(topic, null, null, null);//TODO:
                        this.rep.send(topicUrl);
                        System.out.println("server send:" + topicUrl);
                    }
                    else{
                        //TODO: ErrorPrint...
                    }
                }
                else{
                    //TODO:Error input : no valid topic
                }
            }
            this.close();
        }

        private void close(){
            this.iServer.close();
            System.out.println("IServer Closed!");
            try {
                sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            this.rep.close();
        }
    }


}
