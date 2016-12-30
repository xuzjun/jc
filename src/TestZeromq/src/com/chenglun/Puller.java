
package com.chenglun;

import org.zeromq.ZMQ;

/**
 * Created by chenglun on 25/12/2016.
 */
public class Puller {

    public final String STOP_MSG = "";

    private String url;
    private ZMQ.Context context;
    private ZMQ.Socket puller;
    public Puller(String url){
        this.url = url;

        context = ZMQ.context(1);
        puller = context.socket(ZMQ.PULL);
    }

    public void connect(){
        this.puller.connect(this.url);
    }

    public String pull(){
        return new String(this.puller.recv(0));
    }

    public boolean isEnd(){

    }

    public void close(){
        if(puller != null){
            this.puller.close();
            this.puller = null;
        }
        if(context != null){
            this.context.term();
            this.context = null;
        }
    }
}
