package com.chenglun;

import org.zeromq.ZMQ;

/**
 * Created by chenglun on 25/12/2016.
 * TODO: Error Handler && logger
 */
public class Requester {

    private ZMQ.Socket req;
    private ZMQ.Context context;
    private String url;

    public Requester(String url){
        this.context = ZMQ.context(1);
        this.req = context.socket(ZMQ.REQ);
        this.url = url;
    }
    public void connect(){
        this.req.connect(url);
    }

    public void send(String msg){
        this.req.send(msg.getBytes(), 0);
    }
    public String recv(){
        byte[] bytes = this.req.recv();
        return new String(bytes);
    }

    public void close(){
        if(req != null){
            req.close();
            req = null;
        }
        if(context != null){
            context.term();
            context = null;
        }
    }
}
