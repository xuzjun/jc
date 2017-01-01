package com.chenglun.grpc.hello;

import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;

import java.util.concurrent.TimeUnit;
import java.util.logging.Level;
import java.util.logging.Logger;

import com.chenglun.grpc.hello.GreeterGrpc.GreeterBlockingStub;
import org.junit.Test;

/**
 * Created by chenglun on 01/01/2017.
 */
public class GreeterGrpcClientTest {
    public static class GreeterGrpcClient {
        private static final Logger logger = Logger.getLogger(GreeterGrpcClient.class.getName());

        private final ManagedChannel channel;
        private final GreeterBlockingStub blockingStub;

        /** Construct client for accessing RouteGuide server at {@code host:port}. */
        public GreeterGrpcClient(String host, int port) {
            this(ManagedChannelBuilder.forAddress(host, port).usePlaintext(true));
        }

        /** Construct client for accessing RouteGuide server using the existing channel. */
        public GreeterGrpcClient(ManagedChannelBuilder<?> channelBuilder) {
            channel = channelBuilder.build();
            blockingStub = GreeterGrpc.newBlockingStub(channel);
        }

        public void shutdown() throws InterruptedException {
            channel.shutdown().awaitTermination(5, TimeUnit.SECONDS);
        }
        public void sayHello(){
            HelloGreeting hello = HelloGreeting.newBuilder().setName("helloReqest").build();
            HelloReply hr = blockingStub.sayHello(hello);
            info(hr.getMessage());
        }

        private void info(String msg, Object... params) {
            logger.log(Level.INFO, msg, params);
        }

        private void warning(String msg, Object... params) {
            logger.log(Level.WARNING, msg, params);
        }
    }

    @Test
    public void testClient() throws InterruptedException {
        GreeterGrpcClient client = new GreeterGrpcClient("localhost", 8980);
        try {
            client.sayHello();
        }
        finally {
            client.shutdown();
        }
    }
}

