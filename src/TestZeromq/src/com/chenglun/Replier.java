package com.chenglun;

import org.zeromq.ZMQ;

/**
 * Created by chenglun on 25/12/2016.
 * TODO: Error handler && Logger
 */
public class Replier {
    private ZMQ.Context context;
    private ZMQ.Socket rep;
    private String url;

    public Replier(String url) {

        context = ZMQ.context(1);
        rep = context.socket(ZMQ.REP);
        this.url = url;
    }

    public void bind() {
        this.rep.bind(url);
    }

    public void send(String msg) {
        this.rep.send(msg.getBytes(), 0);
    }

    public String recv() {
        return new String(this.rep.recv(0));
    }

    public void close() {
        if (this.rep != null) {
            this.rep.close();
            this.rep = null;
        }
        if (this.context != null) {
            this.context.term();
            this.context = null;
        }

    }
}
