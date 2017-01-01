package com.chenglun.grpc.hello;

import org.junit.Test;

import io.grpc.Server;
import io.grpc.ServerBuilder;

import java.io.IOException;
import java.util.logging.Logger;


/**
 * Created by chenglun on 01/01/2017.
 */
public class GreeterGrpcServerTest {

    public static class HelloServer {
        private static final Logger logger = Logger.getLogger(HelloServer.class.getName());

        private final int port;
        private final Server server;

        public HelloServer(int port) throws IOException {
            this(ServerBuilder.forPort(port), port);
        }

        public HelloServer(ServerBuilder<?> serverBuilder, int port){
            this.port = port;
            server = serverBuilder.addService(new HelloService())
                    .build();
        }

        /** Start serving requests. */
        public void start() throws IOException {
            server.start();
            logger.info("Server started, listening on " + port);
            Runtime.getRuntime().addShutdownHook(new Thread() {
                @Override
                public void run() {
                    // Use stderr here since the logger may has been reset by its JVM shutdown hook.
                    System.err.println("*** shutting down gRPC server since JVM is shutting down");
                    HelloServer.this.stop();
                    System.err.println("*** server shut down");
                }
            });
        }

        /** Stop serving requests and shutdown resources. */
        public void stop() {
            if (server != null) {
                server.shutdown();
            }
        }

        /**
         * Await termination on the main thread since the grpc library uses daemon threads.
         */
        private void blockUntilShutdown() throws InterruptedException {
            if (server != null) {
                server.awaitTermination();
            }
        }

        private static class HelloService extends GreeterGrpc.GreeterImplBase {
            HelloService(){
            }

            @Override
            public void sayHello(com.chenglun.grpc.hello.HelloGreeting request,
                                 io.grpc.stub.StreamObserver<com.chenglun.grpc.hello.HelloReply> responseObserver) {
                System.out.println(request.getName());
                responseObserver.onNext(HelloReply.newBuilder().setMessage("HelloReply").build());
                responseObserver.onCompleted();
            }

        }
    }
    @Test
    public void testServer(){
        HelloServer server = null;
        try {
            server = new HelloServer(8980);

            server.start();
            server.blockUntilShutdown();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

