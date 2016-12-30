package com.chenglun;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

/**
 * Created by chenglun on 25/12/2016.
 */
public class StockQuotationService {

    public static class DayQuotationPuller {
        public static interface Handler{
            void handle(String msg);
        }
        private Puller puller;
        private Handler handle;
        public DayQuotationPuller(String url, Handler handle){
            this.puller = new Puller(url);
            System.out.println("Puller url:" + url);
            this.handle = handle;
        }

        public void pulling(){
            this.puller.connect();
            while(!Thread.currentThread().isInterrupted()){
                String msg = puller.pull();
                if(this.handle != null){
                    this.handle.handle(msg);
                }
                if(puller.isEndMsg(msg)){
                    break;
                }
            }
            this.puller.close();
        }
    }

    public static class DayQuotationPusher{
        private Pusher pusher;
        public DayQuotationPusher(String url){
            this.pusher = new Pusher(url);
            System.out.println("pusher url: " + url);
        }

        public void pushing(){
            this.pusher.bind();

            int cnt = 0;
            while(!Thread.currentThread().isInterrupted()){
                String msg = String.format("Push %d msg from--> %s", cnt++, this.pusher.getUrl());
                this.pusher.push(msg);
                if(cnt >= 20){
                    this.pusher.pushEndMsg();
                    break;
                }
            }
            this.pusher.close();
        }
    }

    public static class PusherThread extends  Thread{
        private DayQuotationPusher pusher;
        public PusherThread(String url){
            this.pusher = new DayQuotationPusher(url);
        }

        @Override
        public void run() {
            this.pusher.pushing();
            System.out.println("Pusher thread is quit!");
        }
    }

    public static class Client{

        private Requester req;
        public Client(String serverUrl){
            this.req = new Requester(serverUrl);
            this.req.connect(); // block and wait for server(reply) bind
        }
        public String call(String topic, String stockCode, String startDate, String endDate){
            //TODO: req.send(String.format("%s %s %s %s", topic, stockCode, startDate, endDate), 0);
            req.send(topic);
            return this.req.recv();
        }

        public DayQuotationPuller makePuller(String url, DayQuotationPuller.Handler handle){
            return new DayQuotationPuller(url, handle);
        }

        public void close() {
            this.req.close();
        }
    }

    public static interface IService{
        public String server(String topic, String stockCode, String startDate, String endDate);
        public void close();
    }

    public static class Server {
        private Replier rep;

        public Server(String localUrl) {
            this.rep = new Replier(localUrl);
        }

        public void addService(String topic, IService service) {
            if(topicMethodMap.containsKey(topic)) {
                topicMethodMap.replace(topic, service);
            }
            else{
                topicMethodMap.put(topic, service);
            }
        }

        public void removeService(String topic) {
            topicMethodMap.remove(topic);
        }

        private HashMap<String, IService> topicMethodMap = new HashMap<>();
        public void run() {
            rep.bind();
            System.out.println("server runing...");

            while (!Thread.currentThread().isInterrupted()) {
                //TODO: topic ==> Object
                String topic = this.rep.recv();
                System.out.println("server recv :" + topic);

                IService service = topicMethodMap.get(topic);
                if (service != null) {
                    //TODO Return value ==> Object
                    String topicUrl = service.server(topic, null, null, null);
                    this.rep.send(topicUrl);
                    System.out.println("server send:" + topicUrl);
                } else {
                    //TODO: PrintWarning("No Topic register");
                }
            }
        }

        public void close(){
            Iterator iter = topicMethodMap.entrySet().iterator();
            while (iter.hasNext()) {
                Map.Entry<String, IService> entry = (Map.Entry<String, IService>) iter.next();
                IService service = entry.getValue();
                service.close();
            }
            this.topicMethodMap.clear();
            this.rep.close();
        }
    }


}
