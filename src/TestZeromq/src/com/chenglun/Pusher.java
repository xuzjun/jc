package com.chenglun;

import org.zeromq.ZMQ;

/**
 * Created by chenglun on 25/12/2016.
 */
public class Pusher {
    private ZMQ.Context context;
    private ZMQ.Socket pusher;
    private String url;

    public final String END_MSG = "";

    public String getUrl(){
        return url;
    }

    public Pusher(String url){
        this.url = url;
        context = ZMQ.context(1);
        pusher = context.socket(ZMQ.PUSH);
    }

    public void bind(){
        this.pusher.bind(this.url);
    }

    public void push(String msg){
        if(msg != null)
            this.pusher.send(msg.getBytes(), 0);
        else
            ;//Error Handler && log
    }
    public void pushEndMsg(){
        this.push(END_MSG);
    }

    public void close(){
        if(pusher != null){
            pusher.close();
            pusher = null;
        }
        if(context != null){
            context.term();
            context = null;
        }
    }
}
