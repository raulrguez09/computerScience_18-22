import org.apache.thrift.TException;
import org.apache.thrift.transport.TSSLTransportFactory;
import org.apache.thrift.transport.TTransport;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.transport.TSSLTransportFactory.TSSLTransportParameters;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TProtocol;

import java.util.*;

public class JavaClient {
    public static void main(String [] args) {

        try {
            TTransport transport;
            transport = new TSocket("localhost", 9090);
            transport.open();

            TProtocol protocol = new  TBinaryProtocol(transport);
            Calculator.Client client = new Calculator.Client(protocol);

            perform(client);

            transport.close();
        } catch (TException x) {
            x.printStackTrace();
        }
    }

    private static void perform(Calculator.Client client) throws TException
    {
        client.ping();
        System.out.println("ping()");

        System.out.println("Operaciones básicas con double");
        double sum = client.add(1.5,1.5);
        System.out.println("1.5+1.5 =" + sum);

        double sum2 = client.Subtract(4.2,4.1);
        System.out.println("4.2-4.1 = " + sum2);

        double sum3 = client.Multiply(2.5,2.5);
        System.out.println("2.5*2.5 = " + sum3);

        double sum4 = client.Divide(5,2);
        System.out.println("5/2 = " + sum4);
        System.out.println("");

        System.out.println("Operaciones básicas con vectores enteros");
        List<Integer> v1 = new ArrayList<Integer>();
        List<Integer> v2 = new ArrayList<Integer>();
        List<Integer> v3 = new ArrayList<Integer>();
        for(int i = 0; i < 3; i++){
            v1.add(4);
            v2.add(2);
        }
        System.out.print("Primer vector v1: ");
        System.out.print("[" + v1.get(0));
        for(int i = 1; i < v1.size(); i++){
            System.out.print("," + v1.get(i));
        }
        System.out.println("]");

        System.out.print("Segundo vector v2: ");
        System.out.print("[" + v2.get(0));
        for(int i = 1; i < v2.size(); i++){
            System.out.print("," + v2.get(i));
        }
        System.out.println("]");

        v3 = client.listAdd(v1, v2);
        System.out.print("v1 + v2: [" + v3.get(0));
        for(int i = 1; i < v3.size(); i++){
            System.out.print("," + v3.get(i));
        }
        System.out.println("]");

        v3 = client.listSubtract(v1, v2);
        System.out.print("v1 - v2: [" + v3.get(0));
        for(int i = 1; i < v3.size(); i++){
            System.out.print("," + v3.get(i));
        }
        System.out.println("]");


        v3 = client.listMultiply(v1, v2);
        System.out.print("v1 * v2: [" + v3.get(0));
        for(int i = 1; i < v3.size(); i++){
            System.out.print("," + v3.get(i));
        }
        System.out.println("]");


        v3 = client.listDivide(v1, v2);
        System.out.print("v1 / v2: [" + v3.get(0));
        for(int i = 1; i < v3.size(); i++){
            System.out.print("," + v3.get(i));
        }
        System.out.println("]");


    }
}
