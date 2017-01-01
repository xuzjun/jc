package com.chenglun;


import org.zeromq.ZMQ;

public class Main {

    public static void main(String[] args) {
//        testReply();
//        request();

        testPull();
        System.out.println("......");
        testPush();


    }

    private static void request() {
        ZMQ.Context context = ZMQ.context(1);
        ZMQ.Socket socket = context.socket(ZMQ.REQ);

        socket.connect("tcp://127.0.0.1:5555");
        long now = System.currentTimeMillis();
        String request = "hello world my name is \n";
        socket.send(request.getBytes());
        byte[] response = socket.recv();
        System.out.println(response.toString());
        socket.close();
        context.term();
    }

    private static void testReply() {
        ZMQ.Context context = ZMQ.context(1);

        ZMQ.Socket socket = context.socket(ZMQ.REP);
        socket.bind("tcp://*:5555");
        int i = 0;
        int number = 0;
        while (!Thread.currentThread().isInterrupted()) {
            i++;
            if (i == 10000) {
                i = 0;
                System.out.println(++number);
            }
            byte[] request = socket.recv();
            System.out.println("receive : " + new String(request));
            String response = "world";

            socket.send(response.getBytes());
        }
        socket.close();
        context.term();
    }

    private static void sleep(int ms) {
        try {
            Thread.sleep(ms);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }

    private static void testPush() {

        Thread t = new Thread(new Runnable() {
            @Override
            public void run() {
                ZMQ.Context context = ZMQ.context(1);

                ZMQ.Socket pusher = context.socket(ZMQ.PUSH);

                Main.sleep(10000);
                pusher.bind("tcp://*:5557");// bind will block when no client connect it !!!!!!!
                System.out.println("pusher binded!");

                Main.sleep(1000);
                pusher.send("hello".getBytes(), 0);
                Main.sleep(1000);
                System.out.println("pusher send msg");

                pusher.close();
                context.term();

                System.out.println("push thread quit!");

            }
        });

        t.start();
    }

    private static void testPull() {

        Thread t = new Thread(new Runnable() {
            @Override
            public void run() {
                ZMQ.Context context = ZMQ.context(1);
                ZMQ.Socket puller = context.socket(ZMQ.PULL);

                puller.connect("tcp://localhost:5557"); // connect will block if no server bind
                System.out.println("puller connected");

                Main.sleep(10000);
                byte[] msg = puller.recv();
                System.out.println("puller recved");

                System.out.println("pull msg from push :" + new String(msg));
                puller.close();
                context.term();
            }
        });

        t.start();

    }
}




